#include <locale.h>
#include <stdio.h>
#include <math.h>

double f(double x) {
    if (x < -2)
        return (cos(2 * x) - 1) / (x * x);
    else if (x < 3)
        return x * exp(-x / 2.0) + pow(1 + x * x * x, 0.25);
    else
        return log(2 * x + 3) * (pow(x, 4) - 2 * pow(x, 2) + x - 1);
}

double derivative(double x) {
    double h = 1e-5;
    return (f(x + h) - f(x - h)) / (2 * h);
}

int main() {
    setlocale(LC_CTYPE, "");
    int num;
    double x, y, a, b, step;
    double min, max, fx;

    do {
        printf("\n===---МЕНЮ---===\n");
        printf("1. Значение f(x) в точке\n");
        printf("2. Таблица значений\n");
        printf("3. Минимум и максимум на отрезке\n");
        printf("4. Найти x, если f(x) = Y\n");
        printf("5. Производная f'(x)\n");
        printf("6. Контрольный пример\n");
        printf("0. Выход\n");
        printf("Выберите пункт: ");
        scanf("%d", &num);

        switch (num) {

        case 1:
            printf("Введите x: ");
            scanf("%lf", &x);
            if (x >= 3 && (2 * x + 3) <= 0)
                printf("Ошибка: под логарифмом должно быть > 0!\n");
            else if (x >= -2 && x < 3 && (1 + x * x * x) < 0)
                printf("Ошибка: под корнем должно быть >= 0!\n");
            else {
                fx = f(x);
                printf("f(%.3f) = %.6f\n", x, fx);
            }
            break;

        case 2:
            printf("Введите начало:");
            scanf("%lf", &a);
            printf("Введите конец:");
            scanf("%lf", &b);
            printf("Введите шаг:");
            scanf("%lf", &step);
            printf("\n----------------------------------\n");
            printf("|     x      |       f(x)        |\n");
            printf("----------------------------------\n");
            for (x = a; x <= b; x += step) {
                if (x >= 3 && (2 * x + 3) <= 0)
                    printf("| %9.3f |     Ошибка       |\n", x);
                else if (x >= -2 && x < 3 && (1 + x * x * x) < 0)
                    printf("| %9.3f |     Ошибка       |\n", x);
                else
                    printf("| %9.3f | %15.6f |\n", x, f(x));
            }
            printf("----------------------------------\n");
            break;

        case 3:
            printf("Введите начало отрезка: ");
            scanf("%lf", &a);
            printf("Введите конец отрезка: ");
            scanf("%lf", &b);
            int found = 0;
            min = max = f(a);
            for (x = a; x <= b; x += 0.1) {
                fx = f(x);
                if (fx == fx) {
                    found = 1;
                    if (fx < min) min = fx;
                    if (fx > max) max = fx;
                }
            }
            if (found) {
                printf("\nМинимум (Min) = %.6f\n", min);
                printf("Максимум (Max) = %.6f\n", max);
            }
            else {
                printf("Функция не определена на этом отрезке");
            }
            break;

        case 4:
            printf("Введите Y: ");
            scanf("%lf", &y);
            printf("Введите диапазон поиска (a и b): ");
            scanf("%lf %lf", &a, &b);
            for (x = a; x <= b; x += 0.001) {
                if (fabs(f(x) - y) < 0.001) {
                    printf("Приблизительно: x = %.3f, f(x) = %.3f\n", x, f(x));
                    break;
                }
                if (x >= b) {
                    printf("Решение не найдено");
                }
            }
            break;

        case 5:
            printf("Введите x: ");
            scanf("%lf", &x);
            printf("f'(%.3f) = %.6f\n", x, derivative(x));
            break;

        case 6: {
            printf("\n===---КОНТРОЛЬНЫЙ ПРИМЕР---===\n");
            double test_x[] = { -3.0, -1.0, 0.0, 1.0, 2.0, 4.0 };
            int n = 6;
            printf("----------------------------------\n");
            printf("|     x      |       f(x)        |\n");
            printf("----------------------------------\n");
            for (int i = 0; i < n; i++) {
                x = test_x[i];
                printf("| %9.3f | %15.6f |\n", x, f(x));
            }
            printf("----------------------------------\n");
            printf("\nПроизводные:\n");
            printf("f'(0) = %.6f\n", derivative(0));
            printf("f'(3) = %.6f\n", derivative(3));

            min = max = f(-3);
            for (x = -3; x <= 4; x += 0.1) {
                fx = f(x);
                if (fx < min) min = fx;
                if (fx > max) max = fx;
            }
            printf("===========================\n");
            printf("Для промежутка [-3, 4]");
            printf("\nMin = %.6f\nMax = %.6f\n", min, max);
            printf("===========================\n");
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
}