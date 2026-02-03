/*
 * Problem: Design SQL
 * Difficulty: Medium
 * Tags: array, string, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */




typedef struct {
    
} SQL;


SQL* sQLCreate(char** names, int namesSize, int* columns, int columnsSize) {
    
}

bool sQLIns(SQL* obj, char* name, char** row, int rowSize) {
    
}

void sQLRmv(SQL* obj, char* name, int rowId) {
    
}

char* sQLSel(SQL* obj, char* name, int rowId, int columnId) {
    
}

char** sQLExp(SQL* obj, char* name, int* retSize) {
    
}

void sQLFree(SQL* obj) {
    
}

/**
 * Your SQL struct will be instantiated and called as such:
 * SQL* obj = sQLCreate(names, namesSize, columns, columnsSize);
 * bool param_1 = sQLIns(obj, name, row, rowSize);
 
 * sQLRmv(obj, name, rowId);
 
 * char* param_3 = sQLSel(obj, name, rowId, columnId);
 
 * char** param_4 = sQLExp(obj, name, retSize);
 
 * sQLFree(obj);
*/