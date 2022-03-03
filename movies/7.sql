SELECT title FROM movies WHERE year = "2010";
SELECT rating FROM ratings WHERE movie_id in (SELECT id from movies WHERE year = "2010");