"""
Beginner Selenium Example 2: Basic Interactions
=================================================

This example demonstrates:
- How to click buttons and links
- How to fill in text fields
- How to get text from elements
- How to navigate between pages
"""

from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.chrome.options import Options
import time

def setup_driver():
    """Set up Chrome WebDriver."""
    chrome_options = Options()
    chrome_options.add_argument('user-agent=Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36')
    
    try:
        return webdriver.Chrome(options=chrome_options)
    except Exception as e:
        print(f"❌ Error: {e}")
        print("Make sure ChromeDriver is installed!")
        return None


def click_example():
    """Demonstrate clicking buttons and links."""
    driver = setup_driver()
    
    if not driver:
        return
    
    try:
        print("="*60)
        print("CLICKING ELEMENTS EXAMPLE")
        print("="*60)
        
        url = "https://quotes.toscrape.com/"
        driver.get(url)
        time.sleep(2)
        
        print(f"\n1. Opened: {url}")
        print(f"   Current page: {driver.current_url}")
        
        # Find and click a link
        try:
            next_link = driver.find_element(By.PARTIAL_LINK_TEXT, "Next")
            print(f"\n2. Found 'Next' link")
            print(f"   Clicking to go to next page...")
            
            next_link.click()
            time.sleep(2)
            
            print(f"   Now on page: {driver.current_url}")
            print(f"   Page title: {driver.title}")
        except Exception as e:
            print(f"   ⚠️  Could not find or click 'Next' link: {e}")
        
    except Exception as e:
        print(f"❌ Error: {e}")
    finally:
        driver.quit()


def form_filling_example():
    """Demonstrate filling in forms."""
    driver = setup_driver()
    
    if not driver:
        return
    
    try:
        print("\n" + "="*60)
        print("FORM FILLING EXAMPLE")
        print("="*60)
        
        # Use a simple form page
        url = "https://httpbin.org/forms/post"
        driver.get(url)
        time.sleep(2)
        
        print(f"\n1. Opened form page: {url}")
        
        # Find input fields and fill them
        try:
            # Find text input by name
            customer_field = driver.find_element(By.NAME, "custname")
            customer_field.clear()
            customer_field.send_keys("John Doe")
            print("   ✅ Filled in customer name: John Doe")
            
            # Find another field
            tel_field = driver.find_element(By.NAME, "custtel")
            tel_field.clear()
            tel_field.send_keys("123-456-7890")
            print("   ✅ Filled in telephone: 123-456-7890")
            
            # Find textarea
            comments = driver.find_element(By.NAME, "comments")
            comments.clear()
            comments.send_keys("This is a test comment from Selenium!")
            print("   ✅ Filled in comments")
            
            # Wait to see the filled form
            time.sleep(2)
            
        except Exception as e:
            print(f"   ⚠️  Error filling form: {e}")
        
    except Exception as e:
        print(f"❌ Error: {e}")
    finally:
        driver.quit()


def text_extraction_example():
    """Demonstrate extracting text from elements."""
    driver = setup_driver()
    
    if not driver:
        return
    
    try:
        print("\n" + "="*60)
        print("TEXT EXTRACTION EXAMPLE")
        print("="*60)
        
        url = "https://quotes.toscrape.com/"
        driver.get(url)
        time.sleep(2)
        
        print(f"\n1. Extracting text from: {url}")
        
        # Get all quotes
        quotes = driver.find_elements(By.CLASS_NAME, "quote")
        print(f"\n2. Found {len(quotes)} quotes")
        
        # Extract text from first few quotes
        for i, quote in enumerate(quotes[:3], 1):
            try:
                text_elem = quote.find_element(By.CLASS_NAME, "text")
                author_elem = quote.find_element(By.CLASS_NAME, "author")
                
                print(f"\n   Quote {i}:")
                print(f"   Text: {text_elem.text}")
                print(f"   Author: {author_elem.text}")
            except Exception as e:
                print(f"   ⚠️  Error extracting quote {i}: {e}")
        
    except Exception as e:
        print(f"❌ Error: {e}")
    finally:
        driver.quit()


def keyboard_actions_example():
    """Demonstrate keyboard actions."""
    driver = setup_driver()
    
    if not driver:
        return
    
    try:
        print("\n" + "="*60)
        print("KEYBOARD ACTIONS EXAMPLE")
        print("="*60)
        
        url = "https://www.google.com"
        driver.get(url)
        time.sleep(2)
        
        print(f"\n1. Opened: {url}")
        
        # Find search box (this might need adjustment based on Google's current HTML)
        try:
            # Try to find search box - Google's structure may vary
            search_box = driver.find_element(By.NAME, "q")
            
            print("2. Found search box")
            print("   Typing 'Python Selenium'...")
            
            search_box.send_keys("Python Selenium")
            time.sleep(1)
            
            # Press Enter
            search_box.send_keys(Keys.RETURN)
            time.sleep(3)
            
            print(f"   ✅ Searched! Current URL: {driver.current_url}")
            
        except Exception as e:
            print(f"   ⚠️  Could not interact with search box: {e}")
            print("   (Google's HTML structure may have changed)")
        
    except Exception as e:
        print(f"❌ Error: {e}")
    finally:
        driver.quit()


if __name__ == "__main__":
    click_example()
    form_filling_example()
    text_extraction_example()
    keyboard_actions_example()
    
    print("\n" + "="*60)
    print("All examples completed!")
    print("="*60)
    print("\n💡 What you learned:")
    print("  - How to click buttons and links")
    print("  - How to fill in forms")
    print("  - How to extract text from elements")
    print("  - How to use keyboard actions")

