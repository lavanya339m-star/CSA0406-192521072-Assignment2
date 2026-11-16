# TASK 05 – PROCESS SYNCHRONIZATION

## 1. Introduction

Process synchronization is used to coordinate multiple processes or threads that access shared resources. In a railway reservation system, synchronization prevents multiple users from booking the same seat simultaneously.

## 2. Producer–Consumer Problem

The Producer–Consumer problem is a synchronization problem where producers generate data and consumers process it using a shared bounded buffer.

Our program uses:
- POSIX semaphores to control empty and full buffer slots.
- Mutex locks to protect shared buffer variables.
- Four producers and four consumers in the multithreaded test.

## 3. Semaphore Operations

Two semaphores are used:

**Empty semaphore:**
- Represents the number of empty buffer slots.
- Initialized to the buffer size.
- Decremented when a producer inserts an item.

**Full semaphore:**
- Represents the number of filled buffer slots.
- Initialized to zero.
- Incremented when a producer inserts an item.

The mutex ensures that only one thread accesses the shared buffer at a time.

## 4. Producer–Consumer Experimental Results

The program was tested using two configurations.

| Configuration | Producers | Consumers | Items Consumed | Sum |
|---|---:|---:|---:|---:|
| Single-thread test | 1 | 1 | 20 | 210 |
| Multithread test | 4 | 4 | 20 | 210 |

**Observation:**

Both configurations successfully consumed 20 items. The sum of 210 confirms that all values from 1 to 20 were processed exactly once.

## 5. Importance of Mutex

A mutex is used to protect shared resources from simultaneous access.

Without a mutex, multiple threads may update shared variables at the same time, causing race conditions and incorrect results.

With a mutex, only one thread can enter the critical section at a time.

## 6. Other Synchronization Problems

### A. Bounded Buffer Problem

A bounded buffer has a fixed capacity. Producers wait when the buffer is full, and consumers wait when it is empty.

Semaphores and mutex locks are used to coordinate access.

### B. Readers–Writers Problem

Multiple readers can access shared data simultaneously, but writers require exclusive access.

Synchronization prevents readers from accessing data while it is being modified by a writer.

### C. Dining Philosophers Problem

Multiple philosophers share limited forks. Deadlock may occur if every philosopher holds one fork and waits for another.

Solutions include resource ordering and semaphore-based control.

### D. Monitor

A monitor is a high-level synchronization mechanism that combines shared data and operations with mutual exclusion. It controls access to critical sections.

## 7. Railway Reservation System

In a railway reservation system, multiple users may try to reserve the same seat simultaneously.

Synchronization is required to prevent double booking.

**Global Lock:**
- One lock protects the entire reservation system.
- Simple to implement.
- Reduces concurrency because only one booking operation can proceed at a time.

**Per-Train Lock:**
- Each train has a separate lock.
- Bookings for different trains can happen simultaneously.
- Improves concurrency.

**Per-Coach Lock:**
- Each coach has an individual lock.
- Allows bookings in different coaches simultaneously.
- Provides finer-grained concurrency but requires more lock management.

## 8. Testing and Race Conditions

The producer–consumer program should be executed repeatedly to verify synchronization reliability.

Running the experiment 100 times can help identify intermittent synchronization errors.

Removing the mutex may cause race conditions because multiple threads can access shared buffer variables simultaneously.

**Expected observation:** Without proper synchronization, incorrect counts, missing items or duplicate processing may occur.

## 9. Alternative Synchronization Methods

**Atomic Operations:**
- Perform certain operations indivisibly.
- Useful for simple shared counters and flags.

**Spinlocks:**
- Threads repeatedly check whether a lock is available.
- Useful for very short critical sections.
- Can waste CPU time while waiting.

## 10. Conclusion

Process synchronization is essential for maintaining data consistency in concurrent systems. Semaphores control buffer availability, while mutex locks protect shared resources. In railway reservation systems, appropriate locking strategies prevent double booking and improve concurrent access.
