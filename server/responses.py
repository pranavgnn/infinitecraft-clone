from flask import Response
import json

bad_argument_response = None
illegal_argument_response = None
process_fail = None

def init():
    
    global bad_argument_response, illegal_argument_response, process_fail

    bad_argument_response = Response(json.dumps({
        "status": 400,
        "message": "Bad argument(s) provided"
    }), status=400, mimetype="application/json")

    illegal_argument_response = Response(json.dumps({
        "status": 403,
        "message": "Illegal argument(s) provided"
    }), status=403, mimetype="application/json")

    process_fail = Response(json.dumps({
        "status": 500,
        "message": "Internal server error"
    }), status=500, mimetype="application/json")