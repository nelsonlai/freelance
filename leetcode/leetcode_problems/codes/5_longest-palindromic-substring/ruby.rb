# @param {String} s
# @return {String}
def longest_palindrome(s)
    return "" if s.empty?
    
    start = 0
    max_len = 1
    
    expand_around_center = lambda do |left, right|
        while left >= 0 && right < s.length && s[left] == s[right]
            left -= 1
            right += 1
        end
        right - left - 1
    end
    
    (0...s.length).each do |i|
        len1 = expand_around_center.call(i, i)
        len2 = expand_around_center.call(i, i + 1)
        len = [len1, len2].max
        
        if len > max_len
            start = i - (len - 1) / 2
            max_len = len
        end
    end
    
    s[start, max_len]
end