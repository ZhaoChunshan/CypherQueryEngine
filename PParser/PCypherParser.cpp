#include <iostream>
#include <sstream>
#include <algorithm>
#include "PCypherParser.h"


long PCypherParser::parseIntegerLiteral(const std::string &s){
    if(s.length() < 2){
        return strtol(s.c_str(), nullptr, 10);
    }else{
        if(s[1] == 'x')
            return strtol(s.c_str() + 2, nullptr, 16);
        else if(s[1] == 'o')
            return strtol(s.c_str() + 2, nullptr, 8);
        else 
            return strtol(s.c_str(), nullptr, 10);
    }
}

double PCypherParser::parseDoubleLiteral(const std::string &s){
    return atof(s.c_str());
}

std::string PCypherParser::parseStringLiteral(const std::string &s){
    // TODO: 
    return s.substr(1, s.length() - 2);
}

/**
	Throw a runtime error when lexical and syntactic errors are detected in the query.
*/
void CypherErrorListener::syntaxError(antlr4::Recognizer *recognizer, antlr4::Token * offendingSymbol, \
	size_t line, size_t charPositionInLine, const std::string &msg, std::exception_ptr e)
{
	throw std::runtime_error("[Syntax Error]:line " + std::to_string(line) + ":" + std::to_string(charPositionInLine) + " " + msg);
}


/**
	Overall driver function for query parsing.

	@param query the query string.
*/
CypherAST* PCypherParser::CypherParse(const std::string &query)
{
	try{
		std::istringstream ifs(query);
        return CypherParse(ifs);
	}catch(const std::runtime_error& e1)
	{
		throw std::runtime_error(e1.what());
	}
    return nullptr;
}

/**
	Overall driver function for query parsing.

	@param in istream of the query.
*/
CypherAST* PCypherParser::CypherParse(std::istream& in){
    sym_tb_.reset();
    sym_tb_.push(); // go to global scope
    try{
        CypherErrorListener lstnr;
        antlr4::ANTLRInputStream input(in);
        CypherLexer lexer(&input);
        lexer.removeErrorListeners();
	    lexer.addErrorListener(&lstnr);

        antlr4::CommonTokenStream tokens(&lexer);
        CypherParser parser(&tokens);
        parser.removeErrorListeners(); 
        parser.addErrorListener(&lstnr);

        CypherParser::OC_CypherContext *ctx = parser.oC_Cypher();
        auto ast = visitOC_Cypher(ctx).as<CypherAST*>();
        return ast;
    } catch (const std::runtime_error& e1) {
        throw std::runtime_error(e1.what());
    }
    sym_tb_.pop();
    return nullptr;
}

/**
 * @brief visit Cypher query
 * @param ctx CypherParser::OC_CypherContext
 * @return CypherAST*: Root node of the AST.
*/
antlrcpp::Any PCypherParser::visitOC_Cypher(CypherParser::OC_CypherContext *ctx){
    if(ctx->oC_Statement()->oC_Query()->oC_RegularQuery()){
        return visitOC_RegularQuery(ctx->oC_Statement()->oC_Query()->oC_RegularQuery());
    }else{
        return visitOC_StandaloneCall(ctx->oC_Statement()->oC_Query()->oC_StandaloneCall());
    }
}

/**
 * @brief visit regular query (singleQuery1 UNION singleQuery2 UNION singleQuery3)
 * @param ctx CypherParser::OC_RegularQueryContext
 * @return CypherAST*: Root node of the AST.
*/
antlrcpp::Any PCypherParser::visitOC_RegularQuery(CypherParser::OC_RegularQueryContext *ctx)
{
    unsigned n = ctx->oC_Union().size();

    std::vector<std::unique_ptr<SingleQueryAST>> single_qy;
    std::vector<bool> union_all_;

    SingleQueryAST *tmp = visitOC_SingleQuery(ctx->oC_SingleQuery()).as<SingleQueryAST *>();
    single_qy.emplace_back(tmp);

    for(unsigned i = 0; i < n; ++i){
        tmp = visitOC_SingleQuery(ctx->oC_Union(i)->oC_SingleQuery()).as<SingleQueryAST *>();
        single_qy.emplace_back(tmp);   
        union_all_.push_back((bool)ctx->oC_Union(i)->ALL());
    }
    
    PVarset<std::string> column_name(single_qy[0]->query_units_.back()->with_return_->column_name_);
    for(const auto& single_ : single_qy){
        if(single_->query_units_.back()->with_return_->with_ == true ||
        !(PVarset<std::string>(single_->query_units_.back()->with_return_->column_name_) == column_name) ){
            throw std::runtime_error("[ERROR] All sub queries in an UNION must have the same return column names");
        }   
    }

    CypherAST * cypher_ast = new CypherAST();
    cypher_ast->union_all_ = union_all_;
    for(auto& ptr : single_qy){
        cypher_ast->single_querys_.emplace_back(ptr.release());
    }
    cypher_ast->id2var_name_ = sym_tb_.getIdToString();
    cypher_ast->prop_id2string_ = sym_tb_.prop_id2string_;
    cypher_ast->prop2id_ = sym_tb_.prop2id_;
    return cypher_ast;
}

antlrcpp::Any PCypherParser::visitOC_StandaloneCall(CypherParser::OC_StandaloneCallContext *ctx)
{
    throw std::runtime_error("[ERROR] Standalone call not implemented.");
    return antlrcpp::Any();
}

/**
 * @brief visit single query(a query that doesnot have UNION clause, but may have serveral WITH clauses and a RETURN clause.
 * @param ctx pointer to CypherParser::OC_SingleQueryContext 
 * @return SingleQueryAST*
*/
antlrcpp::Any PCypherParser::visitOC_SingleQuery(CypherParser::OC_SingleQueryContext *ctx)
{
    if(ctx->oC_SinglePartQuery()){
        auto query_unit =  visitOC_SinglePartQuery(ctx->oC_SinglePartQuery()).as<QueryUnitAST*>();
        auto single_query = new SingleQueryAST();
        single_query->query_units_.emplace_back(query_unit);
        
        return single_query;
    }else{
        return visitOC_MultiPartQuery(ctx->oC_MultiPartQuery());
    }
}

/**
 * @brief visit single part query(a query that only has reading clauses and a RETURN clause.
 * @param ctx pointer to CypherParser::OC_SingleQueryContext 
 * @return QueryUnitAST*.
*/
antlrcpp::Any PCypherParser::visitOC_SinglePartQuery(CypherParser::OC_SinglePartQueryContext *ctx){

    std::vector<std::unique_ptr<ReadingAST>> readings;
    std::vector<std::unique_ptr<UpdatingAST>> updatings;
    WithReturnAST *with_return = nullptr; 
    for(auto read_ctx : ctx->oC_ReadingClause()){
		// visit reading clauses
        ReadingAST *reading = visitOC_ReadingClause(read_ctx).as<ReadingAST*>();
        readings.emplace_back(reading);
    }
	for(auto update_ctx : ctx->oC_UpdatingClause()){
		// visit updating clauses;
        UpdatingAST *updating = visitOC_UpdatingClause(update_ctx).as<UpdatingAST*>();
        updatings.emplace_back(updating);
	}

	if(ctx->oC_Return()){
		with_return = visitOC_Return(ctx->oC_Return()).as<WithReturnAST*>();
	}
    QueryUnitAST *query_unit = new QueryUnitAST();
    for(auto& read : readings){
        query_unit->reading_.emplace_back(read.release());
    }
    for(auto& update : updatings){
        query_unit->updating_.emplace_back(update.release());
    }
    query_unit->with_return_.reset(with_return);

	return query_unit;
}

/**
 * @brief visit multipart query(a query that is connected by serveral WITH clauses).
 * @param ctx pointer to CypherParser::OC_MultiPartQueryContext 
 * @return SingleQueryAST*.
*/
antlrcpp::Any PCypherParser::visitOC_MultiPartQuery(CypherParser::OC_MultiPartQueryContext *ctx){
    unsigned num_read = ctx->oC_ReadingClause().size();
    unsigned num_update = ctx->oC_UpdatingClause().size();
    unsigned num_child = ctx->children.size();
    unsigned read_ptr = 0, update_ptr = 0, with_ptr = 0;

    std::vector<std::unique_ptr<QueryUnitAST>> query_units;

    query_units.emplace_back(new QueryUnitAST());
    for(int child = 0; child < num_child; ++child){
        if(ctx->children[child]->getText() == ctx->oC_With(with_ptr)->getText()){
            query_units.back()->with_return_.reset(
                visitOC_With(ctx->oC_With(with_ptr)).as<WithReturnAST*>()
            );
            if(++with_ptr == ctx->oC_With().size()) break;
            
            query_units.emplace_back(new QueryUnitAST());
        }else if(read_ptr < ctx->oC_ReadingClause().size() && ctx->children[child]->getText() == ctx->oC_ReadingClause(read_ptr)->getText()){
            query_units.back()->reading_.emplace_back(
                visitOC_ReadingClause(ctx->oC_ReadingClause(read_ptr)).as<ReadingAST*>()
            );
            ++read_ptr;
        }else if(update_ptr < ctx->oC_UpdatingClause().size() && ctx->children[child]->getText() == ctx->oC_UpdatingClause(update_ptr)->getText()){
            query_units.back()->updating_.emplace_back(
                visitOC_UpdatingClause(ctx->oC_UpdatingClause(update_ptr)).as<UpdatingAST*>()
            );
            ++update_ptr;
        }
    }
    query_units.emplace_back(
        visitOC_SinglePartQuery(ctx->oC_SinglePartQuery()).as<QueryUnitAST*>()
    );
    SingleQueryAST * single_query = new SingleQueryAST();
    for(auto& query_unit : query_units){
        single_query->query_units_.emplace_back(query_unit.release());
    }
    return single_query;
}

