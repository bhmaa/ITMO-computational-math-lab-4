#include <bits/stdc++.h>
#include <iostream>
#include <cmath>

using namespace std;

string ltrim(const string &);

string rtrim(const string &);

using fn_t = double(double);

string error_message;
bool has_discontinuity = false;

double first_function(double x) {
    return 1 / x;
}

double second_function(double x) {
    return sin(x) / x;
}

double third_function(double x) {
    return x * x + 2;
}

double fourth_function(double x) {
    return 2 * x + 2;
}

double five_function(double x) {
    return log(x);
}

double default_function(double x) {
    return (x * x - 1) / (x - 1);
}

fn_t &get_function(int n) {
    switch (n) {
        case 1:
            return first_function;
        case 2:
            return second_function;
        case 3:
            return third_function;
        case 4:
            return fourth_function;
        case 5:
            return five_function;
        default:
            return default_function;
    }
}

double integrate_by_simpson(fn_t f, double a, double b, int n) {
    double h = (b - a) / n;
    double sum = f(a) + f(b);
    for (int i = 1; i < n; i += 2) {
        sum += 4 * f(a + i * h);
    }
    for (int i = 2; i < n - 1; i += 2) {
        sum += 2 * f(a + i * h);
    }
    return sum * h / 3.0;
}

double calculate_integral(double a, double b, int f, double epsilon) {
    fn_t &function = get_function(f);
    int n = 2;
    double integral = integrate_by_simpson(function, a, b, n);
    double integral_prev;
    do {
        n *= 2;
        integral_prev = integral;
        integral = integrate_by_simpson(function, a, b, n);
    } while (abs(integral - integral_prev) > epsilon);
    if (isnan(integral) || isinf(integral)) {
        error_message = "Integrated function has discontinuity or does not defined in current interval";
        has_discontinuity = true;
        return 0.0;
    }
    return integral;
}

int main() {
    string a_temp;
    getline(cin, a_temp);

    double a = stod(ltrim(rtrim(a_temp)));

    string b_temp;
    getline(cin, b_temp);

    double b = stod(ltrim(rtrim(b_temp)));

    string f_temp;
    getline(cin, f_temp);

    int f = stoi(ltrim(rtrim(f_temp)));

    string epsilon_temp;
    getline(cin, epsilon_temp);

    double epsilon = stod(ltrim(rtrim(epsilon_temp)));

    double result = calculate_integral(a, b, f, epsilon);
    if (!has_discontinuity) {
        cout << result << "\n";
    } else {
        cout << error_message << "\n";
    }

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
            s.begin(),
            find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
            find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
            s.end()
    );

    return s;
}
