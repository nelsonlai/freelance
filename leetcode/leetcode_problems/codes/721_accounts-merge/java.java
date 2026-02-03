import java.util.*;

class Solution {
    public List<List<String>> accountsMerge(List<List<String>> accounts) {
        Map<String, String> emailToName = new HashMap<>();
        Map<String, Set<String>> graph = new HashMap<>();
        
        for (List<String> account : accounts) {
            String name = account.get(0);
            for (int i = 1; i < account.size(); i++) {
                String email = account.get(i);
                graph.computeIfAbsent(account.get(1), k -> new HashSet<>()).add(email);
                graph.computeIfAbsent(email, k -> new HashSet<>()).add(account.get(1));
                emailToName.put(email, name);
            }
        }
        
        Set<String> visited = new HashSet<>();
        List<List<String>> result = new ArrayList<>();
        
        for (String email : graph.keySet()) {
            if (!visited.contains(email)) {
                Stack<String> stack = new Stack<>();
                stack.push(email);
                visited.add(email);
                List<String> emails = new ArrayList<>();
                while (!stack.isEmpty()) {
                    String node = stack.pop();
                    emails.add(node);
                    for (String neighbor : graph.get(node)) {
                        if (!visited.contains(neighbor)) {
                            visited.add(neighbor);
                            stack.push(neighbor);
                        }
                    }
                }
                Collections.sort(emails);
                emails.add(0, emailToName.get(email));
                result.add(emails);
            }
        }
        
        return result;
    }
}
