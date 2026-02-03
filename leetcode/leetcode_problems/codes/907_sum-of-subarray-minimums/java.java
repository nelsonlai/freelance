import java.util.*;

class Solution {
    public int sumSubarrayMins(int[] arr) {
        int MOD = 1000000007;
        Stack<Integer> stack = new Stack<>();
        long result = 0;
        
        for (int i = 0; i <= arr.length; i++) {
            while (!stack.isEmpty() && (i == arr.length || arr[stack.peek()] >= arr[i])) {
                int mid = stack.pop();
                int left = stack.isEmpty() ? -1 : stack.peek();
                int right = i;
                result = (result + (long)arr[mid] * (mid - left) * (right - mid)) % MOD;
            }
            stack.push(i);
        }
        
        return (int)result;
    }
}
