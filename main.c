#define ﻿_CRT_SECURE_NO_DEPRECATE

#include <locale.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>


double f(double x);
double calculate_point_value(double x);
void create_value_table(double a, double b, double step);
int find_min_max(double a, double b, double* min_res, double* max_res);
int find_x_for_y(double y, double a, double b, double* result_x);
double derivative(double x);

int main() {
    setlocale(LC_CTYPE, "RUS");
    printf("Программа для работы с функцией f(x)\nВыполнил: Чумачек Владислав бИЦ-252\n");
    int num;
    double result;
    do {
        printf("\n===--> МЕНЮ <--===\n");
        printf("1. Значение f(x) в точке\n");
        printf("2. Таблица значений\n");
        printf("3. Минимум и максимум на отрезке\n");
        printf("4. Найти x по значению Y\n");
        printf("5. Производная f'(x)\n");
        printf("0. Выход\n");
        printf("Выберите пункт: ");
        scanf("%d", &num);

        switch (num) {
        case 1: {
            double x;
            printf("Введите x: ");
            scanf("%lf", &x);
            result = calculate_point_value(x);
            if (!isnan(result)) {
                printf("\nОтвет с точностью до 6 знаков:\n");
                printf("f(%.3f) = %.6f\n", x, result);
            }
            else {
                printf("Функция не определена в точке x = %.3f\n", x);
            }
            break;
        }
        case 2: {
            double a, b, x;
            double step;
            printf("Введите начало: ");
            scanf("%lf", &a);
            printf("Введите конец: ");
            scanf("%lf", &b);
            printf("Введите шаг: ");
            scanf("%lf", &step);

            if (step <= 0) {
                printf("Шаг должен быть > 0!\n");
                return;
            }
            if (a > b) {
                printf("Ошибка! Необходимо a < b!\n");
                return;
            }

            create_value_table(a, b, step);
            break;
        }
        case 3: {
            double a, b, min, max;
            printf("Введите начало отрезка: ");
            scanf("%lf", &a);
            printf("Введите конец отрезка: ");
            scanf("%lf", &b);

            result = find_min_max(a, b, &min, &max);

            if (result == -1) {
                printf("Ошибка! Необходимо a < b!\n");
            }
            else if (result == 0) {
                printf("Функция не определена на этом отрезке\n");
            }
            else {
                printf("\nМинимум (Min) = %.6f\n", min);
                printf("Максимум (Max) = %.6f\n", max);
            }
            break;
        }
        case 4: {
            double y, a, b, found_x;
       
            printf("Введите 'Y': ");
            scanf("%lf", &y);
            printf("Введите диапазон поиска (a и b): ");
            scanf("%lf %lf", &a, &b);

            int result = find_x_for_y(y, a, b, &found_x);
            
            if (result == -1) {
                printf("\nОшибка! Необходимо a < b!\n");
            }
            else if (result == 0) {
                printf("\nРешений не найдено в данном диапазоне\n");
            }
            else {
                printf("\nПриблизительно: x = %.6f\n", found_x);
            }
            break;
        }
        case 5: {
            double x;
            printf("Введите x: ");
            scanf("%lf", &x);
            
            double deriv = derivative(x);
            if (isnan(deriv)) {
                printf("Производная не существует.\n");
            }
            else if (isinf(deriv)) {
                printf("Производная бесконечна");
            }
            else {
                printf("f'(%.3f) = %.6f\n", x, deriv);
            }
            break;
        }
        case 0:
            printf("Выход из программы.\n");
            break;
        default:
            printf("Неверный пункт меню.\n");
        }
    } while (num != 0);

    system("pause");
    return 0;
};

double f(double x) {
    if (x < -2.0) {
        return (cos(2.0 * x) - 1.0) / (x * x);
    }
    else if (x >= -2.0 && x < 3.0) {
        return x * exp(-x / 2.0) + pow(1.0 + x * x * x, 0.25);
    }
    else { // x >= 3
        return log(2.0 * x + 3.0) *
            (pow(x, 4.0) - 2.0 * pow(x, 2.0) + x - 1.0);
    }
}

double calculate_point_value(double x) {
    // 1. Проверка корня 4-й степени для второго куска
    if (x >= -2.0 && x < 3.0 && (1.0 + x * x * x) < 0.0) {
        return NAN;  // Корень из отрицательного числа
    }

    // 2. Проверка деления на 0 в первом куске
    if (x < -2.0 && fabs(x) < 1e-10) {
        return NAN;  // Деление на 0 
    }

    return f(x);  // Вычисляем значение
}

void create_value_table(double a, double b, double step) {
    printf("\nТаблица значений:\n");
    printf("------------------------------\n");
    printf("|     x     |      f(x)      |\n");
    printf("------------------------------\n");

    for (double x = a; x <= b + step / 2.0; x += step) {
        // Проверка области определения
        if (x >= -2.0 && x < 3.0) {
            if ((1.0 + x * x * x) < 0.0) {
                printf("|%11.3f|  НЕ ОПРЕДЕЛЕНО |\n", x);
                continue;
            }
        }
    double result = calculate_point_value(x);
        if (isnan(result)) {
            printf("|%11.3f|  НЕ ОПРЕДЕЛЕНО |\n", x);
        }
        else if (isinf(result)) {
            printf("|%11.3f|  БЕСКОНЕЧНО    |\n", x);
        }
        else {
            printf("|%11.3f| %14.6f |\n", x, result);
        }
    }

    printf("------------------------------\n");
}

int find_min_max(double a, double b, double *min_res, double *max_res) {
    if (a > b) {
        return -1;
    }
    int found = 0;
    double min, max;
    double step = 0.001;
    for (double x = a; x <= b + step/2.0; x += step) {
        double fx = calculate_point_value(x);

        // Проверяем, что значение определено и конечно
        if (!isnan(fx) && !isinf(fx)) {
            if (!found) {
                // Первое найденное значение
                min = max = fx;
                found = 1;
            }
            else {
                if (fx < min) min = fx;
                if (fx > max) max = fx;
            }
        }
    }

    if (found) {
        *min_res = min;
        *max_res = max;
        return 1;
    }
    return 0;
}

int find_x_for_y(double y, double a, double b, double* result_x) {
    if (a > b) {
        return -1;
    }
    double step = 0.000001;
    for (double x = a; x <= b + step / 2.0; x += step) {
        if (x >= -2.0 && x < 3.0 && (1.0 + x * x * x) < 0.0) {
            continue;
        }

        double fx = f(x);

        if (isnan(fx) || isinf(fx)) {
            continue;
        }
        if (fabs(fx - y) < step) {
            *result_x = x;
            return 1;
        }
    }
    return 0;
}

double derivative(double x) {
    double h = 1e-5;

    double fx_plus = calculate_point_value(x + h);
    double fx_minus = calculate_point_value(x - h);
    if (isnan(fx_plus) || isnan(fx_minus) || isinf(fx_plus) || isinf(fx_minus)) {
        return NAN;
    }
    return (fx_plus - fx_minus) / (2 * h);
}
