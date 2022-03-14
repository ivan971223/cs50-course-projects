import cs50
import csv

open("shop.db","w").close()
db = cs50.SQL("sqlite:///shop.db")

db.execute("CREATE TABLE users (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, username TEXT NOT NULL, hash TEXT NOT NULL, cash NUMERIC NOT NULL DEFAULT 1000.00)")
db.execute("CREATE TABLE food (id INTEGER, name TEXT NOT NULL, price REAL NOT NULL, PRIMARY KEY(id))")
db.execute("CREATE TABLE order (id INTEGER, user_id INTEGER NOT NULL, orderDate NUMERIC NOT NULL, food_id INTEGER NOT NULL, number INTEGER NOT NULL, total REAL NOT NULL, FOREIGN KEY(user_id) REFERENCES users(id), FOREIGN KEY(food_id) REFERENCES food(id))")

with open("shop.csv", "r", encoding='utf-8-sig') as file:
    reader = csv.DictReader(file)
    for row in reader:
        print(row)
        name = row["name"]
        price = row["price"]
        db.execute("INSERT INTO food (name, price) VALUES(?,?)", name, price)