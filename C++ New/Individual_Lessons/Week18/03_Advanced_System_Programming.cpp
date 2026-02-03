/*
 * Lesson 18.3: Advanced System Programming
 * 
 * This file demonstrates advanced system programming techniques including
 * process management, inter-process communication, signal handling,
 * file system operations, and network programming.
 */

#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include <unordered_map>
#include <functional>
#include <string>
#include <sstream>
#include <chrono>
#include <thread>
#include <mutex>
#include <atomic>
#include <queue>
#include <future>
#include <condition_variable>
#include <random>
#include <algorithm>
#include <exception>
#include <stdexcept>
#include <cassert>
#include <limits>
#include <array>
#include <tuple>
#include <type_traits>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/select.h>
#include <poll.h>
#include <sys/epoll.h>

// Example 1: Process Management
namespace ProcessManagement {
    
    // Process wrapper class
    class Process {
    private:
        pid_t pid_;
        bool running_;
        int exit_status_;
        
    public:
        Process() : pid_(-1), running_(false), exit_status_(0) {}
        
        // Start a new process
        bool start(const std::string& command, const std::vector<std::string>& args = {}) {
            pid_ = fork();
            
            if (pid_ == 0) {
                // Child process
                std::vector<char*> argv;
                argv.push_back(const_cast<char*>(command.c_str()));
                
                for (const auto& arg : args) {
                    argv.push_back(const_cast<char*>(arg.c_str()));
                }
                argv.push_back(nullptr);
                
                execvp(command.c_str(), argv.data());
                exit(1);  // Should not reach here
            } else if (pid_ > 0) {
                // Parent process
                running_ = true;
                return true;
            } else {
                // Fork failed
                return false;
            }
        }
        
        // Wait for process to complete
        int wait() {
            if (pid_ <= 0 || !running_) {
                return -1;
            }
            
            int status;
            pid_t result = waitpid(pid_, &status, 0);
            
            if (result == pid_) {
                running_ = false;
                exit_status_ = WEXITSTATUS(status);
                return exit_status_;
            }
            
            return -1;
        }
        
        // Check if process is running
        bool is_running() const {
            if (pid_ <= 0 || !running_) {
                return false;
            }
            
            int status;
            pid_t result = waitpid(pid_, &status, WNOHANG);
            
            if (result == 0) {
                return true;  // Still running
            } else if (result == pid_) {
                running_ = false;
                exit_status_ = WEXITSTATUS(status);
                return false;
            }
            
            return false;
        }
        
        // Send signal to process
        bool send_signal(int signal) {
            if (pid_ <= 0) {
                return false;
            }
            
            return kill(pid_, signal) == 0;
        }
        
        // Terminate process
        bool terminate() {
            if (send_signal(SIGTERM)) {
                // Wait a bit for graceful termination
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                
                if (is_running()) {
                    // Force kill if still running
                    return send_signal(SIGKILL);
                }
                return true;
            }
            return false;
        }
        
        pid_t get_pid() const { return pid_; }
        int get_exit_status() const { return exit_status_; }
    };
    
    // Process manager for multiple processes
    class ProcessManager {
    private:
        std::vector<std::unique_ptr<Process>> processes_;
        std::mutex mutex_;
        
    public:
        ProcessManager() = default;
        
        ~ProcessManager() {
            cleanup();
        }
        
        // Start a new process
        Process* start_process(const std::string& command, const std::vector<std::string>& args = {}) {
            std::lock_guard<std::mutex> lock(mutex_);
            
            auto process = std::make_unique<Process>();
            if (process->start(command, args)) {
                Process* ptr = process.get();
                processes_.push_back(std::move(process));
                return ptr;
            }
            
            return nullptr;
        }
        
        // Wait for all processes to complete
        void wait_all() {
            std::lock_guard<std::mutex> lock(mutex_);
            
            for (auto& process : processes_) {
                if (process && process->is_running()) {
                    process->wait();
                }
            }
        }
        
        // Terminate all processes
        void terminate_all() {
            std::lock_guard<std::mutex> lock(mutex_);
            
            for (auto& process : processes_) {
                if (process && process->is_running()) {
                    process->terminate();
                }
            }
        }
        
