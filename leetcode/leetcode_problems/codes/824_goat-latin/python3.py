class Solution:
    def toGoatLatin(self, sentence: str) -> str:
        vowels = set('aeiouAEIOU')
        words = sentence.split()
        result = []
        
        for i, word in enumerate(words):
            if word[0] in vowels:
                newWord = word + 'ma'
            else:
                newWord = word[1:] + word[0] + 'ma'
            newWord += 'a' * (i + 1)
            result.append(newWord)
        
        return ' '.join(result)
