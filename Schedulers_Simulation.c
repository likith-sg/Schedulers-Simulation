#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

// Structure to represent a process
typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int priority;
    int waiting_time;
    int turnaround_time;
    bool is_completed;
} Process;

// Function to simulate First-Come-First-Serve (FCFS) scheduling
void FCFS(Process processes[], int n) {
    int time = 0, total_waiting_time = 0, total_turnaround_time = 0;
    int total_burst_time = 0;

    printf("\n--- FCFS Scheduling ---\n");
    for (int i = 0; i < n; i++) {
        if (time < processes[i].arrival_time) {
            time = processes[i].arrival_time;
        }
        processes[i].waiting_time = time - processes[i].arrival_time;
        time += processes[i].burst_time;
        processes[i].turnaround_time = time - processes[i].arrival_time;

        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
        total_burst_time += processes[i].burst_time;

        printf("Process %d: Waiting Time = %d, Turnaround Time = %d\n",
               processes[i].process_id, processes[i].waiting_time, processes[i].turnaround_time);
    }

    float average_waiting_time = (float)total_waiting_time / n;
    float average_turnaround_time = (float)total_turnaround_time / n;
    float throughput = (float)n / time;
    float cpu_utilization = ((float)total_burst_time / time) * 100;

    printf("Throughput: %.2f\n", throughput);
    printf("CPU Utilization: %.2f%%\n", cpu_utilization);
    printf("Average Waiting Time: %.2f\n", average_waiting_time);
    printf("Average Turnaround Time: %.2f\n", average_turnaround_time);
}

// Function to simulate Shortest Job First (SJF) scheduling
void SJF(Process processes[], int n) {
    int time = 0, completed = 0, total_waiting_time = 0, total_turnaround_time = 0;
    int total_burst_time = 0;
    bool completed_processes[n];

    printf("\n--- SJF Scheduling ---\n");
    for (int i = 0; i < n; i++) {
        completed_processes[i] = false;
        total_burst_time += processes[i].burst_time;
    }

    while (completed < n) {
        int shortest = -1;
        for (int i = 0; i < n; i++) {
            if (!completed_processes[i] && processes[i].arrival_time <= time) {
                if (shortest == -1 || processes[i].burst_time < processes[shortest].burst_time) {
                    shortest = i;
                }
            }
        }

        if (shortest == -1) {
            time++;
        } else {
            processes[shortest].waiting_time = time - processes[shortest].arrival_time;
            time += processes[shortest].burst_time;
            processes[shortest].turnaround_time = time - processes[shortest].arrival_time;
            total_waiting_time += processes[shortest].waiting_time;
            total_turnaround_time += processes[shortest].turnaround_time;
            completed_processes[shortest] = true;
            completed++;
            printf("Process %d: Waiting Time = %d, Turnaround Time = %d\n",
                   processes[shortest].process_id, processes[shortest].waiting_time, processes[shortest].turnaround_time);
        }
    }

    float average_waiting_time = (float)total_waiting_time / n;
    float average_turnaround_time = (float)total_turnaround_time / n;
    float throughput = (float)n / time;
    float cpu_utilization = ((float)total_burst_time / time) * 100;

    printf("Throughput: %.2f\n", throughput);
    printf("CPU Utilization: %.2f%%\n", cpu_utilization);
    printf("Average Waiting Time: %.2f\n", average_waiting_time);
    printf("Average Turnaround Time: %.2f\n", average_turnaround_time);
}

// Function to simulate Shortest Remaining Time First (SRTF) scheduling
void SRTF(Process processes[], int n) {
    int time = 0, completed = 0, total_waiting_time = 0, total_turnaround_time = 0;
    int total_burst_time = 0;

    printf("\n--- SRTF Scheduling ---\n");
    for (int i = 0; i < n; i++) {
        total_burst_time += processes[i].burst_time;
        processes[i].remaining_time = processes[i].burst_time;
    }

    while (completed < n) {
        int shortest = -1;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= time && processes[i].remaining_time > 0) {
                if (shortest == -1 || processes[i].remaining_time < processes[shortest].remaining_time) {
                    shortest = i;
                }
            }
        }

        if (shortest == -1) {
            time++;
        } else {
            processes[shortest].remaining_time--;
            if (processes[shortest].remaining_time == 0) {
                processes[shortest].turnaround_time = time + 1 - processes[shortest].arrival_time;
                processes[shortest].waiting_time = processes[shortest].turnaround_time - processes[shortest].burst_time;
                total_waiting_time += processes[shortest].waiting_time;
                total_turnaround_time += processes[shortest].turnaround_time;
                completed++;
                printf("Process %d: Waiting Time = %d, Turnaround Time = %d\n",
                       processes[shortest].process_id, processes[shortest].waiting_time, processes[shortest].turnaround_time);
            }
            time++;
        }
    }

    float average_waiting_time = (float)total_waiting_time / n;
    float average_turnaround_time = (float)total_turnaround_time / n;
    float throughput = (float)n / time;
    float cpu_utilization = ((float)total_burst_time / time) * 100;

    printf("Throughput: %.2f\n", throughput);
    printf("CPU Utilization: %.2f%%\n", cpu_utilization);
    printf("Average Waiting Time: %.2f\n", average_waiting_time);
    printf("Average Turnaround Time: %.2f\n", average_turnaround_time);
}