        // Get running processes count
        size_t get_running_count() const {
            std::lock_guard<std::mutex> lock(mutex_);
            
            size_t count = 0;
            for (const auto& process : processes_) {
                if (process && process->is_running()) {
                    ++count;
                }
            }
            return count;
        }
        
        // Cleanup completed processes
        void cleanup() {
            std::lock_guard<std::mutex> lock(mutex_);
            
            processes_.erase(
                std::remove_if(processes_.begin(), processes_.end(),
                    [](const std::unique_ptr<Process>& process) {
                        return !process || !process->is_running();
                    }),
                processes_.end()
            );
        }
    };
    
    void demonstrateProcessManagement() {
        std::cout << "=== Process Management ===" << std::endl;
        
        ProcessManager manager;
        
        // Start some processes
        auto* process1 = manager.start_process("sleep", {"5"});
        auto* process2 = manager.start_process("echo", {"Hello, World!"});
        
        if (process1 && process2) {
            std::cout << "Started processes with PIDs: " << process1->get_pid() << ", " << process2->get_pid() << std::endl;
            
            // Wait for echo to complete
            int status = process2->wait();
            std::cout << "Echo process exited with status: " << status << std::endl;
            
            // Check if sleep is still running
            if (process1->is_running()) {
                std::cout << "Sleep process is still running" << std::endl;
                
                // Terminate it
                if (process1->terminate()) {
                    std::cout << "Terminated sleep process" << std::endl;
                }
            }
            
            std::cout << "Running processes: " << manager.get_running_count() << std::endl;
        }
        
        manager.cleanup();
    }
}

// Example 2: Inter-Process Communication
namespace InterProcessCommunication {
    
    // Named pipe (FIFO) for IPC
    class NamedPipe {
    private:
        std::string pipe_name_;
        int fd_;
        bool is_reader_;
        
    public:
        NamedPipe(const std::string& name, bool is_reader = true) 
            : pipe_name_(name), fd_(-1), is_reader_(is_reader) {
            
            // Create named pipe
            if (mkfifo(pipe_name_.c_str(), 0666) == -1 && errno != EEXIST) {
                throw std::runtime_error("Failed to create named pipe: " + pipe_name_);
            }
            
            // Open pipe
            int flags = is_reader_ ? O_RDONLY : O_WRONLY;
            fd_ = open(pipe_name_.c_str(), flags);
            if (fd_ == -1) {
                throw std::runtime_error("Failed to open named pipe: " + pipe_name_);
            }
        }
        
        ~NamedPipe() {
            if (fd_ != -1) {
                close(fd_);
            }
            // Remove named pipe
            unlink(pipe_name_.c_str());
        }
        
        // Non-copyable
        NamedPipe(const NamedPipe&) = delete;
        NamedPipe& operator=(const NamedPipe&) = delete;
        
        // Movable
        NamedPipe(NamedPipe&& other) noexcept 
            : pipe_name_(std::move(other.pipe_name_)), fd_(other.fd_), is_reader_(other.is_reader_) {
            other.fd_ = -1;
        }
        
        NamedPipe& operator=(NamedPipe&& other) noexcept {
            if (this != &other) {
                if (fd_ != -1) {
                    close(fd_);
                }
                pipe_name_ = std::move(other.pipe_name_);
                fd_ = other.fd_;
                is_reader_ = other.is_reader_;
                other.fd_ = -1;
            }
            return *this;
        }
        
        // Read data
        ssize_t read(void* buffer, size_t size) {
            if (!is_reader_ || fd_ == -1) {
                return -1;
            }
            return ::read(fd_, buffer, size);
        }
        
        // Write data
        ssize_t write(const void* data, size_t size) {
            if (is_reader_ || fd_ == -1) {
                return -1;
            }
            return ::write(fd_, data, size);
        }
        
