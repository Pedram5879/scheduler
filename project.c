#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char task_type;
    int execution_time;
    char state[10];
    int time_on_processor;
} Task;

int resources_R1, resources_R2, resources_R3;

Task ready_queue[100];
int ready_queue_size = 0;
Task waiting_queue[100];
int waiting_queue_size = 0;

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
