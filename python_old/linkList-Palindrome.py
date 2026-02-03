# LeetCode 234. Palindrome Linked List
# O(n) time, O(1) extra space (reverse the second half in-place and restore)

class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    def isPalindrome(self, head):
        if head is None or head.next is None:
            return True

        # 1) Find the middle (slow at mid; for even n it's the first node of the second half)
        slow, fast = head, head
        while fast and fast.next:
            slow = slow.next
            fast = fast.next.next

        # 2) Reverse second half starting from slow
        second = self._reverse(slow)

        # 3) Compare first half with reversed second half
        p1, p2 = head, second
        ok = True
        while p2:
            if p1.val != p2.val:
                ok = False
                break
            p1 = p1.next
            p2 = p2.next

        # 4) Restore list
        self._reverse(second)

        return ok

    def _reverse(self, node):
        prev = None
        curr = node
        while curr:
            nxt = curr.next
            curr.next = prev
            prev = curr
            curr = nxt
        return prev

# -------- Helpers and test main --------

def build_list(values):
    dummy = ListNode()
    tail = dummy
    for v in values:
        tail.next = ListNode(v)
        tail = tail.next
    return dummy.next

def to_pylist(head):
    out = []
    while head:
        out.append(head.val)
        head = head.next
    return out

def main():
    cases = [
        ([], True),
        ([1], True),
        ([1, 2], False),
        ([1, 2, 2, 1], True),
        ([1, 2, 3, 2, 1], True),
        ([1, 2, 3, 4], False),
        ([1, 0, 1], True),
    ]

    sol = Solution()
    for arr, expected in cases:
        head = build_list(arr)
        original = list(arr)  # keep a copy to verify restoration
        got = sol.isPalindrome(head)
        restored = to_pylist(head)
        sarr = str(arr)
        print(f"Input: {sarr:<15} -> isPalindrome = {got} (expected {expected}), restored_ok = {restored == original}")

if __name__ == "__main__":
    main()