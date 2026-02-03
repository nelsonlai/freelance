"""
Beginner Playwright Example 2: Basic Interactions
==================================================

This example demonstrates:
- Clicking buttons and links
- Filling forms
- Extracting text and attributes
- Keyboard actions
"""

from playwright.sync_api import sync_playwright
import time

def clicking_example():
    """Demonstrate clicking elements."""
    with sync_playwright() as p:
        print("="*60)
        print("CLICKING ELEMENTS EXAMPLE")
        print("="*60)
        
        browser = p.chromium.launch(headless=False)
        page = browser.new_page()
        
        url = "https://quotes.toscrape.com/"
        page.goto(url)
        page.wait_for_load_state('networkidle')
        
        print(f"\n1. Opened: {url}")
        print(f"   Current page: {page.url}")
        
        # Click a link
        try:
            next_link = page.get_by_text('Next', exact=False).first
            if next_link.is_visible():
                print(f"\n2. Found 'Next' link")
                print(f"   Clicking to go to next page...")
                
                next_link.click()
                page.wait_for_load_state('networkidle')
                
                print(f"   Now on page: {page.url}")
                print(f"   Page title: {page.title()}")
        except Exception as e:
            print(f"   ⚠️  Could not find or click 'Next' link: {e}")
        
        browser.close()


def form_filling_example():
    """Demonstrate filling in forms."""
    with sync_playwright() as p:
        print("\n" + "="*60)
        print("FORM FILLING EXAMPLE")
        print("="*60)
        
        browser = p.chromium.launch(headless=False)
        page = browser.new_page()
        
        # Use a simple form page
        url = "https://httpbin.org/forms/post"
        page.goto(url)
        page.wait_for_load_state('networkidle')
        
        print(f"\n1. Opened form page: {url}")
        
        # Fill in form fields
        try:
            # Fill text input
            customer_field = page.locator('input[name="custname"]')
            customer_field.fill("John Doe")
            print("   ✅ Filled in customer name: John Doe")
            
            # Fill telephone
            tel_field = page.locator('input[name="custtel"]')
            tel_field.fill("123-456-7890")
            print("   ✅ Filled in telephone: 123-456-7890")
            
            # Fill email
            email_field = page.locator('input[name="custemail"]')
            email_field.fill("test@example.com")
            print("   ✅ Filled in email: test@example.com")
            
            # Fill textarea
            comments = page.locator('textarea[name="comments"]')
            comments.fill("This is a test comment from Playwright!")
            print("   ✅ Filled in comments")
            
            time.sleep(2)  # Wait to see the filled form
            
        except Exception as e:
            print(f"   ⚠️  Error filling form: {e}")
        
        browser.close()


def text_extraction_example():
    """Demonstrate extracting text and data from elements."""
    with sync_playwright() as p:
        print("\n" + "="*60)
        print("TEXT EXTRACTION EXAMPLE")
        print("="*60)
        
        browser = p.chromium.launch(headless=True)
        page = browser.new_page()
        
        url = "https://quotes.toscrape.com/"
        page.goto(url)
        page.wait_for_load_state('networkidle')
        
        print(f"\n1. Extracting text from: {url}")
        
        # Get all quotes
        quotes = page.locator('.quote').all()
        print(f"\n2. Found {len(quotes)} quotes")
        
        # Extract text from first few quotes
        for i in range(min(3, len(quotes))):
            quote_locator = page.locator('.quote').nth(i)
            
            text = quote_locator.locator('.text').text_content()
            author = quote_locator.locator('.author').text_content()
            
            # Get tags
            tags = quote_locator.locator('.tag').all_text_contents()
            
            print(f"\n   Quote {i+1}:")
            print(f"   Text: {text}")
            print(f"   Author: {author}")
            print(f"   Tags: {', '.join(tags)}")
        
        # Get inner HTML
        print(f"\n3. Getting inner HTML of first quote:")
        first_quote_html = page.locator('.quote').first.inner_html()
        print(f"   First 200 chars: {first_quote_html[:200]}...")
        
        # Get attributes
        print(f"\n4. Getting attributes:")
        links = page.locator('a').first
        href = links.get_attribute('href')
        print(f"   First link href: {href}")
        
        browser.close()


def keyboard_actions_example():
    """Demonstrate keyboard actions."""
    with sync_playwright() as p:
        print("\n" + "="*60)
        print("KEYBOARD ACTIONS EXAMPLE")
        print("="*60)
        
        browser = p.chromium.launch(headless=False)
        page = browser.new_page()
        
        url = "https://www.google.com"
        page.goto(url)
        page.wait_for_load_state('networkidle')
        
        print(f"\n1. Opened: {url}")
        
        # Find search box and type
        try:
            search_box = page.locator('textarea[name="q"]')  # Google's search box
            
            if search_box.is_visible():
                print("2. Found search box")
                print("   Typing 'Playwright Python'...")
                
                search_box.fill("Playwright Python")
                time.sleep(1)
                
                # Press Enter
                search_box.press('Enter')
                page.wait_for_load_state('networkidle')
                time.sleep(2)
                
                print(f"   ✅ Searched! Current URL: {page.url[:80]}...")
            else:
                print("   ⚠️  Search box not found (Google's structure may have changed)")
        except Exception as e:
            print(f"   ⚠️  Error: {e}")
        
        browser.close()


def screenshot_example():
    """Demonstrate taking screenshots."""
    with sync_playwright() as p:
        print("\n" + "="*60)
        print("SCREENSHOT EXAMPLE")
        print("="*60)
        
        browser = p.chromium.launch(headless=True)
        page = browser.new_page()
        
        url = "https://quotes.toscrape.com/"
        page.goto(url)
        page.wait_for_load_state('networkidle')
        
        print(f"\n1. Opened: {url}")
        
        # Take full page screenshot
        screenshot_path = "playwright_screenshot.png"
        page.screenshot(path=screenshot_path, full_page=True)
        print(f"2. ✅ Full page screenshot saved: {screenshot_path}")
        
        # Take screenshot of specific element
        try:
            quote = page.locator('.quote').first
            element_screenshot = "quote_element.png"
            quote.screenshot(path=element_screenshot)
            print(f"3. ✅ Element screenshot saved: {element_screenshot}")
        except Exception as e:
            print(f"   ⚠️  Could not take element screenshot: {e}")
        
        browser.close()


if __name__ == "__main__":
    clicking_example()
    form_filling_example()
    text_extraction_example()
    keyboard_actions_example()
    screenshot_example()
    
    print("\n" + "="*60)
    print("All examples completed!")
    print("="*60)
    print("\n💡 What you learned:")
    print("  - How to click buttons and links")
    print("  - How to fill in forms")
    print("  - How to extract text and attributes")
    print("  - How to use keyboard actions")
    print("  - How to take screenshots")
