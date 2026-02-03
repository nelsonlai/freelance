"""
Beginner Example 1: Basic Web Scraping
======================================

This example demonstrates:
- How to make a simple HTTP request
- How to check if the request was successful
- How to view the HTML content of a webpage
"""

import requests
import json
from bs4 import BeautifulSoup

# Step 1: Make a request to a website
# We'll use httpbin.org which is a simple HTTP request & response service
url = "https://httpbin.org/html"

print("Making request to:", url)
# Note: Some websites require a User-Agent header to prevent blocking
# For this example (httpbin.org), it's optional, but good practice to include
headers = {
    'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.124 Safari/537.36'
}
response = requests.get(url, headers=headers)

# pretty print the response
# print(json.dumps(response.json(), indent=4))

# Step 2: Check if the request was successful
# Status code 200 means success
print(f"Status Code: {response.status_code}")

if response.status_code == 200:
    print("✅ Request successful!")
    
    # Step 3: View the raw HTML content
    print("\n" + "="*50)
    print("Raw HTML Content (first 500 characters):")
    print("="*50)
    print(response.text)
    
    # Step 4: Parse the HTML with BeautifulSoup
    soup = BeautifulSoup(response.text, 'html.parser')
    
    # Step 5: Extract the title
    title = soup.find('title')
    if title:
        print("\n" + "="*50)
        print("Page Title:")
        print("="*50)
        print(title.text)
    
    # Step 6: Extract all headings
    headings = soup.find_all(['h1', 'h2', 'h3'])
    print("\n" + "="*50)
    print("Headings found:")
    print("="*50)
    for heading in headings:
        print(f"- {heading.name}: {heading.text.strip()}")

    # Step 7: Extract all paragraph
    paragraphs = soup.find_all('p')
    print("\n" + "="*50)
    print("Paragraphs found:")
    print("="*50)
    for paragraph in paragraphs:
        print(f"- {paragraph.text.strip()}")
        
else:
    print("❌ Request failed!")
    print(f"Error: {response.status_code}")

print("\n" + "="*50)
print("Example completed!")
print("="*50)

