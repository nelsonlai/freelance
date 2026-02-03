#include "parser.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>

namespace text_parser {

// Token implementation
Token::Token(TokenType type, const std::string& value, size_t line, size_t column)
    : type_(type), value_(value), line_(line), column_(column) {}

std::string Token::to_string() const {
    return "Token(" + utils::token_type_to_string(type_) + ", \"" + value_ + "\", " +
           std::to_string(line_) + ", " + std::to_string(column_) + ")";
}

bool Token::is_keyword() const {
    return type_ == TokenType::KEYWORD;
}

bool Token::is_operator() const {
    return type_ == TokenType::OPERATOR;
}

bool Token::is_delimiter() const {
    return type_ == TokenType::DELIMITER;
}

bool Token::is_literal() const {
    return type_ == TokenType::NUMBER || type_ == TokenType::STRING;
}

// Exception implementations
ParserException::ParserException(const std::string& message, size_t line, size_t column)
    : std::runtime_error(message), line_(line), column_(column) {}

LexerException::LexerException(const std::string& message, size_t line, size_t column)
    : ParserException(message, line, column) {}

ParseException::ParseException(const std::string& message, size_t line, size_t column)
    : ParserException(message, line, column) {}

// ErrorHandler implementation
ErrorHandler::ErrorHandler() {}

void ErrorHandler::report_error(const ParserException& error) {
    std::string message = format_message(error.what(), error.get_line(), error.get_column(), "ERROR");
    errors_.push_back(message);
}

void ErrorHandler::report_warning(const std::string& message, size_t line, size_t column) {
    std::string formatted_message = format_message(message, line, column, "WARNING");
    warnings_.push_back(formatted_message);
}

void ErrorHandler::report_info(const std::string& message, size_t line, size_t column) {
    std::string formatted_message = format_message(message, line, column, "INFO");
    info_.push_back(formatted_message);
}

void ErrorHandler::clear() {
    errors_.clear();
    warnings_.clear();
    info_.clear();
}

void ErrorHandler::print_all() const {
    for (const auto& error : errors_) {
        std::cout << error << std::endl;
    }
    for (const auto& warning : warnings_) {
        std::cout << warning << std::endl;
    }
    for (const auto& info : info_) {
        std::cout << info << std::endl;
    }
}

std::string ErrorHandler::format_message(const std::string& message, size_t line, size_t column, const std::string& type) {
    std::ostringstream oss;
    oss << "[" << type << "]";
    if (line > 0) {
        oss << " Line " << line;
    }
    if (column > 0) {
        oss << ", Column " << column;
    }
    oss << ": " << message;
    return oss.str();
}

// Lexer implementation
const std::set<std::string> Lexer::keywords_ = {
    "if", "else", "while", "for", "do", "switch", "case", "default",
    "break", "continue", "return", "goto", "int", "float", "double",
    "char", "string", "bool", "void", "const", "static", "extern",
    "auto", "register", "volatile", "signed", "unsigned", "long",
    "short", "struct", "union", "enum", "typedef", "sizeof", "new",
    "delete", "this", "class", "public", "private", "protected",
    "virtual", "inline", "friend", "operator", "template", "namespace",
    "using", "try", "catch", "throw", "true", "false", "nullptr"
};

const std::set<char> Lexer::operators_ = {
    '+', '-', '*', '/', '%', '=', '!', '<', '>', '&', '|', '^', '~', '?', ':'
};

const std::set<char> Lexer::delimiters_ = {
    '(', ')', '[', ']', '{', '}', ';', ',', '.', ':', '\\'
};

Lexer::Lexer(const std::string& input) 
    : input_(input), position_(0), current_line_(1), current_column_(1) {}

Token Lexer::next_token() {
    skip_whitespace();
    
    if (position_ >= input_.length()) {
        return Token(TokenType::EOF_TOKEN, "", current_line_, current_column_);
    }
    
    char c = current_char();
    
    if (is_alpha(c)) {
        return read_identifier();
    } else if (is_digit(c)) {
        return read_number();
    } else if (c == '"' || c == '\'') {
        return read_string();
    } else if (is_operator(c)) {
        return read_operator();
    } else if (is_delimiter(c)) {
        return read_delimiter();
    } else if (c == '\n') {
        advance();
        return Token(TokenType::NEWLINE, "\n", current_line_, current_column_);
    } else if (c == '/' && peek_char() == '/') {
        skip_comment();
        return next_token(); // Recursive call to get next token
    } else {
        std::string unknown(1, c);
        advance();
        return Token(TokenType::UNKNOWN, unknown, current_line_, current_column_);
    }
}

Token Lexer::peek_token() {
    size_t saved_position = position_;
    size_t saved_line = current_line_;
    size_t saved_column = current_column_;
    
    Token token = next_token();
    
    position_ = saved_position;
    current_line_ = saved_line;
    current_column_ = saved_column;
    
    return token;
}

bool Lexer::has_more_tokens() const {
    return position_ < input_.length();
}

void Lexer::reset() {
    position_ = 0;
    current_line_ = 1;
    current_column_ = 1;
}

void Lexer::skip_whitespace() {
    while (position_ < input_.length() && is_whitespace(current_char())) {
        advance();
    }
}

void Lexer::skip_comment() {
    while (position_ < input_.length() && current_char() != '\n') {
        advance();
    }
}

Token Lexer::read_identifier() {
    std::string value;
    size_t start_line = current_line_;
    size_t start_column = current_column_;
    
    while (position_ < input_.length() && is_alphanumeric(current_char())) {
        value += current_char();
        advance();
    }
    
    TokenType type = is_keyword(value) ? TokenType::KEYWORD : TokenType::IDENTIFIER;
    return Token(type, value, start_line, start_column);
}

Token Lexer::read_number() {
    std::string value;
    size_t start_line = current_line_;
    size_t start_column = current_column_;
    
    while (position_ < input_.length() && (is_digit(current_char()) || current_char() == '.')) {
        value += current_char();
        advance();
    }
    
    return Token(TokenType::NUMBER, value, start_line, start_column);
}

Token Lexer::read_string() {
    std::string value;
    size_t start_line = current_line_;
    size_t start_column = current_column_;
    
    char quote = current_char();
    value += quote;
    advance();
    
    while (position_ < input_.length() && current_char() != quote) {
        value += current_char();
        advance();
    }
    
    if (position_ < input_.length()) {
        value += current_char();
        advance();
    }
    
    return Token(TokenType::STRING, value, start_line, start_column);
}

Token Lexer::read_operator() {
    std::string value;
    size_t start_line = current_line_;
    size_t start_column = current_column_;
    
    value += current_char();
    advance();
    
    // Check for compound operators
    if (position_ < input_.length() && is_operator(current_char())) {
        char next_char = current_char();
        std::string compound = value + next_char;
        
        // Check for common compound operators
        if (compound == "==" || compound == "!=" || compound == "<=" || 
            compound == ">=" || compound == "++" || compound == "--" ||
            compound == "+=" || compound == "-=" || compound == "*=" ||
            compound == "/=" || compound == "%=" || compound == "&&" ||
            compound == "||" || compound == "<<" || compound == ">>") {
            value = compound;
            advance();
        }
    }
    
    return Token(TokenType::OPERATOR, value, start_line, start_column);
}

Token Lexer::read_delimiter() {
    std::string value(1, current_char());
    size_t start_line = current_line_;
    size_t start_column = current_column_;
    
    advance();
    
    return Token(TokenType::DELIMITER, value, start_line, start_column);
}

bool Lexer::is_whitespace(char c) const {
    return c == ' ' || c == '\t' || c == '\r';
}

bool Lexer::is_alpha(char c) const {
    return std::isalpha(c) || c == '_';
}

bool Lexer::is_digit(char c) const {
    return std::isdigit(c);
}

bool Lexer::is_alphanumeric(char c) const {
    return is_alpha(c) || is_digit(c);
}

bool Lexer::is_operator(char c) const {
    return operators_.find(c) != operators_.end();
}

bool Lexer::is_delimiter(char c) const {
    return delimiters_.find(c) != delimiters_.end();
}

bool Lexer::is_keyword(const std::string& word) const {
    return keywords_.find(word) != keywords_.end();
}

void Lexer::advance() {
    if (position_ < input_.length()) {
        if (current_char() == '\n') {
            current_line_++;
            current_column_ = 1;
        } else {
            current_column_++;
        }
        position_++;
    }
}

char Lexer::current_char() const {
    return position_ < input_.length() ? input_[position_] : '\0';
}

char Lexer::peek_char() const {
    return position_ + 1 < input_.length() ? input_[position_ + 1] : '\0';
}

// GrammarRule implementation
GrammarRule::GrammarRule(const std::string& name, const std::vector<std::string>& production,
                         std::function<void(const std::vector<Token>&)> action)
    : name(name), production(production), action(action) {}

// Parser implementation
Parser::Parser(std::shared_ptr<Lexer> lexer) 
    : lexer_(lexer), parsing_(false), current_token_index_(0) {}

void Parser::parse() {
    parsing_ = true;
    current_token_index_ = 0;
    
    try {
        while (!is_at_end()) {
            parse_statement();
        }
    } catch (const ParseException& e) {
        if (error_handler_) {
            error_handler_->report_error(e);
        }
        parsing_ = false;
        throw;
    }
    
    parsing_ = false;
}

void Parser::add_rule(const GrammarRule& rule) {
    rules_.push_back(rule);
}

void Parser::parse_statement() {
    // Simple statement parsing - can be extended
    if (peek(TokenType::IDENTIFIER)) {
        parse_expression();
    } else if (peek(TokenType::KEYWORD)) {
        const Token& token = current_token();
        if (token.get_value() == "if") {
            // Parse if statement
            consume();
            consume(TokenType::DELIMITER); // '('
            parse_expression();
            consume(TokenType::DELIMITER); // ')'
            parse_statement();
        }
    }
}

void Parser::parse_expression() {
    parse_term();
    
    while (peek(TokenType::OPERATOR)) {
        consume();
        parse_term();
    }
}

void Parser::parse_term() {
    parse_factor();
    
    while (peek(TokenType::OPERATOR)) {
        const Token& op = current_token();
        if (op.get_value() == "*" || op.get_value() == "/" || op.get_value() == "%") {
            consume();
            parse_factor();
        } else {
            break;
        }
    }
}

void Parser::parse_factor() {
    if (peek(TokenType::NUMBER) || peek(TokenType::STRING) || peek(TokenType::IDENTIFIER)) {
        consume();
    } else if (peek(TokenType::DELIMITER) && current_token().get_value() == "(") {
        consume();
        parse_expression();
        consume(TokenType::DELIMITER); // ')'
    } else {
        error("Expected number, string, identifier, or '('");
    }
}

bool Parser::match(TokenType type) {
    return peek(type);
}

bool Parser::match(const std::string& value) {
    return peek(value);
}

bool Parser::peek(TokenType type) const {
    return !is_at_end() && current_token().get_type() == type;
}

bool Parser::peek(const std::string& value) const {
    return !is_at_end() && current_token().get_value() == value;
}

Token Parser::consume() {
    if (is_at_end()) {
        error("Unexpected end of input");
    }
    
    Token token = current_token();
    current_token_index_++;
    return token;
}

Token Parser::consume(TokenType type) {
    if (!match(type)) {
        error("Expected " + utils::token_type_to_string(type));
    }
    return consume();
}

Token Parser::consume(const std::string& value) {
    if (!match(value)) {
        error("Expected '" + value + "'");
    }
    return consume();
}

void Parser::error(const std::string& message) {
    const Token& token = current_token();
    throw ParseException(message, token.get_line(), token.get_column());
}

void Parser::synchronize() {
    consume();
    
    while (!is_at_end()) {
        if (current_token().get_type() == TokenType::DELIMITER && 
            current_token().get_value() == ";") {
            return;
        }
        
        if (current_token().get_type() == TokenType::KEYWORD) {
            return;
        }
        
        consume();
    }
}

bool Parser::is_at_end() const {
    return current_token_index_ >= tokens_.size() || 
           tokens_[current_token_index_].get_type() == TokenType::EOF_TOKEN;
}

const Token& Parser::current_token() const {
    return tokens_[current_token_index_];
}

const Token& Parser::peek_token() const {
    if (current_token_index_ + 1 < tokens_.size()) {
        return tokens_[current_token_index_ + 1];
    }
    return tokens_.back(); // EOF token
}

// TextParser implementation
TextParser::TextParser() 
    : error_handler_(std::make_shared<ErrorHandler>()),
      case_sensitive_(true), skip_comments_(true), skip_whitespace_(true) {
    setup_parser();
}

void TextParser::parse_string(const std::string& input) {
    clear();
    tokenize_input(input);
    parse_tokens();
}

void TextParser::parse_file(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw ParserException("Cannot open file: " + filename);
    }
    
