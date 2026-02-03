# Concurrency & Parallelism Examples
import threading
import time
import requests
import multiprocessing
import os
import asyncio
import aiohttp
import queue
from concurrent.futures import ThreadPoolExecutor, ProcessPoolExecutor, as_completed
import math
import random

print("Concurrency & Parallelism Examples")
print("=" * 40)

# Understanding Concurrency vs Parallelism
print("1. Understanding Concurrency vs Parallelism")
print("-" * 45)

def simple_task(name, duration):
    """Simple task that simulates work."""
    print(f"Task {name} starting")
    time.sleep(duration)
    print(f"Task {name} completed")

# Sequential execution
print("Sequential Execution:")
start_time = time.time()
simple_task("A", 1)
simple_task("B", 1)
simple_task("C", 1)
sequential_time = time.time() - start_time
print(f"Sequential execution took: {sequential_time:.2f} seconds")

# Threaded execution
print("\nThreaded Execution:")
start_time = time.time()

threads = []
for i in range(3):
    thread = threading.Thread(target=simple_task, args=(f"Thread-{i}", 1))
    threads.append(thread)
    thread.start()

# Wait for all threads to complete
for thread in threads:
    thread.join()

threaded_time = time.time() - start_time
print(f"Threaded execution took: {threaded_time:.2f} seconds")

# Thread-safe counter example
print("\n2. Thread-Safe Counter")
print("-" * 25)

class ThreadSafeCounter:
    """Thread-safe counter using locks."""
    
    def __init__(self):
        self._value = 0
        self._lock = threading.Lock()
    
    def increment(self):
        """Increment counter safely."""
        with self._lock:
            self._value += 1
    
    def get_value(self):
        """Get current counter value."""
        with self._lock:
            return self._value
    
    def increment_by(self, amount):
        """Increment counter by specified amount."""
        with self._lock:
            self._value += amount

def worker(counter, iterations):
    """Worker function that increments counter."""
    for _ in range(iterations):
        counter.increment()

# Thread-safe counter demo
counter = ThreadSafeCounter()
threads = []

# Create multiple threads that increment the counter
for i in range(5):
    thread = threading.Thread(target=worker, args=(counter, 1000))
    threads.append(thread)
    thread.start()

# Wait for all threads to complete
for thread in threads:
    thread.join()

print(f"Final counter value: {counter.get_value()}")
print(f"Expected value: {5 * 1000}")

# Producer-Consumer Pattern
print("\n3. Producer-Consumer Pattern")
print("-" * 30)

class ProducerConsumer:
    """Producer-consumer pattern using threads and queues."""
    
    def __init__(self, max_size=5):
        self.queue = queue.Queue(maxsize=max_size)
        self.results = []
        self.lock = threading.Lock()
    
    def producer(self, items):
        """Produce items and put them in queue."""
        for item in items:
            print(f"Producing: {item}")
            self.queue.put(item)
            time.sleep(0.1)  # Simulate work
        print("Producer finished")
    
    def consumer(self, consumer_id):
        """Consume items from queue."""
        while True:
            try:
                item = self.queue.get(timeout=1)
                print(f"Consumer {consumer_id} processing: {item}")
                time.sleep(0.2)  # Simulate work
                
                with self.lock:
                    self.results.append(f"Processed by {consumer_id}: {item}")
                
                self.queue.task_done()
            except queue.Empty:
                print(f"Consumer {consumer_id} finished")
                break

# Using producer-consumer
pc = ProducerConsumer()

# Create producer thread
producer_thread = threading.Thread(
    target=pc.producer, 
    args=([f"Item-{i}" for i in range(10)],)
)

# Create consumer threads
consumer_threads = []
for i in range(3):
    consumer_thread = threading.Thread(
        target=pc.consumer, 
        args=(i,)
    )
    consumer_threads.append(consumer_thread)

# Start all threads
producer_thread.start()
for thread in consumer_threads:
    thread.start()

# Wait for completion
producer_thread.join()
for thread in consumer_threads:
    thread.join()

print(f"Results: {pc.results}")

# ThreadPoolExecutor
print("\n4. ThreadPoolExecutor")
print("-" * 22)

def fetch_url(url):
    """Fetch URL content."""
    try:
        response = requests.get(url, timeout=5)
        return {
            'url': url,
            'status': response.status_code,
            'length': len(response.content)
        }
    except Exception as e:
        return {
            'url': url,
            'status': 'error',
            'error': str(e)
        }

