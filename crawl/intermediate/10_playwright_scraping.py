"""
Intermediate Playwright Example 3: Web Scraping with Playwright
=================================================================

This example demonstrates:
- Scraping JavaScript-rendered content
- Handling infinite scroll
- Extracting data efficiently
- Handling dynamic content
"""

from playwright.sync_api import sync_playwright
import json
import csv
import time

def scrape_javascript_content():
    """Scrape content from JavaScript-rendered pages."""
    with sync_playwright() as p:
        print("="*60)
        print("SCRAPING JAVASCRIPT CONTENT")
        print("="*60)
        
        browser = p.chromium.launch(headless=True)
        page = browser.new_page()
        
        url = "https://quotes.toscrape.com/js/"
        page.goto(url)
        page.wait_for_load_state('networkidle')
        
        print(f"\n1. Opened: {url}")
        
        # Extract quotes (loaded by JavaScript)
        quotes = page.locator('.quote').all()
        print(f"2. Found {len(quotes)} quotes")
        
        data = []
        for quote in quotes:
            text = quote.locator('.text').text_content()
            author = quote.locator('.author').text_content()
            tags = quote.locator('.tag').all_text_contents()
            
            data.append({
                'text': text,
                'author': author,
                'tags': ', '.join(tags)
            })
        
        # Display sample
        if data:
            print("\n3. Sample data:")
            for i, item in enumerate(data[:3], 1):
                print(f"\n   {i}. {item['text'][:50]}...")
                print(f"      Author: {item['author']}")
                print(f"      Tags: {item['tags']}")
        
        browser.close()
        return data


def scrape_infinite_scroll():
    """Handle infinite scroll pages."""
    with sync_playwright() as p:
        print("\n" + "="*60)
        print("INFINITE SCROLL SCRAPING")
        print("="*60)
        
        browser = p.chromium.launch(headless=True)
        page = browser.new_page()
        
        url = "https://quotes.toscrape.com/scroll"
        page.goto(url)
        page.wait_for_load_state('networkidle')
        
        print(f"\n1. Opened: {url}")
        
        # Get initial count
        quotes = page.locator('.quote').all()
        initial_count = len(quotes)
        print(f"   Initial quotes: {initial_count}")
        
        # Scroll and load more
        last_count = initial_count
        scroll_attempts = 0
        max_scrolls = 5
        
        while scroll_attempts < max_scrolls:
            # Scroll to bottom
            page.evaluate("window.scrollTo(0, document.body.scrollHeight)")
            time.sleep(2)  # Wait for new content
            
            # Check for new content
            quotes = page.locator('.quote').all()
            current_count = len(quotes)
            
            if current_count > last_count:
                print(f"   Scroll {scroll_attempts + 1}: Loaded {current_count - last_count} more quotes (total: {current_count})")
                last_count = current_count
            else:
                print(f"   Scroll {scroll_attempts + 1}: No new content")
                break
            
            scroll_attempts += 1
        
        print(f"\n2. ✅ Final quote count: {last_count}")
        print(f"   Total scrolls: {scroll_attempts}")
        
        browser.close()
        return last_count


def scrape_multiple_pages():
    """Scrape multiple pages of content."""
    with sync_playwright() as p:
        print("\n" + "="*60)
        print("MULTI-PAGE SCRAPING")
        print("="*60)
        
        browser = p.chromium.launch(headless=True)
        page = browser.new_page()
        
        base_url = "https://quotes.toscrape.com/"
        all_quotes = []
        max_pages = 3
        
        print(f"\n1. Scraping up to {max_pages} pages...")
        
        current_url = base_url
        page_num = 1
        
        while page_num <= max_pages:
            page.goto(current_url)
            page.wait_for_load_state('networkidle')
            
            print(f"\n   Page {page_num}: {current_url}")
            
            # Extract quotes
            quote_elements = page.locator('.quote').all()
            
            if len(quote_elements) == 0:
                print("   No quotes found, stopping")
                break
            
            for quote in quote_elements:
                text = quote.locator('.text').text_content()
                author = quote.locator('.author').text_content()
                tags = quote.locator('.tag').all_text_contents()
                
                all_quotes.append({
                    'page': page_num,
                    'text': text,
                    'author': author,
                    'tags': ', '.join(tags)
                })
            
            print(f"   Found {len(quote_elements)} quotes on page {page_num}")
            
            # Try to go to next page
            next_button = page.get_by_text('Next', exact=False).first
            if not next_button.is_visible():
                print("   No next page, stopping")
                break
            
            next_button.click()
            page.wait_for_load_state('networkidle')
            current_url = page.url
            page_num += 1
        
        print(f"\n2. ✅ Scraped {len(all_quotes)} quotes from {page_num - 1} page(s)")
        
        browser.close()
        return all_quotes


def save_scraped_data(data, format='json'):
    """Save scraped data to file."""
    if not data:
        print("No data to save")
        return
    
    if format == 'json':
        filename = 'quotes_playwright.json'
        with open(filename, 'w', encoding='utf-8') as f:
            json.dump(data, f, indent=2, ensure_ascii=False)
        print(f"\n✅ Saved {len(data)} items to {filename}")
    
    elif format == 'csv':
        filename = 'quotes_playwright.csv'
        keys = data[0].keys()
        with open(filename, 'w', newline='', encoding='utf-8') as f:
            writer = csv.DictWriter(f, fieldnames=keys)
            writer.writeheader()
            writer.writerows(data)
        print(f"✅ Saved {len(data)} items to {filename}")


if __name__ == "__main__":
    # Example 1: Scrape JavaScript content
    js_data = scrape_javascript_content()
    
    # Example 2: Infinite scroll
    scroll_count = scrape_infinite_scroll()
    
    # Example 3: Multi-page scraping
    multi_page_data = scrape_multiple_pages()
    
    # Save data
    if multi_page_data:
        save_scraped_data(multi_page_data, 'json')
        save_scraped_data(multi_page_data, 'csv')
    
    print("\n" + "="*60)
    print("All scraping examples completed!")
    print("="*60)
    print("\n💡 Key points:")
    print("  - Playwright handles JavaScript automatically")
    print("  - Use wait_for_load_state() for reliable scraping")
    print("  - Infinite scroll can be handled with scrolling")
    print("  - Pagination is straightforward with element clicks")
