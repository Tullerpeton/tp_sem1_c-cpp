#include "Errors/error_message.h"
#include "Task_manager/task_manager.h"

int main() {
    error err = task_manager();
    if (err)
        error_message(err);

    return err;
}
