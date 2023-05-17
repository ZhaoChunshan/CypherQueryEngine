MATCH (p:Product)
WHERE p.name = "p-5"
OPTIONAL MATCH (p)<-[:OFFERS]-(s)
WITH p, count(s) AS supplierNum
OPTIONAL MATCH (p)<-[:ORDERED]-(u)
RETURN p.name, supplierNum, count(u) AS buyerNum
