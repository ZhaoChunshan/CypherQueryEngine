/*=============================================================================
# Filename: BGPQuery.h
# Author: Linglin Yang
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

#include "../Query/QueryTree.h"
#include "../Executor/p_intermediate_results.h"
#include "../Util/Triple.h"
#include "../KVstore/KVstore.h"
#include "../Value/Value.h"
#include "../Value/Expression.h"
#include <cstdlib>
#include <utility>


/* make g++ happy */
using Expression = GPStore::Expression;
class PIntermediateResult;

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
//  std::map<unsigned, Expression *> properties_;
  std::vector<Expression *> exps_;                  // pg Filter on this var, such as filter on prop(a.age = 10)

  // degree_ is the num of how many triples include this item,
  unsigned degree_;                               // rdf, pg

  /* Selection Infomation of this var and its props */
  // todo: use this to denote whether this var is selected or not
//  If selected_ = false, then it must not appeared in any Expression, and it has no selected props
  bool selected_;                                 // rdf, pg
  vector<unsigned> selected_prop_ids_;      // pg, we may select props of a node even if the node itself is not selected

  // zhouyuqi, if use this, please add initial this in VarDescriptor(*****)
  int rewriting_position_;
  // -1 if not allocated a id in BasicQuery
  int basic_query_id;

  bool IsSatellite() const { return this->degree_ == 1 && (!selected_); };
  // int RewritingPosition(){return this->rewriting_position_;};
  // calculate the exact position in final result

  VarDescriptor(unsigned id, VarType var_type, const string &var_name);

  // Constructor for PG Node Var
  // VarDescriptor(unsigned id, VarType var_type, const string &var_name, const std::vector<unsigned>& labels_or_types, const std::map<unsigned, GPStore::Value>& props_, const std::vector<Expression*>& exps);

  // Constructor for PG Edge Var
  VarDescriptor(unsigned id, VarType var_type, const string &var_name, char edge_direct, int range_left, int range_right, const std::vector<unsigned>& labels_or_types, const std::map<unsigned, GPStore::Value>& props_, const std::vector<Expression*>& exps);

  virtual ~VarDescriptor() = default;

  // bool get_edge_type(int edge_id);
  // int get_edge_nei(int edge_id);
  // int get_edge_index(int edge_id);
  bool IsIthEdgeLinkedVarSO(unsigned i_th_edge);
  bool IsIthEdgePreVar(unsigned i_th_edge);

  /**
   * @brief 更新一个节点的邻居信息
   * @param edge_nei_id: 该so变量邻接的节点的varid(or nodeId)
   * @param edge_id: 该so变量邻接的边的varid(or edgeId)
   * @param edge_direct_type: 该so变量的边是出 还是 入
   * @param edge_index: 此边在BGP三元组中位置
   * @param pre_is_var: 边是否是变量
   * @param edge_nei_is_var: 链接节点是否变量
  */
  void update_so_var_edge_info(unsigned edge_nei_id, unsigned edge_id, char edge_direct_type, unsigned edge_index, bool pre_is_var, bool edge_nei_is_var);

  void update_pre_var_edge_info(unsigned s_id, unsigned o_id, bool s_is_var, bool o_is_var, unsigned edge_index);

  void update_statistics_num();

  //TODO, default appoint a var selected_ = false to true
  void update_select_status(bool selected);

  void update_selected_props(const std::vector<unsigned> &props_id);

  void print(KVstore *kvstore);
};

class NodeVarDescriptor : public VarDescriptor {
 public:
  // Adjacent Edges
  vector<unsigned> so_e_index_;           // 第i条边在BGP三元组中的位置
  vector<char> so_e_dir_;         // see Util::EDGE_[OUT|IN|UNDIRECT]
  vector<EdgeType> so_e_type_;  // 第i边常量还是变量
  vector<unsigned> so_e_eid_;             // Adjacent Edge, VarID(varialbe) or Eid(constant)
  // Neighbor nodes
  vector<NodeType> so_nei_type_;        // 指定变量还是常量
  vector<unsigned> so_e_nei_;             // 变量，为varid,常量，为KV id
};

