#include<iostream>
#include<string>
using namespace std;

typedef struct bign
{
	int d[1000];
	int len;
	bign() {
		memset(d, 0, sizeof(d));
		len = 0;
	}
}bign;

bign to_bign(string str)
{
	bign a;
	while (true)
	{
		if (str.empty())break;
		a.d[a.len++] = str.back()-'0';
		str.pop_back();
	}
	return a;
}
int compare(bign i, bign j)
{
	//i>j return 1; i<j return-1; i=j return 0;
	if (i.len > j.len) return 1;
	else if (i.len < j.len) return -1;
	for (int k = i.len - 1; k >= 0; k--)
	{
		if (i.d[k] == j.d[k])continue;
		return  i.d[k] > j.d[k] ?  1 : -1;
	}
	return 0;
}
bign add(bign a, bign b)
{
	bign c;
	int sum = 0, in = 0;
	for (int i = 0; i < a.len||i<b.len; i++)
	{
		sum = a.d[i] + b.d[i] + in;
		c.d[c.len++] = sum % 10;
		sum > 9 ? in = sum / 10 : in = 0;
	}
	if (in != 0) {
		c.d[c.len++] = in;
	}
	return c;
}
bign sub(bign a, bign b)
{
	bign c;
	int sum = 0, in = 0;
	for (int i = 0; i < a.len || i < b.len; i++)
	{
		if (a.d[i] < b.d[i]) {
			--a.d[i + 1];
			a.d[i] += 10;
		}
		c.d[c.len++] = a.d[i] - b.d[i];
	}
	/* 要去除高位的0 1234-1231 = 0003  c.len至少=1*/
	while (c.len - 1 > 0 && c.d[c.len - 1] == 0)--c.len;
	return c;
}

bign divide(bign a, int b, int &r)//可能会产生的余数
{
	bign c;
	int sum;
	c.len = a.len;//最多位数
	for (int i = a.len - 1; i >= 0; i--)
	{
		r = r * 10 + a.d[i];
		if (r < b) c.d[i] = 0;
		else {
			c.d[i] = r / b;
			r = r % b;
		}
	}
	while (c.len - 1 > 0 && c.d[c.len - 1] == 0)--c.len;
	return c;
}

void print_bign(bign a)
{
	for (int i = a.len - 1; i >= 0; i--)
	{
		cout << a.d[i];
	}
	cout<<endl;
}
int main()
{
	string str;
	cin >> str;
	bign a = to_bign(str);
	cin >> str;
	bign b = to_bign(str);
	int r=0;
	print_bign(divide(a, 35, r));
}