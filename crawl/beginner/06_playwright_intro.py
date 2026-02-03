"""
Beginner Playwright Example 1: Introduction to Playwright
=========================================================

This example demonstrates:
- How to install and set up Playwright
- Basic browser automation
- Navigating pages
- Finding and interacting with elements
"""

from playwright.sync_api import sync_playwright
import time

def basic_playwright_example():
    """Basic example: Open a page and extract information."""
    with sync_playwright() as p:
        print("="*60)
        print("BASIC PLAYWRIGHT EXAMPLE")
        print("="*60)
        
        # Launch browser (default is Chromium)
        print("\n1. Launching browser...")
        browser = p.chromium.launch(headless=False)  # headless=False to see the browser
        # For headless: browser = p.chromium.launch(headless=True)
        
        # Create a new page (tab)
        page = browser.new_page()
        
        # Navigate to a webpage
        url = "https://quotes.toscrape.com/"
        print(f"2. Navigating to: {url}")
        page.goto(url)
        
        # Wait for page to load
        page.wait_for_load_state('networkidle')
        
        # Get page title
        title = page.title()
        print(f"   Page title: {title}")
        
        # Get page URL
        current_url = page.url
        print(f"   Current URL: {current_url}")
        
        # Find elements
        print("\n3. Finding elements:")
        
        # Find by text
        quotes = page.locator('.quote').all()
        print(f"   Found {len(quotes)} quotes on the page")
        
        # Get text from element
        if quotes:
            first_quote_text = page.locator('.quote').first.locator('.text').text_content()
            first_quote_author = page.locator('.quote').first.locator('.author').text_content()
            
            print(f"\n4. First quote:")
            print(f"   Text: {first_quote_text}")
            print(f"   Author: {first_quote_author}")
        
        # Find all links
        links = page.locator('a').all()
        print(f"\n5. Found {len(links)} links on the page")
        
        # Close browser
        browser.close()
        print("\n6. ✅ Browser closed")


def finding_elements_example():
    """Demonstrate different ways to find elements with Playwright."""
    with sync_playwright() as p:
        print("\n" + "="*60)
        print("FINDING ELEMENTS EXAMPLE")
        print("="*60)
        
        browser = p.chromium.launch(headless=False)
        page = browser.new_page()
        
        url = "https://quotes.toscrape.com/"
        page.goto(url)
        page.wait_for_load_state('networkidle')
        
        print("\nDifferent ways to find elements:")
        
        # 1. CSS selector
        quotes = page.locator('.quote').all()
        print(f"   1. ✅ Found {len(quotes)} elements by CSS selector '.quote'")
        
        # 2. ID selector
        try:
            header = page.locator('#header')
            if header.is_visible():
                print(f"   2. ✅ Found element by ID '#header'")
        except:
            print(f"   2. ⚠️  Element with ID 'header' not found")
        
        # 3. Text content
        try:
            next_link = page.get_by_text('Next')
            if next_link.is_visible():
                print(f"   3. ✅ Found link by text 'Next'")
        except:
            print(f"   3. ⚠️  Link with text 'Next' not found")
        
        # 4. Role-based locator (accessibility)
        try:
            links = page.get_by_role('link').all()
            print(f"   4. ✅ Found {len(links)} elements by role 'link'")
        except:
            print(f"   4. ⚠️  No links found")
        
        # 5. XPath
        try:
            h1 = page.locator('xpath=//h1')
            if h1.is_visible():
                print(f"   5. ✅ Found element by XPath '//h1'")
                print(f"      Text: {h1.text_content()}")
        except:
            print(f"   5. ⚠️  Element not found by XPath")
        
        browser.close()


def multiple_browsers_example():
    """Demonstrate using different browser engines."""
    print("\n" + "="*60)
    print("MULTIPLE BROWSER ENGINES EXAMPLE")
    print("="*60)
    
    browsers = {
        'Chromium': 'chromium',
        'Firefox': 'firefox',
        'WebKit (Safari)': 'webkit'
    }
    
    url = "https://quotes.toscrape.com/"
    
    with sync_playwright() as p:
        for browser_name, browser_type in browsers.items():
            try:
                print(f"\nTesting {browser_name}...")
                
                # Launch browser
                if browser_type == 'chromium':
                    browser = p.chromium.launch(headless=True)
                elif browser_type == 'firefox':
                    browser = p.firefox.launch(headless=True)
                elif browser_type == 'webkit':
                    browser = p.webkit.launch(headless=True)
                
                page = browser.new_page()
                page.goto(url)
                page.wait_for_load_state('networkidle')
                
                title = page.title()
                print(f"   ✅ {browser_name}: Title = {title}")
                
                browser.close()
            except Exception as e:
                print(f"   ⚠️  {browser_name}: {e}")


if __name__ == "__main__":
    # Run examples
    basic_playwright_example()
    finding_elements_example()
    multiple_browsers_example()
    
    print("\n" + "="*60)
    print("Examples completed!")
    print("="*60)
    print("\n💡 Tips:")
    print("  - Install Playwright browsers: playwright install")
    print("  - Playwright supports Chromium, Firefox, and WebKit")
    print("  - Use locator() for finding elements (modern API)")
    print("  - Use wait_for_load_state() for reliable page loading")
