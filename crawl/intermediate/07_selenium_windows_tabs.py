"""
Intermediate Selenium Example 3: Multiple Windows and Tabs
==========================================================

This example demonstrates:
- How to handle multiple browser windows
- How to switch between windows
- How to open new tabs/windows
- How to close windows
"""

from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.chrome.options import Options
import time

def setup_driver():
    """Set up Chrome WebDriver."""
    chrome_options = Options()
    chrome_options.add_argument('user-agent=Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36')
    
    try:
        return webdriver.Chrome(options=chrome_options)
    except Exception as e:
        print(f"❌ Error: {e}")
        return None


def multiple_windows_example():
    """Demonstrate working with multiple windows."""
    driver = setup_driver()
    
    if not driver:
        return
    
    try:
        print("="*60)
        print("MULTIPLE WINDOWS EXAMPLE")
        print("="*60)
        
        # Open first page
        url1 = "https://quotes.toscrape.com/"
        driver.get(url1)
        time.sleep(2)
        
        print(f"\n1. Opened first window: {url1}")
        print(f"   Window handle: {driver.current_window_handle}")
        original_window = driver.current_window_handle
        
        # Open a new window (using JavaScript)
        driver.execute_script("window.open('');")
        time.sleep(1)
        
        # Get all window handles
        all_windows = driver.window_handles
        print(f"\n2. Total windows open: {len(all_windows)}")
        
        # Switch to the new window
        for window in all_windows:
            if window != original_window:
                driver.switch_to.window(window)
                break
        
        print(f"   Switched to new window")
        print(f"   Current window handle: {driver.current_window_handle}")
        
        # Navigate in the new window
        url2 = "https://www.python.org"
        driver.get(url2)
        time.sleep(2)
        print(f"\n3. Navigated new window to: {url2}")
        print(f"   Title: {driver.title}")
        
        # Switch back to original window
        driver.switch_to.window(original_window)
        print(f"\n4. Switched back to original window")
        print(f"   Title: {driver.title}")
        
        # Close the new window
        for window in all_windows:
            if window != original_window:
                driver.switch_to.window(window)
                driver.close()
                break
        
        print(f"\n5. Closed the new window")
        
        # Switch back to original
        driver.switch_to.window(original_window)
        print(f"   Back to original window")
        
    except Exception as e:
        print(f"❌ Error: {e}")
    finally:
        driver.quit()


def new_tab_example():
    """Demonstrate opening links in new tabs."""
    driver = setup_driver()
    
    if not driver:
        return
    
    try:
        print("\n" + "="*60)
        print("NEW TAB EXAMPLE")
        print("="*60)
        
        url = "https://quotes.toscrape.com/"
        driver.get(url)
        time.sleep(2)
        
        print(f"\n1. Opened: {url}")
        original_window = driver.current_window_handle
        print(f"   Original window handle: {original_window}")
        
        # Find a link and open it in new tab (Ctrl+Click or Cmd+Click)
        try:
            # Find the "Next" link if it exists
            links = driver.find_elements(By.TAG_NAME, "a")
            if links:
                # Open link in new tab using keyboard shortcut
                from selenium.webdriver.common.action_chains import ActionChains
                from selenium.webdriver.common.keys import Keys
                
                # For macOS use CMD, for Windows/Linux use CTRL
                import platform
                modifier = Keys.COMMAND if platform.system() == 'Darwin' else Keys.CONTROL
                
                first_link = links[0]
                ActionChains(driver).key_down(modifier).click(first_link).key_up(modifier).perform()
                
                time.sleep(2)
                
                # Get all windows
                all_windows = driver.window_handles
                print(f"\n2. Total windows/tabs: {len(all_windows)}")
                
                # Switch to new tab
                for window in all_windows:
                    if window != original_window:
                        driver.switch_to.window(window)
                        print(f"   Switched to new tab")
                        print(f"   URL: {driver.current_url}")
                        print(f"   Title: {driver.title}")
                        break
                
                # Switch back
                driver.switch_to.window(original_window)
                print(f"\n3. Switched back to original tab")
                
        except Exception as e:
            print(f"   ⚠️  Error opening new tab: {e}")
        
    except Exception as e:
        print(f"❌ Error: {e}")
    finally:
        driver.quit()


def window_management_example():
    """Demonstrate window management operations."""
    driver = setup_driver()
    
    if not driver:
        return
    
    try:
        print("\n" + "="*60)
        print("WINDOW MANAGEMENT EXAMPLE")
        print("="*60)
        
        url = "https://quotes.toscrape.com/"
        driver.get(url)
        time.sleep(2)
        
        print(f"\n1. Window operations:")
        
        # Get window size
        size = driver.get_window_size()
        print(f"   Current size: {size['width']}x{size['height']}")
        
        # Set window size
        driver.set_window_size(1200, 800)
        print(f"   ✅ Set size to 1200x800")
        time.sleep(1)
        
        # Get window position
        position = driver.get_window_position()
        print(f"   Current position: ({position['x']}, {position['y']})")
        
        # Maximize window
        driver.maximize_window()
        print(f"   ✅ Maximized window")
        time.sleep(1)
        
        # Get window size after maximize
        size = driver.get_window_size()
        print(f"   Size after maximize: {size['width']}x{size['height']}")
        
    except Exception as e:
        print(f"❌ Error: {e}")
    finally:
        driver.quit()


if __name__ == "__main__":
    multiple_windows_example()
    new_tab_example()
    window_management_example()
    
    print("\n" + "="*60)
    print("All window examples completed!")
    print("="*60)
    print("\n💡 Key points:")
    print("  - Use window_handles to get all open windows")
    print("  - Use switch_to.window() to switch between windows")
    print("  - Always close windows you open")
    print("  - Keep track of window handles to switch back")

