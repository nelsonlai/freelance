"""
Problem: Web Crawler
Difficulty: Medium
Tags: string, search

Approach: BFS/DFS to crawl URLs with same hostname
Time Complexity: O(V + E) where V is URLs, E is links
Space Complexity: O(V) for visited set
"""

from urllib.parse import urlparse

class Solution:
    def crawl(self, startUrl: str, htmlParser: 'HtmlParser') -> List[str]:
        def get_hostname(url):
            return urlparse(url).netloc
        
        start_host = get_hostname(startUrl)
        visited = {startUrl}
        queue = [startUrl]
        
        while queue:
            url = queue.pop(0)
            for next_url in htmlParser.getUrls(url):
                if next_url not in visited and get_hostname(next_url) == start_host:
                    visited.add(next_url)
                    queue.append(next_url)
        
        return sorted(list(visited))