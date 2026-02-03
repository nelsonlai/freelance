"""
Intermediate Selenium Example 1: Explicit and Implicit Waits
=============================================================

This example demonstrates:
- Why waits are important
- Implicit waits
- Explicit waits with WebDriverWait
- Expected conditions
"""

from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
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
        return None


def implicit_wait_example():
    """Demonstrate implicit waits."""
    driver = setup_driver()
    
    if not driver:
        return
    
    try:
        print("="*60)
        print("IMPLICIT WAIT EXAMPLE")
        print("="*60)
        
        # Set implicit wait (waits up to 10 seconds for elements to appear)
        driver.implicitly_wait(10)
        print("\n1. Set implicit wait to 10 seconds")
        
        url = "https://quotes.toscrape.com/js/"
        driver.get(url)
        print(f"2. Opened: {url}")
        
        # This will wait up to 10 seconds for the element to appear
        quote = driver.find_element(By.CLASS_NAME, "quote")
        print("3. ✅ Found quote element (waited if necessary)")
        print(f"   Quote text: {quote.find_element(By.CLASS_NAME, "text").text[:50]}...")
        
    except Exception as e:
        print(f"❌ Error: {e}")
    finally:
        driver.quit()


def explicit_wait_example():
    """Demonstrate explicit waits with WebDriverWait."""
    driver = setup_driver()
    
    if not driver:
        return
    
    try:
        print("\n" + "="*60)
        print("EXPLICIT WAIT EXAMPLE")
        print("="*60)
        
        url = "https://quotes.toscrape.com/js/"
        driver.get(url)
        print(f"\n1. Opened: {url}")
        
        # Create WebDriverWait instance (waits up to 10 seconds)
        wait = WebDriverWait(driver, 10)
        
        # Wait for element to be present
        print("2. Waiting for quote element to appear...")
        quote = wait.until(
            EC.presence_of_element_located((By.CLASS_NAME, "quote"))
        )
        print("   ✅ Quote element found!")
        
        # Wait for element to be visible
        print("3. Waiting for quote text to be visible...")
        quote_text = wait.until(
            EC.visibility_of_element_located((By.CLASS_NAME, "text"))
        )
        print(f"   ✅ Quote text visible: {quote_text.text[:50]}...")
        
        # Wait for element to be clickable
        try:
            next_button = wait.until(
                EC.element_to_be_clickable((By.PARTIAL_LINK_TEXT, "Next"))
            )
            print("4. ✅ Next button is clickable!")
        except:
            print("4. ⚠️  Next button not found or not clickable")
        
    except Exception as e:
        print(f"❌ Error: {e}")
    finally:
        driver.quit()


def wait_for_text_example():
    """Wait for specific text to appear."""
    driver = setup_driver()
    
    if not driver:
        return
    
    try:
        print("\n" + "="*60)
        print("WAIT FOR TEXT EXAMPLE")
        print("="*60)
        
        url = "https://quotes.toscrape.com/"
        driver.get(url)
        print(f"\n1. Opened: {url}")
        
        wait = WebDriverWait(driver, 10)
        
        # Wait for specific text to be present in an element
        print("2. Waiting for 'Quotes to Scrape' text...")
        element = wait.until(
            EC.text_to_be_present_in_element((By.TAG_NAME, "h1"), "Quotes to Scrape")
        )
        print("   ✅ Text found!")
        
        # Get the heading
        heading = driver.find_element(By.TAG_NAME, "h1")
        print(f"   Heading text: {heading.text}")
        
    except Exception as e:
        print(f"❌ Error: {e}")
    finally:
        driver.quit()


def wait_for_page_load_example():
    """Wait for page to load completely."""
    driver = setup_driver()
    
    if not driver:
        return
    
    try:
        print("\n" + "="*60)
        print("WAIT FOR PAGE LOAD EXAMPLE")
        print("="*60)
        
        url = "https://quotes.toscrape.com/js/"
        driver.get(url)
        print(f"\n1. Opened: {url}")
        
        wait = WebDriverWait(driver, 10)
        
        # Wait for document ready state
        print("2. Waiting for page to load...")
        wait.until(
            lambda d: d.execute_script("return document.readyState") == "complete"
        )
        print("   ✅ Page loaded!")
        
        # Wait for jQuery to be loaded (if the site uses it)
        try:
            wait.until(
                lambda d: d.execute_script("return typeof jQuery !== 'undefined' && jQuery.active == 0")
            )
            print("   ✅ jQuery finished loading!")
        except:
            print("   ⚠️  Site doesn't use jQuery or it's already loaded")
        
    except Exception as e:
        print(f"❌ Error: {e}")
    finally:
        driver.quit()


if __name__ == "__main__":
    implicit_wait_example()
    explicit_wait_example()
    wait_for_text_example()
    wait_for_page_load_example()
    
    print("\n" + "="*60)
    print("All wait examples completed!")
    print("="*60)
    print("\n💡 Key points:")
    print("  - Implicit waits: Set once, applies to all elements")
    print("  - Explicit waits: More control, wait for specific conditions")
    print("  - Always use waits instead of time.sleep() when possible")
    print("  - Waits make your code more reliable and faster")

