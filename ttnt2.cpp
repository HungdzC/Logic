#include<bits/stdc++.h>
using namespace std;

bool applyOperator(bool a, bool b, char op) {
    switch (op) {
        case '^':
        return a && b; 
        case '|': 
        return a || b; 
        case '-': 
        return !a || b; 
        default: 
        throw invalid_argument("Invalid operator");
    }
}

bool evaluateExpression(const string& expr, const map<char, bool>& values) {
    stack<bool> operands;
    stack<char> operators;

    for (char ch : expr) {
    if (isspace(ch)) continue; 

    if (isalnum(ch)) { 
        if (values.find(ch) == values.end()) {
            throw invalid_argument("Variable value not provided.");
        }
        operands.push(values.at(ch));
    } else if (ch == '!') { 
        if (operands.empty()) {
            throw invalid_argument("Invalid use of NOT operator.");
        }
        bool top = operands.top();
        operands.pop();
        operands.push(!top);
    } else if (ch == '^' || ch == '|' || ch == '-') { 
        operators.push(ch);
    } else { 
        throw invalid_argument(string("Invalid character in expression: ") + ch);
    }
}


    while (!operators.empty() && operands.size() >= 2) {
        char op = operators.top();
        operators.pop();
        bool b = operands.top();
        operands.pop();
        bool a = operands.top();
        operands.pop();
        operands.push(applyOperator(a, b, op));
    }

    return operands.top();
}

int main() {
    string expression;
    cout << "Nhap bieu thuc logic: ";
    getline(cin, expression);

    map<char, bool> values;
    int numVariables;
    cout << "Nhap so luong cac bien: ";
    cin >> numVariables;

    for (int i = 0; i < numVariables; ++i) {
        char variable;
        bool value;
        cout << "Nhap cac bien va gia tri cua chung (1:True va 0:False): ";
        cin >> variable >> value;
        values[variable] = value;
    }

    try {
        bool result = evaluateExpression(expression, values);
        cout << "Ket qua: " << (result ? "True" : "False") << endl;
    } catch (const exception& ex) {
        cerr << "Error: " << ex.what() << endl;
        return 1;
    }

    return 0;
}