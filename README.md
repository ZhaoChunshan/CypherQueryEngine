# CypherQueryEngine
A cypher query engine for propery graph database.

g++ -o CypherQueryEngine  PParser/Cypher/CypherBaseListener.cpp PParser/Cypher/CypherBaseVisitor.cpp PParser/Cypher/CypherLexer.cpp PParser/Cypher/CypherListener.cpp PParser/Cypher/CypherParser.cpp PParser/Cypher/CypherVisitor.cpp PParser/Pattern.cpp PParser/CypherAST.cpp PParser/PCypherParser.cpp Value/Value.cpp  Value/Expression.cpp  PQuery/Varset.cpp test.cpp PParser/Cypher/CypherBaseListener.cpp -I PParser -I PQuery -I Value -I Tools/antlr4-cpp-runtime-4/runtime/src -I PParser/Cypher -L Tools/libantlr4-runtime.a