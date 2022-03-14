import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
import datetime
from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__, static_url_path='/static')

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///shop.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
@login_required
def index():

    if "cart_item" not in session:
        session["cart_item"] = []
    if "cart" not in session:
        session["cart"] = {}

    if request.method == "POST":
        id = request.form.get("id")
        number = int(request.form.get("number"))
        if id and number > 0:
            session["cart_item"].append(id)
            session["cart"][f'{id}'] = number
            foods = db.execute("SELECT id, name, price FROM food")
    elif request.method == "GET":
        foods = db.execute("SELECT id, name, price FROM food")
        return render_template("index.html", foods=foods)


@app.route("/cart", methods=["GET", "POST"])
@login_required
def cart():

    # Ensure cart exists
    if "cart_item" not in session:
        session["cart_item"] = []
    if "cart" not in session:
        session["cart"] = {}

    # POST
    if request.method == "POST":
        id = request.form.get("id")
        try:
            number = int(request.form.get("number"))
        except:
            number = 0
        action = request.form.get("action")
        if action == "delete":
            session["cart_item"].remove(id)
            session["cart"].pop(f"{id}")
            return redirect("/cart")

    # GET
    foods = db.execute("SELECT * FROM food WHERE id in (?)",
                       session["cart_item"])
    index = 0
    total = 0
    for food in foods:
        food["number"] = session["cart"][f'{food["id"]}']
        total += food["price"]*food["number"]
        food["price"] = usd(food["price"])
        index += 1
    total = total
    return render_template("cart.html", foods=foods, total=total, is_added=False)


@app.route("/order", methods=["GET", "POST"])
@login_required
def order():
    if request.method == "POST":
        total = float(request.form.get("total"))
        if total > 0:
            for food_id in session["cart"].keys():
                food_id = food_id
                number = session["cart"][f"{food_id}"]
                order_date = (datetime.datetime.now() + datetime.timedelta(hours=8)).strftime("%Y/%m/%d %H:%M:%S")
                total = total
                row = db.execute("SELECT name FROM food WHERE id = ?", food_id)
                name = row[0]["name"]
                db.execute("INSERT INTO orders (orderDate, user_id, food_id, name, number, total) VALUES(?,?,?,?,?,?)",
                           order_date, session["user_id"], food_id, name, number, total)
            session["cart"] = {}
            session["cart_item"] = []
            return redirect("/order")

    orders = db.execute(
        "SELECT * FROM orders WHERE user_id = ? GROUP BY orderDate ORDER BY orderDate Desc", session["user_id"])
    for order in orders:
        rows = db.execute(
            "SELECT name, number FROM orders WHERE user_id = ? and orderDate = ?", session["user_id"], order["orderDate"])
        description = ""
        for row in rows:
            name = row["name"]
            number = row["number"]
            description += f"{name}*{number}, "
        order["description"] = description[:-2]
    return render_template("order.html", orders=orders)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        if not request.form.get("username") or not request.form.get("password") or not request.form.get("confirmation"):
            return apology("Missing Input")
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        hash_password = generate_password_hash(password)
        user = db.execute("SELECT * FROM users WHERE username = ?", username)
        if user:
            return apology("Username is invalid")
        elif confirmation != password:
            return apology("Password is invalid")

        db.execute("INSERT INTO users (username, hash) VALUES(?,?)",
                   username, hash_password)
        return render_template("login.html")
    else:
        return render_template("register.html")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?",
                          request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")
