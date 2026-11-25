#include <cstdint>
#include <iostream>

void first_n_terms(int n) {
    std::cout << "First " << n << " terms of the Fibonacci series: " << '\n';

    std::int64_t a{0}, b{1};
    for (int i{1}; i <= n; i++) {
        if (i == n) {
            std::cout << a << '\n';
        } else {
            std::cout << a << ", ";
        }

        std::int64_t temp{a};
        a = b;
        b += temp;
    }

    return;
}

void terms_upto_m(std::int64_t m) {
    std::int64_t a{0}, b{1};

    while (a <= m) {
        std::cout << a;

        std::int64_t temp{a};
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
    } else if (n > 93) {
        std::cout << "Can only show first 93 terms" << '\n';
        first_n_terms(93);
    } else {
        first_n_terms(n);
    }

    std::cout << "\n\n";

    int m{};
    std::cout << "Enter the (upto) limit: ";
    std::cin >> m;

    if (m < 0) {
        std::cout << "The number must be a non negative integer" << '\n';
    } else if (m == 0) {
        std::cout << "0" << '\n';
    } else if (m == 1) {
        std::cout << "0, 1, 1" << '\n';
    } else if (m >= 1836311903) {
        std::cout << "Can only show terms upto 1836311902" << '\n';
    } else {
        terms_upto_m(m);
    }

    return 0;
}