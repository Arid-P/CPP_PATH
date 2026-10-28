#include <iostream>

void first_n_terms(int n) {
    std::cout << "First " << n << " terms of the Fibonacci series: " << '\n';

    int a{0}, b{1};
    for (int i{1}; i <= n; i++) {
        if (i == n) {
            std::cout << a << '\n';
        } else {
            std::cout << a << ", ";
        }

        int temp{a};
        a = b;
        b += temp;
    }

    return;
}

void terms_upto_m(int m) {
    int a{0}, b{1};

    while (a <= m) {
        std::cout << a;

        int temp{a};
        a = b;
        b += temp;

        if (a <= m) {
            std::cout << ", ";
        } else {
            std::cout << '\n';
        }
    }

    return;
}

int main() {
    int n{};
    std::cout << "Enter number of terms of the series: ";
    std::cin >> n;

    if (n <= 0) {
        std::cout << "The number must be a posiive integer" << '\n';
    } else {
        first_n_terms(n);
    }

    std::cout << "\n\n";

    int m{};
    std::cout << "Enter the limit: ";
    std::cin >> m;

    if (m < 0) {
        std::cout << "The number must be a non negative integer" << '\n';
    } else if (m == 0) {
        std::cout << "0" << '\n';
    } else if (m == 1) {
        std::cout << "0, 1, 1" << '\n';
    } else {
        terms_upto_m(m);
    }

    return 0;
}