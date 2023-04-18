Cypher中的Value类型：
PropertyType: INTEGER, FLOAT, STRING, BOOLEAN, IntegerArray, floatArray, stringArray, booleanArray, ByteArray
StructuralType: NODE RELATIONSHIP PATH
CompositeType: List MAP
NULL

Value：可以考虑列同质时的优化
Expression: 要支持覆盖变量集合，覆盖属性集合；最好还能支持结点复用、优化；叶子节点与内部结点信息分开存


+ Value.[h|cpp]: 只负责基本的Value的包装、存储，实现orderability, equivalence，求哈希值
+ Expression.[h|cpp]: 负责表达式树AST设计
+ Calculator.[h|cpp]: 负责在表达式树上计算，对表达式树（或其子树）的计算结果是Value