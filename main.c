#define ﻿_CRT_SECURE_NO_DEPRECATE
#include <locale.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double f(double x);
double calculate_point_value(double x);
double create_value_table(double a, double b, double step);
double find_min_max(double a, double b, double* min_res, double* max_res);
double find_x_for_y(double y, double a, double b, double* result_x);
double derivative(double x);

int main() {
    setlocale(LC_CTYPE, "");
    int num;
    int result;
    do {
        printf("\n===--> МЕНЮ <--===\n");
        printf("1. Значение f(x) в точке\n");
        printf("2. Таблица значений\n");
        printf("3. Минимум и максимум на отрезке\n");
        printf("4. Найти x, если f(x) = Y\n");
        printf("5. Производная f'(x)\n");
        printf("0. Выход\n");
        printf("Выберите пункт: ");
        scanf("%d", &num);

        switch (num) {
        case 1: {
            double x;
            printf("Введите x: ");
            scanf("%lf", &x);
            double result = calculate_point_value(x);
            if (result == result) {
                printf("f(%.3f) = %.6f\n", x, result);
            }
        }
            break;
        case 2: {
            double a, b, x;
            double step;
            printf("Введите начало: ");
            scanf("%lf", &a);
            printf("Введите конец: ");
            scanf("%lf", &b);
            printf("Введите шаг: ");
            scanf("%lf", &step);

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

            result = find_x_for_y(y, a, b, &found_x);
            
            if (result == -1) {
                printf("Ошибка! Необходимо a < b!\n");
            }
            else if (result == 0) {
                printf("Решение не найдено\n");
            }
            else {
                printf("Приблизительно: x = %.3f, f(x) = %.3f\n", found_x, f(found_x));
                printf("Всего найдено решений: %d\n", result);
            }
            break;
        }
        case 5: {
            double x;
            printf("Введите x: ");
            scanf("%lf", &x);
            if ((x >= 3 && (2 * x + 3) <= 0) || (x > -2 && x <= 3 && (1 + x * x * x) < 0)) {
                printf("Функция не определена в точке х = %.3f\n", x);
            }
            else {
                double deriv = derivative(x);
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
    if (x <= -2)
        return (cos(2 * x) - 1) / (x * x);
    else if (x <= 3)
        return x * exp(-x / 2.0) + pow(1 + x * x * x, 0.25);
    else
        return log(2 * x + 3) * (pow(x, 4) - 2 * pow(x, 2) + x - 1);
}

double calculate_point_value(double x) {
    if (x >= 3 && (2 * x + 3) <= 0) {
        printf("Ошибка: под логарифмом должно быть > 0!\n");
        return NAN;
    }
    else if (x >= -2 && x < 3 && (1 + x * x * x) < 0) {
        printf("Ошибка: под корнем должно быть >= 0!\n");

    }
    else {
        return f(x);
    }
}

double create_value_table(double a, double b, double step) {
    if (step <= 0) {
        printf("Шаг должен быть > 0!\n");
        return;
    }
    if (a > b) {
        printf("Ошибка! Необходимо a < b!\n");
        return;
    }
    printf("\nТаблица значений:\n");
    printf("------------------------------\n");
    printf("|     x     |      f(x)      |\n");
    printf("------------------------------\n");

    for (double x = a; x <= b; x += step) {
        if (x > -2 && x <= 3 && (1 + x * x * x) < 0) {
            printf("| %9.3f |     Ошибка    |\n", x);
        }
        else if (x > 3 && (2 * x + 3) <= 0) {
            printf("| %9.3f |     Ошибка    |\n", x, f(x));
        }
        else {
            printf("| %9.3f | %14.6f |\n", x, f(x));
        }
    }
    printf("------------------------------\n");
}

double find_min_max(double a, double b, double *min_res, double *max_res) {
    if (a > b) {
        return -1;
    }
    int found = 0;
    double min, max;

    for (double x = a; x <= b; x += 0.1) {
        double fx = f(x);
        if (fx == fx) { //NaN
            if (!found) {
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
    }
    return found;
}

double find_x_for_y(double y, double a, double b, double *result_x) {
    if (a > b) {
        return;
    }
    int solution_found = 0;
    for (double x = a; x <= b; x += 0.001) {
        if (x >= 3 && (2 * x + 3) <= 0) continue;
        if (x > -2 && x <= 3 && (1+x*x*x) < 0) continue;
        if (fabs(f(x) - y) < 0.001) {
            *result_x = x;
            solution_found++;
            break;
        }
    }
    return solution_found;
}

double derivative(double x) {
    double h = 1e-5;
    return (f(x + h) - f(x - h)) / (2 * h);
}
