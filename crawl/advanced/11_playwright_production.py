"""
Advanced Playwright Example 3: Production-Ready Scraping
=========================================================

This example demonstrates:
- Error handling and retries
- Logging and monitoring
- Configuration management
- Data persistence
- Clean architecture
"""

from playwright.sync_api import sync_playwright, TimeoutError as PlaywrightTimeout
import logging
import json
import csv
from datetime import datetime
from typing import List, Dict, Optional
import time

# Configure logging
logging.basicConfig(
    level=logging.INFO,
    format='%(asctime)s - %(name)s - %(levelname)s - %(message)s'
)
logger = logging.getLogger(__name__)


class PlaywrightScraper:
    """Production-ready scraper with error handling and logging."""
    
    def __init__(self, headless=True, timeout=30000):
        """
        Initialize scraper.
        
        Args:
            headless: Run browser in headless mode
            timeout: Default timeout in milliseconds
        """
        self.headless = headless
        self.timeout = timeout
        self.playwright = None
        self.browser = None
    
    def __enter__(self):
        """Context manager entry."""
        self.playwright = sync_playwright().start()
        self.browser = self.playwright.chromium.launch(headless=self.headless)
        logger.info("Browser launched")
        return self
    
    def __exit__(self, exc_type, exc_val, exc_tb):
        """Context manager exit."""
        if self.browser:
            self.browser.close()
            logger.info("Browser closed")
        if self.playwright:
            self.playwright.stop()
    
    def scrape_with_retry(self, url: str, max_retries: int = 3, retry_delay: int = 2) -> Optional[object]:
        """
        Scrape a page with retry logic.
        
        Args:
            url: URL to scrape
            max_retries: Maximum number of retry attempts
            retry_delay: Delay between retries in seconds
            
        Returns:
            Page object or None if failed
        """
        for attempt in range(max_retries):
            try:
                page = self.browser.new_page()
                page.set_default_timeout(self.timeout)
                
                logger.info(f"Attempting to scrape: {url} (attempt {attempt + 1}/{max_retries})")
                page.goto(url, wait_until='networkidle')
                
                logger.info(f"Successfully loaded: {url}")
                return page
                
            except PlaywrightTimeout as e:
                logger.warning(f"Timeout on attempt {attempt + 1}: {e}")
                if page:
                    page.close()
                if attempt < max_retries - 1:
                    time.sleep(retry_delay)
                else:
                    logger.error(f"Failed to scrape {url} after {max_retries} attempts")
                    return None
                    
            except Exception as e:
                logger.error(f"Error on attempt {attempt + 1}: {e}")
                if page:
                    page.close()
                if attempt < max_retries - 1:
                    time.sleep(retry_delay)
                else:
                    return None
        
        return None


