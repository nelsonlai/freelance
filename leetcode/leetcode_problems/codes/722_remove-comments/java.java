import java.util.*;

class Solution {
    public List<String> removeComments(String[] source) {
        boolean inBlock = false;
        List<String> result = new ArrayList<>();
        StringBuilder newline = new StringBuilder();
        
        for (String line : source) {
            int i = 0;
            if (!inBlock) {
                newline = new StringBuilder();
            }
            while (i < line.length()) {
                if (!inBlock && i + 1 < line.length() && line.substring(i, i + 2).equals("/*")) {
                    inBlock = true;
                    i += 2;
                } else if (inBlock && i + 1 < line.length() && line.substring(i, i + 2).equals("*/")) {
                    inBlock = false;
                    i += 2;
                } else if (!inBlock && i + 1 < line.length() && line.substring(i, i + 2).equals("//")) {
                    break;
                } else if (!inBlock) {
                    newline.append(line.charAt(i));
                    i++;
                } else {
                    i++;
                }
            }
            if (!inBlock && newline.length() > 0) {
                result.add(newline.toString());
            }
        }
        
        return result;
    }
}
