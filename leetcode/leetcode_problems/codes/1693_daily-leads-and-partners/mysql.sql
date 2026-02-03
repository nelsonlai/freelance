-- Problem: Daily Leads and Partners
-- Difficulty: Easy
-- Tags: database

-- Approach: Count distinct leads and partners per date and make_name
-- Time Complexity: O(n) where n is records
-- Space Complexity: O(1)

SELECT 
    date_id,
    make_name,
    COUNT(DISTINCT lead_id) AS unique_leads,
    COUNT(DISTINCT partner_id) AS unique_partners
FROM DailySales
GROUP BY date_id, make_name;