/**
 * @brief visit a reading clause.
 * @param ctx pointer to CypherParser::OC_ReadingClauseContext
 * @return ReadingAST *
*/
antlrcpp::Any PCypherParser::visitOC_ReadingClause(CypherParser::OC_ReadingClauseContext *ctx){
    if(ctx->oC_Match()){
        return dynamic_cast<ReadingAST *>(  visitOC_Match(ctx->oC_Match()).as<MatchAST*>()  );
    }else if(ctx->oC_Unwind()){
        return dynamic_cast<ReadingAST *>( visitOC_Unwind(ctx->oC_Unwind()).as<UnwindAST *>() );
    } else {
        return dynamic_cast<ReadingAST *>( visitOC_InQueryCall(ctx->oC_InQueryCall()).as<InQueryCallAST *>() );
    }
}

/**
 * @brief visit a updating clause.
 * @param ctx pointer to CypherParser::OC_UpdatingClauseContext
 * @return UpdatingAST *
*/
antlrcpp::Any PCypherParser::visitOC_UpdatingClause(CypherParser::OC_UpdatingClauseContext *ctx){
    if(ctx->oC_Create()) {
        return dynamic_cast<UpdatingAST *>( visitOC_Create(ctx->oC_Create()).as<CreateAST*>() );
    } else if(ctx->oC_Set()) {
        return dynamic_cast<UpdatingAST *>( visitOC_Set(ctx->oC_Set()).as<SetAST *>() );
    } else if(ctx->oC_Delete()){
        return dynamic_cast<UpdatingAST *>( visitOC_Delete(ctx->oC_Delete()).as<DeleteAST *>() );
    } else if(ctx->oC_Remove()){
        return dynamic_cast<UpdatingAST *>( visitOC_Remove(ctx->oC_Remove()).as<RemoveAST *>() );
    } else {
        return dynamic_cast<UpdatingAST *>( visitOC_Merge(ctx->oC_Merge()).as<MergeAST *>() );
    }
}

/**
 * @brief visit match clause.
 * @param ctx pointer to CypherParser::OC_MatchContext
 * @return MatchAST *
*/
antlrcpp::Any PCypherParser::visitOC_Match(CypherParser::OC_MatchContext *ctx){
    std::vector<std::unique_ptr<GPStore::RigidPattern>> rigid_patterns;
    std::unique_ptr<GPStore::Expression> exp;

    for(auto pat : ctx->oC_Pattern()->oC_PatternPart()){
        GPStore::RigidPattern *rigid =  visitOC_PatternPart(pat).as<GPStore::RigidPattern *>();
        rigid_patterns.emplace_back(rigid);
    }

    if(ctx->oC_Where()){
        exp.reset(visitOC_Expression(ctx->oC_Where()->oC_Expression()).as<GPStore::Expression*>());
    }

    MatchAST *match = new MatchAST();
    match->is_optional_ = (ctx->OPTIONAL() != nullptr);
    for(const auto& rigid : rigid_patterns){
        match->pattern_.emplace_back(*rigid);
    }
    match->where_.reset(exp.release());
    return match;
}

/**
 * @brief visit unwind clause.
 * @param ctx pointer to CypherParser::OC_UnwindContext
 * @return UnwindAST *
*/
antlrcpp::Any PCypherParser::visitOC_Unwind(CypherParser::OC_UnwindContext *ctx){
    std::unique_ptr<GPStore::Expression> exp ( visitOC_Expression(ctx->oC_Expression()).as<GPStore::Expression *>() );
    std::unique_ptr<UnwindAST> unwind(new UnwindAST());
    unwind->exp_.reset(exp.release());
    unwind->var_name_ = ctx->oC_Variable()->getText();
    if(sym_tb_.exists(unwind->var_name_)){
        throw std::runtime_error("Variable `" + unwind->var_name_ + "` already declared.");
    }

    sym_tb_.insert(unwind->var_name_ ,CypherSymbol::VALUE_VAR, sym_tb_.getNextVarId());
    sym_tb_.putString(unwind->var_name_);
    return unwind.release();
}

/**
 * @brief visit InQueryCall clause.
 * @param ctx pointer to CypherParser::OC_InQueryCallContext
 * @return InQueryCallAST *
*/
antlrcpp::Any PCypherParser::visitOC_InQueryCall(CypherParser::OC_InQueryCallContext *ctx){
    throw std::runtime_error("[ERROR] In Query call not implemented.");
    return antlrcpp::Any();
}

antlrcpp::Any PCypherParser::visitOC_Create(CypherParser::OC_CreateContext *ctx){
    throw std::runtime_error("[ERROR] Standalone call not implemented.");
}

antlrcpp::Any PCypherParser::visitOC_Set(CypherParser::OC_SetContext *ctx){
    throw std::runtime_error("[ERROR] Set clause not implemented.");
}

antlrcpp::Any PCypherParser::visitOC_Delete(CypherParser::OC_DeleteContext *ctx){
    throw std::runtime_error("[ERROR] Delete clause not implemented.");
}

antlrcpp::Any PCypherParser::visitOC_Remove(CypherParser::OC_RemoveContext *ctx){
    throw std::runtime_error("[ERROR] Remove clause not implemented.");
}

antlrcpp::Any PCypherParser::visitOC_Merge(CypherParser::OC_MergeContext *ctx){
    throw std::runtime_error("[ERROR] Merge clause not implemented.");
}