# ThreadPoolExecutor demo
urls = [
    'https://httpbin.org/delay/1',
    'https://httpbin.org/delay/2',
    'https://httpbin.org/delay/1',
    'https://httpbin.org/delay/3',
    'https://httpbin.org/delay/1'
]

start_time = time.time()

with ThreadPoolExecutor(max_workers=3) as executor:
    # Submit all tasks
    future_to_url = {executor.submit(fetch_url, url): url for url in urls}
    
    # Process completed tasks
    for future in as_completed(future_to_url):
        url = future_to_url[future]
        try:
            result = future.result()
            print(f"URL: {result['url']}, Status: {result['status']}")
        except Exception as e:
            print(f"URL: {url}, Error: {e}")

executor_time = time.time() - start_time
print(f"ThreadPoolExecutor took: {executor_time:.2f} seconds")

# Multiprocessing
print("\n5. Multiprocessing")
print("-" * 18)

def cpu_intensive_task(n):
    """CPU-intensive task."""
    print(f"Process {os.getpid()} processing {n}")
    # Simulate CPU-intensive work
    result = sum(i * i for i in range(n))
    return result

# Sequential execution
start_time = time.time()
sequential_results = [cpu_intensive_task(100000) for _ in range(4)]
sequential_time = time.time() - start_time
print(f"Sequential execution took: {sequential_time:.2f} seconds")

# Multiprocessing execution
start_time = time.time()

with multiprocessing.Pool(processes=4) as pool:
    multiprocessing_results = pool.map(cpu_intensive_task, [100000] * 4)

multiprocessing_time = time.time() - start_time
print(f"Multiprocessing execution took: {multiprocessing_time:.2f} seconds")
print(f"Speedup: {sequential_time / multiprocessing_time:.2f}x")

# Process communication with Queue
print("\n6. Process Communication")
print("-" * 25)

def worker_process(name, queue, results):
    """Worker process that processes items from queue."""
    while True:
        try:
            item = queue.get(timeout=1)
            print(f"Process {name} (PID: {os.getpid()}) processing: {item}")
            
            # Simulate work
            time.sleep(0.5)
            result = item * 2
            
            results.append(result)
            queue.task_done()
        except:
            print(f"Process {name} finished")
            break

manager = multiprocessing.Manager()
queue = manager.Queue()
results = manager.list()

# Add items to queue
for i in range(10):
    queue.put(i)

# Create and start processes
processes = []
for i in range(3):
    process = multiprocessing.Process(
        target=worker_process,
        args=(f"Worker-{i}", queue, results)
    )
    processes.append(process)
    process.start()

# Wait for all processes to complete
for process in processes:
    process.join()

print(f"Results: {list(results)}")

# Shared memory
def modify_shared_array(shared_array, start, end):
    """Modify a portion of shared array."""
    for i in range(start, end):
        shared_array[i] = shared_array[i] * 2

# Shared memory demo
print("\n7. Shared Memory")
print("-" * 15)
shared_array = multiprocessing.Array('i', range(10))
print(f"Original array: {list(shared_array)}")

# Create processes to modify different portions
processes = []
chunk_size = len(shared_array) // 2

for i in range(2):
    start = i * chunk_size
    end = start + chunk_size
    process = multiprocessing.Process(
        target=modify_shared_array,
        args=(shared_array, start, end)
    )
    processes.append(process)
    process.start()

# Wait for processes to complete
for process in processes:
    process.join()

print(f"Modified array: {list(shared_array)}")

# ProcessPoolExecutor
print("\n8. ProcessPoolExecutor")
print("-" * 22)

def is_prime(n):
    """Check if a number is prime."""
    if n < 2:
        return False
    for i in range(2, int(math.sqrt(n)) + 1):
        if n % i == 0:
            return False
    return True

def find_primes_in_range(start, end):
    """Find all primes in a range."""
    primes = []
    for num in range(start, end):
        if is_prime(num):
            primes.append(num)
    return primes

# Sequential prime finding
start_time = time.time()
sequential_primes = find_primes_in_range(2, 10000)
sequential_time = time.time() - start_time
print(f"Sequential found {len(sequential_primes)} primes in {sequential_time:.2f} seconds")

