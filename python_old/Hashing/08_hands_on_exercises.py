"""
Hands-On Exercises for Hashing
==============================

This file contains practical exercises to reinforce learning about hashing:
- Collision analysis and comparison
- Hash function design and testing
- Performance benchmarking
- Real-world problem solving
- Advanced challenges

These exercises are designed to help students:
- Understand hash function behavior
- Compare different collision resolution strategies
- Analyze performance characteristics
- Apply hashing to solve practical problems

Author: Hash Lecture Series
Purpose: Interactive exercises for hands-on learning
"""

import time
import random
import math
import hashlib
from typing import List, Dict, Tuple, Any, Optional
from collections import defaultdict, Counter


class ExerciseFramework:
    """
    Framework for running hashing exercises with timing and analysis.
    """
    
    def __init__(self):
        """
        Initialize the exercise framework.
        """
        self.results = {}
    
    def time_function(self, func, *args, **kwargs):
        """
        Time a function execution.
        
        Args:
            func: Function to time
            *args: Function arguments
            **kwargs: Function keyword arguments
            
        Returns:
            Tuple of (result, execution_time)
        """
        start_time = time.time()
        result = func(*args, **kwargs)
        end_time = time.time()
        
        return result, end_time - start_time
    
    def run_exercise(self, exercise_name: str, func, *args, **kwargs):
        """
        Run an exercise and store results.
        
        Args:
            exercise_name: Name of the exercise
            func: Function to run
            *args: Function arguments
            **kwargs: Function keyword arguments
            
        Returns:
            Function result
        """
        print(f"\n{'='*60}")
        print(f"EXERCISE: {exercise_name}")
        print(f"{'='*60}")
        
        result, execution_time = self.time_function(func, *args, **kwargs)
        
        self.results[exercise_name] = {
            'result': result,
            'execution_time': execution_time
        }
        
        print(f"Execution time: {execution_time:.6f} seconds")
        
        return result


def exercise_1_collision_analysis():
    """
    Exercise 1: Collision Analysis
    
    Compare different hash functions and collision resolution strategies
    with the same dataset to understand their behavior.
    """
    print("Analyzing collisions for different hash table implementations...")
    
    # Test data designed to cause collisions
    test_keys = [4371, 1323, 6173, 4199, 4344, 9679, 1989, 1323, 6173, 4199]
    table_size = 10
    
    # Different hash functions to test
    hash_functions = {
        "Division (key % size)": lambda k: k % table_size,
        "Multiplication": lambda k: int(table_size * ((k * 0.618) % 1)),
        "Polynomial": lambda k: (k * 31 + 17) % table_size,
        "Simple": lambda k: abs(hash(str(k))) % table_size
    }
    
    print(f"\nTesting with {len(test_keys)} keys and table size {table_size}")
    print("Key".ljust(10), end="")
    for name in hash_functions:
        print(f"{name[:15].ljust(16)}", end="")
    print()
    print("-" * 80)
    
    # Track collisions for each hash function
    collision_counts = {name: 0 for name in hash_functions}
    used_indices = {name: set() for name in hash_functions}
    
    for key in test_keys:
        print(f"{str(key).ljust(10)}", end="")
        
        for name, hash_func in hash_functions.items():
            index = hash_func(key)
            print(f"{str(index).ljust(16)}", end="")
            
            # Check for collision
            if index in used_indices[name]:
                collision_counts[name] += 1
            else:
                used_indices[name].add(index)
        
        print()
    
    print("\nCollision Summary:")
    for name, count in collision_counts.items():
        print(f"  {name}: {count} collisions")
    
    # Analyze distribution
    print(f"\nDistribution Analysis:")
    for name, indices in used_indices.items():
        utilization = len(indices) / table_size
        print(f"  {name}: {len(indices)}/{table_size} slots used ({utilization:.1%})")
    
    return collision_counts