/**
 * @brief visit With .
 * @param ctx pointer to CypherParser::OC_WithContext
 * @return GPStore::WithReturnAST *
*/
antlrcpp::Any PCypherParser::visitOC_With(CypherParser::OC_WithContext *ctx){
    std::unique_ptr<WithReturnAST> with_return(visitOC_ProjectionBody(ctx->oC_ProjectionBody(), true).as<WithReturnAST*>());
    if(ctx->oC_Where()){
        with_return->where_.reset(visitOC_Expression(ctx->oC_Where()->oC_Expression()).as<GPStore::Expression*>());
    }
    return with_return.release();
}
/**
 * @brief visit Return .
 * @param ctx pointer to CypherParser::OC_ReturnContext
 * @return GPStore::WithReturnAST *
*/
antlrcpp::Any PCypherParser::visitOC_Return(CypherParser::OC_ReturnContext *ctx){
    return visitOC_ProjectionBody(ctx->oC_ProjectionBody(), false);
}
/**
 * @brief visit ProjectionBody .
 * @param ctx pointer to CypherParser::OC_ProjectionBodyContext
 * @return GPStore::WithReturnAST *
*/
antlrcpp::Any PCypherParser::visitOC_ProjectionBody(CypherParser::OC_ProjectionBodyContext *ctx, bool is_with){

    std::unique_ptr<WithReturnAST> with_return(new WithReturnAST());    
    with_return->with_ = is_with;
    with_return->distinct_ = ctx->DISTINCT() == nullptr ? false : true;
    with_return->asterisk_ = (ctx->oC_ProjectionItems()->children[0]->getText() == "*");

    for(auto proj_ctx : ctx->oC_ProjectionItems()->oC_ProjectionItem()){
        with_return->proj_exp_.emplace_back(
            visitOC_Expression(proj_ctx->oC_Expression()).as<GPStore::Expression*>()
        );
        if(with_return->proj_exp_.back()->containsAggrFunc())
            with_return->aggregation_ = true;
        with_return->proj_exp_text_.emplace_back(proj_ctx->oC_Expression()->getText());
        if(proj_ctx->oC_Variable()){
            const std::string& var = proj_ctx->oC_Variable()->getText();
            auto & exp = with_return->proj_exp_.back();
            if(!exp->isVariable() || exp->getVariableName() != var){
                with_return->alias_.push_back(var);
                sym_tb_.insert(var, CypherSymbol::VALUE_VAR, sym_tb_.getNextVarId());
                sym_tb_.putString(var);
            }
            else
                with_return->alias_.push_back("");
            if(std::find(with_return->column_name_.begin(), with_return->column_name_.end(), var) == with_return->column_name_.end()){
                with_return->column_name_.push_back(var);
                with_return->column_var_id_.push_back(sym_tb_.search(var).var_id_);
            } else {
                throw std::runtime_error("[ERROR] Multiple result columns with the same name are not supported.");
            }
        } else {
            with_return->alias_.push_back("");

            auto& exp = with_return->proj_exp_.back();
            std::string var;
            if(exp->isVariable()){
                var = exp->getVariableName();
                if(std::find(with_return->column_name_.begin(), with_return->column_name_.end(), var) == with_return->column_name_.end()){
                    with_return->column_name_.push_back(var);
                    with_return->column_var_id_.push_back(sym_tb_.search(var).var_id_);
                } else {
                    throw std::runtime_error("[ERROR] Multiple result columns with the same name are not supported.");
                }
            } else {
                if(is_with){
                    throw std::runtime_error("[ERROR] Expression in WITH must be aliased (use AS).");
                }
                const std::string & var = with_return->proj_exp_text_.back();
                if(std::find(with_return->column_name_.begin(), with_return->column_name_.end(), var) == with_return->column_name_.end()){
                    with_return->column_name_.push_back(var);
                    auto col_id =  sym_tb_.getNextVarId();
                    sym_tb_.insert(var, CypherSymbol::VALUE_VAR, col_id);
                    sym_tb_.putString(var);
                    with_return->column_var_id_.push_back(col_id);
                } else {
                    throw std::runtime_error("[ERROR] Multiple result columns with the same name are not supported.");
                }
            }

        }
    
    }   // for(auto proj_ctx...

    if(with_return->asterisk_){
        with_return->implict_proj_var_id_ = ( PVarset<unsigned>(sym_tb_.getAllNamedVarId())-PVarset<unsigned>(with_return->column_var_id_) ).vars;
    }

    PVarset<unsigned> order_var;
    if(ctx->oC_Order()){
        for(auto sort_ctx : ctx->oC_Order()->oC_SortItem()){
            with_return->ascending_.push_back(sort_ctx->ASC() != nullptr || sort_ctx->ASCENDING()!=nullptr);
            with_return->order_by_.emplace_back(visitOC_Expression(sort_ctx->oC_Expression()).as<GPStore::Expression*>());
            order_var += with_return->order_by_.back()->covered_var_id_;
        }
    }
    if(!with_return->asterisk_){
        with_return->implict_proj_var_id_ = (order_var - PVarset<unsigned>(with_return->column_var_id_) ).vars;
    }

    if(with_return->aggregation_ && with_return->implict_proj_var_id_.size()){
        throw std::runtime_error("[ERROR] Implicit grouping keys are not supported.");
    }

    if(ctx->oC_Limit()){
        with_return->limit_.reset(visitOC_Expression(ctx->oC_Limit()->oC_Expression()).as<GPStore::Expression*>());
    }
    if(ctx->oC_Skip()){
        with_return->skip_.reset(visitOC_Expression(ctx->oC_Skip()->oC_Expression()).as<GPStore::Expression*>());
    }

    if(!with_return->asterisk_)
        sym_tb_.clearExcept(with_return->column_name_);

    return with_return.release();
}
/**
 * @brief visit PatternPart [i.e. RigidPattern] .
 * @param ctx pointer to CypherParser::OC_PatternPartContext
 * @return GPStore::RigidPattern *
*/
antlrcpp::Any PCypherParser::visitOC_PatternPart(CypherParser::OC_PatternPartContext *ctx){
    std::unique_ptr<GPStore::RigidPattern> rigid;
    
    if(ctx->oC_AnonymousPatternPart()->oC_ShortestPathPattern()){
        auto shortest_ctx = ctx->oC_AnonymousPatternPart()->oC_ShortestPathPattern();

        rigid.reset(visitOC_PatternElement(shortest_ctx->oC_PatternElement()).as<GPStore::RigidPattern*>());

        std::string str = shortest_ctx->oC_SymbolicName()->getText();
        std::transform(str.begin(), str.end(), str.begin(), ::toupper);
        if(str == "SHORTESTPATH"){
            rigid->type_ = GPStore::RigidPattern::SHORTEST_PATH;
        }else if(str == "ALLSHORTESTPATHS"){
            rigid->type_ = GPStore::RigidPattern::ALL_SHORTEST_PATHS;
        }else{
            throw std::runtime_error("[ERROR] Only shortestPath and allShortestPaths allowed.");
        }
        
    }else{
        rigid.reset(visitOC_PatternElement(ctx->oC_AnonymousPatternPart()->oC_PatternElement()).as<GPStore::RigidPattern*>());
        rigid->type_ = GPStore::RigidPattern::PATH;
    }

    if(ctx->oC_Variable()){
        rigid->var_name_ = ctx->oC_Variable()->getText();
        rigid->is_anno_var_ = false;
        rigid->var_id_ = sym_tb_.getNextVarId();
        rigid->covered_var_id_.addVar(rigid->var_id_);
        if(sym_tb_.exists(rigid->var_name_)){
            throw std::runtime_error("Variable `" + rigid->var_name_ + "` already declared.");
        }
        sym_tb_.insert(rigid->var_name_, CypherSymbol::PATH_VAR, rigid->var_id_);
        sym_tb_.putString(rigid->var_name_);
        
    }else{
        rigid->is_anno_var_ = true;
    }

    return rigid.release();
}


/**
 * @brief visit PatternElement [i.e. pure path pattern, RigidPattern] .
 * @param ctx pointer to CypherParser::OC_PatternElementContext
 * @return GPStore::RigidPattern *
*/
antlrcpp::Any PCypherParser::visitOC_PatternElement(CypherParser::OC_PatternElementContext *ctx){
    if(ctx->oC_PatternElement()){
        return visitOC_PatternElement(ctx->oC_PatternElement());
    }
    std::unique_ptr<GPStore::RigidPattern> rigid(new GPStore::RigidPattern());
    std::unique_ptr<GPStore::NodePattern> node(visitOC_NodePattern(ctx->oC_NodePattern()).as<GPStore::NodePattern*>());
    std::unique_ptr<GPStore::EdgePattern> edge;
    rigid->nodes_.emplace_back(*node);
    rigid->covered_node_var_id_.addVar(node->var_id_);
    rigid->covered_var_id_.addVar(node->var_id_);
    rigid->type_ = GPStore::RigidPattern::PATH;

    for(auto chain_ctx : ctx->oC_PatternElementChain()){
        edge.reset(visitOC_RelationshipPattern(chain_ctx->oC_RelationshipPattern()).as<GPStore::EdgePattern *>());
        node.reset(visitOC_NodePattern(chain_ctx->oC_NodePattern()).as<GPStore::NodePattern*>());
        

        rigid->covered_node_var_id_.addVar(node->var_id_);
        rigid->covered_var_id_.addVar(node->var_id_);

        rigid->covered_edge_var_id_.addVar(edge->var_id_);
        rigid->covered_var_id_.addVar(edge->var_id_);
        
        rigid->nodes_.emplace_back(*node);
        rigid->edges_.emplace_back(*edge);
    }
    return rigid.release();
}

/**
 * @brief visit NodePattern [i.e. RigidPattern] .
 * @param ctx pointer to CypherParser::OC_NodePatternContext
 * @return GPStore::NodePattern *
*/
antlrcpp::Any PCypherParser::visitOC_NodePattern(CypherParser::OC_NodePatternContext *ctx){
    std::unique_ptr<GPStore::NodePattern> node(new GPStore::NodePattern());
    node->type_ = GPStore::NodePattern::NODE_VAR;
    if(ctx->oC_Variable()){
        node->var_name_ = ctx->oC_Variable()->getText();
        node->is_anno_var_ = false;
        if(sym_tb_.exists(node->var_name_)){
            // TODO: CHECK type .
            node->var_id_ = sym_tb_.search(node->var_name_).var_id_;
        } else {
            node->var_id_ = sym_tb_.getNextVarId();
            sym_tb_.insert(node->var_name_,CypherSymbol::NODE_VAR,node->var_id_);
            sym_tb_.putString(node->var_name_);
        }
    }else{
        node->is_anno_var_ = true;
        node->var_id_ = sym_tb_.getNextVarId();
        node->var_name_ = sym_tb_.getAnnoName();
        sym_tb_.insert(node->var_name_, CypherSymbol::NODE_VAR, node->var_id_);
        sym_tb_.putString(node->var_name_);
    }

    if(ctx->oC_NodeLabels()){
        for(auto node_label_ctx : ctx->oC_NodeLabels()->oC_NodeLabel()){
            node->labels_.emplace_back(node_label_ctx->oC_LabelName()->getText());
        }
    }
    if(ctx->oC_Properties()){
        if(ctx->oC_Properties()->oC_Parameter()){
            node->param_str_ = ctx->oC_Properties()->oC_Parameter()->oC_SymbolicName()->getText();
        }else{
            auto map_ctx = ctx->oC_Properties()->oC_MapLiteral();
            std::vector<std::string> keys;
            std::vector<unsigned> prop_ids;
            std::vector<std::unique_ptr<GPStore::Expression>> values;
            unsigned n = map_ctx->oC_Expression().size();
            for(unsigned i = 0; i < n; ++i){
                keys.emplace_back(map_ctx->oC_PropertyKeyName(i)->getText());
                prop_ids.push_back(sym_tb_.getPropId(keys.back()));
                values.emplace_back(visitOC_Expression(map_ctx->oC_Expression(i)).as<GPStore::Expression*>());
            }
            for(int i = 0; i < n; ++i){
                node->properties_.emplace(make_pair(keys[i], *values[i]));
                node->prop_id_.emplace(std::make_pair(keys[i], prop_ids[i]));
            }
        }
    }
    return node.release();
}

