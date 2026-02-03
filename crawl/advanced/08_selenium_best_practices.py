"""
Advanced Selenium Example 5: Best Practices and Production Code
================================================================

This example demonstrates:
- Page Object Model pattern
- Reusable functions
- Error handling
- Logging
- Configuration management
- Clean code structure
"""

from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.chrome.options import Options
from selenium.common.exceptions import TimeoutException, NoSuchElementException
import logging
import time

# Set up logging
logging.basicConfig(
    level=logging.INFO,
    format='%(asctime)s - %(levelname)s - %(message)s'
)
logger = logging.getLogger(__name__)


class WebDriverManager:
    """Manages WebDriver instances with best practices."""
    
    def __init__(self, headless=True):
        self.headless = headless
        self.driver = None
    
    def create_driver(self):
        """Create and configure WebDriver."""
        chrome_options = Options()
        
        if self.headless:
            chrome_options.add_argument('--headless')
            chrome_options.add_argument('--no-sandbox')
            chrome_options.add_argument('--disable-dev-shm-usage')
        
        chrome_options.add_argument('user-agent=Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36')
        
        try:
            self.driver = webdriver.Chrome(options=chrome_options)
            self.driver.implicitly_wait(10)  # Set implicit wait
            logger.info("WebDriver created successfully")
            return self.driver
        except Exception as e:
            logger.error(f"Failed to create WebDriver: {e}")
            raise
    
    def quit(self):
        """Safely quit the driver."""
        if self.driver:
            try:
                self.driver.quit()
                logger.info("WebDriver closed successfully")
            except Exception as e:
                logger.error(f"Error closing WebDriver: {e}")
    
    def __enter__(self):
        """Context manager entry."""
        self.create_driver()
        return self.driver
    
    def __exit__(self, exc_type, exc_val, exc_tb):
        """Context manager exit."""
        self.quit()


class QuoteScraper:
    """Page Object Model for quotes.toscrape.com"""
    
    def __init__(self, driver):
        self.driver = driver
        self.wait = WebDriverWait(driver, 10)
        self.base_url = "https://quotes.toscrape.com/"
    
    def navigate_to_page(self, path=""):
        """Navigate to a page."""
        url = self.base_url + path
        logger.info(f"Navigating to: {url}")
        self.driver.get(url)
        time.sleep(2)  # Allow page to load
    
    def get_quotes(self):
        """Get all quotes on the current page."""
        try:
            quotes = self.wait.until(
                EC.presence_of_all_elements_located((By.CLASS_NAME, "quote"))
            )
            logger.info(f"Found {len(quotes)} quotes")
            return quotes
        except TimeoutException:
            logger.warning("No quotes found on page")
            return []
    
    def extract_quote_data(self, quote_element):
        """Extract data from a quote element."""
        try:
            text = quote_element.find_element(By.CLASS_NAME, "text").text
            author = quote_element.find_element(By.CLASS_NAME, "author").text
            tags = [tag.text for tag in quote_element.find_elements(By.CLASS_NAME, "tag")]
            
            return {
                'text': text,
                'author': author,
                'tags': tags
            }
        except NoSuchElementException as e:
            logger.error(f"Error extracting quote data: {e}")
            return None
    
    def click_next(self):
        """Click the next page button."""
        try:
            next_button = self.wait.until(
                EC.element_to_be_clickable((By.PARTIAL_LINK_TEXT, "Next"))
            )
            next_button.click()
            logger.info("Clicked next button")
            time.sleep(2)  # Wait for page to load
            return True
        except TimeoutException:
            logger.info("No next button found - reached last page")
            return False
    
    def has_next_page(self):
        """Check if there's a next page."""
        try:
            self.driver.find_element(By.PARTIAL_LINK_TEXT, "Next")
            return True
        except NoSuchElementException:
            return False


def scrape_with_best_practices():
    """Demonstrate scraping with best practices."""
    print("="*60)
    print("BEST PRACTICES EXAMPLE")
    print("="*60)
    
    # Use context manager for automatic cleanup
    with WebDriverManager(headless=True) as driver:
        scraper = QuoteScraper(driver)
        
        all_quotes = []
        max_pages = 3
        
        try:
            scraper.navigate_to_page()
            
            for page in range(1, max_pages + 1):
                logger.info(f"Scraping page {page}")
                
                quotes = scraper.get_quotes()
                
                for quote_element in quotes:
                    quote_data = scraper.extract_quote_data(quote_element)
                    if quote_data:
                        quote_data['page'] = page
                        all_quotes.append(quote_data)
                
                # Try to go to next page
                if not scraper.has_next_page() or page >= max_pages:
                    break
                
                if not scraper.click_next():
                    break
            
            print(f"\n✅ Scraped {len(all_quotes)} quotes from {page} page(s)")
            
            # Display sample
            if all_quotes:
                print("\nSample quotes:")
                for i, quote in enumerate(all_quotes[:3], 1):
                    print(f"\n{i}. {quote['text'][:60]}...")
                    print(f"   Author: {quote['author']}")
                    print(f"   Tags: {', '.join(quote['tags'])}")
                    print(f"   Page: {quote['page']}")
            
        except Exception as e:
            logger.error(f"Error during scraping: {e}")
            raise


def robust_element_finding(driver):
    """Demonstrate robust element finding with error handling."""
    print("\n" + "="*60)
    print("ROBUST ELEMENT FINDING")
    print("="*60)
    
    driver.get("https://quotes.toscrape.com/")
    wait = WebDriverWait(driver, 10)
    
    def safe_find_element(by, value, timeout=10):
        """Safely find an element with error handling."""
        try:
            element = WebDriverWait(driver, timeout).until(
                EC.presence_of_element_located((by, value))
            )
            logger.info(f"Found element: {value}")
            return element
        except TimeoutException:
            logger.warning(f"Element not found: {value}")
            return None
    
    # Try to find elements safely
    quote = safe_find_element(By.CLASS_NAME, "quote")
    if quote:
        print("✅ Found quote element")
    
    next_button = safe_find_element(By.PARTIAL_LINK_TEXT, "Next")
    if next_button:
        print("✅ Found next button")
    else:
        print("⚠️  Next button not found (might be on last page)")


if __name__ == "__main__":
    # Example 1: Best practices scraping
    scrape_with_best_practices()
    
    # Example 2: Robust element finding
    with WebDriverManager(headless=True) as driver:
        robust_element_finding(driver)
    
    print("\n" + "="*60)
    print("Best practices examples completed!")
    print("="*60)
    print("\n💡 Best practices demonstrated:")
    print("  ✅ Page Object Model pattern")
    print("  ✅ Context managers for resource cleanup")
    print("  ✅ Logging for debugging")
    print("  ✅ Error handling with try-except")
    print("  ✅ Reusable functions and classes")
    print("  ✅ Implicit waits for reliability")
    print("  ✅ Clean code structure")

