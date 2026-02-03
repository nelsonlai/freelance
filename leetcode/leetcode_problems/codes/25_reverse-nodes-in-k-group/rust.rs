// Problem: Reverse Nodes in k-Group
// Difficulty: Hard
// Tags: linked_list
// 
// Approach: Optimized algorithm based on problem constraints
// Time Complexity: O(n) to O(n^2) depending on approach
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
    pub fn reverse_k_group(head: Option<Box<ListNode>>, k: i32) -> Option<Box<ListNode>> {
        let mut head = head;
        let mut current = head.as_ref();
        let mut count = 0;
        
        while current.is_some() && count < k {
            current = current.unwrap().next.as_ref();
            count += 1;
        }
        
        if count == k {
            let mut tail = Self::reverse_k_group(
                current.map(|n| n.clone()),
                k
            );
            
            let mut head = head.take();
            while count > 0 {
                if let Some(mut node) = head {
                    let next = node.next.take();
                    node.next = tail;
                    tail = Some(node);
                    head = next;
                }
                count -= 1;
            }
            return tail;
        }
        
        head
    }
}