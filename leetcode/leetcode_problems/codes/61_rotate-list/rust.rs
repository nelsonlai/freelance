// Problem: Rotate List
// Difficulty: Medium
// Tags: array, linked_list
// 
// Approach: Use two pointers or sliding window technique
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(1) to O(n) depending on approach

// Definition for singly-linked list.
// #[derive(PartialEq, Eq, Clone, Debug)]
// pub struct ListNode {
//   pub val: i32,
//   pub next: Option<Box<ListNode>>
// }
// 
// impl ListNode {
//   #[inline]
//   fn new(val: i32) -> Self {
//     ListNode {
//       next: None,
//       val
//     }
//   }
// }
impl Solution {
    pub fn rotate_right(head: Option<Box<ListNode>>, k: i32) -> Option<Box<ListNode>> {
        if head.is_none() {
            return head;
        }
        
        let mut head = head;
        let mut nodes = Vec::new();
        let mut current = head.take();
        
        // Collect all nodes
        while let Some(mut node) = current {
            let next = node.next.take();
            nodes.push(node);
            current = next;
        }
        
        if nodes.is_empty() || k == 0 {
            return Self::build_list(nodes);
        }
        
        let n = nodes.len();
        let k = (k as usize) % n;
        if k == 0 {
            return Self::build_list(nodes);
        }
        
        // Rotate
        nodes.rotate_right(k);
        Self::build_list(nodes)
    }
    
    fn build_list(mut nodes: Vec<Box<ListNode>>) -> Option<Box<ListNode>> {
        if nodes.is_empty() {
            return None;
        }
        let mut head = Some(nodes.remove(0));
        let mut current = &mut head;
        for node in nodes {
            if let Some(ref mut curr) = current {
                curr.next = Some(node);
                current = &mut curr.next;
            }
        }
        head
    }
}