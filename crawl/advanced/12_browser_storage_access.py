"""
Advanced Example: Browser Storage Access
=========================================

This example demonstrates how to access various browser storage types:
- Local Storage
- Session Storage
- Extension Storage
- IndexedDB
- Cookies
- Private State Tokens (Privacy Pass)

Using both Playwright and Selenium approaches.
"""

from playwright.sync_api import sync_playwright
from selenium import webdriver
from selenium.webdriver.chrome.options import Options
import json


# ============================================================================
# PLAYWRIGHT APPROACH
# ============================================================================

def playwright_local_storage():
    """Access Local Storage with Playwright."""
    with sync_playwright() as p:
        print("="*60)
        print("PLAYWRIGHT: LOCAL STORAGE")
        print("="*60)
        
        browser = p.chromium.launch(headless=True)
        context = browser.new_context()
        page = context.new_page()
        
        # Navigate to a page
        url = "https://quotes.toscrape.com/"
        page.goto(url)
        page.wait_for_load_state('networkidle')
        
        print(f"\n1. Opened: {url}")
        
        # Set Local Storage item
        page.evaluate("localStorage.setItem('myKey', 'myValue');")
        page.evaluate("localStorage.setItem('testData', JSON.stringify({name: 'Test', id: 123}));")
        print("   ✅ Set Local Storage items")
        
        # Get Local Storage item
        value = page.evaluate("localStorage.getItem('myKey');")
        print(f"\n2. Get Local Storage item:")
        print(f"   localStorage.getItem('myKey') = {value}")
        
        # Get all Local Storage items
        all_storage = page.evaluate("""
            () => {
                const items = {};
                for (let i = 0; i < localStorage.length; i++) {
                    const key = localStorage.key(i);
                    items[key] = localStorage.getItem(key);
                }
                return items;
            }
        """)
        
        print(f"\n3. All Local Storage items:")
        for key, value in all_storage.items():
            print(f"   {key}: {value}")
        
        # Get Local Storage via context
        storage_state = context.storage_state()
        print(f"\n4. Storage state (context):")
        print(f"   Local Storage keys: {len(storage_state.get('origins', [{}])[0].get('localStorage', []))}")
        
        browser.close()


def playwright_session_storage():
    """Access Session Storage with Playwright."""
    with sync_playwright() as p:
        print("\n" + "="*60)
        print("PLAYWRIGHT: SESSION STORAGE")
        print("="*60)
        
        browser = p.chromium.launch(headless=True)
        context = browser.new_context()
        page = context.new_page()
        
        url = "https://quotes.toscrape.com/"
        page.goto(url)
        page.wait_for_load_state('networkidle')
        
        print(f"\n1. Opened: {url}")
        
        # Set Session Storage item
        page.evaluate("sessionStorage.setItem('sessionKey', 'sessionValue');")
        page.evaluate("sessionStorage.setItem('userSession', JSON.stringify({userId: 456, timestamp: Date.now()}));")
        print("   ✅ Set Session Storage items")
        
        # Get Session Storage item
        value = page.evaluate("sessionStorage.getItem('sessionKey');")
        print(f"\n2. Get Session Storage item:")
        print(f"   sessionStorage.getItem('sessionKey') = {value}")
        
        # Get all Session Storage items
        all_storage = page.evaluate("""
            () => {
                const items = {};
                for (let i = 0; i < sessionStorage.length; i++) {
                    const key = sessionStorage.key(i);
                    items[key] = sessionStorage.getItem(key);
                }
                return items;
            }
        """)
        
        print(f"\n3. All Session Storage items:")
        for key, value in all_storage.items():
            print(f"   {key}: {value}")
        
        browser.close()


