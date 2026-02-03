# Definition for singly-linked list.
# class ListNode
#     attr_accessor :val, :next
#     def initialize(val = 0, _next = nil)
#         @val = val
#         @next = _next
#     end
# end
# @param {ListNode} head
# @param {Integer} k
# @return {ListNode}
def rotate_right(head, k)
    return head if head.nil? || head.next.nil? || k == 0
    
    # Find length and get tail
    length = 1
    tail = head
    while tail.next
        tail = tail.next
        length += 1
    end
    
    k = k % length
    return head if k == 0
    
    # Find new tail
    new_tail = head
    (length - k - 1).times do
        new_tail = new_tail.next
    end
    
    # Rotate
    new_head = new_tail.next
    new_tail.next = nil
    tail.next = head
    
    new_head
end