"""
Advanced Example 3: Scrapy Spider
==================================

This is a Scrapy spider example. To run it:
1. Make sure Scrapy is installed: pip install scrapy
2. Run: scrapy crawl quotes -o quotes.json

Or use the run_scrapy.py script in the parent directory.
"""

import scrapy
from scrapy.crawler import CrawlerProcess


class QuotesSpider(scrapy.Spider):
    """A Scrapy spider to scrape quotes from quotes.toscrape.com"""
    
    name = 'quotes'
    start_urls = ['http://quotes.toscrape.com/']
    
    def parse(self, response):
        """Parse the quotes page."""
        # Extract all quotes on the page
        for quote in response.css('div.quote'):
            yield {
                'text': quote.css('span.text::text').get(),
                'author': quote.css('small.author::text').get(),
                'tags': quote.css('div.tags a.tag::text').getall(),
            }
        
        # Follow pagination links
        next_page = response.css('li.next a::attr(href)').get()
        if next_page:
            # Follow the next page link
            yield response.follow(next_page, self.parse)


class QuotesSpiderWithItems(scrapy.Spider):
    """
    A more advanced Scrapy spider using Items.
    This demonstrates best practices with Scrapy.
    """
    
    name = 'quotes_advanced'
    allowed_domains = ['quotes.toscrape.com']
    start_urls = ['http://quotes.toscrape.com/']
    
    custom_settings = {
        'DOWNLOAD_DELAY': 1,  # Be respectful: 1 second delay
        'RANDOMIZE_DOWNLOAD_DELAY': 0.5,  # Randomize delay
        'CONCURRENT_REQUESTS': 1,  # One request at a time
    }
    
    def parse(self, response):
        """Parse the quotes page."""
        for quote in response.css('div.quote'):
            yield {
                'text': quote.css('span.text::text').get(),
                'author': quote.css('small.author::text').get(),
                'tags': ', '.join(quote.css('div.tags a.tag::text').getall()),
                'url': response.url,
            }
        
        # Follow pagination
        next_page = response.css('li.next a::attr(href)').get()
        if next_page:
            yield response.follow(next_page, self.parse)


# This allows running the spider directly
if __name__ == '__main__':
    process = CrawlerProcess({
        'USER_AGENT': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36',
        'FEEDS': {
            'quotes.json': {'format': 'json'},
        },
    })
    
    process.crawl(QuotesSpider)
    process.start()

