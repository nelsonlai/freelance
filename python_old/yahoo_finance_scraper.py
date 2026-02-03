# ==============================================================================
# Yahoo Finance Scraper - Working Example
# ==============================================================================
# This demonstrates the scraping techniques using Yahoo Finance, which is
# more permissive than Bloomberg. This serves as a practical example of
# the concepts shown in the Bloomberg scraper.

import requests
from bs4 import BeautifulSoup
import json
import pandas as pd
from datetime import datetime
import time
import random

class YahooFinanceScraper:
    """
    Yahoo Finance scraper - working example of scraping techniques.
    """
    
    def __init__(self):
        """
        Initialize the Yahoo Finance scraper.
        """
        self.session = requests.Session()
        self.setup_session()
    
    def setup_session(self):
        """
        Setup session with proper headers.
        """
        headers = {
            'User-Agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120.0.0.0 Safari/537.36',
            'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8',
            'Accept-Language': 'en-US,en;q=0.9',
            'Accept-Encoding': 'gzip, deflate, br',
            'Connection': 'keep-alive',
            'Upgrade-Insecure-Requests': '1',
        }
        
        self.session.headers.update(headers)
        self.session.timeout = 10
    
    def get_page(self, url: str) -> requests.Response:
        """
        Get a page with proper error handling and delays.
        """
        try:
            # Random delay to appear more human-like
            time.sleep(random.uniform(1, 2))
            
            response = self.session.get(url)
            response.raise_for_status()
            return response
            
        except requests.exceptions.RequestException as e:
            print(f"Error fetching {url}: {str(e)}")
            raise
    
    def scrape_homepage(self) -> dict:
        """
        Scrape Yahoo Finance homepage.
        """
        print("Scraping Yahoo Finance homepage...")
        
        try:
            response = self.get_page("https://finance.yahoo.com/")
            soup = BeautifulSoup(response.content, 'html.parser')
            
            data = {
                'timestamp': datetime.now().isoformat(),
                'url': response.url,
                'status_code': response.status_code,
                'title': soup.title.string if soup.title else 'No title',
                'headlines': [],
                'market_data': [],
                'trending_stocks': []
            }
            
            # Extract headlines
            print("Extracting headlines...")
            headline_selectors = [
                'h3', 'h2', 'h1',
                '[data-testid*="headline"]',
                '.js-content-viewer',
                '.Ov(h)'
            ]
            
            for selector in headline_selectors:
                elements = soup.select(selector)
                for element in elements:
                    text = element.get_text(strip=True)
                    if text and len(text) > 15:
                        data['headlines'].append({
                            'text': text,
                            'selector': selector,
                            'timestamp': datetime.now().isoformat()
                        })
            
            # Extract market data
            print("Extracting market data...")
            market_elements = soup.find_all(['span', 'div'], string=lambda text: text and any(
                keyword in text.lower() for keyword in ['nasdaq', 's&p', 'dow', '%', 'points']
            ))
            
            for element in market_elements:
                text = element.get_text(strip=True)
                if text and len(text) < 50:  # Market data is usually short
                    data['market_data'].append({
                        'text': text,
                        'timestamp': datetime.now().isoformat()
                    })
            
            # Extract trending stocks
            print("Extracting trending stocks...")
            stock_elements = soup.find_all(['a', 'span'], string=lambda text: text and '$' in text)
            
            for element in stock_elements:
                text = element.get_text(strip=True)
                if text and len(text) < 30:  # Stock symbols are short
                    data['trending_stocks'].append({
                        'text': text,
                        'timestamp': datetime.now().isoformat()
                    })
            
            # Remove duplicates
            data['headlines'] = self.remove_duplicates(data['headlines'], 'text')
            data['market_data'] = self.remove_duplicates(data['market_data'], 'text')
            data['trending_stocks'] = self.remove_duplicates(data['trending_stocks'], 'text')
            
            print(f"Scraping completed: {len(data['headlines'])} headlines, "
                  f"{len(data['market_data'])} market data points, "
                  f"{len(data['trending_stocks'])} trending stocks")
            
            return data
            
        except Exception as e:
            print(f"Error scraping Yahoo Finance: {str(e)}")
            return {'error': str(e), 'timestamp': datetime.now().isoformat()}
    
    def scrape_stock_page(self, symbol: str) -> dict:
        """
        Scrape a specific stock page.
        """
        print(f"Scraping stock page for {symbol}...")
        
        try:
            url = f"https://finance.yahoo.com/quote/{symbol}"
            response = self.get_page(url)
            soup = BeautifulSoup(response.content, 'html.parser')
            
            stock_data = {
                'symbol': symbol,
                'url': url,
                'timestamp': datetime.now().isoformat(),
                'price': '',
                'change': '',
                'change_percent': '',
                'volume': '',
                'market_cap': ''
            }
            
            # Extract price
            price_element = soup.find('fin-streamer', {'data-field': 'regularMarketPrice'})
            if price_element:
                stock_data['price'] = price_element.get_text(strip=True)
            
            # Extract change
            change_element = soup.find('fin-streamer', {'data-field': 'regularMarketChange'})
            if change_element:
                stock_data['change'] = change_element.get_text(strip=True)
            
            # Extract change percent
            change_percent_element = soup.find('fin-streamer', {'data-field': 'regularMarketChangePercent'})
            if change_percent_element:
                stock_data['change_percent'] = change_percent_element.get_text(strip=True)
            
            # Extract volume
            volume_element = soup.find('td', {'data-test': 'VOLUME-value'})
            if volume_element:
                stock_data['volume'] = volume_element.get_text(strip=True)
            
            # Extract market cap
            market_cap_element = soup.find('td', {'data-test': 'MARKET_CAP-value'})
            if market_cap_element:
                stock_data['market_cap'] = market_cap_element.get_text(strip=True)
            
            return stock_data
            
        except Exception as e:
            print(f"Error scraping stock {symbol}: {str(e)}")
            return {'error': str(e), 'symbol': symbol}
    
    def remove_duplicates(self, items: list, key: str) -> list:
        """
        Remove duplicates from a list of dictionaries based on a key.
        """
        seen = set()
        unique_items = []
        for item in items:
            if item[key] not in seen:
                seen.add(item[key])
                unique_items.append(item)
        return unique_items
    
    def save_data(self, data: dict, filename: str = None):
        """
        Save scraped data to files.
        """
        if filename is None:
            timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
            filename = f"yahoo_finance_{timestamp}"
        
        try:
            # Save as JSON
            json_filename = f"{filename}.json"
            with open(json_filename, 'w', encoding='utf-8') as f:
                json.dump(data, f, indent=2, ensure_ascii=False)
            print(f"Data saved to {json_filename}")
            
            # Save headlines as CSV
            if data.get('headlines'):
                headlines_df = pd.DataFrame(data['headlines'])
                csv_filename = f"{filename}_headlines.csv"
                headlines_df.to_csv(csv_filename, index=False, encoding='utf-8')
                print(f"Headlines saved to {csv_filename}")
            
            # Save market data as CSV
            if data.get('market_data'):
                market_df = pd.DataFrame(data['market_data'])
                csv_filename = f"{filename}_market.csv"
                market_df.to_csv(csv_filename, index=False, encoding='utf-8')
                print(f"Market data saved to {csv_filename}")
            
            # Save trending stocks as CSV
            if data.get('trending_stocks'):
                stocks_df = pd.DataFrame(data['trending_stocks'])
                csv_filename = f"{filename}_stocks.csv"
                stocks_df.to_csv(csv_filename, index=False, encoding='utf-8')
                print(f"Trending stocks saved to {csv_filename}")
                
        except Exception as e:
            print(f"Error saving data: {str(e)}")

