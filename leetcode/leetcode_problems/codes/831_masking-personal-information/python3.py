import re

class Solution:
    def maskPII(self, s: str) -> str:
        if '@' in s:
            s = s.lower()
            name, domain = s.split('@')
            return name[0] + '*****' + name[-1] + '@' + domain
        else:
            digits = re.sub(r'\D', '', s)
            if len(digits) == 10:
                return '***-***-' + digits[-4:]
            else:
                return '+' + '*' * (len(digits) - 10) + '-***-***-' + digits[-4:]
