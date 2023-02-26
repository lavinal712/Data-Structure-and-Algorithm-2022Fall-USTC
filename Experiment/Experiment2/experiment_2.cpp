#include <bits/stdc++.h>

using namespace std;

unordered_map<string, int> operator_priority{{"+", 1}, {"-", 1}, {"*", 2},
                                             {"/", 2}, {"%", 2}, {"^", 3},
                                             {"(", 0}, {")", 4}};

vector<string> nifixToPostfix(vector<string> nifix);
double evalRPN(vector<string> postfix);
bool isNumber(string str);
void printVectorString(vector<string> vecStr);
bool isExpression(string str);
bool isFunction(string str);
bool isLowercaseLetter(string str);
double functions(vector<string> postfix, string function_name);

vector<string> nifixToPostfix(vector<string> nifix) {
    vector<string> postfix;
    stack<string> stk;
    int n = nifix.size();
    for (int i = 0; i < n; i++) {
        string str = nifix[i];
        if (isNumber(str)) {
            postfix.push_back(str);
        } else {
            if (str == "(") {
                stk.push(str);
            } else if (str == ")") {
                while (!stk.empty() && stk.top() != "(") {
                    postfix.push_back(stk.top());
                    stk.pop();
                }
                stk.pop();
            } else if (str.length() > 1) {
                vector<string> nifix_in_function;
                stack<string> stk_brace;
                for (int j = i + 1; j < n; j++) {
                    string str_in_function = nifix[j];
                    if (str_in_function == "(") {
                        stk_brace.push(str_in_function);
                    } else if (str_in_function == ")") {
                        stk_brace.pop();
                    }
                    nifix_in_function.push_back(str_in_function);
                    if (stk_brace.empty()) {
                        vector<string> postfix_in_function =
                            nifixToPostfix(nifix_in_function);
                        postfix.push_back(
                            to_string(functions(postfix_in_function, str)));
                        i = j;
                        break;
                    }
                }
            } else {
                while (!stk.empty() &&
                       operator_priority[stk.top()] > operator_priority[str]) {
                    postfix.push_back(stk.top());
                    stk.pop();
                }
                stk.push(str);
            }
        }
    }
    while (!stk.empty()) {
        postfix.push_back(stk.top());
        stk.pop();
    }
    return postfix;
}

double evalRPN(vector<string> postfix) {
    stack<double> stk;
    int n = postfix.size();
    for (int i = 0; i < n; i++) {
        string str = postfix[i];
        if (isNumber(str)) {
            stk.push(atof(str.c_str()));
        } else {
            double num2 = stk.top();
            stk.pop();
            double num1 = stk.top();
            stk.pop();
            switch (str[0]) {
                case '+':
                    stk.push(num1 + num2);
                    break;
                case '-':
                    stk.push(num1 - num2);
                    break;
                case '*':
                    stk.push(num1 * num2);
                    break;
                case '/':
                    stk.push(num1 / num2);
                    break;
                case '%':
                    stk.push((int)num1 % (int)num2);
                    break;
                case '^':
                    stk.push(pow(num1, num2));
                    break;
                default:
                    break;
            }
        }
    }
    return stk.top();
}

bool isNumber(string str) {
    return !(str == "+" || str == "-" || str == "*" || str == "/" ||
             str == "%" || str == "^" || str == "(" || str == ")" ||
             str == "sin" || str == "cos" || str == "ln" || str == "sqrt" ||
             str == "lg" || str == "");
}

void printVectorString(vector<string> vecStr) {
    for (string str : vecStr) {
        cout << str;
    }
    cout << endl;
}

