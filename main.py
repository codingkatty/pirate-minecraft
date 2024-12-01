from flask import Flask, jsonify, request
import subprocess

app = Flask(__name__)

@app.route('/generate', methods=['GET'])
def generate():
    seed = request.args.get("seed", "0")
    try:
        # Execute the C program with the seed as input
        result = subprocess.run(
            ["./pirate_map", seed],
            capture_output=True,
            text=True
        )
        if result.returncode != 0:
            return {"error": "Failed to generate map data"}, 500
        return result.stdout, 200, {'Content-Type': 'application/json'}
    except Exception as e:
        return {"error": str(e)}, 500

if __name__ == "__main__":
    app.run(debug=True)
