# Playwright Tutorial: Website Testing and Data Crawling

This directory contains comprehensive examples for using Playwright with Python for both website testing and data crawling.

## 📚 What is Playwright?

Playwright is a modern browser automation tool that:
- Supports Chromium, Firefox, and WebKit browsers
- Has built-in auto-waiting (no need for time.sleep()!)
- Provides fast and reliable automation
- Works great for both testing and scraping
- Has excellent async/await support

## 🚀 Installation

1. **Install Playwright package**:
   ```bash
   pip install playwright
   ```

2. **Install browser binaries**:
   ```bash
   playwright install
   ```

   Or install specific browsers:
   ```bash
   playwright install chromium
   playwright install firefox
   playwright install webkit
   ```

## 📁 Course Structure

### 🟢 Beginner Level
- **06_playwright_intro.py** - Introduction to Playwright basics
- **07_playwright_interactions.py** - Clicking, forms, keyboard actions

### 🟡 Intermediate Level
- **08_playwright_waits.py** - Auto-waiting and explicit waits
- **09_playwright_testing.py** - Writing tests and assertions
- **10_playwright_scraping.py** - Scraping JavaScript content

### 🔴 Advanced Level
- **09_playwright_async.py** - Async/await for concurrent operations
- **10_playwright_testing_framework.py** - Complete testing framework
- **11_playwright_production.py** - Production-ready scraping

## 🎯 Key Features Demonstrated

### Testing Features
- ✅ Assertions and expectations
- ✅ Page Object Model
- ✅ Test fixtures and setup/teardown
- ✅ Screenshots and video recording
- ✅ Network interception
- ✅ Test isolation

### Scraping Features
- ✅ JavaScript-rendered content
- ✅ Infinite scroll handling
- ✅ Multi-page scraping
- ✅ Concurrent scraping
- ✅ Error handling and retries
- ✅ Data persistence

## 💡 Playwright vs Selenium

**Playwright Advantages:**
- Built-in auto-waiting (more reliable)
- Faster execution
- Better JavaScript support
- Multiple browser engines
- Better debugging tools
- Simpler API

**Use Playwright when:**
- You need reliable element waiting
- You're building modern web apps
- You want faster test execution
- You need multiple browser support

## 📝 Quick Start

### Basic Example

```python
from playwright.sync_api import sync_playwright

with sync_playwright() as p:
    browser = p.chromium.launch(headless=True)
    page = browser.new_page()
    page.goto("https://example.com")
    
    # Playwright automatically waits for elements!
    title = page.title()
    print(f"Page title: {title}")
    
    browser.close()
```

### Async Example

```python
from playwright.async_api import async_playwright
import asyncio

async def main():
    async with async_playwright() as p:
        browser = await p.chromium.launch(headless=True)
        page = await browser.new_page()
        await page.goto("https://example.com")
        print(f"Title: {await page.title()}")
        await browser.close()

asyncio.run(main())
```

## 🛠️ Common Commands

```bash
# Run a Playwright script
python beginner/06_playwright_intro.py

# Run tests with pytest
pytest intermediate/09_playwright_testing.py -v

# Generate code from browser actions
playwright codegen https://example.com
```

## 📚 Learning Path

1. **Start with Beginner**: Learn basic Playwright operations
2. **Move to Intermediate**: Learn waits, testing, and scraping
3. **Advance to Advanced**: Async operations and production patterns

## ⚠️ Important Notes

- Always use `wait_for_load_state()` for reliable page loading
- Playwright has built-in auto-waiting - don't use `time.sleep()`
- Use context managers (`with` statements) for proper cleanup
- Headless mode is faster but you can use `headless=False` for debugging

## 🔗 Resources

- [Playwright Python Documentation](https://playwright.dev/python/)
- [Playwright Best Practices](https://playwright.dev/python/docs/best-practices)
- [Playwright API Reference](https://playwright.dev/python/docs/api/class-playwright)

Happy automating! 🎭
