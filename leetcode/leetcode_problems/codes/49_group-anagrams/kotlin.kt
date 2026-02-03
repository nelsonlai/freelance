class Solution {
    fun groupAnagrams(strs: Array<String>): List<List<String>> {
        val groups = mutableMapOf<String, MutableList<String>>()
        for (s in strs) {
            val key = s.toCharArray().sorted().joinToString("")
            groups.getOrPut(key) { mutableListOf() }.add(s)
        }
        return groups.values.toList()
    }
}