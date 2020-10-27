#include "error_message.h"

void error_message(error err) {
    switch (err) {
        case INCORRECT_DATA:
            printf("Ошибка: некорректные данные!");
            break;

        case INPUT_ERROR:
            printf("Ошибка: ошибка ввода!");
            break;

        case RUN_THREADS_ERROR:
            printf("Ошибка: ошибка при запуске потоков!");
            break;

        case JOIN_THREADS_ERROR:
            printf("Ошибка: ошибка при ожидании завершения потоков!");
            break;

        case OVERFLOW_ERROR:
            printf("Ошибка: в результате вычислений произошло переполнение!");
            break;

        case SUCCESS:
            break;

        default:
            printf("Ошибка!");
            break;
    }
}
