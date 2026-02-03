"""
Intermediate Playwright Example 2: Testing with Playwright
===========================================================

This example demonstrates:
- Writing tests with Playwright
- Assertions and expectations
- Test organization
- Page Object Model for testing
"""

from playwright.sync_api import sync_playwright, expect
import pytest

def basic_test_example():
    """Demonstrate basic testing patterns."""
    with sync_playwright() as p:
        print("="*60)
        print("BASIC TESTING EXAMPLE")
        print("="*60)
        
        browser = p.chromium.launch(headless=True)
        page = browser.new_page()
        
        # Test: Navigate to page
        url = "https://quotes.toscrape.com/"
        page.goto(url)
        
        print(f"\n1. Testing page: {url}")
        
        # Test: Check page title
        title = page.title()
        assert "Quotes" in title, f"Expected 'Quotes' in title, got '{title}'"
        print(f"   ✅ Title test passed: {title}")
        
        # Test: Check if element exists
        quote = page.locator('.quote').first
        assert quote.is_visible(), "Quote element should be visible"
        print("   ✅ Quote visibility test passed")
        
        # Test: Check element count
        quotes = page.locator('.quote').all()
        assert len(quotes) > 0, "Should have at least one quote"
        print(f"   ✅ Quote count test passed: {len(quotes)} quotes")
        
        # Test: Check text content
        quote_text = quote.locator('.text').text_content()
        assert quote_text is not None and len(quote_text) > 0, "Quote text should not be empty"
        print(f"   ✅ Quote text test passed: {quote_text[:50]}...")
        
        browser.close()
        print("\n✅ All basic tests passed!")


def expect_assertions_example():
    """Demonstrate Playwright's expect API."""
    with sync_playwright() as p:
        print("\n" + "="*60)
        print("EXPECT ASSERTIONS EXAMPLE")
        print("="*60)
        
        browser = p.chromium.launch(headless=True)
        page = browser.new_page()
        
        url = "https://quotes.toscrape.com/"
        page.goto(url)
        page.wait_for_load_state('networkidle')
        
        print(f"\n1. Testing with expect API: {url}")
        
        # Expect: Element to be visible
        quote = page.locator('.quote').first
        expect(quote).to_be_visible()
        print("   ✅ Expect: quote is visible")
        
        # Expect: Element to contain text
        quote_text = quote.locator('.text')
        expect(quote_text).to_contain_text("", {useInnerText: True})
        print("   ✅ Expect: quote text exists")
        
        # Expect: URL to contain specific text
        expect(page).to_have_url("https://quotes.toscrape.com/")
        print("   ✅ Expect: URL is correct")
        
        # Expect: Page to have title
        expect(page).to_have_title(/Quotes/i)
        print("   ✅ Expect: title contains 'Quotes'")
        
        # Expect: Element count
        quotes = page.locator('.quote')
        expect(quotes).to_have_count(10)  # quotes.toscrape.com shows 10 per page
        print("   ✅ Expect: 10 quotes on page")
        
        browser.close()
        print("\n✅ All expect assertions passed!")


def form_testing_example():
    """Test form interactions."""
    with sync_playwright() as p:
        print("\n" + "="*60)
        print("FORM TESTING EXAMPLE")
        print("="*60)
        
        browser = p.chromium.launch(headless=True)
        page = browser.new_page()
        
        url = "https://httpbin.org/forms/post"
        page.goto(url)
        page.wait_for_load_state('networkidle')
        
        print(f"\n1. Testing form: {url}")
        
        # Test: Fill form fields
        customer_field = page.locator('input[name="custname"]')
        customer_field.fill("Test User")
        
        # Verify field value
        expect(customer_field).to_have_value("Test User")
        print("   ✅ Form field value test passed")
        
        # Test: Fill multiple fields
        tel_field = page.locator('input[name="custtel"]')
        tel_field.fill("555-1234")
        
        email_field = page.locator('input[name="custemail"]')
        email_field.fill("test@example.com")
        
        # Test: Checkbox
        checkboxes = page.locator('input[type="checkbox"]')
        if checkboxes.count() > 0:
            first_checkbox = checkboxes.first
            first_checkbox.check()
            expect(first_checkbox).to_be_checked()
            print("   ✅ Checkbox test passed")
        
        # Test: Radio button
        radio_buttons = page.locator('input[type="radio"]')
        if radio_buttons.count() > 0:
            radio_buttons.nth(1).check()
            expect(radio_buttons.nth(1)).to_be_checked()
            print("   ✅ Radio button test passed")
        
        browser.close()
        print("\n✅ All form tests passed!")


class QuotesPage:
    """Page Object Model for Quotes page."""
    
    def __init__(self, page):
        self.page = page
        self.url = "https://quotes.toscrape.com/"
        
        # Locators
        self.quotes = page.locator('.quote')
        self.quote_text = page.locator('.quote .text')
        self.quote_author = page.locator('.quote .author')
        self.next_button = page.get_by_text('Next', exact=False)
    
    def goto(self):
        """Navigate to the page."""
        self.page.goto(self.url)
        self.page.wait_for_load_state('networkidle')
    
    def get_quotes_count(self):
        """Get the number of quotes on the page."""
        return self.quotes.count()
    
    def get_first_quote_text(self):
        """Get text of first quote."""
        return self.quote_text.first.text_content()
    
    def get_first_quote_author(self):
        """Get author of first quote."""
        return self.quote_author.first.text_content()
    
    def click_next(self):
        """Click the next button."""
        self.next_button.first.click()
        self.page.wait_for_load_state('networkidle')
    
    def has_next_button(self):
        """Check if next button exists."""
        return self.next_button.first.is_visible()


def page_object_model_example():
    """Demonstrate Page Object Model pattern."""
    with sync_playwright() as p:
        print("\n" + "="*60)
        print("PAGE OBJECT MODEL EXAMPLE")
        print("="*60)
        
        browser = p.chromium.launch(headless=True)
        page = browser.new_page()
        
        # Create page object
        quotes_page = QuotesPage(page)
        
        # Navigate
        quotes_page.goto()
        print(f"\n1. Navigated to quotes page")
        
        # Test using page object
        quote_count = quotes_page.get_quotes_count()
        expect(page.locator('.quote')).to_have_count(quote_count)
        print(f"   ✅ Found {quote_count} quotes")
        
        # Get quote data
        quote_text = quotes_page.get_first_quote_text()
        quote_author = quotes_page.get_first_quote_author()
        print(f"   ✅ First quote: {quote_text[:50]}...")
        print(f"   ✅ Author: {quote_author}")
        
        # Test next button
        if quotes_page.has_next_button():
            print("\n2. Testing pagination...")
            quotes_page.click_next()
            print("   ✅ Clicked next button")
            print(f"   Current URL: {page.url}")
        
        browser.close()
        print("\n✅ Page Object Model tests passed!")


if __name__ == "__main__":
    basic_test_example()
    expect_assertions_example()
    form_testing_example()
    page_object_model_example()
    
    print("\n" + "="*60)
    print("All testing examples completed!")
    print("="*60)
    print("\n💡 Key points:")
    print("  - Use expect() for readable assertions")
    print("  - Page Object Model keeps tests maintainable")
    print("  - Tests should be clear and focused")
    print("  - Combine with pytest for full test framework")