        // Read string
        std::string read_string() {
            if (!is_reader_ || fd_ == -1) {
                return "";
            }
            
            std::string result;
            char buffer[1024];
            ssize_t bytes_read;
            
            while ((bytes_read = ::read(fd_, buffer, sizeof(buffer) - 1)) > 0) {
                buffer[bytes_read] = '\0';
                result += buffer;
            }
            
            return result;
        }
        
        // Write string
        bool write_string(const std::string& str) {
            if (is_reader_ || fd_ == -1) {
                return false;
            }
            
            ssize_t bytes_written = ::write(fd_, str.c_str(), str.length());
            return bytes_written == static_cast<ssize_t>(str.length());
        }
    };
    
    // Shared memory for IPC
    class SharedMemory {
    private:
        std::string name_;
        void* memory_;
        size_t size_;
        int shm_fd_;
        bool is_creator_;
        
    public:
        SharedMemory(const std::string& name, size_t size, bool create = true) 
            : name_(name), memory_(nullptr), size_(size), shm_fd_(-1), is_creator_(create) {
            
            if (create) {
                // Create shared memory
                shm_fd_ = shm_open(name_.c_str(), O_CREAT | O_RDWR, 0666);
                if (shm_fd_ == -1) {
                    throw std::runtime_error("Failed to create shared memory: " + name_);
                }
                
                // Set size
                if (ftruncate(shm_fd_, size_) == -1) {
                    close(shm_fd_);
                    throw std::runtime_error("Failed to set shared memory size");
                }
            } else {
                // Open existing shared memory
                shm_fd_ = shm_open(name_.c_str(), O_RDWR, 0666);
                if (shm_fd_ == -1) {
                    throw std::runtime_error("Failed to open shared memory: " + name_);
                }
            }
            
            // Map shared memory
            memory_ = mmap(nullptr, size_, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd_, 0);
            if (memory_ == MAP_FAILED) {
                close(shm_fd_);
                throw std::runtime_error("Failed to map shared memory");
            }
        }
        
        ~SharedMemory() {
            if (memory_ != nullptr) {
                munmap(memory_, size_);
            }
            if (shm_fd_ != -1) {
                close(shm_fd_);
            }
            if (is_creator_) {
                shm_unlink(name_.c_str());
            }
        }
        
        // Non-copyable
        SharedMemory(const SharedMemory&) = delete;
        SharedMemory& operator=(const SharedMemory&) = delete;
        
        // Movable
        SharedMemory(SharedMemory&& other) noexcept 
            : name_(std::move(other.name_)), memory_(other.memory_), size_(other.size_), 
              shm_fd_(other.shm_fd_), is_creator_(other.is_creator_) {
            other.memory_ = nullptr;
            other.shm_fd_ = -1;
        }
        
        SharedMemory& operator=(SharedMemory&& other) noexcept {
            if (this != &other) {
                if (memory_ != nullptr) {
                    munmap(memory_, size_);
                }
                if (shm_fd_ != -1) {
                    close(shm_fd_);
                }
                if (is_creator_) {
                    shm_unlink(name_.c_str());
                }
                
                name_ = std::move(other.name_);
                memory_ = other.memory_;
                size_ = other.size_;
                shm_fd_ = other.shm_fd_;
                is_creator_ = other.is_creator_;
                
                other.memory_ = nullptr;
                other.shm_fd_ = -1;
            }
            return *this;
        }
        
        void* data() const { return memory_; }
        size_t size() const { return size_; }
        
        template<typename T>
        T* as() const {
            return static_cast<T*>(memory_);
        }
    };
    
    void demonstrateInterProcessCommunication() {
        std::cout << "\n=== Inter-Process Communication ===" << std::endl;
        
        // Test named pipe
        try {
            // Create reader pipe
            NamedPipe reader_pipe("test_pipe", true);
            
            // Create writer pipe in child process
            pid_t pid = fork();
            if (pid == 0) {
                // Child process
                NamedPipe writer_pipe("test_pipe", false);
                writer_pipe.write_string("Hello from child process!");
                exit(0);
            } else if (pid > 0) {
                // Parent process
                std::string message = reader_pipe.read_string();
                std::cout << "Received message: " << message << std::endl;
                waitpid(pid, nullptr, 0);
            }
        } catch (const std::exception& e) {
            std::cout << "Named pipe error: " << e.what() << std::endl;
        }
        
        // Test shared memory
        try {
            // Create shared memory
            SharedMemory shm("test_shm", 1024, true);
            
            // Write data to shared memory
            int* data = shm.as<int>();
            *data = 42;
            
            std::cout << "Written to shared memory: " << *data << std::endl;
            
            // Read data from shared memory
            int value = *shm.as<int>();
            std::cout << "Read from shared memory: " << value << std::endl;
            
        } catch (const std::exception& e) {
            std::cout << "Shared memory error: " << e.what() << std::endl;
        }
    }
}

