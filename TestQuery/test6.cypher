MATCH (n:Person)
WHERE n.age > 20
CREATE (n)-[:HAS]->(d:Dog {age:n.age}), (n)-[:HAS]->(c:Cat {age:n.age}), (d)-[:KNOWS]->(c)
