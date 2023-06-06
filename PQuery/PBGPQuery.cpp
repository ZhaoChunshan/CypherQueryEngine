
#include "PBGPQuery.h"
#include <algorithm>
using namespace std;

//
// Functions of New BGPQueryNew for Cypher, Created By Chunshan Zhao
//
// Constructor for PG Node Var Or Edge Var
VarDescriptor::VarDescriptor(unsigned id, VarType var_type, const string &var_name, const std::vector<unsigned>& labels_or_types,
                             const std::vector<Expression*>& exps)
        :id_(id), var_type_(var_type), var_name_(var_name),labels_or_types_(labels_or_types),exps_(exps)
{

}

void VarDescriptor::update_selected_props(const std::vector<unsigned> &props_id){
    this->selected_prop_ids_ = props_id;
}
NodeVarDescriptor::NodeVarDescriptor(unsigned id, VarType var_type, const string &var_name, const std::vector<unsigned>& labels_or_types,
                                     const std::vector<Expression*>& exps)
        :VarDescriptor(id, var_type, var_name, labels_or_types, exps){

}

EdgeVarDescriptor::EdgeVarDescriptor(unsigned id, VarType var_type, const string &var_name, const std::vector<unsigned>& labels_or_types,
                                     const std::vector<Expression*>& exps, bool is_sparql_pre, int range_left, int range_right)
        : VarDescriptor(id, var_type, var_name, labels_or_types, exps), is_predicate_var(is_sparql_pre),
          range_left_(range_left), range_right_(range_right)
{
}

void BGPQueryNew::setExecMode(ExecMode exec_mode){
    mode_ = exec_mode;
}

/**
 * @brief 将一个VarDescriptor加入到变量数组中，但此Descriptor需要已经初始化好Basic Infomation和Selection Information。
 * 副作用：更新id_position_map和position_id_map,so_var_id,pre_var_id, var_id_vec, selected_var_id, selected_prop_var_id;
 * selected_pre_var_num; selected_so_var_num;  total_selected_var_num;
 * unsigned total_pre_var_num;unsigned total_so_var_num;unsigned total_var_num;
*/
void BGPQueryNew::addVarDescriptor(shared_ptr<VarDescriptor>& var_desc_shared_ptr){
    unsigned index = var_vector.size(), id = var_desc_shared_ptr->id_;
    id_position_map[id] = index;
    position_id_map[index] = id;
    var_item_to_id[var_desc_shared_ptr->var_name_] = id;
    var_item_to_position[var_desc_shared_ptr->var_name_] = index;
    if(var_desc_shared_ptr->var_type_ == VarDescriptor::VarType::Node){
        so_var_id.push_back(id);
        total_so_var_num++;

        if(var_desc_shared_ptr->selected_){
            selected_so_var_num ++;
        }
    } else {
        pre_var_id.push_back(id);
        total_pre_var_num++;

        if(var_desc_shared_ptr->selected_){
            selected_pre_var_num ++;
        }
    }
    var_id_vec.push_back(id);
    var_vector.emplace_back(var_desc_shared_ptr);
    if(var_desc_shared_ptr->selected_){
        selected_var_id.push_back(id);
        total_selected_var_num++;
        if(!var_desc_shared_ptr->selected_prop_ids_.empty())
            selected_prop_var_id.push_back(id);
    }
    ++total_var_num;
}


/**
* @brief 将Cypher的三元组(s, e, o)添加到s_id_  e_id_; o_id_;之中.副作用：更新每个Vardescriptor的相邻信息。
* @param s: 主语的变量id
* @param e: 边的变量id
* @param o: 宾语的变量id
*/
void BGPQueryNew::addCypherTripleVarId(unsigned s, unsigned e, unsigned o, bool direct){

    vector<unsigned> seo{s, e, o};
    for(auto id: seo){
        std::string var_name = get_vardescrip_by_id(id)->var_name_;
        auto it = item_to_freq.find(var_name);
        if(it == item_to_freq.end()){
            item_to_freq.insert(std::make_pair(var_name, 1));
        }
        else {
            it->second++;
        }
        get_vardescrip_by_id(id)->degree_++;
    }
    dynamic_cast<NodeVarDescriptor*>( get_vardescrip_by_id(s).get())->update_so_var_edge_info(o, e, Util::EDGE_OUT, s_id_.size(),true,true);
    dynamic_cast<NodeVarDescriptor*>( get_vardescrip_by_id(o).get())->update_so_var_edge_info(s, e, Util::EDGE_IN, s_id_.size(),true,true);
    dynamic_cast<EdgeVarDescriptor*>( get_vardescrip_by_id(e).get())->update_pre_var_edge_info(s, o, true, true, s_id_.size());

    s_id_.push_back(s);
    e_id_.push_back(e);
    o_id_.push_back(o);
    directed_.push_back(direct);
    s_const_.push_back(false);
    e_const_.push_back(false);
    o_const_.push_back(false);

}