// Example 3: Signal Handling
namespace SignalHandling {
    
    // Signal handler manager
    class SignalManager {
    private:
        std::map<int, std::function<void(int)>> handlers_;
        std::mutex mutex_;
        
        static SignalManager* instance_;
        
        SignalManager() = default;
        
        // Static signal handler
        static void signal_handler(int signal) {
            if (instance_) {
                instance_->handle_signal(signal);
            }
        }
        
        void handle_signal(int signal) {
            std::lock_guard<std::mutex> lock(mutex_);
            auto it = handlers_.find(signal);
            if (it != handlers_.end()) {
                it->second(signal);
            }
        }
        
    public:
        static SignalManager& get_instance() {
            if (!instance_) {
                instance_ = new SignalManager();
            }
            return *instance_;
        }
        
        // Register signal handler
        bool register_handler(int signal, std::function<void(int)> handler) {
            std::lock_guard<std::mutex> lock(mutex_);
            
            handlers_[signal] = handler;
            
            struct sigaction sa;
            sa.sa_handler = signal_handler;
            sigemptyset(&sa.sa_mask);
            sa.sa_flags = 0;
            
            return sigaction(signal, &sa, nullptr) == 0;
        }
        
        // Unregister signal handler
        bool unregister_handler(int signal) {
            std::lock_guard<std::mutex> lock(mutex_);
            
            auto it = handlers_.find(signal);
            if (it != handlers_.end()) {
                handlers_.erase(it);
                
                // Restore default handler
                signal(signal, SIG_DFL);
                return true;
            }
            
            return false;
        }
        
        // Send signal to current process
        bool send_signal(int signal) {
            return kill(getpid(), signal) == 0;
        }
        
        // Send signal to specific process
        bool send_signal(pid_t pid, int signal) {
            return kill(pid, signal) == 0;
        }
        
        // Block signals
        bool block_signals(const std::vector<int>& signals) {
            sigset_t mask;
            sigemptyset(&mask);
            
            for (int signal : signals) {
                sigaddset(&mask, signal);
            }
            
            return sigprocmask(SIG_BLOCK, &mask, nullptr) == 0;
        }
        
        // Unblock signals
        bool unblock_signals(const std::vector<int>& signals) {
            sigset_t mask;
            sigemptyset(&mask);
            
            for (int signal : signals) {
                sigaddset(&mask, signal);
            }
            
            return sigprocmask(SIG_UNBLOCK, &mask, nullptr) == 0;
        }
    };
    
    SignalManager* SignalManager::instance_ = nullptr;
    
    // RAII wrapper for signal blocking
    class SignalBlocker {
    private:
        std::vector<int> signals_;
        bool blocked_;
        
    public:
        SignalBlocker(const std::vector<int>& signals) : signals_(signals), blocked_(false) {
            if (SignalManager::get_instance().block_signals(signals_)) {
                blocked_ = true;
            }
        }
        
        ~SignalBlocker() {
            if (blocked_) {
                SignalManager::get_instance().unblock_signals(signals_);
            }
        }
        
        // Non-copyable
        SignalBlocker(const SignalBlocker&) = delete;
        SignalBlocker& operator=(const SignalBlocker&) = delete;
        
        // Non-movable
        SignalBlocker(SignalBlocker&&) = delete;
        SignalBlocker& operator=(SignalBlocker&&) = delete;
    };
    
