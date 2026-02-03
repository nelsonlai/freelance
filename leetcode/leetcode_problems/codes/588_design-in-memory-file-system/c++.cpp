/*
 * Problem: Design In-Memory File System
 * Difficulty: Hard
 * Tags: string, graph, hash, sort
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <unordered_map>
#include <set>
#include <vector>
#include <sstream>

using namespace std;

class FileSystem {
private:
    unordered_map<string, string> files;
    unordered_map<string, set<string>> dirs;

public:
    FileSystem() {
        
    }
    
    vector<string> ls(string path) {
        if (files.find(path) != files.end()) {
            size_t pos = path.find_last_of('/');
            return {path.substr(pos + 1)};
        }
        if (dirs.find(path) != dirs.end()) {
            return vector<string>(dirs[path].begin(), dirs[path].end());
        }
        return {};
    }
    
    void mkdir(string path) {
        stringstream ss(path);
        string segment;
        vector<string> parts;
        while (getline(ss, segment, '/')) {
            if (!segment.empty()) {
                parts.push_back(segment);
            }
        }
        
        string curr = "";
        for (int i = 0; i < parts.size(); i++) {
            string prev = curr;
            curr += "/" + parts[i];
            if (i < parts.size() - 1) {
                dirs[prev].insert(parts[i]);
            } else {
                dirs[prev].insert(parts[i]);
            }
        }
    }
    
    void addContentToFile(string filePath, string content) {
        size_t pos = filePath.find_last_of('/');
        string dir = filePath.substr(0, pos);
        string file = filePath.substr(pos + 1);
        
        if (!dir.empty()) {
            mkdir(dir);
        }
        dirs[dir].insert(file);
        files[filePath] += content;
    }
    
    string readContentFromFile(string filePath) {
        return files[filePath];
    }
};

/**
 * Your FileSystem object will be instantiated and called as such:
 * FileSystem* obj = new FileSystem();
 * vector<string> param_1 = obj->ls(path);
 * obj->mkdir(path);
 * obj->addContentToFile(filePath,content);
 * string param_4 = obj->readContentFromFile(filePath);
 */