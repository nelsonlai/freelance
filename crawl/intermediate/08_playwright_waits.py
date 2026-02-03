"""
Intermediate Playwright Example 1: Waits and Auto-Waiting
==========================================================

This example demonstrates:
- Playwright's built-in auto-waiting
- Explicit waits
- Waiting for network conditions
- Waiting for elements to be in specific states
"""

from playwright.sync_api import sync_playwright, TimeoutError as PlaywrightTimeout
import time

def auto_wait_example():
    """Demonstrate Playwright's automatic waiting."""
    with sync_playwright() as p:
        print("="*60)
        print("AUTO-WAIT EXAMPLE")
        print("="*60)
        
        browser = p.chromium.launch(headless=True)
        page = browser.new_page()
        
        url = "https://quotes.toscrape.com/js/"
        print(f"\n1. Opening: {url}")
        page.goto(url)
        
        # Playwright automatically waits for elements to be actionable
        # You don't need explicit waits in most cases!
        print("2. Playwright automatically waits for elements...")
        
        # This will automatically wait for the element to be visible and enabled
        quote = page.locator('.quote').first
        text = quote.locator('.text').text_content()
        
        print(f"   ✅ Got quote text automatically: {text[:50]}...")
        print("   (Playwright waited for the element without explicit wait!)")
        
        browser.close()


def explicit_wait_example():
    """Demonstrate explicit waits when needed."""
    with sync_playwright() as p:
        print("\n" + "="*60)
        print("EXPLICIT WAIT EXAMPLE")
        print("="*60)
        
        browser = p.chromium.launch(headless=True)
        page = browser.new_page()
        
        url = "https://quotes.toscrape.com/js/"
        page.goto(url)
        
        print(f"\n1. Opened: {url}")
        
        # Wait for element to be visible
        print("2. Waiting for quote to be visible...")
        quote = page.wait_for_selector('.quote', state='visible', timeout=10000)
        print("   ✅ Quote is now visible")
        
        # Wait for element to be hidden
        print("\n3. Waiting for specific conditions...")
        
        # Wait for network to be idle
        print("   Waiting for network to be idle...")
        page.wait_for_load_state('networkidle')
        print("   ✅ Network is idle")
        
        # Wait for DOM to be loaded
        page.wait_for_load_state('domcontentloaded')
        print("   ✅ DOM content loaded")
        
        browser.close()


def wait_for_text_example():
    """Wait for specific text to appear."""
    with sync_playwright() as p:
        print("\n" + "="*60)
        print("WAIT FOR TEXT EXAMPLE")
        print("="*60)
        
        browser = p.chromium.launch(headless=True)
        page = browser.new_page()
        
        url = "https://quotes.toscrape.com/"
        page.goto(url)
        
        print(f"\n1. Opened: {url}")
        
        # Wait for text to appear
        print("2. Waiting for 'Quotes to Scrape' text...")
        try:
            page.wait_for_selector('text=Quotes to Scrape', timeout=10000)
            print("   ✅ Text found!")
            
            # Get the heading
            heading = page.locator('h1')
            print(f"   Heading: {heading.text_content()}")
        except PlaywrightTimeout:
            print("   ⚠️  Text not found within timeout")
        
        browser.close()


def wait_for_network_example():
    """Wait for network requests to complete."""
    with sync_playwright() as p:
        print("\n" + "="*60)
        print("WAIT FOR NETWORK EXAMPLE")
        print("="*60)
        
        browser = p.chromium.launch(headless=True)
        page = browser.new_page()
        
        # Listen to network events
        responses = []
        
        def handle_response(response):
            responses.append(response.url)
        
        page.on('response', handle_response)
        
        url = "https://quotes.toscrape.com/"
        print(f"\n1. Opening: {url}")
        page.goto(url)
        
        # Wait for network to be idle (no network requests for 500ms)
        print("2. Waiting for network to be idle...")
        page.wait_for_load_state('networkidle')
        
        print(f"   ✅ Network idle - captured {len(responses)} responses")
        
        # Wait for specific request/response
        print("\n3. Waiting for specific conditions...")
        
        # Example: Wait for a specific URL to be requested
        # page.wait_for_response(lambda response: 'api' in response.url)
        
        browser.close()


def wait_for_element_state_example():
    """Wait for elements to be in specific states."""
    with sync_playwright() as p:
        print("\n" + "="*60)
        print("WAIT FOR ELEMENT STATE EXAMPLE")
        print("="*60)
        
        browser = p.chromium.launch(headless=True)
        page = browser.new_page()
        
        url = "https://quotes.toscrape.com/"
        page.goto(url)
        page.wait_for_load_state('networkidle')
        
        print(f"\n1. Opened: {url}")
        
        # Wait for different element states
        quote = page.locator('.quote').first
        
        print("\n2. Checking element states:")
        
        # Wait for visible
        quote.wait_for(state='visible', timeout=5000)
        print("   ✅ Element is visible")
        
        # Wait for attached (in DOM)
        quote.wait_for(state='attached', timeout=5000)
        print("   ✅ Element is attached to DOM")
        
        # Check if element is visible
        is_visible = quote.is_visible()
        print(f"   ✅ Element visibility: {is_visible}")
        
        # Check if element is enabled
        try:
            next_link = page.get_by_text('Next', exact=False).first
            is_enabled = next_link.is_enabled()
            print(f"   ✅ Next link enabled: {is_enabled}")
        except:
            print("   ⚠️  Next link not found")
        
        browser.close()


if __name__ == "__main__":
    auto_wait_example()
    explicit_wait_example()
    wait_for_text_example()
    wait_for_network_example()
    wait_for_element_state_example()
    
    print("\n" + "="*60)
    print("All wait examples completed!")
    print("="*60)
    print("\n💡 Key points:")
    print("  - Playwright has built-in auto-waiting (no need for time.sleep()!)")
    print("  - Explicit waits are only needed for specific conditions")
    print("  - wait_for_load_state() handles network and DOM loading")
    print("  - wait_for_selector() waits for specific elements")
    print("  - Much more reliable than manual waits!")