// Function to simulate Priority Scheduling
void PriorityScheduling(Process processes[], int n) {
    int time = 0, completed = 0, total_waiting_time = 0, total_turnaround_time = 0;
    int total_burst_time = 0;
    bool completed_processes[n];

    printf("\n--- Priority Scheduling ---\n");
    for (int i = 0; i < n; i++) {
        completed_processes[i] = false;
        total_burst_time += processes[i].burst_time;
    }

    while (completed < n) {
        int highest_priority = -1;
        for (int i = 0; i < n; i++) {
            if (!completed_processes[i] && processes[i].arrival_time <= time) {
                if (highest_priority == -1 || processes[i].priority < processes[highest_priority].priority) {
                    highest_priority = i;
                }
            }
        }

        if (highest_priority == -1) {
            time++;
        } else {
            processes[highest_priority].waiting_time = time - processes[highest_priority].arrival_time;
            time += processes[highest_priority].burst_time;
            processes[highest_priority].turnaround_time = time - processes[highest_priority].arrival_time;
            total_waiting_time += processes[highest_priority].waiting_time;
            total_turnaround_time += processes[highest_priority].turnaround_time;
            completed_processes[highest_priority] = true;
            completed++;
            printf("Process %d: Waiting Time = %d, Turnaround Time = %d\n",
                   processes[highest_priority].process_id, processes[highest_priority].waiting_time, processes[highest_priority].turnaround_time);
        }
    }

    float average_waiting_time = (float)total_waiting_time / n;
    float average_turnaround_time = (float)total_turnaround_time / n;
    float throughput = (float)n / time;
    float cpu_utilization = ((float)total_burst_time / time) * 100;

    printf("Throughput: %.2f\n", throughput);
    printf("CPU Utilization: %.2f%%\n", cpu_utilization);
    printf("Average Waiting Time: %.2f\n", average_waiting_time);
    printf("Average Turnaround Time: %.2f\n", average_turnaround_time);
}

// Function to simulate Round Robin scheduling
void RoundRobin(Process processes[], int n, int quantum) {
    int time = 0, completed = 0, total_waiting_time = 0, total_turnaround_time = 0;
    int total_burst_time = 0;

    printf("\n--- Round Robin Scheduling ---\n");
    for (int i = 0; i < n; i++) {
        total_burst_time += processes[i].burst_time;
        processes[i].remaining_time = processes[i].burst_time;
    }

    while (completed < n) {
        bool did_process = false;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= time && processes[i].remaining_time > 0) {
                did_process = true;
                if (processes[i].remaining_time > quantum) {
                    time += quantum;
                    processes[i].remaining_time -= quantum;
                } else {
                    time += processes[i].remaining_time;
                    processes[i].waiting_time = time - processes[i].arrival_time - processes[i].burst_time;
                    processes[i].turnaround_time = time - processes[i].arrival_time;
                    total_waiting_time += processes[i].waiting_time;
                    total_turnaround_time += processes[i].turnaround_time;
                    processes[i].remaining_time = 0;
                    completed++;
                    printf("Process %d: Waiting Time = %d, Turnaround Time = %d\n",
                           processes[i].process_id, processes[i].waiting_time, processes[i].turnaround_time);
                }
            }
        }
        if (!did_process) time++;
    }

    float average_waiting_time = (float)total_waiting_time / n;
    float average_turnaround_time = (float)total_turnaround_time / n;
    float throughput = (float)n / time;
    float cpu_utilization = ((float)total_burst_time / time) * 100;

    printf("Throughput: %.2f\n", throughput);
    printf("CPU Utilization: %.2f%%\n", cpu_utilization);
    printf("Average Waiting Time: %.2f\n", average_waiting_time);
    printf("Average Turnaround Time: %.2f\n", average_turnaround_time);
}

int main() {
    int n, time_quantum, choice;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process processes[n];

    //Taking priority values irrespective of the process you choose
    for (int i = 0; i < n; i++) {
        printf("Enter arrival time, burst time, and priority for process %d: ", i + 1);
        scanf("%d %d %d", &processes[i].arrival_time, &processes[i].burst_time,
        &processes[i].priority);
        processes[i].process_id = i + 1;
        processes[i].remaining_time = processes[i].burst_time;
    }

    printf("\nChoose Scheduling Algorithm:\n");
    printf("1. FCFS\n");
    printf("2. SJF\n");
    printf("3. SRTF\n");
    printf("4. Priority Scheduling\n");
    printf("5. Round Robin\n");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            FCFS(processes, n);
            break;
        case 2:
            SJF(processes, n);
            break;
        case 3:
            SRTF(processes, n);
            break;
        case 4:
            PriorityScheduling(processes, n);
            break;
        case 5:
            printf("Enter time quantum for Round Robin: ");
            scanf("%d", &time_quantum);
            RoundRobin(processes, n, time_quantum);
            break;
        default:
            printf("Invalid choice!\n");
            break;
    }

    return 0;
}
