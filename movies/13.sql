SELECT name FROM people, movies, stars WHERE movies.id = stars.movie_id AND stars.person_id = people.id AND movies.id IN (SELECT movies.id from people, movies, stars WHERE movies.id = stars.movie_id AND stars.person_id = people.id AND name = "Kevin Bacon" AND birth = "1958") AND NOT people.name = "Kevin Bacon";