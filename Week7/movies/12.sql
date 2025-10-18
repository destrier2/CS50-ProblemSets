/*In 12.sql, write a SQL query to list the titles of all movies in which both Bradley Cooper and Jennifer Lawrence starred.
Your query should output a table with a single column for the title of each movie.
You may assume that there is only one person in the database with the name Bradley Cooper.
You may assume that there is only one person in the database with the name Jennifer Lawrence.
*/
--SELECT title FROM movies JOIN stars ON stars.movie_id = movies.id WHERE stars.
SELECT DISTINCT title FROM movies JOIN stars ON movies.id = stars.movie_id WHERE (
    movies.id IN (
        SELECT movie_id FROM stars WHERE person_id IN (
            SELECT id FROM people WHERE name = 'Jennifer Lawrence'
        )
    ) AND movies.id IN (
        SELECT movie_id FROM stars WHERE person_id IN (
            SELECT id FROM people WHERE name = 'Bradley Cooper'
        )
    )
);