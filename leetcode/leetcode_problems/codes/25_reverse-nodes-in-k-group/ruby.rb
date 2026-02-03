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
def reverse_k_group(head, k)
    current = head
    count = 0
    
    while current && count < k
        current = current.next
        count += 1
    end
    
    if count == k
        current = reverse_k_group(current, k)
        
        while count > 0
            next_node = head.next
            head.next = current
            current = head
            head = next_node
            count -= 1
        end
        head = current
    end
    
    head
end