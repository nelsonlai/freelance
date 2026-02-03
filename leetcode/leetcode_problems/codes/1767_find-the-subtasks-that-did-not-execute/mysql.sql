-- Problem: Find the Subtasks That Did Not Execute
-- Difficulty: Hard
-- Tags: database

-- Approach: Generate all subtasks using recursive CTE, then LEFT JOIN to find missing
-- Time Complexity: O(n * m) where n is tasks, m is subtasks per task
-- Space Complexity: O(n * m)

WITH RECURSIVE SubtaskGenerator AS (
    SELECT task_id, subtasks_count, 1 AS subtask_id
    FROM Tasks
    
    UNION ALL
    
    SELECT task_id, subtasks_count, subtask_id + 1
    FROM SubtaskGenerator
    WHERE subtask_id < subtasks_count
)
SELECT sg.task_id, sg.subtask_id
FROM SubtaskGenerator sg
LEFT JOIN Executed e ON sg.task_id = e.task_id AND sg.subtask_id = e.subtask_id
WHERE e.task_id IS NULL
ORDER BY sg.task_id, sg.subtask_id;

