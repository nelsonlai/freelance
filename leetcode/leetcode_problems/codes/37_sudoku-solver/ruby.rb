# @param {Character[][]} board
# @return {Void} Do not return anything, modify board in-place instead.
def solve_sudoku(board)
    def is_valid(row, col, num)
        (0...9).each do |i|
            return false if board[row][i] == num || board[i][col] == num
            return false if board[3 * (row / 3) + i / 3][3 * (col / 3) + i % 3] == num
        end
        true
    end
    
    def solve
        (0...9).each do |i|
            (0...9).each do |j|
                if board[i][j] == '.'
                    ('1'..'9').each do |num|
                        if is_valid(i, j, num)
                            board[i][j] = num
                            return true if solve
                            board[i][j] = '.'
                        end
                    end
                    return false
                end
            end
        end
        true
    end
    
    solve
end