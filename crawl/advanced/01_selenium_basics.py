"""
Advanced Selenium Example 1: JavaScript and Dynamic Content
=============================================================

This example demonstrates:
- How to set up Selenium WebDriver in headless mode
- How to interact with JavaScript-rendered pages
- How to wait for elements to load
- How to handle dynamic content
- How to scroll pages
"""

from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.chrome.service import Service
from selenium.webdriver.chrome.options import Options
import time

def setup_driver(headless=True):
    """
    Set up and return a Chrome WebDriver instance.
    
    Args:
        headless: Run browser in headless mode (no GUI)
    """
    chrome_options = Options()
    
    if headless:
        chrome_options.add_argument('--headless')
    
    chrome_options.add_argument('--no-sandbox')
    chrome_options.add_argument('--disable-dev-shm-usage')
    chrome_options.add_argument('--disable-blink-features=AutomationControlled')
    chrome_options.add_experimental_option("excludeSwitches", ["enable-automation"])
    chrome_options.add_experimental_option('useAutomationExtension', False)
    
    # User agent to appear more like a real browser
    chrome_options.add_argument('user-agent=Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36')
    
    try:
        driver = webdriver.Chrome(options=chrome_options)
        return driver
    except Exception as e:
        print(f"❌ Error setting up driver: {e}")
        print("Make sure ChromeDriver is installed and in your PATH")
        print("Download from: https://chromedriver.chromium.org/")
        return None


def scrape_dynamic_content(url):
    """
    Scrape content from a JavaScript-rendered page.
    
    Args:
        url: URL to scrape
    """
    driver = setup_driver(headless=True)
    
    if not driver:
        return None
    
    try:
        print(f"Loading: {url}")
        driver.get(url)
        
        # Wait for page to load
        time.sleep(2)
        
        # Wait for specific element (example: wait for body)
        WebDriverWait(driver, 10).until(
            EC.presence_of_element_located((By.TAG_NAME, "body"))
        )
        
        # Get page title
        title = driver.title
        print(f"Page title: {title}")
        
        # Extract text content
        body = driver.find_element(By.TAG_NAME, "body")
        text_content = body.text
        
        # Find all links
        links = driver.find_elements(By.TAG_NAME, "a")
        link_urls = [link.get_attribute('href') for link in links if link.get_attribute('href')]
        
        # Example: Click a button if it exists
        try:
            # This is just an example - adjust selector based on your needs
            button = driver.find_element(By.CSS_SELECTOR, "button")
            if button:
                print("Found a button (not clicking in this example)")
        except:
            pass  # Button not found, that's okay
        
        results = {
            'title': title,
            'text_length': len(text_content),
            'link_count': len(link_urls),
            'sample_text': text_content[:500] if text_content else "",
            'links': link_urls[:10]  # First 10 links
        }
        
        return results
        
    except Exception as e:
        print(f"❌ Error scraping: {e}")
        return None
    finally:
        driver.quit()


def scrape_with_scrolling(url, scroll_pause_time=2):
    """
    Scrape a page that requires scrolling to load content.
    
    Args:
        url: URL to scrape
        scroll_pause_time: Time to wait after each scroll
    """
    driver = setup_driver(headless=True)
    
    if not driver:
        return None
    
    try:
        print(f"Loading: {url}")
        driver.get(url)
        
        # Get initial page height
        last_height = driver.execute_script("return document.body.scrollHeight")
        scroll_count = 0
        
        print("Scrolling to load content...")
        while True:
            # Scroll down to bottom
            driver.execute_script("window.scrollTo(0, document.body.scrollHeight);")
            
            # Wait for new content to load
            time.sleep(scroll_pause_time)
            
            # Calculate new scroll height
            new_height = driver.execute_script("return document.body.scrollHeight")
            scroll_count += 1
            
            if new_height == last_height:
                # No new content loaded
                break
            
            last_height = new_height
            print(f"  Scroll {scroll_count}: Page height increased to {new_height}")
        
        print(f"Finished scrolling after {scroll_count} scrolls")
        
        # Now extract content
        body = driver.find_element(By.TAG_NAME, "body")
        text_content = body.text
        
        results = {
            'scrolls': scroll_count,
            'final_height': last_height,
            'text_length': len(text_content),
            'sample_text': text_content[:500]
        }
        
        return results
        
    except Exception as e:
        print(f"❌ Error: {e}")
        return None
    finally:
        driver.quit()


if __name__ == "__main__":
    print("="*60)
    print("SELENIUM BASICS EXAMPLE")
    print("="*60)
    
    # Example 1: Basic scraping
    print("\n1. Basic Dynamic Content Scraping")
    print("-" * 60)
    url = "https://quotes.toscrape.com/js/"
    results = scrape_dynamic_content(url)
    
    if results:
        print(f"\n✅ Scraping successful!")
        print(f"   Title: {results['title']}")
        print(f"   Text length: {results['text_length']} characters")
        print(f"   Links found: {results['link_count']}")
        print(f"\n   Sample text:\n   {results['sample_text'][:200]}...")
    
    # Example 2: Scrolling
    print("\n\n2. Scrolling to Load Content")
    print("-" * 60)
    scroll_results = scrape_with_scrolling("https://quotes.toscrape.com/scroll")
    
    if scroll_results:
        print(f"\n✅ Scrolling completed!")
        print(f"   Total scrolls: {scroll_results['scrolls']}")
        print(f"   Final page height: {scroll_results['final_height']}px")
        print(f"   Content length: {scroll_results['text_length']} characters")
    
    print("\n" + "="*60)
    print("Example completed!")
    print("="*60)
    print("\n💡 Note: Make sure ChromeDriver is installed")
    print("   Install: brew install chromedriver (macOS)")
    print("   Or download from: https://chromedriver.chromium.org/")

