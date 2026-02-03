"""
Beginner Example 2: Extract Links from a Webpage
=================================================

This example demonstrates:
- How to find all links on a webpage
- How to extract href attributes
- How to filter and categorize links
"""

import requests
from bs4 import BeautifulSoup
from urllib.parse import urljoin, urlparse

def extract_links(url):
    """
    Extract all links from a webpage and categorize them.
    
    Args:
        url: The URL of the webpage to scrape
    """
    try:
        # Make the request
        print(f"Fetching: {url}")
        # Add headers to mimic a real browser (some websites require this)
        headers = {
            'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.124 Safari/537.36'
        }
        response = requests.get(url, headers=headers, timeout=10)
        response.raise_for_status()  # Raises an error for bad status codes
        
        # Parse the HTML
        soup = BeautifulSoup(response.text, 'html.parser')
        
        # Find all anchor tags (<a>)
        links = soup.find_all('a', href=True)
        
        print(f"\nFound {len(links)} links on the page\n")
        
        # Categorize links
        internal_links = []
        external_links = []
        absolute_urls = []
        relative_urls = []
        
        base_domain = urlparse(url).netloc
        
        for link in links:
            href = link.get('href', '')
            link_text = link.text.strip()
            
            # Convert relative URLs to absolute URLs
            absolute_url = urljoin(url, href)
            
            # Categorize
            if href.startswith('http://') or href.startswith('https://'):
                absolute_urls.append(absolute_url)
                if urlparse(absolute_url).netloc == base_domain:
                    internal_links.append(absolute_url)
                else:
                    external_links.append(absolute_url)
            else:
                relative_urls.append(href)
        
        # Display results
        print("="*60)
        print("LINK ANALYSIS")
        print("="*60)
        
        print(f"\n📊 Summary:")
        print(f"  Total links: {len(links)}")
        print(f"  Internal links: {len(internal_links)}")
        print(f"  External links: {len(external_links)}")
        print(f"  Absolute URLs: {len(absolute_urls)}")
        print(f"  Relative URLs: {len(relative_urls)}")
        
        print(f"\n🔗 Sample Internal Links (first 5):")
        for i, link in enumerate(internal_links[:5], 1):
            print(f"  {i}. {link}")
        
        print(f"\n🌐 Sample External Links (first 5):")
        for i, link in enumerate(external_links[:5], 1):
            print(f"  {i}. {link}")
        
        return {
            'all_links': links,
            'internal': internal_links,
            'external': external_links,
            'absolute': absolute_urls,
            'relative': relative_urls
        }
        
    except requests.exceptions.RequestException as e:
        print(f"❌ Error fetching the page: {e}")
        return None
    except Exception as e:
        print(f"❌ An error occurred: {e}")
        return None


if __name__ == "__main__":
    # Example: Extract links from Python.org
    url = "https://www.python.org"
    results = extract_links(url)
    
    print("\n" + "="*60)
    print("Example completed!")
    print("="*60)

