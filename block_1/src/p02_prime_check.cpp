#include <iostream>

int is_prime(int n) {
    if (n <= 0) {
        std::cout << "The number must be a posiive integer" << '\n';
        return -1;
    } else if (n == 1) {
        std::cout << "The number 1 is neither prime or composite." << '\n';
        return -1;
    } else if (n == 2) {
        return 1;
    }

    for (int d{2}; d <= n / d; d++) {
        if (n % d == 0) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int n{};
    std::cout << "Enter a number :";
    std::cin >> n;

    int prime{is_prime(n)};

    if (prime == 1) {
        std::cout << "The number is prime" << '\n';
    } else if (prime == 0) {
        std::cout << "The number is composite" << '\n';
    }

    return 0;
}