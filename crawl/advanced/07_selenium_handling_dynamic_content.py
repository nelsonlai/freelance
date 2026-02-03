"""
Advanced Selenium Example 4: Handling Dynamic Content
======================================================

This example demonstrates:
- Infinite scroll pages
- Lazy loading content
- Dynamic element appearance
- Handling AJAX requests
- Waiting for specific conditions
"""

from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.chrome.options import Options
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
import time

def setup_driver(headless=True):
    """Set up Chrome WebDriver."""
    chrome_options = Options()
    
    if headless:
        chrome_options.add_argument('--headless')
        chrome_options.add_argument('--no-sandbox')
        chrome_options.add_argument('--disable-dev-shm-usage')
    
    chrome_options.add_argument('user-agent=Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36')
    
    try:
        return webdriver.Chrome(options=chrome_options)
    except Exception as e:
        print(f"❌ Error: {e}")
        return None


def infinite_scroll_example():
    """Handle infinite scroll pages."""
    driver = setup_driver(headless=False)  # Show browser for this example
    
    if not driver:
        return
    
    try:
        print("="*60)
        print("INFINITE SCROLL EXAMPLE")
        print("="*60)
        
        url = "https://quotes.toscrape.com/scroll"
        driver.get(url)
        time.sleep(2)
        
        print(f"\n1. Opened: {url}")
        
        # Get initial number of quotes
        quotes = driver.find_elements(By.CLASS_NAME, "quote")
        initial_count = len(quotes)
        print(f"   Initial quotes: {initial_count}")
        
        # Scroll and load more content
        last_count = initial_count
        scroll_attempts = 0
        max_scrolls = 5
        
        while scroll_attempts < max_scrolls:
            # Scroll to bottom
            driver.execute_script("window.scrollTo(0, document.body.scrollHeight);")
            time.sleep(2)  # Wait for new content to load
            
            # Check if new content loaded
            quotes = driver.find_elements(By.CLASS_NAME, "quote")
            current_count = len(quotes)
            
            if current_count > last_count:
                print(f"   Scroll {scroll_attempts + 1}: Loaded {current_count - last_count} more quotes (total: {current_count})")
                last_count = current_count
            else:
                print(f"   Scroll {scroll_attempts + 1}: No new content loaded")
                break
            
            scroll_attempts += 1
        
        print(f"\n2. ✅ Final quote count: {last_count}")
        print(f"   Total scrolls: {scroll_attempts}")
        
    except Exception as e:
        print(f"❌ Error: {e}")
    finally:
        driver.quit()


def lazy_loading_example():
    """Handle lazy-loaded content."""
    driver = setup_driver(headless=True)
    
    if not driver:
        return
    
    try:
        print("\n" + "="*60)
        print("LAZY LOADING EXAMPLE")
        print("="*60)
        
        url = "https://quotes.toscrape.com/"
        driver.get(url)
        
        wait = WebDriverWait(driver, 10)
        
        print(f"\n1. Opened: {url}")
        
        # Wait for images to load (if any)
        print("2. Waiting for images to load...")
        
        # Check if images are loaded
        images = driver.find_elements(By.TAG_NAME, "img")
        print(f"   Found {len(images)} images")
        
        for img in images:
            # Scroll to image to trigger lazy loading
            driver.execute_script("arguments[0].scrollIntoView(true);", img)
            time.sleep(0.5)
            
            # Check if image is loaded
            is_loaded = driver.execute_script(
                "return arguments[0].complete && arguments[0].naturalHeight > 0;", 
                img
            )
            if is_loaded:
                print(f"   ✅ Image loaded: {img.get_attribute('src')}")
        
    except Exception as e:
        print(f"❌ Error: {e}")
    finally:
        driver.quit()


