# CypherQueryEngine
A cypher query engine for propery graph database.


## Usage

### Execute A Query
```cpp
    std::shared_ptr<PGeneralEvaluation> ge = std::make_shared<PGeneralEvaluation>( ... );
    ge->ParseCypherQuery(query);
    ge->GenerateLogicalPlan();
    ge->DoQuery();
    ge->temp_result_->print();
```

### Generate Plan Tree For A Query
```cpp
    PCypherParser parser;
    std::unique_ptr<CypherAST> ast;
    std::unique_ptr<PTreeNode> plan;.
    ast.reset( parser.CypherParse(query, param, nullptr));
    plan.reset(PQueryTree::GenerateQueryTree(ast.get()));
    plan.print();
```

## Warning
Pattern Matching && Storage engine is NOT included in our work.