    void demonstrateSignalHandling() {
        std::cout << "\n=== Signal Handling ===" << std::endl;
        
        SignalManager& manager = SignalManager::get_instance();
        
        // Register signal handlers
        manager.register_handler(SIGINT, [](int signal) {
            std::cout << "Received SIGINT (Ctrl+C)" << std::endl;
            exit(0);
        });
        
        manager.register_handler(SIGTERM, [](int signal) {
            std::cout << "Received SIGTERM" << std::endl;
            exit(0);
        });
        
        manager.register_handler(SIGUSR1, [](int signal) {
            std::cout << "Received SIGUSR1" << std::endl;
        });
        
        std::cout << "Signal handlers registered. Send SIGUSR1 to test." << std::endl;
        std::cout << "Press Ctrl+C to exit." << std::endl;
        
        // Block signals temporarily
        {
            SignalBlocker blocker({SIGUSR1});
            std::cout << "Signals blocked for 2 seconds..." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
        
        std::cout << "Signals unblocked. Waiting for signals..." << std::endl;
        
        // Wait for signals
        for (int i = 0; i < 5; ++i) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << "Waiting... (" << (i + 1) << "/5)" << std::endl;
        }
        
        std::cout << "Signal handling demonstration completed." << std::endl;
    }
}

// Example 4: File System Operations
namespace FileSystemOperations {
    
    // File system utilities
    class FileSystem {
    public:
        // Check if file exists
        static bool file_exists(const std::string& path) {
            struct stat st;
            return stat(path.c_str(), &st) == 0;
        }
        
        // Check if directory exists
        static bool directory_exists(const std::string& path) {
            struct stat st;
            return stat(path.c_str(), &st) == 0 && S_ISDIR(st.st_mode);
        }
        
        // Create directory
        static bool create_directory(const std::string& path, mode_t mode = 0755) {
            return mkdir(path.c_str(), mode) == 0;
        }
        
        // Remove file
        static bool remove_file(const std::string& path) {
            return unlink(path.c_str()) == 0;
        }
        
        // Remove directory
        static bool remove_directory(const std::string& path) {
            return rmdir(path.c_str()) == 0;
        }
        
        // Get file size
        static ssize_t get_file_size(const std::string& path) {
            struct stat st;
            if (stat(path.c_str(), &st) == 0) {
                return st.st_size;
            }
            return -1;
        }
        
        // Get file permissions
        static mode_t get_file_permissions(const std::string& path) {
            struct stat st;
            if (stat(path.c_str(), &st) == 0) {
                return st.st_mode & 0777;
            }
            return 0;
        }
        
        // Set file permissions
        static bool set_file_permissions(const std::string& path, mode_t mode) {
            return chmod(path.c_str(), mode) == 0;
        }
        
        // List directory contents
        static std::vector<std::string> list_directory(const std::string& path) {
            std::vector<std::string> contents;
            
            DIR* dir = opendir(path.c_str());
            if (!dir) {
                return contents;
            }
            
            struct dirent* entry;
            while ((entry = readdir(dir)) != nullptr) {
                if (entry->d_name[0] != '.') {  // Skip hidden files
                    contents.push_back(entry->d_name);
                }
            }
            
            closedir(dir);
            return contents;
        }
        
        // Copy file
        static bool copy_file(const std::string& src, const std::string& dst) {
            int src_fd = open(src.c_str(), O_RDONLY);
            if (src_fd == -1) {
                return false;
            }
            
            int dst_fd = open(dst.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (dst_fd == -1) {
                close(src_fd);
                return false;
            }
            
            char buffer[4096];
            ssize_t bytes_read, bytes_written;
            
            while ((bytes_read = read(src_fd, buffer, sizeof(buffer))) > 0) {
                bytes_written = write(dst_fd, buffer, bytes_read);
                if (bytes_written != bytes_read) {
                    close(src_fd);
                    close(dst_fd);
                    return false;
                }
            }
            
            close(src_fd);
            close(dst_fd);
            return true;
        }
        
        // Move file
        static bool move_file(const std::string& src, const std::string& dst) {
            if (rename(src.c_str(), dst.c_str()) == 0) {
                return true;
            }
            
            // Fallback to copy and delete
            if (copy_file(src, dst)) {
                return remove_file(src);
            }
            
            return false;
        }
    };
    
