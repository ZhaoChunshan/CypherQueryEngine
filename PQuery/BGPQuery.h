/**
 * \  /\  /   /\  | )  /\  /  |  /\  /  |----
 *  \/  \/   /--\ | \ /  \/   | /  \/   |___T
 *
 *  Debug only , donot use!
 *
 */




/*=============================================================================
# Filename: BGPQuery.h
# Author: Linglin Yang && Chunshan Zaho
# Warning: Donot copy this File; It's Just Used for debug, Not Final Version.
# Mail: linglinyang@stu.pku.edu.cn
=============================================================================*/


// READ THIS FIRST
// According to need of rewriting, the whole BGP(including all triples) invokes EncodeBGPQuery,
// the split small BGP invokes EncodeSmallBGPQuery(the id is same as above, so maybe not begin with 0 or not continuous).
// For example, the whole query is:
// select ?s ?o ?o2 ?o3 where{
// 	?s p1 ?o.
// 	?s p2 ?o2.
// 	Optional{?s p3 ?o3}
// }
// Then after EncodeBGPQuery, the var-encode map is: {{?s:0}, {?o:1}, {?o2:2}, {?o3:3}},
// and in small optional BGP(?s p3 ?o3), the var-encode map is {{?s:0}, {?o3:3}}, not {{?s:0}, {?o3:1}}.

#ifndef GSTORE_BGPQUERY_H
#define GSTORE_BGPQUERY_H

#include "../Executor/p_intermediate_results.h"
#include "../Value/Value.h"
#include "../Value/Expression.h"
#include "../Util/Util.h"
#include <cstdlib>
#include <utility>
#include <unordered_map>

using Expression = GPStore::Expression;

class VarDescriptor {
public:
    enum class VarType { Node, Edge, NotDecided };     // rdf,pg, note: NotDecided only used in PlanGenerator
    static std::string GetString(VarType t);        // rdf,pg
    enum class NodeType { VarNodeType, ConNodeType };  // rdf,pg
    enum class EdgeType { VarEdgeType, ConEdgeType };  // rdf,pg

    /* Basic Information of this var. */
    unsigned id_;                                     // rdf,pg
    VarType var_type_;                                // rdf,pg
    std::string var_name_;                            // rdf,pg, maybe empty for pg anno var
    std::vector<unsigned> labels_or_types_;           // pg conjunction of labels or disjunction of types
    std::vector<Expression *> exps_;                  // pg Filter on this var, such as filter on prop(a.age = 10)

    // degree_ is the num of how many triples include this item,
    unsigned degree_;                               // rdf, pg

    /* Selection Infomation of this var and its props */
    // todo: use this to denote whether this var is selected or not
//  If selected_ = false, then it must not appeared in any Expression, and it has no selected props
    bool selected_;                                 // rdf, pg
    std::vector<unsigned> selected_prop_ids_;      // pg

    // zhouyuqi, if use this, please add initial this in VarDescriptor(*****)
    int rewriting_position_;
    // -1 if not allocated a id in BasicQuery
    int basic_query_id;

    bool IsSatellite() const { return this->degree_ == 1 && (!selected_); };
    // int RewritingPosition(){return this->rewriting_position_;};
    // calculate the exact position in final result

    VarDescriptor(unsigned id, VarType var_type, const std::string &var_name);

    // Constructor for PG Node Var Or Edge Var
    VarDescriptor(unsigned id, VarType var_type, const std::string &var_name, const std::vector<unsigned>& labels_or_types, const std::vector<Expression*>& exps);

    virtual ~VarDescriptor() = default;

    // bool get_edge_type(int edge_id);
    // int get_edge_nei(int edge_id);
    // int get_edge_index(int edge_id);

    void update_statistics_num();

    //TODO, default appoint a var selected_ = false to true
    void update_select_status(bool selected);

    void update_selected_props(const std::vector<unsigned> &props_id);

    void print(KVstore *kvstore);
};

class NodeVarDescriptor : public VarDescriptor {
public:
    // Adjacent Edges
    std::vector<unsigned> so_e_index_;           // 第i条边在BGP三元组中的位置
    std::vector<char> so_e_dir_;         // see Util::EDGE_[OUT|IN|UNDIRECT]
    std::vector<EdgeType> so_e_type_;  // 第i边常量还是变量
    std::vector<unsigned> so_e_eid_;             // Adjacent Edge, VarID(varialbe) or Eid(constant)
    // Neighbor nodes
    std::vector<NodeType> so_nei_type_;        // 指定变量还是常量
    std::vector<unsigned> so_e_nei_;             // 变量，为varid,常量，为KV id

