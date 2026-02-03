require 'set'

# @param {Integer} n
# @return {Integer}
def total_n_queens(n)
    count = [0]
    cols = Set.new
    diag1 = Set.new
    diag2 = Set.new
    
    backtrack = lambda do |row|
        if row == n
            count[0] += 1
            return
        end
        
        (0...n).each do |col|
            next if cols.include?(col) || diag1.include?(row - col) || diag2.include?(row + col)
            
            cols.add(col)
            diag1.add(row - col)
            diag2.add(row + col)
            
            backtrack.call(row + 1)
            
            cols.delete(col)
            diag1.delete(row - col)
            diag2.delete(row + col)
        end
    end
    
    backtrack.call(0)
    count[0]
end