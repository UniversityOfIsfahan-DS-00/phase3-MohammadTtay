#include<bits/stdc++.h>

#include<conio.h>

#include<stack.h>

using namespace std;

class Node {
public:
    string data;
    Node * left;
    Node * right;

    Node(string val) {
        this -> data = val;
        left = NULL;
        right = NULL;
    }
};

list < string > infixtoPostfix(string);
string postfixToInfix(list < string > );
double evaluatePos(list < string > );
double evaluatePost_Steps(list < string > );
bool isValid(string);
Node * BTree(list < string > );
void printTree(Node * , int = 0);
string trim(string x);

int main() {
start: system("cls");

    string infix;
    list < string > postfix;
    cout << "Enter The Expression:\n";
    getline(cin, infix);
    infix = trim(infix);

    if (!isValid(infix)) {
        cout << "Error\n";
        cout << "\n\nPress Any Key to Go Back...";
        getch();
        goto start;
    } else {
        try {
            while (true) {
                int firstPage;
                postfix = infixtoPostfix(infix);
                cout << "\n\n<1> Show Answer\n\n" <<
                    "<2> Evaluate With Showing Steps\n\n" <<
                    "<3> Show The Expression Tree \n\n" <<
                    "<4> Finish \n\n" <<
                    "Please Enter A Number: ";
                cin >> firstPage;

                switch (firstPage) {
                case 1:
                    try {
                        cout << "Output:" << evaluatePos(postfix) << "\n\n\n";
                    } catch (string a) {
                        cout << a << endl;
                    }

                    break;
                case 2:
                    try {
                        cout << "Output:\n" << evaluatePost_Steps(postfix) << "\n\n\n";
                    } catch (string a) {
                        cout << a << endl;
                    }

                    break;
                case 3:
                    printTree(BTree(postfix));
                    cout << "\n\n\n";
                    break;
                case 4:
                    cin.ignore();
                    goto start;
                    break;
                default:
                    cout << "Please Enter A Valid Number\n";
                    continue;
                }

            }
        } catch (string a) {
            cout << a << endl;
        } catch (...) {
            cout << "Error" << endl;
        }
    }
    return 0;
}

bool isOperator(char c) {
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') return true;

    return false;
}
bool isOperator(string c) {
    if (c == "+" || c == "-" || c == "*" || c == "/" || c == "^") return true;

    return false;
}

bool isOperand(char c) {
    if (c >= '0' && c <= '9') return true;

    return false;
}

int priority(char Operator) {
    if (Operator == '+' || Operator == '-') return 1;

    if (Operator == '*' || Operator == '/') return 2;

    if (Operator == '^') return 3;

    return 0;
}
bool checkTwoOperators(char FirstOp, char SecondOp) {
    int p1 = priority(FirstOp);
    int p2 = priority(SecondOp);
    if (p1 == p2) {
        if (FirstOp == '^') return false;
        else return true;
    }
    return (p1 > p2 ? true : false);
}

double operation(double a, double b, char Operator) {
    switch (Operator) {
    case '+':
        return b + a;
        break;
    case '-':
        return b - a;
        break;
    case '*':
        return b * a;
        break;
    case '/':
        if (a == 0) {
            string str = "Can't Divide By Zero";
            throw str;
        }
        return b / a;
        break;
    case '^':
        if (b < 0) {
            int x;
            x = int(a);
            if (x != a) {
                string str = "Calculation Outside Of Accepted Range";
                throw str;
            }
        }
        if (b == 0) {
            if (a < 0) {
                string str = "Calculation Outside Of Accepted Range";
                throw str;
            }
        }
        return pow(b, a);
        break;
    default:
        return 0;
    }

}

list < string > infixtoPostfix(string infix) {
    /*---------------------------Main Function---------------------------*/

    Stack < char > S(infix.length());
    list < string > postfix;
    string temp;

    S.push('(');
    infix += ')';

    for (int i = 0; i < infix.length(); i++) {

        if (infix[i] == '(') {
            S.push(infix[i]);
            temp = "";
        } else if (isOperand(infix[i]) || infix[i] == '.') {
            temp += infix[i];
            if (isOperator(infix[i + 1]) || infix[i + 1] == ' ' || infix[i + 1] == '(' || infix[i + 1] == ')') postfix.push_back(temp);
        } else if (isOperator(infix[i])) {
            if (infix[i] == '-') {
                if (i == 0) {
                    infix.insert(i + 1, 1, '1');
                    infix.insert(i + 2, 1, '*');
                    temp += '-';
                    continue;
                } else if (infix[i - 1] == '(' && infix[i + 1] == '(') {
                    infix.insert(i + 1, 1, '1');
                    infix.insert(i + 2, 1, '*');
                    temp += '-';
                    continue;
                } else if (infix[i - 1] == '(' && isOperand(infix[i + 1]) && infix[i + 2] == '^') {
                    infix.insert(i + 1, 1, '1');
                    infix.insert(i + 2, 1, '*');
                    temp += '-';
                    continue;
                } else if (infix[i - 1] == '(' && isOperand(infix[i + 1])) {
                    temp += '-';
                    continue;
                }
            }

            temp = "";
            while (!S.isEmpty() && checkTwoOperators(S.top(), infix[i])) {
                string tempChar = "";
                tempChar += S.top();
                postfix.push_back(tempChar);
                S.pop();
            }
            S.push(infix[i]);
        } else if (infix[i] == ')') {
            temp = "";
            while (!S.isEmpty() && S.top() != '(') {
                string tempChar = "";
                tempChar += S.top();
                postfix.push_back(tempChar);
                S.pop();
            }
            S.pop();
        }
    }
    return postfix;

}
string postfixToInfix(list < string > postfix) {
    /*---------------------------Main Function---------------------------*/
    Stack < string > S(postfix.size());

    for (auto & x: postfix) {
        if (isOperator(x)) {
            string FirstOp = S.top();
            S.pop();
            string SecondOp = S.top();
            S.pop();
            S.push("(" + SecondOp + x + FirstOp + ")");
        } else {
            S.push(x);
        }
    }

    return S.top();
}
double evaluatePos(list < string > postfix) {
    /*---------------------------Main Function---------------------------*/
    Stack < double > stack = Stack < double > (postfix.size());

    for (const auto & x: postfix) {
        if (isOperator(x.c_str())) {
            double val1 = stack.top();
            stack.pop();
            double val2 = stack.top();
            stack.pop();
            try {
                stack.push(operation(val1, val2, * x.c_str()));
            } catch (string a) {
                throw std::move(a);
            }
        } else {
            stack.push(stod(x));
        }
    }
    return stack.top();
}