# Parallel prime finding
start_time = time.time()

# Divide work into chunks
chunk_size = 2500
ranges = [(i, i + chunk_size) for i in range(2, 10000, chunk_size)]

with ProcessPoolExecutor(max_workers=4) as executor:
    futures = [executor.submit(find_primes_in_range, start, end) 
               for start, end in ranges]
    
    parallel_primes = []
    for future in as_completed(futures):
        primes = future.result()
        parallel_primes.extend(primes)

parallel_time = time.time() - start_time
print(f"Parallel found {len(parallel_primes)} primes in {parallel_time:.2f} seconds")
print(f"Speedup: {sequential_time / parallel_time:.2f}x")

# Asyncio
print("\n9. Asyncio")
print("-" * 12)

async def simple_async_task(name, duration):
    """Simple async task."""
    print(f"Task {name} starting")
    await asyncio.sleep(duration)
    print(f"Task {name} completed")
    return f"Result from {name}"

async def fetch_url_async(session, url):
    """Fetch URL content asynchronously."""
    try:
        async with session.get(url) as response:
            content = await response.text()
            return {
                'url': url,
                'status': response.status,
                'length': len(content)
            }
    except Exception as e:
        return {
            'url': url,
            'status': 'error',
            'error': str(e)
        }

# Basic asyncio demo
async def basic_asyncio_demo():
    """Demonstrate basic asyncio functionality."""
    print("Basic Asyncio Demo:")
    
    start_time = time.time()
    
    # Run tasks concurrently
    tasks = [
        simple_async_task("A", 1),
        simple_async_task("B", 1),
        simple_async_task("C", 1)
    ]
    
    results = await asyncio.gather(*tasks)
    asyncio_time = time.time() - start_time
    
    print(f"Async execution took: {asyncio_time:.2f} seconds")
    print(f"Results: {results}")

# Run the basic demo
asyncio.run(basic_asyncio_demo())

# Async context manager
class AsyncDatabaseConnection:
    """Async database connection context manager."""
    
    async def __aenter__(self):
        print("Connecting to database...")
        await asyncio.sleep(0.1)  # Simulate connection time
        self.connected = True
        return self
    
    async def __aexit__(self, exc_type, exc_val, exc_tb):
        print("Closing database connection...")
        await asyncio.sleep(0.1)  # Simulate disconnection time
        self.connected = False
    
    async def query(self, sql):
        """Execute a query."""
        if not self.connected:
            raise RuntimeError("Not connected to database")
        
        await asyncio.sleep(0.1)  # Simulate query time
        return f"Result of: {sql}"

# Async context manager demo
async def async_context_demo():
    """Demonstrate async context manager."""
    print("\nAsync Context Manager Demo:")
    
    async with AsyncDatabaseConnection() as db:
        result1 = await db.query("SELECT * FROM users")
        print(result1)
        
        result2 = await db.query("INSERT INTO users VALUES (1, 'John')")
        print(result2)

asyncio.run(async_context_demo())

# Async producer-consumer
class AsyncProducerConsumer:
    """Async producer-consumer using asyncio."""
    
    def __init__(self, max_size=5):
        self.queue = asyncio.Queue(maxsize=max_size)
        self.results = []
    
    async def producer(self, items):
        """Produce items and put them in queue."""
        for item in items:
            print(f"Producing: {item}")
            await self.queue.put(item)
            await asyncio.sleep(0.1)  # Simulate work
        print("Producer finished")
    
    async def consumer(self, consumer_id):
        """Consume items from queue."""
        while True:
            try:
                item = await asyncio.wait_for(self.queue.get(), timeout=1.0)
                print(f"Consumer {consumer_id} processing: {item}")
                await asyncio.sleep(0.2)  # Simulate work
                
                self.results.append(f"Processed by {consumer_id}: {item}")
                self.queue.task_done()
            except asyncio.TimeoutError:
                print(f"Consumer {consumer_id} finished")
                break

# Async producer-consumer demo
async def async_producer_consumer_demo():
    """Demonstrate async producer-consumer."""
    print("\nAsync Producer-Consumer Demo:")
    
    pc = AsyncProducerConsumer()
    
    # Create tasks
    producer_task = asyncio.create_task(
        pc.producer([f"Item-{i}" for i in range(10)])
    )
    
    consumer_tasks = [
        asyncio.create_task(pc.consumer(i))
        for i in range(3)
    ]
    
    # Wait for producer to finish
    await producer_task
    
    # Wait for consumers to finish
    await asyncio.gather(*consumer_tasks)
    
    print(f"Results: {pc.results}")

