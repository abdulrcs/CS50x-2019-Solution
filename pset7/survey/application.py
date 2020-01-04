import cs50
import csv

from flask import Flask, jsonify, redirect, render_template, request

# Configure application
app = Flask(__name__)

# Reload templates when they are changed
app.config["TEMPLATES_AUTO_RELOAD"] = True


@app.after_request
def after_request(response):
    """Disable caching"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET"])
def get_index():
    return redirect("/form")


@app.route("/form", methods=["GET"])
def get_form():
    return render_template("form.html")


@app.route("/form", methods=["POST"])
def post_form():
    if not request.form.get("name"):
        return render_template("error.html", message="You need input the data correctly!")
    with open("survey.csv", "a") as file:
        writer = csv.DictWriter(file, fieldnames=["name", "house", "role"])
        writer.writerow({"name": request.form.get("name"), "house": request.form.get("house"), "role": request.form.get("role")})
    return render_template("success.html")


@app.route("/sheet")
def get_sheet():
    with open("survey.csv", "r") as file:
        reader = csv.DictReader(file)
        survey = list(reader)
    return render_template("sheet.html", survey=survey)