/**
 * @brief visit RelationshipPattern [i.e. EdgePattern] .
 * @param ctx pointer to CypherParser::OC_RelationshipPatternContext
 * @return GPStore::EdgePattern *
*/
antlrcpp::Any PCypherParser::visitOC_RelationshipPattern(CypherParser::OC_RelationshipPatternContext *ctx){
    std::unique_ptr<GPStore::EdgePattern> edge(new GPStore::EdgePattern());
    edge->type_ = GPStore::EdgePattern::EDGE_VAR;
    if(ctx->oC_LeftArrowHead()){
        if(ctx->oC_RightArrowHead()){
            edge->arrow_direction_ = GPStore::EdgePattern::UNDIRECTED;
        } else {
            edge->arrow_direction_ = GPStore::EdgePattern::LEFT_ARROW;
        }
    }else if(ctx->oC_RightArrowHead()){
        edge->arrow_direction_ = GPStore::EdgePattern::RIGHT_ARROW;
    } else {
        edge->arrow_direction_ = GPStore::EdgePattern::UNDIRECTED;
    }

    auto detail_ctx = ctx->oC_RelationshipDetail();

    if(detail_ctx->oC_Variable()){
        edge->var_name_ = detail_ctx->oC_Variable()->getText();
        edge->is_anno_var_ = false;
        if(sym_tb_.exists(edge->var_name_)){
            edge->var_id_ = sym_tb_.search(edge->var_name_).var_id_;
        } else {
            edge->var_id_ = sym_tb_.getNextVarId();
            sym_tb_.insert(edge->var_name_,CypherSymbol::EDGE_VAR ,edge->var_id_);
            sym_tb_.putString(edge->var_name_);
        }
    }else{
        edge->is_anno_var_ = true;
        edge->var_id_ = sym_tb_.getNextVarId();
        edge->var_name_ = sym_tb_.getAnnoName();
        sym_tb_.insert(edge->var_name_,CypherSymbol::EDGE_VAR ,edge->var_id_);
        sym_tb_.putString(edge->var_name_);
    }

    if(detail_ctx->oC_RelationshipTypes()){
        for(auto rela_type_ctx : detail_ctx->oC_RelationshipTypes()->oC_RelTypeName()){
            edge->edge_types_.emplace_back(rela_type_ctx->getText());
        }
    }
    edge->is_edge_length_v_ = false;
    if(detail_ctx->oC_RangeLiteral()){
        auto range_ = (std::pair<unsigned long long, unsigned long long>*)visitOC_RangeLiteral(detail_ctx->oC_RangeLiteral()).as<void*>();
        if(range_->first == range_->second && range_->first == 1){
            edge->is_edge_length_v_ = false;
        } else{
            edge->is_edge_length_v_ = true;
            edge->range_left_ = range_->first;
            edge->range_right_ = range_->second;
        }
        delete range_;
    }
    if(detail_ctx->oC_Properties()){
        if(detail_ctx->oC_Properties()->oC_Parameter()){
            edge->param_str_ = detail_ctx->oC_Properties()->oC_Parameter()->oC_SymbolicName()->getText();
        }else{
            auto map_ctx = detail_ctx->oC_Properties()->oC_MapLiteral();
            std::vector<std::string> keys;
            std::vector<unsigned> prop_ids;
            std::vector<std::unique_ptr<GPStore::Expression>> values;
            unsigned n = map_ctx->oC_Expression().size();
            for(unsigned i = 0; i < n; ++i){
                keys.emplace_back(map_ctx->oC_PropertyKeyName(i)->getText());
                prop_ids.push_back(sym_tb_.getPropId(keys.back()));
                values.emplace_back(visitOC_Expression(map_ctx->oC_Expression(i)).as<GPStore::Expression*>());
            }
            for(int i = 0; i < n; ++i){
                edge->properties_.emplace(make_pair(keys[i], *values[i]));
                edge->prop_id_.emplace(make_pair(keys[i], prop_ids[i]));
            }
        }
    }
    
    return edge.release();
}

/**
 * @brief visit RangeLiteral 
 * @param ctx pointer to CypherParser::OC_RangeLiteralContext
 * @return void*, pointer to std::pair<unsigned long long, unsigned long long>
*/
antlrcpp::Any PCypherParser::visitOC_RangeLiteral(CypherParser::OC_RangeLiteralContext *ctx){

    int idx, n = ctx->children.size();
    unsigned long long left, right;
    for(idx = 0; idx < n; ++idx){
        if(ctx->children[idx]->getText() == "..")break;
    }
    if(idx == n){
        // 没有..
        if(ctx->oC_IntegerLiteral().size()){
            // 形如 *3
            left = parseIntegerLiteral(ctx->oC_IntegerLiteral()[0]->getText());
            right = left;
        }
        else{
            left = 1;
            right = GPStore::EdgePattern::RANGE_INF;
        }
    }else{
        // 有..
        if(ctx->oC_IntegerLiteral().size() == 2){
            left = parseIntegerLiteral(ctx->oC_IntegerLiteral()[0]->getText());
            right = parseIntegerLiteral(ctx->oC_IntegerLiteral()[1]->getText());
        }else if(ctx->oC_IntegerLiteral().size()){
            const std::string &int_literal = ctx->oC_IntegerLiteral()[0]->getText();
            int i;
            for(i = 0; i < idx; ++i)
                if(ctx->children[i]->getText() == int_literal)
                    break;
            if(i < idx){
                // *5..
                left = parseIntegerLiteral(int_literal);
                right = GPStore::EdgePattern::RANGE_INF;
            }else{
                //*.. 5
                left = 1;
                right = parseIntegerLiteral(int_literal);
            }
        }
    }
    return (void*)new std::pair<unsigned long long ,unsigned long long >(left, right);
}

/**
 * @brief visit Cypher Expression.
 * @param ctx pointer to CypherParser::OC_ExpressionContext
 * @return GPStore::Expression *
*/
antlrcpp::Any PCypherParser::visitOC_Expression(CypherParser::OC_ExpressionContext *ctx){
    return visitOC_OrExpression(ctx->oC_OrExpression());
}

antlrcpp::Any PCypherParser::visitOC_OrExpression(CypherParser::OC_OrExpressionContext *ctx){
    if(ctx->OR().size() == 0){
        return visitOC_XorExpression(ctx->oC_XorExpression(0));
    }
    std::vector<std::unique_ptr<GPStore::Expression>> xor_exps;
    for(auto xor_ctx : ctx->oC_XorExpression()){
        xor_exps.emplace_back( visitOC_XorExpression(xor_ctx).as<GPStore::Expression *>() );
    }
    GPStore::Expression *exp = new GPStore::Expression();
    
    exp->oprt_ = GPStore::Expression::OR;

    for(const auto &xor_exp : xor_exps){
        exp->covered_var_id_ += xor_exp->covered_var_id_;
        exp->covered_props_ += xor_exp->covered_props_;
    }
    
    for(auto& xor_exp : xor_exps){
        exp->children_.push_back(xor_exp.release());
    }

    return exp;
}

antlrcpp::Any PCypherParser::visitOC_XorExpression(CypherParser::OC_XorExpressionContext *ctx){
    if(ctx->XOR().size() == 0){
        return visitOC_AndExpression(ctx->oC_AndExpression(0));
    }
    std::vector<std::unique_ptr<GPStore::Expression>> and_exps;
    for(auto and_ctx : ctx->oC_AndExpression()){
        and_exps.emplace_back( visitOC_AndExpression(and_ctx).as<GPStore::Expression *>() );
    }

    GPStore::Expression *exp = new GPStore::Expression();
    
    exp->oprt_ = GPStore::Expression::XOR;

   
    for(const auto & and_exp : and_exps){
        exp->covered_var_id_ += and_exp->covered_var_id_;
        exp->covered_props_ += and_exp->covered_props_;
    }   

    for(auto& and_exp : and_exps){
        exp->children_.push_back(and_exp.release());
    }

    return exp;
}

