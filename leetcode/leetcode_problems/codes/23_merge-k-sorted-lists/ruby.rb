# Definition for singly-linked list.
# class ListNode
#     attr_accessor :val, :next
#     def initialize(val = 0, _next = nil)
#         @val = val
#         @next = _next
#     end
# end
# @param {ListNode[]} lists
# @return {ListNode}
def merge_k_lists(lists)
    return nil if lists.nil? || lists.empty?
    
    while lists.length > 1
        merged = []
        (0...lists.length).step(2) do |i|
            l1 = lists[i]
            l2 = (i + 1 < lists.length) ? lists[i + 1] : nil
            merged << merge_two(l1, l2)
        end
        lists = merged
    end
    
    lists[0]
end

def merge_two(l1, l2)
    dummy = ListNode.new(0)
    current = dummy
    
    while l1 && l2
        if l1.val <= l2.val
            current.next = l1
            l1 = l1.next
        else
            current.next = l2
            l2 = l2.next
        end
        current = current.next
    end
    
    current.next = l1 || l2
    dummy.next
end