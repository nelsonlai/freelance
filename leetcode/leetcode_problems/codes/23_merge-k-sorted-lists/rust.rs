// Problem: Merge k Sorted Lists
// Difficulty: Hard
// Tags: array, sort, linked_list, queue, heap
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
    pub fn merge_k_lists(lists: Vec<Option<Box<ListNode>>>) -> Option<Box<ListNode>> {
        if lists.is_empty() {
            return None;
        }
        
        let mut lists = lists;
        while lists.len() > 1 {
            let mut merged = Vec::new();
            for i in (0..lists.len()).step_by(2) {
                let l2 = if i + 1 < lists.len() {
                    lists[i + 1].take()
                } else {
                    None
                };
                merged.push(Self::merge_two(lists[i].take(), l2));
            }
            lists = merged;
        }
        
        lists[0].take()
    }
    
    fn merge_two(
        l1: Option<Box<ListNode>>,
        l2: Option<Box<ListNode>>,
    ) -> Option<Box<ListNode>> {
        match (l1, l2) {
            (None, None) => None,
            (Some(l), None) | (None, Some(l)) => Some(l),
            (Some(mut l1), Some(mut l2)) => {
                if l1.val <= l2.val {
                    l1.next = Self::merge_two(l1.next, Some(l2));
                    Some(l1)
                } else {
                    l2.next = Self::merge_two(Some(l1), l2.next);
                    Some(l2)
                }
            }
        }
    }
}