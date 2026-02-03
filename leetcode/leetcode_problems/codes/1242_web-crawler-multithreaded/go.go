// Problem: Web Crawler Multithreaded
// Difficulty: Medium
// Tags: string, search
// 
// Approach: String manipulation with hash map or two pointers
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(1) to O(n) depending on approach

import (
    "math/rand"
    "time"
)


/*
 This is HtmlParser's API interface.
 You should not implement it, or speculate about its implementation
    type HtmlParser struct {
        maps  map[string]int
        imaps map[int]string
        a     map[int][]int
    }
*/
func crawl(startUrl string, htmlParser *HtmlParser) []string {
    
}