void BGPQueryNew::addFilterExp(Expression *exp){
    exps_.push_back(exp);
}


//
// Functions Created By Yuhao Yang
//

//If ith_edge's e is a var, and is a predicate, then return true
bool BGPQueryNew::CheckIthEdgePredicate(unsigned int ith_edge) {
    if (e_const_[ith_edge]) return false;
    return dynamic_cast<EdgeVarDescriptor *>(get_vardescrip_by_id(e_id_[ith_edge]).get())->is_predicate_var;
}

CandidateList& BGPQueryNew::get_all_candidates() {
    return *var_candidates_cache_;
}

//
// Functions of OldBGPQuery, Created By Linglin Yang
//


VarDescriptor::VarDescriptor(unsigned id, VarType var_type, const string &var_name):
        id_(id), var_type_(var_type), var_name_(var_name), selected_(false),degree_(0){};

bool NodeVarDescriptor::IsIthEdgeLinkedVarSO(unsigned int i_th_edge) {

    if(i_th_edge < degree_ && so_nei_type_[i_th_edge] == NodeType::VarNodeType) return true;
    else return false;
}

bool NodeVarDescriptor::IsIthEdgePreVar(unsigned int i_th_edge) {
    return so_e_type_[i_th_edge] == EdgeType::VarEdgeType;
}

/**
 * @brief 更新一个节点的邻居信息
 * @param edge_nei_id: 该so变量邻接的节点的varid(or nodeId)
 * @param pre_id: 该so变量邻接的边的varid(or edgeId)
 * @param edge_type: 该so变量的边是出 还是 入 还是 无向
 * @param edge_index: 此边在BGP三元组中位置
 * @param pre_is_var: 边是否是变量
 * @param edge_nei_is_var: 链接节点是否变量
*/
void NodeVarDescriptor::update_so_var_edge_info(unsigned edge_nei_id, unsigned edge_id, char edge_direct_type,
                                                unsigned edge_index, bool pre_is_var, bool edge_nei_is_var) {


    this->so_e_nei_.push_back(edge_nei_id);
    this->so_e_eid_.push_back(edge_id);
    this->so_e_dir_.push_back(edge_direct_type);
    this->so_e_index_.push_back(edge_index);
    if(pre_is_var)
        this->so_e_type_.push_back(EdgeType::VarEdgeType);
    else{
        this->so_e_type_.push_back(EdgeType::ConEdgeType);
    }

    if(edge_nei_is_var)
        this->so_nei_type_.push_back(NodeType::VarNodeType);
    else{
        this->so_nei_type_.push_back(NodeType::ConNodeType);
    }
}

void EdgeVarDescriptor::update_pre_var_edge_info(unsigned s_id, unsigned o_id, bool s_is_var, bool o_is_var, unsigned edge_index){
    this->s_id_.push_back(s_id);
    this->o_id_.push_back(o_id);

    if(s_is_var){
        this->s_type_.push_back(NodeType::VarNodeType);
    } else{
        this->s_type_.push_back(NodeType::ConNodeType);
    }

    if(o_is_var){
        this->o_type_.push_back(NodeType::VarNodeType);
    } else{
        this->o_type_.push_back(NodeType::ConNodeType);
    }

    this->pre_edge_index_.push_back(edge_index);
}

void VarDescriptor::update_statistics_num() {
    if(this->var_type_ == VarDescriptor::VarType::Node) {
        NodeVarDescriptor *node_var = dynamic_cast<NodeVarDescriptor *>(this);
        this->degree_ = node_var->so_e_index_.size();
    }
    else {
        EdgeVarDescriptor * edge_var = dynamic_cast<EdgeVarDescriptor *>(this);
        this->degree_ = edge_var->pre_edge_index_.size();
    }
}

void VarDescriptor::update_select_status(bool selected) {
    this->selected_ = selected;
}

