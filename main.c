#include <locale.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double f(double x);
double derivative(double x);
void calculate_point_value();
void create_value_table();
void find_min_max();
void find_x_for_y();
void calculate_derivative();


int main() {
    setlocale(LC_CTYPE, "");
    int num;

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
        case 1:
            calculate_point_value();
            break;
        case 2:
            create_value_table();
            break;
        case 3:
            find_min_max();
            break;
        case 4:
            find_x_for_y();
            break;
        case 5:
            calculate_derivative();
            break;
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

double derivative(double x) {
    double h = 1e-5;
    return (f(x + h) - f(x - h)) / (2 * h);
}

void calculate_point_value() {
    double x;
    printf("Введите x: ");
    scanf("%lf", &x);

    if (x >= 3 && (2 * x + 3) <= 0) {
        printf("Ошибка: под логарифмом должно быть > 0!\n");
    }
    else if (x >= -2 && x < 3 && (1 + x * x * x) < 0) {
        printf("Ошибка: под корнем должно быть >= 0!\n");
    }
    else {
        double fx = f(x);
        printf("f(%.3f) = %.6f\n", x, fx);
    }
}


void create_value_table() {
    double a, b, x;
    double step;
    printf("Введите начало: ");
    scanf("%lf", &a);
    printf("Введите конец: ");
    scanf("%lf", &b);
    printf("Введите шаг: ");
    scanf("%lf", &step);

    printf("\nТаблица значений:\n");
    printf("------------------------------\n");
    printf("|     x     |      f(x)      |\n");
    printf("------------------------------\n");

    for (x = a; x <= b; x += step) {
        if (x >= 3 && (2 * x + 3) <= 0) {
            printf("| %9.3f |     Ошибка    |\n", x);
        }
        else if (x >= -2 && x < 3 && (1 + x * x * x) < 0) {
            printf("| %9.3f |     Ошибка    |\n", x);
        }
        else {
            printf("| %9.3f | %14.6f |\n", x, f(x));
        }
    }
    printf("------------------------------\n");
}

void find_min_max() {
    double a, b, x, fx;
    printf("Введите начало отрезка: ");
    scanf("%lf", &a);
    printf("Введите конец отрезка: ");
    scanf("%lf", &b);

    int found = 0;
    double min_val, max_val;

    for (x = a; x <= b; x += 0.1) {
        fx = f(x);
        if (fx == fx) { //NaN
            if (!found) {
                min_val = max_val = fx;
                found = 1;
            }
            else {
                if (fx < min_val) min_val = fx;
                if (fx > max_val) max_val = fx;
            }
        }
    }

    if (found) {
        printf("\nМинимум (Min) = %.6f\n", min_val);
        printf("Максимум (Max) = %.6f\n", max_val);
    }
    else {
        printf("Функция не определена на этом отрезке\n");
    }
}

void find_x_for_y() {
    double y, a, b, x;
    printf("Введите 'y': ");
    scanf("%lf", &y);
    printf("Введите диапазон поиска (a и b): ");
    scanf("%lf %lf", &a, &b);

    int solution_found = 0;
    for (x = a; x <= b; x += 0.001) {
        if (fabs(f(x) - y) < 0.001) {
            printf("Приблизительно: x = %.3f, f(x) = %.3f\n", x, f(x));
            solution_found = 1;
            break;
        }
    }

    if (!solution_found) {
        printf("Решение не найдено\n");
    }
}

void calculate_derivative() {
    double x;
    printf("Введите x: ");
    scanf("%lf", &x);
    printf("f'(%.3f) = %.6f\n", x, derivative(x));
}
