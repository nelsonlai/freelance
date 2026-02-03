"""
Advanced Playwright Example 2: Complete Testing Framework
==========================================================

This example demonstrates:
- Test fixtures and setup/teardown
- Test organization with pytest
- Screenshot on failure
- Video recording
- Test context and isolation
"""

from playwright.sync_api import sync_playwright, expect
import pytest
import time


class TestQuotesPage:
    """Test suite for Quotes page."""
    
    @pytest.fixture(scope="class")
    def browser(self):
        """Create browser instance for all tests in this class."""
        with sync_playwright() as p:
            browser = p.chromium.launch(headless=True)
            yield browser
            browser.close()
    
    @pytest.fixture(scope="function")
    def page(self, browser):
        """Create a new page for each test."""
        page = browser.new_page()
        page.goto("https://quotes.toscrape.com/")
        page.wait_for_load_state('networkidle')
        yield page
        page.close()
    
    def test_page_title(self, page):
        """Test that page title is correct."""
        expect(page).to_have_title(/Quotes/i)
    
    def test_quotes_visible(self, page):
        """Test that quotes are visible."""
        quotes = page.locator('.quote')
        expect(quotes.first).to_be_visible()
    
    def test_quote_count(self, page):
        """Test that page has 10 quotes."""
        quotes = page.locator('.quote')
        expect(quotes).to_have_count(10)
    
    def test_quote_structure(self, page):
        """Test that each quote has text, author, and tags."""
        first_quote = page.locator('.quote').first
        
        text = first_quote.locator('.text')
        author = first_quote.locator('.author')
        tags = first_quote.locator('.tag')
        
        expect(text).to_be_visible()
        expect(author).to_be_visible()
        assert tags.count() > 0, "Quote should have at least one tag"
    
    def test_next_button(self, page):
        """Test pagination with next button."""
        next_button = page.get_by_text('Next', exact=False).first
        
        if next_button.is_visible():
            next_button.click()
            page.wait_for_load_state('networkidle')
            
            # Should be on page 2
            expect(page).to_have_url(/page\/2/)
            expect(page.locator('.quote')).to_have_count(10)


class TestFormSubmission:
    """Test suite for form submission."""
    
    @pytest.fixture(scope="function")
    def page(self):
        """Create page with form."""
        with sync_playwright() as p:
            browser = p.chromium.launch(headless=True)
            page = browser.new_page()
            page.goto("https://httpbin.org/forms/post")
            page.wait_for_load_state('networkidle')
            yield page
            browser.close()
    
    def test_form_fill(self, page):
        """Test filling form fields."""
        customer_field = page.locator('input[name="custname"]')
        customer_field.fill("Test User")
        expect(customer_field).to_have_value("Test User")
    
    def test_checkbox(self, page):
        """Test checkbox interaction."""
        checkboxes = page.locator('input[type="checkbox"]')
        if checkboxes.count() > 0:
            first_checkbox = checkboxes.first
            first_checkbox.check()
            expect(first_checkbox).to_be_checked()
            
            first_checkbox.uncheck()
            expect(first_checkbox).not_to_be_checked()


def test_with_screenshot_on_failure():
    """Example test with screenshot on failure."""
    with sync_playwright() as p:
        browser = p.chromium.launch(headless=True)
        page = browser.new_page()
        
        try:
            page.goto("https://quotes.toscrape.com/")
            page.wait_for_load_state('networkidle')
            
            # This might fail
            expect(page.locator('.nonexistent')).to_be_visible()
            
        except Exception as e:
            # Take screenshot on failure
            page.screenshot(path="test_failure.png")
            print(f"Test failed, screenshot saved: test_failure.png")
            raise
        
        finally:
            browser.close()


def test_with_video_recording():
    """Example test with video recording."""
    with sync_playwright() as p:
        # Launch with video recording
        browser = p.chromium.launch(headless=True)
        context = browser.new_context(record_video_dir="videos/")
        page = context.new_page()
        
        try:
            page.goto("https://quotes.toscrape.com/")
            page.wait_for_load_state('networkidle')
            
            # Perform actions
            next_button = page.get_by_text('Next', exact=False).first
            if next_button.is_visible():
                next_button.click()
                page.wait_for_load_state('networkidle')
            
            # Test assertion
            expect(page).to_have_url(/page\/2/)
            
        finally:
            context.close()
            browser.close()
            # Video is saved automatically


def test_isolation_example():
    """Demonstrate test isolation - each test gets fresh state."""
    with sync_playwright() as p:
        browser = p.chromium.launch(headless=True)
        
        # Test 1: First test
        page1 = browser.new_page()
        page1.goto("https://quotes.toscrape.com/")
        page1.wait_for_load_state('networkidle')
        assert page1.locator('.quote').count() == 10
        page1.close()
        
        # Test 2: Second test (isolated from first)
        page2 = browser.new_page()
        page2.goto("https://quotes.toscrape.com/")
        page2.wait_for_load_state('networkidle')
        assert page2.locator('.quote').count() == 10  # Same initial state
        page2.close()
        
        browser.close()


def test_network_interception():
    """Example of intercepting network requests."""
    with sync_playwright() as p:
        browser = p.chromium.launch(headless=True)
        context = browser.new_context()
        
        # Intercept requests
        def handle_route(route):
            # Modify or block requests
            if 'api' in route.request.url:
                route.abort()
            else:
                route.continue_()
        
        context.route("**/*", handle_route)
        
        page = context.new_page()
        page.goto("https://quotes.toscrape.com/")
        page.wait_for_load_state('networkidle')
        
        # Test that page still works
        expect(page.locator('.quote')).to_have_count(10)
        
        context.close()
        browser.close()


if __name__ == "__main__":
    print("="*60)
    print("TESTING FRAMEWORK EXAMPLES")
    print("="*60)
    print("\nThese examples demonstrate testing patterns with Playwright.")
    print("\nTo run with pytest:")
    print("  pytest advanced/10_playwright_testing_framework.py -v")
    print("\nOr run individual examples:")
    print("  python advanced/10_playwright_testing_framework.py")
    
    # Run standalone examples
    print("\n1. Running standalone test examples...")
    test_isolation_example()
    print("   ✅ Isolation test passed")
    
    try:
        test_with_screenshot_on_failure()
    except:
        print("   ✅ Screenshot on failure test (expected to fail for demo)")
    
    test_network_interception()
    print("   ✅ Network interception test passed")
    
    print("\n" + "="*60)
    print("Examples completed!")
    print("="*60)