    NodeVarDescriptor(unsigned id, VarType var_type, const std::string &var_name, const std::vector<unsigned>& labels_or_types, const std::vector<Expression*>& exps);

    bool IsIthEdgeLinkedVarSO(unsigned i_th_edge);
    bool IsIthEdgePreVar(unsigned i_th_edge);

    void update_so_var_edge_info(unsigned edge_nei_id, unsigned edge_id, char edge_direct_type, unsigned edge_index, bool pre_is_var, bool edge_nei_is_var);

};

class EdgeVarDescriptor : public VarDescriptor {
public:
    bool is_predicate_var;
    int range_left_, range_right_;           // pg rangeLeft=rangeRight=1: it's regular edge; rangeRight=-1 means +INF

    // Adjacent Node information of this Edge var.
    // If the edge var is not a predicate var in SPARQL query, then the vectors below only contain one element.
    std::vector<unsigned> s_id_;
    std::vector<NodeType> s_type_;
    std::vector<unsigned> o_id_;
    std::vector<NodeType> o_type_;
    std::vector<unsigned> pre_edge_index_;   // 该边变量在BGP三元组中的位置

    EdgeVarDescriptor(unsigned id, VarType var_type, const std::string &var_name, const std::vector<unsigned>& labels_or_types,
                      const std::vector<Expression*>& exps, bool is_sparql_pre, int range_left, int range_right);

    void update_pre_var_edge_info(unsigned s_id, unsigned o_id, bool s_is_var, bool o_is_var, unsigned edge_index);

};

enum class ExecMode {Homomorphism, NodeIsomorphism, EdgeIsomorphism};    // rdf, pg

// How to use this class?
// For SPARQL Reader:
// First, all triples need insert one by one by AddTriple
// Then, invoke the function EncodeBGPQuery, this will give every var(selected or not, predicate or not predicate) an id
// If you have special need to encode one small BGP, please invoke the function EncodeSmallBGPQuery,
// and pass big BGPQuery pointer to it, it will keep the var with the same string name having same.
// For Cypher Reader:
// Step1: define a BGPQuery like p = new PBGPQuery()
// Step2: add VarDescriptor one by one by addVarDescriptor;
// Step3: add triple one by one by addCypherTripleVarId;
// Step4: add filter expression among several variables using addFilterExp
// Step5: Optionally set BGPMode to EdgeIsomorphism(Default is Homomorphism)
// Step6: Optionally set Candidate Set
class BGPQueryNew {
public:
    ExecMode mode_;
    bool single_node_;
    bool is_cypher_;
    bool distinct_query;
    bool limit_query;
    unsigned limit_num;

    std::shared_ptr<PIntermediateResult> variable_binding_;         // 最终结果放到这里

    std::vector<Expression *> exps_;
    /* RDF ONLY */


    // all item, including s, p, o, whether var or not
    std::map<std::string, unsigned > item_to_freq;

    // map var item to its position in var_vector
    std::map<std::string, unsigned > var_item_to_position;
    std::map<std::string, unsigned > var_item_to_id;

    /* BOTH RDF AND PG */

    std::map<unsigned, unsigned> id_position_map;
    std::map<unsigned, unsigned> position_id_map;


    std::vector<unsigned> s_id_;
    std::vector<unsigned> e_id_;
    std::vector<unsigned> o_id_;
    std::vector<bool> directed_;    // false means this edge is an undirected edge


    std::vector<bool> s_const_;
    std::vector<bool> e_const_;
    std::vector<bool> o_const_;

    // all var, whether pre or not_pre, whether selected or not_selected
    std::vector<std::shared_ptr<VarDescriptor>> var_vector;

    std::vector<unsigned> so_var_id;
    std::vector<unsigned> pre_var_id;
    std::vector<unsigned> var_id_vec;        // 存放所有变量的id，下标是index(position)，返回id

    // vector indicate selected var id in var_vector, whether pre_var or so_var
    std::vector<unsigned> selected_var_id;

    // vector indicate the id of var whose props are selected (PG)
    std::vector<unsigned> selected_prop_var_id;

//	maybe not used
//	this record all pre_var position in item
//	vector<int> pre_var_position;

    int selected_pre_var_num;
    int selected_so_var_num;
    int total_selected_var_num;

    unsigned total_pre_var_num;
    unsigned total_so_var_num;
    unsigned total_var_num;

//	maybe not use join_pre_var_num
    int join_pre_var_num;
    int join_so_var_num;
    int total_join_var_num;

