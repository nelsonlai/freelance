import java.util.*;

class CBTInserter {
    private TreeNode root;
    private Queue<TreeNode> queue;
    
    public CBTInserter(TreeNode root) {
        this.root = root;
        this.queue = new LinkedList<>();
        Queue<TreeNode> q = new LinkedList<>();
        q.offer(root);
        
        while (!q.isEmpty()) {
            TreeNode node = q.poll();
            if (node.left == null || node.right == null) {
                queue.offer(node);
            }
            if (node.left != null) {
                q.offer(node.left);
            }
            if (node.right != null) {
                q.offer(node.right);
            }
        }
    }
    
    public int insert(int val) {
        TreeNode parent = queue.peek();
        TreeNode newNode = new TreeNode(val);
        
        if (parent.left == null) {
            parent.left = newNode;
        } else {
            parent.right = newNode;
            queue.poll();
        }
        
        queue.offer(newNode);
        return parent.val;
    }
    
    public TreeNode get_root() {
        return root;
    }
}
