#include "error_message.h"

void error_message(error err) {
    switch (err) {
        case INCORRECT_DATA:
            printf("Ошибка: некорректные данные!");
            break;

        case INPUT_ERROR:
            printf("Ошибка: ошибка ввода!");
            break;

        case CALCULATE_ERROR:
            printf("Ошибка: вычисления выполнены некорректно!");
            break;

        case MEMORY_ERROR:
            printf("Ошибка: ошибка при работе с памятью!");
            break;

        case SUCCESS:
            break;

        default:
            printf("Ошибка!");
            break;
    }
}
