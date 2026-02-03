class Solution {
    fun addBinary(a: String, b: String): String {
        val result = StringBuilder()
        var carry = 0
        var i = a.length - 1
        var j = b.length - 1
        
        while (i >= 0 || j >= 0 || carry > 0) {
            var total = carry
            if (i >= 0) {
                total += a[i--] - '0'
            }
            if (j >= 0) {
                total += b[j--] - '0'
            }
            result.append(total % 2)
            carry = total / 2
        }
        
        return result.reverse().toString()
    }
}