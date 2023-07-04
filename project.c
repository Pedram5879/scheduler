#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char task_name[10];
    char task_type;
    int execution_time;
    char state[10];
    int time_on_processor;
} Task;

int resources_R1, resources_R2, resources_R3;

Task ready_queue[100];      // Ready queue for tasks ready to be executed (priority queue)
Task priority_queue[100];   // priority queue
int priority_queue_size = 0; 
int ready_queue_size = 0;
Task waiting_queue[100];    // Waiting queue for tasks with unmet resource requirements
int waiting_queue_size = 0;
int check_resource_availability(Task task) {
    if (task.task_type == 'X' && resources_R1 >= 1 && resources_R2 >= 1)
        return 1;
    else if (task.task_type == 'Y' && resources_R2 >= 1 && resources_R3 >= 1)
        return 1;
    else if (task.task_type == 'Z' && resources_R1 >= 1 && resources_R3 >= 1)
        return 1;
    else
        return 0;
}

void allocate_resources(Task task) {
    if (task.task_type == 'X') {
        resources_R1 -= 1;
        resources_R2 -= 1;
    }
    else if (task.task_type == 'Y') {
        resources_R2 -= 1;
        resources_R3 -= 1;
    }
    else if (task.task_type == 'Z') {
        resources_R1 -= 1;
        resources_R3 -= 1;
    }
}

void deallocate_resources(Task task) {
    if (task.task_type == 'X') {
        resources_R1 += 1;
        resources_R2 += 1;
    }
    else if (task.task_type == 'Y') {
        resources_R2 += 1;
        resources_R3 += 1;
    }
    else if (task.task_type == 'Z') {
        resources_R1 += 1;
        resources_R3 += 1;
    }
}

void update_task_states() {
    int i, j;

    // Check tasks in the waiting queue and allocate resources if available
    for (i = 0; i < waiting_queue_size; i++) {
        Task task = waiting_queue[i];
        if (check_resource_availability(task)) {
            strcpy(task.state, "READY");     // Change state to READY
            allocate_resources(task);        // Allocate resources
            ready_queue[ready_queue_size++] = task; // Add the task to the ready queue
            // Remove the task 
            for (j = i; j < waiting_queue_size - 1; j++) {
                waiting_queue[j] = waiting_queue[j + 1];
            }
            waiting_queue_size--;
            i--;
        }
    }

    for (i = 0; i < ready_queue_size; i++) {
        Task *task = &ready_queue[i];
        if (task->execution_time == task->time_on_processor) {
            strcpy(task->state, "COMPLETED");   // Task execution complete
            deallocate_resources(*task);        // Deallocate resources
            // Remove the task from the ready queue by shifting remaining tasks
            for (j = i; j < ready_queue_size - 1; j++) {
                ready_queue[j] = ready_queue[j + 1];
            }
            ready_queue_size--;
            i--; // Adjust the loop index since the current task is removed
        }
        else if (!check_resource_availability(*task)) {
            strcpy(task->state, "WAITING");     // Required resources not available
            // Remove the task
            for (j = i; j < ready_queue_size - 1; j++) {
                ready_queue[j] = ready_queue[j + 1];
            }
            ready_queue_size--;
            waiting_queue[waiting_queue_size++] = *task; // Add the task to the waiting queue
            i--;
        }
        else {
            strcpy(task->state, "RUNNING");     // Task is currently running on the processor
            task->time_on_processor += 1;
        }
    }
}

void sort_ready_queue(char scheduling_algorithm) {
    int i, j;
    Task temp;

    if (scheduling_algorithm == 'S') { // Shortest-Job-First (SJF)
        for(i = 0; i < ready_queue_size - 1; i++) {
            for(j = 0; j < ready_queue_size - i - 1; j++) {
                if(ready_queue[j].execution_time > ready_queue[j+1].execution_time) {
                    temp = ready_queue[j];
                    ready_queue[j] = ready_queue[j+1];
                    ready_queue[j+1] = temp;
                    printf("ready_queue[j+1].task_name : %c", ready_queue[j+1].task_name);
                }
            }
        }
    }
     // First-Come-First-Serve (FCFS)
     // No need to sort the ready queue for FCFS

    // Add implementation for Round-Robin scheduling algorithm
    if (scheduling_algorithm == 'R') { // Round-Robin
        int quantum;
        printf("Enter the quantum: ");
        scanf("%d", &quantum);
        if(quantum > 0){
            int i;
            int threshold = ready_queue_size * 0.8;

            int current_process = 0;
            while (ready_queue_size > 0) {
                if (ready_queue[current_process].execution_time <= quantum) {
                    // Process completed within this time slice
                    printf("Process %d completed.\n", ready_queue[current_process].task_type);
                    ready_queue_size--;
                    current_process = (current_process + 1) % ready_queue_size;
                } else {
                    // Process still needs more time
                    printf("Allocating quantum %d to process %d.\n", quantum, ready_queue[current_process].task_type);
                    ready_queue[current_process].execution_time -= quantum;
                    current_process = (current_process + 1) % ready_queue_size;
                }
            }
        }
        
    }

}

int main() {
    int initial_R1, initial_R2, initial_R3;
    char scheduling_algorithm;
    int num_tasks;

    printf("Enter the initial number of resources R1: ");
    scanf("%d", &initial_R1);
    printf("Enter the initial number of resources R2: ");
    scanf("%d", &initial_R2);
    printf("Enter the initial number of resources R3: ");
    scanf("%d", &initial_R3);
    
    scanf("%c", &scheduling_algorithm); //read a \n
    
    printf("Enter the scheduling algorithm (S for SJF, F for FCFS, R for RR): ");
    scanf("%c", &scheduling_algorithm);
    
    
    printf("Enter the number of tasks to be scheduled: ");
    scanf("%d", &num_tasks);
    
    // Initialize the system resources
    resources_R1 = initial_R1;
    resources_R2 = initial_R2;
    resources_R3 = initial_R3;

    int i;
    for (i = 0; i < num_tasks; i++) {
        Task new_task;
        printf("Enter task name: ");
        scanf("%s", new_task.task_name);
        printf("new_task.task_name : %s \n", new_task.task_name);
        printf("Enter task type (X, Y, or Z): ");
        fflush(stdin);
        scanf(" %c", &new_task.task_type);
        printf("Enter task execution time: ");
        scanf("%d", &new_task.execution_time);
        strcpy(new_task.state, "READY");
        new_task.time_on_processor = 0;
        priority_queue[priority_queue_size++] = new_task;
    }
    
    printf("ready_queue_size : %d", ready_queue_size );
    
    sort_ready_queue(scheduling_algorithm);
    
    for (int i = 0; i <= ready_queue_size-1; i++) {
        priority_queue[i] = ready_queue[i];
    }

    
    return 0;
}
