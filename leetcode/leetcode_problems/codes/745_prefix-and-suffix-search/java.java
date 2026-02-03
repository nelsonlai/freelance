import java.util.*;

class WordFilter {
    private Map<String, List<Integer>> prefix;
    private Map<String, List<Integer>> suffix;

    public WordFilter(String[] words) {
        prefix = new HashMap<>();
        suffix = new HashMap<>();
        for (int i = 0; i < words.length; i++) {
            String word = words[i];
            for (int j = 0; j <= word.length(); j++) {
                String pre = word.substring(0, j);
                String suf = word.substring(j);
                prefix.computeIfAbsent(pre, k -> new ArrayList<>()).add(i);
                suffix.computeIfAbsent(suf, k -> new ArrayList<>()).add(i);
            }
        }
    }
    
    public int f(String pref, String suff) {
        if (!prefix.containsKey(pref) || !suffix.containsKey(suff)) {
            return -1;
        }
        Set<Integer> prefixSet = new HashSet<>(prefix.get(pref));
        Set<Integer> suffixSet = new HashSet<>(suffix.get(suff));
        prefixSet.retainAll(suffixSet);
        return prefixSet.isEmpty() ? -1 : Collections.max(prefixSet);
    }
}
