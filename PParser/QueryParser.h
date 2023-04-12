#include <typeinfo>

#include "antlr4-runtime.h"
#include "CypherLexer.h"
#include "CypherParser.h"
#include "CypherBaseVisitor.h"
#include "QueryTree.h"

/**
	Parser for Cypher queries, inherited from CypherBaseVisitor, which is
	automatically generated from the Cypher grammar by ANTLR. Implements
	visiting important grammatical units, extracts relevant information,
	and stores in QueryTree (pointed to by query_tree_ptr).
*/
class QueryParser: public CypherBaseVisitor
{
private:
	QueryTree *query_tree_ptr;
public:
	QueryParser(){query_tree_ptr = nullptr;}
	QueryParser(QueryTree *qtp): query_tree_ptr(qtp) {}
	void setQueryTree(QueryTree *qtp) { query_tree_ptr = qtp; }
	void CypherParse(const std::string &query);	// Overall driver function

	antlrcpp::Any visitOC_Query(CypherParser::OC_QueryContext *ctx);
	
    antlrcpp::Any visitOC_RegularQuery(CypherParser::OC_RegularQueryContext *ctx, QueryTree *qt);

    antlrcpp::Any visitOC_SingleQuery(CypherParser::OC_SingleQueryContext *ctx, SingleQuery *single_query);

	antlrcpp::Any visitOC_Union(CypherParser::OC_UnionContext *ctx, QueryTree *qt);
	
    antlrcpp::Any visitOC_SinglePartQuery(CypherParser::OC_SinglePartQueryContext *ctx, MultiPartQueryUnit *query_unit);

    antlrcpp::Any visitOC_MultiPartQuery(CypherParser::OC_MultiPartQueryContext *ctx, SingleQuery *single_query);

	antlrcpp::Any visitOC_ReadingClause(CypherParser::OC_ReadingClauseContext *ctx, ReadingClause **rc_ptr);

    antlrcpp::Any visitOC_UpdatingClause(CypherParser::OC_UpdatingClauseContext *ctx, UpdatingClause **uc_ptr);

    // Reading CLauses
	antlrcpp::Any visitOC_Match(CypherParser::OC_MatchContext *ctx, Match *match);

    antlrcpp::Any visitOC_Unwind(CypherParser::OC_UnwindContext *ctx, Unwind *unwind);

    antlrcpp::Any visitOC_InQueryCall(CypherParser::OC_InQueryCallContext *ctx, InQueryCall *iq_call); 

    // Updating Clauses
    antlrcpp::Any visitOC_Create(CypherParser::OC_CreateContext *ctx, Create *create);
    
    antlrcpp::Any visitOC_Merge(CypherParser::OC_MergeContext *ctx, Merge *merge);

    antlrcpp::Any visitOC_Delete(CypherParser::OC_DeleteContext *ctx, Delete *del);

    antlrcpp::Any visitOC_Set(CypherParser::OC_SetContext *ctx, Set *s);

    antlrcpp::Any visitOC_Remove(CypherParser::OC_RemoveContext *ctx, Remove *remove);


    antlrcpp::Any visitOC_SetItem(CypherParser::OC_SetItemContext *ctx, SetItem *set_item); 

    antlrcpp::Any visitOC_PropertyExpression(CypherParser::OC_PropertyExpressionContext *ctx, PropertyExpression* prop_exp);

    antlrcpp::Any visitOC_RemoveItem(CypherParser::OC_RemoveItemContext *ctx, RemoveItem *remove_item); 

    antlrcpp::Any visitOC_ExplicitProcedureInvocation(CypherParser::OC_ExplicitProcedureInvocationContext *ctx, InQueryCall *iq_call);

    antlrcpp::Any visitOC_ImplicitProcedureInvocation(CypherParser::OC_ImplicitProcedureInvocationContext *ctx, InQueryCall *iq_call);

    antlrcpp::Any visitOC_YieldItems(CypherParser::OC_YieldItemsContext *ctx, InQueryCall *iq_call);

	antlrcpp::Any visitOC_Pattern(CypherParser::OC_PatternContext *ctx, Pattern *pattern); 

	antlrcpp::Any visitOC_PatternPart(CypherParser::OC_PatternPartContext *ctx, PatternPart *pattern_part);

	antlrcpp::Any visitOC_PatternElement(CypherParser::OC_PatternElementContext *ctx, PatternPart *pattern_part);

	antlrcpp::Any visitOC_NodePattern(CypherParser::OC_NodePatternContext *ctx, NodePattern *node_pattern);

    antlrcpp::Any visitOC_Properties(CypherParser::OC_PropertiesContext *ctx, Properties *prop);

	antlrcpp::Any visitOC_PatternElementChain(CypherParser::OC_PatternElementChainContext *ctx, PatternPart *pattern_part);

    antlrcpp::Any visitOC_RelationshipPattern(CypherParser::OC_RelationshipPatternContext *ctx, RelationshipPattern * rela_pattern);

    antlrcpp::Any visitOC_RelationshipDetail(CypherParser::OC_RelationshipDetailContext *ctx, RelationshipPattern * rela_pattern);

    antlrcpp::Any visitOC_RelationshipTypes(CypherParser::OC_RelationshipTypesContext *ctx, RelationshipPattern * rela_pattern);

