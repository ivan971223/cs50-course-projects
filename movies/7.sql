SELECT title, rating FROM movies, ratings WHERE movies.id = ratings.movie_id AND movie_id IN (SELECT id from movies WHERE year = "2010");