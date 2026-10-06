//遞迴
#include <iostream>

int ackermannRecursive(int m, int n) {
    if (m == 0) {
        return n + 1;
    }
    else if (n == 0) {
        return ackermannRecursive(m - 1, 1);
    }
    else {
        return ackermannRecursive(m - 1, ackermannRecursive(m, n - 1));
    }
}

int main() {
    int m, n;
    std::cout << "請輸入 m 和 n (以空格分隔): ";
    if (std::cin >> m >> n) {
        std::cout << "A(" << m << ", " << n << ") = " 
                  << ackermannRecursive(m, n) << std::endl;
    }
    return 0;
}
//非遞迴