    std::ostringstream buffer;
    buffer << file.rdbuf();
    file.close();
    
    parse_string(buffer.str());
}

void TextParser::setup_parser() {
    lexer_ = std::make_shared<Lexer>("");
    parser_ = std::make_shared<Parser>(lexer_);
    
    lexer_->set_error_handler(error_handler_);
    parser_->set_error_handler(error_handler_);
}

void TextParser::tokenize_input(const std::string& input) {
    lexer_ = std::make_shared<Lexer>(input);
    lexer_->set_error_handler(error_handler_);
    
    tokens_.clear();
    
    try {
        while (lexer_->has_more_tokens()) {
            Token token = lexer_->next_token();
            
            if (token.get_type() == TokenType::EOF_TOKEN) {
                break;
            }
            
            if (skip_whitespace_ && token.get_type() == TokenType::WHITESPACE) {
                continue;
            }
            
            if (skip_comments_ && token.get_type() == TokenType::COMMENT) {
                continue;
            }
            
            tokens_.push_back(token);
        }
    } catch (const LexerException& e) {
        error_handler_->report_error(e);
        throw;
    }
    
    // Add EOF token
    tokens_.push_back(Token(TokenType::EOF_TOKEN, "", 0, 0));
}

void TextParser::parse_tokens() {
    parser_->parse();
}

