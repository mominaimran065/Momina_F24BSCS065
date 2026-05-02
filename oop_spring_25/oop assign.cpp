#include <iostream>
#include <string>
using namespace std;

class ItemType 
{
private:
    char value;

public:
    void Initialize(char ch) 
    {
        value = ch;
    }
    char GetValue() const 
    {
        return value;
    }
};

class Stack 
{
private:
    int top;
    ItemType stack[100];   // stack array

public:
    Stack() 
    { 
        top = -1; 
    }

    bool isEmpty()
    {
        return top == -1; 
    }
    bool isFull() 
    {
        return top == 99; 
    }

    void push(ItemType item) 
    {
        if (!isFull()) //checking if stack is full
        {
            stack[++top] = item;
        }
    }

    void pop() 
    {
        if (!isEmpty()) //checking if stack is empty
        {
            top--;
        }
    }

    ItemType Top() 
    {   
        return stack[top];
    }
};

// function to set precedence
int precedence(char op) 
{
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return -1;
}

bool isOperator(char c) 
{
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

bool isOperand(char c) 
{
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'));
}

// check if brackets are balanced
bool isBalancedBrackets(const string& exp) 
{
    Stack st;
    ItemType temp;

    for (int i = 0; i < exp.size(); i++) 
    {
        char c = exp[i];
        if (c == '(') 
        {
            temp.Initialize(c);
            st.push(temp);
        }
        else if (c == ')') 
        {
            if (st.isEmpty()) return false;
            st.pop();
        }
    }
    return st.isEmpty();
}

// extra expression validation
bool isValidExpression(const string& exp) 
{
    if (exp.empty()) return false;

    if (!isBalancedBrackets(exp)) return false;

    if (isOperator(exp[0])) return false;       // cannot start with operator

    if (isOperator(exp[exp.size() - 1])) return false; // cannot end with operator

    for (int i = 0; i < exp.size() - 1; i++) {
        char curr = exp[i], next = exp[i + 1];

        if (isOperator(curr) && isOperator(next)) return false;  // two operators

        if (isOperand(curr) && isOperand(next)) return false;    // two operands

        if (isOperand(curr) && next == '(') return false;        // a( not allowed

        if (curr == ')' && isOperand(next)) return false;        // )a not allowed
    }
    return true;
}

// infix to postfix
string infixToPostfix(const string& exp) 
{
    Stack st;
    ItemType temp;
    string result = "";

    for (int i = 0; i < exp.size(); i++) 
    {
        char c = exp[i];

        if (isOperand(c)) 
        {
            result += c;
        }
        else if (c == '(') 
        {
            temp.Initialize(c);
            st.push(temp);
        }
        else if (c == ')') 
        {
            while (!st.isEmpty() && st.Top().GetValue() != '(') 
            {
                result += st.Top().GetValue();
                st.pop();
            }
            st.pop(); // remove '('
        }
        else if (isOperator(c)) 
        {
            while (!st.isEmpty() && precedence(st.Top().GetValue()) >= precedence(c)) 
            {
                result += st.Top().GetValue();
                st.pop();
            }
            temp.Initialize(c);
            st.push(temp);
        }
    }

    while (!st.isEmpty()) 
    {
        result += st.Top().GetValue();
        st.pop();
    }

    return result;
}

// infix to prefix
string infixToPrefix(string exp) 
{
    // reverse string
    for (int i = 0, j = exp.size() - 1; i < j; i++, j--) 
    {
        char temp = exp[i];
        exp[i] = exp[j];
        exp[j] = temp;
    }

    // swap brackets
    for (int i = 0; i < exp.size(); i++) 
    {
        if (exp[i] == '(') exp[i] = ')';
        else if (exp[i] == ')') exp[i] = '(';
    }

    // get postfix of reversed
    string postfix = infixToPostfix(exp);

    // reverse postfix to get prefix
    for (int i = 0, j = postfix.size() - 1; i < j; i++, j--) 
    {
        char temp = postfix[i];
        postfix[i] = postfix[j];
        postfix[j] = temp;
    }

    return postfix;
}

int main() 
{
    string infix;
    cout << "Enter an infix expression: ";
    cin >> infix;

    if (!isValidExpression(infix)) 
    {
        cout << "Error: Invalid infix expression!" << endl;
        return 0;
    }

    string postfix = infixToPostfix(infix);
    string prefix = infixToPrefix(infix);

    cout << "Postfix: " << postfix << endl;
    cout << "Prefix: " << prefix << endl;

    return 0;
}

