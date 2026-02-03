object Solution {
    def addBinary(a: String, b: String): String = {
        var result = List[Char]()
        var carry = 0
        var i = a.length - 1
        var j = b.length - 1
        
        while (i >= 0 || j >= 0 || carry > 0) {
            var total = carry
            if (i >= 0) {
                total += a(i) - '0'
                i -= 1
            }
            if (j >= 0) {
                total += b(j) - '0'
                j -= 1
            }
            result = (total % 2 + '0').toChar :: result
            carry = total / 2
        }
        
        result.mkString
    }
}