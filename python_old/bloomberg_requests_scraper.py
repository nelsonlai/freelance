# ==============================================================================
# Bloomberg Scraper using Requests + BeautifulSoup
# ==============================================================================
# A lightweight scraper that uses requests instead of Selenium.
# This approach is faster and less likely to be detected, but may miss
# JavaScript-rendered content.

import requests
from bs4 import BeautifulSoup
import json
import pandas as pd
from datetime import datetime
import time
import random

class BloombergRequestsScraper:
    """
    Bloomberg scraper using requests and BeautifulSoup.
    """
    
    def __init__(self):
        """
        Initialize the requests-based scraper.
        """
        self.session = requests.Session()
        self.setup_session()
    
    def setup_session(self):
        """
        Setup session with proper headers and settings.
        """
        headers = {
            'User-Agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120.0.0.0 Safari/537.36',
            'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8',
            'Accept-Language': 'en-US,en;q=0.9',
            'Accept-Encoding': 'gzip, deflate, br',
            'Connection': 'keep-alive',
            'Upgrade-Insecure-Requests': '1',
            'Sec-Fetch-Dest': 'document',
            'Sec-Fetch-Mode': 'navigate',
            'Sec-Fetch-Site': 'none',
            'Cache-Control': 'max-age=0'
        }
        
        self.session.headers.update(headers)
        
        # Add some randomness to requests
        self.session.timeout = 10
    
    def get_page(self, url: str) -> requests.Response:
        """
        Get a page with proper error handling and delays.
        """
        try:
            # Random delay to appear more human-like
            time.sleep(random.uniform(1, 3))
            
            response = self.session.get(url)
            response.raise_for_status()
            return response
            
        except requests.exceptions.RequestException as e:
            print(f"Error fetching {url}: {str(e)}")
            raise
    
    def scrape_bloomberg_homepage(self) -> dict:
        """
        Scrape Bloomberg homepage for headlines and links.
        """
        print("Scraping Bloomberg homepage with requests...")
        
        try:
            # Get the main page
            response = self.get_page("https://www.bloomberg.com/")
            soup = BeautifulSoup(response.content, 'html.parser')
            
            data = {
                'timestamp': datetime.now().isoformat(),
                'url': response.url,
                'status_code': response.status_code,
                'title': soup.title.string if soup.title else 'No title',
                'headlines': [],
                'article_links': [],
                'market_data': []
            }
            
            # Extract headlines
            print("Extracting headlines...")
            headline_tags = ['h1', 'h2', 'h3', 'h4']
            for tag in headline_tags:
                elements = soup.find_all(tag)
                for element in elements:
                    text = element.get_text(strip=True)
                    if text and len(text) > 15:  # Filter out short text
                        data['headlines'].append({
                            'text': text,
                            'tag': tag,
                            'class': element.get('class', []),
                            'timestamp': datetime.now().isoformat()
                        })
            
            # Extract article links
            print("Extracting article links...")
            links = soup.find_all('a', href=True)
            for link in links:
                href = link.get('href')
                text = link.get_text(strip=True)
                
                # Filter for news/article links
                if (href and text and 
                    len(text) > 10 and 
                    any(keyword in href.lower() for keyword in ['/news/', '/markets/', '/businessweek/', '/opinion/'])):
                    
                    # Make absolute URL
                    if href.startswith('/'):
                        href = 'https://www.bloomberg.com' + href
                    
                    data['article_links'].append({
                        'title': text,
                        'url': href,
                        'timestamp': datetime.now().isoformat()
                    })
            
            # Try to extract market data
            print("Extracting market data...")
            market_elements = soup.find_all(['span', 'div'], class_=lambda x: x and any(
                keyword in x.lower() for keyword in ['market', 'quote', 'price', 'index']
            ))
            
            for element in market_elements:
                text = element.get_text(strip=True)
                if text and any(char.isdigit() for char in text):
                    data['market_data'].append({
                        'text': text,
                        'class': element.get('class', []),
                        'timestamp': datetime.now().isoformat()
                    })
            
            # Remove duplicates
            data['headlines'] = self.remove_duplicates(data['headlines'], 'text')
            data['article_links'] = self.remove_duplicates(data['article_links'], 'url')
            data['market_data'] = self.remove_duplicates(data['market_data'], 'text')
            
            print(f"Scraping completed: {len(data['headlines'])} headlines, "
                  f"{len(data['article_links'])} articles, "
                  f"{len(data['market_data'])} market data points")
            
            return data
            
        except Exception as e:
            print(f"Error scraping Bloomberg: {str(e)}")
            return {'error': str(e), 'timestamp': datetime.now().isoformat()}
    
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
    
    def scrape_article(self, url: str) -> dict:
        """
        Scrape a specific Bloomberg article.
        """
        print(f"Scraping article: {url}")
        
        try:
            response = self.get_page(url)
            soup = BeautifulSoup(response.content, 'html.parser')
            
            # Extract article content
            article_data = {
                'url': url,
                'timestamp': datetime.now().isoformat(),
                'title': '',
                'content': '',
                'author': '',
                'publish_date': ''
            }
            
            # Try to find title
            title_selectors = ['h1', '.headline', '.article-title', '[data-module="ArticleHeadline"]']
            for selector in title_selectors:
                title_elem = soup.select_one(selector)
                if title_elem:
                    article_data['title'] = title_elem.get_text(strip=True)
                    break
            
            # Try to find content
            content_selectors = ['.article-content', '.story-body', '.article-body', '[data-module="ArticleBody"]']
            for selector in content_selectors:
                content_elem = soup.select_one(selector)
                if content_elem:
                    article_data['content'] = content_elem.get_text(strip=True)
                    break
            
            # Try to find author
            author_selectors = ['.byline', '.author', '[data-module="Byline"]']
            for selector in author_selectors:
                author_elem = soup.select_one(selector)
                if author_elem:
                    article_data['author'] = author_elem.get_text(strip=True)
                    break
            
            return article_data
            
        except Exception as e:
            print(f"Error scraping article {url}: {str(e)}")
            return {'error': str(e), 'url': url}
    
    def save_data(self, data: dict, filename: str = None):
        """
        Save scraped data to files.
        """
        if filename is None:
            timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
            filename = f"bloomberg_requests_{timestamp}"
        
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
            
            # Save article links as CSV
            if data.get('article_links'):
                articles_df = pd.DataFrame(data['article_links'])
                csv_filename = f"{filename}_articles.csv"
                articles_df.to_csv(csv_filename, index=False, encoding='utf-8')
                print(f"Article links saved to {csv_filename}")
            
            # Save market data as CSV
            if data.get('market_data'):
                market_df = pd.DataFrame(data['market_data'])
                csv_filename = f"{filename}_market.csv"
                market_df.to_csv(csv_filename, index=False, encoding='utf-8')
                print(f"Market data saved to {csv_filename}")
                
        except Exception as e:
            print(f"Error saving data: {str(e)}")