antlrcpp::Any PCypherParser::visitOC_AndExpression(CypherParser::OC_AndExpressionContext *ctx){
    if(ctx->AND().size() == 0){
        return visitOC_NotExpression(ctx->oC_NotExpression(0));
    }
    std::vector<std::unique_ptr<GPStore::Expression>> not_exps;
    for(auto not_ctx : ctx->oC_NotExpression()){
        not_exps.emplace_back( visitOC_NotExpression(not_ctx).as<GPStore::Expression *>() );
    }

    GPStore::Expression *exp = new GPStore::Expression();
    
    exp->oprt_ = GPStore::Expression::AND;

    for(const auto & not_exp : not_exps){
        exp->covered_var_id_ += not_exp->covered_var_id_;
        exp->covered_props_ += not_exp->covered_props_;
    }

    for(auto& not_exp : not_exps){
        exp->children_.push_back(not_exp.release());
    }

    return exp;
}

antlrcpp::Any PCypherParser::visitOC_NotExpression(CypherParser::OC_NotExpressionContext *ctx){
    if(ctx->NOT().size() == 0){
        return visitOC_ComparisonExpression(ctx->oC_ComparisonExpression());
    }
    GPStore::Expression *comp = visitOC_ComparisonExpression(ctx->oC_ComparisonExpression())\
                                .as<GPStore::Expression *>();
    GPStore::Expression *exp = new GPStore::Expression();
    exp->oprt_ = GPStore::Expression::NOT;
    exp->covered_var_id_ = comp->covered_var_id_;
    exp->covered_props_ = comp->covered_props_;
    exp->children_.push_back(comp);

    if(ctx->NOT().size() % 2 == 0){
        auto tmp = exp;
        exp = new GPStore::Expression();
        exp->oprt_ = GPStore::Expression::NOT;
        exp->covered_var_id_ = tmp->covered_var_id_;
        exp->covered_props_ = tmp->covered_props_;
        exp->children_.push_back(tmp);
    }
    return exp;
}

antlrcpp::Any PCypherParser::visitOC_ComparisonExpression(CypherParser::OC_ComparisonExpressionContext *ctx){
    if(ctx->oC_PartialComparisonExpression().size() == 0){
        return visitOC_StringListNullPredicateExpression(ctx->oC_StringListNullPredicateExpression());
    }
    std::vector<std::unique_ptr<GPStore::Expression>> slnp_exps;
    std::vector<GPStore::Expression::OperatorType> oprts;
    
    slnp_exps.emplace_back(
        visitOC_StringListNullPredicateExpression(ctx->oC_StringListNullPredicateExpression())\
        .as<GPStore::Expression*>() );
    
    for(auto partial_comp_ctx : ctx->oC_PartialComparisonExpression()){
        const std::string& text = partial_comp_ctx->getText();
        if(text[0] == '='){
            oprts.push_back(GPStore::Expression::EQUAL);
        }else if(text[0] == '>'){
            if(text.size() > 1 && text[1] == '='){
                oprts.push_back(GPStore::Expression::GREATER_EQUAL);
            }else{
                oprts.push_back(GPStore::Expression::GREATER);
            }
        }else if(text[0] == '<'){
            if(text.size() > 1 && text[1] == '='){
                oprts.push_back(GPStore::Expression::LESS_EQUAL);
            }else if(text.size() > 1  && text[1] == '>'){
                oprts.push_back(GPStore::Expression::NOT_EQUAL);
            }else{
                oprts.push_back(GPStore::Expression::LESS);
            }
        }
        
        slnp_exps.emplace_back(visitOC_StringListNullPredicateExpression \
        (partial_comp_ctx->oC_StringListNullPredicateExpression()).as<GPStore::Expression *>());
    }

    unsigned n = oprts.size();
    GPStore::Expression *exp = new GPStore::Expression();
    if( n == 1 ){
        exp->oprt_ = oprts[0];
        exp->children_.push_back(slnp_exps[0].release());
        exp->children_.push_back(slnp_exps[1].release());
        exp->covered_var_id_ = exp->children_[0]->covered_var_id_ + exp->children_[1]->covered_var_id_;
        exp->covered_props_ = exp->children_[0]->covered_props_ + exp->children_[1]->covered_props_;
        return exp;
    }

    exp->oprt_ = GPStore::Expression::AND;
    for(unsigned i = 0; i < n; ++i){
        //slnp_exp i, i + 1; use i and copy i + 1
        GPStore::Expression *comp_tmp = new GPStore::Expression();
        comp_tmp->oprt_ = oprts[i];
        comp_tmp->children_.push_back(slnp_exps[i].release());
        comp_tmp->children_.push_back ( new GPStore::Expression(*slnp_exps[i + 1]) );
        comp_tmp->covered_var_id_ = comp_tmp->children_[0]->covered_var_id_ + comp_tmp->children_[1]->covered_var_id_;
        comp_tmp->covered_props_ = comp_tmp->children_[0]->covered_props_ + comp_tmp->children_[1]->covered_props_;
        
        exp->children_.push_back(comp_tmp);
    }

    for(auto child : exp->children_){
        exp->covered_var_id_ += child->covered_var_id_;
        exp->covered_props_ += child->covered_props_;   
    }

    return exp;
}


antlrcpp::Any PCypherParser::visitOC_StringListNullPredicateExpression(CypherParser::OC_StringListNullPredicateExpressionContext *ctx){
    unsigned n = ctx->children.size();
    if(n == 1){
        return visitOC_AddOrSubtractExpression(ctx->oC_AddOrSubtractExpression());
    }

    std::unique_ptr<GPStore::Expression> exp( 
        visitOC_AddOrSubtractExpression(ctx->oC_AddOrSubtractExpression()).as<GPStore::Expression*>()
    );

    unsigned str_pre_ptr = 0, lst_pre_ptr = 0, null_pre_ptr = 0;
    for(unsigned i = 1; i < n; ++i){
        const std::string& text = ctx->children[i]->getText();
        GPStore::Expression::OperatorType oprt;
        GPStore::Expression *tmp = nullptr, *addsub_exp = nullptr;

        // Initialize oprt && addsub_exp

        if(str_pre_ptr < ctx->oC_StringPredicateExpression().size() &&
        ctx->oC_StringPredicateExpression(str_pre_ptr)->getText() == text){

            addsub_exp = visitOC_AddOrSubtractExpression(
                ctx->oC_StringPredicateExpression(str_pre_ptr)->oC_AddOrSubtractExpression()
            ).as<GPStore::Expression*>();

            if(ctx->oC_StringPredicateExpression(str_pre_ptr)->STARTS() != nullptr){
                oprt = GPStore::Expression::STARTS_WITH;
            }else if(ctx->oC_StringPredicateExpression(str_pre_ptr)->ENDS() != nullptr){
                oprt = GPStore::Expression::ENDS_WITH;
            }else{
                oprt = GPStore::Expression::CONTAINS;
            }
            ++str_pre_ptr;

        }
        else if(lst_pre_ptr < ctx->oC_ListPredicateExpression().size() &&
        ctx->oC_ListPredicateExpression(lst_pre_ptr)->getText() == text){
            addsub_exp = visitOC_AddOrSubtractExpression(
                ctx->oC_ListPredicateExpression(lst_pre_ptr)->oC_AddOrSubtractExpression()
            ).as<GPStore::Expression*>();
            oprt = GPStore::Expression::IN;
            ++lst_pre_ptr;

        } 
        else if(null_pre_ptr < ctx->oC_NullPredicateExpression().size() &&
        ctx->oC_NullPredicateExpression(null_pre_ptr)->getText() == text){

            if(ctx->oC_NullPredicateExpression(null_pre_ptr)->NOT() != nullptr){
                oprt = GPStore::Expression::IS_NOT_NULL;
            }else{
                oprt = GPStore::Expression::IS_NULL;
            }
            ++null_pre_ptr;
        }

        tmp = new GPStore::Expression();
        if(oprt == GPStore::Expression::IS_NOT_NULL || oprt == GPStore::Expression::IS_NULL){
            tmp->oprt_ = oprt;
            tmp->covered_props_ = exp->covered_props_;
            tmp->covered_var_id_ = exp->covered_var_id_;

            tmp->children_.push_back(exp.release());
        } else {

            tmp->oprt_ = oprt;
            tmp->covered_var_id_ = exp->covered_var_id_ + addsub_exp->covered_var_id_;
            tmp->covered_props_ = exp->covered_props_ + addsub_exp->covered_props_;

            tmp->children_.push_back(exp.release());
            tmp->children_.push_back(addsub_exp);

        }
        exp.reset(tmp);
    } // for(unsigned i = 1; i < n; ++i)

    return exp.release();
}