    std::shared_ptr<CandidateList> var_candidates_cache_;
    std::shared_ptr<std::unordered_map<std::string, GPStore::Value>> param_;

    BGPQueryNew();
    ~BGPQueryNew();
    /**
     * @brief set all statistic num to zero
    */
    void initial();



    // return var_id in var_vector, if not find, return -1; RDF only
    unsigned get_var_id_by_name(const std::string& var_name);
    // rdf, pg
    std::string get_var_name_by_id(unsigned var_id);
    // rdf only
    unsigned get_var_index_by_name(const std::string& var_name);

    // rdf, pg
    unsigned get_var_id_by_index(unsigned index);
    // rdf, pg
    unsigned get_var_position_by_id(unsigned id);
    // rdf, pg
    const std::vector<unsigned> &get_var_id_vec();
    // rdf.pg
    const std::shared_ptr<VarDescriptor> &get_vardescrip_by_index(unsigned index);
    // rdf, pg
    const std::shared_ptr<VarDescriptor> &get_vardescrip_by_id(unsigned id);

    bool CheckIthEdgePredicate(unsigned ith_edge);

    // void update_so_var_edge_info(uns);

    void count_statistics_num();                // rdf only


    unsigned get_total_var_num();
    unsigned get_pre_var_num();


    unsigned get_var_degree_by_id(unsigned var_id);
    VarDescriptor::VarType get_var_type_by_id(unsigned var_id);

    bool is_var_selected_by_id(unsigned var_id);

    // for EntiType var
    unsigned get_so_var_edge_index(unsigned var_id, int edge_id);
    char get_so_var_edge_direct_type(unsigned var_id, unsigned edge_id);    // see Util:EDGE_IN, OUT, UNDIRECT
    unsigned get_so_var_edge_nei(unsigned var_id, unsigned edge_id);
    VarDescriptor::NodeType get_so_var_edge_nei_type(unsigned var_id, unsigned edge_id);
    unsigned get_so_var_edge_eid(unsigned var_id, unsigned edge_id);
    VarDescriptor::EdgeType get_so_var_edge_var_const_type(unsigned var_id, unsigned edge_id);


    // for PreType var
    // Find this Pre Var 's index in Triples. [The ith occurance]
    unsigned get_pre_var_edge_index(unsigned var_id, unsigned edge_id);
    unsigned get_pre_var_s_id(unsigned var_id, unsigned edge_id);
    VarDescriptor::NodeType get_pre_var_s_type(unsigned var_id, unsigned edge_id);
    unsigned get_pre_var_o_id(unsigned var_id, unsigned edge_id);
    VarDescriptor::NodeType get_pre_var_o_type(unsigned var_id, unsigned edge_id);

    bool check_already_joined_pre_var(std::vector<unsigned> &already_node, unsigned pre_var_id);




    bool is_var_satellite_by_index(unsigned index);
    bool is_var_satellite_by_id(unsigned id);

    void print(KVstore * kvstore);

//	void set_var_candidate_cache(unsigned var_id, shared_ptr<IDList> candidate_cache);

//	shared_ptr<IDList> get_candidate_list_by_d var_id);
    CandidateList& get_all_candidates();


    std::vector<unsigned*>* get_result_list_pointer();
    std::vector<std::vector<TYPE_ENTITY_LITERAL_ID>>* get_result_list_pointer1();
    std::unique_ptr<unsigned[]>& resultPositionToId();
    /* tells if the var_id appears in the position of
     * subject / predicate / object
     * @returns (is_entity,is_literal,is_predicate)*/
    std::tuple<bool,bool,bool> GetOccurPosition(int var_id);


    // add code here

    void setExecMode(ExecMode exec_mode);

    void addVarDescriptor(std::shared_ptr<VarDescriptor>& var_desc_shared_ptr);
    /**
     * @brief 将Cypher的三元组(s, e, o)添加到s_id_  e_id_; o_id_;之中.副作用：更新每个Vardescriptor的相邻信息。
     * @param s: 主语的变量id
     * @param e: 边的变量id
     * @param o: 宾语的变量id
    */
    void addCypherTripleVarId(unsigned s, unsigned e, unsigned o, bool direct);
    void addFilterExp(Expression *exp);

private:

    std::vector<unsigned*> result_list;
    std::vector<std::vector<TYPE_ENTITY_LITERAL_ID>> result_list1;
    std::unique_ptr<unsigned[]> result_position_to_id;
};


#endif //GSTORE_BGPQUERY_H
