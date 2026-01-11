#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <stdlib.h>

double input_scanf(const char* message);
double f(double x);
void create_value_table(double a, double b, double step);
int save_table_to_file(double a, double b, double step, const char* filename);
int find_x_for_y(double y, double a, double b, double eps, double* result_x);
int check_increasing(double a, double b, double step);
double derivative(double x, double h);

int main() {
    setlocale(LC_CTYPE, "RUS");
    printf("Программа для работы с функцией f(x)\nВыполнил: Чумачек Владислав, бИЦ-252\n");
    int num;
    double result;

    do {
        printf("\n*<<<===<( МЕНЮ )>===>>>*\n");
        printf("1. Значение f(x) в точке\n");
        printf("2. Таблица значений\n");
        printf("3. Сохранить таблицу в файл\n");
        printf("4. Найти x по значению Y\n");
        printf("5. Проверка на возрастание\n");
        printf("6. Производная f'(x)\n");
        printf("0. Выход\n");
        num = (int)input_scanf("Выберите пункт: ");

        switch (num) {
        case 1: {
            double x = input_scanf("\nВведите x: ");
            int count = (int)input_scanf("Введите точность ответа: ");
            if (count < 0) count = 0;

            result = f(x);
            if (!isnan(result)) {
                printf("\nОтвет: f(%.15g) = %.*f\n", x, count, result);
            }
            else {
                printf("Функция не определена в точке x = %.15g\n", x);
            }
            break;
        }
        case 2: {
            double a = input_scanf("\nВведите начало (a): ");
            double b = input_scanf("Введите конец (b): ");
            double step = input_scanf("Введите шаг: ");

            if (step <= 0) {
                printf("Шаг должен быть > 0!\n");
                break;
            }
            if (a > b) {
                printf("Ошибка! Необходимо a < b!\n");
                break;
            }

            create_value_table(a, b, step);
            break;
        }
        case 3: {
            char filename[100];
            printf("\nВведите имя файла (например, table.txt): ");
            scanf("%s", filename);
            double a = input_scanf("Введите начало (a): ");
            double b = input_scanf("Введите конец (b): ");
            double step = input_scanf("Введите шаг: ");

            if (step <= 0) {
                printf("Ошибка: Шаг должен быть > 0!\n");
                break;
            }
            if (a > b) {
                printf("Ошибка: Необходимо a < b!\n");
                break;
            }

            int status = save_table_to_file(a, b, step, filename);
            if (status == 1) {
                printf("Успешно! Таблица сохранена в файл '%s'\n", filename);
            }
            else {
                printf("Ошибка при создании или записи файла '%s'\n", filename);
            }
            break;
        }
        case 4: {
            double y = input_scanf("\nВведите 'Y': ");
            double a = input_scanf("Введите начало диапазона (a): ");
            double b = input_scanf("Введите конец диапазона (b): ");
            double eps = input_scanf("Введите точность поиска (например, 0.001): ");
            int count = (int)input_scanf("Введите точность ответа: ");
            if (count < 0) count = 0;

            if (eps <= 0) {
                printf("Ошибка! Точность должна быть > 0\n");
                break;
            }
            if (a > b) {
                printf("Ошибка! Необходимо a < b!\n");
                break;
            }

            double found_x;
            int res = find_x_for_y(y, a, b, eps, &found_x);

            if (res == 1) {
                printf("\nПриблизительно: x = %.*f (при точности поиска = %.15g)\n", count, found_x, eps);
            }
            else {
                printf("\nРешений не найдено в данном диапазоне (с заданной точностью)\n");
            }
            break;
        }
        case 5: {
            double a = input_scanf("\nВведите начало отрезка (a): ");
            double b = input_scanf("Введите конец отрезка (b): ");
            double step = input_scanf("Введите шаг проверки: ");

            if (step <= 0) {
                printf("Шаг должен быть > 0!\n");
                break;
            }
            if (a > b) {
                printf("Ошибка! Необходимо a < b!\n");
                break;
            }

            int res = check_increasing(a, b, step);
            if (res == 1) {
                printf("\nОтвет: Функция МОНОТОННО ВОЗРАСТАЕТ на отрезке [%.15g; %.15g]\n", a, b);
            }
            else if (res == 0) {
                printf("\nОтвет: Функция НЕ ЯВЛЯЕТСЯ монотонно возрастающей на отрезке [%.15g; %.15g]\n", a, b);
            }
            else if (res == -1) {
                printf("\nОшибка: на отрезке [%.15g; %.15g] есть точки разрыва или неопределенности\n", a, b);
            }
            break;
        }
        case 6: {
            double x = input_scanf("\nВведите x: ");
            double h = input_scanf("Введите шаг приращения dx (например, 0.00001): ");
            int count = (int)input_scanf("Введите точность ответа: ");
            if (count < 0) count = 0;

            if (h <= 0) {
                printf("\nОшибка! Шаг dx должен быть > 0\n");
                break;
            }

            double deriv = derivative(x, h);
            if (isnan(deriv)) {
                printf("\nОтвет: Производная не существует (область неопределенности)\n");
            }
            else if (isinf(deriv)) {
                printf("\nОтвет: Производная бесконечна\n");
            }
            else {
                printf("\nОтвет: f'(%.15g) = %.*f (при dx=%.15g)\n", x, count, deriv, h);
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

    return 0;
}

double input_scanf(const char* message) {
    double value;
    printf("%s", message);
    while (scanf("%lf", &value) != 1) {
        printf("\nОшибка! Введите число!\nПопробуйте снова:");
        while (getchar() != '\n');
    }
    return value;
}

double f(double x) {
    if (x < -2.0) {
        return (cos(2.0 * x) - 1.0) / (x * x);
    }
    else if (x >= -2.0 && x < 3.0) {

        if ((1.0 + x * x * x) < 0.0) {
            return NAN; // Проверка: под корнем 4-й степени не должно быть отрицательного числа
        }
        return x * exp(-x / 2.0) + pow(1.0 + x * x * x, 0.25);
    }
    else {
        return log(2.0 * x + 3.0) * (pow(x, 4.0) - 2.0 * pow(x, 2.0) + x - 1.0);
    }
}

void create_value_table(double a, double b, double step) {
    printf("\nТаблица значений:\n");
    printf("------------------------------\n");
    printf("|     x     |      f(x)      |\n");
    printf("------------------------------\n");

    for (double x = a; x <= b + step / 2.0; x += step) {
        double result = f(x);

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

int save_table_to_file(double a, double b, double step, const char* filename) {
    FILE* fp = fopen(filename, "w");

    if (fp == NULL) {
        return 0;
    }

    fprintf(fp, "Таблица значений:\n");
    fprintf(fp, "------------------------------\n");
    fprintf(fp, "|     x     |      f(x)      |\n");
    fprintf(fp, "------------------------------\n");

    for (double x = a; x <= b + step / 2.0; x += step) {
        double result = f(x);

        if (isnan(result)) {
            fprintf(fp, "|%11.3f|  НЕ ОПРЕДЕЛЕНО |\n", x);
        }
        else if (isinf(result)) {
            fprintf(fp, "|%11.3f|  БЕСКОНЕЧНО    |\n", x);
        }
        else {
            fprintf(fp, "|%11.3f| %14.6f |\n", x, result);
        }
    }
    fprintf(fp, "------------------------------\n");
    fclose(fp);
    return 1;
}

int find_x_for_y(double y, double a, double b, double eps, double* result_x) {
    for (double x = a; x <= b + eps / 2.0; x += eps) {
        double fx = f(x);

        if (isnan(fx) || isinf(fx)) {
            continue;
        }

        if (fabs(fx - y) < eps) {
            *result_x = x;
            return 1;
        }
    }
    return 0;
}

int check_increasing(double a, double b, double step) {
    double previous_y = f(a);

    if (isnan(previous_y) || isinf(previous_y)) {
        return -1;
    }

    for (double x = a + step; x <= b + step / 2.0; x += step) {
        double current_y = f(x);

        if (isnan(current_y) || isinf(current_y)) {
            return -1;
        }
        if (current_y <= previous_y) {
            return 0;
        }
        previous_y = current_y;
    }
    return 1;
}

double derivative(double x, double h) {
    double fx_plus = f(x + h);
    double fx_minus = f(x - h);

    if (isnan(fx_plus) || isnan(fx_minus) || isinf(fx_plus) || isinf(fx_minus)) {
        return NAN;
    }
    return (fx_plus - fx_minus) / (2 * h);
}
