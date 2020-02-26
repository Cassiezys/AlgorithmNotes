#include<iostream>
#include<string>
#include<stack>
#include<queue>
#include<map>
using namespace std;
struct node {
    double num;
    char op;
    bool flag;//(true)操作数还是(false)运算符
    node() { num = 0; };
};
string str;
queue<node> postr;
stack<node> op;
node temp;
map<char, int> opmap;
void to_post()
{
    for (int i = 0; i < str.size();)
    {
        if (str[i] >= '0' && str[i] <= '9') {//操作数
            temp.flag = true;
            temp.num = 0;
            while (str[i] >= '0' && str[i] <= '9' && i < str.size())
                temp.num = temp.num * 10 + (str[i++] - '0');
            postr.push(temp);
        }
        else {
            temp.flag = false;
            temp.op = str[i];
            while (!op.empty() && opmap[str[i]] <= opmap[op.top().op]  ) {
                postr.push(op.top());
                op.pop();
            }
            op.push(temp);
            ++i;
        }
    }
    while (!op.empty()) {
        postr.push(op.top());
        op.pop();
    }
}
double opera(node i, node j,node pnode)
{
    char p = pnode.op;
    double o1 = i.num, o2 = j.num;
    switch (p)
    {
    case '+':return o1 + o2;
    case '-':return o1 - o2;
    case '*':return o1 * o2;
    case '/': return o1 == 0 ? 0 : o1 / o2;
    }
}
double calculate()
{
    node op1, op2; double result;
    while (!postr.empty())
    {
        if (postr.front().flag) {//操作数
            op.push(postr.front());
            postr.pop();
        }
        else {
            op2=op.top(); 
            op.pop();
            op1=op.top();
            op.pop();
            result = opera(op1, op2, postr.front());
            postr.pop();
            op1.num = result;
            op.push(op1);
        }
    }
    return op.top().num;
}
void clean()
{
    while (!op.empty()) {
        op.pop();
    }
    while (!postr.empty()) {
        postr.pop();
    }
}
int main()
{  
    opmap['+'] = opmap['-'] = 1;
    opmap['*'] = opmap['/'] = 2;
    while (getline(cin, str), str != "0") {
        clean();//初始化栈；
        to_post();
        cout << str << "=";
      //  print_post();
        cout << calculate()<<endl;
    }
    return 0;
}