class EdgeVarDescriptor : public VarDescriptor {
 public:
  bool is_predicate_var;
  int range_left_, range_right_;           // pg rangeLeft=rangeRight=1: it's regular edge; rangeRight=-1 means +INF

  // Adjacent Node information of this Edge var.
  // If the edge var is not a predicate var in SPARQL query, then the vectors below only contain one element.
  vector<unsigned> s_id_;
  vector<NodeType> s_type_;
  vector<unsigned> o_id_;
  vector<NodeType> o_type_;
  vector<unsigned> pre_edge_index_;   // 该边变量在BGP三元组中的位置
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
// Step6: Optionally set VaraibleBinding using setVariableBinding
class BGPQueryNew {
 public:
    ExecMode mode_;
    bool is_cypher_;
    bool distinct_query;
    bool limit_query;
    unsigned limit_num;
    shared_ptr<std::vector<Order>> ordered_by_expressions_;

    std::shared_ptr<PIntermediateResult> variable_binding_;         // 最终结果也放到这里

    std::vector<Expression *> exps_;
    /* RDF ONLY */


	// all item, including s, p, o, whether var or not
	map<string, unsigned > item_to_freq;   

	// map var item to its position in var_vector
	map<string, unsigned > var_item_to_position;
	map<string, unsigned > var_item_to_id;

    /* BOTH RDF AND PG */

	map<unsigned, unsigned> id_position_map;
	map<unsigned, unsigned> position_id_map;


	vector<unsigned> s_id_;
	vector<unsigned> e_id_;
	vector<unsigned> o_id_;
    vector<bool> directed_;    // false means this edge is an undirected edge


	vector<bool> s_const_;
	vector<bool> e_const_;
	vector<bool> o_const_;

	// all var, whether pre or not_pre, whether selected or not_selected
	vector<shared_ptr<VarDescriptor>> var_vector;

	vector<unsigned> so_var_id;
	vector<unsigned> pre_var_id;
	vector<unsigned> var_id_vec;        // 存放所有变量的id，下标是index(position)，返回id

	// vector indicate selected var position in var_vector, whether pre_var or so_var
	vector<unsigned> selected_var_id;

    // vector indicate the position of var whose props are selected (PG)
    vector<unsigned> selected_prop_var_id;    

	vector<string> pre_var_names;

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

    CandidateList var_candidates_cache_;


    BGPQueryNew();
	~BGPQueryNew();
    /**
     * @brief set all statistic num to zero
    */
	void initial();

    // Add triple function for RDF
	void AddTriple(const Triple& _triple);

	// return var_id in var_vector, if not find, return -1; RDF only
	unsigned get_var_id_by_name(const string& var_name);
    // rdf, pg
	string get_var_name_by_id(unsigned var_id);
    // rdf only
	unsigned get_var_index_by_name(const string& var_name);

    // rdf, pg
	unsigned get_var_id_by_index(unsigned index);
    // rdf, pg
	unsigned get_var_position_by_id(unsigned id);
    // rdf, pg
	const vector<unsigned> &get_var_id_vec();
    // rdf.pg
	const shared_ptr<VarDescriptor> &get_vardescrip_by_index(unsigned index);
    // rdf, pg
	const shared_ptr<VarDescriptor> &get_vardescrip_by_id(unsigned id);

    bool CheckIthEdgePredicate(unsigned ith_edge);

	// void update_so_var_edge_info(uns);

	void ScanAllVar(const vector<string>& _query_var);  // rdf only
	bool build_edge_info(KVstore *_kvstore);    // rdf only
	void count_statistics_num();                // rdf only

	bool EncodeBGPQuery(KVstore* _kvstore, const vector<string>& _query_var, bool distinct = false); // rdf only



	void ScanAllVarByBigBGPID(BGPQueryNew *big_bgpquery, const vector<string>& _query_var);    // rdf only
	bool EncodeSmallBGPQuery(BGPQueryNew *big_bgpquery_, KVstore* _kvstore,
							 const vector<string>& _query_var, bool distinct = false);// rdf only

