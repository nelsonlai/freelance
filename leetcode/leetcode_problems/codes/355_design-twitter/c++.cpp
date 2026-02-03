/*
 * Problem: Design Twitter
 * Difficulty: Medium
 * Tags: hash, linked_list, queue, heap
 * 
 * Approach: Use hash map for O(1) lookups
 * Time Complexity: O(n) to O(n^2) depending on approach
 * Space Complexity: O(n) for hash map
 */

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <algorithm>

using namespace std;

class Twitter {
private:
    int time;
    unordered_map<int, vector<pair<int, int>>> tweets;
    unordered_map<int, unordered_set<int>> follows;

public:
    Twitter() {
        time = 0;
    }
    
    void postTweet(int userId, int tweetId) {
        tweets[userId].push_back({time--, tweetId});
    }
    
    vector<int> getNewsFeed(int userId) {
        follows[userId].insert(userId);
        
        priority_queue<pair<int, int>> heap;
        for (int followeeId : follows[userId]) {
            if (tweets.find(followeeId) != tweets.end()) {
                vector<pair<int, int>>& userTweets = tweets[followeeId];
                if (!userTweets.empty()) {
                    pair<int, int> lastTweet = userTweets.back();
                    heap.push({lastTweet.first, lastTweet.second});
                }
            }
        }
        
        vector<int> result;
        while (!heap.empty() && result.size() < 10) {
            result.push_back(heap.top().second);
            heap.pop();
        }
        
        return result;
    }
    
    void follow(int followerId, int followeeId) {
        follows[followerId].insert(followeeId);
    }
    
    void unfollow(int followerId, int followeeId) {
        if (follows.find(followerId) != follows.end()) {
            follows[followerId].erase(followeeId);
        }
    }
};

/**
 * Your Twitter object will be instantiated and called as such:
 * Twitter* obj = new Twitter();
 * obj->postTweet(userId,tweetId);
 * vector<int> param_2 = obj->getNewsFeed(userId);
 * obj->follow(followerId,followeeId);
 * obj->unfollow(followerId,followeeId);
 */