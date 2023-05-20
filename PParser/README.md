# PParser
解析Cypher查询，生成抽象语法树CypherAST。抽象语法树的节点是各种各样的Clause。
支持所有的查询语句与更新语句（Merge除外）。表达式部分，基本都支持，除了
+ PatternComprehension 
+ Quantifier
+ ExistentialSubquery

## Usage

```cpp
PCypherParser parser;
std::unique_ptr<CypherAST> ast;
for(query : queries){
    ast.reset(parser.CypherParse(query, pstore));
    // do something
}

```
