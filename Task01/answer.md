
# Q1 – Processes and Process States

## 1. Process-State Diagram

The five process states are:

- New: Process is being created.
- Ready: Process is waiting for CPU allocation.
- Running: Process is executing.
- Waiting: Process is waiting for I/O or an event.
- Terminated: Process has completed execution.

Transitions:
New → Ready → Running → Terminated.
Running → Waiting → Ready.
Running → Ready when preempted.

## 2. Process Control Block (PCB)

A Process Control Block is a data structure maintained by the operating system to store information about a process.

| Component | Description |
|---|---|
| Process ID | Unique identification number |
| Process State | Current state of the process |
| Program Counter | Address of the next instruction |
| CPU Registers | Stores register values |
| Scheduling Information | Priority and scheduling details |
| Memory Information | Memory allocation details |
| I/O Information | Open files and devices |
| Accounting Information | CPU usage and execution time |

## 3. Evaluation of 2000 Processes

- Context switching increases CPU overhead.
- Every process requires a separate address space.
- Memory consumption increases.
- Processes waiting for I/O remain blocked.
- Too many processes can reduce server performance.

## 4. Design Decision

| Design | Evaluation |
|---|---|
| Process per student | Strong isolation but high memory usage |
| Thread per student | Lower memory usage but shared resources |
| Fixed worker pool | Controls resource usage and improves scalability |

Recommended Design: A fixed worker pool is recommended because it reduces resource overhead, supports concurrent student sessions and improves CPU utilization.

## 5. Alternative Concept – Threads

Threads share code, data and open files, but each thread has its own stack, registers and program counter.

Threads generally require less memory and have lower switching overhead than processes. However, a crash in one thread can affect the entire server process.

## 6. Experimental Observation

The fork() program successfully created four child processes. The ps command displayed their process IDs and parent process ID. The child processes entered the sleeping state during execution and completed successfully.

