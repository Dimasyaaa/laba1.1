#include <iostream>
#include <stdexcept> //для исключений
#include <cmath>

using namespace std;

class Fraction {
private:
    int numerator;
    int denominator;

    // Метод для нахождения наибольшего общего делителя
    int gcd(int a, int b) {
        // Убедимся, что оба числа положительные
        a = abs(a);
        b = abs(b);
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    // Собственный метод для сокращения дроби
    void reduce() {
        int greatestCommonDivisor = gcd(numerator, denominator);
        numerator /= greatestCommonDivisor;
        denominator /= greatestCommonDivisor;


        // Если знаменатель отрицательный, приведем к положительному
        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
    }

public:
    //безаргументный конструктор
    Fraction() : numerator(1), denominator(1) {}

    //конструктор с параметрами
    Fraction(int num, int denom) : numerator(num), denominator(denom) {
        if (denom == 0) {
            throw invalid_argument("Знаменатель не может быть нулем");
        }
        reduce();
    }

    //метод для ввода дроби
    void input() {
        cout << "Числитель:";
        cin >> numerator;
        cout << "Знаменатель:";
        cin >> denominator;
        if (denominator == 0) {
            throw invalid_argument("Знаменатель не может быть нулем");
        }
        reduce();
    }

    //метод для вывода дроби
    void print() const {
        cout << numerator << "/" << denominator;
    }

    //перегрузка операторов сложения
    Fraction operator+(const Fraction& other) const {
        int num = numerator * other.denominator + other.numerator * denominator;
        int denom = denominator * other.denominator;
        return Fraction(num, denom);
    }

    Fraction operator+(int value) const {
        return *this + Fraction(value, 1);
    }

    Fraction operator+(double value) const {
        return *this + Fraction(static_cast<int>(value * denominator), denominator); // приводим к целому числу
    }

    //перегрузка операторов вычитания
    Fraction operator-(const Fraction& other) const {
        int num = numerator * other.denominator - other.numerator * denominator;
        int denom = denominator * other.denominator;
        return Fraction(num, denom);
    }

    Fraction operator-(int value) const {
        return *this - Fraction(value, 1);
    }

    Fraction operator-(double value) const {
        return *this - Fraction(static_cast<int>(value * denominator), denominator);
    }

    //перегрузка операторов умножения
    Fraction operator*(const Fraction& other) const {
        int num = numerator * other.numerator;
        int denom = denominator * other.denominator;
        return Fraction(num, denom);
    }

    Fraction operator*(int value) const {
        return *this * Fraction(value, 1);
    }

    Fraction operator*(double value) const {
        return *this * Fraction(static_cast<int>(value * denominator), denominator);
    }

    //перегрузка операторов деления
    Fraction operator/(const Fraction& other) const {
        int num = numerator * other.denominator;
        int denom = denominator * other.numerator;
        return Fraction(num, denom);
    }

    Fraction operator/(int value) const {
        return *this / Fraction(value, 1);
    }

    Fraction operator/(double value) const {
        return *this / Fraction(static_cast<int>(value * denominator), denominator);
    }

    //перегрузка операторов сравнения с дробями
    bool operator>(const Fraction& other) const {
        return numerator * other.denominator > other.numerator * denominator;
    }

    bool operator<(const Fraction& other) const {
        return numerator * other.denominator < other.numerator * denominator;
    }

    bool operator>=(const Fraction& other) const {
        return !(*this < other);
    }

    bool operator<=(const Fraction& other) const {
        return !(*this > other);
    }

    bool operator==(const Fraction& other) const {
        return numerator * other.denominator == other.numerator * denominator;
    }

    bool operator!=(const Fraction& other) const {
        return !(*this == other);
    }

    //перегрузка операторов сравнения с целыми числами
    bool operator>(int value) const {
        return numerator > value * denominator;
    }

    bool operator<(int value) const {
        return numerator < value * denominator;
    }

    bool operator>=(int value) const {
        return numerator >= value * denominator;
    }

    bool operator<=(int value) const {
        return numerator <= value * denominator;
    }

    bool operator==(int value) const {
        return numerator == value * denominator;
    }

    bool operator!=(int value) const {
        return numerator != value * denominator;
    }

    //перегрузка операторов сравнения с вещественными числами
    bool operator>(double value) const {
        double result = static_cast<double>(numerator) / denominator;
        return result > value;
    }

    bool operator<(double value) const {
        double result = static_cast<double>(numerator) / denominator;
        return result < value;
    }

    bool operator>=(double value) const {
        double result = static_cast<double>(numerator) / denominator;
        const double epsilon = 1e-9;
        return (result > value) || (abs(result - value) < epsilon);
    }

    bool operator<=(double value) const {
        double result = static_cast<double>(numerator) / denominator;
        const double epsilon = 1e-9;
        return (result < value) || (abs(result - value) < epsilon);
    }

    bool operator==(double value) const {
        double result = static_cast<double>(numerator) / denominator;
        const double epsilon = 1e-9;
        return abs(result - value) <= epsilon;
    }

    bool operator!=(double value) const {
        double result = static_cast<double>(numerator) / denominator;
        const double epsilon = 1e-9;
        return abs(result - value) >= epsilon;
    }

    //перегрузка операторов инкремента и декремента
    Fraction& operator++() { //префиксный
        numerator++;
        reduce();
        return *this;
    }

    Fraction operator++(int) { //постфиксный
        Fraction temp = *this;
        ++(*this);
        return temp;
    }

    Fraction& operator--() { //префиксный
        numerator--;
        reduce();
        return *this;
    }

    Fraction operator--(int) { //постфиксный
        Fraction temp = *this;
        --(*this);
        return temp;
    }
};

//функция вывода меню
void displayMenu() {
    cout << "===============МЕНЮ===============" << endl;
    cout << "1. Сложение дробей " << endl;
    cout << "2. Сложение с целым " << endl;
    cout << "3. Сложение с вещественным " << endl;
    cout << "4. Вычитание дробей " << endl;
    cout << "5. Вычитание целого " << endl;
    cout << "6. Вычитание вещественного " << endl;
    cout << "7. Умножение дробей " << endl;
    cout << "8. Умножение на целое " << endl;
    cout << "9. Умножение на вещественное " << endl;
    cout << "10. Деление дробей " << endl;
    cout << "11. Деление на целое " << endl;
    cout << "12. Деление на вещественное " << endl;
    cout << "13. Пре-инкремент " << endl;
    cout << "14. Пост-инкремент " << endl;
    cout << "15. Пре-декремент " << endl;
    cout << "16. Пост-декремент " << endl;
    cout << "17. Сравнение строгое " << endl;
    cout << "18. Сравнение строгое с целым " << endl;
    cout << "19. Сравнение строгое с вещественным " << endl;
    cout << "20. Сравнение нестрогое " << endl;
    cout << "21. Сравнение нестрогое с целым " << endl;
    cout << "22. Сравнение нестрогое с вещественным " << endl;
    cout << "23. Равенство " << endl;
    cout << "24. Равенство с целым " << endl;
    cout << "25. Равенство с вещественным " << endl;
    cout << "0. Выход" << endl;
    cout << "Выбор:";
}

int main() {

    setlocale(LC_ALL, "Rus");

    Fraction f1, f2, result;
    int intNum;
    double doubleNum;
    bool compare;
    int choice;
    bool running = true;

    while (running) {
        displayMenu();
        cin >> choice;
        cout << "==================================" << endl;

        switch (choice) {
        case 1:
            cout << "Введите первую дробь" << endl;
            f1.input();
            cout << "Введите вторую дробь" << endl;
            f2.input();
            result = f1 + f2;
            cout << "Результат: ";
            result.print();
            break;
        case 2:
            cout << "Введите первую дробь" << endl;
            f1.input();
            cout << "Введите число:";
            cin >> intNum;
            result = f1 + intNum;
            cout << "Результат: ";
            result.print();
            break;
        case 3:
            cout << "Введите первую дробь" << endl;
            f1.input();
            cout << "Введите число:";
            cin >> doubleNum;
            result = f1 + doubleNum;
            cout << "Результат: ";
            result.print();
            break;
        case 4:
            cout << "Введите первую дробь" << endl;
            f1.input();
            cout << "Введите вторую дробь" << endl;
            f2.input();
            result = f1 - f2;
            cout << "Результат: ";
            result.print();
            break;
        case 5:
            cout << "Введите первую дробь" << endl;
            f1.input();
            cout << "Введите число:";
            cin >> intNum;
            result = f1 - intNum;
            cout << "Результат: ";
            result.print();
            break;
        case 6:
            cout << "Введите первую дробь" << endl;
            f1.input();
            cout << "Введите число:";
            cin >> doubleNum;
            result = f1 - doubleNum;
            cout << "Результат: ";
            result.print();
            break;
        case 7:
            cout << "Введите первую дробь" << endl;
            f1.input();
            cout << "Введите вторую дробь" << endl;
            f2.input();
            result = f1 * f2;
            cout << "Результат: ";
            result.print();
            break;
        case 8:
            cout << "Введите первую дробь" << endl;
            f1.input();
            cout << "Введите число:";
            cin >> intNum;
            result = f1 * intNum;
            cout << "Результат: ";
            result.print();
            break;
        case 9:
            cout << "Введите первую дробь" << endl;
            f1.input();
            cout << "Введите число:";
            cin >> doubleNum;
            result = f1 * doubleNum;
            cout << "Результат: ";
            result.print();
            break;
        case 10:
            cout << "Введите первую дробь" << endl;
            f1.input();
            cout << "Введите вторую дробь" << endl;
            f2.input();
            result = f1 / f2;
            cout << "Результат: ";
            result.print();
            break;
        case 11:
            cout << "Введите первую дробь" << endl;
            f1.input();
            cout << "Введите число:";
            cin >> intNum;
            result = f1 / intNum;
            cout << "Результат: ";
            result.print();
            break;
        case 12:
            cout << "Введите первую дробь" << endl;
            f1.input();
            cout << "Введите число:";
            cin >> doubleNum;
            result = f1 / doubleNum;
            cout << "Результат: ";
            result.print();
            break;
        case 13:
            cout << "Введите первую дробь" << endl;
            f1.input();
            result = ++f1;
            cout << "Результат: ";
            result.print();
            break;
        case 14:
            cout << "Введите первую дробь" << endl;
            f1.input();
            result = f1++;
            cout << "Результат: ";
            result.print();
            break;
        case 15:
            cout << "Введите первую дробь" << endl;
            f1.input();
            result = --f1;
            cout << "Результат: ";
            result.print();
            break;
        case 16:
            cout << "Введите первую дробь" << endl;
            f1.input();
            result = f1--;
            cout << "Результат: ";
            result.print();
            break;
        case 17:
            cout << "Введите первую дробь" << endl;
            f1.input();
            cout << "Введите вторую дробь" << endl;
            f2.input();
            if (f1 > f2) {
                cout << "Результат: ";
                f1.print();
                cout << " > ";
                f2.print();
            }
            else {
                cout << "Результат: ";
                f1.print();
                cout << " < ";
                f2.print();
            }
            break;
        case 18:
            cout << "Введите первую дробь" << endl;
            f1.input();
            cout << "Введите число:";
            cin >> intNum;
            if (f1 > intNum) {
                cout << "Результат: ";
                f1.print();
                cout << " > " << intNum;
            }
            else {
                cout << "Результат: ";
                f1.print();
                cout << " < " << intNum;
            }
            break;
        case 19:
            cout << "Введите первую дробь" << endl;
            f1.input();
            cout << "Введите число:";
            cin >> doubleNum;
            if (f1 > doubleNum) {
                cout << "Результат: ";
                f1.print();
                cout << " > " << doubleNum;
            }
            else {
                cout << "Результат: ";
                f1.print();
                cout << " < " << doubleNum;
            }
            break;
        case 20:
            cout << "Введите первую дробь" << endl;
            f1.input();
            cout << "Введите вторую дробь" << endl;
            f2.input();
            if (f1 >= f2) {
                cout << "Результат: ";
                f1.print();
                cout << " >= ";
                f2.print();
            }
            else {
                cout << "Результат: ";
                f1.print();
                cout << " <= ";
                f2.print();
            }
            break;
        case 21:
            cout << "Введите первую дробь" << endl;
            f1.input();
            cout << "Введите число:";
            cin >> intNum;
            if (f1 >= intNum) {
                cout << "Результат: ";
                f1.print();
                cout << " >= " << intNum;
            }
            else {
                cout << "Результат: ";
                f1.print();
                cout << " <= " << intNum;
            }
            break;
        case 22:
            cout << "Введите первую дробь" << endl;
            f1.input();
            cout << "Введите число:";
            cin >> doubleNum;
            if (f1 > doubleNum) {
                cout << "Результат: ";
                f1.print();
                cout << " >= " << doubleNum;
            }
            else {
                cout << "Результат: ";
                f1.print();
                cout << " <= " << doubleNum;
            }
            break;
        case 23:
            cout << "Введите первую дробь" << endl;
            f1.input();
            cout << "Введите вторую дробь" << endl;
            f2.input();
            if (f1 == f2) {
                cout << "Результат: ";
                f1.print();
                cout << " == ";
                f2.print();
            }
            else {
                cout << "Результат: ";
                f1.print();
                cout << " != ";
                f2.print();
            }
            break;
        case 24:
            cout << "Введите первую дробь" << endl;
            f1.input();
            cout << "Введите число:";
            cin >> intNum;
            if (f1 == intNum) {
                cout << "Результат: ";
                f1.print();
                cout << " == " << intNum;
            }
            else {
                cout << "Результат: ";
                f1.print();
                cout << " != " << intNum;
            }
            break;
        case 25:
            cout << "Введите первую дробь" << endl;
            f1.input();
            cout << "Введите число:";
            cin >> doubleNum;
            if (f1 == doubleNum) {
                cout << "Результат: ";
                f1.print();
                cout << " == " << doubleNum;
            }
            else {
                cout << "Результат: ";
                f1.print();
                cout << " != " << doubleNum;
            }
            break;
        case 0:
            running = false;
            break;
        default:
            cout << "Ошибка выбора пункта меню" << endl;
            break;
        }
        cout << endl;
    }
    return 0;
}
