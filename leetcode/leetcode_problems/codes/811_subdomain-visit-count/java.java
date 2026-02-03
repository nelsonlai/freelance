import java.util.*;

class Solution {
    public List<String> subdomainVisits(String[] cpdomains) {
        Map<String, Integer> count = new HashMap<>();
        for (String cpdomain : cpdomains) {
            String[] parts = cpdomain.split(" ");
            int visits = Integer.parseInt(parts[0]);
            String domain = parts[1];
            count.put(domain, count.getOrDefault(domain, 0) + visits);
            for (int i = 0; i < domain.length(); i++) {
                if (domain.charAt(i) == '.') {
                    String subdomain = domain.substring(i + 1);
                    count.put(subdomain, count.getOrDefault(subdomain, 0) + visits);
                }
            }
        }
        
        List<String> result = new ArrayList<>();
        for (Map.Entry<String, Integer> entry : count.entrySet()) {
            result.add(entry.getValue() + " " + entry.getKey());
        }
        return result;
    }
}
