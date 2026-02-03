# Quick Start Guide

Get started with web scraping in 5 minutes!

## Installation

1. **Install Python 3.8+** (if not already installed)
   ```bash
   python --version  # Should be 3.8 or higher
   ```

2. **Install dependencies**
   ```bash
   pip install -r requirements.txt
   ```

## Your First Scrape (Beginner)

1. **Navigate to beginner examples**
   ```bash
   cd beginner
   ```

2. **Run your first scraper**
   ```bash
   python 01_basic_scraping.py
   ```

   You should see:
   - The HTML content of a webpage
   - The page title
   - Headings found on the page

3. **Try the other beginner examples**
   ```bash
   python 02_extract_links.py
   python 03_extract_text.py
   ```

## Next Steps

### For Beginners
1. Complete all 3 beginner examples
2. Read `beginner/README.md` for detailed explanations
3. Try the exercises in `beginner/exercises/`

### For Intermediate Users
1. Start with `intermediate/01_pagination.py`
2. Learn about forms, rate limiting, and data storage
3. Practice with intermediate exercises

### For Advanced Users
1. Set up Selenium (install ChromeDriver)
2. Try `advanced/01_selenium_basics.py`
3. Explore async scraping and Scrapy

## Common Issues

### Issue: "Module not found"
**Solution**: Make sure you've installed requirements:
```bash
pip install -r requirements.txt
```

### Issue: Selenium ChromeDriver error
**Solution**: Install ChromeDriver:
- macOS: `brew install chromedriver`
- Or download from: https://chromedriver.chromium.org/

### Issue: "Connection timeout"
**Solution**: 
- Check your internet connection
- The website might be down
- Try a different URL

## Learning Path

```
Beginner (Week 1)
├── Basic scraping
├── Extract links
└── Extract text

Intermediate (Week 2)
├── Pagination
├── Forms
├── Rate limiting
└── Data storage

Advanced (Week 3)
├── Selenium
├── Async scraping
├── Scrapy
└── Database integration
```

## Tips for Success

1. **Start simple**: Master the basics before moving to advanced topics
2. **Practice**: Try modifying the examples
3. **Read error messages**: They usually tell you what's wrong
4. **Be respectful**: Always add delays and check robots.txt
5. **Experiment**: Try scraping different websites

## Need Help?

- Check the README files in each level directory
- Review the code comments in examples
- Practice with the exercises
- Refer to official documentation for libraries

Happy scraping! 🕷️

