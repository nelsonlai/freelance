# @param {String} s
# @param {String[]} words
# @return {Integer[]}
def find_substring(s, words)
    result = []
    return result if s.nil? || s.empty? || words.nil? || words.empty?
    
    word_len = words[0].length
    word_count = Hash.new(0)
    words.each { |word| word_count[word] += 1 }
    
    (0...word_len).each do |i|
        left = i
        seen = Hash.new(0)
        count = 0
        
        j = i
        while j <= s.length - word_len
            word = s[j, word_len]
            
            if word_count.key?(word)
                seen[word] += 1
                count += 1
                
                while seen[word] > word_count[word]
                    left_word = s[left, word_len]
                    seen[left_word] -= 1
                    count -= 1
                    left += word_len
                end
                
                if count == words.length
                    result << left
                    left_word = s[left, word_len]
                    seen[left_word] -= 1
                    count -= 1
                    left += word_len
                end
            else
                seen.clear
                count = 0
                left = j + word_len
            end
            j += word_len
        end
    end
    
    result
end