#include <typeinfo>
#include "antlr4-runtime.h"
#include "CypherLexer.h"
#include "CypherParser.h"
#include "CypherBaseVisitor.h"
#include "../PQuery/PQueryTree.h"
#include "../PQuery/Pattern.h"
#include <unordered_map>
#include <unordered_set>
/**
	Parser for Cypher queries, inherited from CypherBaseVisitor, which is
	automatically generated from the Cypher grammar by ANTLR. Implements
	visiting important grammatical units, extracts relevant information,
	and stores in QueryTree (pointed to by query_tree_ptr).
*/
class PCypherParser: public CypherBaseVisitor
{
private:
	PQueryTree *query_tree_ptr_;
    unsigned nextVarId;     // 下个变量名
    unsigned nextAnnoId;    // 下个匿名变量号
    /* VarInfo: 类型检查、查询改写等用途；指向当前变量名描述的NodePattern或EdgePattern，以后再次出现此变量，相关label，prop写入其中 */
    struct VarInfo{
        enum VarType {NODE_VAR, EDGE_VAR, PATH_VAR, VALUE_VAR};
        VarType var_ty_;
        unsigned var_id_;
    };
    /* 每个变量名到变量信息的映射，类似于符号表 */
    std::unordered_map<std::string, VarInfo> var_info_;

public:
	PCypherParser():nextVarId(0), nextAnnoId(0) {query_tree_ptr_ = nullptr;}
	PCypherParser(PQueryTree *query_tree_ptr): query_tree_ptr_(query_tree_ptr),nextVarId(0), nextAnnoId(0) {}
	void setQueryTree(PQueryTree *query_tree_ptr) { 
        query_tree_ptr_ = query_tree_ptr; 
        nextVarId = nextAnnoId = 0;
        var_info_.clear();}
	void CypherParse(const std::string &query);	// Overall driver function
    void CypherParse(std::istream& in);

private:
    std::string getNextAnno();
    unsigned getNextId();
    /**
     * @brief 进入下一个With块，刷新变量命名。nextVarId置为0，nextAnnoId不变，清空var_info，插入with_vars_
    */
    void resetNextWith(const std::vector<std::string> &with_vars_);

    antlrcpp::Any visitOC_Query(CypherParser::OC_QueryContext *ctx);
    antlrcpp::Any visitOC_RegularQuery(CypherParser::OC_RegularQueryContext *ctx);
    antlrcpp::Any visitOC_StandaloneCall(CypherParser::OC_StandaloneCallContext *ctx);
    antlrcpp::Any visitOC_SingleQuery(CypherParser::OC_SingleQueryContext *ctx);
    antlrcpp::Any visitOC_SinglePartQuery(CypherParser::OC_SinglePartQueryContext *ctx);
    antlrcpp::Any visitOC_MultiPartQuery(CypherParser::OC_MultiPartQueryContext *ctx);

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

