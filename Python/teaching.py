'''
題目：
寫一個函式 is_palindrome(s) 判斷字串是否為回文。
回文意思是正著念、反著念都一樣，例如 "level"、"madam"。

輸入："level" → 回傳 True
輸入："hello" → 回傳 False
'''
def is_palindrome(s):
    return s == s[::-1]

if __name__ == "__main__":
    # 測試程式碼
    print(is_palindrome("level"))  # True
    print(is_palindrome("madam"))  # True
    print(is_palindrome("racecar"))  # True
    print(is_palindrome("hello"))  # False