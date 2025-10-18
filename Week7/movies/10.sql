/*In 10.sql, write a SQL query to list the names of all people who have directed a movie that received a rating of at least 9.0.
Your query should output a table with a single column for the name of each person.
If a person directed more than one movie that received a rating of at least 9.0, they should only appear in your results once.*/
/*
One query for the movie id for all ratings over 9
One query for all the stars and person ids within that movie 
One query for all the names 
*/
SELECT DISTINCT name FROM people WHERE id IN (
    SELECT person_id FROM directors JOIN movies ON movies.id = directors.movie_id WHERE movies.id IN (
        SELECT movies.id FROM ratings JOIN movies ON movies.id = ratings.movie_id WHERE ratings.rating >= 9.0
    )
);