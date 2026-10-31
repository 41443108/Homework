
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;

class Polynomial;

class Term {
    friend class Polynomial;
private:
    float coef;
    int exp;
};

class Polynomial {
private:
    Term* termArray;
    int capacity;
    int terms;

public:
    Polynomial() : capacity(2), terms(0) {
        termArray = new Term[capacity];
    }

    Polynomial(const Polynomial& p) {
        capacity = max(2, p.terms);
        terms = p.terms;
        termArray = new Term[capacity];
        copy(p.termArray, p.termArray + terms, termArray);
    }

    ~Polynomial() {
        delete[] termArray;
    }

    Polynomial& operator=(const Polynomial& p) {
        if (this != &p) {
            delete[] termArray;
            capacity = max(2, p.terms);
            terms = p.terms;
            termArray = new Term[capacity];
            copy(p.termArray, p.termArray + terms, termArray);
        }
        return *this;
    }

    void newTerm(const float theCoef, const int theExp);

    Polynomial Add(const Polynomial& b);

    Polynomial Mult(const Polynomial& b);

    float Eval(float x);

    void Print();
};

// 新增多項式項目
void Polynomial::newTerm(const float theCoef, const int theExp) {
    if (theCoef == 0) return;

    int i = 0;

    while (i < terms && termArray[i].exp > theExp)
        i++;

    if (i < terms && termArray[i].exp == theExp) {
        termArray[i].coef += theCoef;

        if (termArray[i].coef == 0) {
            for (int j = i; j < terms - 1; j++)
                termArray[j] = termArray[j + 1];
            terms--;
        }
        return;
    }

    if (terms == capacity) {
        capacity *= 2;
        Term* temp = new Term[capacity];
        copy(termArray, termArray + terms, temp);
        delete[] termArray;
        termArray = temp;
    }

    for (int j = terms; j > i; j--)
        termArray[j] = termArray[j - 1];

    termArray[i].coef = theCoef;
    termArray[i].exp = theExp;
    terms++;
}

// 多項式加法
Polynomial Polynomial::Add(const Polynomial& b) {
    Polynomial c;

    int aPos = 0, bPos = 0;

    while (aPos < terms && bPos < b.terms) {
        if (termArray[aPos].exp == b.termArray[bPos].exp) {
            float t = termArray[aPos].coef + b.termArray[bPos].coef;

            c.newTerm(t, termArray[aPos].exp);

            aPos++;
            bPos++;
        }
        else if (termArray[aPos].exp < b.termArray[bPos].exp) {
            c.newTerm(b.termArray[bPos].coef,
                b.termArray[bPos].exp);
            bPos++;
        }
        else {
            c.newTerm(termArray[aPos].coef,
                termArray[aPos].exp);
            aPos++;
        }
    }

    for (; aPos < terms; aPos++)
        c.newTerm(termArray[aPos].coef, termArray[aPos].exp);

    for (; bPos < b.terms; bPos++)
        c.newTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);

    return c;
}

// 多項式乘法
Polynomial Polynomial::Mult(const Polynomial& b) {
    Polynomial c;

    for (int i = 0; i < terms; i++) {
        for (int j = 0; j < b.terms; j++) {
            float coef = termArray[i].coef * b.termArray[j].coef;
            int exp = termArray[i].exp + b.termArray[j].exp;

            c.newTerm(coef, exp);
        }
    }

    return c;
}

// 代入 X 計算
float Polynomial::Eval(float x) {
    float result = 0;

    for (int i = 0; i < terms; i++) {
        result += termArray[i].coef *
            pow(x, termArray[i].exp);
    }

    return result;
}

// 顯示多項式
void Polynomial::Print() {
    if (terms == 0) {
        cout << "0";
        return;
    }

    for (int i = 0; i < terms; i++) {
        float coef = termArray[i].coef;

        if (i > 0) {
            if (coef >= 0)
                cout << " + ";
            else
                cout << " - ";
        }
        else if (coef < 0) {
            cout << "-";
        }

        cout << fabs(coef);

        if (termArray[i].exp != 0) {
            cout << "x";

            if (termArray[i].exp != 1)
                cout << "^" << termArray[i].exp;
        }
    }
}

// 輸入多項式
void InputPolynomial(Polynomial& p) {
    int n, exp;
    float coef;

    p = Polynomial();

    cout << "請輸入多項式項數：";
    cin >> n;

    cout << "請輸入係數和指數：\n";

    for (int i = 0; i < n; i++) {
        cin >> coef >> exp;
        p.newTerm(coef, exp);
    }
}

// 主程式
int main() {
    Polynomial A, B;

    cout << "輸入多項式 A\n";
    InputPolynomial(A);

    cout << "輸入多項式 B\n";
    InputPolynomial(B);

    int choice;
    float x;

    do {
        cout << "\n======= Polynomial 選單 =======\n";
        cout << "1. 顯示 A、B\n";
        cout << "2. A + B\n";
        cout << "3. A * B\n";
        cout << "4. 計算 A(x)\n";
        cout << "5. 計算 B(x)\n";
        cout << "6. 重新輸入 A\n";
        cout << "7. 重新輸入 B\n";
        cout << "0. 結束程式\n";
        cout << "\n選擇：";

        cin >> choice;

        switch (choice) {
        case 1:
            cout << "A = ";
            A.Print();

            cout << "\nB = ";
            B.Print();
            cout << endl;
            break;

        case 2: {
            Polynomial C = A.Add(B);

            cout << "A + B = ";
            C.Print();
            cout << endl;
            break;
        }

        case 3: {
            Polynomial C = A.Mult(B);

            cout << "A * B = ";
            C.Print();
            cout << endl;
            break;
        }

        case 4:
            cout << "請輸入 X：";
            cin >> x;

            cout << "A(" << x << ") = "
                << A.Eval(x) << endl;
            break;

        case 5:
            cout << "請輸入 X：";
            cin >> x;

            cout << "B(" << x << ") = "
                << B.Eval(x) << endl;
            break;

        case 6:
            cout << "重新輸入多項式 A\n";
            InputPolynomial(A);
            break;

        case 7:
            cout << "重新輸入多項式 B\n";
            InputPolynomial(B);
            break;

        case 0:
            cout << "程式結束！\n";
            break;

        default:
            cout << "選擇錯誤，請重新輸入！\n";
        }

    } while (choice != 0);

    return 0;
}
