require 'set'

# @param {Character[][]} board
# @return {Boolean}
def is_valid_sudoku(board)
    seen = Set.new
    
    (0...9).each do |i|
        (0...9).each do |j|
            if board[i][j] != '.'
                num = board[i][j]
                row_key = "row-#{i}-#{num}"
                col_key = "col-#{j}-#{num}"
                box_key = "box-#{i / 3}-#{j / 3}-#{num}"
                
                return false if seen.include?(row_key) || seen.include?(col_key) || seen.include?(box_key)
                
                seen.add(row_key)
                seen.add(col_key)
                seen.add(box_key)
            end
        end
    end
    
    true
end