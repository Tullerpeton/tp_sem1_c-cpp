#include "gtest/gtest.h"
#include "Errors/error_code.h"
#include "Algorithm_calculate_sum/sequential_sum.h"
#include "Algorithm_calculate_sum/parallel_sum.h"
#include "Task_manager/task_manager.h"
#include "Algorithm_calculate_sum/my_math.h"
#include "File/bin_file_routines.h"

// Static lib
TEST(static_lib, calculate_sequential_sum_array) {
    {
        // Data is missing
        char filename[MAX_LEN_FILE_NAME] = "Set_tests/empty.bin";
        int64_t sum = 0;
        EXPECT_EQ(calculate_sequential_sum_array(&sum, 0, filename), SUCCESS);
        EXPECT_EQ(sum, 0);
    }

    {
        // Pointer sum = NULL
        char filename[MAX_LEN_FILE_NAME] = "Set_tests/empty.bin";
        int64_t* sum = NULL;
        EXPECT_EQ(calculate_sequential_sum_array(sum, 0, filename), INCORRECT_DATA);
    }

    {
        // File name = NULL
        char* filename = NULL;
        int64_t sum = 0;
        EXPECT_EQ(calculate_sequential_sum_array(&sum, 0, filename), INCORRECT_DATA);
    }

    {
        // Base case
        char filename[MAX_LEN_FILE_NAME] = "Set_tests/10.bin";
        int64_t sum = 0;
        EXPECT_EQ(calculate_sequential_sum_array(&sum, 10, filename), SUCCESS);
        EXPECT_EQ(sum, 72632);
    }

    {
        // Incorrect filename
        char filename[MAX_LEN_FILE_NAME] = "Set_tests/incorrect_filename.bin";
        int64_t sum = 0;
        EXPECT_EQ(calculate_sequential_sum_array(&sum, 100, filename), INCORRECT_DATA);
    }
}

// Shared lib
TEST(shared_lib, calculate_parallel_sum_array) {
    {
        // Data is missing
        char filename[MAX_LEN_FILE_NAME] = "Set_tests/empty.bin";
        int64_t sum = 0;
        EXPECT_EQ(calculate_parallel_sum_array(&sum, 0, filename), SUCCESS);
        EXPECT_EQ(sum, 0);
    }

    {
        // Pointer sum = NULL
        char filename[MAX_LEN_FILE_NAME] = "Set_tests/empty.bin";
        int64_t* sum = NULL;
        EXPECT_EQ(calculate_parallel_sum_array(sum, 0, filename), INCORRECT_DATA);
    }

    {
        // File descriptor = NULL
        char* filename = NULL;
        int64_t sum = 0;
        EXPECT_EQ(calculate_parallel_sum_array(&sum, 0, filename), INCORRECT_DATA);
    }

    {
        // Base case
        char filename[MAX_LEN_FILE_NAME] = "Set_tests/10.bin";
        int64_t sum = 0;
        EXPECT_EQ(calculate_parallel_sum_array(&sum, 10, filename), SUCCESS);
        EXPECT_EQ(sum, 72632);
    }

    {
        // Incorrect filename
        char filename[MAX_LEN_FILE_NAME] = "Set_tests/incorrect_filename.bin";
        int64_t sum = 0;
        EXPECT_EQ(calculate_parallel_sum_array(&sum, 100, filename), INCORRECT_DATA);
    }
}

TEST(shared_lib, init_threads) {
    {
        // Base case
        thread_args args[3];
        char filename[MAX_LEN_FILE_NAME] = "Set_tests/10.bin";
        EXPECT_EQ(init_threads(args, 3, 1, filename), SUCCESS);
    }

    {
        // Size array < 1
        thread_args args[3];
        char filename[MAX_LEN_FILE_NAME] = "Set_tests/10.bin";
        EXPECT_EQ(init_threads(args, 3, 0, filename), INCORRECT_DATA);
    }

    {
        // Count threads < 1
        thread_args args[3];
        char filename[MAX_LEN_FILE_NAME] = "Set_tests/10.bin";
        EXPECT_EQ(init_threads(args, 0, 3, filename), INCORRECT_DATA);
    }

    {
        // File name = NULL
        thread_args args[3];
        char* filename = NULL;
        EXPECT_EQ(init_threads(args, 3, 3, filename), INCORRECT_DATA);
    }

    {
        // Args = NULL
        thread_args* args = NULL;
        char filename[MAX_LEN_FILE_NAME] = "Set_tests/10.bin";
        EXPECT_EQ(init_threads(args, 3, 3, filename), INCORRECT_DATA);
    }

    {
        // Incorrect file name
        thread_args args[3];
        char filename[MAX_LEN_FILE_NAME] = "Set_tests/incorrect_filename.bin";
        EXPECT_EQ(init_threads(args, 3, 3, filename), INCORRECT_DATA);
    }
}

