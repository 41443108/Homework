# 41443108

作業一-2

## 解題說明

本題要求實作一個遞迴函數，計算包含 $n$ 個元素的集合 $S$ 之所有可能子集（包含空集合與自身）。

### 解題策略

1.回溯法 (Backtracking)：對集合中的每個元素都有「包含」與「不包含」兩種選擇。
2.字串操作：用 std::string 傳遞與維護當前形成的子集字串。 

## 程式實作

以下為主要程式碼：

```cpp
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
```

## 效能分析
遞迴版本
1. 時間複雜度：程式的時間複雜度為 $O(2^n)$。
2. 空間複雜度：空間複雜度為 $O(A(n))$。

## 測試與驗證

### 測試案例

| 測試案例 | 輸入集合 $S$ | 預期子集個數 $(2^n)$ | 實際輸出個數 |
|----------|--------------|----------|----------|
| 測試一   | $abc$      | 8       | 2       |
| 測試二   | $a$      | 8       |2      |


### 編譯與執行指令

```shell
$ g++ -std=c++17 -o problem2 problem2.cpp
$ ./problem2
Powerset(S) 結果為:
{ }
{ c }
{ b }
{ b c }
{ a }
{ a c }
{ a b }
{ a b c }
```

### 結論

1.程式正確性驗證：程式能準確列舉出包含空集合 $\{ \}$ 在內的所有 $2^n$ 個可能子集，結果完全符合數學上冪集的定義與題目要求。
2. 時間與空間效能：由於大小為 $n$ 的集合其子集總數恆為 $2^n$ 個，時間複雜度受限於問題本身的輸出規模為 $O(2^n)$。在實作上透過遞迴回溯將空間複雜度控制在 $O(n)$，達成了空間利用的最佳化。
## 申論及開發報告
選擇遞迴實作的原因與設計思考在本程式中，使用遞迴回溯法（Recursive Backtracking）來求解集合 $S$ 的冪集（Powerset），主要考量與開發細節如下：

二元樹決策模型（Binary Decision Tree）求解冪集的本質是針對集合中的每一個元素做出「二元選擇」——包含或不包含。
遞迴寫法能非常自然地繪製出二元決策樹：
左分支：不選擇當前元素 $S[index]$，直接進入下一層遞迴。
右分支：選擇當前元素 $S[index]$，加入當前組合後進入下一層遞迴。
當遞迴深度達到集合大小 $n$ 時（到達葉子節點），即代表完成一個子集的建立並進行輸出。

記憶體與字串操作的優化在限制標頭檔使用環境下，程式採用 std::string 傳遞與維護當前狀態。
藉由 C++ 的值傳遞或字串連接技巧，能在遞迴呼叫的過程中自動完成狀態的建立與回溯，
不需要額外寫手動的狀態復原邏輯，使程式碼極度簡潔且不容易出錯。

演算法空間開銷控制相較於非遞迴法在元素過多時可能需要考慮型態位元數限制，遞迴回溯法只受限於系統呼叫堆疊深度。
其呼叫堆疊深度最大僅為 $n$，空間複雜度保持為極佳的 $O(n)$。
