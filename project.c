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

int main() {
    return 0;
}
