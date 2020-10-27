#include "gtest/gtest.h"
#include "Algorithm_calculate_sum/sequential_sum.h"
#include "Algorithm_calculate_sum/parallel_sum.h"

TEST(stress_test, stress_test) {
    {
        // File = 10 nums
        int64_t sum1 = 0, sum2 = 0;
        char filename[MAX_LEN_FILE_NAME] = "Set_tests/10.bin";
        EXPECT_EQ(calculate_sequential_sum_array(&sum1, 10, filename), SUCCESS);
        EXPECT_EQ(calculate_parallel_sum_array(&sum2, 10, filename), SUCCESS);
        EXPECT_EQ(sum1, sum2);
    }

    {
        // File = 500 nums
        int64_t sum1 = 0, sum2 = 0;
        char filename[MAX_LEN_FILE_NAME] = "Set_tests/500.bin";
        EXPECT_EQ(calculate_sequential_sum_array(&sum1, 500, filename), SUCCESS);
        EXPECT_EQ(calculate_parallel_sum_array(&sum2, 500, filename), SUCCESS);
        EXPECT_EQ(sum1, sum2);
    }

    {
        // File = 10 000 nums
        int64_t sum1 = 0, sum2 = 0;
        char filename[MAX_LEN_FILE_NAME] = "Set_tests/10_000.bin";
        EXPECT_EQ(calculate_sequential_sum_array(&sum1, 10000, filename), SUCCESS);
        EXPECT_EQ(calculate_parallel_sum_array(&sum2, 10000, filename), SUCCESS);
        EXPECT_EQ(sum1, sum2);
    }
}