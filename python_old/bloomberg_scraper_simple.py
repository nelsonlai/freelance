# ==============================================================================
# Simple Bloomberg Scraper - Basic Example
# ==============================================================================
# A simplified version of the Bloomberg scraper for educational purposes.
# This version focuses on the core concepts without extensive error handling.

from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.chrome.service import Service
from selenium.webdriver.chrome.options import Options
from webdriver_manager.chrome import ChromeDriverManager
import time

def simple_bloomberg_scraper():
    """
    Simple function to scrape Bloomberg homepage.
    """
    # Setup Chrome options
    chrome_options = Options()
    chrome_options.add_argument("--headless")  # Run in background
    chrome_options.add_argument("--no-sandbox")
    chrome_options.add_argument("--disable-dev-shm-usage")
    
    # Initialize driver
    service = Service(ChromeDriverManager().install())
    driver = webdriver.Chrome(service=service, options=chrome_options)
    
    try:
        print("Navigating to Bloomberg...")
        driver.get("https://www.bloomberg.com/")
        
        # Wait for page to load
        time.sleep(5)
        
        print(f"Page Title: {driver.title}")
        print(f"Current URL: {driver.current_url}")
        
        # Find and print headlines
        print("\n=== HEADLINES ===")
        headlines = driver.find_elements(By.TAG_NAME, "h1")
        headlines.extend(driver.find_elements(By.TAG_NAME, "h2"))
        headlines.extend(driver.find_elements(By.TAG_NAME, "h3"))
        
        for i, headline in enumerate(headlines[:10], 1):
            text = headline.text.strip()
            if text:
                print(f"{i}. {text}")
        
        # Find and print links
        print("\n=== ARTICLE LINKS ===")
        links = driver.find_elements(By.CSS_SELECTOR, "a[href*='/news/']")
        
        for i, link in enumerate(links[:5], 1):
            href = link.get_attribute('href')
            text = link.text.strip()
            if text and href:
                print(f"{i}. {text}")
                print(f"   URL: {href}")
        
        # Get page source length
        print(f"\nPage source length: {len(driver.page_source)} characters")
        
    except Exception as e:
        print(f"Error: {e}")
    
    finally:
        driver.quit()
        print("\nScraping completed!")

if __name__ == "__main__":
    simple_bloomberg_scraper()
