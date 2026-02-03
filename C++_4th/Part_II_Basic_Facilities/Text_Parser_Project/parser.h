#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include <memory>
#include <stdexcept>
#include <functional>
#include <map>
#include <set>

namespace text_parser {

// Forward declarations
class Token;
class Lexer;
class Parser;
class ErrorHandler;
class ParserException;

// Token types
enum class TokenType {
    IDENTIFIER,
    NUMBER,
    STRING,
    OPERATOR,
    DELIMITER,
    KEYWORD,
    WHITESPACE,
    NEWLINE,
    COMMENT,
    EOF_TOKEN,
    UNKNOWN
};

// Token class
class Token {
public:
    Token(TokenType type, const std::string& value, size_t line = 0, size_t column = 0);
    
    TokenType get_type() const { return type_; }
    const std::string& get_value() const { return value_; }
    size_t get_line() const { return line_; }
    size_t get_column() const { return column_; }
    
    std::string to_string() const;
    bool is_keyword() const;
    bool is_operator() const;
    bool is_delimiter() const;
    bool is_literal() const;
    
private:
    TokenType type_;
    std::string value_;
    size_t line_;
    size_t column_;
};

// Custom exception classes
class ParserException : public std::runtime_error {
public:
    ParserException(const std::string& message, size_t line = 0, size_t column = 0);
    size_t get_line() const { return line_; }
    size_t get_column() const { return column_; }
    
private:
    size_t line_;
    size_t column_;
};

class LexerException : public ParserException {
public:
    LexerException(const std::string& message, size_t line = 0, size_t column = 0);
};

class ParseException : public ParserException {
public:
    ParseException(const std::string& message, size_t line = 0, size_t column = 0);
};

// Error handler
class ErrorHandler {
public:
    ErrorHandler();
    
    void report_error(const ParserException& error);
    void report_warning(const std::string& message, size_t line = 0, size_t column = 0);
    void report_info(const std::string& message, size_t line = 0, size_t column = 0);
    
    bool has_errors() const { return !errors_.empty(); }
    bool has_warnings() const { return !warnings_.empty(); }
    
    const std::vector<std::string>& get_errors() const { return errors_; }
    const std::vector<std::string>& get_warnings() const { return warnings_; }
    const std::vector<std::string>& get_info() const { return info_; }
    
    void clear();
    void print_all() const;
    
private:
    std::vector<std::string> errors_;
    std::vector<std::string> warnings_;
    std::vector<std::string> info_;
    
    std::string format_message(const std::string& message, size_t line, size_t column, const std::string& type);
};

// Lexer class
class Lexer {
public:
    Lexer(const std::string& input);
    
    Token next_token();
    Token peek_token();
    bool has_more_tokens() const;
    void reset();
    
    size_t get_current_line() const { return current_line_; }
    size_t get_current_column() const { return current_column_; }
    
    void set_error_handler(std::shared_ptr<ErrorHandler> handler) { error_handler_ = handler; }
    
private:
    std::string input_;
    size_t position_;
    size_t current_line_;
    size_t current_column_;
    std::shared_ptr<ErrorHandler> error_handler_;
    
    static const std::set<std::string> keywords_;
    static const std::set<char> operators_;
    static const std::set<char> delimiters_;
    
    void skip_whitespace();
    void skip_comment();
    Token read_identifier();
    Token read_number();
    Token read_string();
    Token read_operator();
    Token read_delimiter();
    
    bool is_whitespace(char c) const;
    bool is_alpha(char c) const;
    bool is_digit(char c) const;
    bool is_alphanumeric(char c) const;
    bool is_operator(char c) const;
    bool is_delimiter(char c) const;
    bool is_keyword(const std::string& word) const;
    
    void advance();
    char current_char() const;
    char peek_char() const;
};

// Grammar rule
struct GrammarRule {
    std::string name;
    std::vector<std::string> production;
    std::function<void(const std::vector<Token>&)> action;
    
    GrammarRule(const std::string& name, const std::vector<std::string>& production,
                std::function<void(const std::vector<Token>&)> action = nullptr);
};

// Parser class
class Parser {
public:
    Parser(std::shared_ptr<Lexer> lexer);
    
    void parse();
    void add_rule(const GrammarRule& rule);
    void set_error_handler(std::shared_ptr<ErrorHandler> handler) { error_handler_ = handler; }
    
    bool is_parsing() const { return parsing_; }
    const std::vector<Token>& get_tokens() const { return tokens_; }
    
private:
    std::shared_ptr<Lexer> lexer_;
    std::shared_ptr<ErrorHandler> error_handler_;
    std::vector<Token> tokens_;
    std::vector<GrammarRule> rules_;
    bool parsing_;
    size_t current_token_index_;
    
    void parse_statement();
    void parse_expression();
    void parse_term();
    void parse_factor();
    
    bool match(TokenType type);
    bool match(const std::string& value);
    bool peek(TokenType type) const;
    bool peek(const std::string& value) const;
    
    Token consume();
    Token consume(TokenType type);
    Token consume(const std::string& value);
    
    void error(const std::string& message);
    void synchronize();
    
    bool is_at_end() const;
    const Token& current_token() const;
    const Token& peek_token() const;
};

// Main parser class
class TextParser {
public:
    TextParser();
    ~TextParser() = default;
    
    // Parse methods
    void parse_string(const std::string& input);
    void parse_file(const std::string& filename);
    
    // Configuration
    void set_case_sensitive(bool sensitive) { case_sensitive_ = sensitive; }
    void set_skip_comments(bool skip) { skip_comments_ = skip; }
    void set_skip_whitespace(bool skip) { skip_whitespace_ = skip; }
    
    // Results
    bool has_errors() const { return error_handler_->has_errors(); }
    bool has_warnings() const { return error_handler_->has_warnings(); }
    
    const std::vector<Token>& get_tokens() const { return tokens_; }
    const std::vector<std::string>& get_errors() const { return error_handler_->get_errors(); }
    const std::vector<std::string>& get_warnings() const { return error_handler_->get_warnings(); }
    
    // Utility methods
    void print_tokens() const;
    void print_errors() const;
    void print_warnings() const;
    void print_all() const;
    
    void clear();
    
private:
    std::shared_ptr<ErrorHandler> error_handler_;
    std::shared_ptr<Lexer> lexer_;
    std::shared_ptr<Parser> parser_;
    std::vector<Token> tokens_;
    
    bool case_sensitive_;
    bool skip_comments_;
    bool skip_whitespace_;
    
    void setup_parser();
    void tokenize_input(const std::string& input);
    void parse_tokens();
};

// Utility functions
namespace utils {
    std::string token_type_to_string(TokenType type);
    bool is_whitespace(char c);
    bool is_alpha(char c);
    bool is_digit(char c);
    bool is_alphanumeric(char c);
    std::string trim(const std::string& str);
    std::vector<std::string> split(const std::string& str, char delimiter);
    std::string to_lower(const std::string& str);
    std::string to_upper(const std::string& str);
}

} // namespace text_parser

#endif // PARSER_H
