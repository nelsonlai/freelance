import java.util.*;

class ExamRoom {
    private int n;
    private TreeSet<int[]> starts;
    private Map<Integer, int[]> startMap;
    private Map<Integer, int[]> endMap;

    public ExamRoom(int n) {
        this.n = n;
        this.starts = new TreeSet<>((a, b) -> {
            int distA = distance(a[0], a[1]);
            int distB = distance(b[0], b[1]);
            if (distA != distB) return distB - distA;
            return a[0] - b[0];
        });
        this.startMap = new HashMap<>();
        this.endMap = new HashMap<>();
        int[] interval = {-1, n};
        starts.add(interval);
        startMap.put(-1, interval);
        endMap.put(n, interval);
    }

    public int seat() {
        int[] interval = starts.pollFirst();
        int left = interval[0], right = interval[1];
        int seat;
        if (left == -1) {
            seat = 0;
        } else if (right == n) {
            seat = n - 1;
        } else {
            seat = (left + right) / 2;
        }
        
        int[] leftInterval = {left, seat};
        int[] rightInterval = {seat, right};
        starts.add(leftInterval);
        starts.add(rightInterval);
        startMap.put(left, leftInterval);
        startMap.put(seat, rightInterval);
        endMap.put(seat, leftInterval);
        endMap.put(right, rightInterval);
        
        return seat;
    }

    public void leave(int p) {
        int[] leftInterval = endMap.get(p);
        int[] rightInterval = startMap.get(p);
        int left = leftInterval[0];
        int right = rightInterval[1];
        
        starts.remove(leftInterval);
        starts.remove(rightInterval);
        startMap.remove(left);
        startMap.remove(p);
        endMap.remove(p);
        endMap.remove(right);
        
        int[] newInterval = {left, right};
        starts.add(newInterval);
        startMap.put(left, newInterval);
        endMap.put(right, newInterval);
    }

    private int distance(int left, int right) {
        if (left == -1) return right;
        if (right == n) return n - 1 - left;
        return (right - left) / 2;
    }
}
