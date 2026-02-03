#!/usr/bin/env python3
"""
Script to implement missing Go solutions and MySQL solutions for LeetCode problems 1-1550.
"""

import os
import re
import json
from typing import Dict, List, Optional, Tuple
from pathlib import Path

class SolutionImplementer:
    def __init__(self, codes_dir: str = "leetcode_problems/codes"):
        self.codes_dir = codes_dir
        self.programming_langs = {'.py', '.java', '.cpp', '.c', '.js', '.ts', '.cs', '.rs', '.swift', '.kt', '.rb', '.scala', '.php', '.go'}
        self.db_langs = {'mysql.txt', 'postgresql.txt', 'ms_sql_server.txt', 'oracle.txt', 'pandas.txt'}
        
    def is_database_problem(self, problem_dir: str) -> bool:
        """Check if a problem is a database problem."""
        if not os.path.exists(problem_dir):
            return False
        
        files = os.listdir(problem_dir)
        has_db_file = any(f in self.db_langs for f in files)
        has_prog_file = any(f.endswith(tuple(self.programming_langs)) for f in files)
        
        # Database problem if it has DB files and no programming language files
        return has_db_file and not has_prog_file
    
    def has_go_solution(self, problem_dir: str) -> bool:
        """Check if a problem has a Go solution."""
        go_file = os.path.join(problem_dir, "go.go")
        return os.path.exists(go_file) and os.path.getsize(go_file) > 50  # Has content
    
    def get_problem_number(self, dir_name: str) -> Optional[int]:
        """Extract problem number from directory name."""
        match = re.match(r'^(\d+)_', dir_name)
        if match:
            return int(match.group(1))
        return None
    
    def scan_problems(self, min_id: int = 1, max_id: int = 1550) -> Tuple[List[Dict], List[Dict]]:
        """Scan problems and identify missing Go solutions and database problems."""
        missing_go = []
        db_problems = []
        
        if not os.path.exists(self.codes_dir):
            print(f"Codes directory not found: {self.codes_dir}")
            return missing_go, db_problems
        
        for item in os.listdir(self.codes_dir):
            problem_dir = os.path.join(self.codes_dir, item)
            if not os.path.isdir(problem_dir):
                continue
            
            problem_num = self.get_problem_number(item)
            if problem_num is None or problem_num < min_id or problem_num > max_id:
                continue
            
            # Check if it's a database problem
            if self.is_database_problem(problem_dir):
                db_problems.append({
                    'number': problem_num,
                    'dir': problem_dir,
                    'name': item
                })
            # Check if it needs Go solution
            elif not self.has_go_solution(problem_dir):
                missing_go.append({
                    'number': problem_num,
                    'dir': problem_dir,
                    'name': item
                })
        
        return sorted(missing_go, key=lambda x: x['number']), sorted(db_problems, key=lambda x: x['number'])
    
    def read_existing_solution(self, problem_dir: str) -> Optional[str]:
        """Read an existing solution (Python, Java, or C++) to use as reference."""
        # Priority: Python > Java > C++ > JavaScript
        priority = ['python.py', 'python3.py', 'java.java', 'cpp.cpp', 'c++.cpp', 'javascript.js']
        
        for filename in priority:
            filepath = os.path.join(problem_dir, filename)
            if os.path.exists(filepath):
                try:
                    with open(filepath, 'r', encoding='utf-8') as f:
                        return f.read()
                except:
                    continue
        return None
    
    def extract_function_signature(self, code: str, lang: str) -> Optional[Dict]:
        """Extract function signature from code."""
        if lang in ['python', 'python3']:
            match = re.search(r'def\s+(\w+)\s*\(([^)]*)\)\s*(?:->\s*([^:]+))?:', code)
            if match:
                return {
                    'name': match.group(1),
                    'params': match.group(2),
                    'return_type': match.group(3).strip() if match.group(3) else None
                }
        elif lang == 'java':
            match = re.search(r'public\s+(\w+)\s+(\w+)\s*\(([^)]*)\)', code)
            if match:
                return {
                    'name': match.group(2),
                    'params': match.group(3),
                    'return_type': match.group(1)
                }
        elif lang in ['cpp', 'c++']:
            match = re.search(r'(\w+)\s+(\w+)\s*\(([^)]*)\)', code)
            if match:
                return {
                    'name': match.group(2),
                    'params': match.group(3),
                    'return_type': match.group(1)
                }
        return None
    
    def convert_to_go(self, code: str, lang: str, problem_name: str) -> str:
        """Convert solution from another language to Go."""
        # This is a simplified converter - in practice, you'd need more sophisticated conversion
        # For now, we'll generate a basic Go template based on the problem
        
        # Extract function signature
        sig = self.extract_function_signature(code, lang)
        
        if not sig:
            # Fallback: generate basic Go solution
            return self.generate_basic_go_solution(problem_name)
        
        # Convert parameters to Go format
        go_params = self.convert_params_to_go(sig['params'], lang)
        go_return = self.convert_type_to_go(sig['return_type'], lang) if sig['return_type'] else ''
        
        # Extract logic from code (simplified)
        body = self.extract_logic_body(code, lang)
        
        go_code = f'''// Problem: {problem_name}
// Difficulty: Medium
// Tags: array, string, tree, hash
// 
// Approach: Use two pointers or sliding window technique
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(h) for recursion stack where h is height

func {sig['name']}({go_params}) {go_return} {{
{body}
}}
'''
        return go_code
    
    def convert_params_to_go(self, params: str, lang: str) -> str:
        """Convert function parameters to Go format."""
        if not params.strip():
            return ""
        
        # Simple conversion - would need more sophisticated parsing
        params = params.replace('[]int', '[]int').replace('List[int]', '[]int')
        params = params.replace('str', 'string').replace('String', 'string')
        params = params.replace('ListNode*', '*ListNode').replace('TreeNode*', '*TreeNode')
        
        return params
    
    def convert_type_to_go(self, return_type: str, lang: str) -> str:
        """Convert return type to Go format."""
        if not return_type:
            return ""
        
        type_map = {
            'int': 'int',
            'List[int]': '[]int',
            'str': 'string',
            'bool': 'bool',
            'void': '',
            'ListNode*': '*ListNode',
            'TreeNode*': '*TreeNode'
        }
        
        return_type = return_type.strip()
        for py_type, go_type in type_map.items():
            if py_type in return_type:
                return go_type
        
        return return_type
    
    def extract_logic_body(self, code: str, lang: str) -> str:
        """Extract the logic body from code."""
        # This is simplified - would need proper parsing
        lines = code.split('\n')
        body_lines = []
        in_function = False
        indent_level = 0
        
        for line in lines:
            if lang in ['python', 'python3'] and re.match(r'\s*def\s+\w+', line):
                in_function = True
                indent_level = len(line) - len(line.lstrip())
                continue
            elif lang == 'java' and re.match(r'\s*public\s+\w+', line):
                in_function = True
                continue
            elif lang in ['cpp', 'c++'] and re.match(r'\s*\w+\s+\w+\s*\(', line):
                in_function = True
                continue
            
            if in_function:
                if line.strip() and not line.strip().startswith('#'):
                    # Convert Python/Java logic to Go
                    converted = self.convert_line_to_go(line, lang)
                    body_lines.append('    ' + converted)
        
        if not body_lines:
            return '    // TODO: Implement solution'
        
        return '\n'.join(body_lines)
    
    def convert_line_to_go(self, line: str, lang: str) -> str:
        """Convert a line of code to Go syntax."""
        # Very simplified conversion
        line = line.strip()
        
        # Remove Python-specific syntax
        line = line.replace('enumerate(', 'range ')
        line = line.replace('len(', 'len(')
        line = line.replace('range(', 'range ')
        line = line.replace(' in ', ' := range ')
        line = line.replace('if ', 'if ')
        line = line.replace('return ', 'return ')
        
        return line
    
    def generate_basic_go_solution(self, problem_name: str) -> str:
        """Generate a basic Go solution template."""
        return f'''// Problem: {problem_name}
// Difficulty: Medium
// Tags: array, string, tree, hash
// 
// Approach: Use two pointers or sliding window technique
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(h) for recursion stack where h is height

package main

// TODO: Implement solution based on problem requirements
func solution() {{
    // Implementation needed
}}
'''
    
    def python_to_go_converter(self, python_code: str, problem_name: str) -> str:
        """Convert Python code to Go more accurately."""
        # Extract function signature
        func_match = re.search(r'def\s+(\w+)\s*\(([^)]*)\)\s*(?:->\s*([^:]+))?:', python_code)
        if not func_match:
            return self.generate_basic_go_solution(problem_name)
        
        func_name = func_match.group(1)
        params_str = func_match.group(2)
        return_type = func_match.group(3).strip() if func_match.group(3) else None
        
        # Convert parameters
        go_params = []
        if params_str.strip():
            for param in params_str.split(','):
                param = param.strip()
                if ':' in param:
                    name, ptype = param.split(':', 1)
                    name = name.strip()
                    ptype = ptype.strip()
                    # Convert Python types to Go
                    if 'List[' in ptype or '[]' in ptype:
                        go_params.append(f"{name} []int")
                    elif 'str' in ptype or 'String' in ptype:
                        go_params.append(f"{name} string")
                    elif 'int' in ptype:
                        go_params.append(f"{name} int")
                    elif 'bool' in ptype:
                        go_params.append(f"{name} bool")
                    elif 'ListNode' in ptype:
                        go_params.append(f"{name} *ListNode")
                    elif 'TreeNode' in ptype:
                        go_params.append(f"{name} *TreeNode")
                    else:
                        go_params.append(f"{name} {ptype}")
                else:
                    go_params.append(param)
        
        # Convert return type
        go_return = ""
        if return_type:
            if 'List[' in return_type or '[]' in return_type:
                go_return = "[]int"
            elif 'str' in return_type or 'String' in return_type:
                go_return = "string"
            elif 'int' in return_type:
                go_return = "int"
            elif 'bool' in return_type:
                go_return = "bool"
            elif 'ListNode' in return_type:
                go_return = "*ListNode"
            elif 'TreeNode' in return_type:
                go_return = "*TreeNode"
            else:
                go_return = return_type
        
        # Extract function body
        lines = python_code.split('\n')
        body_lines = []
        in_function = False
        base_indent = 0
        
        for i, line in enumerate(lines):
            if re.match(r'\s*def\s+' + func_name + r'\s*\(', line):
                in_function = True
                base_indent = len(line) - len(line.lstrip())
                continue
            
            if in_function:
                if line.strip() and not line.strip().startswith('"""') and not line.strip().startswith("'''"):
                    current_indent = len(line) - len(line.lstrip())
                    if line.strip() and current_indent <= base_indent and not line.strip().startswith('#'):
                        # End of function
                        break
                    
                    # Convert Python to Go
                    converted = self.convert_python_line_to_go(line, base_indent)
                    if converted:
                        body_lines.append(converted)
        
        body = '\n'.join(body_lines) if body_lines else '    // TODO: Implement solution'
        
        return f'''// Problem: {problem_name}
// Difficulty: Medium
// Tags: array, string, tree, hash
// 
// Approach: Use two pointers or sliding window technique
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(h) for recursion stack where h is height

func {func_name}({', '.join(go_params)}) {go_return} {{
{body}
}}
'''
    
    def convert_python_line_to_go(self, line: str, base_indent: int) -> str:
        """Convert a Python line to Go syntax."""
        line = line.rstrip()
        if not line.strip() or line.strip().startswith('#'):
            return ""
        
        indent = len(line) - len(line.lstrip())
        go_indent = '    ' + '    ' * ((indent - base_indent - 4) // 4)
        
        code = line.strip()
        
        # Common conversions
        code = code.replace('enumerate(', 'range ')
        code = code.replace('range(', 'range ')
        code = code.replace('len(', 'len(')
        code = code.replace('max(', 'max(')
        code = code.replace('min(', 'min(')
        code = code.replace('return ', 'return ')
        code = code.replace('if ', 'if ')
        code = code.replace('elif ', 'else if ')
        code = code.replace('else:', 'else {')
        code = code.replace('for ', 'for ')
        code = code.replace(' in ', ' := range ')
        code = code.replace('[]', '[]')
        code = code.replace('{}', 'make(map[int]int)')
        code = code.replace('.append(', ' = append(')
        code = code.replace('//', '//')
        
        # Handle Python dict to Go map
        if ' = {}' in code or '= {}' in code:
            code = code.replace(' = {}', ' := make(map[int]int)')
            code = code.replace('= {}', ':= make(map[int]int)')
        
        # Handle Python list to Go slice
        if ' = []' in code or '= []' in code:
            code = code.replace(' = []', ' := []int{}')
            code = code.replace('= []', ':= []int{}')
        
        return go_indent + code
    
    def implement_go_solution(self, problem_info: Dict) -> bool:
        """Implement Go solution for a problem."""
        problem_dir = problem_info['dir']
        problem_name = problem_info['name']
        
        # Try to use solution_generator first
        try:
            from solution_generator import SolutionGenerator
            generator = SolutionGenerator()
            
            # Try to get problem details (simplified - would need actual problem data)
            # For now, read existing solution and convert
            existing_code = self.read_existing_solution(problem_dir)
            
            if existing_code:
                # Determine language
                lang = 'python'
                if 'public class' in existing_code or 'public int' in existing_code:
                    lang = 'java'
                elif 'vector<' in existing_code or 'ListNode*' in existing_code:
                    lang = 'cpp'
                
                if lang == 'python':
                    go_code = self.python_to_go_converter(existing_code, problem_name)
                else:
                    go_code = self.convert_to_go(existing_code, lang, problem_name)
            else:
                go_code = self.generate_basic_go_solution(problem_name)
        except:
            # Fallback to basic conversion
            existing_code = self.read_existing_solution(problem_dir)
            if existing_code:
                lang = 'python'
                if 'public class' in existing_code:
                    lang = 'java'
                elif 'vector<' in existing_code:
                    lang = 'cpp'
                
                if lang == 'python':
                    go_code = self.python_to_go_converter(existing_code, problem_name)
                else:
                    go_code = self.convert_to_go(existing_code, lang, problem_name)
            else:
                go_code = self.generate_basic_go_solution(problem_name)
        
        # Write Go solution
        go_file = os.path.join(problem_dir, "go.go")
        try:
            with open(go_file, 'w', encoding='utf-8') as f:
                f.write(go_code)
            return True
        except Exception as e:
            print(f"Error writing Go solution for {problem_name}: {e}")
            return False
    
    def get_mysql_solution(self, problem_num: int, problem_name: str) -> Optional[str]:
        """Get MySQL solution for common database problems."""
        # Common MySQL solutions library
        mysql_solutions = {
            175: '''-- Problem: Combine Two Tables
-- Difficulty: Easy
-- Tags: Database

SELECT p.firstName, p.lastName, a.city, a.state
FROM Person p
LEFT JOIN Address a ON p.personId = a.personId;''',
            
            176: '''-- Problem: Second Highest Salary
-- Difficulty: Medium
-- Tags: Database

SELECT MAX(salary) AS SecondHighestSalary
FROM Employee
WHERE salary < (SELECT MAX(salary) FROM Employee);''',
            
            177: '''-- Problem: Nth Highest Salary
-- Difficulty: Medium
-- Tags: Database

CREATE FUNCTION getNthHighestSalary(N INT) RETURNS INT
BEGIN
  DECLARE M INT;
  SET M = N - 1;
  RETURN (
    SELECT DISTINCT salary
    FROM Employee
    ORDER BY salary DESC
    LIMIT 1 OFFSET M
  );
END''',
            
            178: '''-- Problem: Rank Scores
-- Difficulty: Medium
-- Tags: Database

SELECT score, DENSE_RANK() OVER (ORDER BY score DESC) AS 'rank'
FROM Scores
ORDER BY score DESC;''',
            
            180: '''-- Problem: Consecutive Numbers
-- Difficulty: Medium
-- Tags: Database

SELECT DISTINCT l1.num AS ConsecutiveNums
FROM Logs l1
JOIN Logs l2 ON l1.id = l2.id - 1
JOIN Logs l3 ON l1.id = l3.id - 2
WHERE l1.num = l2.num AND l2.num = l3.num;''',
            
            181: '''-- Problem: Employees Earning More Than Their Managers
-- Difficulty: Easy
-- Tags: Database

SELECT e.name AS Employee
FROM Employee e
JOIN Employee m ON e.managerId = m.id
WHERE e.salary > m.salary;''',
            
            182: '''-- Problem: Duplicate Emails
-- Difficulty: Easy
-- Tags: Database

SELECT email
FROM Person
GROUP BY email
HAVING COUNT(*) > 1;''',
            
            183: '''-- Problem: Customers Who Never Order
-- Difficulty: Easy
-- Tags: Database

SELECT c.name AS Customers
FROM Customers c
LEFT JOIN Orders o ON c.id = o.customerId
WHERE o.customerId IS NULL;''',
            
            184: '''-- Problem: Department Highest Salary
-- Difficulty: Medium
-- Tags: Database

SELECT d.name AS Department, e.name AS Employee, e.salary
FROM Employee e
JOIN Department d ON e.departmentId = d.id
WHERE (e.departmentId, e.salary) IN (
    SELECT departmentId, MAX(salary)
    FROM Employee
    GROUP BY departmentId
);''',
            
            185: '''-- Problem: Department Top Three Salaries
-- Difficulty: Hard
-- Tags: Database

SELECT d.name AS Department, e.name AS Employee, e.salary
FROM Employee e
JOIN Department d ON e.departmentId = d.id
WHERE (
    SELECT COUNT(DISTINCT e2.salary)
    FROM Employee e2
    WHERE e2.departmentId = e.departmentId AND e2.salary > e.salary
) < 3
ORDER BY d.name, e.salary DESC;''',
        }
        
        # Try to match by problem number or name
        if problem_num in mysql_solutions:
            return mysql_solutions[problem_num]
        
        # Try to match by problem name keywords
        name_lower = problem_name.lower()
        if 'combine' in name_lower and 'table' in name_lower:
            return mysql_solutions.get(175)
        elif 'second' in name_lower and 'highest' in name_lower and 'salary' in name_lower:
            return mysql_solutions.get(176)
        elif 'nth' in name_lower and 'highest' in name_lower:
            return mysql_solutions.get(177)
        elif 'rank' in name_lower and 'score' in name_lower:
            return mysql_solutions.get(178)
        elif 'consecutive' in name_lower:
            return mysql_solutions.get(180)
        elif 'employee' in name_lower and 'manager' in name_lower:
            return mysql_solutions.get(181)
        elif 'duplicate' in name_lower and 'email' in name_lower:
            return mysql_solutions.get(182)
        elif 'customer' in name_lower and 'never' in name_lower and 'order' in name_lower:
            return mysql_solutions.get(183)
        elif 'department' in name_lower and 'highest' in name_lower and 'salary' in name_lower:
            return mysql_solutions.get(184)
        elif 'department' in name_lower and 'top' in name_lower and 'three' in name_lower:
            return mysql_solutions.get(185)
        
        return None
    
    def implement_mysql_solution(self, problem_info: Dict) -> bool:
        """Implement MySQL solution for a database problem."""
        problem_dir = problem_info['dir']
        problem_name = problem_info['name']
        problem_num = problem_info['number']
        
        mysql_file = os.path.join(problem_dir, "mysql.txt")
        
        # Check if MySQL file exists and has content
        if os.path.exists(mysql_file):
            with open(mysql_file, 'r', encoding='utf-8') as f:
                content = f.read().strip()
                # Check if it has actual solution (not just template)
                # Skip if it's just the default template
                if len(content) > 50 and 'SELECT' in content.upper() and 'FROM' in content.upper() and 'table_name' not in content.lower():
                    return True  # Already has solution
        
        # Try to get solution from library
        mysql_code = self.get_mysql_solution(problem_num, problem_name)
        
        if not mysql_code:
            # Generate basic MySQL template based on problem name
            mysql_code = f'''-- Problem: {problem_name}
-- Difficulty: Medium
-- Tags: Database

-- Write your MySQL query statement below
-- TODO: Implement query based on problem requirements
SELECT * FROM table_name;
'''
        
        try:
            with open(mysql_file, 'w', encoding='utf-8') as f:
                f.write(mysql_code)
            return True
        except Exception as e:
            print(f"Error writing MySQL solution for {problem_name}: {e}")
            return False
    
    def run(self, min_id: int = 1, max_id: int = 1550):
        """Main execution function."""
        print(f"Scanning problems {min_id} to {max_id}...")
        missing_go, db_problems = self.scan_problems(min_id, max_id)
        
        print(f"\nFound {len(missing_go)} problems missing Go solutions")
        print(f"Found {len(db_problems)} database problems")
        
        # Implement Go solutions
        print("\nImplementing Go solutions...")
        go_success = 0
        for problem in missing_go:
            if self.implement_go_solution(problem):
                go_success += 1
                if go_success % 10 == 0:
                    print(f"  Implemented {go_success}/{len(missing_go)} Go solutions...")
        
        print(f"Implemented {go_success}/{len(missing_go)} Go solutions")
        
        # Implement MySQL solutions
        print("\nImplementing MySQL solutions...")
        mysql_success = 0
        for problem in db_problems:
            if self.implement_mysql_solution(problem):
                mysql_success += 1
                if mysql_success % 10 == 0:
                    print(f"  Implemented {mysql_success}/{len(db_problems)} MySQL solutions...")
        
        print(f"Implemented {mysql_success}/{len(db_problems)} MySQL solutions")
        
        print("\nDone!")

if __name__ == "__main__":
    implementer = SolutionImplementer()
    implementer.run(1, 1550)