TEST(shared_lib, run_threads) {
    {
        // Threads pointer = NULL
        thread_args args[3];
        pthread_t* threads = NULL;
        EXPECT_EQ(run_threads(threads, args, 3), INCORRECT_DATA);
    }

    {
        // Args pointer = NULL
        thread_args* args = NULL;
        pthread_t threads[3];
        EXPECT_EQ(run_threads(threads, args, 3), INCORRECT_DATA);
    }

    {
        // Threads count < 1
        thread_args args[3];
        pthread_t threads[3];
        EXPECT_EQ(run_threads(threads, args, 0), INCORRECT_DATA);
    }
}

TEST(shared_lib, wait_threads) {
    {
        // Threads count < 1
        int64_t sum = 0;
        thread_args args[3];
        EXPECT_EQ(get_result_sum_threads(&sum, args, 0), INCORRECT_DATA);
    }

    {
        // Sum pointer = NULL
        int64_t* sum = NULL;
        thread_args args[3];
        EXPECT_EQ(get_result_sum_threads(sum, args, 3), INCORRECT_DATA);
    }

    {
        // Args pointer = NULL
        int64_t sum = 0;
        thread_args* args = NULL;
        EXPECT_EQ(get_result_sum_threads(&sum, args, 3), INCORRECT_DATA);
    }
}

TEST(shared_lib, get_result_sum_threads) {
    {
        // Threads pointer = NULL
        pthread_t* threads = NULL;
        EXPECT_EQ(wait_threads(threads, 3), INCORRECT_DATA);
    }

    {
        // Threads count < 1
        pthread_t threads[3];
        EXPECT_EQ(wait_threads(threads, 0), INCORRECT_DATA);
    }
}

TEST(shared_lib, get_number_CPU) {
    {
        EXPECT_EQ(get_number_CPU() > 0, true);
    }
}

// My math module
TEST(my_math, add_num) {
    {
        // Overflow
        int64_t sum = INT64_MAX;
        int num = 1;
        EXPECT_EQ(add_num(&sum, num), OVERFLOW_ERROR);
    }

    {
        // Base case
        int64_t sum = 1;
        int num = 1;
        EXPECT_EQ(add_num(&sum, num), SUCCESS);
    }
}

// Task manager module
TEST(task_manager, task_manager) {
    {
        task* new_task = NULL;
        EXPECT_EQ(task_manager(new_task), INCORRECT_DATA);
    }

    {
        // Sequential mode
        task new_task;
        strcpy(new_task.input, "Set_tests/10.bin");
        new_task.size_array = 10;
        new_task.is_parallel = 0;
        EXPECT_EQ(task_manager(&new_task), SUCCESS);
    }

    {
        // Parallel mode
        task new_task;
        strcpy(new_task.input, "Set_tests/10.bin");
        new_task.size_array = 10;
        new_task.is_parallel = 1;
        EXPECT_EQ(task_manager(&new_task), SUCCESS);
    }
}

// Bin file routines module
TEST(bin_file_routines, get_int_by_position) {
    {
        // Num pointer = NULL
        int* num = NULL;
        FILE* file = fopen("Set_tests/10.bin", "rb");
        EXPECT_EQ(get_int_by_position(num, 0, file), INCORRECT_DATA);
        fclose(file);
    }

    {
        // File descriptor = NULL
        int num = 0;
        FILE* file = NULL;
        EXPECT_EQ(get_int_by_position(&num, 0, file), INCORRECT_DATA);
    }

    {
        // Base case
        int num;
        FILE* file = fopen("Set_tests/10.bin", "rb");
        EXPECT_EQ(get_int_by_position(&num, 0, file), SUCCESS);
        fclose(file);
    }
}