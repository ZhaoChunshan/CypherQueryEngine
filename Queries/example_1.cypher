CREATE (u1:User {uid: 60, name:"FlyPig"}),
       (u2:User {uid: 125, name:"Cata"}),
       (u3:User {uid: 129, name:"Ferry"}),
       (p1:Product {pid: 20, name:"p-1"}),
       (p2:Product {pid: 21, name:"p-2"}),
       (p3:Product {pid: 22, name:"p-3"}),
       (p4:Product {pid: 23, name:"p-4"}),
       (p5:Product {pid: 24, name:"p-5"}),
       (s1:Shop {sid: 10, name:"cStore"}),
       (s2:Shop {pid: 12, name:"gMall"}),
       (u1)-[:ORDERED]->(p1),
       (u1)-[:ORDERED]->(p2),
       (u1)-[:ORDERED]->(p3),
       (u1)-[:ORDERED]->(p4),
       (u2)-[:ORDERED]->(p1),
       (u2)-[:ORDERED]->(p2),
       (u2)-[:ORDERED]->(p3),
       (u2)-[:ORDERED]->(p4),
       (u3)-[:ORDERED]->(p1),
       (u3)-[:ORDERED]->(p2),
       (u3)-[:ORDERED]->(p3),
       (s1)-[:OFFERS]->(p1),
       (s1)-[:OFFERS]->(p2),
       (s2)-[:OFFERS]->(p3),
       (s2)-[:OFFERS]->(p4),
       (s2)-[:OFFERS]->(p5)