void VarDescriptor::print(KVstore *kvstore) {

    cout << "var: " << var_name_ << " , id is " << id_ << ", var type: " << (var_type_ == VarType::Node ? "Entity" : "Predicate") << endl;
    cout << "degree = " << degree_ << ", selected: " << (selected_ ? "true" : "false") << endl;

    if(var_type_ == VarType::Node){
        NodeVarDescriptor * node = dynamic_cast<NodeVarDescriptor*>(this);
        cout << "edge type, edge index, edge nei, edge nei type, var edge pre, var edge pre type: " << endl;
        for(unsigned i = 0; i < node->so_e_type_.size(); ++i){
            cout << (int)node->so_e_type_.at(i)<< '\t' << node->so_e_index_[i] << '\t' << node->so_e_nei_[i] << '\t';

            if(node->so_nei_type_[i] == NodeType::VarNodeType)
                cout << node->so_e_nei_[i] << '\t' << "varsotype" << '\t';
            else
//                cout << kvstore->getStringByID(node->so_e_nei_[i]) << '\t' << "consotype" << '\t';

            if(node->so_e_type_[i] == EdgeType::VarEdgeType){
                cout << node->so_e_eid_[i] << '\t' << "varpretype" << endl;
            } else{
//                cout << kvstore->getPredicateByID(node->so_e_eid_[i]) << '\t' << "conpretype" << endl;
            }
        }

    } else{
        EdgeVarDescriptor * edge = dynamic_cast<EdgeVarDescriptor*>(this);
        cout << "s_type_.size() = " << edge->s_type_.size() << endl;
        for(unsigned i = 0; i < edge->s_type_.size(); ++i){

            if(edge->s_type_[i] == NodeType::ConNodeType){
//                cout << "s is con, " << kvstore->getStringByID(edge->s_id_[i]) << "\t";
            } else{
                cout << "s is var, " << edge->s_id_[i] << "\t";
            }

            if(edge->o_type_[i] == NodeType::ConNodeType){
//                cout << "o is con, " << kvstore->getStringByID(edge->o_id_[i]) << endl;
            } else{
                cout << "o is var, " << edge->o_id_[i] << endl;
            }
        }
    }
}
std::string VarDescriptor::GetString(VarType t) {
    // VarType{Entity, Predicate, NotDecided
    switch(t){
        case VarType::Node:
            return "VarType::Node";
            break;
        case VarType::Edge:
            return "VarType::Edge";
            break;
        case VarType::NotDecided:
            return "VarType::NotDecided";
            break;
    }
    return "VarType::Fault";
}

BGPQueryNew::BGPQueryNew():mode_(ExecMode::Homomorphism),single_node_(false){
    this->initial();

}

BGPQueryNew::~BGPQueryNew() {
    for(auto p:result_list)
        if(p != nullptr)
            delete[] p;
}


// general_evalutial first new one BGPQueryNew, than initial it.
// than add Triple one by one.
void BGPQueryNew::initial() {

    this->total_var_num = 0;
    this->total_so_var_num = 0;
    this->total_pre_var_num = 0;

    this->total_join_var_num = 0;
    this->join_pre_var_num = 0;
    this->join_so_var_num = 0;

    selected_pre_var_num = 0;
    selected_so_var_num = 0;
    total_selected_var_num = 0;

    mode_ = ExecMode::Homomorphism;
    single_node_ = false;
    is_cypher_ = true;
    distinct_query = false;
    limit_num = INVALID;
    limit_query = false;
}



unsigned BGPQueryNew::get_var_id_by_name(const string& var_name) {
    return this->var_item_to_id[var_name];
    // for(unsigned i = 0; i < this->var_vector.size(); ++i){
    // 	if(var_vector[i]->var_name_ == var_name){
    // 		return i;
    // 	}
    // }
    //
    // // not found, return -1
    // return -1;
}

string BGPQueryNew::get_var_name_by_id(unsigned int var_id) {
    return var_vector[id_position_map[var_id]]->var_name_;
}

unsigned int BGPQueryNew::get_var_index_by_name(const string &var_name) {
    return this->var_item_to_position[var_name];
}

unsigned int BGPQueryNew::get_var_id_by_index(unsigned int index) {
    return this->var_id_vec[index];
}

unsigned int BGPQueryNew::get_var_position_by_id(unsigned int id) {
    return this->id_position_map[id];
}

const vector<unsigned int> &BGPQueryNew::get_var_id_vec() {
    return this->var_id_vec;
}

const shared_ptr<VarDescriptor> &BGPQueryNew::get_vardescrip_by_index(unsigned index) {
    return this->var_vector[index];
}

const shared_ptr<VarDescriptor> &BGPQueryNew::get_vardescrip_by_id(unsigned id) {
    return this->var_vector[this->get_var_position_by_id(id)];
}



