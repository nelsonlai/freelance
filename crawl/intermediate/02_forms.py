"""
Intermediate Example 2: Handling Forms and POST Requests
==========================================================

This example demonstrates:
- How to submit forms using POST requests
- How to handle search forms
- How to extract data from form responses
"""

import requests
from bs4 import BeautifulSoup
import time

def submit_search_form(search_url, search_query):
    """
    Submit a search form and extract results.
    
    Args:
        search_url: URL of the search page
        search_query: The search term
    """
    headers = {
        'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36'
    }
    
    try:
        # First, get the search page to see the form structure
        print(f"Loading search page: {search_url}")
        response = requests.get(search_url, headers=headers, timeout=10)
        response.raise_for_status()
        
        soup = BeautifulSoup(response.text, 'html.parser')
        
        # Find the search form
        form = soup.find('form')
        if not form:
            print("No form found on the page")
            return None
        
        # Determine form action and method
        form_action = form.get('action', '')
        form_method = form.get('method', 'get').lower()
        
        # Build the full URL for form submission
        if form_action.startswith('http'):
            submit_url = form_action
        else:
            from urllib.parse import urljoin
            submit_url = urljoin(search_url, form_action)
        
        # Find input fields
        inputs = form.find_all(['input', 'select', 'textarea'])
        form_data = {}
        
        for inp in inputs:
            name = inp.get('name')
            if name:
                input_type = inp.get('type', 'text').lower()
                
                if input_type == 'text' or input_type == 'search':
                    # For text inputs, use our search query
                    if 'search' in name.lower() or 'q' in name.lower():
                        form_data[name] = search_query
                    else:
                        form_data[name] = inp.get('value', '')
                elif input_type == 'hidden':
                    form_data[name] = inp.get('value', '')
                elif input_type == 'submit':
                    # Some forms need the submit button value
                    if inp.get('name'):
                        form_data[inp.get('name')] = inp.get('value', '')
        
        print(f"\nSubmitting search for: '{search_query}'")
        print(f"Form method: {form_method}")
        print(f"Submit URL: {submit_url}")
        
        # Submit the form
        if form_method == 'post':
            response = requests.post(submit_url, data=form_data, headers=headers, timeout=10)
        else:
            response = requests.get(submit_url, params=form_data, headers=headers, timeout=10)
        
        response.raise_for_status()
        
        # Parse results
        soup = BeautifulSoup(response.text, 'html.parser')
        
        # Extract search results (adjust selectors based on the website)
        results = []
        
        # Example: For quotes.toscrape.com search
        quote_divs = soup.find_all('div', class_='quote')
        
        for quote in quote_divs:
            text_elem = quote.find('span', class_='text')
            author_elem = quote.find('small', class_='author')
            
            if text_elem and author_elem:
                results.append({
                    'text': text_elem.text.strip(),
                    'author': author_elem.text.strip()
                })
        
        return results
        
    except requests.exceptions.RequestException as e:
        print(f"❌ Error: {e}")
        return None
    except Exception as e:
        print(f"❌ Unexpected error: {e}")
        return None


def simple_search_example():
    """
    A simpler example using a site with a known search form.
    This example uses httpbin.org to demonstrate POST requests.
    """
    print("\n" + "="*60)
    print("SIMPLE POST REQUEST EXAMPLE")
    print("="*60)
    
    # Example: Submit form data to httpbin.org
    url = "https://httpbin.org/post"
    
    form_data = {
        'search_query': 'Python programming',
        'category': 'technology',
        'sort': 'relevance'
    }
    
    headers = {
        'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36'
    }
    
    print(f"\nSubmitting POST request to: {url}")
    print(f"Form data: {form_data}")
    
    response = requests.post(url, data=form_data, headers=headers)
    
    if response.status_code == 200:
        result = response.json()
        print("\n✅ Request successful!")
        print(f"\nServer received form data:")
        print(f"  {result.get('form', {})}")
    else:
        print(f"❌ Request failed with status: {response.status_code}")


if __name__ == "__main__":
    print("="*60)
    print("FORM HANDLING EXAMPLE")
    print("="*60)
    
    # Example 1: Simple POST request
    simple_search_example()
    
    # Example 2: Search on quotes.toscrape.com
    print("\n" + "="*60)
    print("SEARCH FORM EXAMPLE")
    print("="*60)
    
    search_url = "http://quotes.toscrape.com/search.aspx"
    search_query = "change"
    
    results = submit_search_form(search_url, search_query)
    
    if results:
        print(f"\n✅ Found {len(results)} results:")
        for i, result in enumerate(results[:5], 1):  # Show first 5
            print(f"\n{i}. {result['text'][:60]}...")
            print(f"   - {result['author']}")
    else:
        print("\nNo results found or error occurred.")
    
    print("\n" + "="*60)
    print("Example completed!")
    print("="*60)

