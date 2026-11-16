# TASK 06 – DEADLOCKS AND BANKER'S ALGORITHM

## 1. Introduction

A deadlock occurs when two or more processes wait indefinitely for resources held by one another. Deadlock management is important in operating systems to ensure efficient resource allocation.

In a laboratory environment, resources such as GPUs, software licences and storage devices may be shared by multiple processes.

## 2. Four Necessary Conditions for Deadlock

Deadlock occurs when all four conditions exist simultaneously.

1. **Mutual Exclusion:** A resource can be used by only one process at a time.
2. **Hold and Wait:** A process holds one resource while waiting for another.
3. **No Preemption:** Resources cannot be forcibly taken away from a process.
4. **Circular Wait:** A circular chain of processes exists, where each process waits for a resource held by the next process.

## 3. Resource Allocation Graph (RAG)

A Resource Allocation Graph represents the relationship between processes and resources.

- Process nodes are represented by circles.
- Resource nodes are represented by rectangles.
- Request edges indicate that a process is waiting for a resource.
- Allocation edges indicate that a resource is assigned to a process.

**Example:**

```text
P1 ---> R2 ---> P2
^               |
|               v
R1 <--- P2 <---- 
```

A cycle in a resource allocation graph can indicate a possible deadlock. With multiple instances of resources, a cycle alone does not always prove deadlock.

## 4. Banker's Algorithm

Banker's Algorithm is a deadlock avoidance algorithm. It checks whether allocating resources will leave the system in a safe state.

The main data structures are:

- **Available:** Number of currently available resources.
- **Maximum:** Maximum resource requirement of each process.
- **Allocation:** Resources currently allocated to each process.
- **Need:** Remaining resources required by each process.

Formula:

Need = Maximum - Allocation

### Steps

1. Calculate the Need matrix.
2. Check whether a process's Need is less than or equal to Available.
3. If possible, assume that the process completes.
4. Release its allocated resources and update Available.
5. Repeat until all processes finish or no suitable process can be found.

## 5. Experimental Results

The Banker's Algorithm program was implemented in C and executed successfully.

### Initial System State

The system was found to be in a safe state.

**Safe sequence:**

P1 → P3 → P4 → P0 → P2

### Resource Request Results

| Process | Request Result | Explanation |
|---|---|---|
| P1 | Granted | Request keeps the system safe |
| P4 | Must wait | Resources are currently unavailable |
| P0 | Denied | Request results in an unsafe state |

The experiment demonstrates how Banker's Algorithm checks resource requests before granting them.

## 6. Deadlock Handling Strategies

### A. Deadlock Prevention

Prevention ensures that at least one of the four necessary deadlock conditions cannot occur.

Examples include:
- Making resources shareable where possible.
- Requiring processes to request resources together.
- Allowing resource preemption.
- Enforcing resource ordering.

### B. Deadlock Avoidance

Avoidance checks resource allocation requests before granting them.

Banker's Algorithm is an example of deadlock avoidance.

### C. Deadlock Detection

The operating system periodically checks whether deadlock has occurred by examining resource allocation and waiting relationships.

### D. Deadlock Recovery

Recovery methods include:
- Terminating one or more processes.
- Preempting resources.
- Rolling back processes to a previous safe state.

### E. Ostrich Approach

The Ostrich approach ignores deadlocks when their occurrence is sufficiently rare and the cost of prevention or detection is greater than the expected loss.

## 7. Time Complexity

Let n represent the number of processes and m represent the number of resource types.

The safety algorithm has an approximate time complexity of:

O(n² × m)

This is because the algorithm may examine every process repeatedly while checking resource requirements.

As the number of processes and resource types increases, the computation required also increases.

## 8. Performance Evaluation

The algorithm can be evaluated using different process counts:

| Number of Processes | Expected Behaviour |
|---|---|
| 10 | Lower computation time |
| 100 | Moderate computation time |
| 1000 | Higher computation time |

The number of processes affects the time required to check system safety. Actual execution times depend on the hardware and implementation.

## 9. Recommendation

For a laboratory environment with shared GPUs, licences and storage resources, Banker's Algorithm is suitable when maximum resource requirements are known in advance.

Resource allocation should be checked before granting requests. Deadlock detection and recovery can also be used when resource requirements cannot be predicted accurately.

## 10. Conclusion

Deadlocks can affect system performance and prevent processes from completing. Banker's Algorithm helps avoid deadlocks by checking system safety before allocating resources. Proper resource management, prevention and recovery strategies improve operating system reliability.