def main():
    """
    Main function to demonstrate Bloomberg scraping with requests.
    """
    scraper = BloombergRequestsScraper()
    
    try:
        # Scrape Bloomberg homepage
        data = scraper.scrape_bloomberg_homepage()
        
        # Print results
        print("\n" + "="*60)
        print("BLOOMBERG REQUESTS SCRAPING RESULTS")
        print("="*60)
        
        if 'error' in data:
            print(f"Error: {data['error']}")
        else:
            print(f"Page Title: {data['title']}")
            print(f"Status Code: {data['status_code']}")
            print(f"Scraped at: {data['timestamp']}")
            print(f"Headlines: {len(data['headlines'])}")
            print(f"Article Links: {len(data['article_links'])}")
            print(f"Market Data: {len(data['market_data'])}")
            
            # Display sample headlines
            if data['headlines']:
                print(f"\nSample Headlines:")
                print("-" * 40)
                for i, headline in enumerate(data['headlines'][:5], 1):
                    print(f"{i}. {headline['text']}")
            
            # Display sample article links
            if data['article_links']:
                print(f"\nSample Article Links:")
                print("-" * 40)
                for i, article in enumerate(data['article_links'][:3], 1):
                    print(f"{i}. {article['title']}")
                    print(f"   URL: {article['url']}")
            
            # Display sample market data
            if data['market_data']:
                print(f"\nSample Market Data:")
                print("-" * 40)
                for i, market in enumerate(data['market_data'][:5], 1):
                    print(f"{i}. {market['text']}")
        
        # Save data
        scraper.save_data(data)
        
    except Exception as e:
        print(f"Error in main execution: {str(e)}")

if __name__ == "__main__":
    main()