    antlrcpp::Any visitOC_RangeLiteral(CypherParser::OC_RangeLiteralContext *ctx, RelationshipPattern *rela_pattern);
	
    // 以下为尤其繁琐的表达式相关
    antlrcpp::Any visitOC_Expression(CypherParser::OC_ExpressionContext *ctx, Expression *exp);

    antlrcpp::Any visitOC_OrExpression(CypherParser::OC_OrExpressionContext *ctx, Expression *exp);

    antlrcpp::Any visitOC_XorExpression(CypherParser::OC_XorExpressionContext *ctx, Expression *exp);

    antlrcpp::Any visitOC_AndExpression(CypherParser::OC_AndExpressionContext *ctx, Expression *exp);

    antlrcpp::Any visitOC_NotExpression(CypherParser::OC_NotExpressionContext *ctx, Expression *exp);

    antlrcpp::Any visitOC_ComparisonExpression(CypherParser::OC_ComparisonExpressionContext *ctx, Expression *exp);


    antlrcpp::Any visitOC_StringListNullPredicateExpression(CypherParser::OC_StringListNullPredicateExpressionContext *ctx, Expression *exp);

    antlrcpp::Any visitOC_AddOrSubtractExpression(CypherParser::OC_AddOrSubtractExpressionContext *ctx, Expression *exp); 

    antlrcpp::Any visitOC_MultiplyDivideModuloExpression(CypherParser::OC_MultiplyDivideModuloExpressionContext *ctx, Expression *exp);
    
    antlrcpp::Any visitOC_PowerOfExpression(CypherParser::OC_PowerOfExpressionContext *ctx, Expression *exp);
    
    antlrcpp::Any visitOC_UnaryAddOrSubtractExpression(CypherParser::OC_UnaryAddOrSubtractExpressionContext *ctx, Expression *exp);

    antlrcpp::Any visitOC_ListOperatorExpression(CypherParser::OC_ListOperatorExpressionContext *ctx, Expression *exp);

    antlrcpp::Any visitOC_PropertyOrLabelsExpression(CypherParser::OC_PropertyOrLabelsExpressionContext *ctx, Expression *exp);

    // 以上是Atom之前的表达式部分 
    antlrcpp::Any visitOC_Atom(CypherParser::OC_AtomContext *ctx, Atom **atom);
    
    antlrcpp::Any visitOC_Literal(CypherParser::OC_LiteralContext *ctx, Literal *literal);

    antlrcpp::Any visitOC_Parameter(CypherParser::OC_ParameterContext *ctx, Parameter *param); 

    
    antlrcpp::Any visitOC_CaseExpression(CypherParser::OC_CaseExpressionContext *ctx, CaseExpression *case_exp);

    antlrcpp::Any visitOC_ListComprehension(CypherParser::OC_ListComprehensionContext *ctx, ListComprehension *list_cpr);

    antlrcpp::Any visitOC_PatternComprehension(CypherParser::OC_PatternComprehensionContext *ctx, PatternComprehension *pat_cpr);
	
    antlrcpp::Any visitOC_Quantifier(CypherParser::OC_QuantifierContext *ctx, Quantifier *qntf);

    antlrcpp::Any visitOC_PatternPredicate(CypherParser::OC_PatternPredicateContext *ctx, PatternPredicate *ptn_pdc);
    
    antlrcpp::Any visitOC_ParenthesizedExpression(CypherParser::OC_ParenthesizedExpressionContext *ctx, ParenthesizedExpression *par_exp);

    antlrcpp::Any visitOC_FunctionInvocation(CypherParser::OC_FunctionInvocationContext *ctx, FunctionInvocation *func_ivoc);

    antlrcpp::Any visitOC_ExistentialSubquery(CypherParser::OC_ExistentialSubqueryContext *ctx, ExistentialSubquery *sub_query);
    
    
    antlrcpp::Any visitOC_Variable(CypherParser::OC_VariableContext *ctx, Variable *var);
    // Atom部分结束

    antlrcpp::Any visitOC_RelationshipsPattern(CypherParser::OC_RelationshipsPatternContext *ctx, PatternPart *pattern_part); 

    // WITH RETURN
    antlrcpp::Any visitOC_With(CypherParser::OC_WithContext *ctx, WithReturn *with);

    antlrcpp::Any visitOC_Return(CypherParser::OC_ReturnContext *ctx, WithReturn *ret);
    
    antlrcpp::Any visitOC_ProjectionBody(CypherParser::OC_ProjectionBodyContext *ctx, WithReturn *wr);
    
    // Standalone Call
    antlrcpp::Any visitOC_StandaloneCall(CypherParser::OC_StandaloneCallContext *ctx, QueryTree *qt);

    void printNode(antlr4::ParserRuleContext *ctx, const char *nodeTypeName);
	void printTree(antlr4::tree::ParseTree *root, int dep);
};

/**
	Listener for errors during Cypher query parsing, which throws a 
	corresponding exception when an error arises.
*/
class CypherErrorListener: public antlr4::BaseErrorListener
{
public:
	void syntaxError(antlr4::Recognizer *recognizer, antlr4::Token * offendingSymbol, \
		size_t line, size_t charPositionInLine, const std::string &msg, std::exception_ptr e);
};