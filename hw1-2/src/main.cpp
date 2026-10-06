#include <iostream>
#include <string>

void generatePowerset(const std::string& S, std::string current, size_t index) {
    if (index == S.length()) {
        std::cout << "{ ";
        for (char c : current) {
            std::cout << c << " ";
        }
        std::cout << "}\n";
        return;
    }

    generatePowerset(S, current, index + 1);

    generatePowerset(S, current + S[index], index + 1);
}

int main() {
    std::string S = "abc";
    std::string current = "";

    std::cout << "Powerset(S) 結果為:\n";
    generatePowerset(S, current, 0);

    return 0;
}
