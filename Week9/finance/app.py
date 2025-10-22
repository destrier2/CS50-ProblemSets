import os
import re

from cs50 import SQL
from datetime import datetime
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd #Helps to format values as USD

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False #no cookies
app.config["SESSION_TYPE"] = "filesystem" #use filesystem
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


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
	purchases = db.execute("SELECT symbol, SUM(amount) AS amount FROM transactions WHERE user_id=? GROUP BY symbol", session["user_id"])
	updatedPurchases = []
	balance = db.execute("SELECT cash FROM users WHERE id=?", session["user_id"])[0]["cash"]
	total = balance
	for row in purchases:
		cost = lookup(row["symbol"])["price"]
		total += cost*row["amount"]
		updatedPurchases.append({
			"symbol": row["symbol"],
			"amount": row["amount"],
			"price": cost,
			"value": cost*row["amount"]
		})
	username = db.execute("SELECT username FROM users WHERE id=?", session["user_id"])[0]["username"]
	return render_template("index.html", username=username, balance=balance, total=total, purchases=updatedPurchases)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
	"""Buy shares of stock"""
	if request.method == "POST":
		symbol = request.form.get("symbol")
		checkSymbol = lookup(symbol)
		if checkSymbol == None:
			return apology("Please ensure you enter a valid symbol")
		shares = request.form.get("shares")
		if not bool(re.fullmatch(r'\d+', shares)):
			flash("Please ensure you enter a valid number of shares.")
			return apology("oops")
		elif int(shares) <= 0 or not shares or int(shares) != shares:
			flash("Please ensure you enter a positive number of shares")
			return apology("oops")
		#assume that if they get this far, everything is correct
		cost = checkSymbol["price"]
		user = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
		if not user:
			flash(f"An error occured. User {session["user_id"]} can't find cash")
		else: 
		#error: compare a float to float
			cash = user[0]["cash"]
			if float(cash) < (float(cost)*float(shares)):
				flash(f"You do not have enough money to buy {shares} shares of {checkSymbol["symbol"]}")
				return render_template("buy.html")
			else:
				cash -= float(cost)*float(shares)
				db.execute("INSERT INTO transactions (user_id, username, symbol, price, amount, timestamp) VALUES (?, ?, ?, ?, ?, ?)", session["user_id"], user[0]["username"], symbol.upper(), float(cost)*float(shares), shares, datetime.now())
				db.execute("UPDATE users SET cash = ? WHERE id = ?", cash, session["user_id"])
				
				flash(f"You successfully purchased {int(shares)} shares of {checkSymbol["name"]} ({checkSymbol["symbol"]}) for ${round(float(cost)*float(shares), 2)}. You now have ${round(cash,2)} remaining in your account.")
		return redirect("/")
	return render_template("buy.html")


@app.route("/history")
@login_required
def history():
	"""Show history of transactions"""
	actions = db.execute("SELECT * FROM transactions")
	if not actions or len(actions) == 0:
		flash("There are no transactions in your history.")
	else:
		newactions=[]
		flash("Hi")
		for row in actions:
			if (row["amount"] < 0):
				buysell = "Sell"
			else:
				buysell = "Buy"
			newactions.append({
				"symbol": row["symbol"],
				"amount": abs(row["amount"]),
				"price": row["price"],
				"timestamp": row["timestamp"],
				"buysell": buysell
			})
			
		#set buysell to buy or sell
	return render_template("history.html", transactions=newactions)


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
		rows = db.execute(
			"SELECT * FROM users WHERE username = ?", request.form.get("username")
		)

		# Ensure username exists and password is correct
		if len(rows) != 1 or not check_password_hash(
			rows[0]["hash"], request.form.get("password")
		):
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
		symbol = request.form.get("symbol")
		quote=lookup(symbol)
		if (quote == None) or not quote:
			flash("This stock symbol doesn't exist")
			return apology("Oops")
		else:
			return render_template("quoted.html", quote=quote)

	elif request.method == "GET" :
		return render_template("quote.html")
	return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
	"""Register user"""
	if request.method == "POST":
		username = request.form.get("username")
		if not username:
			return apology("Please enter a valid username")
		try:
			password = request.form.get("password")
			if not password or not password == request.form.get("confirmation"):
				return apology("Please ensure you enter a valid password correctly twice")
			db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, generate_password_hash(password))
			flash("Successfully created an account!")
		except:
			return apology("This user already exists")
		return render_template("login.html")
	else:
		return render_template("register.html")
	  


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
	"""Sell shares of stock"""
	
	tempshares = db.execute("SELECT DISTINCT symbol FROM transactions")
	shareslist = []
	for share in tempshares:
		shareslist.append(share["symbol"])
	if request.method == "POST":
		shares = request.form.get("shares")
		symbol = request.form.get("symbol")
		if not shares or not symbol:
			flash("Please ensure you enter a valid share symbol and a valid share amount")
			return apology("You must choose a share")
		if int(shares) <= 0:
			flash("Please ensure you enter a positive number of shares.")
			return apology("Stocks must be a positive integer")
		ownedshares = int(db.execute("SELECT DISTINCT symbol, SUM(amount) as amount FROM transactions WHERE user_id=? AND symbol=? GROUP BY symbol", session["user_id"], symbol)[0]["amount"])
		if (ownedshares) < int(shares):
			flash(f"You do not own {shares} shares of {symbol}")
			return render_template("sell.html", shares=shareslist)
		#get username
		username = db.execute("SELECT username FROM users WHERE id=?", session["user_id"])[0]["username"]
		#get current price
		price = lookup(symbol)["price"]
		#add the transaction to transactions
		db.execute("INSERT INTO transactions (user_id, username, symbol, price, amount, timestamp) VALUES (?, ?, ?, ?, ?, ?)", session["user_id"], username, symbol, price, int(shares)*(-1), datetime.now())
		db.execute("UPDATE users SET cash=cash+? WHERE id=?", price, session["user_id"])
		flash(f"Successfully sold {shares} shares of {symbol} for {price*float(shares)}")
		return redirect("/")
	return render_template("sell.html", shares=shareslist)

@app.route("/settings", methods=["GET", "POST"])
@login_required
def settings():
	#View settings --> allow user to change their password
	if request.method == "POST":
		flash("Sucessfully changed password. Please log in again")
		logout()
	return render_template("settings.html")