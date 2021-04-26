#include<iostream>
#include<string>
#include<cmath>
#include<stack>
#include<typeinfo>
using namespace std;

static stack<int> opStack;
static string result;
static char op[] = {'+','*','^',')','(','-','/'}; // index%4 = prior. (+,-)는 0, (*,/)는 1, ^는 2.

// operator라면 op_list에서 알맞은 index를 부여받고, operand라면 7을 return
int findIndex(char _op){
    for(int i=0;i<7;i++){
        if(_op == op[i]){  
            return i;
        }
    }
    return 7;
}

// operand라면 result string에 추가, operator라면 opStack에 push
void inputFunc(char _input){
    int temp;
    temp = findIndex(_input);
    if(temp == 7){
        result += _input;
    }
    else {
        temp = findIndex(_input);
        opStack.push(temp);
    }
}

void infix2postfix (string _input) {
    int top;
    int current;
    for(int i=0; i < _input.length(); i++){
        top = !opStack.empty() ? opStack.top() : 0;
        current = findIndex(_input[i]);
        if(current == 7){
            inputFunc(_input[i]);
        }
        else if(current != 3){
            if(current%5 >= top%5 || top == 4 || opStack.empty()){
                inputFunc(_input[i]);  
                continue;
            }
            while(opStack.top() != 4 && !opStack.empty()){
                top = opStack.top();
                opStack.pop();
                result += op[top];
                if(opStack.empty()) break;                
            }
            inputFunc(_input[i]);
        }
        else{
            while(top != 4){
                opStack.pop();
                result += op[top];
                top = opStack.top();
            }
            opStack.pop();
        }
    }
    while(!opStack.empty()){
        top = opStack.top();
        opStack.pop();
        result += op[top];
    }
}

// infix -> postfix
int main(){
    string input;
    cin >> input;
    infix2postfix(input);
    cout << result << endl;
    int x;
    return 0;
}
