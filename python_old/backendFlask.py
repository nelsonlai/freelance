from flask import Flask, request, jsonify

app = Flask(__name__)

CORS(app)  # Enable CORS for frontend access

@app.route('/', methods=['GET'])
def index():
    return "Hello, World!"

@app.route('/api/userinfo', methods=['GET'])
def get_user_info():
    ## Interaction with database
    ## ....
    ## ....
    return jsonify({
        "name": "Nelson Lai",
        "age": 42,
        "email": "nelson@example.com"
    })

# POST: Create user
@app.route('/api/userinfo', methods=['POST'])
def create_user():
    headers = request.headers
    data = request.get_json()
    name = data['name']
    password = data['password']
    ## perform database query
    # Normally, you'd save this to a database
    return jsonify({"message": "User created", "user": data}), 201

# PUT: Update user by ID
@app.route('/api/userinfo/<int:user_id>', methods=['PUT'])
def update_user(user_id):
    userId = user_id
    SQL ... (userId)
    data = request.get_json()
    # Normally, you'd update the user in your database here
    return jsonify({"message": f"User {user_id} updated", "user": data})
    
if __name__ == '__main__':
    app.run(port=5000)