def playwright_cookies():
    """Access Cookies with Playwright."""
    with sync_playwright() as p:
        print("\n" + "="*60)
        print("PLAYWRIGHT: COOKIES")
        print("="*60)
        
        browser = p.chromium.launch(headless=True)
        context = browser.new_context()
        page = context.new_page()
        
        url = "https://quotes.toscrape.com/"
        page.goto(url)
        page.wait_for_load_state('networkidle')
        
        print(f"\n1. Opened: {url}")
        
        # Add cookies
        context.add_cookies([
            {
                'name': 'test_cookie',
                'value': 'test_value',
                'domain': 'quotes.toscrape.com',
                'path': '/',
            },
            {
                'name': 'user_pref',
                'value': 'dark_mode',
                'domain': 'quotes.toscrape.com',
                'path': '/',
            }
        ])
        print("   ✅ Added cookies")
        
        # Get all cookies
        cookies = context.cookies()
        print(f"\n2. All cookies ({len(cookies)}):")
        for cookie in cookies:
            print(f"   Name: {cookie['name']}")
            print(f"   Value: {cookie['value']}")
            print(f"   Domain: {cookie.get('domain', 'N/A')}")
            print(f"   Path: {cookie.get('path', 'N/A')}")
            print()
        
        # Get cookies for specific URL
        url_cookies = context.cookies(url)
        print(f"3. Cookies for {url}: {len(url_cookies)}")
        
        # Get specific cookie value
        cookie_value = next((c['value'] for c in cookies if c['name'] == 'test_cookie'), None)
        print(f"\n4. Get specific cookie 'test_cookie': {cookie_value}")
        
        browser.close()


def playwright_indexeddb():
    """Access IndexedDB with Playwright."""
    with sync_playwright() as p:
        print("\n" + "="*60)
        print("PLAYWRIGHT: INDEXEDDB")
        print("="*60)
        
        browser = p.chromium.launch(headless=True)
        context = browser.new_context()
        page = context.new_page()
        
        url = "https://quotes.toscrape.com/"
        page.goto(url)
        page.wait_for_load_state('networkidle')
        
        print(f"\n1. Opened: {url}")
        
        # Access IndexedDB via JavaScript
        print("2. Accessing IndexedDB...")
        
        # Example: Create database and store data
        indexeddb_result = page.evaluate("""
            () => {
                return new Promise((resolve) => {
                    const request = indexedDB.open('testDB', 1);
                    
                    request.onerror = () => resolve({success: false, error: 'Failed to open DB'});
                    
                    request.onsuccess = (event) => {
                        const db = event.target.result;
                        
                        // Get all database names
                        if (window.indexedDB.databases) {
                            window.indexedDB.databases().then(databases => {
                                resolve({
                                    success: true,
                                    databases: databases.map(db => db.name),
                                    currentDB: db.name,
                                    version: db.version
                                });
                            });
                        } else {
                            resolve({
                                success: true,
                                currentDB: db.name,
                                version: db.version,
                                note: 'databases() not supported'
                            });
                        }
                    };
                    
                    request.onupgradeneeded = (event) => {
                        const db = event.target.result;
                        if (!db.objectStoreNames.contains('testStore')) {
                            db.createObjectStore('testStore', {keyPath: 'id'});
                        }
                    };
                });
            }
        """)
        
        print(f"   IndexedDB Result: {json.dumps(indexeddb_result, indent=2)}")
        
        # Get database info
        db_info = page.evaluate("""
            () => {
                if (window.indexedDB.databases) {
                    return window.indexedDB.databases().then(dbs => {
                        return dbs.map(db => ({
                            name: db.name,
                            version: db.version
                        }));
                    });
                }
                return Promise.resolve([]);
            }
        """)
        
        if db_info:
            print(f"\n3. Available IndexedDB databases:")
            for db in db_info:
                print(f"   Name: {db['name']}, Version: {db['version']}")
        
        browser.close()


def playwright_storage_state():
    """Save and restore storage state (Local Storage, Session Storage, Cookies)."""
    with sync_playwright() as p:
        print("\n" + "="*60)
        print("PLAYWRIGHT: STORAGE STATE (SAVE/RESTORE)")
        print("="*60)
        
        # Create context and set up storage
        browser = p.chromium.launch(headless=True)
        context = browser.new_context()
        page = context.new_page()
        
        url = "https://quotes.toscrape.com/"
        page.goto(url)
        
        # Set storage
        page.evaluate("localStorage.setItem('savedData', 'important_value');")
        context.add_cookies([{
            'name': 'saved_cookie',
            'value': 'cookie_value',
            'domain': 'quotes.toscrape.com',
            'path': '/',
        }])
        
        # Save storage state
        storage_state = context.storage_state()
        print(f"\n1. Saved storage state:")
        print(f"   Cookies: {len(storage_state.get('cookies', []))}")
        print(f"   Origins: {len(storage_state.get('origins', []))}")
        
        # Save to file
        with open('storage_state.json', 'w') as f:
            json.dump(storage_state, f, indent=2)
        print(f"   ✅ Saved to storage_state.json")
        
        browser.close()
        
        # Restore from saved state
        print(f"\n2. Restoring from saved state...")
        browser2 = p.chromium.launch(headless=True)
        context2 = browser2.new_context(storage_state=storage_state)
        page2 = context2.new_page()
        
        page2.goto(url)
        
        # Verify restored storage
        restored_value = page2.evaluate("localStorage.getItem('savedData');")
        print(f"   ✅ Restored Local Storage value: {restored_value}")
        
        restored_cookies = context2.cookies()
        print(f"   ✅ Restored cookies: {len(restored_cookies)}")
        
        browser2.close()


