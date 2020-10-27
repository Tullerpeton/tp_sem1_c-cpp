#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include "Config/configuration.h"
#include "Task_manager/task_manager.h"
#include "Errors/error_message.h"


struct option options[] = {
        { "help",      no_argument,       NULL,           'h' },
        { "parallel",  required_argument, NULL,           'p' },
        { "input",     required_argument, NULL,           'i' },
        { "size_arr",  required_argument, NULL,           's' },
        { NULL,        0,                 NULL,            0  }
};

int main(int argc, char** argv) {
    // Default settings
    task new_task;
    strcpy(new_task.input, STDIN);
    new_task.size_array = SIZE_ARRAY;
    new_task.is_parallel = IS_PARALLEL;

    // Parse options
    int c, opt_index;
    while ((c = getopt_long(argc, argv, "-:hpi:s:", options, &opt_index)) != -1) {
        switch (c) {

            case 1:
                printf("Non-option argument %s\n", optarg);
                break;

            case 'h':
                printf("Usage: %s [--help|--parallel|--input <filename>|"
                       "|--size_array <size>|]\n", argv[0]);
                break;

            case 'i':
                strcpy(new_task.input, optarg);
                break;

            case 'p':
                new_task.is_parallel = 1;
                break;

            case 's':
                new_task.size_array = atoi(optarg);
                break;

            case '?':
                printf("Unknown option %c\n", optopt);
                break;

            case ':':
                printf("Missing argument for %c\n", optopt);
                break;

            default:
                break;
        }
    }

    // Main logic
    error err = task_manager(&new_task);
    if (err)
        error_message(err);

    return err;
}