def exercise_2_hash_function_quality():
    """
    Exercise 2: Hash Function Quality Analysis
    
    Analyze the quality of different hash functions by measuring:
    - Distribution uniformity
    - Avalanche effect
    - Collision resistance
    """
    print("Analyzing hash function quality...")
    
    # Generate test data
    test_strings = [f"string_{i}" for i in range(1000)]
    
    # Hash functions to test
    def division_hash(s, size=100):
        return abs(hash(s)) % size
    
    def polynomial_hash(s, size=100):
        h = 0
        for c in s:
            h = (h * 31 + ord(c)) % size
        return h
    
    def crypto_hash(s, size=100):
        return int(hashlib.md5(s.encode()).hexdigest(), 16) % size
    
    hash_functions = {
        "Division": division_hash,
        "Polynomial": polynomial_hash,
        "Crypto": crypto_hash
    }
    
    results = {}
    
    for name, hash_func in hash_functions.items():
        print(f"\n--- {name} Hash Function ---")
        
        # Test distribution
        distribution = [0] * 100
        for s in test_strings:
            index = hash_func(s, 100)
            distribution[index] += 1
        
        # Calculate statistics
        mean = sum(distribution) / len(distribution)
        variance = sum((x - mean) ** 2 for x in distribution) / len(distribution)
        std_dev = math.sqrt(variance)
        
        print(f"Distribution statistics:")
        print(f"  Mean: {mean:.2f}")
        print(f"  Standard deviation: {std_dev:.2f}")
        print(f"  Min count: {min(distribution)}")
        print(f"  Max count: {max(distribution)}")
        
        # Test avalanche effect
        avalanche_tests = []
        for s in test_strings[:100]:  # Test first 100 strings
            original_hash = hash_func(s, 100)
            
            # Test small changes
            modified = s[:-1] + chr((ord(s[-1]) + 1) % 256) if len(s) > 0 else s + "x"
            modified_hash = hash_func(modified, 100)
            
            # Count bit differences (simplified)
            bit_differences = bin(original_hash ^ modified_hash).count('1')
            avalanche_tests.append(bit_differences)
        
        avg_avalanche = sum(avalanche_tests) / len(avalanche_tests)
        print(f"Avalanche effect (avg bit changes): {avg_avalanche:.2f}")
        
        results[name] = {
            'std_dev': std_dev,
            'avalanche': avg_avalanche,
            'distribution': distribution
        }
    
    return results


def exercise_3_performance_comparison():
    """
    Exercise 3: Performance Comparison
    
    Compare the performance of different hash table implementations
    with various data sizes and operations.
    """
    print("Comparing hash table performance...")
    
    # Simple hash table implementations for comparison
    class SimpleChainingHashTable:
        def __init__(self, size=1000):
            self.size = size
            self.table = [[] for _ in range(size)]
        
        def hash(self, key):
            return abs(hash(key)) % self.size
        
        def insert(self, key, value):
            index = self.hash(key)
            self.table[index].append((key, value))
        
        def search(self, key):
            index = self.hash(key)
            for k, v in self.table[index]:
                if k == key:
                    return v
            return None
    
    class SimpleProbingHashTable:
        def __init__(self, size=1000):
            self.size = size
            self.table = [None] * size
        
        def hash(self, key):
            return abs(hash(key)) % self.size
        
        def insert(self, key, value):
            index = self.hash(key)
            while self.table[index] is not None:
                index = (index + 1) % self.size
            self.table[index] = (key, value)
        
        def search(self, key):
            index = self.hash(key)
            original_index = index
            while self.table[index] is not None:
                if self.table[index][0] == key:
                    return self.table[index][1]
                index = (index + 1) % self.size
                if index == original_index:
                    break
            return None
    
    # Test different data sizes
    data_sizes = [100, 500, 1000, 2000]
    
    results = {}
    
    for size in data_sizes:
        print(f"\n--- Testing with {size} elements ---")
        
        # Generate test data
        test_data = [(f"key_{i}", f"value_{i}") for i in range(size)]
        search_keys = [f"key_{i}" for i in range(0, size, 10)]  # Search every 10th key
        
        # Test chaining hash table
        chaining_ht = SimpleChainingHashTable(size * 2)  # 50% load factor
        
        start_time = time.time()
        for key, value in test_data:
            chaining_ht.insert(key, value)
        chaining_insert_time = time.time() - start_time
        
        start_time = time.time()
        for key in search_keys:
            chaining_ht.search(key)
        chaining_search_time = time.time() - start_time
        
        # Test probing hash table
        probing_ht = SimpleProbingHashTable(size * 2)  # 50% load factor
        
        start_time = time.time()
        for key, value in test_data:
            probing_ht.insert(key, value)
        probing_insert_time = time.time() - start_time
        
        start_time = time.time()
        for key in search_keys:
            probing_ht.search(key)
        probing_search_time = time.time() - start_time
        
        print(f"Chaining - Insert: {chaining_insert_time:.6f}s, Search: {chaining_search_time:.6f}s")
        print(f"Probing  - Insert: {probing_insert_time:.6f}s, Search: {probing_search_time:.6f}s")
        
        results[size] = {
            'chaining_insert': chaining_insert_time,
            'chaining_search': chaining_search_time,
            'probing_insert': probing_insert_time,
            'probing_search': probing_search_time
        }
    
    return results


