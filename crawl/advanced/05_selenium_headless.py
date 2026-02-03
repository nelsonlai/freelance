"""
Advanced Selenium Example 2: Headless Browsing
==============================================

This example demonstrates:
- How to run Selenium in headless mode (no browser window)
- Benefits of headless mode
- Screenshot capture
- Performance considerations
"""

from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.chrome.options import Options
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
import time

def setup_headless_driver():
    """
    Set up Chrome WebDriver in headless mode.
    Headless mode runs without opening a browser window - faster and uses less resources.
    """
    chrome_options = Options()
    
    # Enable headless mode
    chrome_options.add_argument('--headless')
    
    # Additional options for headless mode
    chrome_options.add_argument('--no-sandbox')
    chrome_options.add_argument('--disable-dev-shm-usage')
    chrome_options.add_argument('--disable-gpu')
    chrome_options.add_argument('--window-size=1920,1080')
    
    # User agent
    chrome_options.add_argument('user-agent=Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36')
    
    try:
        driver = webdriver.Chrome(options=chrome_options)
        return driver
    except Exception as e:
        print(f"❌ Error: {e}")
        return None


def headless_scraping_example():
    """Demonstrate scraping in headless mode."""
    driver = setup_headless_driver()
    
    if not driver:
        return
    
    try:
        print("="*60)
        print("HEADLESS SCRAPING EXAMPLE")
        print("="*60)
        
        url = "https://quotes.toscrape.com/js/"
        print(f"\n1. Opening (headless): {url}")
        driver.get(url)
        
        wait = WebDriverWait(driver, 10)
        
        # Wait for content to load
        wait.until(EC.presence_of_element_located((By.CLASS_NAME, "quote")))
        
        # Extract data
        quotes = driver.find_elements(By.CLASS_NAME, "quote")
        print(f"2. ✅ Found {len(quotes)} quotes (in headless mode)")
        
        # Extract first few quotes
        for i, quote in enumerate(quotes[:3], 1):
            text = quote.find_element(By.CLASS_NAME, "text").text
            author = quote.find_element(By.CLASS_NAME, "author").text
            print(f"\n   Quote {i}:")
            print(f"   {text[:60]}...")
            print(f"   - {author}")
        
        print("\n3. ✅ Scraping completed (no browser window was shown!)")
        
    except Exception as e:
        print(f"❌ Error: {e}")
    finally:
        driver.quit()


def screenshot_example():
    """Demonstrate taking screenshots in headless mode."""
    driver = setup_headless_driver()
    
    if not driver:
        return
    
    try:
        print("\n" + "="*60)
        print("SCREENSHOT EXAMPLE")
        print("="*60)
        
        url = "https://quotes.toscrape.com/"
        driver.get(url)
        time.sleep(2)
        
        print(f"\n1. Opened: {url}")
        
        # Take full page screenshot
        screenshot_path = "selenium_screenshot.png"
        driver.save_screenshot(screenshot_path)
        print(f"2. ✅ Screenshot saved: {screenshot_path}")
        
        # Take screenshot of specific element
        try:
            quote = driver.find_element(By.CLASS_NAME, "quote")
            element_screenshot = "quote_element.png"
            quote.screenshot(element_screenshot)
            print(f"3. ✅ Element screenshot saved: {element_screenshot}")
        except Exception as e:
            print(f"   ⚠️  Could not take element screenshot: {e}")
        
    except Exception as e:
        print(f"❌ Error: {e}")
    finally:
        driver.quit()


def headless_vs_normal_comparison():
    """Compare headless vs normal mode performance."""
    import time
    
    print("\n" + "="*60)
    print("HEADLESS VS NORMAL MODE COMPARISON")
    print("="*60)
    
    url = "https://quotes.toscrape.com/"
    
    # Test headless mode
    print("\n1. Testing headless mode...")
    start = time.time()
    
    driver = setup_headless_driver()
    if driver:
        driver.get(url)
        quotes = driver.find_elements(By.CLASS_NAME, "quote")
        driver.quit()
        headless_time = time.time() - start
        print(f"   ✅ Headless mode: {headless_time:.2f} seconds")
        print(f"   Found {len(quotes)} quotes")
    else:
        headless_time = None
    
    # Note: Normal mode test would require manual observation
    print("\n💡 Benefits of headless mode:")
    print("  - Faster execution (no GUI rendering)")
    print("  - Lower resource usage")
    print("  - Can run on servers without display")
    print("  - Better for automated testing/scraping")
    print("  - Still fully functional - JavaScript works!")


if __name__ == "__main__":
    headless_scraping_example()
    screenshot_example()
    headless_vs_normal_comparison()
    
    print("\n" + "="*60)
    print("Headless examples completed!")
    print("="*60)

