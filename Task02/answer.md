# TASK 02 – CPU SCHEDULING

## 1. Problem Description

A cloud video encoding system executes four processes. CPU scheduling algorithms are used to allocate CPU time efficiently and reduce waiting time and turnaround time.

### Given Process Details

| Process | Arrival Time | Burst Time |
|---|---:|---:|
| P1 | 0 | 8 |
| P2 | 1 | 4 |
| P3 | 2 | 9 |
| P4 | 3 | 5 |

## 2. Scheduling Algorithms

### A. First Come First Serve (FCFS)

FCFS executes processes in the order of arrival.

**Gantt Chart:**

```text
0       8       12       21       26
|  P1   |  P2   |   P3   |   P4   |
```

| Process | TAT | WT | RT |
|---|---:|---:|---:|
| P1 | 8 | 0 | 0 |
| P2 | 11 | 7 | 7 |
| P3 | 19 | 10 | 10 |
| P4 | 23 | 18 | 18 |

Average TAT = 15.25  
Average WT = 8.75  
Average RT = 8.75

### B. Shortest Job First (SJF)

SJF selects the available process with the shortest burst time. It is non-preemptive.

**Gantt Chart:**

```text
0       8       12      17        26
|  P1   |  P2   |  P4   |    P3   |
```

| Process | TAT | WT | RT |
|---|---:|---:|---:|
| P1 | 8 | 0 | 0 |
| P2 | 11 | 7 | 7 |
| P3 | 24 | 15 | 15 |
| P4 | 14 | 9 | 9 |

Average TAT = 14.25  
Average WT = 7.75  
Average RT = 7.75

### C. Shortest Remaining Time First (SRTF)

SRTF is the preemptive version of SJF. A process with the shortest remaining execution time is selected.

**Gantt Chart:**

```text
0   1       5       10       17        26
|P1 |  P2   |  P4   |   P1   |    P3   |
```

| Process | TAT | WT | RT |
|---|---:|---:|---:|
| P1 | 17 | 9 | 0 |
| P2 | 4 | 0 | 0 |
| P3 | 24 | 15 | 15 |
| P4 | 7 | 2 | 2 |

Average TAT = 13.00  
Average WT = 6.50  
Average RT = 4.25

### D. Round Robin (RR)

Round Robin allocates a fixed time quantum to each process in cyclic order.

**Time Quantum = 3**

```text
P1(0-3) P2(3-6) P3(6-9) P4(9-12)
P1(12-15) P2(15-16) P3(16-19)
P4(19-21) P1(21-23) P3(23-26)
```

| Process | TAT | WT | RT |
|---|---:|---:|---:|
| P1 | 23 | 15 | 0 |
| P2 | 15 | 11 | 2 |
| P3 | 24 | 15 | 4 |
| P4 | 18 | 13 | 6 |

Average TAT = 20.00  
Average WT = 13.50  
Average RT = 3.00

## 3. Priority Scheduling

Priority Scheduling executes the process with the highest priority first.

Since the assignment does not provide priority values, the following values are assumed. A smaller number represents a higher priority.

| Process | Priority |
|---|---:|
| P1 | 2 |
| P2 | 1 |
| P3 | 4 |
| P4 | 3 |

Non-preemptive Priority Scheduling is used.

**Gantt Chart:**

```text
0       8       12      17        26
|  P1   |  P2   |  P4   |    P3   |
```

| Process | TAT | WT | RT |
|---|---:|---:|---:|
| P1 | 8 | 0 | 0 |
| P2 | 11 | 7 | 7 |
| P3 | 24 | 15 | 15 |
| P4 | 14 | 9 | 9 |

Average TAT = 14.25  
Average WT = 7.75  
Average RT = 7.75

## 4. Round Robin with Different Time Quantum Values

The Round Robin program was tested using three different time quantum values.

| Time Quantum | Average WT | Average TAT | Context Switches |
|---|---:|---:|---:|
| 1 | 12.50 | 19.00 | 25 |
| 3 | 13.50 | 20.00 | 9 |
| 20 | 8.75 | 15.25 | 3 |

**Observation:**

- Quantum 1 provides frequent CPU switching and better response time, but causes more context-switch overhead.
- Quantum 3 provides a balance between responsiveness and switching overhead.
- Quantum 20 behaves similarly to FCFS because the quantum is larger than every process burst time.

## 5. Alternative Scheduling Algorithm – Multilevel Feedback Queue (MLFQ)

MLFQ uses multiple priority queues with different time quantum values.

- New processes enter the highest-priority queue.
- Processes that use their full time quantum may move to a lower-priority queue.
- Short and interactive tasks receive faster CPU service.
- It improves responsiveness for interactive systems.

## 6. Time Complexity

| Algorithm | Time Complexity |
|---|---|
| FCFS | O(n) |
| SJF | O(n log n) with sorting |
| SRTF | O(n log n) with a priority queue |
| Priority Scheduling | O(n log n) with sorting |
| Round Robin | O(n + total CPU burst / quantum) |

## 7. Conclusion

Different CPU scheduling algorithms provide different performance results. SRTF provides the lowest average waiting time among the calculated algorithms for this workload. Round Robin provides fair CPU allocation and is suitable for time-sharing systems. A suitable scheduling algorithm should be selected based on response time, waiting time, turnaround time and context-switch overhead.