def exercise_4_load_factor_impact():
    """
    Exercise 4: Load Factor Impact Analysis
    
    Analyze how load factor affects hash table performance.
    """
    print("Analyzing load factor impact on performance...")
    
    class LoadFactorHashTable:
        def __init__(self, size):
            self.size = size
            self.table = [None] * size
            self.count = 0
        
        def hash(self, key):
            return abs(hash(key)) % self.size
        
        def insert(self, key, value):
            index = self.hash(key)
            original_index = index
            probes = 0
            
            while self.table[index] is not None:
                index = (index + 1) % self.size
                probes += 1
                if index == original_index:
                    return -1  # Table full
            
            self.table[index] = (key, value)
            self.count += 1
            return probes
        
        def search(self, key):
            index = self.hash(key)
            original_index = index
            probes = 0
            
            while self.table[index] is not None:
                if self.table[index][0] == key:
                    return self.table[index][1], probes
                index = (index + 1) % self.size
                probes += 1
                if index == original_index:
                    break
            
            return None, probes
    
    # Test different load factors
    table_size = 1000
    load_factors = [0.1, 0.3, 0.5, 0.7, 0.9]
    
    results = {}
    
    for target_lf in load_factors:
        print(f"\n--- Load Factor: {target_lf:.1f} ---")
        
        ht = LoadFactorHashTable(table_size)
        num_elements = int(table_size * target_lf)
        
        # Insert elements and measure probes
        total_insert_probes = 0
        for i in range(num_elements):
            probes = ht.insert(f"key_{i}", f"value_{i}")
            if probes >= 0:
                total_insert_probes += probes
        
        avg_insert_probes = total_insert_probes / num_elements if num_elements > 0 else 0
        
        # Search for random keys and measure probes
        search_keys = [f"key_{i}" for i in random.sample(range(num_elements), min(100, num_elements))]
        total_search_probes = 0
        
        for key in search_keys:
            _, probes = ht.search(key)
            total_search_probes += probes
        
        avg_search_probes = total_search_probes / len(search_keys) if search_keys else 0
        
        actual_lf = ht.count / table_size
        
        print(f"Target load factor: {target_lf:.1f}")
        print(f"Actual load factor: {actual_lf:.3f}")
        print(f"Average insert probes: {avg_insert_probes:.2f}")
        print(f"Average search probes: {avg_search_probes:.2f}")
        
        results[target_lf] = {
            'actual_lf': actual_lf,
            'avg_insert_probes': avg_insert_probes,
            'avg_search_probes': avg_search_probes
        }
    
    return results


