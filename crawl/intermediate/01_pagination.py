"""
Intermediate Example 1: Handling Pagination
===========================================

This example demonstrates:
- How to scrape multiple pages
- How to detect and follow pagination links
- How to collect data from all pages
"""

import requests
from bs4 import BeautifulSoup
import time
from urllib.parse import urljoin, urlparse

def scrape_paginated_content(base_url, max_pages=10):
    """
    Scrape content from multiple pages.
    
    Args:
        base_url: The first page URL
        max_pages: Maximum number of pages to scrape
    """
    all_data = []
    current_url = base_url
    page_num = 1
    
    # Headers to mimic a real browser
    headers = {
        'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36'
    }
    
    while page_num <= max_pages and current_url:
        try:
            print(f"Scraping page {page_num}: {current_url}")
            
            response = requests.get(current_url, headers=headers, timeout=10)
            response.raise_for_status()
            
            soup = BeautifulSoup(response.text, 'html.parser')
            
            # Extract data from current page (example: quotes from quotes.toscrape.com)
            # Adjust selectors based on the website you're scraping
            items = soup.find_all('div', class_='quote')
            
            if not items:
                print("No items found on this page. Stopping.")
                break
            
            page_data = []
            for item in items:
                # Extract quote text
                text_elem = item.find('span', class_='text')
                text = text_elem.text.strip() if text_elem else "N/A"
                
                # Extract author
                author_elem = item.find('small', class_='author')
                author = author_elem.text.strip() if author_elem else "N/A"
                
                # Extract tags
                tags = [tag.text for tag in item.find_all('a', class_='tag')]
                
                page_data.append({
                    'page': page_num,
                    'text': text,
                    'author': author,
                    'tags': ', '.join(tags)
                })
            
            all_data.extend(page_data)
            print(f"  Found {len(page_data)} items on page {page_num}")
            
            # Find next page link
            next_link = soup.find('li', class_='next')
            if next_link and next_link.find('a'):
                next_url = next_link.find('a')['href']
                current_url = urljoin(base_url, next_url)
                page_num += 1
            else:
                print("No next page found. Reached end.")
                break
            
            # Be respectful: add a delay between requests
            time.sleep(1)
            
        except requests.exceptions.RequestException as e:
            print(f"❌ Error on page {page_num}: {e}")
            break
        except Exception as e:
            print(f"❌ Unexpected error on page {page_num}: {e}")
            break
    
    return all_data


def save_to_csv(data, filename='scraped_data.csv'):
    """Save scraped data to CSV file."""
    import csv
    
    if not data:
        print("No data to save.")
        return
    
    keys = data[0].keys()
    with open(filename, 'w', newline='', encoding='utf-8') as f:
        writer = csv.DictWriter(f, fieldnames=keys)
        writer.writeheader()
        writer.writerows(data)
    
    print(f"\n✅ Data saved to {filename}")


if __name__ == "__main__":
    # Example: Scrape quotes from quotes.toscrape.com
    # This is a demo site designed for scraping practice
    base_url = "http://quotes.toscrape.com/"
    
    print("="*60)
    print("PAGINATION SCRAPING EXAMPLE")
    print("="*60)
    print(f"\nScraping from: {base_url}")
    print("Maximum pages: 5\n")
    
    data = scrape_paginated_content(base_url, max_pages=10)
    
    print("\n" + "="*60)
    print("SCRAPING SUMMARY")
    print("="*60)
    print(f"Total items scraped: {len(data)}")
    
    if data:
        print(f"\nSample data (first 3 items):")
        for i, item in enumerate(data[:3], 1):
            print(f"\n{i}. {item['text'][:50]}...")
            print(f"   Author: {item['author']}")
            print(f"   Tags: {item['tags']}")
        
        # Save to CSV
        save_to_csv(data, 'quotes_scraped.csv')
    
    print("\n" + "="*60)
    print("Example completed!")
    print("="*60)