antlrcpp::Any PCypherParser::visitOC_AddOrSubtractExpression(CypherParser::OC_AddOrSubtractExpressionContext *ctx){
    if(ctx->oC_MultiplyDivideModuloExpression().size() == 1){
        return visitOC_MultiplyDivideModuloExpression(ctx->oC_MultiplyDivideModuloExpression(0));
    }
    std::unique_ptr<GPStore::Expression> exp(
        visitOC_MultiplyDivideModuloExpression(ctx->oC_MultiplyDivideModuloExpression(0)).as<GPStore::Expression *>()
    );

    unsigned n = ctx->children.size(), mul_ptr = 1;
    GPStore::Expression *tmp = nullptr, *muldiv_exp = nullptr;

    for(unsigned i = 1; i < n; ++i){
        const std::string& text = ctx->children[i]->getText();
        GPStore::Expression::OperatorType op;

        if(text.size() == 1 && text[0] == '+'){
            op = GPStore::Expression::ADD;
        }else if(text.size() == 1 && text[0] == '-'){
            op = GPStore::Expression::SUB;
        } else {
            continue;
        }

        muldiv_exp = visitOC_MultiplyDivideModuloExpression(ctx->oC_MultiplyDivideModuloExpression(mul_ptr)).as<GPStore::Expression *>();
        ++mul_ptr;

        tmp = new GPStore::Expression();
        tmp->oprt_ = op;
        tmp->covered_var_id_ = exp->covered_var_id_ + muldiv_exp->covered_var_id_;
        tmp->covered_props_ = exp->covered_props_ + muldiv_exp->covered_props_;
        tmp->children_.push_back(exp.release());
        tmp->children_.push_back(muldiv_exp);
        exp.reset(tmp);

    }

    return exp.release();
}

antlrcpp::Any PCypherParser::visitOC_MultiplyDivideModuloExpression(CypherParser::OC_MultiplyDivideModuloExpressionContext *ctx){
    if(ctx->oC_PowerOfExpression().size() == 1){
        return visitOC_PowerOfExpression(ctx->oC_PowerOfExpression(0));
    }
    std::unique_ptr<GPStore::Expression> exp(
        visitOC_PowerOfExpression(ctx->oC_PowerOfExpression(0)).as<GPStore::Expression *>()
    );

    unsigned n = ctx->children.size(), pow_ptr = 1;
    GPStore::Expression *tmp = nullptr, *pow_exp = nullptr;

    for(unsigned i = 1; i < n; ++i){
        const std::string& text = ctx->children[i]->getText();
        GPStore::Expression::OperatorType op;

        if(text.size() == 1 && text[0] == '*'){
            op = GPStore::Expression::MUL;
        }else if(text.size() == 1 && text[0] == '/'){
            op = GPStore::Expression::DIV;
        } else if(text.size() == 1 && text[0] == '%'){
            op = GPStore::Expression::MOD;
        } else {
            continue;
        }

        pow_exp = visitOC_PowerOfExpression(ctx->oC_PowerOfExpression(pow_ptr)).as<GPStore::Expression *>();
        ++pow_ptr;

        tmp = new GPStore::Expression();
        tmp->oprt_ = op;
        tmp->covered_var_id_ = exp->covered_var_id_ + pow_exp->covered_var_id_;
        tmp->covered_props_ = exp->covered_props_ + pow_exp->covered_props_;
        tmp->children_.push_back(exp.release());
        tmp->children_.push_back(pow_exp);
        
        exp.reset(tmp);

    }

    return exp.release();
}

antlrcpp::Any PCypherParser::visitOC_PowerOfExpression(CypherParser::OC_PowerOfExpressionContext *ctx){
    if(ctx->oC_UnaryAddOrSubtractExpression().size() == 1){
        return visitOC_UnaryAddOrSubtractExpression(ctx->oC_UnaryAddOrSubtractExpression(0));
    }

    std::unique_ptr<GPStore::Expression> exp(
    visitOC_UnaryAddOrSubtractExpression(ctx->oC_UnaryAddOrSubtractExpression(0)).as<GPStore::Expression*>()
    );

    int n = ctx->oC_UnaryAddOrSubtractExpression().size();
    for(unsigned i = 1; i < n; ++i){
        auto unary_exp = visitOC_UnaryAddOrSubtractExpression(ctx->oC_UnaryAddOrSubtractExpression(i))
        .as<GPStore::Expression*>();
        auto tmp = new GPStore::Expression();
        tmp->oprt_ = GPStore::Expression::POW;
        tmp->covered_var_id_ = exp->covered_var_id_ + unary_exp->covered_var_id_;
        tmp->covered_props_ = exp->covered_props_ + unary_exp->covered_props_;
        tmp->children_.push_back(exp.release());
        tmp->children_.push_back(unary_exp);

        exp.reset(tmp);
    }
    return exp.release();
}

antlrcpp::Any PCypherParser::visitOC_UnaryAddOrSubtractExpression(CypherParser::OC_UnaryAddOrSubtractExpressionContext *ctx){
    if(ctx->children.size() == 1){
        return visitOC_ListOperatorExpression(ctx->oC_ListOperatorExpression());
    }
    auto tmp = visitOC_ListOperatorExpression(ctx->oC_ListOperatorExpression()).as<GPStore::Expression*>();
    GPStore::Expression::OperatorType op;
    if(ctx->children[0]->getText()[0] == '+'){
        op = GPStore::Expression::IDENTITY;
    }else{
        op = GPStore::Expression::NEGATION;
    }
    auto exp = new GPStore::Expression();
    exp->oprt_ = op;
    exp->covered_props_ = tmp->covered_props_;
    exp->covered_var_id_ =tmp->covered_var_id_;
    exp->children_.push_back(tmp);
    return exp;
}

antlrcpp::Any PCypherParser::visitOC_ListOperatorExpression(CypherParser::OC_ListOperatorExpressionContext *ctx){
    unsigned n = ctx->children.size();
    if(n == 1){
        return visitOC_PropertyOrLabelsExpression(ctx->oC_PropertyOrLabelsExpression());
    }

    bool has_two_dots = false;
    unsigned exp_ptr = 0, num_exp = ctx->oC_Expression().size();
    
    std::vector<std::unique_ptr<GPStore::Expression>> index_exps;
    std::unique_ptr<GPStore::Expression> exp(visitOC_PropertyOrLabelsExpression(ctx->oC_PropertyOrLabelsExpression()).as<GPStore::Expression *>());
    
    for(auto exp_ctx : ctx->oC_Expression()){
        index_exps.emplace_back( visitOC_Expression(exp_ctx).as<GPStore::Expression *>() );
    }

    for(unsigned i = 1; i < n; ++i){
        const std::string& text = ctx->children[i]->getText();
        if(text.size() == 1 && text[0] == '['){
            has_two_dots = false;
        } else if(text.size() == 1 && text[0] == ']'){
            auto tmp = new GPStore::Expression();
            tmp->children_.push_back(exp.release());
            if(has_two_dots){
                tmp->oprt_ = GPStore::Expression::SLICE;
                tmp->children_.push_back(index_exps[exp_ptr++].release());
                tmp->children_.push_back(index_exps[exp_ptr++].release());
            } else {
                tmp->oprt_ = GPStore::Expression::INDEX;
                tmp->children_.push_back(index_exps[exp_ptr++].release());
            }
            for(auto child : tmp->children_){
                tmp->covered_var_id_ += child->covered_var_id_;
                tmp->covered_props_ += child->covered_props_;
            }
            exp.reset(tmp);
        }
        else if(text.size() == 2 && text[0] == '.' && text[1] == '.'){
            has_two_dots = true;
        }
    }

    return exp.release();
}

antlrcpp::Any PCypherParser::visitOC_PropertyOrLabelsExpression(CypherParser::OC_PropertyOrLabelsExpressionContext *ctx){
    auto atom = visitOC_Atom(ctx->oC_Atom()).as<GPStore::Atom *>();
    
    if(ctx->oC_PropertyLookup().size() != 0 || ctx->oC_NodeLabels() != nullptr){
        auto exp = new GPStore::Expression();
        exp->atom_ = atom;
        exp->covered_var_id_ = atom->covered_var_id_;
        exp->covered_props_ = atom->covered_props_;
        exp->property_label_ = new GPStore::AtomPropertyLabels();
    
        for(auto prop_look_up : ctx->oC_PropertyLookup()){
            exp->property_label_->addKeyName(prop_look_up->oC_PropertyKeyName()->getText());
            unsigned kid = sym_tb_.getPropId(exp->property_label_->key_names_.back());
            exp->property_label_->prop_ids_.push_back(kid);
        }    
        if(ctx->oC_NodeLabels() != nullptr){
            for(auto label : ctx->oC_NodeLabels()->oC_NodeLabel()){
                exp->property_label_->addNodeLabel(label->oC_LabelName()->getText());
            }
        }
        if(atom->atom_type_ == GPStore::Atom::VARIABLE && exp->property_label_->key_names_.size()){
            // TODO: covered propery.

            exp->covered_props_.addVar(std::make_pair(
                dynamic_cast<GPStore::Variable*>(atom)->id_, exp->property_label_->prop_ids_[0]));
        }
        return exp;
    } else if(atom->atom_type_ == GPStore::Atom::PARENTHESIZED_EXPRESSION){
        auto exp = dynamic_cast<GPStore::ParenthesizedExpression*>(atom)->exp_;
        dynamic_cast<GPStore::ParenthesizedExpression*>(atom)->exp_ = nullptr;
        delete atom;
        return exp;
    } else {
        auto exp = new GPStore::Expression();
        exp->atom_ = atom;
        exp->covered_props_ = atom->covered_props_;
        exp->covered_var_id_ = atom->covered_var_id_;
        return exp;
    }
}

