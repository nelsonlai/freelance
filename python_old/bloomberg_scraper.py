# ==============================================================================
# Bloomberg Website Scraper using Selenium
# ==============================================================================
# This script demonstrates how to crawl the Bloomberg website using Python Selenium.
# It extracts headlines, market data, and article information from the homepage.
#
# Requirements:
# - selenium
# - webdriver-manager (for automatic driver management)
# - beautifulsoup4 (for HTML parsing)
# - pandas (for data manipulation)
#
# Usage:
# python bloomberg_scraper.py

import time
import json
import logging
from datetime import datetime
from typing import List, Dict, Optional

from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.chrome.service import Service
from selenium.webdriver.chrome.options import Options
from selenium.common.exceptions import TimeoutException, NoSuchElementException
from webdriver_manager.chrome import ChromeDriverManager
from bs4 import BeautifulSoup
import pandas as pd

# Configure logging
logging.basicConfig(
    level=logging.INFO,
    format='%(asctime)s - %(levelname)s - %(message)s',
    handlers=[
        logging.FileHandler('bloomberg_scraper.log'),
        logging.StreamHandler()
    ]
)
logger = logging.getLogger(__name__)

class BloombergScraper:
    """
    A class to scrape data from Bloomberg website using Selenium.
    """
    
    def __init__(self, headless: bool = True, wait_time: int = 10):
        """
        Initialize the Bloomberg scraper.
        
        Args:
            headless (bool): Whether to run browser in headless mode
            wait_time (int): Maximum wait time for elements to load
        """
        self.wait_time = wait_time
        self.driver = None
        self.wait = None
        self.setup_driver(headless)
    
    def setup_driver(self, headless: bool = True):
        """
        Setup Chrome WebDriver with appropriate options.
        
        Args:
            headless (bool): Whether to run browser in headless mode
        """
        try:
            chrome_options = Options()
            
            if headless:
                chrome_options.add_argument("--headless")
            
            # Additional options for better performance and stealth
            chrome_options.add_argument("--no-sandbox")
            chrome_options.add_argument("--disable-dev-shm-usage")
            chrome_options.add_argument("--disable-blink-features=AutomationControlled")
            chrome_options.add_experimental_option("excludeSwitches", ["enable-automation"])
            chrome_options.add_experimental_option('useAutomationExtension', False)
            chrome_options.add_argument("--user-agent=Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120.0.0.0 Safari/537.36")
            
            # Setup service with automatic driver management
            service = Service(ChromeDriverManager().install())
            
            # Initialize driver
            self.driver = webdriver.Chrome(service=service, options=chrome_options)
            self.driver.execute_script("Object.defineProperty(navigator, 'webdriver', {get: () => undefined})")
            
            # Setup wait object
            self.wait = WebDriverWait(self.driver, self.wait_time)
            
            logger.info("Chrome WebDriver initialized successfully")
            
        except Exception as e:
            logger.error(f"Failed to initialize WebDriver: {str(e)}")
            raise
    
    def navigate_to_bloomberg(self) -> bool:
        """
        Navigate to Bloomberg homepage.
        
        Returns:
            bool: True if successful, False otherwise
        """
        try:
            logger.info("Navigating to Bloomberg website...")
            self.driver.get("https://www.bloomberg.com/")
            
            # Wait for page to load
            self.wait.until(EC.presence_of_element_located((By.TAG_NAME, "body")))
            
            # Handle cookie consent if present
            self.handle_cookie_consent()
            
            logger.info("Successfully navigated to Bloomberg")
            return True
            
        except TimeoutException:
            logger.error("Timeout while loading Bloomberg page")
            return False
        except Exception as e:
            logger.error(f"Error navigating to Bloomberg: {str(e)}")
            return False
    
    def handle_cookie_consent(self):
        """
        Handle cookie consent popup if it appears.
        """
        try:
            # Common selectors for cookie consent buttons
            cookie_selectors = [
                "button[data-testid='cookie-consent-accept']",
                "button[class*='cookie']",
                "button[class*='consent']",
                "button[class*='accept']",
                "[data-testid='cookie-banner-accept']",
                ".cookie-consent button",
                "#cookie-consent button"
            ]
            
            for selector in cookie_selectors:
                try:
                    cookie_button = self.driver.find_element(By.CSS_SELECTOR, selector)
                    if cookie_button.is_displayed():
                        cookie_button.click()
                        logger.info("Cookie consent handled")
                        time.sleep(1)
                        break
                except NoSuchElementException:
                    continue
                    
        except Exception as e:
            logger.debug(f"Cookie consent handling failed: {str(e)}")
    
    def get_market_data(self) -> Dict[str, str]:
        """
        Extract market data from the top of the page.
        
        Returns:
            Dict[str, str]: Market data with indices and their values
        """
        market_data = {}
        
        try:
            logger.info("Extracting market data...")
            
            # Wait for market data to load
            time.sleep(3)
            
            # Get page source and parse with BeautifulSoup
            soup = BeautifulSoup(self.driver.page_source, 'html.parser')
            
            # Look for market data elements
            market_selectors = [
                "[data-testid*='market']",
                "[class*='market']",
                "[class*='index']",
                "[class*='quote']",
                ".market-data",
                ".market-indices"
            ]
            
            for selector in market_selectors:
                elements = soup.select(selector)
                for element in elements:
                    text = element.get_text(strip=True)
                    if text and any(char.isdigit() for char in text):
                        # Try to extract index name and value
                        parts = text.split()
                        if len(parts) >= 2:
                            market_data[parts[0]] = ' '.join(parts[1:])
            
            # Alternative approach: look for specific market indices
            market_indices = ['S&P 500', 'Nasdaq', 'Dow', 'FTSE', 'Nikkei']
            for index in market_indices:
                try:
                    element = self.driver.find_element(By.XPATH, f"//*[contains(text(), '{index}')]")
                    parent = element.find_element(By.XPATH, "./..")
                    market_data[index] = parent.text
                except NoSuchElementException:
                    continue
            
            logger.info(f"Extracted {len(market_data)} market data points")
            
        except Exception as e:
            logger.error(f"Error extracting market data: {str(e)}")
        
        return market_data
    
    def get_headlines(self) -> List[Dict[str, str]]:
        """
        Extract headlines from the main page.
        
        Returns:
            List[Dict[str, str]]: List of headlines with metadata
        """
        headlines = []
        
        try:
            logger.info("Extracting headlines...")
            
            # Wait for content to load
            time.sleep(3)
            
            soup = BeautifulSoup(self.driver.page_source, 'html.parser')
            
            # Common selectors for headlines
            headline_selectors = [
                "h1", "h2", "h3",
                "[data-testid*='headline']",
                "[class*='headline']",
                "[class*='story']",
                "a[href*='/news/']",
                ".story-package-module__story__headline",
                ".story-package-module__story__summary"
            ]
            
            for selector in headline_selectors:
                elements = soup.select(selector)
                for element in elements:
                    text = element.get_text(strip=True)
                    if text and len(text) > 20:  # Filter out short text
                        headline_data = {
                            'text': text,
                            'tag': element.name,
                            'class': element.get('class', []),
                            'href': element.get('href', ''),
                            'timestamp': datetime.now().isoformat()
                        }
                        headlines.append(headline_data)
            
            # Remove duplicates based on text content
            seen_texts = set()
            unique_headlines = []
            for headline in headlines:
                if headline['text'] not in seen_texts:
                    seen_texts.add(headline['text'])
                    unique_headlines.append(headline)
            
            headlines = unique_headlines[:20]  # Limit to top 20 headlines
            logger.info(f"Extracted {len(headlines)} unique headlines")
            
        except Exception as e:
            logger.error(f"Error extracting headlines: {str(e)}")
        
        return headlines
    
    def get_article_links(self) -> List[Dict[str, str]]:
        """
        Extract article links from the page.
        
        Returns:
            List[Dict[str, str]]: List of article links with metadata
        """
        article_links = []
        
        try:
            logger.info("Extracting article links...")
            
            # Find all links that look like articles
            links = self.driver.find_elements(By.CSS_SELECTOR, "a[href*='/news/'], a[href*='/markets/'], a[href*='/businessweek/']")
            
            for link in links[:15]:  # Limit to first 15 links
                try:
                    href = link.get_attribute('href')
                    text = link.text.strip()
                    
                    if href and text and len(text) > 10:
                        article_data = {
                            'title': text,
                            'url': href,
                            'timestamp': datetime.now().isoformat()
                        }
                        article_links.append(article_data)
                        
                except Exception as e:
                    logger.debug(f"Error processing link: {str(e)}")
                    continue
            
            logger.info(f"Extracted {len(article_links)} article links")
            
        except Exception as e:
            logger.error(f"Error extracting article links: {str(e)}")
        
        return article_links
    
    def scroll_and_load_more(self, scroll_count: int = 3):
        """
        Scroll down to load more content.
        
        Args:
            scroll_count (int): Number of times to scroll
        """
        try:
            logger.info(f"Scrolling {scroll_count} times to load more content...")
            
            for i in range(scroll_count):
                self.driver.execute_script("window.scrollTo(0, document.body.scrollHeight);")
                time.sleep(2)
                
                # Check if there's a "Load More" button and click it
                try:
                    load_more_button = self.driver.find_element(By.CSS_SELECTOR, 
                        "button[class*='load'], button[class*='more'], [data-testid*='load-more']")
                    if load_more_button.is_displayed():
                        self.driver.execute_script("arguments[0].click();", load_more_button)
                        time.sleep(2)
                except NoSuchElementException:
                    pass
            
            logger.info("Finished scrolling and loading content")
            
        except Exception as e:
            logger.error(f"Error during scrolling: {str(e)}")
    
    def scrape_all_data(self) -> Dict:
        """
        Scrape all available data from Bloomberg homepage.
        
        Returns:
            Dict: Complete scraped data
        """
        scraped_data = {
            'timestamp': datetime.now().isoformat(),
            'url': self.driver.current_url,
            'market_data': {},
            'headlines': [],
            'article_links': [],
            'page_title': '',
            'page_source_length': 0
        }
        
        try:
            # Get page title
            scraped_data['page_title'] = self.driver.title
            scraped_data['page_source_length'] = len(self.driver.page_source)
            
            # Extract different types of data
            scraped_data['market_data'] = self.get_market_data()
            scraped_data['headlines'] = self.get_headlines()
            scraped_data['article_links'] = self.get_article_links()
            
            # Scroll to load more content
            self.scroll_and_load_more()
            
            # Re-extract data after scrolling
            scraped_data['headlines'].extend(self.get_headlines())
            scraped_data['article_links'].extend(self.get_article_links())
            
            # Remove duplicates
            seen_headlines = set()
            unique_headlines = []
            for headline in scraped_data['headlines']:
                if headline['text'] not in seen_headlines:
                    seen_headlines.add(headline['text'])
                    unique_headlines.append(headline)
            scraped_data['headlines'] = unique_headlines
            
            seen_links = set()
            unique_links = []
            for link in scraped_data['article_links']:
                if link['url'] not in seen_links:
                    seen_links.add(link['url'])
                    unique_links.append(link)
            scraped_data['article_links'] = unique_links
            
            logger.info(f"Successfully scraped data: {len(scraped_data['headlines'])} headlines, "
                       f"{len(scraped_data['article_links'])} articles, "
                       f"{len(scraped_data['market_data'])} market data points")
            
        except Exception as e:
            logger.error(f"Error during data scraping: {str(e)}")
        
        return scraped_data
    
    def save_data(self, data: Dict, filename: str = None):
        """
        Save scraped data to JSON and CSV files.
        
        Args:
            data (Dict): Scraped data to save
            filename (str): Base filename (without extension)
        """
        if filename is None:
            timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
            filename = f"bloomberg_data_{timestamp}"
        
        try:
            # Save as JSON
            json_filename = f"{filename}.json"
            with open(json_filename, 'w', encoding='utf-8') as f:
                json.dump(data, f, indent=2, ensure_ascii=False)
            logger.info(f"Data saved to {json_filename}")
            
            # Save headlines as CSV
            if data['headlines']:
                headlines_df = pd.DataFrame(data['headlines'])
                csv_filename = f"{filename}_headlines.csv"
                headlines_df.to_csv(csv_filename, index=False, encoding='utf-8')
                logger.info(f"Headlines saved to {csv_filename}")
            
            # Save article links as CSV
            if data['article_links']:
                articles_df = pd.DataFrame(data['article_links'])
                csv_filename = f"{filename}_articles.csv"
                articles_df.to_csv(csv_filename, index=False, encoding='utf-8')
                logger.info(f"Article links saved to {csv_filename}")
            
            # Save market data as CSV
            if data['market_data']:
                market_df = pd.DataFrame(list(data['market_data'].items()), 
                                       columns=['Index', 'Value'])
                csv_filename = f"{filename}_market.csv"
                market_df.to_csv(csv_filename, index=False, encoding='utf-8')
                logger.info(f"Market data saved to {csv_filename}")
                
        except Exception as e:
            logger.error(f"Error saving data: {str(e)}")
    
    def close(self):
        """
        Close the WebDriver and cleanup resources.
        """
        if self.driver:
            self.driver.quit()
            logger.info("WebDriver closed successfully")

