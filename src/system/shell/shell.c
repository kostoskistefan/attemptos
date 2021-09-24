#include "shell.h"

void execute(char* command)
{
    if(strcmp(command, "") == 0)
    {
        print("\n> ");
        return;
    }
        
    if (strcmp(command, "exit") == 0) {
        printf("%s", "Stopping the CPU. Exiting...");
        asm volatile("hlt");
    }

    else if (strcmp(command, "clear") == 0) {
        clear_screen();
    }

    else if (contains(command, "echo")) {
        print(command);
    }

    else printf("Command not recognized: %s", command);

    print("\n> ");
}