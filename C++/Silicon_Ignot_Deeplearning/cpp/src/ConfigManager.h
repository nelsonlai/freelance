#pragma once

#include <string>
#include <map>
#include <vector>
#include <yaml-cpp/yaml.h>

/**
 * ConfigManager class handles YAML configuration file parsing and validation
 * Provides centralized configuration management for the entire system
 */
class ConfigManager {
public:
    /**
     * Constructor
     * @param config_file Path to YAML configuration file
     */
    ConfigManager(const std::string& config_file);
    
    /**
     * Destructor
     */
    ~ConfigManager();
    
    /**
     * Load configuration from file
     * @return true if loading successful, false otherwise
     */
    bool loadConfig();
    
    /**
     * Validate configuration parameters
     * @return true if valid, false otherwise
     */
    bool validateConfig();
    
    /**
     * Get camera configuration
     * @return Map of camera parameters
     */
    std::map<std::string, int> getCameraConfig() const;
    
    /**
     * Get preprocessing configuration
     * @return Map of preprocessing parameters
     */
    std::map<std::string, double> getPreprocessingConfig() const;
    
    /**
     * Get inference configuration
     * @return Map of inference parameters
     */
    std::map<std::string, std::string> getInferenceConfig() const;
    
    /**
     * Get logging configuration
     * @return Map of logging parameters
     */
    std::map<std::string, std::string> getLoggingConfig() const;
    
    /**
     * Get specific parameter value
     * @param section Configuration section name
     * @param key Parameter key
     * @return Parameter value as string
     */
    std::string getParameter(const std::string& section, const std::string& key) const;
    
    /**
     * Get integer parameter value
     * @param section Configuration section name
     * @param key Parameter key
     * @param default_value Default value if parameter not found
     * @return Parameter value as integer
     */
    int getIntParameter(const std::string& section, const std::string& key, int default_value = 0) const;
    
    /**
     * Get double parameter value
     * @param section Configuration section name
     * @param key Parameter key
     * @param default_value Default value if parameter not found
     * @return Parameter value as double
     */
    double getDoubleParameter(const std::string& section, const std::string& key, double default_value = 0.0) const;
    
    /**
     * Get boolean parameter value
     * @param section Configuration section name
     * @param key Parameter key
     * @param default_value Default value if parameter not found
     * @return Parameter value as boolean
     */
    bool getBoolParameter(const std::string& section, const std::string& key, bool default_value = false) const;
    
    /**
     * Check if configuration is loaded
     * @return true if loaded, false otherwise
     */
    bool isLoaded() const;
    
    /**
     * Get configuration file path
     * @return Configuration file path
     */
    std::string getConfigFilePath() const;
    
    /**
     * Print configuration summary
     */
    void printConfigSummary() const;

private:
    std::string config_file_path_;
    YAML::Node config_;
    bool loaded_;
    
    /**
     * Validate camera configuration
     * @return true if valid, false otherwise
     */
    bool validateCameraConfig() const;
    
    /**
     * Validate preprocessing configuration
     * @return true if valid, false otherwise
     */
    bool validatePreprocessingConfig() const;
    
    /**
     * Validate inference configuration
     * @return true if valid, false otherwise
     */
    bool validateInferenceConfig() const;
    
    /**
     * Validate logging configuration
     * @return true if valid, false otherwise
     */
    bool validateLoggingConfig() const;
    
    /**
     * Check if parameter exists
     * @param section Configuration section name
     * @param key Parameter key
     * @return true if exists, false otherwise
     */
    bool parameterExists(const std::string& section, const std::string& key) const;
};
