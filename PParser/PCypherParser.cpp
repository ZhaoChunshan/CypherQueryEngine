#include <iostream>
#include <sstream>
#include "PCypherParser.h"
#include "../PQuery/PQueryOperator.h"
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
void PCypherParser::CypherParse(const std::string &query)
{
	try{
		std::istringstream ifs(query);
        CypherParse(ifs);
	}catch(const std::runtime_error& e1)
	{
		throw std::runtime_error(e1.what());
	}
}

/**
	Overall driver function for query parsing.

	@param in istream of the query.
*/
void PCypherParser::CypherParse(std::istream& in){
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
        visitOC_Cypher(ctx);

    } catch (const std::runtime_error& e1) {
        throw std::runtime_error(e1.what());
    }
}

antlrcpp::Any PCypherParser::visitOC_Query(CypherParser::OC_QueryContext *ctx)
{
    if(ctx->oC_RegularQuery()){
        visitOC_RegularQuery(ctx->oC_RegularQuery());
    }else{
        visitOC_StandaloneCall(ctx->oC_StandaloneCall());
    }
    return antlrcpp::Any();
}

/**
 * @brief visit regular query (singleQuery1 UNION singleQuery2 UNION singleQuery3)
 * @param ctx CypherParser::OC_RegularQueryContext
 * @return PQueryOperator*: Root node of the plan tree.
*/
antlrcpp::Any PCypherParser::visitOC_RegularQuery(CypherParser::OC_RegularQueryContext *ctx)
{
    unsigned n = ctx->oC_Union().size();

    // TODO: Check every single query has a return clause.

    PQueryOperator *tree = visitOC_SingleQuery(ctx->oC_SingleQuery()).as<PQueryOperator *>();
    for(unsigned i = 0; i < n; ++i){
        PQueryOperator *tmp, *new_node;
        try {
            tmp = visitOC_SingleQuery(ctx->oC_Union(i)->oC_SingleQuery()).as<PQueryOperator *>();
        }catch (const std::runtime_error& e1) {
            delete tree;
            throw std::runtime_error(e1.what());
        }
        
        new_node = new PQueryOperator(PQueryOperator::UNION);
        if(ctx->oC_Union(i)->ALL())
            new_node->union_ty_ = PQueryOperator::CYPHER_UNION_ALL;
        else
            new_node->union_ty_ = PQueryOperator::CYPHER_UNION;
        tmp->parent_ = tree->parent_ = new_node;
        new_node->left_ = tree;
        new_node->right_ = tmp;

        tree = new_node;
        
        if(!(tree->left_->minial_varset_ == tree->left_->maximal_varset_) ||
         !(tree->right_->minial_varset_ == tree->right_->maximal_varset_) ||
         !(tree->left_->maximal_varset_ == tree->right_->maximal_varset_)){
            delete tree;
            throw std::runtime_error("[ERROR] All sub queries in an UNION must have the same return column names.");
        }

        tree->maximal_varset_ = tree->left_->maximal_varset_;
        tree->minial_varset_ = tree->maximal_varset_;
    }
    return tree;
}

antlrcpp::Any PCypherParser::visitOC_StandaloneCall(CypherParser::OC_StandaloneCallContext *ctx)
{
    throw std::runtime_error("[ERROR] Standalone call not implemented.");
    return antlrcpp::Any();
}

/**
 * @brief visit single query(a query that doesnot have UNION clause, but may have serveral WITH clauses and a RETURN clause.
 * @param ctx pointer to CypherParser::OC_SingleQueryContext 
 * @return PQueryOperator*: Root node of the plan tree.
*/
antlrcpp::Any PCypherParser::visitOC_SingleQuery(CypherParser::OC_SingleQueryContext *ctx)
{
    if(ctx->oC_SinglePartQuery()){
        return visitOC_SinglePartQuery(ctx->oC_SinglePartQuery());
    }else{
        return visitOC_MultiPartQuery(ctx->oC_MultiPartQuery());
    }
}

/**
 * @brief visit single part query(a query that only has reading clauses and a RETURN clause.
 * @param ctx pointer to CypherParser::OC_SingleQueryContext 
 * @return PQueryOperator*: Root node of the plan tree.
*/
antlrcpp::Any PCypherParser::visitOC_SinglePartQuery(CypherParser::OC_SinglePartQueryContext *ctx){
    PQueryOperator *tree = nullptr;
    for(auto read_ctx : ctx->oC_ReadingClause()){
        PQueryOperator *tmp = nullptr, *new_node = nullptr;
        try {
            tmp = visitOC_ReadingClause(read_ctx);
        }
        
    }
}

antlrcpp::Any PCypherParser::visitOC_MultiPartQuery(CypherParser::OC_MultiPartQueryContext *ctx){

}
