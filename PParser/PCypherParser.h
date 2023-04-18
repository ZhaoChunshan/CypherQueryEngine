#include <typeinfo>
#include "antlr4-runtime.h"
#include "CypherLexer.h"
#include "CypherParser.h"
#include "CypherBaseVisitor.h"
#include "CypherAST.h"
#include "Pattern.h"
#include <unordered_map>
#include <unordered_set>
/**
	Parser for Cypher queries, inherited from CypherBaseVisitor, which is
	automatically generated from the Cypher grammar by ANTLR. Implements
	visiting important grammatical units, extracts relevant information,
	and stores in CypherAST (pointed to by cypher_ast_).
*/
class PCypherParser: public CypherBaseVisitor
{
public:

    /* VarInfo: 类型检查/命名冲突等 */
    struct VarInfo{
        enum VarType {NODE_VAR, EDGE_VAR, PATH_VAR, VALUE_VAR};
        VarType var_ty_;
        unsigned var_id_;
        VarInfo(){}
        VarInfo(VarType vty, unsigned var_id):var_ty_(vty), var_id_(var_id){}
    };
    /* 每个变量名到变量信息的映射，类似于符号表 */
    std::unordered_map<std::string, VarInfo> var_info_;
private:
    
    /* with、return 块 无编码，其余可编码 */
    unsigned nextVarId, nextAnnoId;
    

public:
	PCypherParser(){}

	CypherAST* CypherParse(const std::string &query);	// Overall driver function
    CypherAST* CypherParse(std::istream& in);
private:

    /**
     * @brief 分配一个变量的id
    */
    unsigned getNextVarId();
    std::pair<unsigned, std::string> getAnnoIdAndName();
    bool existsVar(const std::string& var_name);
    VarInfo& searchVar(const std::string &var_name);
    void insertVar(const std::string& var_name, unsigned var_id, VarInfo::VarType ty);

    /* helper functions */
    static long parseIntegerLiteral(const std::string &s);
    static double parseDoubleLiteral(const std::string &s);
    static std::string parseStringLiteral(const std::string &s);
    
    antlrcpp::Any visitOC_Cypher(CypherParser::OC_CypherContext *ctx);
    antlrcpp::Any visitOC_RegularQuery(CypherParser::OC_RegularQueryContext *ctx);
    antlrcpp::Any visitOC_StandaloneCall(CypherParser::OC_StandaloneCallContext *ctx);
    antlrcpp::Any visitOC_SingleQuery(CypherParser::OC_SingleQueryContext *ctx);
    antlrcpp::Any visitOC_SinglePartQuery(CypherParser::OC_SinglePartQueryContext *ctx);
    antlrcpp::Any visitOC_MultiPartQuery(CypherParser::OC_MultiPartQueryContext *ctx);

    antlrcpp::Any visitOC_ReadingClause(CypherParser::OC_ReadingClauseContext *ctx);
    antlrcpp::Any visitOC_UpdatingClause(CypherParser::OC_UpdatingClauseContext *ctx);

    antlrcpp::Any visitOC_Match(CypherParser::OC_MatchContext *ctx);
    antlrcpp::Any visitOC_Unwind(CypherParser::OC_UnwindContext *ctx);
    antlrcpp::Any visitOC_InQueryCall(CypherParser::OC_InQueryCallContext *ctx);

    antlrcpp::Any visitOC_Create(CypherParser::OC_CreateContext *ctx);
    antlrcpp::Any visitOC_Set(CypherParser::OC_SetContext *ctx);
    antlrcpp::Any visitOC_Delete(CypherParser::OC_DeleteContext *ctx);
    antlrcpp::Any visitOC_Remove(CypherParser::OC_RemoveContext *ctx);
    antlrcpp::Any visitOC_Merge(CypherParser::OC_MergeContext *ctx);

