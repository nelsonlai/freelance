class Solution(object):
    def lengthOfLastWord(self, s):
        """
        :type s: str
        :rtype: int
        """
        s = s.rstrip()
        length = 0
        for i in range(len(s) - 1, -1, -1):
            if s[i] == ' ':
                break
            length += 1
        return length