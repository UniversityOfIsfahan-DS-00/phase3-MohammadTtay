#include<bits/stdc++.h>

#include<stack.h>

using namespace std;

list < string > infixtoPostfix(string);
string postfixToInfix(list < string >);
void evaluatePostfix(list < string > );

int main() {
    string infix;
    list < string > postfix;
    getline(cin, infix);
    postfix = infixtoPostfix(infix);
    evaluatePostfix(postfix);


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
        return b / a;
        break;
    case '^':
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

        if (infix[i] == ' ')
            continue;
        else if (infix[i] == '(') {
            S.push(infix[i]);
            temp = "";
        } else if (isOperand(infix[i]) || infix[i] == '.') {
            temp += infix[i];
            if (isOperator(infix[i + 1]) || infix[i + 1] == ' ' || infix[i + 1] == '(' || infix[i + 1] == ')') postfix.push_back(temp);
        } else if (isOperator(infix[i])) {
            if (infix[i] == '-' && infix[i - 1] == '(') {
                infix.insert(i, 1, '0');
                i--;
                continue;
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
string postfixToInfix(list<string> postfix){
    /*---------------------------Main Function---------------------------*/
    Stack<string> S(postfix.size());

    for (auto &x : postfix)
    {
        if (isOperator(x))
        {
            string FirstOp = S.top();
            S.pop();
            string SecondOp = S.top();
            S.pop();
            S.push("(" + SecondOp + x + FirstOp + ")");
        }
        else
        {
            S.push(x);
        }
    }

    return S.top();
}



void evaluatePostfix(list < string > postfix) {
    /*---------------------------Main Function---------------------------*/
    cout << postfixToInfix(postfix) << endl;
    if(postfix.size()==1){
        return ;
    }
    double a, b;
    Stack < double > S(postfix.size());
    list<string> temp;
    bool flag=false;

    for (auto &x: postfix) {
        if(flag==true){
            temp.push_back(x);
            continue;
        }
        else if (isOperator(x.c_str())) {
            a = S.top();
            S.pop();
            b = S.top();
            S.pop();
            S.push(operation(a, b, * x.c_str()));
            int stackSize=S.Size();
            for(int i=0;i<stackSize;i++){
                temp.push_front(to_string(S.top()));
                S.pop();
            }
            flag=true;
        } else {
            S.push(stod(x));
        }
    }
    evaluatePostfix(temp);
}
