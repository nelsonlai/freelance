/**
 * Problem: Design Snake Game
 * Difficulty: Medium
 * Tags: array, string, hash, queue
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class SnakeGame {
    private int width;
    private int height;
    private Queue<int[]> food;
    private Deque<int[]> snake;
    private Map<String, int[]> directions;
    private int score;

    public SnakeGame(int width, int height, int[][] food) {
        this.width = width;
        this.height = height;
        this.food = new LinkedList<>();
        for (int[] f : food) {
            this.food.offer(f);
        }
        this.snake = new LinkedList<>();
        this.snake.offer(new int[]{0, 0});
        this.directions = new HashMap<>();
        directions.put("U", new int[]{-1, 0});
        directions.put("D", new int[]{1, 0});
        directions.put("L", new int[]{0, -1});
        directions.put("R", new int[]{0, 1});
        this.score = 0;
    }
    
    public int move(String direction) {
        int[] dir = directions.get(direction);
        int[] head = snake.peekFirst();
        int[] newHead = {head[0] + dir[0], head[1] + dir[1]};
        
        if (newHead[0] < 0 || newHead[0] >= height || 
            newHead[1] < 0 || newHead[1] >= width) {
            return -1;
        }
        
        if (!food.isEmpty() && Arrays.equals(newHead, food.peek())) {
            food.poll();
            score++;
        } else {
            snake.pollLast();
        }
        
        for (int[] body : snake) {
            if (Arrays.equals(body, newHead)) {
                return -1;
            }
        }
        
        snake.offerFirst(newHead);
        return score;
    }
}

/**
 * Your SnakeGame object will be instantiated and called as such:
 * SnakeGame obj = new SnakeGame(width, height, food);
 * int param_1 = obj.move(direction);
 */