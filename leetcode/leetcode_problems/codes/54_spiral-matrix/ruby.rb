# @param {Integer[][]} matrix
# @return {Integer[]}
def spiral_order(matrix)
    return [] if matrix.empty? || matrix[0].empty?
    
    result = []
    top, bottom = 0, matrix.length - 1
    left, right = 0, matrix[0].length - 1
    
    while top <= bottom && left <= right
        # Right
        (left..right).each do |j|
            result << matrix[top][j]
        end
        top += 1
        
        # Down
        (top..bottom).each do |i|
            result << matrix[i][right]
        end
        right -= 1
        
        # Left
        if top <= bottom
            (right).downto(left).each do |j|
                result << matrix[bottom][j]
            end
            bottom -= 1
        end
        
        # Up
        if left <= right
            (bottom).downto(top).each do |i|
                result << matrix[i][left]
            end
            left += 1
        end
    end
    
    result
end