# ============================================================================
# SELENIUM APPROACH
# ============================================================================

def selenium_local_storage():
    """Access Local Storage with Selenium."""
    print("\n" + "="*60)
    print("SELENIUM: LOCAL STORAGE")
    print("="*60)
    
    chrome_options = Options()
    chrome_options.add_argument('--headless')
    driver = webdriver.Chrome(options=chrome_options)
    
    try:
        url = "https://quotes.toscrape.com/"
        driver.get(url)
        print(f"\n1. Opened: {url}")
        
        # Set Local Storage
        driver.execute_script("localStorage.setItem('myKey', 'myValue');")
        driver.execute_script("localStorage.setItem('testData', JSON.stringify({name: 'Test', id: 123}));")
        print("   ✅ Set Local Storage items")
        
        # Get Local Storage item
        value = driver.execute_script("return localStorage.getItem('myKey');")
        print(f"\n2. Get Local Storage item:")
        print(f"   localStorage.getItem('myKey') = {value}")
        
        # Get all Local Storage items
        all_storage = driver.execute_script("""
            var items = {};
            for (var i = 0; i < localStorage.length; i++) {
                var key = localStorage.key(i);
                items[key] = localStorage.getItem(key);
            }
            return items;
        """)
        
        print(f"\n3. All Local Storage items:")
        for key, value in all_storage.items():
            print(f"   {key}: {value}")
        
        # Get Local Storage size
        size = driver.execute_script("return localStorage.length;")
        print(f"\n4. Local Storage size: {size} items")
        
    finally:
        driver.quit()


def selenium_session_storage():
    """Access Session Storage with Selenium."""
    print("\n" + "="*60)
    print("SELENIUM: SESSION STORAGE")
    print("="*60)
    
    chrome_options = Options()
    chrome_options.add_argument('--headless')
    driver = webdriver.Chrome(options=chrome_options)
    
    try:
        url = "https://quotes.toscrape.com/"
        driver.get(url)
        print(f"\n1. Opened: {url}")
        
        # Set Session Storage
        driver.execute_script("sessionStorage.setItem('sessionKey', 'sessionValue');")
        driver.execute_script("sessionStorage.setItem('userSession', JSON.stringify({userId: 456}));")
        print("   ✅ Set Session Storage items")
        
        # Get Session Storage item
        value = driver.execute_script("return sessionStorage.getItem('sessionKey');")
        print(f"\n2. Get Session Storage item:")
        print(f"   sessionStorage.getItem('sessionKey') = {value}")
        
        # Get all Session Storage items
        all_storage = driver.execute_script("""
            var items = {};
            for (var i = 0; i < sessionStorage.length; i++) {
                var key = sessionStorage.key(i);
                items[key] = sessionStorage.getItem(key);
            }
            return items;
        """)
        
        print(f"\n3. All Session Storage items:")
        for key, value in all_storage.items():
            print(f"   {key}: {value}")
        
    finally:
        driver.quit()


def selenium_cookies():
    """Access Cookies with Selenium."""
    print("\n" + "="*60)
    print("SELENIUM: COOKIES")
    print("="*60)
    
    chrome_options = Options()
    chrome_options.add_argument('--headless')
    driver = webdriver.Chrome(options=chrome_options)
    
    try:
        url = "https://quotes.toscrape.com/"
        driver.get(url)
        print(f"\n1. Opened: {url}")
        
        # Add cookies
        driver.add_cookie({
            'name': 'test_cookie',
            'value': 'test_value',
            'domain': 'quotes.toscrape.com',
            'path': '/',
        })
        driver.add_cookie({
            'name': 'user_pref',
            'value': 'dark_mode',
            'domain': 'quotes.toscrape.com',
            'path': '/',
        })
        print("   ✅ Added cookies")
        
        # Get all cookies
        cookies = driver.get_cookies()
        print(f"\n2. All cookies ({len(cookies)}):")
        for cookie in cookies:
            print(f"   Name: {cookie['name']}")
            print(f"   Value: {cookie['value']}")
            print(f"   Domain: {cookie.get('domain', 'N/A')}")
            print(f"   Path: {cookie.get('path', 'N/A')}")
            print()
        
        # Get specific cookie
        cookie_value = driver.get_cookie('test_cookie')
        if cookie_value:
            print(f"3. Get specific cookie 'test_cookie':")
            print(f"   Value: {cookie_value['value']}")
        
        # Delete cookie
        driver.delete_cookie('test_cookie')
        print(f"\n4. ✅ Deleted cookie 'test_cookie'")
        
        # Verify deletion
        remaining_cookies = driver.get_cookies()
        print(f"   Remaining cookies: {len(remaining_cookies)}")
        
    finally:
        driver.quit()


