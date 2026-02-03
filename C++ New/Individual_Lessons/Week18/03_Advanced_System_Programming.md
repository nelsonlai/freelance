# Week 18, Lesson 3: Advanced System Programming

## 1. Learning Objectives

- Understand advanced system programming concepts and techniques.
- Learn process management and control operations.
- Explore inter-process communication mechanisms.
- Understand signal handling and process communication.
- Learn file system operations and management.
- Explore network programming fundamentals.
- Understand system resource management and optimization.
- Learn best practices for system-level programming.

## 2. Prerequisites

- Understanding of basic system programming concepts
- Knowledge of C++ fundamentals and threading
- Familiarity with operating system concepts
- Understanding of file I/O and network basics
- Knowledge of process and memory management

## 3. Process Management

### 3.1 Process Creation and Control

**Process Operations:**
- Creating child processes with `fork()`
- Executing programs with `exec()` family
- Waiting for process completion with `wait()`
- Sending signals to processes
- Process termination and cleanup

**Process States:**
- Running: Process is currently executing
- Ready: Process is waiting to be scheduled
- Blocked: Process is waiting for an event
- Terminated: Process has completed execution

### 3.2 Process Wrapper Class

```cpp
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
```

### 3.3 Process Manager

```cpp
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
```

## 4. Inter-Process Communication

### 4.1 IPC Mechanisms

**Types of IPC:**
- **Pipes**: Unidirectional communication between related processes
- **Named Pipes (FIFOs)**: Bidirectional communication between unrelated processes
- **Shared Memory**: Fast data sharing between processes
- **Message Queues**: Structured message passing
- **Semaphores**: Synchronization primitives
- **Sockets**: Network-based communication

### 4.2 Named Pipes (FIFOs)

```cpp
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
```

### 4.3 Shared Memory

```cpp
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
```

## 5. Signal Handling

### 5.1 Signal Concepts

**Signal Types:**
- **SIGINT**: Interrupt signal (Ctrl+C)
- **SIGTERM**: Termination signal
- **SIGKILL**: Kill signal (cannot be caught)
- **SIGUSR1/SIGUSR2**: User-defined signals
- **SIGHUP**: Hangup signal
- **SIGCHLD**: Child process terminated

**Signal Actions:**
- **SIG_DFL**: Default action
- **SIG_IGN**: Ignore signal
- **Custom handler**: User-defined function

### 5.2 Signal Manager

```cpp
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
```

### 5.3 Signal Blocking

```cpp
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
```

## 6. File System Operations

### 6.1 File System Utilities

```cpp
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
```

### 6.2 File Watcher

```cpp
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
```

## 7. Network Programming

### 7.1 TCP Server

```cpp
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
```

### 7.2 TCP Client

```cpp
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
```

## 8. Best Practices

### 8.1 System Programming Guidelines

**Process Management:**
- Always check return values from system calls
- Handle process termination properly
- Use appropriate signals for process control
- Implement proper error handling

**IPC Considerations:**
- Choose appropriate IPC mechanism for use case
- Handle synchronization issues
- Implement proper cleanup procedures
- Consider security implications

### 8.2 Error Handling

**System Call Errors:**
- Check return values from system calls
- Use errno for error information
- Implement proper error recovery
- Provide meaningful error messages

**Resource Management:**
- Use RAII for automatic cleanup
- Handle resource leaks properly
- Implement proper exception safety
- Consider resource limits

### 8.3 Performance Considerations

**System Call Overhead:**
- Minimize system call frequency
- Use appropriate buffering
- Consider asynchronous I/O
- Optimize for specific use cases

**Memory Management:**
- Use appropriate memory allocation strategies
- Consider memory-mapped files
- Implement proper caching
- Monitor memory usage

## 9. Common Pitfalls and Solutions

### 9.1 Process Management Pitfalls

**Problem**: Zombie processes
**Solution**: Use wait() or waitpid() to clean up child processes

**Problem**: Orphaned processes
**Solution**: Implement proper process hierarchy and cleanup

**Problem**: Signal handling issues
**Solution**: Use proper signal handling patterns and avoid signal-unsafe functions

### 9.2 IPC Pitfalls

**Problem**: Deadlocks in IPC
**Solution**: Implement proper locking order and timeout mechanisms

**Problem**: Data corruption in shared memory
**Solution**: Use proper synchronization primitives

**Problem**: Resource leaks
**Solution**: Implement proper cleanup procedures

### 9.3 File System Pitfalls

**Problem**: Race conditions in file operations
**Solution**: Use proper locking mechanisms

**Problem**: Permission issues
**Solution**: Check and set appropriate file permissions

**Problem**: Disk space issues
**Solution**: Implement proper error handling and monitoring

## 10. Advanced Topics

### 10.1 Asynchronous I/O

**Async I/O Benefits:**
- Non-blocking operations
- Better resource utilization
- Improved scalability
- Reduced thread overhead

**Implementation:**
- Use epoll for Linux
- Use kqueue for BSD/macOS
- Use I/O completion ports for Windows

### 10.2 System Monitoring

**Monitoring Techniques:**
- Process monitoring
- Resource usage tracking
- Performance metrics
- System health checks

### 10.3 Security Considerations

**Security Best Practices:**
- Principle of least privilege
- Input validation
- Secure communication
- Access control

## 11. Summary

Advanced system programming provides powerful tools for interacting with the operating system and managing system resources. Key takeaways include:

1. **Process management** enables creating and controlling child processes
2. **Inter-process communication** allows processes to share data and synchronize
3. **Signal handling** provides a mechanism for process communication and control
4. **File system operations** enable programmatic file and directory management
5. **Network programming** enables communication between processes on different machines
6. **System programming** requires understanding of operating system concepts
7. **Proper error handling** and resource management are crucial for system programs
8. **System programming** provides low-level control over system resources

Effective system programming requires understanding both the application requirements and the underlying system characteristics, combined with proper use of system calls and modern C++ features.

## 12. Exercises

### Exercise 1: Process Manager
Implement a process manager that can start, monitor, and control multiple child processes with proper cleanup and error handling.

### Exercise 2: IPC System
Create an IPC system using named pipes and shared memory for communication between multiple processes.

### Exercise 3: Signal Handler
Implement a signal handler system that can register, unregister, and manage multiple signal handlers with proper synchronization.

### Exercise 4: File System Monitor
Create a file system monitor that can watch multiple directories and files for changes, with proper event handling.

### Exercise 5: Network Server
Implement a network server that can handle multiple concurrent clients with proper connection management and error handling.

## 13. Further Reading

- "Advanced Programming in the UNIX Environment" by W. Richard Stevens
- "The Linux Programming Interface" by Michael Kerrisk
- "Unix Network Programming" by W. Richard Stevens
- "Systems Programming: Designing and Developing Distributed Applications" by Richard John Anthony
- "Computer Systems: A Programmer's Perspective" by Randal E. Bryant and David R. O'Hallaron
- "Operating System Concepts" by Abraham Silberschatz, Peter Baer Galvin, and Greg Gagne
- "The Design and Implementation of the 4.3BSD UNIX Operating System" by Samuel J. Leffler, Marshall Kirk McKusick, Michael J. Karels, and John S. Quarterman
