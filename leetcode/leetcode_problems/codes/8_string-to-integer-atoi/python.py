class Solution(object):
    def myAtoi(self, s):
        """
        :type s: str
        :rtype: int
        """
        INT_MAX = 2**31 - 1
        INT_MIN = -2**31
        
        s = s.strip()
        if not s:
            return 0
        
        sign = 1
        i = 0
        
        if s[0] == '-':
            sign = -1
            i = 1
        elif s[0] == '+':
            i = 1
        
        result = 0
        while i < len(s) and s[i].isdigit():
            digit = int(s[i])
            if result > (INT_MAX - digit) // 10:
                return INT_MAX if sign == 1 else INT_MIN
            result = result * 10 + digit
            i += 1
        
        return sign * result