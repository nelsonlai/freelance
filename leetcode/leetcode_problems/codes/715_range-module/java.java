import java.util.*;

class RangeModule {
    private List<int[]> ranges;

    public RangeModule() {
        ranges = new ArrayList<>();
    }
    
    public void addRange(int left, int right) {
        List<int[]> newRanges = new ArrayList<>();
        boolean inserted = false;
        for (int[] range : ranges) {
            if (range[1] < left) {
                newRanges.add(range);
            } else if (range[0] > right) {
                if (!inserted) {
                    newRanges.add(new int[]{left, right});
                    inserted = true;
                }
                newRanges.add(range);
            } else {
                left = Math.min(left, range[0]);
                right = Math.max(right, range[1]);
            }
        }
        if (!inserted) {
            newRanges.add(new int[]{left, right});
        }
        ranges = newRanges;
    }
    
    public boolean queryRange(int left, int right) {
        for (int[] range : ranges) {
            if (range[0] <= left && right <= range[1]) {
                return true;
            }
        }
        return false;
    }
    
    public void removeRange(int left, int right) {
        List<int[]> newRanges = new ArrayList<>();
        for (int[] range : ranges) {
            if (range[1] < left || range[0] > right) {
                newRanges.add(range);
            } else {
                if (range[0] < left) {
                    newRanges.add(new int[]{range[0], left});
                }
                if (range[1] > right) {
                    newRanges.add(new int[]{right, range[1]});
                }
            }
        }
        ranges = newRanges;
    }
}
