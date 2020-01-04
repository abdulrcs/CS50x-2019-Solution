import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # Declare a dict to put the SQL into
    portfolio = {}
    # Look up the current user
    users = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"])
    stocks = db.execute(
        "SELECT symbol, SUM(shares) as shares FROM portfolio WHERE user_id = :user_id GROUP BY symbol", user_id=session["user_id"])

    # Update to current price
    for stock in stocks:
        portfolio[stock["symbol"]] = lookup(stock["symbol"])

    # Set a cash
    cash = users[0]["cash"]
    total = cash

    return render_template("index.html", portfolio=portfolio, stocks=stocks, cash=cash, total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        api = lookup(symbol)
        if api == None:
            return apology("invalid symbol", 400)
        try:
            shares = int(request.form.get("shares"))
        except:
            return apology("Shares must be a valid number", 400)
        if shares < 1:
            return apology("Shares can't be less than one", 400)
        price = float(api.get("price"))
        rows = db.execute("SELECT cash FROM users WHERE id = :ids", ids=session["user_id"])
        cash = rows[0]["cash"]
        if cash > (price * shares):
            db.execute("UPDATE users SET cash = cash - :total WHERE id = :ids", total=(shares * price), ids=session["user_id"])
            db.execute("INSERT INTO portfolio (user_id, symbol, price, shares) VALUES(:ids, :symbol, :price, :shares)",
                       ids=session["user_id"], symbol=symbol, shares=shares, price=price)
        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/check", methods=["GET"])
def check():
    """Return true if username available, else false, in JSON format"""

    # Set name equals to the username from the form
    name = request.args.get("username")
    # Call a database of all the username
    username = db.execute("SELECT username FROM users")

    # If the length of characters is less than one return false
    if len(name) < 1:
        return jsonify(False)
    else:
        # Check if the username already in the database
        for user in username:
            if user["username"] == name:
                return jsonify(False)

    return jsonify(True)


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    history = db.execute(
        "SELECT symbol, shares, price, date FROM portfolio WHERE user_id = :user_id ORDER BY date ASC", user_id=session["user_id"])

    return render_template("history.html", history=history)


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
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]
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
        # Ensure username was submitted
        if not request.form.get("symbol"):
            return apology("must provide symbol", 400)

        # Ensure password was submitted
        elif not lookup(request.form.get("symbol")):
            return apology("symbol doesn't exist", 400)
        api = lookup(request.form.get("symbol"))
        return render_template("symbol.html", name=api.get("name"), price=api.get("price"), symbol=api.get("symbol"))
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Ensure password confirmation
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("Password do not match", 400)

        # Query database for username
        result = db.execute("INSERT INTO users (username, hash) VALUES(:username, :hash)", username=request.form.get(
            "username"), hash=generate_password_hash(request.form.get("password")))
        if not result:
            return apology("username already exist", 400)
        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))
        session["user_id"] = rows[0]["id"]
        return redirect("/quote")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    if request.method == "POST":

        symbol = request.form.get("symbol")
        if not symbol:
            return apology("must provide symbol", 400)
        try:
            shares = int(request.form.get("shares"))
        except:
            return apology("Shares must be a valid number", 400)
        # Check database for number of shares
        stock = db.execute("SELECT SUM(shares) as total FROM portfolio WHERE user_id = :user_id AND symbol = :symbol GROUP BY symbol",
                           user_id=session["user_id"], symbol=request.form.get("symbol"))
        # If the shares in the database is less than "shares" then show an error
        if stock[0]["total"] < shares:
            return apology("You don't have enough shares", 400)
        api = lookup(symbol)
        price = float(api.get("price"))
        db.execute("UPDATE users SET cash = cash + :total WHERE id = :ids", total=(shares * price), ids=session["user_id"])
        db.execute("INSERT INTO portfolio (user_id, symbol, price, shares) VALUES(:ids, :symbol, :price, :shares)",
                   ids=session["user_id"], symbol=symbol, shares=-shares, price=price)
        return redirect("/")

    else:
        stocks = db.execute("SELECT symbol FROM portfolio WHERE user_id = :user_id", user_id=session["user_id"])
        return render_template("sell.html", stocks=stocks)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)