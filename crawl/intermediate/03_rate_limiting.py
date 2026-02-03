"""
Intermediate Example 3: Rate Limiting and Respectful Scraping
==============================================================

This example demonstrates:
- How to add delays between requests
- How to respect robots.txt
- How to implement exponential backoff for retries
- How to use random delays to appear more human-like
"""

import requests
from bs4 import BeautifulSoup
import time
import random
from urllib.robotparser import RobotFileParser
from urllib.parse import urlparse

class RespectfulScraper:
    """
    A scraper class that implements rate limiting and respects robots.txt
    """
    
    def __init__(self, base_url, delay_range=(1, 3)):
        """
        Initialize the scraper.
        
        Args:
            base_url: Base URL of the website
            delay_range: Tuple of (min, max) seconds to wait between requests
        """
        self.base_url = base_url
        self.delay_range = delay_range
        self.robots_parser = None
        self.last_request_time = 0
        
        # Parse robots.txt
        self._parse_robots_txt()
        
        # Headers to mimic a real browser
        self.headers = {
            'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36'
        }
    
    def _parse_robots_txt(self):
        """Parse and cache robots.txt for the website."""
        try:
            parsed_url = urlparse(self.base_url)
            robots_url = f"{parsed_url.scheme}://{parsed_url.netloc}/robots.txt"
            
            print(f"Checking robots.txt: {robots_url}")
            
            self.robots_parser = RobotFileParser()
            self.robots_parser.set_url(robots_url)
            self.robots_parser.read()
            
            # Check if we can fetch the base URL
            if self.robots_parser.can_fetch('*', self.base_url):
                print("✅ robots.txt allows scraping")
            else:
                print("⚠️  robots.txt may restrict scraping")
                
        except Exception as e:
            print(f"⚠️  Could not parse robots.txt: {e}")
            print("   Proceeding with caution...")
    
    def _wait_between_requests(self):
        """Wait a random amount of time between requests."""
        # Calculate time since last request
        time_since_last = time.time() - self.last_request_time
        
        # Random delay within specified range
        delay = random.uniform(*self.delay_range)
        
        # If we haven't waited long enough, wait the remaining time
        if time_since_last < delay:
            wait_time = delay - time_since_last
            print(f"  Waiting {wait_time:.2f} seconds (rate limiting)...")
            time.sleep(wait_time)
        
        self.last_request_time = time.time()
    
    def can_fetch(self, url):
        """Check if we can fetch a URL according to robots.txt."""
        if self.robots_parser:
            return self.robots_parser.can_fetch('*', url)
        return True
    
    def get(self, url, max_retries=3, backoff_factor=2):
        """
        Make a GET request with retry logic and rate limiting.
        
        Args:
            url: URL to fetch
            max_retries: Maximum number of retry attempts
            backoff_factor: Multiplier for exponential backoff
        """
        # Check robots.txt
        if not self.can_fetch(url):
            print(f"⚠️  robots.txt disallows: {url}")
            return None
        
        # Rate limiting
        self._wait_between_requests()
        
        # Retry logic with exponential backoff
        for attempt in range(max_retries):
            try:
                print(f"Fetching: {url} (attempt {attempt + 1})")
                response = requests.get(url, headers=self.headers, timeout=10)
                response.raise_for_status()
                return response
                
            except requests.exceptions.RequestException as e:
                if attempt < max_retries - 1:
                    wait_time = backoff_factor ** attempt
                    print(f"  Error: {e}")
                    print(f"  Retrying in {wait_time} seconds...")
                    time.sleep(wait_time)
                else:
                    print(f"  ❌ Failed after {max_retries} attempts: {e}")
                    return None
        
        return None
    
    def scrape_multiple_pages(self, urls):
        """
        Scrape multiple URLs with rate limiting.
        
        Args:
            urls: List of URLs to scrape
        """
        results = []
        
        print(f"\nScraping {len(urls)} pages with rate limiting...")
        print(f"Delay range: {self.delay_range[0]}-{self.delay_range[1]} seconds\n")
        
        for i, url in enumerate(urls, 1):
            print(f"[{i}/{len(urls)}] ", end="")
            response = self.get(url)
            
            if response:
                soup = BeautifulSoup(response.text, 'html.parser')
                title = soup.find('title')
                title_text = title.text.strip() if title else "No title"
                results.append({
                    'url': url,
                    'title': title_text,
                    'status': 'success'
                })
                print(f"✅ Success: {title_text[:50]}")
            else:
                results.append({
                    'url': url,
                    'title': None,
                    'status': 'failed'
                })
                print(f"❌ Failed")
        
        return results


def demonstrate_rate_limiting():
    """Demonstrate rate limiting with multiple requests."""
    
    # Example URLs (using httpbin.org for demonstration)
    base_url = "https://httpbin.org"
    urls = [
        f"{base_url}/html",
        f"{base_url}/json",
        f"{base_url}/xml",
    ]
    
    print("="*60)
    print("RATE LIMITING DEMONSTRATION")
    print("="*60)
    
    # Create scraper with 1-3 second delays
    scraper = RespectfulScraper(base_url, delay_range=(1, 3))
    
    # Scrape multiple pages
    results = scraper.scrape_multiple_pages(urls)
    
    # Summary
    print("\n" + "="*60)
    print("SUMMARY")
    print("="*60)
    successful = sum(1 for r in results if r['status'] == 'success')
    print(f"Successful: {successful}/{len(results)}")
    print(f"Failed: {len(results) - successful}/{len(results)}")
    
    return results


if __name__ == "__main__":
    results = demonstrate_rate_limiting()
    
    print("\n" + "="*60)
    print("Example completed!")
    print("="*60)
    print("\n💡 Tips for respectful scraping:")
    print("  1. Always check robots.txt")
    print("  2. Add delays between requests")
    print("  3. Use exponential backoff for retries")
    print("  4. Set a reasonable User-Agent header")
    print("  5. Don't scrape too frequently")
    print("  6. Respect the website's terms of service")