def exercise_5_real_world_problem():
    """
    Exercise 5: Real-World Problem Solving
    
    Solve a practical problem using hashing techniques.
    Problem: Build a simple web server log analyzer.
    """
    print("Building a web server log analyzer...")
    
    class WebLogAnalyzer:
        def __init__(self):
            self.ip_visits = defaultdict(int)
            self.page_views = defaultdict(int)
            self.user_agents = defaultdict(int)
            self.status_codes = defaultdict(int)
            self.hourly_traffic = defaultdict(int)
        
        def parse_log_line(self, line):
            """
            Parse a simple log line format:
            IP - - [timestamp] "method path protocol" status size "referer" "user_agent"
            """
            parts = line.split('"')
            if len(parts) < 3:
                return None
            
            # Extract IP
            ip = parts[0].split()[0]
            
            # Extract method, path, protocol
            request_parts = parts[1].split()
            if len(request_parts) >= 2:
                method = request_parts[0]
                path = request_parts[1]
            else:
                method = "UNKNOWN"
                path = "/"
            
            # Extract status code
            status_line = parts[2].strip()
            status = status_line.split()[0] if status_line else "000"
            
            # Extract user agent
            user_agent = parts[3] if len(parts) > 3 else "Unknown"
            
            # Extract hour from timestamp (simplified)
            timestamp_part = parts[0].split('[')[1].split(']')[0] if '[' in parts[0] else "01/Jan/2024:00:00:00"
            hour = timestamp_part.split(':')[1] if ':' in timestamp_part else "00"
            
            return {
                'ip': ip,
                'method': method,
                'path': path,
                'status': status,
                'user_agent': user_agent,
                'hour': hour
            }
        
        def add_log_line(self, line):
            """Add a log line to the analysis."""
            parsed = self.parse_log_line(line)
            if parsed:
                self.ip_visits[parsed['ip']] += 1
                self.page_views[parsed['path']] += 1
                self.user_agents[parsed['user_agent']] += 1
                self.status_codes[parsed['status']] += 1
                self.hourly_traffic[parsed['hour']] += 1
        
        def get_top_ips(self, n=10):
            """Get top N IP addresses by visit count."""
            return Counter(self.ip_visits).most_common(n)
        
        def get_top_pages(self, n=10):
            """Get top N pages by view count."""
            return Counter(self.page_views).most_common(n)
        
        def get_status_summary(self):
            """Get summary of HTTP status codes."""
            return dict(self.status_codes)
        
        def get_hourly_traffic(self):
            """Get traffic by hour."""
            return dict(self.hourly_traffic)
    
    # Generate sample log data
    sample_logs = [
        '192.168.1.1 - - [25/Dec/2024:10:15:30] "GET /index.html HTTP/1.1" 200 1234 "https://google.com" "Mozilla/5.0"',
        '192.168.1.2 - - [25/Dec/2024:10:16:45] "GET /about.html HTTP/1.1" 200 567 "https://google.com" "Mozilla/5.0"',
        '192.168.1.1 - - [25/Dec/2024:10:17:12] "POST /login HTTP/1.1" 302 0 "https://example.com" "Chrome/91.0"',
        '192.168.1.3 - - [25/Dec/2024:10:18:33] "GET /images/logo.png HTTP/1.1" 200 2345 "" "Mozilla/5.0"',
        '192.168.1.1 - - [25/Dec/2024:10:19:55] "GET /index.html HTTP/1.1" 200 1234 "https://example.com" "Mozilla/5.0"',
        '192.168.1.4 - - [25/Dec/2024:10:20:11] "GET /contact.html HTTP/1.1" 404 0 "https://google.com" "Safari/14.0"',
        '192.168.1.2 - - [25/Dec/2024:10:21:22] "GET /about.html HTTP/1.1" 200 567 "https://example.com" "Chrome/91.0"',
        '192.168.1.5 - - [25/Dec/2024:11:05:44] "GET /index.html HTTP/1.1" 200 1234 "https://google.com" "Mozilla/5.0"',
        '192.168.1.1 - - [25/Dec/2024:11:06:15] "GET /products.html HTTP/1.1" 200 890 "https://example.com" "Mozilla/5.0"',
        '192.168.1.3 - - [25/Dec/2024:11:07:33] "GET /images/banner.jpg HTTP/1.1" 200 4567 "" "Chrome/91.0"'
    ]
    
    # Analyze logs
    analyzer = WebLogAnalyzer()
    
    for log_line in sample_logs:
        analyzer.add_log_line(log_line)
    
    # Display results
    print(f"\nLog Analysis Results:")
    print(f"Total log entries processed: {len(sample_logs)}")
    
    print(f"\nTop IP addresses:")
    top_ips = analyzer.get_top_ips(5)
    for ip, count in top_ips:
        print(f"  {ip}: {count} visits")
    
    print(f"\nTop pages:")
    top_pages = analyzer.get_top_pages(5)
    for page, count in top_pages:
        print(f"  {page}: {count} views")
    
    print(f"\nHTTP Status Codes:")
    status_summary = analyzer.get_status_summary()
    for status, count in status_summary.items():
        print(f"  {status}: {count}")
    
    print(f"\nHourly Traffic:")
    hourly_traffic = analyzer.get_hourly_traffic()
    for hour, count in sorted(hourly_traffic.items()):
        print(f"  {hour}:00 - {count} requests")
    
    return analyzer


