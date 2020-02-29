#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
const int maxn = 1001;

int fruit[maxn], n;

void create(int n)
{
	for (int i = 1; i <= n; i++)
	{
		cin >> fruit[i];
	}
}
int sortway()
{
	int j, temp, sum = 0;
	sort(fruit, fruit + n + 1);
	for (int i = 2; i <= n; i++)
	{
		fruit[i] += fruit[i - 1];
		sum += fruit[i];
		j = i;
		temp = fruit[i];
		while (fruit[j + 1] < temp && j + 1 <= n) {
			fruit[j] = fruit[j + 1];
			++j;
		}
		fruit[j] = temp;
	}
	return sum;
}
/*Ð¡¶¥¶Ñ*/
void AdjustDown(int low, int high)
{
	int i = low, j = i * 2;
	while (j <= high)
	{
		if (fruit[j] > fruit[j + 1] && j + 1 <= high)++j;
		if (fruit[j] < fruit[i]) {
			swap(fruit[i], fruit[j]);
			i = j;
			j = i * 2;
		}
		else break;
	}
}
/*Ð¡¶¥¶Ñ*/
void createHeap()
{
	for (int i = n / 2; i >= 1; i--)
	{
		AdjustDown(i, n);
	}
}
int getTop()
{
	swap(fruit[1],fruit[n--]);
	AdjustDown(1, n);
	return fruit[n + 1];
}
void UpAdjust(int low, int high)
{
	int i = high, j = i / 2;
	while (j >= low)
	{
		if (fruit[i] < fruit[j]) {
			swap(fruit[i], fruit[j]);
			i = j;
			j = i / 2;
		}
		else break;
	}
}
void insert(int x)
{
	fruit[++n] = x;
	UpAdjust(1, n);
}
void huffman()
{
	int temp,sum = 0;
	while(n!=1)
	{
		temp = getTop() + getTop();
		sum += temp;
		insert(temp);
	}
	cout << sum<<endl;
}
priority_queue<long long, vector<long long>, greater<long long > > q;
void que(int n)
{
	long long temp,x,y,ans=0;
	for (int i = 0; i < n; i++)
	{
		scanf("%lld", &temp);
		q.push(temp);
	}
	while (q.size()>1)
	{
		x = q.top();
		q.pop();
		y = q.top();
		q.pop();
		q.push(x + y);
		ans += x + y;
	}
	printf("%lld", ans);
}
int main()
{
	cin >> n;
	//create(n);
	//createHeap();
	//sortway()
	//huffman();

	que(n);
}