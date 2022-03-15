import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
import datetime
from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    symbols = db.execute(
        "SELECT symbol, SUM(shares) AS sum_shares FROM transactions WHERE user_id = ? GROUP BY symbol", session["user_id"])
    cash = db.execute("SELECT cash FROM users WHERE id = ?",
                      session["user_id"])
    cash = cash[0]["cash"]
    total = 0
    for symbol in symbols:
        if symbol["sum_shares"] == 0:
            symbols.remove(symbol)
        qdict = lookup(symbol["symbol"])
        symbol["price"] = format(qdict["price"], '.2f')
        symbol["total"] = format(symbol["sum_shares"]*qdict["price"], '.2f')
        symbol["name"] = qdict["name"]
        total += float(symbol["total"])
    total += cash
    return render_template("index.html", symbols=symbols, cash=format(cash, '.2f'), total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        if not request.form.get("shares") or not request.form.get("symbol"):
            return apology("Missing input")
        try:
            shares = float(request.form.get("shares"))
        except:
            return apology("Invalid number of shares")

        if shares < 1 or not shares.is_integer():
            return apology("Invalid number of shares")

        symbol = request.form.get("symbol").upper()
        qdict = lookup(symbol)
        if symbol is None or not qdict:
            return apology("Invalid symbol")
        print(symbol)
        price = int(qdict["price"])
        rows = db.execute(
            "SELECT cash FROM users WHERE id = ?", session["user_id"])
        cash = rows[0]["cash"]
        date = datetime.datetime.now()
        if float(cash) < (price*shares):
            return apology("Not enough cash")
        else:
            shares = int(shares)
            db.execute("INSERT INTO transactions (user_id, date, symbol, price, shares) VALUES(?,?,?,?,?)",
                       session["user_id"], date, symbol, price, shares)
            cash -= price * shares
            db.execute("UPDATE users SET cash = ? WHERE id = ?",
                       cash, session["user_id"])
            return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transactions = db.execute(
        "SELECT * FROM transactions WHERE user_id = ? ORDER BY date DESC", session["user_id"])
    for transaction in transactions:
        qdict = lookup(transaction["symbol"])
        transaction["name"] = qdict["name"]
        transaction["total"] = int(transaction["shares"])*qdict["price"]

    return render_template("history.html", transactions=transactions)


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


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        if not request.form.get("symbol") or not lookup(request.form.get("symbol")):
            return apology("Missing Input")
        quote = request.form.get("symbol")
        qdict = lookup(quote)
        price = "{:.2f}".format(qdict["price"])
        return render_template("quoted.html", name=qdict["name"], price=price, symbol=qdict["symbol"])
    else:
        return render_template("quote.html")


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


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        if not request.form.get("shares") or not request.form.get("symbol"):
            return apology("Missing input")
        try:
            shares = float(request.form.get("shares"))
        except:
            return apology("Invalid number of shares")

        if shares < 1 or not float(shares).is_integer():
            return apology("Invalid number of shares")

        symbol = request.form.get("symbol").upper()
        shares = int(request.form.get("shares"))
        porfolio = db.execute(
            "SELECT symbol, SUM(shares) AS sum_shares FROM transactions WHERE user_id = ? GROUP BY ?", session["user_id"], symbol)
        qdict = lookup(symbol)

        if symbol is None or not qdict:
            return apology("Invalid symbol")
        if not porfolio:
            return apology("You do not own any share")
        elif porfolio[0]["sum_shares"] < shares:
            return apology("You do not own enough share")

        price = qdict["price"]
        rows = db.execute(
            "SELECT cash FROM users WHERE id = ?", session["user_id"])
        cash = rows[0]["cash"]
        date = datetime.datetime.now()

        shares = int(shares)
        db.execute("INSERT INTO transactions (user_id, date, symbol, price, shares) VALUES(?,?,?,?,?)",
                   session["user_id"], date, symbol, price, -shares)
        cash += price * shares
        db.execute("UPDATE users SET cash = ? WHERE id = ?",
                   cash, session["user_id"])
        return redirect("/")
    else:
        symbols = db.execute(
            "SELECT symbol, SUM(shares) AS sum_shares FROM transactions WHERE user_id = ? GROUP BY symbol", session["user_id"])
        for symbol in symbols:
            if symbol["sum_shares"] == 0:
                symbols.remove(symbol)
        return render_template("sell.html", symbols=symbols)
