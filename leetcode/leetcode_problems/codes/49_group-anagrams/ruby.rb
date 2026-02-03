# @param {String[]} strs
# @return {String[][]}
def group_anagrams(strs)
    groups = {}
    strs.each do |s|
        key = s.chars.sort.join
        groups[key] ||= []
        groups[key] << s
    end
    groups.values
end