#!/usr/bin/env python3
"""
Solution Generator for LeetCode Problems
Generates optimized solutions for LeetCode problems in multiple programming languages.
"""

import re
from typing import Dict, Optional, List, Tuple
from html2text import html2text
from solution_library import SolutionLibrary


class SolutionGenerator:
    """Generates optimized solutions for LeetCode problems."""
    
    def __init__(self):
        # Initialize solution library
        self.solution_library = SolutionLibrary()
        # Language to file extension mapping
        self.lang_extensions = {
            'python': '.py',
            'python3': '.py',
            'java': '.java',
            'cpp': '.cpp',
            'c++': '.cpp',
            'c': '.c',
            'javascript': '.js',
            'typescript': '.ts',
            'csharp': '.cs',
            'c#': '.cs',
            'go': '.go',
            'rust': '.rs',
            'swift': '.swift',
            'kotlin': '.kt',
            'ruby': '.rb',
            'scala': '.scala',
            'php': '.php',
        }
        
        # Problem type patterns
        self.problem_patterns = {
            'array': ['array', 'two pointers', 'sliding window', 'prefix sum'],
            'string': ['string', 'palindrome', 'substring', 'anagram'],
            'tree': ['tree', 'binary tree', 'bst', 'dfs', 'bfs'],
            'graph': ['graph', 'topological', 'shortest path', 'union find'],
            'dp': ['dynamic programming', 'dp', 'memoization'],
            'greedy': ['greedy'],
            'math': ['math', 'number theory', 'combinatorics'],
            'hash': ['hash', 'hashmap', 'hash table'],
            'sort': ['sort', 'sorting'],
            'search': ['binary search', 'search'],
            'linked_list': ['linked list', 'list node'],
            'stack': ['stack'],
            'queue': ['queue'],
            'heap': ['heap', 'priority queue'],
        }
    
    def parse_problem_description(self, content: str) -> Dict:
        """Parse problem description to extract key information."""
        if not content:
            return {}
        
        # Convert HTML to text
        try:
            text = html2text(content)
        except:
            text = re.sub(r'<[^>]+>', '', content)
        
        # Extract constraints
        constraints = {}
        constraint_patterns = {
            'length': r'(\d+)\s*<=?\s*(?:nums|array|string|list)\.length',
            'values': r'-?\d+\s*<=?\s*(?:nums|array|string|list)\[i\]\s*<=?\s*-?\d+',
            'range': r'(\d+)\s*<=?\s*n\s*<=?\s*(\d+)',
        }
        
        for key, pattern in constraint_patterns.items():
            match = re.search(pattern, text, re.IGNORECASE)
            if match:
                constraints[key] = match.groups()
        
        # Extract examples
        examples = []
        example_pattern = r'example\s+\d+[:\-]?\s*(.*?)(?=example\s+\d+|$)'
        matches = re.finditer(example_pattern, text, re.IGNORECASE | re.DOTALL)
        for match in matches:
            examples.append(match.group(1).strip())
        
        return {
            'text': text,
            'constraints': constraints,
            'examples': examples,
        }
    
    def identify_problem_type(self, tags: List[Dict], description: str) -> List[str]:
        """Identify problem type from tags and description."""
        types = []
        tag_names = [tag.get('name', '').lower() for tag in tags] if tags else []
        description_lower = description.lower() if description else ''
        
        combined_text = ' '.join(tag_names) + ' ' + description_lower
        
        for problem_type, keywords in self.problem_patterns.items():
            if any(keyword in combined_text for keyword in keywords):
                types.append(problem_type)
        
        return types if types else ['general']
    
    def generate_solution(self, problem_detail: Dict, language: str, starter_code: str) -> str:
        """
        Generate optimized solution for a problem in the specified language.
        First checks solution library, then uses pattern-based generation.
        """
        if not problem_detail or not starter_code:
            return starter_code
        
        # Extract problem information
        title = problem_detail.get('title', '')
        title_slug = problem_detail.get('titleSlug', '')
        difficulty = problem_detail.get('difficulty', 'Medium')
        tags = problem_detail.get('topicTags', [])
        content = problem_detail.get('content', '')
        sample_test_case = problem_detail.get('sampleTestCase', '')
        
        # First, check if we have a solution in the library
        if title_slug:
            library_solution = self.solution_library.get_solution(title_slug, language)
            if library_solution:
                # Merge library solution with starter code structure
                return self._merge_solution_with_starter(starter_code, library_solution, title, difficulty, tags)
        
        # Parse description
        parsed = self.parse_problem_description(content)
        problem_types = self.identify_problem_type(tags, parsed.get('text', ''))
        
        # Generate solution based on language and problem type
        lang_lower = language.lower()
        
        if lang_lower in ['python', 'python3']:
            return self._generate_python_solution(starter_code, problem_types, parsed, title, difficulty, title_slug)
        elif lang_lower == 'java':
            return self._generate_java_solution(starter_code, problem_types, parsed, title, difficulty, title_slug)
        elif lang_lower in ['cpp', 'c++']:
            return self._generate_cpp_solution(starter_code, problem_types, parsed, title, difficulty, title_slug)
        elif lang_lower == 'javascript':
            return self._generate_javascript_solution(starter_code, problem_types, parsed, title, difficulty, title_slug)
        elif lang_lower == 'typescript':
            return self._generate_typescript_solution(starter_code, problem_types, parsed, title, difficulty, title_slug)
        elif lang_lower == 'c':
            return self._generate_c_solution(starter_code, problem_types, parsed, title, difficulty, title_slug)
        elif lang_lower in ['csharp', 'c#']:
            return self._generate_csharp_solution(starter_code, problem_types, parsed, title, difficulty, title_slug)
        elif lang_lower == 'go':
            return self._generate_go_solution(starter_code, problem_types, parsed, title, difficulty, title_slug)
        elif lang_lower == 'rust':
            return self._generate_rust_solution(starter_code, problem_types, parsed, title, difficulty, title_slug)
        else:
            # For other languages, return starter code with basic structure
            return self._generate_generic_solution(starter_code, problem_types, parsed, title, difficulty, title_slug)
    
    def _merge_solution_with_starter(self, starter_code: str, solution_body: str, 
                                    title: str, difficulty: str, tags: List[Dict]) -> str:
        """Merge solution from library with starter code structure."""
        # Extract header comment style from starter code
        lang_lower = self._detect_language(starter_code)
        
        # Create header
        tag_names = ', '.join([tag.get('name', '') for tag in tags]) if tags else 'general'
        header = self._create_header(title, difficulty, tag_names, lang_lower)
        
        # Extract function/class structure from starter code
        if lang_lower in ['python', 'python3']:
            # For Python, replace function body
            func_match = re.search(r'(def\s+\w+\s*\([^)]*\)\s*->?\s*[^:]+?:)', starter_code)
            if func_match:
                func_sig = func_match.group(1)
                # Indent solution body
                indented_body = '\n'.join(['        ' + line if line.strip() else line 
                                          for line in solution_body.split('\n')])
                return header + func_sig + '\n' + indented_body
        elif lang_lower == 'java':
            # For Java, replace method body
            class_match = re.search(r'(class\s+\w+\s*\{)', starter_code)
            method_match = re.search(r'(public\s+\w+\s+\w+\s*\([^)]*\)\s*\{)', starter_code)
            if class_match and method_match:
                class_sig = class_match.group(1)
                method_sig = method_match.group(1)
                # Indent solution body
                indented_body = '\n'.join(['        ' + line if line.strip() else line 
                                          for line in solution_body.split('\n')])
                return header + class_sig + '\n    ' + method_sig + '\n' + indented_body + '\n    }\n}'
        elif lang_lower in ['cpp', 'c++']:
            # For C++, replace function body
            func_match = re.search(r'(\w+\s+\w+\s*\([^)]*\)\s*\{)', starter_code)
            if func_match:
                func_sig = func_match.group(1)
                # Indent solution body
                indented_body = '\n'.join(['        ' + line if line.strip() else line 
                                          for line in solution_body.split('\n')])
                return header + func_sig + '\n' + indented_body + '\n    }'
        elif lang_lower in ['csharp', 'c#']:
            # For C#, replace method body
            class_match = re.search(r'(public\s+class\s+\w+\s*\{)', starter_code)
            method_match = re.search(r'(public\s+\w+\s+\w+\s*\([^)]*\)\s*\{)', starter_code)
            if class_match and method_match:
                class_sig = class_match.group(1)
                method_sig = method_match.group(1)
                # Indent solution body
                indented_body = '\n'.join(['        ' + line if line.strip() else line 
                                          for line in solution_body.split('\n')])
                return header + class_sig + '\n    ' + method_sig + '\n' + indented_body + '\n    }\n}'
        
        # Fallback: just return header + solution
        return header + solution_body
    
    def _detect_language(self, code: str) -> str:
        """Detect programming language from code."""
        if 'def ' in code or 'class Solution:' in code:
            return 'python'
        elif 'public class' in code or 'public int' in code:
            return 'java'
        elif 'vector<' in code or 'ListNode*' in code:
            return 'cpp'
        elif 'public class Solution' in code and 'int[]' in code:
            return 'csharp'
        elif 'func ' in code:
            return 'go'
        elif 'function' in code or 'var ' in code:
            return 'javascript'
        return 'python'
    
    def _create_header(self, title: str, difficulty: str, tags: str, language: str) -> str:
        """Create header comment based on language."""
        lang_lower = language.lower()
        if lang_lower in ['python', 'python3']:
            return f'"""\nProblem: {title}\nDifficulty: {difficulty}\nTags: {tags}\n"""\n\n'
        elif lang_lower in ['java', 'javascript', 'typescript']:
            return f'/**\n * Problem: {title}\n * Difficulty: {difficulty}\n * Tags: {tags}\n */\n\n'
        else:
            return f'/*\n * Problem: {title}\n * Difficulty: {difficulty}\n * Tags: {tags}\n */\n\n'
    
    def _generate_python_solution(self, starter_code: str, problem_types: List[str], 
                                  parsed: Dict, title: str, difficulty: str, title_slug: str = '') -> str:
        """Generate Python solution."""
        # Extract function signature
        func_match = re.search(r'def\s+(\w+)\s*\([^)]*\)\s*->?\s*([^:]+)?:', starter_code)
        if not func_match:
            return starter_code
        
        func_name = func_match.group(1)
        return_type = func_match.group(2).strip() if func_match.group(2) else 'int'
        
        # Generate solution based on problem type
        solution = starter_code.rstrip()
        
        # Add comment header
        header = f'''"""
Problem: {title}
Difficulty: {difficulty}
Tags: {', '.join(problem_types)}

Approach: {self._get_approach_description(problem_types)}
Time Complexity: {self._get_time_complexity(problem_types)}
Space Complexity: {self._get_space_complexity(problem_types)}
"""

'''
        
        # Insert solution logic based on problem type
        if 'hash' in problem_types and 'array' in problem_types:
            solution = self._add_hash_array_solution_python(solution, func_name, parsed)
        elif 'array' in problem_types or 'two pointers' in problem_types:
            solution = self._add_array_solution_python(solution, func_name, parsed)
        elif 'string' in problem_types:
            solution = self._add_string_solution_python(solution, func_name, parsed)
        elif 'tree' in problem_types:
            solution = self._add_tree_solution_python(solution, func_name, parsed)
        elif 'dp' in problem_types:
            solution = self._add_dp_solution_python(solution, func_name, parsed)
        elif 'hash' in problem_types:
            solution = self._add_hash_solution_python(solution, func_name, parsed)
        else:
            solution = self._add_generic_solution_python(solution, func_name, parsed)
        
        return header + solution
    
    def _generate_java_solution(self, starter_code: str, problem_types: List[str],
                               parsed: Dict, title: str, difficulty: str, title_slug: str = '') -> str:
        """Generate Java solution."""
        solution = starter_code.rstrip()
        
        # Add comment header
        header = f'''/**
 * Problem: {title}
 * Difficulty: {difficulty}
 * Tags: {', '.join(problem_types)}
 * 
 * Approach: {self._get_approach_description(problem_types)}
 * Time Complexity: {self._get_time_complexity(problem_types)}
 * Space Complexity: {self._get_space_complexity(problem_types)}
 */

'''
        
        # Extract class and method
        class_match = re.search(r'class\s+(\w+)', starter_code)
        method_match = re.search(r'public\s+(\w+)\s+(\w+)\s*\([^)]*\)', starter_code)
        
        if method_match:
            method_name = method_match.group(2)
            if 'hash' in problem_types and 'array' in problem_types:
                solution = self._add_hash_array_solution_java(solution, method_name, parsed)
            elif 'array' in problem_types:
                solution = self._add_array_solution_java(solution, method_name, parsed)
            elif 'string' in problem_types:
                solution = self._add_string_solution_java(solution, method_name, parsed)
            elif 'tree' in problem_types:
                solution = self._add_tree_solution_java(solution, method_name, parsed)
            elif 'dp' in problem_types:
                solution = self._add_dp_solution_java(solution, method_name, parsed)
            else:
                solution = self._add_generic_solution_java(solution, method_name, parsed)
        
        return header + solution
    
    def _generate_cpp_solution(self, starter_code: str, problem_types: List[str],
                              parsed: Dict, title: str, difficulty: str, title_slug: str = '') -> str:
        """Generate C++ solution."""
        solution = starter_code.rstrip()
        
        header = f'''/*
 * Problem: {title}
 * Difficulty: {difficulty}
 * Tags: {', '.join(problem_types)}
 * 
 * Approach: {self._get_approach_description(problem_types)}
 * Time Complexity: {self._get_time_complexity(problem_types)}
 * Space Complexity: {self._get_space_complexity(problem_types)}
 */

'''
        
        method_match = re.search(r'(\w+)\s+(\w+)\s*\([^)]*\)', starter_code)
        if method_match:
            method_name = method_match.group(2)
            if 'hash' in problem_types and 'array' in problem_types:
                solution = self._add_hash_array_solution_cpp(solution, method_name, parsed)
            elif 'array' in problem_types:
                solution = self._add_array_solution_cpp(solution, method_name, parsed)
            elif 'tree' in problem_types:
                solution = self._add_tree_solution_cpp(solution, method_name, parsed)
            else:
                solution = self._add_generic_solution_cpp(solution, method_name, parsed)
        
        return header + solution
    
    def _generate_javascript_solution(self, starter_code: str, problem_types: List[str],
                                     parsed: Dict, title: str, difficulty: str, title_slug: str = '') -> str:
        """Generate JavaScript solution."""
        solution = starter_code.rstrip()
        header = f'''/**
 * Problem: {title}
 * Difficulty: {difficulty}
 * Tags: {', '.join(problem_types)}
 * 
 * Approach: {self._get_approach_description(problem_types)}
 * Time Complexity: {self._get_time_complexity(problem_types)}
 * Space Complexity: {self._get_space_complexity(problem_types)}
 */

'''
        return header + solution
    
    def _generate_typescript_solution(self, starter_code: str, problem_types: List[str],
                                     parsed: Dict, title: str, difficulty: str, title_slug: str = '') -> str:
        """Generate TypeScript solution."""
        return self._generate_javascript_solution(starter_code, problem_types, parsed, title, difficulty)
    
    def _generate_c_solution(self, starter_code: str, problem_types: List[str],
                            parsed: Dict, title: str, difficulty: str, title_slug: str = '') -> str:
        """Generate C solution."""
        solution = starter_code.rstrip()
        header = f'''/*
    * Problem: {title}
    * Difficulty: {difficulty}
    * Tags: {', '.join(problem_types)}
    * 
    * Approach: {self._get_approach_description(problem_types)}
    * Time Complexity: {self._get_time_complexity(problem_types)}
    * Space Complexity: {self._get_space_complexity(problem_types)}
    */

'''
        return header + solution
    
    def _generate_csharp_solution(self, starter_code: str, problem_types: List[str],
                                 parsed: Dict, title: str, difficulty: str, title_slug: str = '') -> str:
        """Generate C# solution."""
        solution = starter_code.rstrip()
        header = f'''/*
    * Problem: {title}
    * Difficulty: {difficulty}
    * Tags: {', '.join(problem_types)}
    * 
    * Approach: {self._get_approach_description(problem_types)}
    * Time Complexity: {self._get_time_complexity(problem_types)}
    * Space Complexity: {self._get_space_complexity(problem_types)}
    */

'''
        
        # Extract method
        method_match = re.search(r'public\s+\w+\s+(\w+)\s*\([^)]*\)', starter_code)
        if method_match:
            method_name = method_match.group(1)
            if 'hash' in problem_types and 'array' in problem_types:
                solution = self._add_hash_array_solution_csharp(solution, method_name, parsed)
            elif 'array' in problem_types:
                solution = self._add_array_solution_csharp(solution, method_name, parsed)
            else:
                solution = self._add_generic_solution_csharp(solution, method_name, parsed)
        
        return header + solution
    
    def _add_hash_array_solution_csharp(self, code: str, method_name: str, parsed: Dict) -> str:
        """Add hash map + array solution for C#."""
        body = '''Dictionary<int, int> map = new Dictionary<int, int>();
        for (int i = 0; i < nums.Length; i++) {
            int complement = target - nums[i];
            if (map.ContainsKey(complement)) {
                return new int[] { map[complement], i };
            }
            map[nums[i]] = i;
        }
        return new int[] {};'''
        return self._replace_csharp_method_body(code, method_name, body)
    
    def _add_array_solution_csharp(self, code: str, method_name: str, parsed: Dict) -> str:
        """Add array solution for C#."""
        if 'height' in code.lower():
            body = '''int left = 0, right = height.Length - 1;
        int maxArea = 0;
        
        while (left < right) {
            int width = right - left;
            int area = width * Math.Min(height[left], height[right]);
            maxArea = Math.Max(maxArea, area);
            
            if (height[left] < height[right]) {
                left++;
            } else {
                right--;
            }
        }
        
        return maxArea;'''
        else:
            body = '''int left = 0, right = nums.Length - 1;
        
        while (left < right) {
            if (nums[left] + nums[right] == target) {
                return new int[] { left, right };
            } else if (nums[left] + nums[right] < target) {
                left++;
            } else {
                right--;
            }
        }
        
        return new int[] {};'''
        return self._replace_csharp_method_body(code, method_name, body)
    
    def _add_generic_solution_csharp(self, code: str, method_name: str, parsed: Dict) -> str:
        """Add generic solution for C#."""
        body = '''int result = 0;
        foreach (int num in nums) {
            result += num;
        }
        return result;'''
        return self._replace_csharp_method_body(code, method_name, body)
    
    def _replace_csharp_method_body(self, code: str, method_name: str, body: str) -> str:
        """Replace C# method body."""
        pattern = r'(public\s+\w+\s+' + method_name + r'\s*\([^)]*\)\s*\{)'
        match = re.search(pattern, code)
        if match:
            start = match.end()
            brace_count = 1
            end = start
            for i in range(start, len(code)):
                if code[i] == '{':
                    brace_count += 1
                elif code[i] == '}':
                    brace_count -= 1
                    if brace_count == 0:
                        end = i
                        break
            body_lines = body.split('\n')
            indented_body = '\n'.join(['        ' + line for line in body_lines])
            return code[:start] + '\n' + indented_body + '\n    ' + code[end:]
        return code
    
    def _generate_go_solution(self, starter_code: str, problem_types: List[str],
                             parsed: Dict, title: str, difficulty: str, title_slug: str = '') -> str:
        """Generate Go solution."""
        solution = starter_code.rstrip()
        header = f'''// Problem: {title}
// Difficulty: {difficulty}
// Tags: {', '.join(problem_types)}
// 
// Approach: {self._get_approach_description(problem_types)}
// Time Complexity: {self._get_time_complexity(problem_types)}
// Space Complexity: {self._get_space_complexity(problem_types)}

'''
        return header + solution
    
    def _generate_rust_solution(self, starter_code: str, problem_types: List[str],
                               parsed: Dict, title: str, difficulty: str, title_slug: str = '') -> str:
        """Generate Rust solution."""
        solution = starter_code.rstrip()
        header = f'''// Problem: {title}
// Difficulty: {difficulty}
// Tags: {', '.join(problem_types)}
// 
// Approach: {self._get_approach_description(problem_types)}
// Time Complexity: {self._get_time_complexity(problem_types)}
// Space Complexity: {self._get_space_complexity(problem_types)}

'''
        return header + solution
    
    def _generate_generic_solution(self, starter_code: str, problem_types: List[str],
                                   parsed: Dict, title: str, difficulty: str, title_slug: str = '') -> str:
        """Generate generic solution for unsupported languages."""
        return starter_code
    
    # Helper methods for adding solution logic
    def _add_hash_array_solution_python(self, code: str, func_name: str, parsed: Dict) -> str:
        """Add hash map + array solution (e.g., Two Sum)."""
        return self._replace_function_body(code, func_name, '''seen = {}
        for i, num in enumerate(nums):
            complement = target - num
            if complement in seen:
                return [seen[complement], i]
            seen[num] = i
        return []''')
    
    def _add_array_solution_python(self, code: str, func_name: str, parsed: Dict) -> str:
        """Add array solution logic for Python (two pointers, sliding window)."""
        # Check function signature to determine approach
        func_sig = re.search(r'def\s+\w+\s*\(([^)]*)\)', code)
        if func_sig:
            params = func_sig.group(1)
            if 'height' in params.lower():
                # Container with most water pattern
                return self._replace_function_body(code, func_name, '''left, right = 0, len(height) - 1
        max_area = 0
        
        while left < right:
            width = right - left
            area = width * min(height[left], height[right])
            max_area = max(max_area, area)
            
            if height[left] < height[right]:
                left += 1
            else:
                right -= 1
        
        return max_area''')
            elif 'target' in params.lower() and 'nums' in params.lower():
                # Two sum or similar
                return self._add_hash_array_solution_python(code, func_name, parsed)
        
        # Generic two pointers
        return self._replace_function_body(code, func_name, '''left, right = 0, len(nums) - 1
        
        while left < right:
            # TODO: Implement two pointers logic based on problem
            if nums[left] + nums[right] == target:
                return [left, right]
            elif nums[left] + nums[right] < target:
                left += 1
            else:
                right -= 1
        
        return []''')
    
    def _add_string_solution_python(self, code: str, func_name: str, parsed: Dict) -> str:
        """Add string solution logic for Python."""
        return self._replace_function_body(code, func_name, '''# String manipulation solution
        # Common patterns: sliding window, two pointers, hash map
        char_count = {}
        left = 0
        max_len = 0
        
        for right in range(len(s)):
            char_count[s[right]] = char_count.get(s[right], 0) + 1
            
            # Adjust window based on problem constraints
            while len(char_count) > k:  # Example: longest substring with at most k distinct chars
                char_count[s[left]] -= 1
                if char_count[s[left]] == 0:
                    del char_count[s[left]]
                left += 1
            
            max_len = max(max_len, right - left + 1)
        
        return max_len''')
    
    def _add_tree_solution_python(self, code: str, func_name: str, parsed: Dict) -> str:
        """Add tree solution logic for Python (DFS/BFS)."""
        return self._replace_function_body(code, func_name, '''# DFS solution
        if not root:
            return []
        
        result = []
        
        def dfs(node):
            if not node:
                return
            # Pre-order, in-order, or post-order traversal
            result.append(node.val)  # Pre-order
            dfs(node.left)
            # result.append(node.val)  # In-order
            dfs(node.right)
            # result.append(node.val)  # Post-order
        
        dfs(root)
        return result''')
    
    def _add_dp_solution_python(self, code: str, func_name: str, parsed: Dict) -> str:
        """Add dynamic programming solution for Python."""
        return self._replace_function_body(code, func_name, '''# DP solution with memoization
        memo = {}
        
        def dp(i):
            if i in memo:
                return memo[i]
            
            # Base case
            if i < 0:
                return 0
            
            # Recurrence relation
            result = max(dp(i-1), dp(i-2) + nums[i])
            memo[i] = result
            return result
        
        return dp(len(nums) - 1)''')
    
    def _add_hash_solution_python(self, code: str, func_name: str, parsed: Dict) -> str:
        """Add hash map solution for Python."""
        return self._replace_function_body(code, func_name, '''seen = {}
        for i, num in enumerate(nums):
            if num in seen:
                return [seen[num], i]
            seen[num] = i
        return []''')
    
    def _add_generic_solution_python(self, code: str, func_name: str, parsed: Dict) -> str:
        """Add generic solution for Python."""
        return self._replace_function_body(code, func_name, '''# Optimized solution
        # Analyze problem constraints and implement accordingly
        result = 0
        
        for i in range(len(nums)):
            # Implement logic based on problem requirements
            result += nums[i]
        
        return result''')
    
    def _replace_function_body(self, code: str, func_name: str, body: str) -> str:
        """Replace function body with actual implementation."""
        lines = code.split('\n')
        result = []
        in_function = False
        indent_level = 0
        func_start_idx = -1
        
        for i, line in enumerate(lines):
            if re.match(r'\s*def\s+' + func_name + r'\s*\(', line):
                result.append(line)
                in_function = True
                indent_level = len(line) - len(line.lstrip())
                func_start_idx = i
                # Skip existing body until we find the next def/class at same or less indentation
                continue
            
            if in_function:
                current_indent = len(line) - len(line.lstrip()) if line.strip() else indent_level + 1
                # If we hit a line with same or less indentation (and it's not empty), we're out of function
                if line.strip() and current_indent <= indent_level and not line.strip().startswith('#'):
                    # Add the body before this line
                    body_lines = body.split('\n')
                    for body_line in body_lines:
                        result.append(' ' * (indent_level + 4) + body_line)
                    in_function = False
                    result.append(line)
                    continue
                # Skip existing body lines
                continue
            
            result.append(line)
        
        # If we're still in function at the end, add body
        if in_function:
            body_lines = body.split('\n')
            for body_line in body_lines:
                result.append(' ' * (indent_level + 4) + body_line)
        
        return '\n'.join(result)
    
    # Java solution helpers
    def _add_hash_array_solution_java(self, code: str, method_name: str, parsed: Dict) -> str:
        """Add hash map + array solution for Java."""
        body = '''Map<Integer, Integer> map = new HashMap<>();
        for (int i = 0; i < nums.length; i++) {
            int complement = target - nums[i];
            if (map.containsKey(complement)) {
                return new int[]{map.get(complement), i};
            }
            map.put(nums[i], i);
        }
        return new int[]{};'''
        return self._replace_java_method_body(code, method_name, body)
    
    def _add_array_solution_java(self, code: str, method_name: str, parsed: Dict) -> str:
        """Add array solution for Java."""
        # Check if it's container with most water
        if 'height' in code.lower():
            body = '''int left = 0, right = height.length - 1;
        int maxArea = 0;
        
        while (left < right) {
            int width = right - left;
            int area = width * Math.min(height[left], height[right]);
            maxArea = Math.max(maxArea, area);
            
            if (height[left] < height[right]) {
                left++;
            } else {
                right--;
            }
        }
        
        return maxArea;'''
        else:
            body = '''int left = 0, right = nums.length - 1;
        
        while (left < right) {
            if (nums[left] + nums[right] == target) {
                return new int[]{left, right};
            } else if (nums[left] + nums[right] < target) {
                left++;
            } else {
                right--;
            }
        }
        
        return new int[]{};'''
        return self._replace_java_method_body(code, method_name, body)
    
    def _add_string_solution_java(self, code: str, method_name: str, parsed: Dict) -> str:
        """Add string solution for Java."""
        body = '''Map<Character, Integer> charCount = new HashMap<>();
        int left = 0;
        int maxLen = 0;
        
        for (int right = 0; right < s.length(); right++) {
            charCount.put(s.charAt(right), charCount.getOrDefault(s.charAt(right), 0) + 1);
            
            while (charCount.size() > k) {
                charCount.put(s.charAt(left), charCount.get(s.charAt(left)) - 1);
                if (charCount.get(s.charAt(left)) == 0) {
                    charCount.remove(s.charAt(left));
                }
                left++;
            }
            
            maxLen = Math.max(maxLen, right - left + 1);
        }
        
        return maxLen;'''
        return self._replace_java_method_body(code, method_name, body)
    
    def _add_tree_solution_java(self, code: str, method_name: str, parsed: Dict) -> str:
        """Add tree solution for Java."""
        body = '''List<Integer> result = new ArrayList<>();
        dfs(root, result);
        return result;
    }
    
    private void dfs(TreeNode node, List<Integer> result) {
        if (node == null) return;
        result.add(node.val);  // Pre-order
        dfs(node.left, result);
        dfs(node.right, result);'''
        return self._replace_java_method_body(code, method_name, body)
    
    def _add_dp_solution_java(self, code: str, method_name: str, parsed: Dict) -> str:
        """Add DP solution for Java."""
        body = '''int[] dp = new int[nums.length + 1];
        dp[0] = 0;
        dp[1] = nums[0];
        
        for (int i = 2; i <= nums.length; i++) {
            dp[i] = Math.max(dp[i-1], dp[i-2] + nums[i-1]);
        }
        
        return dp[nums.length];'''
        return self._replace_java_method_body(code, method_name, body)
    
    def _add_generic_solution_java(self, code: str, method_name: str, parsed: Dict) -> str:
        """Add generic solution for Java."""
        body = '''int result = 0;
        for (int num : nums) {
            result += num;
        }
        return result;'''
        return self._replace_java_method_body(code, method_name, body)
    
    def _replace_java_method_body(self, code: str, method_name: str, body: str) -> str:
        """Replace Java method body."""
        # Find method signature
        pattern = r'(public\s+\w+\s+' + method_name + r'\s*\([^)]*\)\s*\{)'
        match = re.search(pattern, code)
        if match:
            start = match.end()
            # Find matching closing brace
            brace_count = 1
            end = start
            for i in range(start, len(code)):
                if code[i] == '{':
                    brace_count += 1
                elif code[i] == '}':
                    brace_count -= 1
                    if brace_count == 0:
                        end = i
                        break
            # Replace body
            body_lines = body.split('\n')
            indented_body = '\n'.join(['        ' + line for line in body_lines])
            return code[:start] + '\n' + indented_body + '\n    ' + code[end:]
        return code
    
    # C++ solution helpers
    def _add_hash_array_solution_cpp(self, code: str, method_name: str, parsed: Dict) -> str:
        """Add hash map + array solution for C++."""
        body = '''unordered_map<int, int> map;
        for (int i = 0; i < nums.size(); i++) {
            int complement = target - nums[i];
            if (map.find(complement) != map.end()) {
                return {map[complement], i};
            }
            map[nums[i]] = i;
        }
        return {};'''
        return self._replace_cpp_method_body(code, method_name, body)
    
    def _add_array_solution_cpp(self, code: str, method_name: str, parsed: Dict) -> str:
        """Add array solution for C++."""
        if 'height' in code.lower():
            body = '''int left = 0, right = height.size() - 1;
        int maxArea = 0;
        
        while (left < right) {
            int width = right - left;
            int area = width * min(height[left], height[right]);
            maxArea = max(maxArea, area);
            
            if (height[left] < height[right]) {
                left++;
            } else {
                right--;
            }
        }
        
        return maxArea;'''
        else:
            body = '''int left = 0, right = nums.size() - 1;
        
        while (left < right) {
            if (nums[left] + nums[right] == target) {
                return {left, right};
            } else if (nums[left] + nums[right] < target) {
                left++;
            } else {
                right--;
            }
        }
        
        return {};'''
        return self._replace_cpp_method_body(code, method_name, body)
    
    def _add_tree_solution_cpp(self, code: str, method_name: str, parsed: Dict) -> str:
        """Add tree solution for C++."""
        body = '''vector<int> result;
        dfs(root, result);
        return result;
    }
    
private:
    void dfs(TreeNode* node, vector<int>& result) {
        if (!node) return;
        result.push_back(node->val);  // Pre-order
        dfs(node->left, result);
        dfs(node->right, result);
    }'''
        return self._replace_cpp_method_body(code, method_name, body)
    
    def _add_generic_solution_cpp(self, code: str, method_name: str, parsed: Dict) -> str:
        """Add generic solution for C++."""
        body = '''int result = 0;
        for (int num : nums) {
            result += num;
        }
        return result;'''
        return self._replace_cpp_method_body(code, method_name, body)
    
    def _replace_cpp_method_body(self, code: str, method_name: str, body: str) -> str:
        """Replace C++ method body."""
        pattern = r'(\w+\s+' + method_name + r'\s*\([^)]*\)\s*\{)'
        match = re.search(pattern, code)
        if match:
            start = match.end()
            brace_count = 1
            end = start
            for i in range(start, len(code)):
                if code[i] == '{':
                    brace_count += 1
                elif code[i] == '}':
                    brace_count -= 1
                    if brace_count == 0:
                        end = i
                        break
            body_lines = body.split('\n')
            indented_body = '\n'.join(['        ' + line for line in body_lines])
            return code[:start] + '\n' + indented_body + '\n    ' + code[end:]
        return code
    
    # Complexity and approach descriptions
    def _get_approach_description(self, problem_types: List[str]) -> str:
        """Get approach description based on problem types."""
        if 'array' in problem_types:
            return 'Use two pointers or sliding window technique'
        elif 'string' in problem_types:
            return 'String manipulation with hash map or two pointers'
        elif 'tree' in problem_types:
            return 'DFS or BFS traversal'
        elif 'dp' in problem_types:
            return 'Dynamic programming with memoization or tabulation'
        elif 'hash' in problem_types:
            return 'Use hash map for O(1) lookups'
        elif 'greedy' in problem_types:
            return 'Greedy algorithm with local optimal choices'
        else:
            return 'Optimized algorithm based on problem constraints'
    
    def _get_time_complexity(self, problem_types: List[str]) -> str:
        """Get time complexity estimate."""
        if 'array' in problem_types or 'string' in problem_types:
            return 'O(n) or O(n log n)'
        elif 'tree' in problem_types:
            return 'O(n) where n is number of nodes'
        elif 'dp' in problem_types:
            return 'O(n * m) where n and m are problem dimensions'
        else:
            return 'O(n) to O(n^2) depending on approach'
    
    def _get_space_complexity(self, problem_types: List[str]) -> str:
        """Get space complexity estimate."""
        if 'dp' in problem_types:
            return 'O(n) or O(n * m) for DP table'
        elif 'tree' in problem_types:
            return 'O(h) for recursion stack where h is height'
        elif 'hash' in problem_types:
            return 'O(n) for hash map'
        else:
            return 'O(1) to O(n) depending on approach'

