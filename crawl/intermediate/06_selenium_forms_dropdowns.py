"""
Intermediate Selenium Example 2: Forms and Dropdowns
====================================================

This example demonstrates:
- How to handle different form elements
- How to work with dropdowns/select elements
- How to handle checkboxes and radio buttons
- How to submit forms
"""

from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait, Select
from selenium.webdriver.support import expected_conditions as EC
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


def dropdown_example():
    """Demonstrate working with dropdown/select elements."""
    driver = setup_driver()
    
    if not driver:
        return
    
    try:
        print("="*60)
        print("DROPDOWN/SELECT ELEMENT EXAMPLE")
        print("="*60)
        
        # Use a page with a form
        url = "https://httpbin.org/forms/post"
        driver.get(url)
        time.sleep(2)
        
        print(f"\n1. Opened: {url}")
        
        wait = WebDriverWait(driver, 10)
        
        # Find select element
        try:
            select_element = wait.until(
                EC.presence_of_element_located((By.NAME, "custcard"))
            )
            
            # Create Select object
            select = Select(select_element)
            
            print("\n2. Working with dropdown:")
            
            # Get all options
            options = select.options
            print(f"   Total options: {len(options)}")
            for opt in options:
                print(f"     - {opt.text} (value: {opt.get_attribute('value')})")
            
            # Select by visible text
            select.select_by_visible_text("Visa")
            print("\n3. ✅ Selected 'Visa' by visible text")
            time.sleep(1)
            
            # Select by value
            select.select_by_value("amex")
            print("4. ✅ Selected 'American Express' by value")
            time.sleep(1)
            
            # Select by index
            select.select_by_index(0)
            print("5. ✅ Selected first option by index")
            
            # Get selected option
            selected = select.first_selected_option
            print(f"\n6. Currently selected: {selected.text}")
            
        except Exception as e:
            print(f"   ⚠️  Error with dropdown: {e}")
        
    except Exception as e:
        print(f"❌ Error: {e}")
    finally:
        driver.quit()


def checkbox_radio_example():
    """Demonstrate working with checkboxes and radio buttons."""
    driver = setup_driver()
    
    if not driver:
        return
    
    try:
        print("\n" + "="*60)
        print("CHECKBOX AND RADIO BUTTON EXAMPLE")
        print("="*60)
        
        url = "https://httpbin.org/forms/post"
        driver.get(url)
        time.sleep(2)
        
        print(f"\n1. Opened: {url}")
        
        wait = WebDriverWait(driver, 10)
        
        # Work with checkboxes
        try:
            # Find all checkboxes
            checkboxes = driver.find_elements(By.CSS_SELECTOR, "input[type='checkbox']")
            print(f"\n2. Found {len(checkboxes)} checkboxes")
            
            for i, checkbox in enumerate(checkboxes, 1):
                # Check if it's already selected
                is_selected = checkbox.is_selected()
                print(f"   Checkbox {i}: {'checked' if is_selected else 'unchecked'}")
                
                # Click to toggle
                if not is_selected:
                    checkbox.click()
                    print(f"   ✅ Checked checkbox {i}")
                    time.sleep(0.5)
            
        except Exception as e:
            print(f"   ⚠️  Error with checkboxes: {e}")
        
        # Work with radio buttons
        try:
            radio_buttons = driver.find_elements(By.CSS_SELECTOR, "input[type='radio']")
            print(f"\n3. Found {len(radio_buttons)} radio buttons")
            
            for i, radio in enumerate(radio_buttons, 1):
                value = radio.get_attribute('value')
                is_selected = radio.is_selected()
                print(f"   Radio {i}: value='{value}', selected={is_selected}")
            
            # Select a radio button
            if radio_buttons:
                radio_buttons[1].click()
                print("   ✅ Selected second radio button")
                time.sleep(1)
                
        except Exception as e:
            print(f"   ⚠️  Error with radio buttons: {e}")
        
    except Exception as e:
        print(f"❌ Error: {e}")
    finally:
        driver.quit()


def form_submission_example():
    """Demonstrate submitting a form."""
    driver = setup_driver()
    
    if not driver:
        return
    
    try:
        print("\n" + "="*60)
        print("FORM SUBMISSION EXAMPLE")
        print("="*60)
        
        url = "https://httpbin.org/forms/post"
        driver.get(url)
        time.sleep(2)
        
        print(f"\n1. Opened: {url}")
        
        wait = WebDriverWait(driver, 10)
        
        # Fill in the form
        print("\n2. Filling in form fields:")
        
        # Customer name
        name_field = wait.until(EC.presence_of_element_located((By.NAME, "custname")))
        name_field.clear()
        name_field.send_keys("Test User")
        print("   ✅ Filled customer name")
        
        # Telephone
        tel_field = driver.find_element(By.NAME, "custtel")
        tel_field.clear()
        tel_field.send_keys("555-1234")
        print("   ✅ Filled telephone")
        
        # Email
        email_field = driver.find_element(By.NAME, "custemail")
        email_field.clear()
        email_field.send_keys("test@example.com")
        print("   ✅ Filled email")
        
        # Size (radio button)
        size_radio = driver.find_element(By.CSS_SELECTOR, "input[value='medium']")
        size_radio.click()
        print("   ✅ Selected size")
        
        # Toppings (checkboxes)
        topping1 = driver.find_element(By.CSS_SELECTOR, "input[value='bacon']")
        topping1.click()
        print("   ✅ Selected topping")
        
        # Comments
        comments = driver.find_element(By.NAME, "comments")
        comments.clear()
        comments.send_keys("This is a test submission from Selenium")
        print("   ✅ Filled comments")
        
        time.sleep(1)
        
        # Submit the form
        print("\n3. Submitting form...")
        submit_button = driver.find_element(By.CSS_SELECTOR, "input[type='submit']")
        submit_button.click()
        
        # Wait for response
        wait.until(EC.url_changes(url))
        time.sleep(2)
        
        print(f"   ✅ Form submitted!")
        print(f"   New URL: {driver.current_url}")
        
        # Check if we got a response
        if "forms/post" not in driver.current_url:
            print("   ✅ Successfully submitted and received response")
        
    except Exception as e:
        print(f"❌ Error: {e}")
    finally:
        driver.quit()


if __name__ == "__main__":
    dropdown_example()
    checkbox_radio_example()
    form_submission_example()
    
    print("\n" + "="*60)
    print("All form examples completed!")
    print("="*60)
    print("\n💡 Key points:")
    print("  - Use Select class for dropdowns")
    print("  - Check is_selected() before clicking checkboxes/radios")
    print("  - Always wait for elements before interacting")
    print("  - Forms can be submitted with submit() or clicking submit button")