def wait_for_ajax_example():
    """Wait for AJAX requests to complete."""
    driver = setup_driver(headless=True)
    
    if not driver:
        return
    
    try:
        print("\n" + "="*60)
        print("WAIT FOR AJAX EXAMPLE")
        print("="*60)
        
        url = "https://quotes.toscrape.com/js/"
        driver.get(url)
        
        wait = WebDriverWait(driver, 10)
        
        print(f"\n1. Opened: {url}")
        
        # Wait for jQuery to finish (if site uses jQuery)
        print("2. Waiting for AJAX/jQuery to complete...")
        
        try:
            # Wait for jQuery to be loaded and all AJAX requests to complete
            wait.until(
                lambda d: d.execute_script(
                    "return typeof jQuery !== 'undefined' && jQuery.active == 0"
                )
            )
            print("   ✅ jQuery AJAX requests completed")
        except:
            # Site might not use jQuery, check for vanilla JS
            print("   ⚠️  Site doesn't use jQuery or it's not loaded")
        
        # Wait for document ready
        wait.until(
            lambda d: d.execute_script("return document.readyState") == "complete"
        )
        print("   ✅ Document ready")
        
        # Now elements should be loaded
        quotes = driver.find_elements(By.CLASS_NAME, "quote")
        print(f"3. ✅ Found {len(quotes)} quotes after waiting for AJAX")
        
    except Exception as e:
        print(f"❌ Error: {e}")
    finally:
        driver.quit()


def dynamic_element_wait_example():
    """Wait for dynamically appearing elements."""
    driver = setup_driver(headless=True)
    
    if not driver:
        return
    
    try:
        print("\n" + "="*60)
        print("DYNAMIC ELEMENT WAIT EXAMPLE")
        print("="*60)
        
        url = "https://quotes.toscrape.com/js/"
        driver.get(url)
        
        wait = WebDriverWait(driver, 10)
        
        print(f"\n1. Opened: {url}")
        
        # Wait for element to be present (appears in DOM)
        print("2. Waiting for quote element to appear in DOM...")
        quote = wait.until(
            EC.presence_of_element_located((By.CLASS_NAME, "quote"))
        )
        print("   ✅ Element present in DOM")
        
        # Wait for element to be visible (actually displayed)
        print("3. Waiting for quote element to be visible...")
        visible_quote = wait.until(
            EC.visibility_of_element_located((By.CLASS_NAME, "quote"))
        )
        print("   ✅ Element is visible")
        
        # Wait for element to be clickable
        try:
            link = wait.until(
                EC.element_to_be_clickable((By.PARTIAL_LINK_TEXT, "Next"))
            )
            print("4. ✅ Link is clickable")
        except:
            print("4. ⚠️  Link not found or not clickable")
        
        # Wait for multiple elements
        print("5. Waiting for multiple quotes to appear...")
        quotes = wait.until(
            EC.presence_of_all_elements_located((By.CLASS_NAME, "quote"))
        )
        print(f"   ✅ Found {len(quotes)} quotes")
        
    except Exception as e:
        print(f"❌ Error: {e}")
    finally:
        driver.quit()


def custom_wait_condition_example():
    """Create custom wait conditions."""
    driver = setup_driver(headless=True)
    
    if not driver:
        return
    
    try:
        print("\n" + "="*60)
        print("CUSTOM WAIT CONDITION EXAMPLE")
        print("="*60)
        
        url = "https://quotes.toscrape.com/"
        driver.get(url)
        
        wait = WebDriverWait(driver, 10)
        
        print(f"\n1. Opened: {url}")
        
        # Custom condition: wait for at least 5 quotes
        print("2. Waiting for at least 5 quotes...")
        
        def at_least_n_quotes(n):
            def condition(driver):
                quotes = driver.find_elements(By.CLASS_NAME, "quote")
                return len(quotes) >= n
            return condition
        
        wait.until(at_least_n_quotes(5))
        quotes = driver.find_elements(By.CLASS_NAME, "quote")
        print(f"   ✅ Found {len(quotes)} quotes (at least 5)")
        
    except Exception as e:
        print(f"❌ Error: {e}")
    finally:
        driver.quit()


if __name__ == "__main__":
    infinite_scroll_example()
    lazy_loading_example()
    wait_for_ajax_example()
    dynamic_element_wait_example()
    custom_wait_condition_example()
    
    print("\n" + "="*60)
    print("Dynamic content examples completed!")
    print("="*60)
    print("\n💡 Key points:")
    print("  - Always wait for dynamic content to load")
    print("  - Use WebDriverWait instead of time.sleep()")
    print("  - Scroll to trigger lazy loading")
    print("  - Wait for AJAX/jQuery to complete")
    print("  - Create custom wait conditions for specific needs")

