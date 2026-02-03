# ==============================================================================
# Advanced Bloomberg Scraper with Anti-Detection Features
# ==============================================================================
# This version includes better anti-detection measures and alternative approaches
# to handle Bloomberg's bot detection systems.

import time
import random
import json
from datetime import datetime
from typing import List, Dict, Optional

from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.chrome.service import Service
from selenium.webdriver.chrome.options import Options
from selenium.webdriver.common.action_chains import ActionChains
from selenium.common.exceptions import TimeoutException, NoSuchElementException
from webdriver_manager.chrome import ChromeDriverManager
from bs4 import BeautifulSoup
import requests
import pandas as pd

class AdvancedBloombergScraper:
    """
    Advanced Bloomberg scraper with anti-detection features.
    """
    
    def __init__(self, headless: bool = False, wait_time: int = 15):
        """
        Initialize the advanced Bloomberg scraper.
        
        Args:
            headless (bool): Whether to run browser in headless mode
            wait_time (int): Maximum wait time for elements to load
        """
        self.wait_time = wait_time
        self.driver = None
        self.wait = None
        self.setup_stealth_driver(headless)
    
    def setup_stealth_driver(self, headless: bool = False):
        """
        Setup Chrome WebDriver with advanced stealth options.
        """
        try:
            chrome_options = Options()
            
            if headless:
                chrome_options.add_argument("--headless=new")
            
            # Advanced stealth options
            chrome_options.add_argument("--no-sandbox")
            chrome_options.add_argument("--disable-dev-shm-usage")
            chrome_options.add_argument("--disable-blink-features=AutomationControlled")
            chrome_options.add_argument("--disable-extensions")
            chrome_options.add_argument("--disable-plugins")
            chrome_options.add_argument("--disable-images")  # Faster loading
            chrome_options.add_argument("--disable-javascript")  # May help avoid detection
            
            # User agent rotation
            user_agents = [
                "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120.0.0.0 Safari/537.36",
                "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120.0.0.0 Safari/537.36",
                "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120.0.0.0 Safari/537.36"
            ]
            chrome_options.add_argument(f"--user-agent={random.choice(user_agents)}")
            
            # Additional stealth settings
            chrome_options.add_experimental_option("excludeSwitches", ["enable-automation"])
            chrome_options.add_experimental_option('useAutomationExtension', False)
            chrome_options.add_argument("--disable-web-security")
            chrome_options.add_argument("--allow-running-insecure-content")
            
            # Setup service
            service = Service(ChromeDriverManager().install())
            
            # Initialize driver
            self.driver = webdriver.Chrome(service=service, options=chrome_options)
            
            # Execute stealth scripts
            self.driver.execute_script("Object.defineProperty(navigator, 'webdriver', {get: () => undefined})")
            self.driver.execute_cdp_cmd('Network.setUserAgentOverride', {
                "userAgent": random.choice(user_agents)
            })
            
            # Setup wait object
            self.wait = WebDriverWait(self.driver, self.wait_time)
            
            print("Advanced Chrome WebDriver initialized successfully")
            
        except Exception as e:
            print(f"Failed to initialize WebDriver: {str(e)}")
            raise
    
    def human_like_delay(self, min_delay: float = 1.0, max_delay: float = 3.0):
        """
        Add human-like delays between actions.
        """
        delay = random.uniform(min_delay, max_delay)
        time.sleep(delay)
    
    def human_like_scroll(self):
        """
        Perform human-like scrolling behavior.
        """
        try:
            # Random scroll patterns
            scroll_actions = [
                lambda: self.driver.execute_script("window.scrollTo(0, document.body.scrollHeight/4);"),
                lambda: self.driver.execute_script("window.scrollTo(0, document.body.scrollHeight/2);"),
                lambda: self.driver.execute_script("window.scrollTo(0, document.body.scrollHeight);"),
                lambda: self.driver.execute_script("window.scrollTo(0, 0);")
            ]
            
            for action in random.sample(scroll_actions, 2):
                action()
                self.human_like_delay(0.5, 1.5)
                
        except Exception as e:
            print(f"Error during human-like scrolling: {str(e)}")
    
    def try_alternative_approach(self) -> Dict:
        """
        Try alternative approach using requests + BeautifulSoup.
        """
        print("Trying alternative approach with requests...")
        
        headers = {
            'User-Agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120.0.0.0 Safari/537.36',
            'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8',
            'Accept-Language': 'en-US,en;q=0.5',
            'Accept-Encoding': 'gzip, deflate',
            'Connection': 'keep-alive',
            'Upgrade-Insecure-Requests': '1',
        }
        
        try:
            response = requests.get("https://www.bloomberg.com/", headers=headers, timeout=10)
            response.raise_for_status()
            
            soup = BeautifulSoup(response.content, 'html.parser')
            
            # Extract basic information
            data = {
                'timestamp': datetime.now().isoformat(),
                'method': 'requests',
                'status_code': response.status_code,
                'title': soup.title.string if soup.title else 'No title',
                'headlines': [],
                'links': []
            }
            
            # Extract headlines
            for tag in ['h1', 'h2', 'h3']:
                elements = soup.find_all(tag)
                for element in elements:
                    text = element.get_text(strip=True)
                    if text and len(text) > 10:
                        data['headlines'].append({
                            'text': text,
                            'tag': tag,
                            'timestamp': datetime.now().isoformat()
                        })
            
            # Extract links
            links = soup.find_all('a', href=True)
            for link in links[:20]:  # Limit to first 20 links
                href = link.get('href')
                text = link.get_text(strip=True)
                if href and text and len(text) > 5:
                    data['links'].append({
                        'text': text,
                        'url': href,
                        'timestamp': datetime.now().isoformat()
                    })
            
            print(f"Alternative approach successful: {len(data['headlines'])} headlines, {len(data['links'])} links")
            return data
            
        except Exception as e:
            print(f"Alternative approach failed: {str(e)}")
            return {'error': str(e), 'method': 'requests'}
    
    def scrape_with_selenium(self) -> Dict:
        """
        Scrape using Selenium with anti-detection measures.
        """
        print("Attempting Selenium scraping with anti-detection...")
        
        try:
            # Navigate to Bloomberg
            print("Navigating to Bloomberg...")
            self.driver.get("https://www.bloomberg.com/")
            
            # Human-like delay
            self.human_like_delay(3, 5)
            
            # Check if we're blocked
            if "robot" in self.driver.title.lower() or "unusual activity" in self.driver.page_source.lower():
                print("Bot detection triggered. Trying alternative approach...")
                return self.try_alternative_approach()
            
            # Human-like scrolling
            self.human_like_scroll()
            
            # Extract data
            data = {
                'timestamp': datetime.now().isoformat(),
                'method': 'selenium',
                'title': self.driver.title,
                'url': self.driver.current_url,
                'headlines': [],
                'links': []
            }
            
            # Extract headlines
            soup = BeautifulSoup(self.driver.page_source, 'html.parser')
            for tag in ['h1', 'h2', 'h3']:
                elements = soup.find_all(tag)
                for element in elements:
                    text = element.get_text(strip=True)
                    if text and len(text) > 10:
                        data['headlines'].append({
                            'text': text,
                            'tag': tag,
                            'timestamp': datetime.now().isoformat()
                        })
            
            # Extract links
            links = soup.find_all('a', href=True)
            for link in links[:20]:
                href = link.get('href')
                text = link.get_text(strip=True)
                if href and text and len(text) > 5:
                    data['links'].append({
                        'text': text,
                        'url': href,
                        'timestamp': datetime.now().isoformat()
                    })
            
            print(f"Selenium scraping successful: {len(data['headlines'])} headlines, {len(data['links'])} links")
            return data
            
        except Exception as e:
            print(f"Selenium scraping failed: {str(e)}")
            return {'error': str(e), 'method': 'selenium'}
    
    def scrape_bloomberg(self) -> Dict:
        """
        Main scraping method that tries multiple approaches.
        """
        print("Starting Bloomberg scraping with multiple approaches...")
        
        # Try Selenium first
        selenium_result = self.scrape_with_selenium()
        
        # If Selenium fails or gets blocked, try requests
        if 'error' in selenium_result or selenium_result.get('method') == 'requests':
            print("Selenium approach failed, trying requests approach...")
            requests_result = self.try_alternative_approach()
            
            # Return the better result
            if 'error' not in requests_result:
                return requests_result
            else:
                return selenium_result
        
        return selenium_result
    
    def save_results(self, data: Dict, filename: str = None):
        """
        Save scraping results to files.
        """
        if filename is None:
            timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
            filename = f"bloomberg_advanced_{timestamp}"
        
        try:
            # Save as JSON
            json_filename = f"{filename}.json"
            with open(json_filename, 'w', encoding='utf-8') as f:
                json.dump(data, f, indent=2, ensure_ascii=False)
            print(f"Results saved to {json_filename}")
            
            # Save headlines as CSV if available
            if data.get('headlines'):
                headlines_df = pd.DataFrame(data['headlines'])
                csv_filename = f"{filename}_headlines.csv"
                headlines_df.to_csv(csv_filename, index=False, encoding='utf-8')
                print(f"Headlines saved to {csv_filename}")
            
            # Save links as CSV if available
            if data.get('links'):
                links_df = pd.DataFrame(data['links'])
                csv_filename = f"{filename}_links.csv"
                links_df.to_csv(csv_filename, index=False, encoding='utf-8')
                print(f"Links saved to {csv_filename}")
                
        except Exception as e:
            print(f"Error saving results: {str(e)}")
    
    def close(self):
        """
        Close the WebDriver.
        """
        if self.driver:
            self.driver.quit()
            print("WebDriver closed")

