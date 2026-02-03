import java.util.*;

class Solution {
    private int i;
    private String formula;
    
    public String countOfAtoms(String formula) {
        this.formula = formula;
        this.i = 0;
        Map<String, Integer> count = parse();
        
        List<String> atoms = new ArrayList<>(count.keySet());
        Collections.sort(atoms);
        StringBuilder result = new StringBuilder();
        for (String atom : atoms) {
            result.append(atom);
            if (count.get(atom) > 1) {
                result.append(count.get(atom));
            }
        }
        return result.toString();
    }
    
    private Map<String, Integer> parse() {
        Map<String, Integer> count = new HashMap<>();
        while (i < formula.length()) {
            if (formula.charAt(i) == '(') {
                i++;
                Map<String, Integer> inner = parse();
                i++;
                int num = getNum();
                for (Map.Entry<String, Integer> entry : inner.entrySet()) {
                    count.put(entry.getKey(), count.getOrDefault(entry.getKey(), 0) + entry.getValue() * num);
                }
            } else if (formula.charAt(i) == ')') {
                break;
            } else {
                String atom = getAtom();
                int num = getNum();
                count.put(atom, count.getOrDefault(atom, 0) + num);
            }
        }
        return count;
    }
    
    private String getAtom() {
        int start = i;
        i++;
        while (i < formula.length() && Character.isLowerCase(formula.charAt(i))) {
            i++;
        }
        return formula.substring(start, i);
    }
    
    private int getNum() {
        if (i >= formula.length() || !Character.isDigit(formula.charAt(i))) {
            return 1;
        }
        int num = 0;
        while (i < formula.length() && Character.isDigit(formula.charAt(i))) {
            num = num * 10 + (formula.charAt(i) - '0');
            i++;
        }
        return num;
    }
}