    antlrcpp::Any visitOC_With(CypherParser::OC_WithContext *ctx);
    antlrcpp::Any visitOC_Return(CypherParser::OC_ReturnContext *ctx);
    antlrcpp::Any visitOC_ProjectionBody(CypherParser::OC_ProjectionBodyContext *ctx, bool is_with) ;

    /* Pattern */

    antlrcpp::Any visitOC_PatternPart(CypherParser::OC_PatternPartContext *ctx);
    antlrcpp::Any visitOC_NodePattern(CypherParser::OC_NodePatternContext *ctx);
    antlrcpp::Any visitOC_RelationshipPattern(CypherParser::OC_RelationshipPatternContext *ctx);
    antlrcpp::Any visitOC_RangeLiteral(CypherParser::OC_RangeLiteralContext *ctx);
    antlrcpp::Any visitOC_PatternElement(CypherParser::OC_PatternElementContext *ctx);

    /* Expression */

    antlrcpp::Any visitOC_Expression(CypherParser::OC_ExpressionContext *ctx);
    antlrcpp::Any visitOC_OrExpression(CypherParser::OC_OrExpressionContext *ctx);
    antlrcpp::Any visitOC_XorExpression(CypherParser::OC_XorExpressionContext *ctx);
    antlrcpp::Any visitOC_AndExpression(CypherParser::OC_AndExpressionContext *ctx) ;
    antlrcpp::Any visitOC_NotExpression(CypherParser::OC_NotExpressionContext *ctx);
    antlrcpp::Any visitOC_ComparisonExpression(CypherParser::OC_ComparisonExpressionContext *ctx);
    antlrcpp::Any visitOC_StringListNullPredicateExpression(CypherParser::OC_StringListNullPredicateExpressionContext *ctx);
    antlrcpp::Any visitOC_AddOrSubtractExpression(CypherParser::OC_AddOrSubtractExpressionContext *ctx) ;
    antlrcpp::Any visitOC_MultiplyDivideModuloExpression(CypherParser::OC_MultiplyDivideModuloExpressionContext *ctx);
    antlrcpp::Any visitOC_PowerOfExpression(CypherParser::OC_PowerOfExpressionContext *ctx);
    antlrcpp::Any visitOC_UnaryAddOrSubtractExpression(CypherParser::OC_UnaryAddOrSubtractExpressionContext *ctx);
    antlrcpp::Any visitOC_ListOperatorExpression(CypherParser::OC_ListOperatorExpressionContext *ctx) ;
    antlrcpp::Any visitOC_PropertyOrLabelsExpression(CypherParser::OC_PropertyOrLabelsExpressionContext *ctx);
    
    antlrcpp::Any visitOC_Atom(CypherParser::OC_AtomContext *ctx);
    
    antlrcpp::Any visitOC_Literal(CypherParser::OC_LiteralContext *ctx);
    antlrcpp::Any visitOC_Parameter(CypherParser::OC_ParameterContext *ctx);
    antlrcpp::Any visitOC_Variable(CypherParser::OC_VariableContext *ctx);
    antlrcpp::Any visitOC_CaseExpression(CypherParser::OC_CaseExpressionContext *ctx);
    antlrcpp::Any visitOC_ListComprehension(CypherParser::OC_ListComprehensionContext *ctx) ;
    antlrcpp::Any visitOC_PatternComprehension(CypherParser::OC_PatternComprehensionContext *ctx);
    antlrcpp::Any visitOC_Quantifier(CypherParser::OC_QuantifierContext *ctx);
    antlrcpp::Any visitOC_PatternPredicate(CypherParser::OC_PatternPredicateContext *ctx);
    antlrcpp::Any visitOC_FunctionInvocation(CypherParser::OC_FunctionInvocationContext *ctx);
    antlrcpp::Any visitOC_ExistentialSubquery(CypherParser::OC_ExistentialSubqueryContext *ctx);
    antlrcpp::Any visitOC_ParenthesizedExpression(CypherParser::OC_ParenthesizedExpressionContext *ctx) ;    
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