def main():
    """
    Main function to demonstrate Bloomberg scraping.
    """
    scraper = None
    
    try:
        # Initialize scraper (set headless=False to see browser)
        scraper = BloombergScraper(headless=True, wait_time=15)
        
        # Navigate to Bloomberg
        if not scraper.navigate_to_bloomberg():
            logger.error("Failed to navigate to Bloomberg")
            return
        
        # Scrape all data
        data = scraper.scrape_all_data()
        
        # Print summary
        print("\n" + "="*60)
        print("BLOOMBERG SCRAPING RESULTS")
        print("="*60)
        print(f"Page Title: {data['page_title']}")
        print(f"Scraped at: {data['timestamp']}")
        print(f"Market Data Points: {len(data['market_data'])}")
        print(f"Headlines: {len(data['headlines'])}")
        print(f"Article Links: {len(data['article_links'])}")
        
        # Display market data
        if data['market_data']:
            print("\nMARKET DATA:")
            print("-" * 30)
            for index, value in data['market_data'].items():
                print(f"{index}: {value}")
        
        # Display top headlines
        if data['headlines']:
            print(f"\nTOP {min(5, len(data['headlines']))} HEADLINES:")
            print("-" * 50)
            for i, headline in enumerate(data['headlines'][:5], 1):
                print(f"{i}. {headline['text']}")
        
        # Display top article links
        if data['article_links']:
            print(f"\nTOP {min(3, len(data['article_links']))} ARTICLE LINKS:")
            print("-" * 50)
            for i, article in enumerate(data['article_links'][:3], 1):
                print(f"{i}. {article['title']}")
                print(f"   URL: {article['url']}")
        
        # Save data to files
        scraper.save_data(data)
        
        print(f"\nData saved to files with timestamp: {data['timestamp']}")
        
    except Exception as e:
        logger.error(f"Error in main execution: {str(e)}")
    
    finally:
        if scraper:
            scraper.close()

if __name__ == "__main__":
    main()
