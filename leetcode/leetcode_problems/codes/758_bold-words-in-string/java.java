class Solution {
    public String boldWords(String[] words, String s) {
        int n = s.length();
        boolean[] bold = new boolean[n];
        
        for (String word : words) {
            int start = 0;
            while (true) {
                int idx = s.indexOf(word, start);
                if (idx == -1) break;
                for (int i = idx; i < idx + word.length(); i++) {
                    bold[i] = true;
                }
                start = idx + 1;
            }
        }
        
        StringBuilder result = new StringBuilder();
        for (int i = 0; i < n; i++) {
            if (bold[i] && (i == 0 || !bold[i - 1])) {
                result.append("<b>");
            }
            result.append(s.charAt(i));
            if (bold[i] && (i == n - 1 || !bold[i + 1])) {
                result.append("</b>");
            }
        }
        
        return result.toString();
    }
}
