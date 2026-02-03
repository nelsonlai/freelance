class Solution:
    def ipToCIDR(self, ip: str, n: int) -> List[str]:
        def ipToInt(ip):
            parts = ip.split('.')
            return int(parts[0]) * 256**3 + int(parts[1]) * 256**2 + int(parts[2]) * 256 + int(parts[3])
        
        def intToIP(x):
            return f"{x >> 24}.{(x >> 16) & 255}.{(x >> 8) & 255}.{x & 255}"
        
        start = ipToInt(ip)
        result = []
        
        while n > 0:
            mask = 33 - (start & -start).bit_length()
            mask = min(mask, 33 - (n).bit_length())
            result.append(f"{intToIP(start)}/{mask}")
            start += 1 << (32 - mask)
            n -= 1 << (32 - mask)
        
        return result