    // File watcher
    class FileWatcher {
    private:
        std::string path_;
        std::function<void(const std::string&)> callback_;
        std::atomic<bool> running_;
        std::thread watcher_thread_;
        
    public:
        FileWatcher(const std::string& path, std::function<void(const std::string&)> callback) 
            : path_(path), callback_(callback), running_(false) {}
        
        ~FileWatcher() {
            stop();
        }
        
        // Non-copyable
        FileWatcher(const FileWatcher&) = delete;
        FileWatcher& operator=(const FileWatcher&) = delete;
        
        // Start watching
        void start() {
            if (running_) {
                return;
            }
            
            running_ = true;
            watcher_thread_ = std::thread(&FileWatcher::watch_loop, this);
        }
        
        // Stop watching
        void stop() {
            if (running_) {
                running_ = false;
                if (watcher_thread_.joinable()) {
                    watcher_thread_.join();
                }
            }
        }
        
    private:
        void watch_loop() {
            int fd = open(path_.c_str(), O_RDONLY);
            if (fd == -1) {
                return;
            }
            
            struct stat st;
            if (fstat(fd, &st) == -1) {
                close(fd);
                return;
            }
            
            time_t last_modified = st.st_mtime;
            
            while (running_) {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                
                if (fstat(fd, &st) == 0) {
                    if (st.st_mtime != last_modified) {
                        last_modified = st.st_mtime;
                        if (callback_) {
                            callback_(path_);
                        }
                    }
                }
            }
            
            close(fd);
        }
    };
    
    void demonstrateFileSystemOperations() {
        std::cout << "\n=== File System Operations ===" << std::endl;
        
        const std::string test_dir = "test_directory";
        const std::string test_file = "test_directory/test_file.txt";
        const std::string test_copy = "test_directory/test_file_copy.txt";
        
        try {
            // Create test directory
            if (FileSystem::create_directory(test_dir)) {
                std::cout << "Created directory: " << test_dir << std::endl;
            }
            
            // Create test file
            int fd = open(test_file.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd != -1) {
                write(fd, "Hello, World!", 13);
                close(fd);
                std::cout << "Created file: " << test_file << std::endl;
            }
            
            // Check file existence
            if (FileSystem::file_exists(test_file)) {
                std::cout << "File exists: " << test_file << std::endl;
            }
            
            // Get file size
            ssize_t size = FileSystem::get_file_size(test_file);
            std::cout << "File size: " << size << " bytes" << std::endl;
            
            // Get file permissions
            mode_t perms = FileSystem::get_file_permissions(test_file);
            std::cout << "File permissions: " << std::oct << perms << std::endl;
            
            // Copy file
            if (FileSystem::copy_file(test_file, test_copy)) {
                std::cout << "Copied file to: " << test_copy << std::endl;
            }
            
            // List directory contents
            auto contents = FileSystem::list_directory(test_dir);
            std::cout << "Directory contents:" << std::endl;
            for (const auto& item : contents) {
                std::cout << "  " << item << std::endl;
            }
            
            // Test file watcher
            FileWatcher watcher(test_file, [](const std::string& path) {
                std::cout << "File modified: " << path << std::endl;
            });
            
            watcher.start();
            
            // Modify file
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            fd = open(test_file.c_str(), O_WRONLY | O_APPEND);
            if (fd != -1) {
                write(fd, " (modified)", 11);
                close(fd);
            }
            
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            watcher.stop();
            
            // Cleanup
            FileSystem::remove_file(test_copy);
            FileSystem::remove_file(test_file);
            FileSystem::remove_directory(test_dir);
            
            std::cout << "Cleaned up test files and directory" << std::endl;
            
        } catch (const std::exception& e) {
            std::cout << "File system error: " << e.what() << std::endl;
        }
    }
}

// Example 5: Network Programming
namespace NetworkProgramming {
    
    // TCP server
    class TCPServer {
    private:
        int server_fd_;
        int port_;
        std::atomic<bool> running_;
        std::thread server_thread_;
        
