# PQuery
完成查询层算子设计，从抽象语法树生成执行树；
完成中间结果表设计，遍历执行树获得查询结果。
暂未实现的功能：
+ Merge语句
+ 最短路径求解shortestPath, allShortestPaths
+ 存储调用过程CALL
+ 高级表达式，如
  + PatternComprehension
  + Quantifier
  + ExistentialSubquery
  + ListComprehension
  + PatternPredicate
+ 

## Usage

### Generate Plan Tree For A Query
```cpp
    PCypherParser parser;
    std::unique_ptr<CypherAST> ast;
    std::unique_ptr<PTreeNode> plan;.
    ast.reset( parser.CypherParse(query, param, nullptr));
    plan.reset(PQueryTree::GenerateQueryTree(ast.get()));
    plan.print();
```

### Execute A Query
To be implemented.
