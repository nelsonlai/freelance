"""
Beginner Example 3: Extract and Clean Text Content
==================================================

This example demonstrates:
- How to extract text from HTML elements
- How to clean and format text
- How to extract specific content (paragraphs, lists, etc.)
"""

import requests
from bs4 import BeautifulSoup
import re

def clean_text(text):
    """
    Clean text by removing extra whitespace and newlines.
    
    Args:
        text: Raw text string
        
    Returns:
        Cleaned text string
    """
    if not text:
        return ""
    
    # Remove extra whitespace
    text = re.sub(r'\s+', ' ', text)
    # Remove leading/trailing whitespace
    text = text.strip()
    return text

def extract_text_content(url):
    """
    Extract various text elements from a webpage.
    
    Args:
        url: The URL of the webpage to scrape
    """
    try:
        print(f"Fetching: {url}")
        # Add headers to mimic a real browser (some websites require this)
        headers = {
            'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.124 Safari/537.36'
        }
        response = requests.get(url, headers=headers, timeout=10)
        response.raise_for_status()
        
        soup = BeautifulSoup(response.text, 'html.parser')
        
        # Remove script and style elements (they don't contain visible text)
        for script in soup(["script", "style", "meta", "link"]):
            script.decompose()
        
        # Extract different types of content
        results = {}
        
        # 1. Page title
        title = soup.find('title')
        results['title'] = clean_text(title.text) if title else "No title found"
        
        # 2. Main heading (h1)
        h1 = soup.find('h1')
        results['main_heading'] = clean_text(h1.text) if h1 else "No h1 found"
        
        # 3. All paragraphs
        paragraphs = soup.find_all('p')
        results['paragraphs'] = [clean_text(p.text) for p in paragraphs if clean_text(p.text)]
        
        # 4. All headings (h1-h6)
        headings = soup.find_all(['h1', 'h2', 'h3', 'h4', 'h5', 'h6'])
        results['headings'] = [
            {'level': h.name, 'text': clean_text(h.text)} 
            for h in headings
        ]
        
        # 5. List items
        list_items = soup.find_all(['li'])
        results['list_items'] = [clean_text(li.text) for li in list_items if clean_text(li.text)]
        
        # 6. All text (combined)
        all_text = soup.get_text()
        results['all_text'] = clean_text(all_text)
        
        # Display results
        print("\n" + "="*60)
        print("TEXT EXTRACTION RESULTS")
        print("="*60)
        
        print(f"\n📄 Title:")
        print(f"  {results['title']}")
        
        print(f"\n📝 Main Heading (h1):")
        print(f"  {results['main_heading']}")
        
        print(f"\n📑 Headings ({len(results['headings'])} found):")
        for heading in results['headings'][:10]:  # Show first 10
            print(f"  {heading['level'].upper()}: {heading['text']}")
        if len(results['headings']) > 10:
            print(f"  ... and {len(results['headings']) - 10} more")
        
        print(f"\n📄 Paragraphs ({len(results['paragraphs'])} found):")
        for i, para in enumerate(results['paragraphs'][:3], 1):  # Show first 3
            print(f"  {i}. {para[:100]}..." if len(para) > 100 else f"  {i}. {para}")
        if len(results['paragraphs']) > 3:
            print(f"  ... and {len(results['paragraphs']) - 3} more paragraphs")
        
        print(f"\n📋 List Items ({len(results['list_items'])} found):")
        for i, item in enumerate(results['list_items'][:5], 1):  # Show first 5
            print(f"  {i}. {item[:80]}..." if len(item) > 80 else f"  {i}. {item}")
        if len(results['list_items']) > 5:
            print(f"  ... and {len(results['list_items']) - 5} more items")
        
        print(f"\n📊 Statistics:")
        print(f"  Total characters: {len(results['all_text'])}")
        print(f"  Total words: {len(results['all_text'].split())}")
        print(f"  Total paragraphs: {len(results['paragraphs'])}")
        
        return results
        
    except requests.exceptions.RequestException as e:
        print(f"❌ Error fetching the page: {e}")
        return None
    except Exception as e:
        print(f"❌ An error occurred: {e}")
        return None


if __name__ == "__main__":
    # Example: Extract text from a Wikipedia article
    url = "https://en.wikipedia.org/wiki/Python_(programming_language)"
    results = extract_text_content(url)
    
    print("\n" + "="*60)
    print("Example completed!")
    print("="*60)

