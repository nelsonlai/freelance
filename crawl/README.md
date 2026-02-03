# Web Crawling Tutorial: From Beginner to Advanced

This repository contains comprehensive teaching materials and Python code examples for learning web crawling at three different levels.

## 📚 Course Structure

### 🟢 Beginner Level
- Introduction to web scraping concepts
- Basic HTML parsing with BeautifulSoup
- Simple data extraction
- **Prerequisites**: Basic Python knowledge

### 🟡 Intermediate Level
- Handling forms and pagination
- Rate limiting and respectful scraping
- Error handling and retries
- Data cleaning and storage
- **Prerequisites**: Completed Beginner level

### 🔴 Advanced Level
- JavaScript-heavy sites with Selenium
- Asynchronous scraping with asyncio
- Scrapy framework
- Database integration
- **Prerequisites**: Completed Intermediate level

## 🚀 Getting Started

1. **Install Python 3.8+** (if not already installed)

2. **Install dependencies**:
   ```bash
   pip install -r requirements.txt
   ```

3. **Start with Beginner Level**:
   - Read `beginner/README.md`
   - Run the examples in order
   - Complete the exercises

## 📁 Project Structure

```
crawl/
├── README.md (this file)
├── requirements.txt
├── beginner/
│   ├── README.md
│   ├── 01_basic_scraping.py
│   ├── 02_extract_links.py
│   ├── 03_extract_text.py
│   └── exercises/
├── intermediate/
│   ├── README.md
│   ├── 01_pagination.py
│   ├── 02_forms.py
│   ├── 03_rate_limiting.py
│   ├── 04_data_storage.py
│   └── exercises/
└── advanced/
    ├── README.md
    ├── 01_selenium_basics.py
    ├── 02_async_scraping.py
    ├── 03_scrapy_example/
    ├── 04_database_integration.py
    └── exercises/
```

## ⚠️ Important Notes

- **Always respect robots.txt**: Check `https://example.com/robots.txt` before scraping
- **Rate limiting**: Don't overwhelm servers with too many requests
- **Terms of Service**: Make sure you're allowed to scrape the website
- **Legal compliance**: Understand the legal implications in your jurisdiction

## 🎯 Learning Path

1. **Week 1**: Complete Beginner level (3-4 hours)
2. **Week 2**: Complete Intermediate level (4-5 hours)
3. **Week 3**: Complete Advanced level (5-6 hours)

## 📝 Exercises

Each level includes exercises to practice what you've learned. Solutions are provided in separate files.

## 🤝 Contributing

Feel free to submit improvements or additional examples!

## 📄 License

This educational material is provided for learning purposes.