vector<string> stringToNifix(string str) {
    int n = str.length();
    vector<string> nifix;
    string numstr = "";
    string s = "";
    for (int i = 0; i < n; i++) {
        char c = str[i];
        if ((c >= '0' && c <= '9') || c == '.' ||
            (c == '-' && (i == 0 || str[i - 1] == '('))) {
            numstr += c;
        } else {
            if (numstr.length() != 0) {
                nifix.push_back(numstr);
                numstr = "";
            }
            if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' ||
                c == '^' || c == '(' || c == ')') {
                if (c == '(' && s.length() != 0) {
                    nifix.push_back(s);
                    s = "";
                }
                s = c;
                nifix.push_back(s);
                s = "";
            } else {
                s += c;
            }
        }
    }
    if (numstr.length() != 0) {
        nifix.push_back(numstr);
    }
    return nifix;
}

bool isExpression(string str) {
    int n = str.length();
    stack<char> stk;
    string s1 = "";
    string s2 = "";
    string s3 = "";
    for (int i = 0; i < n; i++) {
        char c = str[i];
        if (i >= 1) {
            s2 += str[i - 1];
        }
        if (i < n - 1) {
            s3 += str[i + 1];
        }
        if (c == '(') {
            stk.push(c);
            if (((isNumber(s2) && !isLowercaseLetter(s2)) || s2 == ")") ||
                (s3 == ")")) {
                return false;
            }
        } else if (c == ')') {
            if (stk.empty()) {
                return false;
            }
            stk.pop();
            if ((isLowercaseLetter(s2) || s2 == "(") || (s3 == "(")) {
                return false;
            }
        } else if (c >= 'a' && c <= 'z') {
            if (isNumber(s2) || isLowercaseLetter(s2) || s2 == ")") {
                return false;
            }
            for (int j = i; j < n; j++) {
                if (str[j] >= 'a' && str[j] <= 'z') {
                    s1 += str[j];
                } else {
                    if (!isFunction(s1)) {
                        return false;
                    }
                    i = j - 1;
                    break;
                }
            }
            if (i < n - 1) {
                s3 = str[i + 1];
            }
            if (s3 != "(") {
                return false;
            }
        } else {
            s1 += c;
            if (!isNumber(s1) && c != '.') {
                if (!((c != '-' &&
                       (isNumber(s2) || isLowercaseLetter(s2) || s2 == ")") &&
                       (isNumber(s3) || isLowercaseLetter(s3) || s3 == "(")) ||
                      (c == '-' &&
                       (isNumber(s2) || isLowercaseLetter(s2) || s2 == "(" ||
                        s2 == ")" || s2 == "") &&
                       (isNumber(s3) || isLowercaseLetter(s3) || s3 == "(")))) {
                    return false;
                }
            }
        }
        s1 = s2 = s3 = "";
    }
    if (!stk.empty()) {
        return false;
    }
    return true;
}

bool isFunction(string str) {
    return str == "sin" || str == "cos" || str == "ln" || str == "lg" ||
           str == "sqrt";
}

bool isLowercaseLetter(string str) {
    return str[0] >= 'a' && str[0] <= 'z';
}

double functions(vector<string> postfix, string function_name) {
    if (function_name == "sin") {
        return sin(evalRPN(postfix));
    } else if (function_name == "cos") {
        return cos(evalRPN(postfix));
    } else if (function_name == "ln") {
        return log(evalRPN(postfix));
    } else if (function_name == "lg") {
        return log(evalRPN(postfix)) / log(10);
    } else if (function_name == "sqrt") {
        return sqrt(evalRPN(postfix));
    } else {
        return 0;
    }
}

int main() {
    string str;
    while (true) {
        cout << "Please enter an expression to calculate(Enter [Q/q] to exit)"
             << endl;
        cin >> str;
        if (str == "Q" || str == "q") {
            break;
        }
        if (isExpression(str)) {
            vector<string> nifix = stringToNifix(str);
            vector<string> postfix = nifixToPostfix(nifix);
            cout << "Ans: " << evalRPN(postfix) << endl;
        } else {
            cout << "Invalid expression" << endl;
        }
    }
    return 0;
}
