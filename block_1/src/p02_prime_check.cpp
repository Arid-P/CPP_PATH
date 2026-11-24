#include <iostream>

bool is_prime(int n) {
    if (n == 2) {
        return true;
    }

    for (int d{2}; d * d <= n; d++) {
        if (n % d == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    int n{};
    std::cout << "Enter a number :";
    std::cin >> n;

    if (n <= 0) {
        std::cout << "The number must be a posiive integer" << '\n';
        return 0;
    } else if (n == 1) {
        std::cout << "The number 1 is neither prime or composite." << '\n';
        return 0;
    }

    bool prime{is_prime(n)};

    if (prime) {
        std::cout << "The number is prime" << '\n';
    } else {
        std::cout << "The number is composite" << '\n';
    }

    return 0;
}