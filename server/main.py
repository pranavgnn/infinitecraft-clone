from dotenv import load_dotenv
load_dotenv()

from flask import Flask, request, jsonify
from database import Database
from request import craft as ai_craft
import responses

app = Flask(__name__)
database = Database()

with app.app_context():
    responses.init()

@app.route("/craft", methods=["GET"])
def craft():
    item1 = request.args.get("item1")
    item2 = request.args.get("item2")

    if type(item1) != str or type(item2) != str:
        return responses.bad_argument_response

    if not database.check(item1) or not database.check(item2):
        return responses.illegal_argument_response
    
    crafted_result = ai_craft(item1, item2, database)

    if not crafted_result:
        return responses.process_fail

    return jsonify(crafted_result)


if __name__ == "__main__":
    app.run(debug=False)