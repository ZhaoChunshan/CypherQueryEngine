MATCH (p1)<-[:ORDERED]-(u1)-[:ORDERED]->(p2),
      (p3)<-[:ORDERED]-(u1)-[:ORDERED]->(p4),
      (p1)<-[:ORDERED]-(u2)-[:ORDERED]->(p2),
      (p3)<-[:ORDERED]-(u2)-[:ORDERED]->(p4),
      (p1)<-[:ORDERED]-(u3)-[:ORDERED]->(p2),
      (u3)-[:ORDERED]->(p3)
WHERE u1 <> u2 AND u1 <> u3 AND u2 <> u3 AND
      p1 <> p2 AND p1 <> p3 AND p1 <> p4 AND
      p2 <> p3 AND p2 <> p4 AND p3 <> p4 AND
      NOT (u3)-[:ORDERED]->(p4)
RETURN DISTINCT u3.uid AS userId, u3.name AS userName,
                p4.pid AS productId, p4.name AS productName