void BGPQueryNew::count_statistics_num() {

    // TODO: need to check whether this = var_so_num + var_pre_num
    this->total_var_num = this->var_vector.size();
    this->total_selected_var_num = this->selected_var_id.size();

    for(unsigned i = 0; i < this->var_vector.size(); ++ i){
        this->var_vector[i]->update_statistics_num();
    }

    for(unsigned i = 0; i < selected_var_id.size(); ++i)
        this->var_vector[id_position_map[selected_var_id[i]]]->update_select_status(true);
}



unsigned int BGPQueryNew::get_total_var_num() {
    return this->total_var_num;
}

unsigned int BGPQueryNew::get_pre_var_num() {
    return this->total_pre_var_num;
}


unsigned int BGPQueryNew::get_var_degree_by_id(unsigned int var_id) {
    return var_vector[id_position_map[var_id]]->degree_;
}

VarDescriptor::VarType BGPQueryNew::get_var_type_by_id(unsigned int var_id) {
    return var_vector[id_position_map[var_id]]->var_type_;
}

bool BGPQueryNew::is_var_selected_by_id(unsigned int var_id) {
    return var_vector[id_position_map[var_id]]->selected_;
}

unsigned int BGPQueryNew::get_so_var_edge_index(unsigned int var_id, int edge_id) {
    NodeVarDescriptor* node = dynamic_cast<NodeVarDescriptor*>(var_vector[id_position_map[var_id]].get());
    return node->so_e_index_[edge_id];
}

char BGPQueryNew::get_so_var_edge_direct_type(unsigned int var_id, unsigned int edge_id) {
    NodeVarDescriptor* node = dynamic_cast<NodeVarDescriptor*>(var_vector[id_position_map[var_id]].get());
    return node->so_e_dir_[edge_id];
}

unsigned int BGPQueryNew::get_so_var_edge_nei(unsigned int var_id, unsigned int edge_id) {
    NodeVarDescriptor* node = dynamic_cast<NodeVarDescriptor*>(var_vector[id_position_map[var_id]].get());
    return node->so_e_nei_[edge_id];
}

VarDescriptor::NodeType BGPQueryNew::get_so_var_edge_nei_type(unsigned int var_id, unsigned int edge_id) {
    NodeVarDescriptor* node = dynamic_cast<NodeVarDescriptor*>(var_vector[id_position_map[var_id]].get());
    return node->so_nei_type_[edge_id];
}

unsigned int BGPQueryNew::get_so_var_edge_eid(unsigned int var_id, unsigned int edge_id) {
    NodeVarDescriptor* node = dynamic_cast<NodeVarDescriptor*>(var_vector[id_position_map[var_id]].get());
    return node->so_e_eid_[edge_id];
}

VarDescriptor::EdgeType BGPQueryNew::get_so_var_edge_var_const_type(unsigned int var_id, unsigned int edge_id) {
    NodeVarDescriptor* node = dynamic_cast<NodeVarDescriptor*>(var_vector[id_position_map[var_id]].get());
    return node->so_e_type_[edge_id];
}


unsigned int BGPQueryNew::get_pre_var_edge_index(unsigned int var_id, unsigned int edge_id) {
    EdgeVarDescriptor * edge  = dynamic_cast<EdgeVarDescriptor*>(var_vector[id_position_map[var_id]].get());
    return edge->pre_edge_index_[edge_id];
}

unsigned int BGPQueryNew::get_pre_var_s_id(unsigned int var_id, unsigned int edge_id) {
    EdgeVarDescriptor * edge  = dynamic_cast<EdgeVarDescriptor*>(var_vector[id_position_map[var_id]].get());
    return edge->s_id_[edge_id];
}

VarDescriptor::NodeType BGPQueryNew::get_pre_var_s_type(unsigned int var_id, unsigned int edge_id) {
    EdgeVarDescriptor * edge  = dynamic_cast<EdgeVarDescriptor*>(var_vector[id_position_map[var_id]].get());
    return edge->s_type_[edge_id];
}

unsigned int BGPQueryNew::get_pre_var_o_id(unsigned int var_id, unsigned int edge_id) {
    EdgeVarDescriptor * edge  = dynamic_cast<EdgeVarDescriptor*>(var_vector[id_position_map[var_id]].get());
    return edge->o_id_[edge_id];
}