def main():
    """
    Main function to demonstrate advanced Bloomberg scraping.
    """
    scraper = None
    
    try:
        # Initialize scraper (set headless=True for background operation)
        scraper = AdvancedBloombergScraper(headless=False, wait_time=20)
        
        # Scrape Bloomberg
        data = scraper.scrape_bloomberg()
        
        # Print results
        print("\n" + "="*60)
        print("ADVANCED BLOOMBERG SCRAPING RESULTS")
        print("="*60)
        print(f"Method used: {data.get('method', 'unknown')}")
        print(f"Title: {data.get('title', 'No title')}")
        print(f"Timestamp: {data.get('timestamp', 'No timestamp')}")
        
        if 'error' in data:
            print(f"Error: {data['error']}")
        else:
            print(f"Headlines found: {len(data.get('headlines', []))}")
            print(f"Links found: {len(data.get('links', []))}")
            
            # Display sample headlines
            if data.get('headlines'):
                print(f"\nSample Headlines:")
                print("-" * 40)
                for i, headline in enumerate(data['headlines'][:5], 1):
                    print(f"{i}. {headline['text']}")
            
            # Display sample links
            if data.get('links'):
                print(f"\nSample Links:")
                print("-" * 40)
                for i, link in enumerate(data['links'][:3], 1):
                    print(f"{i}. {link['text']}")
                    print(f"   URL: {link['url']}")
        
        # Save results
        scraper.save_results(data)
        
    except Exception as e:
        print(f"Error in main execution: {str(e)}")
    
    finally:
        if scraper:
            scraper.close()

if __name__ == "__main__":
    main()
