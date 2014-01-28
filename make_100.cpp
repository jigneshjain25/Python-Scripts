#include<iostream>
#include<stack>
using namespace std;

double reqd=100.0;

int get_prio(char x){
    if(x=='(')return 3;
    if(x=='*'||x=='/')return 2;
    return 1;
}

int is_operator(char ch){
    return (ch=='*' || ch=='/' || ch=='+' || ch=='-');
}

string infix_to_postfix(string str){
    stack<char> S;
    string dummy="";
    int len= str.length();
    for(int i=0;i<len;i++){
        char ch=str[i];
        if(is_operator(ch))
        {
            int prec = get_prio(ch);
            while(!S.empty() && get_prio(S.top()) >= prec && S.top()!='(')
            {
                dummy+=S.top();
                S.pop();
            }
            S.push(ch);
        }
        else if(ch=='(')
            S.push(ch);
        else if(ch==')')
        {
            while(S.top()!='(')
            {
                dummy+=S.top();
                S.pop();
            }
            S.pop();
        }
        else dummy+=ch;
    }
    while(!S.empty())
    {
        dummy+=S.top();
        S.pop();
    }
    return dummy;
}
double compute(string str)
{
    double result,operand1,operand2;
    stack<double> S;
    for (int i = 0 ; i < str.length(); i++)
    {
        if (str[i] == '*')
        {
            operand1 = S.top();S.pop();
            operand2 = S.top();S.pop();
            result = operand1 * operand2;
            S.push(result);
        }

        else if (str[i] == '/')
        {
            operand1 = S.top();S.pop();
            operand2 = S.top();S.pop();
            result = operand2 / operand1;
            S.push(result);
        }

        else if (str[i] == '+')
        {
            operand1 = S.top();S.pop();
            operand2 = S.top();S.pop();
            result = operand1 + operand2;
            S.push(result);
        }

        else if (str[i] == '-')
        {
            operand1 = S.top();S.pop();
            operand2 = S.top();S.pop();
            result = operand2 - operand1;
            S.push(result);
        }

        else
        {
            result = double(str[i] - '0');
            S.push(result);
        }
    }

    result = S.top();
    S.pop();
    return result;
}

void solve2(string s)
{
    string one="(";
    string two=")";
    int n = s.length();
    for(int i=0;i<=s.length();i+=2){
        
        s.insert(i,one);
        for(int j=i+4;j<=s.length();j+=2)
        {
            s.insert(j,two);
            
            if(compute(infix_to_postfix(s))==reqd) 
               cout<<s<<endl;

            s.erase(s.begin()+j);
        }
        s.erase(s.begin()+i);
    }
}

void solve(string s, int index){
    s+=(index+'0');
    if(index==9){
       if(compute(infix_to_postfix(s))==reqd) 
           cout<<s<<endl;
       else
           solve2(s);
       return;
    }
    solve(s+"+",index+1);
    solve(s+"-",index+1);
    solve(s+"*",index+1);
    solve(s+"/",index+1);
}

int main(){
    string s="";
    solve(s,1);
}
