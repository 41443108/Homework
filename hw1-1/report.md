# 41443108

作業一-1

## 解題說明

本題要求實作 Ackermann 函數A(m, n)，並分別提供遞迴(Recursive)與非遞迴 (Non-recursive) 兩種演算法。

### 解題策略

1.遞迴版本：直接依據數學定義進行條件分流與自我呼叫。
2. 非遞迴版本：用自訂陣列（Array）來模擬堆疊（Stack）結構，將參數量推入堆疊中逐步疊代計算。  

## 程式實作

以下為主要程式碼：
遞迴版本
```cpp
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
```
非遞迴版本
```cpp
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
```
## 效能分析
遞迴版本
1. 時間複雜度：程式的時間複雜度為 $O(A(m,n))$。
2. 空間複雜度：空間複雜度為 $O(A(m,n))$。
非遞迴版本
1. 時間複雜度：程式的時間複雜度為 $O(A(m,n))$。
2. 空間複雜度：空間複雜度為 $O(A(m,n))$。
## 測試與驗證

### 測試案例

| 測試案例 | 輸入參數 $(m,n)$ | 預期輸出 | 實際輸出(遞迴) | 實際輸出(非遞迴) |
|----------|--------------|----------|----------|------------|
| 測試一   | $m=0,n=0$      | 1        | 1        |1        |
| 測試二   | $m=1,n=2$      | 4       | 4       |4       |
| 測試三   | $m=2,n=1$      | 5       | 5        |5        |
| 測試四   | $m=3,n=3$      | 61       | 61       |61       |
| 測試五   | $m=4,n=3$     | 異常拋出 | 異常拋出 | 異常拋出 |

### 編譯與執行指令

```shell
$ g++ -std=c++17 -o problem1-1 problem1-1.cpp
$ ./problem1-1
請輸入 m 和 n (以空格分隔): 2 1
A(2, 1) = 5
```

### 結論

1. 程式正確性驗證：遞迴與非遞迴兩種版本的輸出結果完全一致，且皆能準確計算A(m, n)的數值。  
2. 計算極限與成長速度：Ackermann 函數，其時間與空間複雜度隨 $m$ 的增加呈超指數級增長。實測顯示當 $m<=3$ 時程式執行順暢，但當 $m>=4$ 時，即便使用非遞迴版本，也會因計算次數過多而遭遇時間與記憶體空間的極限。
## 申論及開發報告
選擇遞迴與非遞迴實作的比較在本程式中，分別使用遞迴與非遞迴（自訂堆疊）兩種方式實作 Ackermann 函數 $A(m, n)$，主要理由與比較如下：

遞迴實作：邏輯直觀且極貼近數學定義
Ackermann 函數本身為一高度遞迴定義的數學函數。使用遞迴寫法能以極少的程式碼精確表達其三大分支條件：
當 $m = 0$ 時返回 $n + 1$。   
當 $n = 0$ 時轉化為子問題 $A(m-1, 1)$。   
其餘情況轉化為巢狀遞迴 $A(m-1, A(m, n-1))$。

非遞迴實作：突破系統呼叫堆疊（Call Stack）限制由於 Ackermann 函數的數值呈爆炸性成長，使用遞迴呼叫時，
系統會在記憶體中建立大量的 Stack Frame。當參數稍大（如 $m >= 4$）時，極易導致 Stack Overflow。   
非遞迴版本透過自訂陣列模擬堆疊（Stack）結構，將原本由作業系統維護的呼叫堆疊移至記憶體 Heap/Data 區塊管理，
降低了函數呼叫的開銷與風險。
