/**
 * Problem: Stone Game
 * Difficulty: Medium
 * 
 * Approach: Mathematical observation
 * Since there are an even number of piles and the total number of stones is odd,
 * the first player can always win by choosing the optimal strategy.
 * The first player can always choose either all odd-indexed or all even-indexed piles,
 * whichever has more stones, ensuring a win.
 * 
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 */
class Solution {
    public boolean stoneGame(int[] piles) {
        // The first player can always win due to the game's constraints
        // (even number of piles, odd total stones)
        return true;
    }
}
