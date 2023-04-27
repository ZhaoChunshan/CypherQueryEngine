#include <typeinfo>
#include "antlr4-runtime.h"
#include "CypherLexer.h"
#include "CypherParser.h"
#include "CypherBaseVisitor.h"
#include "CypherAST.h"
#include "Pattern.h"
#include <unordered_map>
#include <unordered_set>
#include <map>


class CypherSymbol{
public:
    enum VarType {NODE_VAR, EDGE_VAR, PATH_VAR, VALUE_VAR};
    VarType var_ty_;
    unsigned var_id_;
    CypherSymbol(){}
    CypherSymbol(VarType vty):var_ty_(vty){}
    CypherSymbol(unsigned var_id):var_id_(var_id){}
    CypherSymbol(VarType vty, unsigned var_id):var_ty_(vty), var_id_(var_id){}
};

class SymbolTableStack{
public:
    std::vector<std::string> id2string_;
    std::unordered_map<std::string, unsigned> prop2id_;
    // dont map 0xffffffff to any string
    std::map<unsigned, std::string> prop_id2string_;
    // the prop_name string must already in database.
    std::vector<std::unordered_map<std::string, CypherSymbol>> symbol_tb_st_;
    unsigned next_var_id_, next_anno_id_, next_prop_id_;
public:
    SymbolTableStack(){reset();}
    bool exists(const std::string & var) const;
    CypherSymbol& search(const std::string & var) ;
    void insert(const std::string& var_name, const CypherSymbol& sym);
    void insert(const std::string& var_name, CypherSymbol::VarType var_ty, unsigned var_id);
    void clearExcept(const std::vector<std::string> & remain_var);
    void clear();
    void push();
    void pop();
    void reset();
    unsigned getNextVarId();
    std::string getAnnoName();
    void putString(const std::string& str) { id2string_.emplace_back(str); }
    std::vector<unsigned> getAllVarId();
    std::vector<unsigned> getAllNamedVarId();
    const std::vector<std::string>& getIdToString(){return id2string_;}
    unsigned getPropId(const std::string &prop);
};

/**
 * @brief Parser for Cypher queries, inherited from CypherBaseVisitor, which is
 * automatically generated from the Cypher grammar by ANTLR. Implements
 * visiting important grammatical units, extracts relevant information,
 * and stores in CypherAST (pointed to by cypher_ast_).
 * @warning var id will be save, and we have a id=>string map
 * @warning property name , property id will be save, we have map between them; For an undate clause, a property name may dont have prop id in PStore.
 * @warning label, type only save name, dont have id now.
*/
class PCypherParser: public CypherBaseVisitor
{
private:
    SymbolTableStack sym_tb_;
public:
	PCypherParser(){}

	CypherAST* CypherParse(const std::string &query);	// Overall driver function
    CypherAST* CypherParse(std::istream& in);

    const std::vector<std::string>& getIdToString(){
        return sym_tb_.getIdToString();
    }
private:

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
