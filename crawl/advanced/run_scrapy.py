"""
Helper script to run the Scrapy spider example.
This makes it easier to run without using the Scrapy CLI.
"""

import sys
from pathlib import Path

# Add the project root to the path
project_root = Path(__file__).parent.parent
sys.path.insert(0, str(project_root))

from scrapy.crawler import CrawlerProcess
from advanced.scrapy_example.quotes_spider import QuotesSpider

if __name__ == '__main__':
    process = CrawlerProcess({
        'USER_AGENT': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36',
        'DOWNLOAD_DELAY': 1,
        'RANDOMIZE_DOWNLOAD_DELAY': 0.5,
        'FEEDS': {
            'quotes_scrapy.json': {'format': 'json'},
        },
    })
    
    print("="*60)
    print("SCRAPY SPIDER EXAMPLE")
    print("="*60)
    print("\nRunning Scrapy spider...")
    print("This will scrape quotes from quotes.toscrape.com")
    print("Results will be saved to quotes_scrapy.json\n")
    
    process.crawl(QuotesSpider)
    process.start()
    
    print("\n" + "="*60)
    print("Scraping completed!")
    print("Check quotes_scrapy.json for results")
    print("="*60)