/**
 * @brief visit Atom
 * @param ctx pointer to CypherParser::OC_AtomContext
 * @return Atom *
*/
antlrcpp::Any PCypherParser::visitOC_Atom(CypherParser::OC_AtomContext *ctx){
    if(ctx->COUNT() != nullptr){
        return dynamic_cast<GPStore::Atom *>(new GPStore::Count());
    } else if(ctx->oC_Literal() != nullptr){
        return dynamic_cast<GPStore::Atom *>(visitOC_Literal(ctx->oC_Literal()).as<GPStore::Literal *>());
    } else if(ctx->oC_Parameter() != nullptr){
        return dynamic_cast<GPStore::Atom *>(visitOC_Parameter(ctx->oC_Parameter()).as<GPStore::Parameter *>());
    } else if(ctx->oC_CaseExpression() != nullptr ){
        return dynamic_cast<GPStore::Atom *>(visitOC_CaseExpression(ctx->oC_CaseExpression()).as<GPStore::CaseExpression *>());
    } else if(ctx->oC_ListComprehension() != nullptr){
        return dynamic_cast<GPStore::Atom *>(visitOC_ListComprehension(ctx->oC_ListComprehension()).as<GPStore::ListComprehension *>());
    } else if(ctx->oC_PatternComprehension() != nullptr){
        return dynamic_cast<GPStore::Atom *>(visitOC_PatternComprehension(ctx->oC_PatternComprehension()).as<GPStore::PatternComprehension *>());
    } else if(ctx->oC_Quantifier() != nullptr ){
        return dynamic_cast<GPStore::Atom *>(visitOC_Quantifier(ctx->oC_Quantifier()).as<GPStore::Quantifier *>());
    } else if(ctx->oC_PatternPredicate() != nullptr){
        return dynamic_cast<GPStore::Atom *>(visitOC_PatternPredicate(ctx->oC_PatternPredicate()).as<GPStore::PatternPredicate *>());
    } else if(ctx->oC_ParenthesizedExpression() != nullptr){
        return dynamic_cast<GPStore::Atom *>(visitOC_ParenthesizedExpression(ctx->oC_ParenthesizedExpression()).as<GPStore::ParenthesizedExpression *>());
    } else if(ctx->oC_FunctionInvocation() != nullptr ){
        return dynamic_cast<GPStore::Atom *>(visitOC_FunctionInvocation(ctx->oC_FunctionInvocation()).as<GPStore::FunctionInvocation *>());
    } else if(ctx->oC_ExistentialSubquery()){
        return dynamic_cast<GPStore::Atom *>(visitOC_ExistentialSubquery(ctx->oC_ExistentialSubquery()).as<GPStore::ExistentialSubquery*>());
    } else if(ctx->oC_Variable()){
        return dynamic_cast<GPStore::Atom *>(visitOC_Variable(ctx->oC_Variable()).as<GPStore::Variable *>());
    }
    return antlrcpp::Any();
}
    
antlrcpp::Any PCypherParser::visitOC_Literal(CypherParser::OC_LiteralContext *ctx){
    std::unique_ptr<GPStore::Literal> literal(new GPStore::Literal());
    if(ctx->oC_BooleanLiteral()){
        literal->literal_type = GPStore::Literal::BOOLEAN_LITERAL;
        literal->b = (ctx->oC_BooleanLiteral()->TRUE()) ? true : false;
    }else if(ctx->CypherNULL()){
        literal->literal_type = GPStore::Literal::NULL_LITERAL;
    }else if(ctx->oC_NumberLiteral()){
        auto num_ctx = ctx->oC_NumberLiteral();
        if(num_ctx->oC_DoubleLiteral()){
            literal->literal_type = GPStore::Literal::DOUBLE_LITERAL;
            literal->d = parseDoubleLiteral(num_ctx->getText());
        }else{
            literal->literal_type = GPStore::Literal::INT_LITERAL;
            literal->i = parseIntegerLiteral(num_ctx->getText());
        }
    }else if(ctx->StringLiteral()){
        const std::string &text = ctx->StringLiteral()->getText();
        literal->literal_type = GPStore::Literal::STRING_LITERAL;
        literal->s = parseStringLiteral(text);
    }else if(ctx->oC_ListLiteral()){
        literal->literal_type = GPStore::Literal::LIST_LITERAL;
        std::vector<std::unique_ptr<GPStore::Expression>> exps;
        for(auto exp_ctx : ctx->oC_ListLiteral()->oC_Expression()){
            exps.emplace_back(
            visitOC_Expression(exp_ctx).as<GPStore::Expression *>()
            );
            literal->covered_var_id_ += exps.back()->covered_var_id_;
            literal->covered_props_ += exps.back()->covered_props_;
            
        }
        for(auto& exp : exps){
            literal->list_literal.push_back(exp.release());
        }
    }else if(ctx->oC_MapLiteral()){
        literal->literal_type = GPStore::Literal::MAP_LITERAL;
        
        std::vector<std::string> prop_keys;
        std::vector<std::unique_ptr<GPStore::Expression>> exps;
        unsigned n = ctx->oC_MapLiteral()->oC_Expression().size();
        
        for(unsigned i = 0; i < n; ++i){
            prop_keys.push_back(ctx->oC_MapLiteral()->oC_PropertyKeyName(i)->getText());
            exps.emplace_back( visitOC_Expression(ctx->oC_MapLiteral()->oC_Expression(i)).as<GPStore::Expression *>());
            literal->covered_var_id_ += exps.back()->covered_var_id_;
            literal->covered_props_ += exps.back()->covered_props_;
            
        }
        for(unsigned i = 0; i < n; ++i){
            literal->map_literal.insert(make_pair(prop_keys[i], exps[i].release()));
        }
    }
    return literal.release();
}

antlrcpp::Any PCypherParser::visitOC_Parameter(CypherParser::OC_ParameterContext *ctx){
    auto param = new GPStore::Parameter();
    if(ctx->oC_SymbolicName()){
        param->symbolic_name = ctx->getText();
    }else{
        param->parameter_num = parseIntegerLiteral(ctx->DecimalInteger()->getText());
    }
    return param;

}

antlrcpp::Any PCypherParser::visitOC_Variable(CypherParser::OC_VariableContext *ctx){
    std::unique_ptr<GPStore::Variable> var(new GPStore::Variable());
    var->var_ = ctx->getText();
    if(!sym_tb_.exists(var->var_)){
        throw std::runtime_error("Variable `" + var->var_ + "` not defined.");
    }
    var->id_ = sym_tb_.search(var->var_).var_id_;
    var->covered_var_id_.addVar(var->id_);
    return var.release();
}

antlrcpp::Any PCypherParser::visitOC_CaseExpression(CypherParser::OC_CaseExpressionContext *ctx){
    std::unique_ptr<GPStore::CaseExpression> case_exp(new GPStore::CaseExpression());
    

    case_exp->case_type = 
        (ctx->oC_Expression().size() == (int)(bool)(ctx->ELSE())? 
        GPStore::CaseExpression::GENERIC : GPStore::CaseExpression::SIMPLE);
    
    if(case_exp->case_type == GPStore::CaseExpression::SIMPLE){
        case_exp->test_expr = visitOC_Expression(ctx->oC_Expression(0)).as<GPStore::Expression*>();
        case_exp->covered_var_id_ += case_exp->test_expr->covered_var_id_;
        case_exp->covered_props_ += case_exp->covered_props_;
    }

    for(auto ca_ctx : ctx->oC_CaseAlternative()){
        case_exp->when_exprs.push_back(visitOC_Expression(ca_ctx->oC_Expression(0)).as<GPStore::Expression *>());
        case_exp->then_exprs.push_back(visitOC_Expression(ca_ctx->oC_Expression(1)).as<GPStore::Expression *>());
        case_exp->covered_var_id_ += case_exp->when_exprs.back()->covered_var_id_;
        case_exp->covered_props_ += case_exp->when_exprs.back()->covered_props_;
       
        case_exp->covered_var_id_ += case_exp->then_exprs.back()->covered_var_id_;
        case_exp->covered_props_ += case_exp->then_exprs.back()->covered_props_;
    }

    if(ctx->ELSE()){
        case_exp->else_expr = visitOC_Expression(
            ctx->oC_Expression((int)(case_exp->case_type == GPStore::CaseExpression::SIMPLE))
        ).as<GPStore::Expression *>();
        case_exp->covered_var_id_ += case_exp->else_expr->covered_var_id_;
        case_exp->covered_props_ += case_exp->else_expr->covered_props_;
    }

    return case_exp.release();
}