def main():
    """
    Main function to demonstrate Yahoo Finance scraping.
    """
    scraper = YahooFinanceScraper()
    
    try:
        # Scrape Yahoo Finance homepage
        data = scraper.scrape_homepage()
        
        # Print results
        print("\n" + "="*60)
        print("YAHOO FINANCE SCRAPING RESULTS")
        print("="*60)
        
        if 'error' in data:
            print(f"Error: {data['error']}")
        else:
            print(f"Page Title: {data['title']}")
            print(f"Status Code: {data['status_code']}")
            print(f"Scraped at: {data['timestamp']}")
            print(f"Headlines: {len(data['headlines'])}")
            print(f"Market Data: {len(data['market_data'])}")
            print(f"Trending Stocks: {len(data['trending_stocks'])}")
            
            # Display sample headlines
            if data['headlines']:
                print(f"\nSample Headlines:")
                print("-" * 40)
                for i, headline in enumerate(data['headlines'][:5], 1):
                    print(f"{i}. {headline['text']}")
            
            # Display sample market data
            if data['market_data']:
                print(f"\nSample Market Data:")
                print("-" * 40)
                for i, market in enumerate(data['market_data'][:5], 1):
                    print(f"{i}. {market['text']}")
            
            # Display sample trending stocks
            if data['trending_stocks']:
                print(f"\nSample Trending Stocks:")
                print("-" * 40)
                for i, stock in enumerate(data['trending_stocks'][:5], 1):
                    print(f"{i}. {stock['text']}")
        
        # Save data
        scraper.save_data(data)
        
        # Example: Scrape specific stock
        print(f"\n" + "="*60)
        print("SCRAPING SPECIFIC STOCK EXAMPLE")
        print("="*60)
        
        stock_symbols = ['AAPL', 'GOOGL', 'MSFT']
        stock_data = []
        
        for symbol in stock_symbols:
            stock_info = scraper.scrape_stock_page(symbol)
            if 'error' not in stock_info:
                stock_data.append(stock_info)
                print(f"\n{symbol} Stock Data:")
                print(f"  Price: {stock_info.get('price', 'N/A')}")
                print(f"  Change: {stock_info.get('change', 'N/A')}")
                print(f"  Change %: {stock_info.get('change_percent', 'N/A')}")
                print(f"  Volume: {stock_info.get('volume', 'N/A')}")
                print(f"  Market Cap: {stock_info.get('market_cap', 'N/A')}")
        
        # Save stock data
        if stock_data:
            timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
            stock_filename = f"yahoo_stocks_{timestamp}"
            
            with open(f"{stock_filename}.json", 'w', encoding='utf-8') as f:
                json.dump(stock_data, f, indent=2, ensure_ascii=False)
            
            stocks_df = pd.DataFrame(stock_data)
            stocks_df.to_csv(f"{stock_filename}.csv", index=False, encoding='utf-8')
            print(f"\nStock data saved to {stock_filename}.json and {stock_filename}.csv")
        
    except Exception as e:
        print(f"Error in main execution: {str(e)}")

if __name__ == "__main__":
    main()