class QuotesScraper(PlaywrightScraper):
    """Specialized scraper for quotes.toscrape.com."""
    
    def __init__(self, **kwargs):
        super().__init__(**kwargs)
        self.base_url = "https://quotes.toscrape.com/"
    
    def scrape_page(self, url: str) -> List[Dict]:
        """
        Scrape quotes from a single page.
        
        Args:
            url: URL to scrape
            
        Returns:
            List of quote dictionaries
        """
        page = self.scrape_with_retry(url)
        
        if not page:
            return []
        
        try:
            quotes = page.locator('.quote').all()
            data = []
            
            for quote in quotes:
                try:
                    text = quote.locator('.text').text_content()
                    author = quote.locator('.author').text_content()
                    tags = quote.locator('.tag').all_text_contents()
                    
                    data.append({
                        'text': text.strip() if text else '',
                        'author': author.strip() if author else '',
                        'tags': ', '.join(tags),
                        'url': url,
                        'scraped_at': datetime.now().isoformat()
                    })
                except Exception as e:
                    logger.warning(f"Error extracting quote: {e}")
                    continue
            
            logger.info(f"Extracted {len(data)} quotes from {url}")
            return data
            
        except Exception as e:
            logger.error(f"Error scraping page {url}: {e}")
            return []
        finally:
            page.close()
    
    def scrape_multiple_pages(self, max_pages: int = 5) -> List[Dict]:
        """
        Scrape multiple pages.
        
        Args:
            max_pages: Maximum number of pages to scrape
            
        Returns:
            List of all quotes from all pages
        """
        all_quotes = []
        current_url = self.base_url
        page_num = 1
        
        logger.info(f"Starting multi-page scrape (max {max_pages} pages)")
        
        while page_num <= max_pages:
            # Scrape current page
            quotes = self.scrape_page(current_url)
            
            if not quotes:
                logger.warning(f"No quotes found on page {page_num}, stopping")
                break
            
            all_quotes.extend(quotes)
            logger.info(f"Page {page_num}: Found {len(quotes)} quotes (total: {len(all_quotes)})")
            
            # Check for next page
            try:
                page = self.browser.new_page()
                page.goto(current_url)
                page.wait_for_load_state('networkidle')
                
                next_button = page.get_by_text('Next', exact=False).first
                
                if not next_button.is_visible():
                    logger.info("No next page found, stopping")
                    page.close()
                    break
                
                next_button.click()
                page.wait_for_load_state('networkidle')
                current_url = page.url
                page.close()
                
                page_num += 1
                
                # Be respectful: add delay
                time.sleep(1)
                
            except Exception as e:
                logger.error(f"Error navigating to next page: {e}")
                break
        
        logger.info(f"Completed scraping: {len(all_quotes)} quotes from {page_num} pages")
        return all_quotes


class DataPersister:
    """Handle data persistence."""
    
    @staticmethod
    def save_json(data: List[Dict], filename: str):
        """Save data to JSON file."""
        with open(filename, 'w', encoding='utf-8') as f:
            json.dump(data, f, indent=2, ensure_ascii=False)
        logger.info(f"Saved {len(data)} items to {filename}")
    
    @staticmethod
    def save_csv(data: List[Dict], filename: str):
        """Save data to CSV file."""
        if not data:
            logger.warning("No data to save")
            return
        
        keys = data[0].keys()
        with open(filename, 'w', newline='', encoding='utf-8') as f:
            writer = csv.DictWriter(f, fieldnames=keys)
            writer.writeheader()
            writer.writerows(data)
        logger.info(f"Saved {len(data)} items to {filename}")


def production_scraping_example():
    """Demonstrate production-ready scraping."""
    print("="*60)
    print("PRODUCTION-READY SCRAPING EXAMPLE")
    print("="*60)
    
    # Create scraper with context manager
    with QuotesScraper(headless=True, timeout=30000) as scraper:
        # Scrape multiple pages
        quotes = scraper.scrape_multiple_pages(max_pages=3)
        
        # Save data
        if quotes:
            persister = DataPersister()
            timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
            
            json_file = f"quotes_production_{timestamp}.json"
            csv_file = f"quotes_production_{timestamp}.csv"
            
            persister.save_json(quotes, json_file)
            persister.save_csv(quotes, csv_file)
            
            # Display statistics
            print(f"\n✅ Scraping completed!")
            print(f"   Total quotes: {len(quotes)}")
            print(f"   Unique authors: {len(set(q['author'] for q in quotes))}")
            print(f"   Files saved:")
            print(f"     - {json_file}")
            print(f"     - {csv_file}")
            
            # Show sample
            if quotes:
                print(f"\n   Sample quotes:")
                for i, quote in enumerate(quotes[:3], 1):
                    print(f"\n   {i}. {quote['text'][:60]}...")
                    print(f"      Author: {quote['author']}")
        else:
            print("\n❌ No quotes scraped")


if __name__ == "__main__":
    production_scraping_example()
    
    print("\n" + "="*60)
    print("Production example completed!")
    print("="*60)
    print("\n💡 Production features demonstrated:")
    print("  ✅ Error handling with retries")
    print("  ✅ Logging for monitoring")
    print("  ✅ Context managers for resource cleanup")
    print("  ✅ Configuration options")
    print("  ✅ Data persistence")
    print("  ✅ Clean, maintainable code structure")