asyncio.run(async_producer_consumer_demo())

# Async semaphore for rate limiting
class AsyncRateLimiter:
    """Async rate limiter using semaphore."""
    
    def __init__(self, rate_limit):
        self.semaphore = asyncio.Semaphore(rate_limit)
    
    async def acquire(self):
        """Acquire a permit."""
        await self.semaphore.acquire()
    
    def release(self):
        """Release a permit."""
        self.semaphore.release()
    
    async def __aenter__(self):
        await self.acquire()
        return self
    
    async def __aexit__(self, exc_type, exc_val, exc_tb):
        self.release()

async def rate_limited_task(task_id, rate_limiter):
    """Task that respects rate limiting."""
    async with rate_limiter:
        print(f"Task {task_id} starting")
        await asyncio.sleep(random.uniform(0.5, 1.5))
        print(f"Task {task_id} completed")

# Rate limiting demo
async def rate_limiting_demo():
    """Demonstrate rate limiting."""
    print("\nRate Limiting Demo:")
    
    rate_limiter = AsyncRateLimiter(2)  # Allow 2 concurrent tasks
    
    tasks = [
        asyncio.create_task(rate_limited_task(i, rate_limiter))
        for i in range(10)
    ]
    
    await asyncio.gather(*tasks)

asyncio.run(rate_limiting_demo())

# Performance comparison
print("\n10. Performance Comparison")
print("-" * 28)

def sync_task(url):
    """Synchronous task."""
    try:
        response = requests.get(url, timeout=5)
        return {'url': url, 'status': response.status_code}
    except:
        return {'url': url, 'status': 'error'}

def threading_task(urls):
    """Threading implementation."""
    with ThreadPoolExecutor(max_workers=5) as executor:
        results = list(executor.map(sync_task, urls))
    return results

def multiprocessing_task(urls):
    """Multiprocessing implementation."""
    with ProcessPoolExecutor(max_workers=5) as executor:
        results = list(executor.map(sync_task, urls))
    return results

async def async_task(session, url):
    """Async task."""
    try:
        async with session.get(url) as response:
            return {'url': url, 'status': response.status}
    except:
        return {'url': url, 'status': 'error'}

async def asyncio_task(urls):
    """Asyncio implementation."""
    async with aiohttp.ClientSession() as session:
        tasks = [async_task(session, url) for url in urls]
        results = await asyncio.gather(*tasks)
    return results

# Performance comparison
async def performance_comparison():
    """Compare different concurrency approaches."""
    print("Performance Comparison:")
    
    urls = [
        'https://httpbin.org/delay/1',
        'https://httpbin.org/delay/1',
        'https://httpbin.org/delay/1',
        'https://httpbin.org/delay/1',
        'https://httpbin.org/delay/1'
    ]
    
    # Synchronous
    start_time = time.time()
    sync_results = [sync_task(url) for url in urls]
    sync_time = time.time() - start_time
    print(f"Synchronous: {sync_time:.2f} seconds")
    
    # Threading
    start_time = time.time()
    threading_results = threading_task(urls)
    threading_time = time.time() - start_time
    print(f"Threading: {threading_time:.2f} seconds")
    
    # Multiprocessing
    start_time = time.time()
    multiprocessing_results = multiprocessing_task(urls)
    multiprocessing_time = time.time() - start_time
    print(f"Multiprocessing: {multiprocessing_time:.2f} seconds")
    
    # Asyncio
    start_time = time.time()
    asyncio_results = await asyncio_task(urls)
    asyncio_time = time.time() - start_time
    print(f"Asyncio: {asyncio_time:.2f} seconds")
    
    # Speedup comparison
    print(f"\nSpeedup vs Synchronous:")
    print(f"Threading: {sync_time / threading_time:.2f}x")
    print(f"Multiprocessing: {sync_time / multiprocessing_time:.2f}x")
    print(f"Asyncio: {sync_time / asyncio_time:.2f}x")

# Run performance comparison
asyncio.run(performance_comparison())

print("\nConcurrency & Parallelism examples completed!")


