class Solution:
    def similarRGB(self, color: str) -> str:
        def closest(s):
            num = int(s, 16)
            q, r = divmod(num, 17)
            if r > 8:
                q += 1
            return f"{q:02x}"
        
        return "#" + closest(color[1:3]) + closest(color[3:5]) + closest(color[5:7])
