MATCH (p:Product)
WHERE p.name = "p-5"
OPTIONAL MATCH (p)<-[:OFFERS]-(s)
WITH p, count(s) AS supplyerNum
OPTIONAL MATCH (p)<-[:ORDERED]-(u)
RETURN p.name, supplyerNum, count(u) AS buyerNum
