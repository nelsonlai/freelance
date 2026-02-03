"""
Beginner Selenium Example 1: Introduction to Selenium
=====================================================

This example demonstrates:
- How to set up Selenium WebDriver
- How to open a webpage
- How to find elements on a page
- How to interact with basic elements
"""

from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.chrome.service import Service
from selenium.webdriver.chrome.options import Options
import time

def setup_driver():
    """
    Set up and return a Chrome WebDriver instance.
    This is a basic setup without headless mode so you can see what's happening.
    """
    chrome_options = Options()
    
    # Add a user agent to appear more like a real browser
    chrome_options.add_argument('user-agent=Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36')
    
    try:
        driver = webdriver.Chrome(options=chrome_options)
        return driver
    except Exception as e:
        print(f"❌ Error setting up driver: {e}")
        print("\n💡 Make sure ChromeDriver is installed:")
        print("   macOS: brew install chromedriver")
        print("   Or download from: https://chromedriver.chromium.org/")
        return None


def basic_selenium_example():
    """Basic example: Open a page and extract information."""
    driver = setup_driver()
    
    if not driver:
        return
    
    try:
        print("="*60)
        print("BASIC SELENIUM EXAMPLE")
        print("="*60)
        
        # Open a webpage
        url = "https://quotes.toscrape.com/"
        print(f"\n1. Opening: {url}")
        driver.get(url)
        
        # Wait a moment for the page to load
        time.sleep(2)
        
        # Get page title
        title = driver.title
        print(f"   Page title: {title}")
        
        # Find elements by different methods
        print("\n2. Finding elements:")
        
        # Find by tag name
        quotes = driver.find_elements(By.CLASS_NAME, "quote")
        print(f"   Found {len(quotes)} quotes on the page")
        
        # Find by CSS selector
        first_quote = driver.find_element(By.CSS_SELECTOR, "div.quote")
        quote_text = first_quote.find_element(By.CLASS_NAME, "text")
        author = first_quote.find_element(By.CLASS_NAME, "author")
        
        print(f"\n3. First quote:")
        print(f"   Text: {quote_text.text}")
        print(f"   Author: {author.text}")
        
        # Find all links
        links = driver.find_elements(By.TAG_NAME, "a")
        print(f"\n4. Found {len(links)} links on the page")
        
        # Get page source length
        page_source_length = len(driver.page_source)
        print(f"\n5. Page source length: {page_source_length} characters")
        
    except Exception as e:
        print(f"❌ Error: {e}")
    finally:
        # Always close the browser
        print("\n6. Closing browser...")
        driver.quit()
        print("✅ Done!")


def find_elements_example():
    """Demonstrate different ways to find elements."""
    driver = setup_driver()
    
    if not driver:
        return
    
    try:
        print("\n" + "="*60)
        print("FINDING ELEMENTS EXAMPLE")
        print("="*60)
        
        url = "https://quotes.toscrape.com/"
        driver.get(url)
        time.sleep(2)
        
        print("\nDifferent ways to find elements:")
        
        # 1. By ID
        try:
            element = driver.find_element(By.ID, "some-id")
            print("   ✅ Found by ID")
        except:
            print("   ⚠️  No element with ID 'some-id' found")
        
        # 2. By class name
        quotes = driver.find_elements(By.CLASS_NAME, "quote")
        print(f"   ✅ Found {len(quotes)} elements by class name 'quote'")
        
        # 3. By tag name
        links = driver.find_elements(By.TAG_NAME, "a")
        print(f"   ✅ Found {len(links)} elements by tag name 'a'")
        
        # 4. By CSS selector
        first_quote = driver.find_element(By.CSS_SELECTOR, "div.quote")
        print("   ✅ Found element by CSS selector 'div.quote'")
        
        # 5. By XPath
        try:
            element = driver.find_element(By.XPATH, "//div[@class='quote']")
            print("   ✅ Found element by XPath")
        except:
            print("   ⚠️  XPath not found")
        
        # 6. By link text
        try:
            next_link = driver.find_element(By.LINK_TEXT, "Next")
            print(f"   ✅ Found link by text: '{next_link.text}'")
        except:
            print("   ⚠️  Link with text 'Next' not found")
        
    except Exception as e:
        print(f"❌ Error: {e}")
    finally:
        driver.quit()


if __name__ == "__main__":
    # Run examples
    basic_selenium_example()
    find_elements_example()
    
    print("\n" + "="*60)
    print("Examples completed!")
    print("="*60)
    print("\n💡 Tips:")
    print("  - Always use driver.quit() to close the browser")
    print("  - Use time.sleep() to wait for pages to load")
    print("  - Try different methods to find elements")
    print("  - Check the browser window to see what's happening")

