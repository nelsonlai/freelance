/**
 * Problem: Design In-Memory File System
 * Difficulty: Hard
 * Tags: string, graph, hash, sort
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class FileSystem {
    private Map<String, String> files;
    private Map<String, Set<String>> dirs;

    public FileSystem() {
        files = new HashMap<>();
        dirs = new HashMap<>();
    }
    
    public List<String> ls(String path) {
        if (files.containsKey(path)) {
            String[] parts = path.split("/");
            return Arrays.asList(parts[parts.length - 1]);
        }
        Set<String> contents = dirs.getOrDefault(path, new TreeSet<>());
        return new ArrayList<>(contents);
    }
    
    public void mkdir(String path) {
        String[] parts = path.split("/");
        for (int i = 1; i < parts.length; i++) {
            String curr = "/" + String.join("/", Arrays.copyOfRange(parts, 1, i + 1));
            if (i < parts.length - 1) {
                String parent = "/" + String.join("/", Arrays.copyOfRange(parts, 1, i));
                dirs.computeIfAbsent(parent, k -> new TreeSet<>()).add(parts[i]);
            } else {
                String parent = "/" + String.join("/", Arrays.copyOfRange(parts, 1, i));
                dirs.computeIfAbsent(parent, k -> new TreeSet<>()).add(parts[i]);
            }
        }
    }
    
    public void addContentToFile(String filePath, String content) {
        String[] parts = filePath.split("/");
        String dir = "/" + String.join("/", Arrays.copyOfRange(parts, 1, parts.length - 1));
        if (parts.length > 2) {
            mkdir(dir);
        }
        dirs.computeIfAbsent(dir, k -> new TreeSet<>()).add(parts[parts.length - 1]);
        files.put(filePath, files.getOrDefault(filePath, "") + content);
    }
    
    public String readContentFromFile(String filePath) {
        return files.get(filePath);
    }
}

/**
 * Your FileSystem object will be instantiated and called as such:
 * FileSystem obj = new FileSystem();
 * List<String> param_1 = obj.ls(path);
 * obj.mkdir(path);
 * obj.addContentToFile(filePath,content);
 * String param_4 = obj.readContentFromFile(filePath);
 */