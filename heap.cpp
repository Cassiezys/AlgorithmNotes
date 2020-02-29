#include<iostream>
#include<vector>
using namespace std;
const int maxn = 100;
int heap[maxn], n = 10;

/*���µ��������ӽ��Ƚ�֪������high*/
void downAdjust(int low, int high)
{
	int i = low, j = 2 * i , temp; //jΪ���ӽ��
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
/*ɾ���Ѷ����Ѷ������һ��Ԫ�ؽ��� �� �ٵ����Ѷ���*/
void delTop()
{
	heap[1] = heap[n--];
	downAdjust(1, n);
}
/*���ϵ���������Ƚ� ֱ��С��low*/
void upAdjust(int low, int high)
{
	int i = high, j = low / 2; //jΪ�����
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
/*���Ԫ��*/
void insert(int x) {
	heap[++n] = x;
	upAdjust(1, n);
}
int main()
{
	vector<int> arr;
	/* 1-10 �±�*/
	for (int i = 0; i < 11; i++)
	{
		cin >> heap[i];
	}
	for (int i = n/2; i >= 1; i--)
	{
		downAdjust(i, n);//����ö�٣���n/2��ʼ������ֱ���Ѷ���
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