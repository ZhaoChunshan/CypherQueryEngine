UNWIND [{ name: "Bob", score: 10}, {name: "Alice", score: 100}, { name: "Bob", score: 120}] AS dict
RETURN dict["name"] AS name, dict["score"] AS score
ORDER BY name