antlrcpp::Any PCypherParser::visitOC_ListComprehension(CypherParser::OC_ListComprehensionContext *ctx) {
    std::unique_ptr<GPStore::ListComprehension> lc_exp(new GPStore::ListComprehension());
    throw std::runtime_error("[ERROR] List Comprehension not implemented.");

    if(ctx->oC_Expression()){
        lc_exp->trans_ = visitOC_Expression(ctx->oC_Expression()).as<GPStore::Expression*>();
    }

    auto fte_ctx = ctx->oC_FilterExpression();
    lc_exp->var_name_ = fte_ctx->oC_IdInColl()->oC_Variable()->getText();

    lc_exp->exp_ = visitOC_Expression(fte_ctx->oC_IdInColl()->oC_Expression()).as<GPStore::Expression*>();

    if(fte_ctx->oC_Where()){
        lc_exp->filter_ = visitOC_Expression(fte_ctx->oC_Where()->oC_Expression()).as<GPStore::Expression*>();
    }

    return lc_exp.release();
}

antlrcpp::Any PCypherParser::visitOC_PatternComprehension(CypherParser::OC_PatternComprehensionContext *ctx){
    throw std::runtime_error("[ERROR] Pattern Comprehension not implemented.");
}

antlrcpp::Any PCypherParser::visitOC_Quantifier(CypherParser::OC_QuantifierContext *ctx){
    throw std::runtime_error("[ERROR] Quantifier not implemented.");
    std::unique_ptr<GPStore::Quantifier> qntf(new GPStore::Quantifier);
    if(ctx->ALL()){
        qntf->quantifier_type_ = GPStore::Quantifier::ALL;
    } else if(ctx-> ANY()){
        qntf->quantifier_type_ = GPStore::Quantifier::ANY;
    } else if(ctx->NONE()){
        qntf->quantifier_type_ = GPStore::Quantifier::NONE;
    } else if(ctx->SINGLE()){
        qntf->quantifier_type_ = GPStore::Quantifier::SINGLE;
    }
    auto fte_ctx = ctx->oC_FilterExpression();
    qntf->var_name_ = fte_ctx->oC_IdInColl()->oC_Variable()->getText();

    qntf->container_ =  visitOC_Expression(fte_ctx->oC_IdInColl()->oC_Expression()).as<GPStore::Expression *>();

    if(fte_ctx->oC_Where()){
        qntf->exp_ =  visitOC_Expression(fte_ctx->oC_Where()->oC_Expression()).as<GPStore::Expression*>();
    }
    return qntf.release();
}

antlrcpp::Any PCypherParser::visitOC_PatternPredicate(CypherParser::OC_PatternPredicateContext *ctx){
    throw std::runtime_error("[ERROR] Pattern Predicate not implemented.");
}

antlrcpp::Any PCypherParser::visitOC_FunctionInvocation(CypherParser::OC_FunctionInvocationContext *ctx){
    std::vector<std::unique_ptr<GPStore::Expression>> args;
    std::vector<std::string> func_name;
    auto fn_ctx = ctx->oC_FunctionName();
    for(auto sch : fn_ctx->oC_Namespace()->oC_SchemaName()){
        func_name.push_back(sch->getText());
    }
    func_name.push_back(fn_ctx->oC_SchemaName()->getText());
    
    for(auto exp_ctx : ctx->oC_Expression()){
        args.emplace_back(visitOC_Expression(exp_ctx).as<GPStore::Expression *>());
    }

    std::unique_ptr<GPStore::FunctionInvocation> func_invoc(new GPStore::FunctionInvocation());
    if(func_invoc->isAggregationFunction()){
        for(auto & arg: args){
            if(arg->containsAggrFunc()){
                throw std::runtime_error("[ERROR] Can't use aggregate functions inside of aggregate functions.");
            }
        }
    }
    func_invoc->distinct = (bool)ctx->DISTINCT();
    for(auto & arg : args){
        func_invoc->covered_var_id_ += arg->covered_var_id_;
        func_invoc->covered_props_ += arg->covered_props_;
        func_invoc->args.push_back(arg.release());

    }
    for(const auto& str : func_name){
        func_invoc->func_name_.emplace_back(str);
    }
    
    return func_invoc.release();
}

antlrcpp::Any PCypherParser::visitOC_ExistentialSubquery(CypherParser::OC_ExistentialSubqueryContext *ctx){
    throw std::runtime_error("[ERROR] Existential Subquery not implemented.");
}

antlrcpp::Any PCypherParser::visitOC_ParenthesizedExpression(CypherParser::OC_ParenthesizedExpressionContext *ctx) {
    auto exp = visitOC_Expression(ctx->oC_Expression()).as<GPStore::Expression*>();
    auto parenthesized = new GPStore::ParenthesizedExpression();
    parenthesized->exp_ = exp;
    parenthesized->covered_var_id_ = exp->covered_var_id_;
    parenthesized->covered_props_ = exp->covered_props_;
    return parenthesized;
}


bool SymbolTableStack::exists(const std::string & var) const{
    unsigned n = symbol_tb_st_.size();
    if(n == 0) return false;
    for(int i = n - 1; i >= 0; --i){
        if(symbol_tb_st_[i].find(var) != symbol_tb_st_[i].end())
            return true;
    }

    return false;
}

/**
 * @brief search the variable var in symbol table . should make sure exists(var)==true
 * @param var variable name
 * @return CypherSymbol&
*/
CypherSymbol& SymbolTableStack::search(const std::string & var) {
    unsigned n = symbol_tb_st_.size();
    for(int i = n - 1; i >= 0; --i){
        auto it = symbol_tb_st_[i].find(var);
        if(symbol_tb_st_[i].end() != it)
            return it->second;
    }
    return symbol_tb_st_[0].at(var);
}

void SymbolTableStack::insert(const std::string& var_name, const CypherSymbol& sym){
    symbol_tb_st_.back().insert(std::make_pair(var_name, sym));
}
void SymbolTableStack::insert(const std::string& var_name, CypherSymbol::VarType var_ty, unsigned var_id){
    symbol_tb_st_.back().insert(std::make_pair(var_name, CypherSymbol(var_ty, var_id)));
}

void SymbolTableStack::clearExcept(const std::vector<std::string> & remain_var){
    unsigned n = symbol_tb_st_.size();
    if(n == 0) return;
    decltype(symbol_tb_st_) symbol_tb_st_new;

    for(unsigned i = 0; i < n; ++i){
        symbol_tb_st_new.emplace_back();
    }

    for(int i = n - 1; i >= 0; --i){
        for(const auto &p : symbol_tb_st_[i]){
            if(find(remain_var.begin(), remain_var.end(), p.first) != remain_var.end()){
                symbol_tb_st_new[i].insert(make_pair(p.first, p.second));
            }
        }
    }

    symbol_tb_st_.swap(symbol_tb_st_new);
}

void SymbolTableStack::clear(){
    symbol_tb_st_.clear();
}

void SymbolTableStack::reset(){
    symbol_tb_st_.clear();
    id2string_.clear();
    prop2id_.clear();
    prop_id2string_.clear();
    next_var_id_ = 0;
    next_anno_id_ = 0;
    next_prop_id_ = 0;
}


void SymbolTableStack::push(){
    symbol_tb_st_.emplace_back();
}

void SymbolTableStack::pop(){
    symbol_tb_st_.pop_back();
}

unsigned SymbolTableStack::getNextVarId(){
    return next_var_id_++;
}

std::string SymbolTableStack::getAnnoName(){
    return "@anno_" + std::to_string(next_anno_id_++);
}

std::vector<unsigned> SymbolTableStack::getAllVarId(){
    PVarset<unsigned> var_ids;
    for(const auto &ma : symbol_tb_st_){
        for(const auto &p : ma){
            var_ids.addVar(p.second.var_id_);
        }
    }
    return var_ids.vars;
}

std::vector<unsigned> SymbolTableStack::getAllNamedVarId(){
    PVarset<unsigned> var_ids;
    for(const auto &ma : symbol_tb_st_){
        for(const auto &p : ma){
            if(p.first.at(0) != '@')
                var_ids.addVar(p.second.var_id_);
        }
    }
    return var_ids.vars;
}

/**
 * @brief Return the prop id of a prop name, and save the id<->prop map.
*/
unsigned SymbolTableStack::getPropId(const std::string &prop){
    auto it = prop2id_.find(prop);
    if(it != prop2id_.end()){
        return it->second;
    } else {
        // access PStore here! We use fake id now.
        unsigned new_id = next_prop_id_++;
        // we dont check new_id == 0xfffffff, it is not important
        prop2id_.insert(std::make_pair(prop, new_id));
        prop_id2string_.insert(std::make_pair(new_id, prop));
        return new_id;
    }
}
