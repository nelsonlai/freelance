# @param {Integer} n
# @return {Integer[][]}
def generate_matrix(n)
    matrix = Array.new(n) { Array.new(n, 0) }
    num = 1
    top, bottom = 0, n - 1
    left, right = 0, n - 1
    
    while top <= bottom && left <= right
        # Right
        (left..right).each do |j|
            matrix[top][j] = num
            num += 1
        end
        top += 1
        
        # Down
        (top..bottom).each do |i|
            matrix[i][right] = num
            num += 1
        end
        right -= 1
        
        # Left
        if top <= bottom
            (right).downto(left).each do |j|
                matrix[bottom][j] = num
                num += 1
            end
            bottom -= 1
        end
        
        # Up
        if left <= right
            (bottom).downto(top).each do |i|
                matrix[i][left] = num
                num += 1
            end
            left += 1
        end
    end
    
    matrix
end