void TextParser::print_tokens() const {
    std::cout << "Tokens:" << std::endl;
    for (const auto& token : tokens_) {
        if (token.get_type() != TokenType::EOF_TOKEN) {
            std::cout << "  " << token.to_string() << std::endl;
        }
    }
}

void TextParser::print_errors() const {
    error_handler_->print_all();
}

void TextParser::print_warnings() const {
    for (const auto& warning : error_handler_->get_warnings()) {
        std::cout << warning << std::endl;
    }
}

void TextParser::print_all() const {
    print_tokens();
    print_errors();
}

void TextParser::clear() {
    tokens_.clear();
    error_handler_->clear();
}

// Utility functions
namespace utils {
    std::string token_type_to_string(TokenType type) {
        switch (type) {
            case TokenType::IDENTIFIER: return "IDENTIFIER";
            case TokenType::NUMBER: return "NUMBER";
            case TokenType::STRING: return "STRING";
            case TokenType::OPERATOR: return "OPERATOR";
            case TokenType::DELIMITER: return "DELIMITER";
            case TokenType::KEYWORD: return "KEYWORD";
            case TokenType::WHITESPACE: return "WHITESPACE";
            case TokenType::NEWLINE: return "NEWLINE";
            case TokenType::COMMENT: return "COMMENT";
            case TokenType::EOF_TOKEN: return "EOF";
            case TokenType::UNKNOWN: return "UNKNOWN";
            default: return "UNKNOWN";
        }
    }
    
    bool is_whitespace(char c) {
        return c == ' ' || c == '\t' || c == '\r' || c == '\n';
    }
    
    bool is_alpha(char c) {
        return std::isalpha(c) || c == '_';
    }
    
    bool is_digit(char c) {
        return std::isdigit(c);
    }
    
    bool is_alphanumeric(char c) {
        return is_alpha(c) || is_digit(c);
    }
    
    std::string trim(const std::string& str) {
        size_t first = str.find_first_not_of(' ');
        if (first == std::string::npos) {
            return "";
        }
        size_t last = str.find_last_not_of(' ');
        return str.substr(first, (last - first + 1));
    }
    
    std::vector<std::string> split(const std::string& str, char delimiter) {
        std::vector<std::string> result;
        std::istringstream iss(str);
        std::string token;
        
        while (std::getline(iss, token, delimiter)) {
            result.push_back(token);
        }
        
        return result;
    }
    
    std::string to_lower(const std::string& str) {
        std::string result = str;
        std::transform(result.begin(), result.end(), result.begin(), ::tolower);
        return result;
    }
    
    std::string to_upper(const std::string& str) {
        std::string result = str;
        std::transform(result.begin(), result.end(), result.begin(), ::toupper);
        return result;
    }
}

} // namespace text_parser