def exercise_6_advanced_challenge():
    """
    Exercise 6: Advanced Challenge
    
    Implement a simple distributed cache system using consistent hashing.
    """
    print("Implementing a distributed cache system...")
    
    class DistributedCache:
        def __init__(self):
            self.servers = {}
            self.hash_ring = {}
            self.sorted_keys = []
        
        def _hash(self, key):
            """Generate hash for consistent hashing."""
            return int(hashlib.md5(key.encode()).hexdigest(), 16)
        
        def add_server(self, server_id):
            """Add a server to the distributed cache."""
            # Create multiple virtual nodes for better load distribution
            for i in range(3):  # 3 virtual nodes per server
                virtual_node = f"{server_id}:{i}"
                hash_key = self._hash(virtual_node)
                self.hash_ring[hash_key] = server_id
                self.sorted_keys.append(hash_key)
            
            self.sorted_keys.sort()
            self.servers[server_id] = {}  # Initialize server storage
        
        def remove_server(self, server_id):
            """Remove a server from the distributed cache."""
            # Remove virtual nodes
            keys_to_remove = []
            for hash_key, server in self.hash_ring.items():
                if server == server_id:
                    keys_to_remove.append(hash_key)
            
            for key in keys_to_remove:
                del self.hash_ring[key]
                self.sorted_keys.remove(key)
            
            # Migrate data to other servers
            if server_id in self.servers:
                data_to_migrate = self.servers[server_id]
                del self.servers[server_id]
                
                # Re-assign data to remaining servers
                for key, value in data_to_migrate.items():
                    self.set(key, value)
        
        def get_server_for_key(self, key):
            """Get the server responsible for a key using consistent hashing."""
            if not self.hash_ring:
                return None
            
            hash_key = self._hash(key)
            
            # Find the first server with hash >= key's hash
            for ring_hash in self.sorted_keys:
                if ring_hash >= hash_key:
                    return self.hash_ring[ring_hash]
            
            # Wrap around to first server
            return self.hash_ring[self.sorted_keys[0]]
        
        def set(self, key, value):
            """Set a key-value pair in the cache."""
            server_id = self.get_server_for_key(key)
            if server_id:
                self.servers[server_id][key] = value
                return True
            return False
        
        def get(self, key):
            """Get a value from the cache."""
            server_id = self.get_server_for_key(key)
            if server_id and server_id in self.servers:
                return self.servers[server_id].get(key)
            return None
        
        def get_load_distribution(self):
            """Get the load distribution across servers."""
            distribution = {}
            for server_id, data in self.servers.items():
                distribution[server_id] = len(data)
            return distribution
    
    # Test the distributed cache
    cache = DistributedCache()
    
    # Add servers
    servers = ["server1", "server2", "server3"]
    for server in servers:
        cache.add_server(server)
        print(f"Added {server}")
    
    # Add some data
    test_data = [
        ("user:1", "Alice"),
        ("user:2", "Bob"),
        ("user:3", "Charlie"),
        ("product:1", "Laptop"),
        ("product:2", "Phone"),
        ("session:1", "abc123"),
        ("session:2", "def456"),
        ("config:theme", "dark"),
        ("config:lang", "en"),
        ("cache:key1", "value1")
    ]
    
    print(f"\nAdding data to cache:")
    for key, value in test_data:
        success = cache.set(key, value)
        print(f"  {key} -> {value} ({'✓' if success else '✗'})")
    
    # Show load distribution
    print(f"\nLoad distribution:")
    distribution = cache.get_load_distribution()
    for server, count in distribution.items():
        print(f"  {server}: {count} items")
    
    # Test retrieval
    print(f"\nTesting data retrieval:")
    test_keys = ["user:1", "product:2", "session:1", "nonexistent"]
    for key in test_keys:
        value = cache.get(key)
        print(f"  {key}: {value}")
    
    # Test server removal
    print(f"\nRemoving server2...")
    cache.remove_server("server2")
    
    print(f"\nLoad distribution after removal:")
    distribution = cache.get_load_distribution()
    for server, count in distribution.items():
        print(f"  {server}: {count} items")
    
    # Test retrieval after server removal
    print(f"\nTesting data retrieval after server removal:")
    for key in test_keys:
        value = cache.get(key)
        print(f"  {key}: {value}")
    
    return cache