    public:
        TCPServer(int port) : server_fd_(-1), port_(port), running_(false) {}
        
        ~TCPServer() {
            stop();
        }
        
        // Non-copyable
        TCPServer(const TCPServer&) = delete;
        TCPServer& operator=(const TCPServer&) = delete;
        
        // Start server
        bool start() {
            server_fd_ = socket(AF_INET, SOCK_STREAM, 0);
            if (server_fd_ == -1) {
                return false;
            }
            
            int opt = 1;
            if (setsockopt(server_fd_, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
                close(server_fd_);
                return false;
            }
            
            struct sockaddr_in address;
            address.sin_family = AF_INET;
            address.sin_addr.s_addr = INADDR_ANY;
            address.sin_port = htons(port_);
            
            if (bind(server_fd_, (struct sockaddr*)&address, sizeof(address)) == -1) {
                close(server_fd_);
                return false;
            }
            
            if (listen(server_fd_, 5) == -1) {
                close(server_fd_);
                return false;
            }
            
            running_ = true;
            server_thread_ = std::thread(&TCPServer::server_loop, this);
            
            return true;
        }
        
        // Stop server
        void stop() {
            if (running_) {
                running_ = false;
                if (server_fd_ != -1) {
                    close(server_fd_);
                }
                if (server_thread_.joinable()) {
                    server_thread_.join();
                }
            }
        }
        
        // Check if server is running
        bool is_running() const {
            return running_;
        }
        
    private:
        void server_loop() {
            while (running_) {
                struct sockaddr_in client_address;
                socklen_t client_len = sizeof(client_address);
                
                int client_fd = accept(server_fd_, (struct sockaddr*)&client_address, &client_len);
                if (client_fd == -1) {
                    if (running_) {
                        continue;
                    }
                    break;
                }
                
                // Handle client in separate thread
                std::thread client_thread(&TCPServer::handle_client, this, client_fd);
                client_thread.detach();
            }
        }
        
        void handle_client(int client_fd) {
            char buffer[1024];
            ssize_t bytes_read;
            
            while ((bytes_read = read(client_fd, buffer, sizeof(buffer) - 1)) > 0) {
                buffer[bytes_read] = '\0';
                
                // Echo back the message
                std::string response = "Echo: " + std::string(buffer);
                write(client_fd, response.c_str(), response.length());
            }
            
            close(client_fd);
        }
    };
    
    // TCP client
    class TCPClient {
    private:
        int client_fd_;
        std::string host_;
        int port_;
        
    public:
        TCPClient(const std::string& host, int port) 
            : client_fd_(-1), host_(host), port_(port) {}
        
        ~TCPClient() {
            disconnect();
        }
        
        // Non-copyable
        TCPClient(const TCPClient&) = delete;
        TCPClient& operator=(const TCPClient&) = delete;
        
        // Connect to server
        bool connect() {
            client_fd_ = socket(AF_INET, SOCK_STREAM, 0);
            if (client_fd_ == -1) {
                return false;
            }
            
            struct sockaddr_in server_address;
            server_address.sin_family = AF_INET;
            server_address.sin_port = htons(port_);
            
            if (inet_pton(AF_INET, host_.c_str(), &server_address.sin_addr) <= 0) {
                close(client_fd_);
                return false;
            }
            
            if (::connect(client_fd_, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
                close(client_fd_);
                return false;
            }
            
            return true;
        }
        
        // Disconnect from server
        void disconnect() {
            if (client_fd_ != -1) {
                close(client_fd_);
                client_fd_ = -1;
            }
        }
        
        // Send data
        bool send(const std::string& data) {
            if (client_fd_ == -1) {
                return false;
            }
            
            ssize_t bytes_sent = write(client_fd_, data.c_str(), data.length());
            return bytes_sent == static_cast<ssize_t>(data.length());
        }
        
        // Receive data
        std::string receive() {
            if (client_fd_ == -1) {
                return "";
            }
            
            char buffer[1024];
            ssize_t bytes_read = read(client_fd_, buffer, sizeof(buffer) - 1);
            
            if (bytes_read > 0) {
                buffer[bytes_read] = '\0';
                return std::string(buffer);
            }
            
            return "";
        }
        
        // Check if connected
        bool is_connected() const {
            return client_fd_ != -1;
        }
    };
    