	static bool CheckConstBGPExist(const vector<Triple> &triple_vt, KVstore *kvstore);// rdf only

	unsigned get_triple_num();
	unsigned get_total_var_num();
	unsigned get_pre_var_num();


	unsigned get_var_degree_by_id(unsigned var_id);
	VarDescriptor::VarType get_var_type_by_id(unsigned var_id);

	bool is_var_selected_by_id(unsigned var_id);

	// for EntiType var
	unsigned get_so_var_edge_index(unsigned var_id, int edge_id);
	bool get_so_var_edge_direct_type(unsigned var_id, unsigned edge_id);
	unsigned get_so_var_edge_nei(unsigned var_id, unsigned edge_id);
	VarDescriptor::NodeType get_so_var_edge_nei_type(unsigned var_id, unsigned edge_id);
	unsigned get_so_var_edge_eid(unsigned var_id, unsigned edge_id);
	VarDescriptor::EdgeType get_so_var_edge_var_const_type(unsigned var_id, unsigned edge_id);


	// for PreType var
	unsigned get_pre_var_edge_index(unsigned var_id, unsigned edge_id);
	unsigned get_pre_var_s_id(unsigned var_id, unsigned edge_id);
	VarDescriptor::NodeType get_pre_var_s_type(unsigned var_id, unsigned edge_id);
	unsigned get_pre_var_o_id(unsigned var_id, unsigned edge_id);
	VarDescriptor::NodeType get_pre_var_o_type(unsigned var_id, unsigned edge_id);

	bool check_already_joined_pre_var(vector<unsigned> &already_node, unsigned pre_var_id);

	const vector<Triple> &get_triple_vt();
	const Triple &get_triple_by_index(unsigned index);


	bool is_var_satellite_by_index(unsigned index);
	bool is_var_satellite_by_id(unsigned id);

	void print(KVstore * kvstore);

//	void set_var_candidate_cache(unsigned var_id, shared_ptr<IDList> candidate_cache);

//	shared_ptr<IDList> get_candidate_list_by_d var_id);
    CandidateList& get_all_candidates();


	vector<unsigned*>* get_result_list_pointer();
    vector<vector<TYPE_ENTITY_LITERAL_ID>>* get_result_list_pointer1();
    unique_ptr<unsigned[]>& resultPositionToId();
    /* tells if the var_id appears in the position of
     * subject / predicate / object
     * @returns (is_entity,is_literal,is_predicate)*/
    std::tuple<bool,bool,bool> GetOccurPosition(int var_id);


    // add code here

    void setExecMode(ExecMode exec_mode);

    /**
     * @brief 将一个VarDescriptor加入到变量数组中，但此Descriptor需要已经初始化好Basic Infomation和Selection Information。
     * 副作用：更新id_position_map和position_id_map,so_var_id,pre_var_id, var_id_vec, selected_var_id, selected_prop_var_id;   
     * selected_pre_var_num; selected_so_var_num;  total_selected_var_num;
     * unsigned total_pre_var_num;unsigned total_so_var_num;unsigned total_var_num;
    */
    void addVarDescriptor(shared_ptr<VarDescriptor>& var_desc_shared_ptr);
    /**
     * @brief 将Cypher的三元组(s, e, o)添加到s_id_  e_id_; o_id_;之中.副作用：更新每个Vardescriptor的相邻信息。
     * @param s: 主语的变量id
     * @param e: 边的变量id
     * @param o: 宾语的变量id
    */
    void addCypherTripleVarId(unsigned s, unsigned e, unsigned o);
    void addFilterExp(Expression *exp);
    void setVariableBinding(std::shared_ptr<PIntermediateResult>& var_bind_);
    

private:
	vector<Triple> triple_vt;
    vector<unsigned*> result_list;
    vector<vector<TYPE_ENTITY_LITERAL_ID>> result_list1;
    unique_ptr<unsigned[]> result_position_to_id;
};


#endif //GSTORE_BGPQUERY_H
