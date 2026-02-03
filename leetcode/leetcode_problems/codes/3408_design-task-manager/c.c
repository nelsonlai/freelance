/*
 * Problem: Design Task Manager
 * Difficulty: Medium
 * Tags: hash, queue, heap
 * 
 * Approach: Use hash map for O(1) lookups
 * Time Complexity: O(n) to O(n^2) depending on approach
 * Space Complexity: O(n) for hash map
 */




typedef struct {
    
} TaskManager;


TaskManager* taskManagerCreate(int** tasks, int tasksSize, int* tasksColSize) {
    
}

void taskManagerAdd(TaskManager* obj, int userId, int taskId, int priority) {
    
}

void taskManagerEdit(TaskManager* obj, int taskId, int newPriority) {
    
}

void taskManagerRmv(TaskManager* obj, int taskId) {
    
}

int taskManagerExecTop(TaskManager* obj) {
    
}

void taskManagerFree(TaskManager* obj) {
    
}

/**
 * Your TaskManager struct will be instantiated and called as such:
 * TaskManager* obj = taskManagerCreate(tasks, tasksSize, tasksColSize);
 * taskManagerAdd(obj, userId, taskId, priority);
 
 * taskManagerEdit(obj, taskId, newPriority);
 
 * taskManagerRmv(obj, taskId);
 
 * int param_4 = taskManagerExecTop(obj);
 
 * taskManagerFree(obj);
*/