## 
'''
curl -i -s -X PUT "localhost:54321/users/1" \
  -H "Content-Type: application/json" 
  -d '{"username":"john_doe_updated","email":"john.updated@example.com","age":26,"active":true}'
'''
## Use python requests to perform the same operation
import requests

url = "http://localhost:54321/users/1"
headers = {"Content-Type": "application/json"}
data = {
    "username": "john_doe_updated",
    "email": "john.updated@example.com",
    "age": 26,
    "active": True
}

response = requests.put(url, headers=headers, json=data)
print(response.status_code)
print(response.json())
