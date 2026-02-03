"""
Intermediate Example 4: Storing Scraped Data
=============================================

This example demonstrates:
- How to save data to CSV files
- How to save data to JSON files
- How to save data to Excel files
- How to save data to a database (SQLite)
"""

import requests
from bs4 import BeautifulSoup
import json
import csv
import sqlite3
from datetime import datetime

# Try to import pandas, but make it optional in case of compatibility issues
try:
    import pandas as pd
    PANDAS_AVAILABLE = True
except (ImportError, ValueError) as e:
    PANDAS_AVAILABLE = False
    print(f"⚠️  Note: pandas is not available ({type(e).__name__})")
    print("   Excel export will be skipped. Other formats (CSV, JSON, DB) will still work.")
    print("   To fix: pip install --upgrade pandas numpy openpyxl")
    print()

def scrape_sample_data():
    """Scrape some sample data for demonstration."""
    url = "http://quotes.toscrape.com/"
    
    print("Scraping sample data...")
    response = requests.get(url, timeout=10)
    response.raise_for_status()
    
    soup = BeautifulSoup(response.text, 'html.parser')
    quotes = soup.find_all('div', class_='quote')
    
    data = []
    for quote in quotes:
        text_elem = quote.find('span', class_='text')
        author_elem = quote.find('small', class_='author')
        tags = [tag.text for tag in quote.find_all('a', class_='tag')]
        
        data.append({
            'text': text_elem.text.strip() if text_elem else '',
            'author': author_elem.text.strip() if author_elem else '',
            'tags': ', '.join(tags),
            'scraped_at': datetime.now().isoformat()
        })
    
    print(f"Scraped {len(data)} items")
    return data


def save_to_json(data, filename='data.json'):
    """Save data to a JSON file."""
    print(f"\nSaving to JSON: {filename}")
    
    with open(filename, 'w', encoding='utf-8') as f:
        json.dump(data, f, indent=2, ensure_ascii=False)
    
    print(f"✅ Saved {len(data)} items to {filename}")


def save_to_csv(data, filename='data.csv'):
    """Save data to a CSV file."""
    print(f"\nSaving to CSV: {filename}")
    
    if not data:
        print("No data to save")
        return
    
    keys = data[0].keys()
    with open(filename, 'w', newline='', encoding='utf-8') as f:
        writer = csv.DictWriter(f, fieldnames=keys)
        writer.writeheader()
        writer.writerows(data)
    
    print(f"✅ Saved {len(data)} items to {filename}")


def save_to_excel(data, filename='data.xlsx'):
    """Save data to an Excel file using pandas."""
    print(f"\nSaving to Excel: {filename}")
    
    if not PANDAS_AVAILABLE:
        print("⚠️  Skipped: pandas is not available or has compatibility issues")
        print("   To fix this, try: pip install --upgrade pandas numpy openpyxl")
        print("   Or reinstall: pip uninstall pandas numpy && pip install pandas numpy openpyxl")
        return
    
    if not data:
        print("No data to save")
        return
    
    try:
        df = pd.DataFrame(data)
        df.to_excel(filename, index=False, engine='openpyxl')
        print(f"✅ Saved {len(data)} items to {filename}")
    except Exception as e:
        print(f"⚠️  Error saving to Excel: {e}")
        print("   This might be a pandas/numpy compatibility issue.")
        print("   Try: pip install --upgrade pandas numpy openpyxl")


def save_to_database(data, db_name='scraped_data.db'):
    """Save data to a SQLite database."""
    print(f"\nSaving to database: {db_name}")
    
    if not data:
        print("No data to save")
        return
    
    # Connect to database (creates if doesn't exist)
    conn = sqlite3.connect(db_name)
    cursor = conn.cursor()
    
    # Create table
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS quotes (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            text TEXT NOT NULL,
            author TEXT NOT NULL,
            tags TEXT,
            scraped_at TEXT
        )
    ''')
    
    # Insert data
    for item in data:
        cursor.execute('''
            INSERT INTO quotes (text, author, tags, scraped_at)
            VALUES (?, ?, ?, ?)
        ''', (item['text'], item['author'], item['tags'], item['scraped_at']))
    
    # Commit and close
    conn.commit()
    conn.close()
    
    print(f"✅ Saved {len(data)} items to database {db_name}")


def read_from_database(db_name='scraped_data.db'):
    """Read data from the database."""
    print(f"\nReading from database: {db_name}")
    
    conn = sqlite3.connect(db_name)
    cursor = conn.cursor()
    
    cursor.execute('SELECT * FROM quotes')
    rows = cursor.fetchall()
    
    conn.close()
    
    print(f"✅ Retrieved {len(rows)} items from database")
    return rows


def demonstrate_all_formats():
    """Demonstrate saving data in all formats."""
    print("="*60)
    print("DATA STORAGE DEMONSTRATION")
    print("="*60)
    
    # Scrape sample data
    data = scrape_sample_data()
    
    if not data:
        print("No data to save")
        return
    
    # Save in different formats
    save_to_json(data, 'quotes.json')
    save_to_csv(data, 'quotes.csv')
    save_to_excel(data, 'quotes.xlsx')
    save_to_database(data, 'quotes.db')
    
    # Demonstrate reading from database
    print("\n" + "="*60)
    print("READING FROM DATABASE")
    print("="*60)
    rows = read_from_database('quotes.db')
    
    if rows:
        print(f"\nSample data from database (first 2 rows):")
        for i, row in enumerate(rows[:2], 1):
            print(f"\n{i}. ID: {row[0]}")
            print(f"   Text: {row[1][:50]}...")
            print(f"   Author: {row[2]}")
            print(f"   Tags: {row[3]}")
            print(f"   Scraped at: {row[4]}")


if __name__ == "__main__":
    demonstrate_all_formats()
    
    print("\n" + "="*60)
    print("Example completed!")
    print("="*60)
    print("\n📁 Files created:")
    print("  - quotes.json (JSON format)")
    print("  - quotes.csv (CSV format)")
    if PANDAS_AVAILABLE:
        print("  - quotes.xlsx (Excel format)")
    else:
        print("  - quotes.xlsx (Excel format) - SKIPPED (pandas not available)")
    print("  - quotes.db (SQLite database)")

