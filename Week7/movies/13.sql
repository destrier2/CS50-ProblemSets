/*In 13.sql, write a SQL query to list the names of all people who starred in a movie in which Kevin Bacon also starred.
Your query should output a table with a single column for the name of each person.
There may be multiple people named Kevin Bacon in the database. Be sure to only select the Kevin Bacon born in 1958.
Kevin Bacon himself should not be included in the resulting list.*/

--Get a list of all movies in which Kevin Bacon starred
--Then take that list and search it for all the other names of people
SELECT DISTINCT name FROM people WHERE id IN (
	SELECT person_id FROM stars JOIN movies ON movies.id = stars.movie_id WHERE movies.id IN (
		SELECT movies.id FROM movies JOIN stars ON movies.id = stars.movie_id WHERE stars.person_id IN(
			--Get Kevin Bacon's id
			SELECT id FROM people WHERE name = 'Kevin Bacon' AND birth = 1958
		)
	)
) AND NOT id = (
	SELECT id FROM people WHERE name = 'Kevin Bacon' AND birth = 1958
);