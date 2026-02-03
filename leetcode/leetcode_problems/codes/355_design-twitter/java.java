/**
 * Problem: Design Twitter
 * Difficulty: Medium
 * Tags: hash, linked_list, queue, heap
 * 
 * Approach: Use hash map for O(1) lookups
 * Time Complexity: O(n) to O(n^2) depending on approach
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class Twitter {
    private int time;
    private Map<Integer, List<int[]>> tweets;
    private Map<Integer, Set<Integer>> follows;

    public Twitter() {
        time = 0;
        tweets = new HashMap<>();
        follows = new HashMap<>();
    }
    
    public void postTweet(int userId, int tweetId) {
        tweets.putIfAbsent(userId, new ArrayList<>());
        tweets.get(userId).add(new int[]{time--, tweetId});
    }
    
    public List<Integer> getNewsFeed(int userId) {
        follows.putIfAbsent(userId, new HashSet<>());
        follows.get(userId).add(userId);
        
        PriorityQueue<int[]> heap = new PriorityQueue<>((a, b) -> a[0] - b[0]);
        for (int followeeId : follows.get(userId)) {
            if (tweets.containsKey(followeeId)) {
                List<int[]> userTweets = tweets.get(followeeId);
                if (!userTweets.isEmpty()) {
                    int[] lastTweet = userTweets.get(userTweets.size() - 1);
                    heap.offer(new int[]{lastTweet[0], lastTweet[1], followeeId, userTweets.size() - 1});
                }
            }
        }
        
        List<Integer> result = new ArrayList<>();
        while (!heap.isEmpty() && result.size() < 10) {
            int[] tweet = heap.poll();
            result.add(tweet[1]);
            if (tweet[3] > 0) {
                List<int[]> userTweets = tweets.get(tweet[2]);
                int[] nextTweet = userTweets.get(tweet[3] - 1);
                heap.offer(new int[]{nextTweet[0], nextTweet[1], tweet[2], tweet[3] - 1});
            }
        }
        
        return result;
    }
    
    public void follow(int followerId, int followeeId) {
        follows.putIfAbsent(followerId, new HashSet<>());
        follows.get(followerId).add(followeeId);
    }
    
    public void unfollow(int followerId, int followeeId) {
        if (follows.containsKey(followerId)) {
            follows.get(followerId).remove(followeeId);
        }
    }
}

/**
 * Your Twitter object will be instantiated and called as such:
 * Twitter obj = new Twitter();
 * obj.postTweet(userId,tweetId);
 * List<Integer> param_2 = obj.getNewsFeed(userId);
 * obj.follow(followerId,followeeId);
 * obj.unfollow(followerId,followeeId);
 */