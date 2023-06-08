UNWIND [{ name: "Bob", score: 10}, {name: "Alice", score: 100}, { name: "Bob", score: 120}] AS dict
WITH dict["name"] AS name, dict["score"] AS score
RETURN name, sum(score) as totalScore