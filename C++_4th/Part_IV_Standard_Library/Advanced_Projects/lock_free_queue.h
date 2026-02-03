#ifndef LOCK_FREE_QUEUE_H
#define LOCK_FREE_QUEUE_H

#include <atomic>
#include <memory>

// Lock-free queue implementation using atomic operations
template<typename T>
class LockFreeQueue {
private:
    struct Node {
        std::atomic<T*> data;
        std::atomic<Node*> next;
        
        Node() : data(nullptr), next(nullptr) {}
    };
    
    std::atomic<Node*> head_;
    std::atomic<Node*> tail_;
    
public:
    LockFreeQueue() {
        Node* dummy = new Node;
        head_.store(dummy);
        tail_.store(dummy);
    }
    
    ~LockFreeQueue() {
        while (Node* const old_head = head_.load()) {
            head_.store(old_head->next);
            delete old_head;
        }
    }
    
    // Enqueue an item
    void enqueue(T item) {
        Node* const new_node = new Node;
        T* const data = new T(std::move(item));
        
        Node* const prev_tail = tail_.exchange(new_node);
        prev_tail->data.store(data);
        prev_tail->next.store(new_node);
    }
    
    // Dequeue an item
    bool dequeue(T& result) {
        Node* head = head_.load();
        Node* new_head = head->next.load();
        
        if (new_head == nullptr) {
            return false;
        }
        
        T* const data = new_head->data.load();
        if (data == nullptr) {
            return false;
        }
        
        result = *data;
        delete data;
        
        head_.store(new_head);
        delete head;
        
        return true;
    }
    
    // Check if queue is empty
    bool empty() const {
        Node* head = head_.load();
        Node* tail = tail_.load();
        return head == tail;
    }
};

#endif // LOCK_FREE_QUEUE_H