double evaluatePost_Steps(list < string > postfix) {
    /*---------------------------Main Function---------------------------*/

    if (postfix.size() == 1) {
        return stod(postfix.front());
    }
    cout << postfixToInfix(postfix) << endl;

    double a, b;
    Stack < double > S(postfix.size());
    list < string > temp;
    bool flag = false;

    for (auto & x: postfix) {
        if (flag == true) {
            temp.push_back(x);
            continue;
        } else if (isOperator(x.c_str())) {
            a = S.top();
            S.pop();
            b = S.top();
            S.pop();
            try {
                S.push(operation(a, b, * x.c_str()));
            } catch (string a) {
                throw std::move(a);
            }

            int stackSize = S.Size();
            for (int i = 0; i < stackSize; i++) {
                temp.push_front(to_string(S.top()));
                S.pop();
            }
            flag = true;
        } else {
            S.push(stod(x));
        }
    }
    return evaluatePost_Steps(temp);
}
bool validParenthesis(string infix) {
    string parenthesis;
    for (auto x: infix) {
        if (x == '(' || x == ')') {
            parenthesis.push_back(x);
        }
    }
    Stack < char > S(parenthesis.size());

    for (int i = 0; i < parenthesis.length(); i++) {
        if (parenthesis[i] == '(') {
            S.push(parenthesis[i]);
            continue;
        }

        if (parenthesis[i] == ')') {
            if (S.isEmpty()) return false;
            S.pop();
        }
    }

    return (S.isEmpty());
}
bool isValid(string infix) {
    int infixSize = infix.size(), i;

    if (!validParenthesis(infix)) return false;

    if ((isOperator(infix[0]) && infix[0] != '-') || isOperator(infix[infixSize - 1])) {
        return false;
    }
    string DotCheck;
    for (i = 0; i < infixSize - 1; i++) {
        DotCheck += infix[i];

        if (!isOperator(infix[i]) && !isOperand(infix[i]) && infix[i] != '(' && infix[i] != ')' && infix[i] != '.') {
            return false;
        }
        if (infix[i] == '(') {
            if (infix[i + 1] == ')' || (isOperator(infix[i + 1]) && infix[i + 1] != '-') || isOperand(infix[i - 1])) {
                return false;
            }
        }

        if (isOperator(infix[i])) {
            if (isOperator(infix[i + 1]) || infix[i + 1] == ')' || infix[i + 1] == '.' || infix[i - 1] == '.') {
                return false;
            }
            if (count(DotCheck.begin(), DotCheck.end(), '.') > 1) return false;
            DotCheck = "";
        }

    }
    if (!isOperator(infix[i]) && !isOperand(infix[i]) && infix[i] != '(' && infix[i] != ')' && infix[i] != '.') {
        return false;
    }
    if (count(DotCheck.begin(), DotCheck.end(), '.') > 1) return false;

    return true;

}

Node * BTree(list < string > postfix) {
    Stack < Node * > S;
    Node * Temp;
    for (const auto & x: postfix) {
        if (x == "+" || x == "-" || x == "*" || x == "/" || x == "^") {
            Temp = new Node(x);
            Temp -> right = S.top();
            S.pop();
            Temp -> left = S.top();
            S.pop();
            S.push(Temp);
        } else {
            Temp = new Node(x);
            S.push(Temp);
        }

    }
    return Temp;
}

void printTree(Node * root, int space) {
    if (root == NULL)
        return;

    space += 10;

    printTree(root -> right, space);

    cout << endl;
    for (int i = 10; i < space; i++)
        cout << " ";
    cout << root -> data << "\n";

    printTree(root -> left, space);
}

string trim(string x) {
    string temp;
    for (auto t: x) {
        if (t != ' ') temp += t;
    }
    return temp;
}