def selenium_indexeddb():
    """Access IndexedDB with Selenium."""
    print("\n" + "="*60)
    print("SELENIUM: INDEXEDDB")
    print("="*60)
    
    chrome_options = Options()
    chrome_options.add_argument('--headless')
    driver = webdriver.Chrome(options=chrome_options)
    
    try:
        url = "https://quotes.toscrape.com/"
        driver.get(url)
        print(f"\n1. Opened: {url}")
        
        # Access IndexedDB
        print("2. Accessing IndexedDB...")
        
        # Check if IndexedDB is available
        indexeddb_available = driver.execute_script("return typeof indexedDB !== 'undefined';")
        print(f"   IndexedDB available: {indexeddb_available}")
        
        # Get database names (if supported)
        databases = driver.execute_script("""
            if (window.indexedDB.databases) {
                return window.indexedDB.databases().then(dbs => {
                    return dbs.map(db => ({
                        name: db.name,
                        version: db.version
                    }));
                });
            }
            return [];
        """)
        
        if databases:
            print(f"\n3. Available IndexedDB databases:")
            for db in databases:
                print(f"   Name: {db['name']}, Version: {db['version']}")
        else:
            print("   Note: IndexedDB.databases() may not be supported in this browser")
        
    finally:
        driver.quit()


# ============================================================================
# PRIVATE STATE TOKENS (Privacy Pass) - Advanced
# ============================================================================

def playwright_private_state_tokens():
    """Access Private State Tokens with Playwright."""
    with sync_playwright() as p:
        print("\n" + "="*60)
        print("PLAYWRIGHT: PRIVATE STATE TOKENS")
        print("="*60)
        
        print("\n1. Private State Tokens (Privacy Pass) are browser-managed")
        print("   and cannot be directly accessed via JavaScript for security reasons.")
        print("   However, we can check if the API is available:")
        
        browser = p.chromium.launch(headless=True)
        context = browser.new_context()
        page = context.new_page()
        
        url = "https://quotes.toscrape.com/"
        page.goto(url)
        page.wait_for_load_state('networkidle')
        
        # Check Private State Token API availability
        token_check = page.evaluate("""
            () => {
                return {
                    documentHasPrivateToken: typeof document.privateToken !== 'undefined',
                    fetchHasPrivateToken: typeof fetch !== 'undefined' && 'privateToken' in Request.prototype
                };
            }
        """)
        
        print(f"\n2. Private State Token API check:")
        print(f"   document.privateToken available: {token_check.get('documentHasPrivateToken', False)}")
        print(f"   Fetch privateToken available: {token_check.get('fetchHasPrivateToken', False)}")
        
        print("\n   Note: Private State Tokens are managed by the browser")
        print("   and cannot be directly read/modified for security reasons.")
        print("   They are used for anti-fraud and privacy-preserving authentication.")
        
        browser.close()


def selenium_private_state_tokens():
    """Access Private State Tokens with Selenium."""
    print("\n" + "="*60)
    print("SELENIUM: PRIVATE STATE TOKENS")
    print("="*60)
    
    chrome_options = Options()
    chrome_options.add_argument('--headless')
    driver = webdriver.Chrome(options=chrome_options)
    
    try:
        url = "https://quotes.toscrape.com/"
        driver.get(url)
        print(f"\n1. Opened: {url}")
        
        # Check Private State Token API
        token_check = driver.execute_script("""
            return {
                documentHasPrivateToken: typeof document.privateToken !== 'undefined',
                fetchHasPrivateToken: typeof fetch !== 'undefined' && 'privateToken' in Request.prototype
            };
        """)
        
        print(f"\n2. Private State Token API check:")
        print(f"   document.privateToken available: {token_check.get('documentHasPrivateToken', False)}")
        print(f"   Fetch privateToken available: {token_check.get('fetchHasPrivateToken', False)}")
        
        print("\n   Note: Private State Tokens are browser-managed and cannot")
        print("   be directly accessed via automation for security reasons.")
        
    finally:
        driver.quit()


