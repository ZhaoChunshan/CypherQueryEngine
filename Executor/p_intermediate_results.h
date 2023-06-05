#ifndef P_INTERMEDIATE_RESULTS_H
#define P_INTERMEDIATE_RESULTS_H

#include <map>
#include <vector>
#include <list>
#include "../Value/Value.h"

using GPStore::Value;

using DataGraphNodeIdType = unsigned;
using DataGraphEdgeIdType = unsigned long long;
using LabelIdType = unsigned;
using PropertyIdType = unsigned;
using VarNodeIdType = unsigned;


using PathType = std::vector<DataGraphNodeIdType>;
using SPOEmbeddingType = std::vector<DataGraphNodeIdType>; // @attention: of p is LabelIdType, which is the same as DataGraphNodeIdtype.
using EdgeEmbeddingType = std::vector<DataGraphEdgeIdType>;
using PathEmbeddingType = std::vector<PathType>;
using PropertyEmbeddingType = std::vector<Value>;


class CandidateList {
public:
    std::map<VarNodeIdType, std::vector<DataGraphNodeIdType>> data_;

    void FilterList(VarNodeIdType node_id, std::vector<DataGraphNodeIdType>& x_list) {
        if (data_.count(node_id) == 0) return;
        auto & filter = data_[node_id];
        std::vector<DataGraphNodeIdType> new_x_list;
        int idx = 0;
        for (auto x: x_list) {
            while (idx < filter.size() && filter[idx] < x) {
                idx++;
            }
            if (idx == filter.size()) break;
            if (filter[idx] == x) {
                new_x_list.push_back(x);
            }
        }
        x_list = new_x_list;
    }

    void FilterListOfPairOnFirstPlace(VarNodeIdType node_id1, std::vector<DataGraphEdgeIdType>& x_list) {
        if (data_.count(node_id1) == 0) return;
        auto & filter = data_[node_id1];
        std::vector<DataGraphEdgeIdType> new_x_list;
        int idx = 0;
        for (int i = 0; i < x_list.size(); i += 2) {
            auto x = x_list[i];
            while (idx < filter.size() && filter[idx] < x) {
                idx ++;
            }
            if (idx == filter.size()) break;
            if (filter[idx] == x) {
                new_x_list.push_back(x_list[i]);
                new_x_list.push_back(x_list[i + 1]);
            }
        }
        x_list = new_x_list;
    }

    void FilterListOfPairOnBothPlaces(VarNodeIdType node_id1, VarNodeIdType node_id2, std::vector<DataGraphNodeIdType>& x_list) {
        //FilterListOfPairOnFirstPlace(node_id1, x_list);
        bool have_filter1 = data_.count(node_id1) != 0;
        bool have_filter2 = data_.count(node_id2) != 0;
        if (!have_filter1 && !have_filter2) return;
        // auto & filter = data_[node_id2];
        std::vector<DataGraphNodeIdType> tmp;
        auto &filter1 = have_filter1 ? data_[node_id1] : tmp;
        auto &filter2 = have_filter2 ? data_[node_id2] : tmp;
        std::vector<DataGraphNodeIdType> new_x_list;
        for (int i = 0; i < x_list.size(); i += 2) {
            auto x1 = x_list[i], x2 = x_list[i + 1];
            if (have_filter1) {
                auto it = std::lower_bound(filter1.begin(), filter1.end(), x1);
                if (it == filter1.end() || ((*it) == x1)) continue;
            }
            if (have_filter2) {
                auto it = std::lower_bound(filter2.begin(), filter2.end(), x2);
                if (it == filter2.end() || ((*it) == x2)) continue;
            }
            new_x_list.push_back(x1);
            new_x_list.push_back(x2);
        }
        x_list = new_x_list;
    }
};

/**
  * @brief Intermediate results generated during the execution of the plan.
  */
class PIntermediateResult {
public:
    // 2-dim table. Each lines stores one graph embedding.
    std::vector<SPOEmbeddingType> spo_vars_;
    std::map<VarNodeIdType, unsigned> spo_id2pos_; // var node id to column id
    std::map<unsigned, VarNodeIdType> pos2spo_id_; // column id to var node id
    int spo_column_num_;

    // edge embedding
    std::vector<EdgeEmbeddingType> edges_;
    std::map<VarNodeIdType, unsigned> e_id2pos_;
    std::map<unsigned, VarNodeIdType> pos2e_id_;
    int edge_column_num_;

    // for unfix-length variable
    std::vector<PathEmbeddingType> paths_;
    std::map<VarNodeIdType, unsigned> path_id2pos_;
    std::map<unsigned, VarNodeIdType> pos2path_id_;
    int path_column_num_;

    // for properties
    std::vector<PropertyEmbeddingType> properties_;
    std::map<std::pair<VarNodeIdType, PropertyIdType>, unsigned> prop_id2pos_; // <varId, propId> to column
    std::map<unsigned, std::pair<VarNodeIdType, PropertyIdType>> pos2prop_id_;
    int prop_column_num_;

    int getRowNum() { return spo_vars_.size(); }
    // int getSOColumnNum() { return so_column_num_; }
    // int getPreColumnNum() { return pre_column_num_; }
    // int getPathColumnNum() { return path_column_num_; }

    void UpdateEmbedding(
            const std::vector<SPOEmbeddingType> &new_so_vars,
            const std::vector<EdgeEmbeddingType> &new_edges,
            const std::vector<PathEmbeddingType> &new_path_vars,
            const std::vector<PropertyEmbeddingType> &new_props) {
        spo_vars_ = new_so_vars;
        edges_ = new_edges;
        paths_ = new_path_vars;
        properties_ = new_props;
    }

    void UpdateSPOEmbedding(
            const std::vector<SPOEmbeddingType> &new_so_vars
    ) {
        spo_vars_ = new_so_vars;
    }

    void UpdateProperties(const std::vector<PropertyEmbeddingType> &new_props) {
        properties_ = new_props;
    }

    void AddSPOColumn(int var_id) {
        pos2spo_id_[spo_id2pos_[var_id] = spo_column_num_] = var_id;
        spo_column_num_++;
    }

    void AddEdgeColumn(int var_id) {
        pos2e_id_[e_id2pos_[var_id] = edge_column_num_] = var_id;
        edge_column_num_++;
    }

    void AddPathColumn(int var_id) {
        pos2path_id_[path_id2pos_[var_id] = path_column_num_] = var_id;
        path_column_num_++;
    }

    void AddPropertyColumn(int var_id, int prop_id) {
        auto idx = std::make_pair(var_id, prop_id);
        pos2prop_id_[prop_id2pos_[idx] = prop_column_num_] = idx;
        prop_column_num_++;
    }
};

#endif
