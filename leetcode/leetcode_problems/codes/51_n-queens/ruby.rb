require 'set'

# @param {Integer} n
# @return {String[][]}
def solve_n_queens(n)
    result = []
    board = Array.new(n) { Array.new(n, '.') }
    cols = Set.new
    diag1 = Set.new
    diag2 = Set.new
    
    backtrack = lambda do |row|
        if row == n
            result << board.map { |r| r.join('') }
            return
        end
        
        (0...n).each do |col|
            next if cols.include?(col) || diag1.include?(row - col) || diag2.include?(row + col)
            
            board[row][col] = 'Q'
            cols.add(col)
            diag1.add(row - col)
            diag2.add(row + col)
            
            backtrack.call(row + 1)
            
            board[row][col] = '.'
            cols.delete(col)
            diag1.delete(row - col)
            diag2.delete(row + col)
        end
    end
    
    backtrack.call(0)
    result
end