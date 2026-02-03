/**
 * Problem: Design a File Sharing System
 * Difficulty: Medium
 * Tags: hash, sort, queue, heap
 * 
 * Approach: Use hash map for O(1) lookups
 * Time Complexity: O(n) to O(n^2) depending on approach
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class FileSharing {
    private Map<Integer, Set<Integer>> userChunks;
    private Map<Integer, Set<Integer>> chunkUsers;
    private PriorityQueue<Integer> availableIds;
    private int nextId;

    public FileSharing(int m) {
        userChunks = new HashMap<>();
        chunkUsers = new HashMap<>();
        for (int i = 1; i <= m; i++) {
            chunkUsers.put(i, new HashSet<>());
        }
        availableIds = new PriorityQueue<>();
        nextId = 1;
    }
    
    public int join(List<Integer> ownedChunks) {
        int userId;
        if (!availableIds.isEmpty()) {
            userId = availableIds.poll();
        } else {
            userId = nextId++;
        }
        
        userChunks.put(userId, new HashSet<>(ownedChunks));
        for (int chunk : ownedChunks) {
            chunkUsers.get(chunk).add(userId);
        }
        
        return userId;
    }
    
    public void leave(int userID) {
        for (int chunk : userChunks.get(userID)) {
            chunkUsers.get(chunk).remove(userID);
        }
        userChunks.remove(userID);
        availableIds.offer(userID);
    }
    
    public List<Integer> request(int userID, int chunkID) {
        List<Integer> users = new ArrayList<>(chunkUsers.get(chunkID));
        Collections.sort(users);
        if (!users.isEmpty()) {
            userChunks.get(userID).add(chunkID);
            chunkUsers.get(chunkID).add(userID);
        }
        return users;
    }
}

/**
 * Your FileSharing object will be instantiated and called as such:
 * FileSharing obj = new FileSharing(m);
 * int param_1 = obj.join(ownedChunks);
 * obj.leave(userID);
 * List<Integer> param_3 = obj.request(userID,chunkID);
 */