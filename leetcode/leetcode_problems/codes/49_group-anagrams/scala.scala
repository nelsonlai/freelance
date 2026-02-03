import scala.collection.mutable

object Solution {
    def groupAnagrams(strs: Array[String]): List[List[String]] = {
        val groups = mutable.Map[String, mutable.ListBuffer[String]]()
        for (s <- strs) {
            val key = s.sorted
            groups.getOrElseUpdate(key, mutable.ListBuffer[String]()) += s
        }
        groups.values.map(_.toList).toList
    }
}