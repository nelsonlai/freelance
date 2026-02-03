"""
Advanced Playwright Example 1: Async/Await with Playwright
===========================================================

This example demonstrates:
- Asynchronous Playwright operations
- Concurrent scraping
- Parallel browser instances
- Performance optimization
"""

from playwright.async_api import async_playwright
import asyncio
import time

async def async_basic_example():
    """Basic async example."""
    async with async_playwright() as p:
        print("="*60)
        print("ASYNC BASIC EXAMPLE")
        print("="*60)
        
        browser = await p.chromium.launch(headless=True)
        page = await browser.new_page()
        
        url = "https://quotes.toscrape.com/"
        print(f"\n1. Opening: {url}")
        
        await page.goto(url)
        await page.wait_for_load_state('networkidle')
        
        # Extract data asynchronously
        quotes = await page.locator('.quote').all()
        print(f"2. ✅ Found {len(quotes)} quotes (async)")
        
        if quotes:
            text = await quotes[0].locator('.text').text_content()
            author = await quotes[0].locator('.author').text_content()
            print(f"\n3. First quote:")
            print(f"   {text[:50]}...")
            print(f"   - {author}")
        
        await browser.close()


async def scrape_single_page(url, page):
    """Scrape a single page asynchronously."""
    await page.goto(url)
    await page.wait_for_load_state('networkidle')
    
    quotes = await page.locator('.quote').all()
    
    data = []
    for quote in quotes:
        text = await quote.locator('.text').text_content()
        author = await quote.locator('.author').text_content()
        tags = await quote.locator('.tag').all_text_contents()
        
        data.append({
            'url': url,
            'text': text,
            'author': author,
            'tags': ', '.join(tags)
        })
    
    return data


async def concurrent_scraping_example():
    """Scrape multiple pages concurrently."""
    async with async_playwright() as p:
        print("\n" + "="*60)
        print("CONCURRENT SCRAPING EXAMPLE")
        print("="*60)
        
        browser = await p.chromium.launch(headless=True)
        
        urls = [
            "https://quotes.toscrape.com/",
            "https://quotes.toscrape.com/page/2/",
            "https://quotes.toscrape.com/page/3/",
        ]
        
        print(f"\n1. Scraping {len(urls)} pages concurrently...")
        
        # Create multiple pages (tabs)
        pages = [await browser.new_page() for _ in urls]
        
        # Scrape all pages concurrently
        start_time = time.time()
        tasks = [scrape_single_page(url, page) for url, page in zip(urls, pages)]
        results = await asyncio.gather(*tasks)
        elapsed_time = time.time() - start_time
        
        # Close all pages
        for page in pages:
            await page.close()
        
        await browser.close()
        
        # Combine results
        all_data = []
        for result in results:
            all_data.extend(result)
        
        print(f"\n2. ✅ Scraped {len(all_data)} quotes from {len(urls)} pages")
        print(f"   Time: {elapsed_time:.2f} seconds")
        print(f"   Average: {elapsed_time/len(urls):.2f} seconds per page")
        
        return all_data


async def parallel_browsers_example():
    """Use multiple browser instances in parallel."""
    async with async_playwright() as p:
        print("\n" + "="*60)
        print("PARALLEL BROWSERS EXAMPLE")
        print("="*60)
        
        urls = [
            "https://quotes.toscrape.com/",
            "https://quotes.toscrape.com/page/2/",
            "https://quotes.toscrape.com/page/3/",
        ]
        
        print(f"\n1. Creating {len(urls)} browser instances...")
        
        async def scrape_with_browser(url):
            """Scrape with a dedicated browser instance."""
            browser = await p.chromium.launch(headless=True)
            page = await browser.new_page()
            
            await page.goto(url)
            await page.wait_for_load_state('networkidle')
            
            count = await page.locator('.quote').count()
            title = await page.title()
            
            await browser.close()
            
            return {
                'url': url,
                'title': title,
                'quote_count': count
            }
        
        # Scrape with parallel browsers
        start_time = time.time()
        tasks = [scrape_with_browser(url) for url in urls]
        results = await asyncio.gather(*tasks)
        elapsed_time = time.time() - start_time
        
        print(f"\n2. ✅ Results:")
        for result in results:
            print(f"   {result['url']}: {result['quote_count']} quotes")
        
        print(f"\n   Time: {elapsed_time:.2f} seconds")
        print(f"   Average: {elapsed_time/len(urls):.2f} seconds per page")
        
        return results


async def compare_sync_vs_async():
    """Compare sync vs async performance."""
    print("\n" + "="*60)
    print("SYNC VS ASYNC COMPARISON")
    print("="*60)
    
    urls = [
        "https://quotes.toscrape.com/",
        "https://quotes.toscrape.com/page/2/",
        "https://quotes.toscrape.com/page/3/",
    ]
    
    # Async version
    print("\n1. Async version (concurrent):")
    start = time.time()
    async with async_playwright() as p:
        browser = await p.chromium.launch(headless=True)
        pages = [await browser.new_page() for _ in urls]
        tasks = [scrape_single_page(url, page) for url, page in zip(urls, pages)]
        await asyncio.gather(*tasks)
        for page in pages:
            await page.close()
        await browser.close()
    async_time = time.time() - start
    print(f"   Time: {async_time:.2f} seconds")
    
    # Estimated sync time
    print("\n2. Sync version (sequential):")
    print(f"   Estimated time: ~{len(urls) * 2:.2f} seconds (2 seconds per page)")
    
    print(f"\n⚡ Speed improvement: ~{len(urls) * 2 / async_time:.1f}x faster with async!")


async def main():
    """Run all async examples."""
    await async_basic_example()
    await concurrent_scraping_example()
    await parallel_browsers_example()
    await compare_sync_vs_async()
    
    print("\n" + "="*60)
    print("All async examples completed!")
    print("="*60)
    print("\n💡 Key points:")
    print("  - Use async/await for better performance")
    print("  - asyncio.gather() for concurrent operations")
    print("  - Multiple pages = faster than sequential")
    print("  - Multiple browsers = even faster (more resources)")


if __name__ == "__main__":
    asyncio.run(main())
