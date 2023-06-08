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
+ 不支持对pattern命名，如p = ((a)-[]-(c))

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
```cpp
    std::shared_ptr<PGeneralEvaluation> ge = std::make_shared<PGeneralEvaluation>( ... );
    ge->ParseCypherQuery(query);
    ge->GenerateLogicalPlan();
    ge->DoQuery();
    ge->temp_result_->print();
```

## Attention
Where will we access KVstore ?
+ Parser: encode property key name to its id.
+ Calculator: Check existence of Labels && Get node/edge properties.
+ GeneralEvaluation: Of course GE will access KVStore, see CREATE, DELETE, SET, REMOVE, etc.

Moreover, remember to call Optimizer/Executor in BGP of GE.

## Questions
+ How can I get all labels of a node? `getObjlListBysubIDpreID` don't tell me #label returned.
+ 