# ============================================================================
# EXTENSION STORAGE (Chrome Extension) - Advanced
# ============================================================================

def playwright_extension_storage():
    """Access Chrome Extension Storage with Playwright."""
    print("\n" + "="*60)
    print("PLAYWRIGHT: EXTENSION STORAGE")
    print("="*60)
    
    print("\n1. Extension Storage is accessed through Chrome Extension APIs.")
    print("   To access extension storage, you need to:")
    print("   - Load an unpacked extension")
    print("   - Use extension context to access chrome.storage API")
    
    with sync_playwright() as p:
        # Note: Loading extensions requires specific setup
        print("\n2. To load an extension with Playwright:")
        print("   context = browser.new_context()")
        print("   # Extension storage is accessible via chrome.storage API")
        print("   # from within the extension's context, not from web pages")
        
        print("\n   Example extension context:")
        print("   browser = p.chromium.launch_persistent_context(")
        print("       user_data_dir='/path/to/profile',")
        print("       headless=False,")
        print("       args=['--disable-extensions-except=/path/to/ext']")
        print("   )")
        
        print("\n3. Extension storage types:")
        print("   - chrome.storage.local: Persistent storage")
        print("   - chrome.storage.sync: Synced across devices")
        print("   - chrome.storage.session: Session-only storage")
        print("   - chrome.storage.managed: Enterprise-managed")


def selenium_extension_storage():
    """Access Chrome Extension Storage with Selenium."""
    print("\n" + "="*60)
    print("SELENIUM: EXTENSION STORAGE")
    print("="*60)
    
    print("\n1. To access extension storage with Selenium:")
    print("   chrome_options = Options()")
    print("   chrome_options.add_extension('/path/to/extension.crx')")
    print("   # or")
    print("   chrome_options.add_argument('--load-extension=/path/to/unpacked')")
    
    print("\n2. Extension storage is accessed via chrome.storage API")
    print("   from within the extension's background/content scripts.")
    print("   It cannot be directly accessed from web pages.")
    
    print("\n3. To access extension storage programmatically:")
    print("   - Use Chrome DevTools Protocol (CDP)")
    print("   - Access via extension's background page")
    print("   - Use chrome.storage.get() / chrome.storage.set()")


# ============================================================================
# MAIN EXECUTION
# ============================================================================

if __name__ == "__main__":
    print("="*60)
    print("BROWSER STORAGE ACCESS EXAMPLES")
    print("="*60)
    print("\nThis example demonstrates accessing:")
    print("  1. Local Storage")
    print("  2. Session Storage")
    print("  3. Extension Storage (info)")
    print("  4. IndexedDB")
    print("  5. Cookies")
    print("  6. Private State Tokens (info)")
    print("\nUsing both Playwright and Selenium approaches.\n")
    
    # Playwright examples
    print("\n" + "="*60)
    print("PLAYWRIGHT EXAMPLES")
    print("="*60)
    
    playwright_local_storage()
    playwright_session_storage()
    playwright_cookies()
    playwright_indexeddb()
    playwright_storage_state()
    playwright_private_state_tokens()
    playwright_extension_storage()
    
    # Selenium examples
    print("\n" + "="*60)
    print("SELENIUM EXAMPLES")
    print("="*60)
    
    selenium_local_storage()
    selenium_session_storage()
    selenium_cookies()
    selenium_indexeddb()
    selenium_private_state_tokens()
    selenium_extension_storage()
    
    print("\n" + "="*60)
    print("ALL EXAMPLES COMPLETED")
    print("="*60)
    print("\n💡 Key Points:")
    print("  ✅ Local Storage: Persistent, domain-specific")
    print("  ✅ Session Storage: Session-only, tab-specific")
    print("  ✅ Cookies: Sent with HTTP requests, domain-specific")
    print("  ✅ IndexedDB: NoSQL database in browser")
    print("  ⚠️  Extension Storage: Requires extension context, not directly accessible")
    print("  ⚠️  Private State Tokens: Browser-managed, security-protected")
    print("\n  Both Playwright and Selenium can access these storages,")
    print("  but Playwright has better built-in support for storage state management.")
