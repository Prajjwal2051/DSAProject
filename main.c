#include "scheduler.h"
#include <stdio.h>

int main() {
    TaskScheduler scheduler;
    initScheduler(&scheduler);
    
    printf("\n");
    printf("  ==================================================\n");
    printf("                                                    \n");
    printf("        WELCOME TO TASK SCHEDULER SYSTEM           \n");
    printf("                                                    \n");
    printf("         Data Structures & Algorithms              \n");
    printf("              Laboratory Project                   \n");
    printf("                                                    \n");
    printf("  ==================================================\n");
    printf("\n  Press Enter to start...");
    getchar();
    
    runScheduler(&scheduler);
    
    return 0;
}
