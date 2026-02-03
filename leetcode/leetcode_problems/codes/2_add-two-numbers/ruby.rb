# Definition for singly-linked list.
# class ListNode
#     attr_accessor :val, :next
#     def initialize(val = 0, _next = nil)
#         @val = val
#         @next = _next
#     end
# end
# @param {ListNode} l1
# @param {ListNode} l2
# @return {ListNode}
def add_two_numbers(l1, l2)
    dummy = ListNode.new(0)
    current = dummy
    carry = 0
    
    while l1 || l2 || carry != 0
        val1 = l1 ? l1.val : 0
        val2 = l2 ? l2.val : 0
        sum = val1 + val2 + carry
        carry = sum / 10
        current.next = ListNode.new(sum % 10)
        current = current.next
        l1 = l1 ? l1.next : nil
        l2 = l2 ? l2.next : nil
    end
    
    dummy.next
end