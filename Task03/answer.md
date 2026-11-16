# TASK 03 – THREADS

## 1. Introduction

The traffic monitoring system uses 64 cameras to capture and process video data. Multithreading allows multiple camera tasks to execute concurrently, improving system responsiveness and resource utilization.

## 2. One Thread Per Camera

In this approach, 64 POSIX threads are created, with one thread assigned to each camera.

**Advantages:**
- Each camera can be processed independently.
- Multiple tasks can execute concurrently.
- Easy to understand and implement.

**Disadvantages:**
- Creating many threads increases memory usage.
- Thread creation and management cause overhead.
- Too many threads may reduce performance.

## 3. Thread Pool Implementation

A thread pool uses a fixed number of worker threads to process multiple camera tasks.

The program was tested with different worker counts.

| Configuration | Cameras Processed |
|---|---:|
| One thread per camera | 64 |
| Thread pool – 4 workers | 64 |
| Thread pool – 8 workers | 64 |
| Thread pool – 16 workers | 64 |

**Observation:** All configurations successfully processed 64 cameras. A thread pool reduces the overhead of creating a separate thread for every task and allows better resource management.

## 4. Shared Resources and Individual Resources

**Shared resources:**
- Threads share the same process memory.
- They can access global variables and shared data.
- Synchronization is required to prevent race conditions.

**Individual resources:**
- Each thread has its own stack.
- Each thread has its own register state and program counter.
- These allow threads to execute independently.

## 5. User-Level and Kernel-Level Threads

**User-Level Threads:**
- Managed by a user-level thread library.
- Thread operations can be faster.
- The kernel may not schedule individual user threads directly.

**Kernel-Level Threads:**
- Managed by the operating system kernel.
- The kernel schedules individual threads.
- They support parallel execution on multiple CPU cores.

## 6. Speedup and Performance

Speedup is calculated using:

Speedup = Execution time using one worker / Execution time using multiple workers

Increasing the number of workers can improve performance because multiple tasks execute concurrently. However, performance may eventually reach a plateau due to CPU core limitations, synchronization overhead, memory usage and resource contention.

The current program verifies task completion but does not measure execution time. Therefore, exact speedup values are not reported.

## 7. Race Condition Demonstration

A race condition occurs when multiple threads access and modify shared data simultaneously without proper synchronization.

The program uses a shared counter. Two threads increment the counter 100,000 times each.

**Observed output:**

- Counter without mutex: 163264 in one run and 97601 in another run.
- Counter with mutex: 200000.

The incorrect results without a mutex demonstrate a race condition. A mutex ensures that only one thread modifies the shared counter at a time.

## 8. Process-Based Alternative Using IPC

Instead of threads, the system can create separate processes to handle camera streams.

Processes have separate memory spaces and can communicate using:
- Pipes
- Shared memory
- Message queues

**Advantages:**
- Better isolation between camera-processing tasks.
- A failure in one process is less likely to affect others.

**Disadvantages:**
- Higher memory consumption.
- Process creation and context switching have additional overhead.
- IPC requires communication and synchronization.

## 9. Conclusion

Multithreading is useful for processing multiple traffic camera streams concurrently. Thread pools provide controlled resource usage, while mutex locks protect shared data from race conditions. For this system, a fixed-size thread pool is a practical approach because it balances concurrency and resource management.