def run_all_exercises():
    """
    Run all exercises and provide a comprehensive summary.
    """
    print("HASHING HANDS-ON EXERCISES")
    print("="*60)
    
    framework = ExerciseFramework()
    
    # Run all exercises
    exercises = [
        ("Collision Analysis", exercise_1_collision_analysis),
        ("Hash Function Quality", exercise_2_hash_function_quality),
        ("Performance Comparison", exercise_3_performance_comparison),
        ("Load Factor Impact", exercise_4_load_factor_impact),
        ("Real-World Problem", exercise_5_real_world_problem),
        ("Advanced Challenge", exercise_6_advanced_challenge)
    ]
    
    for name, func in exercises:
        framework.run_exercise(name, func)
    
    # Summary
    print(f"\n{'='*60}")
    print("EXERCISE SUMMARY")
    print(f"{'='*60}")
    
    for exercise_name, result in framework.results.items():
        print(f"{exercise_name}: {result['execution_time']:.6f}s")
    
    total_time = sum(result['execution_time'] for result in framework.results.values())
    print(f"\nTotal execution time: {total_time:.6f}s")
    
    print(f"\n{'='*60}")
    print("KEY LEARNINGS")
    print(f"{'='*60}")
    print("1. Hash function choice significantly affects collision rates")
    print("2. Load factor has a major impact on performance")
    print("3. Different collision resolution strategies have trade-offs")
    print("4. Hashing is essential for real-world applications")
    print("5. Consistent hashing enables distributed systems")
    print("6. Performance analysis helps optimize hash table design")


if __name__ == "__main__":
    """
    Main execution block. When this file is run directly, it will:
    1. Run all hands-on exercises
    2. Provide timing and performance analysis
    3. Demonstrate real-world applications
    4. Challenge students with advanced problems
    """
    
    # Run all exercises
    run_all_exercises()
    
    print(f"\n{'='*60}")
    print("EDUCATIONAL NOTES:")
    print(f"{'='*60}")
    print("1. Exercise Design Principles:")
    print("   - Start with simple concepts and build complexity")
    print("   - Use real-world examples to maintain interest")
    print("   - Provide immediate feedback and results")
    print("   - Challenge students with progressively harder problems")
    print()
    print("2. Learning Objectives:")
    print("   - Understand hash function behavior and quality")
    print("   - Compare different collision resolution strategies")
    print("   - Analyze performance characteristics")
    print("   - Apply hashing to solve practical problems")
    print("   - Design and implement distributed systems")
    print()
    print("3. Best Practices Demonstrated:")
    print("   - Measure and analyze performance")
    print("   - Use appropriate data structures for the problem")
    print("   - Consider trade-offs between memory and performance")
    print("   - Design for scalability and distribution")
    print("   - Test with realistic data and scenarios")
    print()
    print("4. Next Steps for Students:")
    print("   - Experiment with different hash functions")
    print("   - Implement more sophisticated collision resolution")
    print("   - Build larger, more complex applications")
    print("   - Study advanced topics like perfect hashing")
    print("   - Explore distributed systems and consistent hashing")