VarDescriptor::NodeType BGPQueryNew::get_pre_var_o_type(unsigned int var_id, unsigned int edge_id) {
    EdgeVarDescriptor * edge  = dynamic_cast<EdgeVarDescriptor*>(var_vector[id_position_map[var_id]].get());
    return edge->o_type_[edge_id];
}

bool BGPQueryNew::check_already_joined_pre_var(vector<unsigned int> &already_node, unsigned int pre_var_id) {
    for(auto x:already_node){
        NodeVarDescriptor* var_descip = dynamic_cast<NodeVarDescriptor*>(get_vardescrip_by_id(x).get());
        for(unsigned i = 0; i < var_descip->degree_; ++i){
            if(var_descip->so_nei_type_[i] == VarDescriptor::NodeType::VarNodeType &&
               var_descip->so_e_type_[i] == VarDescriptor::EdgeType::VarEdgeType)
                if(std::find(already_node.begin(), already_node.end(), var_descip->so_e_nei_[i]) != already_node.end() &&
                   var_descip->so_e_eid_[i] == pre_var_id)
                    return true;
        }
    }
    return false;
}





bool BGPQueryNew::is_var_satellite_by_index(unsigned index) {
    auto var_descrip = var_vector[index];
    return (var_descrip->var_type_ == VarDescriptor::VarType::Node and
            var_descrip->degree_ == 1 and !var_descrip->selected_);// && var_descrip->selected_ == false);
}

bool BGPQueryNew::is_var_satellite_by_id(unsigned int id) {
    auto var_descrip = get_vardescrip_by_id(id);
    return (var_descrip->var_type_ == VarDescriptor::VarType::Node and
            var_descrip->degree_ == 1 and !var_descrip->selected_);
}

/**
 * Print this BGPQueryNew's info, just for debug, not for user.
 * Use VarDescriptor::print
 * @param kvstore kvstore's pointer
 */
void BGPQueryNew::print(KVstore *kvstore) {
    cout << (this->distinct_query ? "DISTINCT BGP" : "NOT DISTINCT BGP") << endl;
    cout << "this BGP has " << var_vector.size() << " vars, ie. total_var_num = " << this->total_var_num << ", " << std::endl;

    cout << "total so var num = " << total_so_var_num << ", so_var_id.size() = " << so_var_id.size() << endl;
    for(unsigned i = 0; i < so_var_id.size(); ++ i ){
        cout << "var name: " << var_vector[id_position_map[so_var_id[i]]]->var_name_ << endl;
    }
    cout << "total pre vat num = " << total_pre_var_num << ", pre_var_id.size() = " << pre_var_id.size() << endl;
    for(unsigned i = 0; i < pre_var_id.size(); ++ i){
        cout << "var name: " << var_vector[id_position_map[pre_var_id[i]]]->var_name_ << endl;
    }

    cout << "id position map:" << endl;
    for(auto id_pos : id_position_map){
        cout << id_pos.first << " : " << id_pos.second << endl;
    }
    cout << "position id map:" << endl;
    for(auto pos_id : position_id_map){
        cout << pos_id.first << " : " << pos_id.second << endl;
    }

    cout << "item to freq map:" << endl;
    for(const auto& item_freq : item_to_freq){
        cout << item_freq.first << " : " << item_freq.second << endl;
    }

    cout << "item to position map:" << endl;
    for(const auto& item_pos : var_item_to_position){
        cout << item_pos.first << " : " << item_pos.second << endl;
    }

    cout << "item to id map:" << endl;
    for(const auto& item_id : var_item_to_id){
        cout << item_id.first << " : " << item_id.second << endl;
    }

    cout << "s_id, p_id, o_id:" << endl;
    for(unsigned i = 0; i < s_id_.size(); ++i){
        cout << s_id_[i] << (s_const_[i] ? "const" : "var") << "    ";
        cout << e_id_[i] << (e_const_[i] ? "const" : "var") << "    ";
        cout << o_id_[i] << (o_const_[i] ? "const" : "var") << endl;

    }


    cout << endl << "VAR INFO:" << endl;
    for(unsigned i = 0; i < var_vector.size(); ++ i){
        var_vector[i]->print(kvstore);
    }
}




vector<unsigned*>*
BGPQueryNew::get_result_list_pointer()
{
    return &(this->result_list);
}

vector<vector<TYPE_ENTITY_LITERAL_ID>>*
BGPQueryNew::get_result_list_pointer1()
{
    return &(this->result_list1);
}

unique_ptr<unsigned[]>&
BGPQueryNew::resultPositionToId()
{
    return result_position_to_id;
}
