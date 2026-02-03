/**
 * Problem: Add Two Polynomials Represented as Linked Lists
 * Difficulty: Medium
 * Tags: array, math, linked_list
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

/**
 * Definition for polynomial singly-linked list.
 * class PolyNode {
 *     int coefficient, power;
 *     PolyNode next = null;
 * 
 *     PolyNode() {}
 *     PolyNode(int x, int y) { this.coefficient = x; this.power = y; }
 *     PolyNode(int x, int y, PolyNode next) { this.coefficient = x; this.power = y; this.next = next; }
 * }
 */

class Solution {
    public PolyNode addPoly(PolyNode poly1, PolyNode poly2) {
        PolyNode dummy = new PolyNode();
        PolyNode current = dummy;
        
        while (poly1 != null && poly2 != null) {
            if (poly1.power > poly2.power) {
                current.next = new PolyNode(poly1.coefficient, poly1.power);
                poly1 = poly1.next;
                current = current.next;
            } else if (poly2.power > poly1.power) {
                current.next = new PolyNode(poly2.coefficient, poly2.power);
                poly2 = poly2.next;
                current = current.next;
            } else {
                int coeff = poly1.coefficient + poly2.coefficient;
                if (coeff != 0) {
                    current.next = new PolyNode(coeff, poly1.power);
                    current = current.next;
                }
                poly1 = poly1.next;
                poly2 = poly2.next;
            }
        }
        
        current.next = (poly1 != null) ? poly1 : poly2;
        
        return dummy.next;
    }
}