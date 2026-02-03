/**
 * Problem: Design Excel Sum Formula
 * Difficulty: Hard
 * Tags: array, string, graph, hash, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;
import java.util.regex.*;

class Excel {
    private Map<String, Integer> cells;
    private Map<String, String[]> formulas;

    public Excel(int height, char width) {
        cells = new HashMap<>();
        formulas = new HashMap<>();
    }
    
    public void set(int row, char column, int val) {
        String key = row + "" + column;
        cells.put(key, val);
        formulas.remove(key);
    }
    
    public int get(int row, char column) {
        String key = row + "" + column;
        if (formulas.containsKey(key)) {
            return calculateSum(formulas.get(key));
        }
        return cells.getOrDefault(key, 0);
    }
    
    public int sum(int row, char column, String[] numbers) {
        String key = row + "" + column;
        formulas.put(key, numbers);
        return calculateSum(numbers);
    }
    
    private int calculateSum(String[] numbers) {
        int total = 0;
        for (String num : numbers) {
            if (num.contains(":")) {
                total += sumRange(num);
            } else {
                total += getCellValue(num);
            }
        }
        return total;
    }
    
    private int sumRange(String range) {
        String[] parts = range.split(":");
        int[] start = parseCell(parts[0]);
        int[] end = parseCell(parts[1]);
        int total = 0;
        for (int r = start[0]; r <= end[0]; r++) {
            for (int c = start[1]; c <= end[1]; c++) {
                total += get(r, (char)('A' + c - 1));
            }
        }
        return total;
    }
    
    private int getCellValue(String cell) {
        int[] pos = parseCell(cell);
        return get(pos[0], (char)('A' + pos[1] - 1));
    }
    
    private int[] parseCell(String cell) {
        Pattern pattern = Pattern.compile("([A-Z]+)(\\d+)");
        Matcher matcher = pattern.matcher(cell);
        if (matcher.find()) {
            String colStr = matcher.group(1);
            int row = Integer.parseInt(matcher.group(2));
            int col = 0;
            for (char c : colStr.toCharArray()) {
                col = col * 26 + (c - 'A' + 1);
            }
            return new int[]{row, col};
        }
        return new int[]{0, 0};
    }
}

/**
 * Your Excel object will be instantiated and called as such:
 * Excel obj = new Excel(height, width);
 * obj.set(row,column,val);
 * int param_2 = obj.get(row,column);
 * int param_3 = obj.sum(row,column,numbers);
 */