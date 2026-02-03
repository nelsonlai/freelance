# Scrapy Example

This directory contains a Scrapy spider example.

## Running the Spider

### Method 1: Using Scrapy CLI

```bash
# Navigate to this directory
cd advanced/03_scrapy_example

# Run the spider
scrapy crawl quotes -o quotes.json

# Or run the advanced version
scrapy crawl quotes_advanced -o quotes_advanced.json
```

### Method 2: Using Python Script

```bash
# From the project root
python advanced/03_scrapy_example/quotes_spider.py
```

### Method 3: Using the Helper Script

```bash
# From the project root
python advanced/run_scrapy.py
```

## Scrapy Features Demonstrated

1. **CSS Selectors**: Using Scrapy's CSS selector syntax
2. **Pagination**: Following links to next pages
3. **Items**: Structured data extraction
4. **Settings**: Custom settings for rate limiting
5. **Output**: Saving to JSON, CSV, or other formats

## Scrapy vs Other Methods

**Advantages:**
- Built-in request scheduling
- Automatic retry mechanisms
- Middleware support
- Item pipelines for data processing
- Excellent for large-scale scraping

**When to use:**
- Large-scale scraping projects
- Need for structured data pipelines
- Complex crawling requirements
- Production scraping systems

## Next Steps

- Learn about Scrapy Items and ItemLoaders
- Explore Scrapy Middleware
- Build custom pipelines
- Set up Scrapy projects with multiple spiders

