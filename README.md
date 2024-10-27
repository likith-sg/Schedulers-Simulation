# Process Scheduling Algorithms in C

This repository contains a C program that simulates various process scheduling algorithms. It allows users to input process details and choose from different scheduling methods to evaluate their performance in terms of waiting time, turnaround time, CPU utilization, and throughput.

## Features

The program implements the following scheduling algorithms:

1. **First-Come-First-Serve (FCFS)**: Processes are scheduled in the order they arrive. This algorithm is simple but can lead to the "convoy effect," where short processes wait for a long process to finish.

2. **Shortest Job First (SJF)**: The process with the smallest burst time is scheduled next. This algorithm can minimize average waiting time but may cause starvation for longer processes.

3. **Shortest Remaining Time First (SRTF)**: A preemptive version of SJF where the process with the smallest remaining time is scheduled next. This can improve response time for shorter processes.

4. **Priority Scheduling**: Each process is assigned a priority, and the process with the highest priority (lowest priority number) is scheduled first. This can lead to starvation if low-priority processes are consistently preempted.

5. **Round Robin (RR)**: Each process is assigned a fixed time quantum, and processes are cycled through in a round-robin manner. This approach provides a fair allocation of CPU time but may increase turnaround time for short processes.

## How It Works

- **Input**: The program prompts the user to enter the number of processes and their respective arrival times, burst times, and priorities.

- **Scheduling Choice**: After inputting process details, the user can choose a scheduling algorithm to simulate.

- **Output**: For the selected scheduling algorithm, the program calculates and displays:
  - Waiting time for each process
  - Turnaround time for each process
  - Average waiting time
  - Average turnaround time
  - CPU utilization
  - Throughput

## Compilation and Execution

To compile and run the program, follow these steps:

### Clone the Repository:
```bash
git clone https://github.com/likith-sg/Schedulers-Simulation.git
cd Schedulers-Simulation
```

### Compile the Program:
```bash
gcc -o Schedulers_Simulation Schedulers_Simulation.c
```

### Run the Progrm:
```bash
./Schedulers_Simulation
```

## Example Input/Output
### Input:
```bash
Enter number of processes: 3
Enter arrival time, burst time, and priority for process 1: 0 5 2
Enter arrival time, burst time, and priority for process 2: 1 3 1
Enter arrival time, burst time, and priority for process 3: 2 8 3
```

### Output:
```bash
--- SJF Scheduling ---
Process 1: Waiting Time = 0, Turnaround Time = 5
Process 2: Waiting Time = 4, Turnaround Time = 7
Process 3: Waiting Time = 5, Turnaround Time = 13
Throughput: 0.23
CPU Utilization: 100.00%
Average Waiting Time: 3.00
Average Turnaround Time: 8.33
```

## Contributing
### Contributions are welcome! Feel free to open an issue or submit a pull request if you have suggestions or improvements.

## License
### This project is licensed under the MIT License. See the LICENSE file for more details.
