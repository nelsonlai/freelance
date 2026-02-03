#pragma once

#include <sqlite3.h>
#include <string>
#include <vector>
#include <memory>
#include <chrono>

/**
 * DatabaseLogger class handles SQLite database operations for defect logging
 * Stores defect detection results with timestamps and metadata
 */
class DatabaseLogger {
public:
    /**
     * Constructor
     * @param db_path Path to SQLite database file
     */
    DatabaseLogger(const std::string& db_path);
    
    /**
     * Destructor
     */
    ~DatabaseLogger();
    
    /**
     * Initialize database and create tables if needed
     * @return true if initialization successful, false otherwise
     */
    bool initialize();
    
    /**
     * Log defect detection result
     * @param class_label Detected defect class
     * @param confidence Confidence score
     * @param processing_time Processing time in milliseconds
     * @param image_path Path to saved image (optional)
     * @return true if logging successful, false otherwise
     */
    bool logDefect(const std::string& class_label, double confidence, 
                   double processing_time, const std::string& image_path = "");
    
    /**
     * Get defect statistics for a time period
     * @param start_time Start timestamp
     * @param end_time End timestamp
     * @return Map of class names to counts
     */
    std::map<std::string, int> getDefectStatistics(
        const std::chrono::system_clock::time_point& start_time,
        const std::chrono::system_clock::time_point& end_time);
    
    /**
     * Get recent defects (last N records)
     * @param count Number of recent records to retrieve
     * @return Vector of defect records
     */
    std::vector<DefectRecord> getRecentDefects(int count = 100);
    
    /**
     * Check if database is ready
     * @return true if ready, false otherwise
     */
    bool isReady() const;
    
    /**
     * Close database connection
     */
    void close();

private:
    sqlite3* db_;
    std::string db_path_;
    bool initialized_;
    
    /**
     * Create database tables
     * @return true if successful, false otherwise
     */
    bool createTables();
    
    /**
     * Execute SQL query
     * @param sql SQL query string
     * @return true if successful, false otherwise
     */
    bool executeQuery(const std::string& sql);
    
    /**
     * Get current timestamp as string
     * @return Timestamp string
     */
    std::string getCurrentTimestamp() const;
};

/**
 * DefectRecord struct for database records
 */
struct DefectRecord {
    int id;
    std::string timestamp;
    std::string class_label;
    double confidence;
    double processing_time_ms;
    std::string image_path;
    
    DefectRecord() : id(0), confidence(0.0), processing_time_ms(0.0) {}
};
