#include<iostream>
#include<map>

using namespace std;
const int maxn = 2020;
map<string, int> StringToInt;
map<int, string> IntToString;
map<string, int> Gang;
int G[maxn][maxn] = { 0 }, weight[maxn] = { 0 };//边权和点权值
int n, k, numP = 0;//通话对数，门限，总人数初始值为0；
bool visit[maxn] = { false };

int toInt(string name)
{
	if (StringToInt.find(name) != StringToInt.end()) {
		return StringToInt[name];
	}
	else {
		StringToInt[name] = numP;
		IntToString[numP] = name;
		return numP++;
	}
}
void Dfs(int vertex, int& head, int& numMember, int& totalValue)
{
	++numMember;
	visit[vertex] = true;
	if (weight[vertex] > weight[head]) {
		head = vertex;
	}
	for (int i = 0; i < numP; i++)
	{
		if (G[vertex][i] > 0) {
			totalValue += G[vertex][i];
			G[vertex][i] = 0;
			G[i][vertex] = 0;
			if (visit[i] == false) {
				Dfs(i, head, numMember, totalValue);
			}
		}
	}
}
void DfsTravel()
{
	for (int i = 0; i < numP; i++)
	{
		if (visit[i] == false) {
			int head = i, numMember = 0, totalValue = 0;
			Dfs(i, head, numMember, totalValue);
			if (numMember > 2 && totalValue > k) {
				Gang[IntToString[head]] = numMember;
			}
		}
	}
}
int main()
{
	int w;
	string p1, p2;
	cin >> n >> k;
	for (int i = 0; i < n; i++)
	{
		cin >> p1 >> p2 >> w;
		int d1 = toInt(p1);
		int d2 = toInt(p2);
		weight[d1] += w;
		weight[d1] += w;
		G[d1][d2] += w;
		G[d2][d1] += w;
	}
	DfsTravel();
	cout << Gang.size() << endl;
	for (map<string,int>::iterator it = Gang.begin(); it !=Gang.end(); it++)
	{
		cout << it->first << " " << it->second << endl;
	}
}