    void demonstrateNetworkProgramming() {
        std::cout << "\n=== Network Programming ===" << std::endl;
        
        const int port = 8080;
        
        // Start server
        TCPServer server(port);
        if (server.start()) {
            std::cout << "TCP server started on port " << port << std::endl;
            
            // Wait a bit for server to start
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            
            // Connect client
            TCPClient client("127.0.0.1", port);
            if (client.connect()) {
                std::cout << "TCP client connected to server" << std::endl;
                
                // Send some messages
                std::vector<std::string> messages = {
                    "Hello, Server!",
                    "This is a test message.",
                    "Goodbye!"
                };
                
                for (const auto& message : messages) {
                    if (client.send(message)) {
                        std::cout << "Sent: " << message << std::endl;
                        
                        std::string response = client.receive();
                        if (!response.empty()) {
                            std::cout << "Received: " << response << std::endl;
                        }
                    }
                    
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                }
                
                client.disconnect();
                std::cout << "TCP client disconnected" << std::endl;
            }
            
            server.stop();
            std::cout << "TCP server stopped" << std::endl;
        }
    }
}

int main() {
    std::cout << "=== Advanced System Programming Demonstration ===" << std::endl;
    std::cout << "This program demonstrates advanced system programming techniques including\n"
              << "process management, inter-process communication, signal handling,\n"
              << "file system operations, and network programming.\n" << std::endl;
    
    // Demonstrate various system programming techniques
    ProcessManagement::demonstrateProcessManagement();
    InterProcessCommunication::demonstrateInterProcessCommunication();
    SignalHandling::demonstrateSignalHandling();
    FileSystemOperations::demonstrateFileSystemOperations();
    NetworkProgramming::demonstrateNetworkProgramming();
    
    std::cout << "\n=== Key Takeaways ===" << std::endl;
    std::cout << "1. Process management enables creating and controlling child processes" << std::endl;
    std::cout << "2. Inter-process communication allows processes to share data and synchronize" << std::endl;
    std::cout << "3. Signal handling provides a mechanism for process communication and control" << std::endl;
    std::cout << "4. File system operations enable programmatic file and directory management" << std::endl;
    std::cout << "5. Network programming enables communication between processes on different machines" << std::endl;
    std::cout << "6. System programming requires understanding of operating system concepts" << std::endl;
    std::cout << "7. Proper error handling and resource management are crucial for system programs" << std::endl;
    std::cout << "8. System programming provides low-level control over system resources" << std::endl;
    
    std::cout << "\nProgram completed successfully!" << std::endl;
    return 0;
}

/*
 * Compilation Instructions:
 * 
 * Using GCC:
 * g++ -std=c++17 -Wall -Wextra -O2 -pthread -o advanced_system_programming 03_Advanced_System_Programming.cpp
 * 
 * Using Clang:
 * clang++ -std=c++17 -Wall -Wextra -O2 -pthread -o advanced_system_programming 03_Advanced_System_Programming.cpp
 * 
 * Using MSVC (Visual Studio):
 * cl /std:c++17 /EHsc /O2 03_Advanced_System_Programming.cpp
 * 
 * Running:
 * ./advanced_system_programming (Linux/macOS)
 * advanced_system_programming.exe (Windows)
 * 
 * Note: This lesson requires C++17 for some features.
 * System programming features require POSIX-compatible systems.
 * 
 * Advanced System Programming Notes:
 * - Process management enables creating and controlling child processes
 * - Inter-process communication allows processes to share data and synchronize
 * - Signal handling provides a mechanism for process communication and control
 * - File system operations enable programmatic file and directory management
 * - Network programming enables communication between processes on different machines
 * - System programming requires understanding of operating system concepts
 * - Proper error handling and resource management are crucial for system programs
 * - System programming provides low-level control over system resources
 */"""
