"""
Advanced Example 2: Asynchronous Scraping
==========================================

This example demonstrates:
- How to scrape multiple pages concurrently using asyncio
- How to use aiohttp for async HTTP requests
- How to control concurrency
- How to handle errors in async context
"""

import asyncio
import aiohttp
from bs4 import BeautifulSoup
import time
from typing import List, Dict

class AsyncScraper:
    """A scraper that uses async/await for concurrent requests."""
    
    def __init__(self, max_concurrent=5):
        """
        Initialize the async scraper.
        
        Args:
            max_concurrent: Maximum number of concurrent requests
        """
        self.max_concurrent = max_concurrent
        self.semaphore = asyncio.Semaphore(max_concurrent)
        self.session = None
    
    async def create_session(self):
        """Create an aiohttp session."""
        self.session = aiohttp.ClientSession(
            timeout=aiohttp.ClientTimeout(total=10),
            headers={'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36'}
        )
    
    async def close_session(self):
        """Close the aiohttp session."""
        if self.session:
            await self.session.close()
    
    async def fetch_page(self, url: str) -> Dict:
        """
        Fetch a single page.
        
        Args:
            url: URL to fetch
            
        Returns:
            Dictionary with page data or error information
        """
        async with self.semaphore:  # Limit concurrent requests
            try:
                async with self.session.get(url) as response:
                    if response.status == 200:
                        html = await response.text()
                        soup = BeautifulSoup(html, 'html.parser')
                        
                        # Extract basic information
                        title = soup.find('title')
                        title_text = title.text.strip() if title else "No title"
                        
                        # Count elements
                        paragraphs = len(soup.find_all('p'))
                        links = len(soup.find_all('a', href=True))
                        
                        return {
                            'url': url,
                            'status': 'success',
                            'title': title_text,
                            'paragraphs': paragraphs,
                            'links': links
                        }
                    else:
                        return {
                            'url': url,
                            'status': 'error',
                            'error': f'HTTP {response.status}'
                        }
            except asyncio.TimeoutError:
                return {
                    'url': url,
                    'status': 'error',
                    'error': 'Timeout'
                }
            except Exception as e:
                return {
                    'url': url,
                    'status': 'error',
                    'error': str(e)
                }
    
    async def scrape_multiple(self, urls: List[str]) -> List[Dict]:
        """
        Scrape multiple URLs concurrently.
        
        Args:
            urls: List of URLs to scrape
            
        Returns:
            List of results
        """
        await self.create_session()
        
        try:
            # Create tasks for all URLs
            tasks = [self.fetch_page(url) for url in urls]
            
            # Execute all tasks concurrently
            results = await asyncio.gather(*tasks)
            
            return results
        finally:
            await self.close_session()


async def demonstrate_async_scraping():
    """Demonstrate async scraping with multiple URLs."""
    print("="*60)
    print("ASYNCHRONOUS SCRAPING EXAMPLE")
    print("="*60)
    
    # Example URLs (using httpbin.org for demonstration)
    urls = [
        "https://httpbin.org/html",
        "https://httpbin.org/json",
        "https://httpbin.org/xml",
        "https://httpbin.org/uuid",
        "https://httpbin.org/base64/SFRUUEJJTiBpcyBhd2Vzb21l",
        "https://httpbin.org/delay/1",
        "https://httpbin.org/delay/2",
        "https://httpbin.org/status/200",
    ]
    
    print(f"\nScraping {len(urls)} URLs")
    print(f"Max concurrent requests: 5")
    
    # Time the operation
    start_time = time.time()
    
    scraper = AsyncScraper(max_concurrent=5)
    results = await scraper.scrape_multiple(urls)
    
    elapsed_time = time.time() - start_time
    
    # Display results
    print("\n" + "="*60)
    print("RESULTS")
    print("="*60)
    
    successful = sum(1 for r in results if r['status'] == 'success')
    failed = len(results) - successful
    
    print(f"\n✅ Successful: {successful}/{len(results)}")
    print(f"❌ Failed: {failed}/{len(results)}")
    print(f"⏱️  Total time: {elapsed_time:.2f} seconds")
    print(f"⚡ Average time per URL: {elapsed_time/len(urls):.2f} seconds")
    
    print(f"\nDetailed results:")
    for i, result in enumerate(results, 1):
        if result['status'] == 'success':
            print(f"\n{i}. ✅ {result['url']}")
            print(f"   Title: {result.get('title', 'N/A')[:50]}")
            print(f"   Paragraphs: {result.get('paragraphs', 0)}")
            print(f"   Links: {result.get('links', 0)}")
        else:
            print(f"\n{i}. ❌ {result['url']}")
            print(f"   Error: {result.get('error', 'Unknown error')}")
    
    return results


async def compare_sync_vs_async():
    """Compare synchronous vs asynchronous scraping."""
    print("\n" + "="*60)
    print("SYNC VS ASYNC COMPARISON")
    print("="*60)
    
    urls = [
        "https://httpbin.org/delay/1",
        "https://httpbin.org/delay/1",
        "https://httpbin.org/delay/1",
        "https://httpbin.org/delay/1",
        "https://httpbin.org/delay/1",
    ]
    
    # Async version
    print("\n1. Async version (concurrent):")
    start = time.time()
    scraper = AsyncScraper(max_concurrent=5)
    await scraper.create_session()
    tasks = [scraper.fetch_page(url) for url in urls]
    await asyncio.gather(*tasks)
    await scraper.close_session()
    async_time = time.time() - start
    print(f"   Time: {async_time:.2f} seconds")
    
    # Note: For true sync comparison, we'd use requests, but that's slower
    print("\n2. Sync version (sequential):")
    print("   (Would take ~5 seconds for 5 URLs with 1s delay each)")
    print(f"   Estimated time: ~{len(urls) * 1:.2f} seconds")
    
    print(f"\n⚡ Speed improvement: ~{len(urls) * 1 / async_time:.1f}x faster with async!")


if __name__ == "__main__":
    # Run the async examples
    print("Running async scraping examples...\n")
    
    # Example 1: Basic async scraping
    results = asyncio.run(demonstrate_async_scraping())
    
    # Example 2: Comparison
    asyncio.run(compare_sync_vs_async())
    
    print("\n" + "="*60)
    print("Example completed!")
    print("="*60)
    print("\n💡 Benefits of async scraping:")
    print("  - Much faster for multiple URLs")
    print("  - Better resource utilization")
    print("  - Can handle hundreds of URLs efficiently")
    print("  - Still respects rate limits with semaphores")

