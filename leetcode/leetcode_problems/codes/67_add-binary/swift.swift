class Solution {
    func addBinary(_ a: String, _ b: String) -> String {
        var result = ""
        var carry = 0
        var i = a.count - 1
        var j = b.count - 1
        let aArray = Array(a)
        let bArray = Array(b)
        
        while i >= 0 || j >= 0 || carry > 0 {
            var total = carry
            if i >= 0 {
                total += Int(String(aArray[i])) ?? 0
                i -= 1
            }
            if j >= 0 {
                total += Int(String(bArray[j])) ?? 0
                j -= 1
            }
            result = String(total % 2) + result
            carry = total / 2
        }
        
        return result
    }
}