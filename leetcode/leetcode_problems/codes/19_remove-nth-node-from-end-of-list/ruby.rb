# Definition for singly-linked list.
# class ListNode
#     attr_accessor :val, :next
#     def initialize(val = 0, _next = nil)
#         @val = val
#         @next = _next
#     end
# end
# @param {ListNode} head
# @param {Integer} n
# @return {ListNode}
def remove_nth_from_end(head, n)
    dummy = ListNode.new(0)
    dummy.next = head
    first = dummy
    second = dummy
    
    (n + 1).times do
        first = first.next
    end
    
    while first
        first = first.next
        second = second.next
    end
    
    second.next = second.next.next
    dummy.next
end