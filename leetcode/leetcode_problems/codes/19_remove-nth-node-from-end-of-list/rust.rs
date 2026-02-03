// Problem: Remove Nth Node From End of List
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
    pub fn remove_nth_from_end(head: Option<Box<ListNode>>, n: i32) -> Option<Box<ListNode>> {
        let mut dummy = Box::new(ListNode { val: 0, next: head });
        let mut first = dummy.as_mut() as *mut ListNode;
        let mut second = dummy.as_mut() as *mut ListNode;
        
        unsafe {
            for _ in 0..=n {
                first = (*first).next.as_mut().unwrap().as_mut() as *mut ListNode;
            }
            
            while (*first).next.is_some() {
                first = (*first).next.as_mut().unwrap().as_mut() as *mut ListNode;
                second = (*second).next.as_mut().unwrap().as_mut() as *mut ListNode;
            }
            
            let next = (*second).next.as_mut().unwrap().next.take();
            (*second).next = next;
        }
        
        dummy.next
    }
}