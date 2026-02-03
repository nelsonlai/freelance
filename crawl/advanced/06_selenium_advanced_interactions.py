"""
Advanced Selenium Example 3: Advanced Interactions
====================================================

This example demonstrates:
- ActionChains for complex interactions
- Mouse movements and hover
- Drag and drop
- Keyboard shortcuts
- JavaScript execution
"""

from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.common.action_chains import ActionChains
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.chrome.options import Options
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
import time

def setup_driver(headless=False):
    """Set up Chrome WebDriver."""
    chrome_options = Options()
    
    if headless:
        chrome_options.add_argument('--headless')
        chrome_options.add_argument('--no-sandbox')
        chrome_options.add_argument('--disable-dev-shm-usage')
    
    chrome_options.add_argument('user-agent=Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36')
    
    try:
        return webdriver.Chrome(options=chrome_options)
    except Exception as e:
        print(f"❌ Error: {e}")
        return None


def action_chains_example():
    """Demonstrate ActionChains for complex interactions."""
    driver = setup_driver()
    
    if not driver:
        return
    
    try:
        print("="*60)
        print("ACTIONCHAINS EXAMPLE")
        print("="*60)
        
        url = "https://quotes.toscrape.com/"
        driver.get(url)
        time.sleep(2)
        
        print(f"\n1. Opened: {url}")
        
        # Create ActionChains object
        actions = ActionChains(driver)
        
        # Find an element to interact with
        try:
            quote = driver.find_element(By.CLASS_NAME, "quote")
            
            # Move to element (hover)
            print("2. Moving mouse to quote element...")
            actions.move_to_element(quote).perform()
            time.sleep(1)
            print("   ✅ Moved mouse to element")
            
            # Click and hold
            print("3. Clicking and holding...")
            actions.click_and_hold(quote).perform()
            time.sleep(0.5)
            actions.release().perform()
            print("   ✅ Clicked and released")
            
            # Double click
            print("4. Double clicking...")
            actions.double_click(quote).perform()
            time.sleep(1)
            print("   ✅ Double clicked")
            
            # Right click (context menu)
            print("5. Right clicking...")
            actions.context_click(quote).perform()
            time.sleep(1)
            print("   ✅ Right clicked")
            
        except Exception as e:
            print(f"   ⚠️  Error: {e}")
        
    except Exception as e:
        print(f"❌ Error: {e}")
    finally:
        driver.quit()


def drag_and_drop_example():
    """Demonstrate drag and drop (if a suitable page is available)."""
    driver = setup_driver()
    
    if not driver:
        return
    
    try:
        print("\n" + "="*60)
        print("DRAG AND DROP EXAMPLE")
        print("="*60)
        
        # Use a page with drag and drop functionality
        # For demonstration, we'll show the concept
        url = "https://jqueryui.com/droppable/"
        driver.get(url)
        time.sleep(3)
        
        print(f"\n1. Opened: {url}")
        
        # Switch to iframe if needed
        try:
            iframe = driver.find_element(By.CSS_SELECTOR, "iframe.demo-frame")
            driver.switch_to.frame(iframe)
            print("2. Switched to iframe")
            
            wait = WebDriverWait(driver, 10)
            
            # Find draggable and droppable elements
            draggable = wait.until(EC.presence_of_element_located((By.ID, "draggable")))
            droppable = wait.until(EC.presence_of_element_located((By.ID, "droppable")))
            
            print("3. Found draggable and droppable elements")
            
            # Perform drag and drop
            actions = ActionChains(driver)
            actions.drag_and_drop(draggable, droppable).perform()
            time.sleep(2)
            
            print("   ✅ Drag and drop completed!")
            
            # Check if drop was successful
            droppable_text = droppable.text
            if "Dropped" in droppable_text:
                print("   ✅ Drop successful - element shows 'Dropped'")
            
            # Switch back from iframe
            driver.switch_to.default_content()
            
        except Exception as e:
            print(f"   ⚠️  Error with drag and drop: {e}")
            print("   (This example requires a page with drag-and-drop functionality)")
        
    except Exception as e:
        print(f"❌ Error: {e}")
    finally:
        driver.quit()


