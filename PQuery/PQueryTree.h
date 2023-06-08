#ifndef PQUERY_PQUERYTREE_H
#define PQUERY_PQUERYTREE_H

#include "PQueryOperator.h"
#include <unordered_map>
#include <string>
#include "../Value/Value.h"
#include "../PParser/CypherAST.h"
#include "../Util/Util.h"

/**
 * @brief Class PTreeNode: node of the PlanTree. Each PlanTree node has one or two children.
 * */
class PTreeNode{
public:
    std::unique_ptr<PQueryOperator> operator_;
    PTreeNode *left_, *right_;
    PTreeNode():left_(nullptr), right_(nullptr) { }
    ~PTreeNode();
    void print(int dep = 0) const;
};

/**
 * @brief Generate Plan Tree.
 * */
class PQueryTree {
public:
    // Generate a plan tree for a CypherAST.
    static PTreeNode *GenerateQueryTree(const CypherAST *cypher_ast);

private:
    PTreeNode *root_;
    std::shared_ptr<std::vector<std::string>> id2var_name_;                 // decode: var_id To var_name
    std::shared_ptr<std::unordered_map<std::string, unsigned>> prop2id_;    // a cache of PStore: prop=>id
    std::shared_ptr<std::map<unsigned, std::string>> prop_id2string_;       // valid property_id To propertyKeyNames

    PQueryTree(const std::shared_ptr<std::vector<std::string>> &id2var_name,
               const std::shared_ptr<std::unordered_map<std::string, unsigned>> &prop2id,
               const std::shared_ptr<std::map<unsigned, std::string>> &prop_id2string);

    ~PQueryTree();

    // Generate Functions:

    void GetQueryTree(const CypherAST *cypher_ast);

    PTreeNode *GetQueryTree(const SingleQueryAST *single_query);

    PTreeNode *GetQueryTree(const QueryUnitAST *query_unit, PTreeNode *tree);

    BGPOperator *GetBGPFromMatch(const MatchAST *match);

    PTreeNode *GetQueryTree(const UnwindAST *unwind, PTreeNode *tree);

    PTreeNode *GetQueryTree(const InQueryCallAST *call, PTreeNode *tree);

    PTreeNode *GetQueryTree(const WithReturnAST *with_return, PTreeNode *tree);

    PTreeNode *GetQueryTree(const CreateAST *_create, PTreeNode *tree);

    PTreeNode *GetQueryTree(const DeleteAST *_delete, PTreeNode *tree);

    PTreeNode *GetQueryTree(const SetAST *_set, PTreeNode *tree);

    PTreeNode *GetQueryTree(const RemoveAST *_remove, PTreeNode *tree);

    // Optimizer Functions && Helper functions

    void ClipVarset(PTreeNode *tree, const PVarset<unsigned> &required);

    PTreeNode * FilterPushdown(PTreeNode *tree, PTreeNode * parent, GPStore::Expression * filter);

    void RewriteBGPOperator(BGPOperator * bgp);

    BGPOperator *MergeBGP(std::vector<BGPOperator *> &bgp);

    PTreeNode *SplitBGPByConnectedComponent(BGPOperator *bgp, PTreeNode *tree);

    std::pair<std::map<unsigned, unsigned> *, unsigned>
    CalculateBGPConnectedComponent(const BGPOperator *bgp);


    PTreeNode *GenerateCypherUnion(PTreeNode *left, PTreeNode *right);

    PTreeNode *GenerateDistinct(PTreeNode *tree);

    PTreeNode *GenerateRelatedFilters(std::vector<GPStore::Expression *> &filters, PTreeNode *tree);

    PTreeNode *GenerateBinaryOperator(PTreeNode *left, PTreeNode *right, PQueryOperator::OperatorType op);

    PTreeNode *GenerateShortestPath(GPStore::RigidPattern *rigid_pattern, PTreeNode * tree);


    void _dfs_label(unsigned u, const std::map<unsigned, std::set<unsigned>> &adj, std::map<unsigned, unsigned> &labels,
               unsigned cur_label);

    std::pair<std::map<unsigned, unsigned> *, unsigned>
    calculateGraphConnectedComponent(const std::map<unsigned, std::set<unsigned>> &adj);

    template<class T>
    static void RemoveNullPtr(std::vector<std::unique_ptr<T> > & ptr_vec){
        std::vector<std::unique_ptr<T>>  new_vec;
        for(auto & ptr : ptr_vec){
            if(ptr != nullptr){
                new_vec.emplace_back(ptr.release());
            }
        }
        ptr_vec.swap(new_vec);
    }
};

#endif