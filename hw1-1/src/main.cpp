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
#include <iostream>

int ackermannNonRecursive(int m, int n) {
    int s[100000]; // 以陣列模擬 Stack
    int top = -1;

    s[++top] = m;

    while (top >= 0) {
        m = s[top--];

        if (m == 0) {
            n = n + 1;
        }
        else if (n == 0) {
            s[++top] = m - 1;
            n = 1;
        }
        else {
            s[++top] = m - 1;
            s[++top] = m;
            n = n - 1;
        }
    }
    return n;
}

int main() {
    int m, n;
    std::cout << "請輸入 m 和 n (以空格分隔): ";
    if (std::cin >> m >> n) {
        std::cout << "A(" << m << ", " << n << ") = " 
                  << ackermannNonRecursive(m, n) << std::endl;
    }
    return 0;
}
