#include<iostream>
#include<vector>
using namespace std;
const int maxn = 100;
int heap[maxn], n = 10;

/*向下调整：与子结点比较知道大于high*/
void downAdjust(int low, int high)
{
	int i = low, j = 2 * i , temp; //j为孩子结点
	while (j <= high)
	{
		if(heap[j] < heap[j + 1]&&j+1<=high) ++j;
 		if (heap[i] < heap[j]) {
			temp = heap[i];
			heap[i] = heap[j];
			heap[j] = temp;
			i = j;
			j = 2 * i;
		}else break;
	}
}
/*删除堆顶：堆顶和最后一个元素交换 ： 再调整堆顶。*/
void delTop()
{
	heap[1] = heap[n--];
	downAdjust(1, n);
}
/*向上调整：与结点比较 直到小于low*/
void upAdjust(int low, int high)
{
	int i = high, j = low / 2; //j为父结点
	while (j >= low)
	{
		if (heap[i] > heap[j]) {
			swap(heap[i], heap[j]);
			i = j;
			j = i / 2;
		}
		else break;
	}
}
/*添加元素*/
void insert(int x) {
	heap[++n] = x;
	upAdjust(1, n);
}
int main()
{
	vector<int> arr;
	/* 1-10 下标*/
	for (int i = 0; i < 11; i++)
	{
		cin >> heap[i];
	}
	for (int i = n/2; i >= 1; i--)
	{
		downAdjust(i, n);//逆向枚举，从n/2开始调整，直到堆顶。
	}
	for (int i = 1; i <= 10; i++)
	{
		swap(heap[1], heap[n - i+1]);
		downAdjust(1, n - i);
	}
	for (int i = 0; i <=n; i++)
	{
		cout << heap[i] << " ";
	}
	return 0;
}