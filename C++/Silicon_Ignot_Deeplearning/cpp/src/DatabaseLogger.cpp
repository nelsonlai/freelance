#include "DatabaseLogger.h"
#include <iostream>
#include <sstream>
#include <iomanip>

DatabaseLogger::DatabaseLogger(const std::string& db_path)
    : db_(nullptr), db_path_(db_path), initialized_(false) {
}

DatabaseLogger::~DatabaseLogger() {
    close();
}

bool DatabaseLogger::initialize() {
    // Open database
    int rc = sqlite3_open(db_path_.c_str(), &db_);
    if (rc != SQLITE_OK) {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db_) << std::endl;
        return false;
    }
    
    // Create tables
    if (!createTables()) {
        std::cerr << "Error creating database tables" << std::endl;
        return false;
    }
    
    initialized_ = true;
    std::cout << "Database logger initialized: " << db_path_ << std::endl;
    return true;
}

bool DatabaseLogger::logDefect(const std::string& class_label, double confidence,
                              double processing_time, const std::string& image_path) {
    if (!initialized_) {
        std::cerr << "Database logger not initialized" << std::endl;
        return false;
    }
    
    std::ostringstream sql;
    sql << "INSERT INTO defects (timestamp, class_label, confidence, processing_time_ms, image_path) "
        << "VALUES ('" << getCurrentTimestamp() << "', '" << class_label << "', "
        << confidence << ", " << processing_time << ", '" << image_path << "');";
    
    if (!executeQuery(sql.str())) {
        std::cerr << "Error logging defect to database" << std::endl;
        return false;
    }
    
    return true;
}

std::map<std::string, int> DatabaseLogger::getDefectStatistics(
    const std::chrono::system_clock::time_point& start_time,
    const std::chrono::system_clock::time_point& end_time) {
    
    std::map<std::string, int> stats;
    
    if (!initialized_) {
        return stats;
    }
    
    // Convert time points to strings
    auto start_time_t = std::chrono::system_clock::to_time_t(start_time);
    auto end_time_t = std::chrono::system_clock::to_time_t(end_time);
    
    std::ostringstream start_str, end_str;
    start_str << std::put_time(std::localtime(&start_time_t), "%Y-%m-%d %H:%M:%S");
    end_str << std::put_time(std::localtime(&end_time_t), "%Y-%m-%d %H:%M:%S");
    
    std::ostringstream sql;
    sql << "SELECT class_label, COUNT(*) FROM defects "
        << "WHERE timestamp BETWEEN '" << start_str.str() << "' AND '" << end_str.str() << "' "
        << "GROUP BY class_label;";
    
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db_, sql.str().c_str(), -1, &stmt, nullptr);
    
    if (rc != SQLITE_OK) {
        std::cerr << "Error preparing statistics query: " << sqlite3_errmsg(db_) << std::endl;
        return stats;
    }
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const char* class_label = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        int count = sqlite3_column_int(stmt, 1);
        stats[std::string(class_label)] = count;
    }
    
    sqlite3_finalize(stmt);
    return stats;
}

std::vector<DefectRecord> DatabaseLogger::getRecentDefects(int count) {
    std::vector<DefectRecord> records;
    
    if (!initialized_) {
        return records;
    }
    
    std::ostringstream sql;
    sql << "SELECT id, timestamp, class_label, confidence, processing_time_ms, image_path "
        << "FROM defects ORDER BY timestamp DESC LIMIT " << count << ";";
    
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db_, sql.str().c_str(), -1, &stmt, nullptr);
    
    if (rc != SQLITE_OK) {
        std::cerr << "Error preparing recent defects query: " << sqlite3_errmsg(db_) << std::endl;
        return records;
    }
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        DefectRecord record;
        record.id = sqlite3_column_int(stmt, 0);
        record.timestamp = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        record.class_label = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        record.confidence = sqlite3_column_double(stmt, 3);
        record.processing_time_ms = sqlite3_column_double(stmt, 4);
        record.image_path = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));
        records.push_back(record);
    }
    
    sqlite3_finalize(stmt);
    return records;
}

bool DatabaseLogger::isReady() const {
    return initialized_ && db_ != nullptr;
}

void DatabaseLogger::close() {
    if (db_) {
        sqlite3_close(db_);
        db_ = nullptr;
    }
    initialized_ = false;
}

bool DatabaseLogger::createTables() {
    const char* create_table_sql = R"(
        CREATE TABLE IF NOT EXISTS defects (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            timestamp TEXT NOT NULL,
            class_label TEXT NOT NULL,
            confidence REAL NOT NULL,
            processing_time_ms REAL NOT NULL,
            image_path TEXT
        );
        
        CREATE INDEX IF NOT EXISTS idx_timestamp ON defects(timestamp);
        CREATE INDEX IF NOT EXISTS idx_class_label ON defects(class_label);
    )";
    
    return executeQuery(create_table_sql);
}

bool DatabaseLogger::executeQuery(const std::string& sql) {
    char* err_msg = nullptr;
    int rc = sqlite3_exec(db_, sql.c_str(), nullptr, nullptr, &err_msg);
    
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << err_msg << std::endl;
        sqlite3_free(err_msg);
        return false;
    }
    
    return true;
}

std::string DatabaseLogger::getCurrentTimestamp() const {
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    
    std::ostringstream oss;
    oss << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S");
    return oss.str();
}
