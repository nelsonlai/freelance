# Bloomberg Website Scraper

This project demonstrates how to crawl the Bloomberg website using Python Selenium. It includes both a comprehensive scraper and a simple example.

## Files

- `bloomberg_scraper.py` - Full-featured scraper with error handling and data export
- `bloomberg_scraper_simple.py` - Simple example for learning purposes
- `requirements_bloomberg.txt` - Required Python packages
- `README_bloomberg_scraper.md` - This documentation

## Features

### Full Scraper (`bloomberg_scraper.py`)
- ✅ Market data extraction
- ✅ Headlines scraping
- ✅ Article links collection
- ✅ Automatic scrolling and content loading
- ✅ Cookie consent handling
- ✅ Data export to JSON and CSV
- ✅ Comprehensive error handling and logging
- ✅ Configurable headless/visible browser mode

### Simple Scraper (`bloomberg_scraper_simple.py`)
- ✅ Basic page navigation
- ✅ Simple headline extraction
- ✅ Article link collection
- ✅ Minimal dependencies

## Installation

1. Install required packages:
```bash
pip install -r requirements_bloomberg.txt
```

2. Chrome browser must be installed on your system (Selenium will automatically download the ChromeDriver)

## Usage

### Full Scraper
```python
python bloomberg_scraper.py
```

### Simple Scraper
```python
python bloomberg_scraper_simple.py
```

### Custom Usage
```python
from bloomberg_scraper import BloombergScraper

# Initialize scraper
scraper = BloombergScraper(headless=False)  # Set to False to see browser

# Navigate and scrape
scraper.navigate_to_bloomberg()
data = scraper.scrape_all_data()

# Save data
scraper.save_data(data, "my_bloomberg_data")

# Cleanup
scraper.close()
```

## Output

The scraper generates several output files:
- `bloomberg_data_YYYYMMDD_HHMMSS.json` - Complete scraped data
- `bloomberg_data_YYYYMMDD_HHMMSS_headlines.csv` - Headlines data
- `bloomberg_data_YYYYMMDD_HHMMSS_articles.csv` - Article links
- `bloomberg_data_YYYYMMDD_HHMMSS_market.csv` - Market data
- `bloomberg_scraper.log` - Execution log

## Data Structure

### Market Data
```json
{
  "S&P 500": "6,631.96 +0.48%",
  "Nasdaq": "22,470.72 +0.94%",
  "Dow": "40,002.53 +0.51%"
}
```

### Headlines
```json
[
  {
    "text": "Trump's War on Media Reaches New Extreme With Kimmel Suspension",
    "tag": "h2",
    "class": ["headline-class"],
    "href": "/news/article/...",
    "timestamp": "2025-01-27T10:30:00"
  }
]
```

### Article Links
```json
[
  {
    "title": "Disney Executives to Meet With Kimmel, Assess Show's Future",
    "url": "https://www.bloomberg.com/news/articles/...",
    "timestamp": "2025-01-27T10:30:00"
  }
]
```

## Important Notes

### Legal and Ethical Considerations
- ✅ This scraper is for educational purposes
- ✅ Respect Bloomberg's robots.txt and terms of service
- ✅ Use reasonable delays between requests
- ✅ Don't overload their servers
- ✅ Consider using their official API for production use

### Technical Considerations
- The scraper handles dynamic content loading
- Cookie consent popups are automatically handled
- Market data extraction may vary based on page structure changes
- Some content may require JavaScript execution

### Troubleshooting
- If ChromeDriver issues occur, the script will automatically download the correct version
- For headless mode issues, try running with `headless=False` to debug
- Check the log file for detailed error information
- Ensure you have a stable internet connection

## Customization

You can customize the scraper by:
- Modifying selectors in the extraction methods
- Adding new data extraction methods
- Changing the scrolling behavior
- Adjusting wait times and delays
- Adding new output formats

## Dependencies

- `selenium` - Web browser automation
- `webdriver-manager` - Automatic driver management
- `beautifulsoup4` - HTML parsing
- `pandas` - Data manipulation
- `lxml` - XML/HTML parser
- `requests` - HTTP requests (optional)

## Browser Requirements

- Chrome browser (latest version recommended)
- ChromeDriver will be automatically downloaded and managed
