# TASK 04 – INTER-PROCESS COMMUNICATION (IPC)

## 1. Introduction

Inter-Process Communication (IPC) allows processes to exchange data and coordinate their activities. In a weather monitoring system, a parent process collects temperature readings and sends them to a child process using a pipe.

## 2. Pipe Communication

A pipe is a communication mechanism that allows data to flow between related processes.

In this program:
- The parent process acts as the weather station.
- The child process acts as the weather analyzer.
- The parent sends six temperature readings through the pipe.
- The child reads the values and calculates the average and maximum temperature.

### Program Output

```text
Weather Station Analyzer
Total readings: 6
Average temperature: 35.50
Maximum temperature: 41
Reader done
```

## 3. Importance of EOF

EOF means End Of File. It indicates that no more data is available from the pipe.

The parent process must close the writing end using `close(fd[1])` after sending all readings.

If the writing end is not closed, the child process continues waiting for more data because it does not receive EOF. This can cause the program to hang.

## 4. Shared Memory vs Message Passing

| Shared Memory | Message Passing |
|---|---|
| Processes share a memory region. | Processes exchange messages. |
| Fast for large data transfers. | May involve additional copying. |
| Requires synchronization. | Communication is controlled through messages. |
| Suitable for large data exchange. | Suitable for smaller or structured communication. |

## 5. IPC Performance Experiment

The pipe communication program was tested with three different data sizes.

### Observed Results

| Data Size | Bytes Received | Transfer Time |
|---|---:|---:|
| 1 MB | 1,048,576 | 0.0003 seconds |
| 10 MB | 10,485,760 | 0.0035 seconds |
| 100 MB | 104,857,600 | 0.0303 seconds |

### Observation

- The pipe successfully transferred all three data sizes.
- Transfer time increased as the data size increased.
- Larger data transfers require more communication time.
- These timings are measurements from the current system and may vary on different computers.

## 6. Shared Memory and Semaphore Alternative

Shared memory can be used as an alternative to pipes.

Steps:
1. Create a shared memory segment.
2. Attach the parent and child processes to the shared memory.
3. The parent writes temperature readings into the shared memory.
4. The child reads and processes the readings.
5. Use semaphores to synchronize access and prevent simultaneous conflicting operations.
6. Detach and remove the shared memory segment after completion.

## 7. Advantages and Disadvantages of IPC

**Advantages:**
- Allows processes to exchange information.
- Supports coordination between processes.
- Shared memory provides efficient data sharing.
- Pipes provide simple communication between related processes.

**Disadvantages:**
- Synchronization may be required.
- Improper pipe handling can cause blocking.
- Shared memory requires careful access control.
- IPC mechanisms add implementation complexity.

## 8. Conclusion

IPC is important for communication between processes. Pipes provide a simple way to transfer weather readings, while shared memory can improve performance for large data transfers. Proper synchronization and closing pipe ends are necessary for reliable communication.
