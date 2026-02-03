"""
Problem: Web Crawler Multithreaded
Difficulty: Medium
Tags: string, search

Approach: Use threading with queue and locks for thread-safe crawling
Time Complexity: O(V + E) where V is URLs, E is links
Space Complexity: O(V) for visited set
"""

import threading
from urllib.parse import urlparse
from queue import Queue

class Solution:
    def crawl(self, startUrl: str, htmlParser: 'HtmlParser') -> List[str]:
        def get_hostname(url):
            return urlparse(url).netloc
        
        start_host = get_hostname(startUrl)
        visited = set()
        visited_lock = threading.Lock()
        queue = Queue()
        queue.put(startUrl)
        
        def worker():
            while True:
                try:
                    url = queue.get(timeout=0.1)
                except:
                    break
                
                with visited_lock:
                    if url in visited:
                        queue.task_done()
                        continue
                    visited.add(url)
                
                urls = htmlParser.getUrls(url)
                for next_url in urls:
                    if get_hostname(next_url) == start_host:
                        with visited_lock:
                            if next_url not in visited:
                                queue.put(next_url)
                
                queue.task_done()
        
        threads = [threading.Thread(target=worker) for _ in range(10)]
        for t in threads:
            t.start()
        
        queue.join()
        for t in threads:
            t.join()
        
        return sorted(list(visited))