def javascript_execution_example():
    """Demonstrate executing JavaScript code."""
    driver = setup_driver()
    
    if not driver:
        return
    
    try:
        print("\n" + "="*60)
        print("JAVASCRIPT EXECUTION EXAMPLE")
        print("="*60)
        
        url = "https://quotes.toscrape.com/"
        driver.get(url)
        time.sleep(2)
        
        print(f"\n1. Opened: {url}")
        
        # Execute JavaScript to get page title
        title = driver.execute_script("return document.title;")
        print(f"2. Page title (via JavaScript): {title}")
        
        # Execute JavaScript to scroll
        print("3. Scrolling page with JavaScript...")
        driver.execute_script("window.scrollTo(0, document.body.scrollHeight);")
        time.sleep(2)
        print("   ✅ Scrolled to bottom")
        
        # Execute JavaScript to get element count
        quote_count = driver.execute_script("return document.querySelectorAll('.quote').length;")
        print(f"4. Quote count (via JavaScript): {quote_count}")
        
        # Execute JavaScript to modify page
        driver.execute_script("document.body.style.backgroundColor = 'lightblue';")
        time.sleep(1)
        print("5. ✅ Changed background color (via JavaScript)")
        
        # Execute JavaScript with arguments
        driver.execute_script("arguments[0].style.border = '3px solid red';", 
                             driver.find_element(By.CLASS_NAME, "quote"))
        time.sleep(1)
        print("6. ✅ Added border to first quote (via JavaScript)")
        
        # Execute async JavaScript
        result = driver.execute_async_script("""
            var callback = arguments[arguments.length - 1];
            setTimeout(function() {
                callback('Async JavaScript executed!');
            }, 1000);
        """)
        print(f"7. Async result: {result}")
        
    except Exception as e:
        print(f"❌ Error: {e}")
    finally:
        driver.quit()


def keyboard_shortcuts_example():
    """Demonstrate keyboard shortcuts and combinations."""
    driver = setup_driver()
    
    if not driver:
        return
    
    try:
        print("\n" + "="*60)
        print("KEYBOARD SHORTCUTS EXAMPLE")
        print("="*60)
        
        url = "https://quotes.toscrape.com/"
        driver.get(url)
        time.sleep(2)
        
        print(f"\n1. Opened: {url}")
        
        # Get body element to send keys to
        body = driver.find_element(By.TAG_NAME, "body")
        
        actions = ActionChains(driver)
        
        # Ctrl+A (Select all) - or Cmd+A on Mac
        import platform
        modifier = Keys.COMMAND if platform.system() == 'Darwin' else Keys.CONTROL
        
        print("2. Pressing Ctrl/Cmd+A (Select All)...")
        actions.key_down(modifier).send_keys('a').key_up(modifier).perform()
        time.sleep(1)
        print("   ✅ Selected all text")
        
        # F5 to refresh (though this might navigate away)
        print("3. Pressing F5 (Refresh)...")
        body.send_keys(Keys.F5)
        time.sleep(2)
        print("   ✅ Refreshed page")
        
        # Tab navigation
        print("4. Pressing Tab to navigate...")
        body.send_keys(Keys.TAB)
        time.sleep(0.5)
        body.send_keys(Keys.TAB)
        print("   ✅ Tabbed through elements")
        
    except Exception as e:
        print(f"❌ Error: {e}")
    finally:
        driver.quit()


if __name__ == "__main__":
    action_chains_example()
    drag_and_drop_example()
    javascript_execution_example()
    keyboard_shortcuts_example()
    
    print("\n" + "="*60)
    print("Advanced interaction examples completed!")
    print("="*60)
    print("\n💡 Key points:")
    print("  - ActionChains allow complex mouse/keyboard interactions")
    print("  - JavaScript execution gives you full control")
    print("  - Drag and drop works with ActionChains")
    print("  - Keyboard shortcuts can automate many tasks")

