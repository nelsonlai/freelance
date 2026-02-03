class Solution(object):
    def isValidSudoku(self, board):
        """
        :type board: List[List[str]]
        :rtype: bool
        """
        seen = set()
        
        for i in range(9):
            for j in range(9):
                if board[i][j] != '.':
                    num = board[i][j]
                    row_key = "row-{}-{}".format(i, num)
                    col_key = "col-{}-{}".format(j, num)
                    box_key = "box-{}-{}-{}".format(i // 3, j // 3, num)
                    
                    if row_key in seen or col_key in seen or box_key in seen:
                        return False
                    
                    seen.add(row_key)
                    seen.add(col_key)
                    seen.add(box_key)
        
        return True