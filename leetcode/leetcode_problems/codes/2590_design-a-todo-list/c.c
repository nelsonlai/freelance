/*
 * Problem: Design a Todo List
 * Difficulty: Medium
 * Tags: array, string, hash, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */




typedef struct {
    
} TodoList;


TodoList* todoListCreate() {
    
}

int todoListAddTask(TodoList* obj, int userId, char* taskDescription, int dueDate, char** tags, int tagsSize) {
    
}

char** todoListGetAllTasks(TodoList* obj, int userId, int* retSize) {
    
}

char** todoListGetTasksForTag(TodoList* obj, int userId, char* tag, int* retSize) {
    
}

void todoListCompleteTask(TodoList* obj, int userId, int taskId) {
    
}

void todoListFree(TodoList* obj) {
    
}

/**
 * Your TodoList struct will be instantiated and called as such:
 * TodoList* obj = todoListCreate();
 * int param_1 = todoListAddTask(obj, userId, taskDescription, dueDate, tags, tagsSize);
 
 * char** param_2 = todoListGetAllTasks(obj, userId, retSize);
 
 * char** param_3 = todoListGetTasksForTag(obj, userId, tag, retSize);
 
 * todoListCompleteTask(obj, userId, taskId);
 
 * todoListFree(obj);
*/