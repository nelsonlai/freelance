# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def numComponents(self, head: Optional[ListNode], nums: List[int]) -> int:
        numSet = set(nums)
        result = 0
        inComponent = False
        
        while head:
            if head.val in numSet:
                if not inComponent:
                    result += 1
                    inComponent = True
            else:
                inComponent = False
            head = head.next
        
        return result
