object Solution {
    def isPalindrome(x: Int): Boolean = {
        if (x < 0 || (x != 0 && x % 10 == 0)) {
            return false
        }
        
        var x = x
        var reversedHalf = 0
        
        while (x > reversedHalf) {
            reversedHalf = reversedHalf * 10 + x % 10
            x /= 10
        }
        
        x == reversedHalf || x == reversedHalf / 10
    }
}