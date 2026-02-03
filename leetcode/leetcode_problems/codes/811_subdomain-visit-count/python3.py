from collections import defaultdict

class Solution:
    def subdomainVisits(self, cpdomains: List[str]) -> List[str]:
        count = defaultdict(int)
        for cpdomain in cpdomains:
            parts = cpdomain.split()
            visits = int(parts[0])
            domain = parts[1]
            count[domain] += visits
            for i in range(len(domain)):
                if domain[i] == '.':
                    count[domain[i+1:]] += visits
        return [f"{v} {k}" for k, v in count.items()]
