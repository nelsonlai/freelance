/*
 * Problem: Serialize and Deserialize N-ary Tree
 * Difficulty: Hard
 * Tags: string, tree, search
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {
        // TODO: Implement optimized solution
        return 0;
    }

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

#include <string>
#include <vector>
#include <sstream>

using namespace std;

class Codec {
private:
    void dfsSerialize(Node* node, vector<string>& result) {
        if (!node) {
            return;
        }
        result.push_back(to_string(node->val));
        result.push_back(to_string(node->children.size()));
        for (Node* child : node->children) {
            dfsSerialize(child, result);
        }
    }
    
    Node* dfsDeserialize(vector<string>& values, int& index) {
        if (index >= values.size()) {
            return nullptr;
        }
        
        int val = stoi(values[index++]);
        int numChildren = stoi(values[index++]);
        
        vector<Node*> children;
        for (int i = 0; i < numChildren; i++) {
            children.push_back(dfsDeserialize(values, index));
        }
        
        return new Node(val, children);
    }

public:
    // Encodes a tree to a single string.
    string serialize(Node* root) {
        if (!root) {
            return "";
        }
        
        vector<string> result;
        dfsSerialize(root, result);
        
        stringstream ss;
        for (int i = 0; i < result.size(); i++) {
            if (i > 0) ss << ",";
            ss << result[i];
        }
        return ss.str();
    }
	
    // Decodes your encoded data to tree.
    Node* deserialize(string data) {
        if (data.empty()) {
            return nullptr;
        }
        
        vector<string> values;
        stringstream ss(data);
        string item;
        while (getline(ss, item, ',')) {
            values.push_back(item);
        }
        
        int index = 0;
        return dfsDeserialize(values, index);
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));