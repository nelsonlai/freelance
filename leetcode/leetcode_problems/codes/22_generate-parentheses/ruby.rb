# @param {Integer} n
# @return {String[]}
def generate_parenthesis(n)
    result = []
    
    backtrack = lambda do |current, open_count, close_count|
        if current.length == 2 * n
            result << current
            return
        end
        
        if open_count < n
            backtrack.call(current + '(', open_count + 1, close_count)
        end
        
        if close_count < open_count
            backtrack.call(current + ')', open_count, close_count + 1)
        end
    end
    
    backtrack.call("", 0, 0)
    result
end