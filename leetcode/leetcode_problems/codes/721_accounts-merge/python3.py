from collections import defaultdict

class Solution:
    def accountsMerge(self, accounts: List[List[str]]) -> List[List[str]]:
        email_to_name = {}
        graph = defaultdict(set)
        
        for account in accounts:
            name = account[0]
            for email in account[1:]:
                graph[account[1]].add(email)
                graph[email].add(account[1])
                email_to_name[email] = name
        
        visited = set()
        result = []
        
        for email in graph:
            if email not in visited:
                stack = [email]
                visited.add(email)
                emails = []
                while stack:
                    node = stack.pop()
                    emails.append(node)
                    for neighbor in graph[node]:
                        if neighbor not in visited:
                            visited.add(neighbor)
                            stack.append(neighbor)
                result.append([email_to_name[email]] + sorted(emails))
        
        return result
