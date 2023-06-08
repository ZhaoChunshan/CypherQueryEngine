MATCH (n:Person)-[r:KNOWS]->(m:Person)
MATCH (d:DOG)
RETURN n, m, r, d.age