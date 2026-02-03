# @param {String} s
# @param {Integer} num_rows
# @return {String}
def convert(s, num_rows)
    return s if num_rows == 1 || num_rows >= s.length
    
    rows = Array.new(num_rows, '')
    current_row = 0
    going_down = false
    
    s.each_char do |char|
        rows[current_row] += char
        if current_row == 0 || current_row == num_rows - 1
            going_down = !going_down
        end
        current_row += going_down ? 1 : -1
    end
    
    rows.join
end