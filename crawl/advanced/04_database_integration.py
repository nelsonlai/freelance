"""
Advanced Example 4: Database Integration
=========================================

This example demonstrates:
- How to store scraped data in a production database
- Using SQLAlchemy ORM for database operations
- Creating database models
- Batch inserts for performance
- Querying stored data
"""

from sqlalchemy import create_engine, Column, Integer, String, Text, DateTime
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import sessionmaker
from datetime import datetime
import requests
from bs4 import BeautifulSoup

Base = declarative_base()


class Quote(Base):
    """Database model for quotes."""
    __tablename__ = 'quotes'
    
    id = Column(Integer, primary_key=True, autoincrement=True)
    text = Column(Text, nullable=False)
    author = Column(String(200), nullable=False)
    tags = Column(String(500))
    source_url = Column(String(500))
    scraped_at = Column(DateTime, default=datetime.utcnow)
    
    def __repr__(self):
        return f"<Quote(id={self.id}, author='{self.author}')>"


class DatabaseScraper:
    """A scraper that stores data in a database."""
    
    def __init__(self, database_url='sqlite:///quotes.db'):
        """
        Initialize the database scraper.
        
        Args:
            database_url: Database connection URL
                          Examples:
                          - SQLite: 'sqlite:///quotes.db'
                          - PostgreSQL: 'postgresql://user:pass@localhost/dbname'
                          - MySQL: 'mysql://user:pass@localhost/dbname'
        """
        self.engine = create_engine(database_url, echo=False)
        self.Session = sessionmaker(bind=self.engine)
        
        # Create tables
        Base.metadata.create_all(self.engine)
        print(f"✅ Database initialized: {database_url}")
    
    def scrape_quotes(self, url='http://quotes.toscrape.com/', max_pages=3):
        """
        Scrape quotes and store them in the database.
        
        Args:
            url: Starting URL
            max_pages: Maximum number of pages to scrape
        """
        session = self.Session()
        scraped_count = 0
        
        try:
            current_url = url
            page = 1
            
            while page <= max_pages and current_url:
                print(f"Scraping page {page}: {current_url}")
                
                response = requests.get(current_url, timeout=10)
                response.raise_for_status()
                
                soup = BeautifulSoup(response.text, 'html.parser')
                quotes = soup.find_all('div', class_='quote')
                
                if not quotes:
                    break
                
                # Batch insert quotes
                for quote_div in quotes:
                    text_elem = quote_div.find('span', class_='text')
                    author_elem = quote_div.find('small', class_='author')
                    tags = [tag.text for tag in quote_div.find_all('a', class_='tag')]
                    
                    if text_elem and author_elem:
                        quote = Quote(
                            text=text_elem.text.strip(),
                            author=author_elem.text.strip(),
                            tags=', '.join(tags),
                            source_url=current_url
                        )
                        session.add(quote)
                        scraped_count += 1
                
                # Find next page
                next_link = soup.find('li', class_='next')
                if next_link and next_link.find('a'):
                    from urllib.parse import urljoin
                    current_url = urljoin(current_url, next_link.find('a')['href'])
                    page += 1
                else:
                    break
            
            # Commit all changes
            session.commit()
            print(f"✅ Scraped and stored {scraped_count} quotes")
            
        except Exception as e:
            session.rollback()
            print(f"❌ Error: {e}")
        finally:
            session.close()
    
    def get_all_quotes(self):
        """Retrieve all quotes from the database."""
        session = self.Session()
        try:
            quotes = session.query(Quote).all()
            return quotes
        finally:
            session.close()
    
    def get_quotes_by_author(self, author):
        """Get quotes by a specific author."""
        session = self.Session()
        try:
            quotes = session.query(Quote).filter(Quote.author == author).all()
            return quotes
        finally:
            session.close()
    
    def get_statistics(self):
        """Get statistics about stored quotes."""
        session = self.Session()
        try:
            total_quotes = session.query(Quote).count()
            authors = session.query(Quote.author).distinct().count()
            
            # Get most quoted author
            from sqlalchemy import func
            most_quoted = session.query(
                Quote.author,
                func.count(Quote.id).label('count')
            ).group_by(Quote.author).order_by(func.count(Quote.id).desc()).first()
            
            return {
                'total_quotes': total_quotes,
                'unique_authors': authors,
                'most_quoted_author': most_quoted[0] if most_quoted else None,
                'most_quoted_count': most_quoted[1] if most_quoted else 0
            }
        finally:
            session.close()


def demonstrate_database_integration():
    """Demonstrate database integration."""
    print("="*60)
    print("DATABASE INTEGRATION EXAMPLE")
    print("="*60)
    
    # Create scraper with SQLite database
    scraper = DatabaseScraper('sqlite:///quotes_production.db')
    
    # Scrape and store quotes
    print("\n1. Scraping and storing quotes...")
    scraper.scrape_quotes(max_pages=3)
    
    # Get statistics
    print("\n2. Database Statistics:")
    print("-" * 60)
    stats = scraper.get_statistics()
    print(f"   Total quotes: {stats['total_quotes']}")
    print(f"   Unique authors: {stats['unique_authors']}")
    if stats['most_quoted_author']:
        print(f"   Most quoted author: {stats['most_quoted_author']} ({stats['most_quoted_count']} quotes)")
    
    # Query examples
    print("\n3. Query Examples:")
    print("-" * 60)
    
    # Get all quotes
    all_quotes = scraper.get_all_quotes()
    print(f"\n   Total quotes in database: {len(all_quotes)}")
    
    if all_quotes:
        # Show first 3 quotes
        print(f"\n   Sample quotes (first 3):")
        for i, quote in enumerate(all_quotes[:3], 1):
            print(f"\n   {i}. {quote.text[:60]}...")
            print(f"      Author: {quote.author}")
            print(f"      Tags: {quote.tags}")
        
        # Get quotes by a specific author
        if all_quotes:
            author = all_quotes[0].author
            author_quotes = scraper.get_quotes_by_author(author)
            print(f"\n   Quotes by '{author}': {len(author_quotes)}")
    
    print("\n" + "="*60)
    print("Example completed!")
    print("="*60)
    print("\n💡 Database file: quotes_production.db")
    print("   You can query this database using SQL or SQLAlchemy")


if __name__ == "__main__":
    demonstrate_database_integration()

