#include<iostream>
#include<vector>
#include<queue>
using namespace std;
const int maxn = 100;
const int INF = 1000000000;
struct Node
{
	int vertex;
	int distance;
	Node(int v,int d):vertex(v),distance(d){}
	bool operator < (const Node& b)const { //使用引用效率高
		return distance > b.distance;
	}
};
int G[maxn][maxn],lowcost[maxn];
vector<Node> Adj[maxn];
bool book[maxn] = { false };
int N, M, st;
void PrimHeap(int& sum)
{
	memset(book, false, sizeof(book));
	sum = 0;
	int ans = N-1;//需要访问N-1个点
	priority_queue<Node> Q;
	for (int i = 0; i < Adj[st].size(); i++)
	{
		Q.push(Adj[st][i]);
	}
	book[st] = true;
	while (!Q.empty() && ans)
	{
		Node node = Q.top();
		Q.pop();
		if (book[node.vertex])continue;//访问过了便不再访问
		book[node.vertex] = true;
		sum += node.distance;
		ans--;
		int u = node.vertex;
		for (int j = 0; j < Adj[u].size(); j++)
		{
			int v = Adj[u][j].vertex;
			int dis = Adj[u][j].distance;
			if (book[v] == false) {
				Q.push(Adj[u][j]);
			}
		}
	}
}

void Primheap(int& sum)
{
	memset(book, false, sizeof(book));
	priority_queue<Node> Q;
	for (int i = 0; i < Adj[st].size(); i++)
	{
		Q.push(Adj[st][i]);
	}
	sum = 0;
	book[st] = true;
	int ans = N-1;
	while (!Q.empty()&&ans)
	{
		Node node = Q.top(); Q.pop();
		if (book[node.vertex])continue;
		book[node.vertex] = true;
		int u = node.vertex;
		sum += node.distance;
		ans--;
		for (int j = 0; j < Adj[u].size(); j++)
		{
			if (book[Adj[u][j].vertex] == false) {
				Q.push(Adj[u][j]);
			}
		}
	}
}
void Prim(int &sum)
{
	memset(book, false, sizeof(book));
	fill(lowcost, lowcost + N, INF);
	lowcost[st] = 0;
	sum = 0;
	for (int i = 0; i < N; i++)
	{
		int u = -1, min = INF;
		for (int j = 0; j < N; j++)
		{
			if (book[j]==false && lowcost[j] < min) {
				u = j;
				min = lowcost[j];
			}
		}
		if (u == -1)return;
		book[u] = true;
		sum += lowcost[u];
		for (int j = 0; j < N; j++)
		{
			if (book[j] == false && G[u][j] < lowcost[j]) {
				lowcost[j] = G[u][j];
			}
		}
	}
}
void Prim2(int& sum)
{
	memset(book, false, sizeof(book));
	fill(lowcost, lowcost + N, INF);
	sum = 0;
	lowcost[st] = 0;
	for (int i = 0; i < N; i++)
	{
		int u = -1, min = INF;
		for (int j = 0; j < N; j++)
		{
			if (book[j] == false && lowcost[j] < min) {
				u = j;
				min = lowcost[j];
			}
		}
		if (u == -1)return;
		book[u] = true;
		sum += lowcost[u];
		for (int j = 0; j < Adj[u].size(); j++)
		{
			int v = Adj[u][j].vertex;
			int dis = Adj[u][j].distance;
			if (book[v] == false && dis < lowcost[v]) {
				lowcost[v] = dis;
			}
		}
	}

}
void init()
{
	fill(G[0], G[0] + maxn * maxn, INF);
	cin >> N >> M >>st;
	int u, v, w;
	for (int i = 0; i < M; i++)
	{
		cin >> u >> v >> w;
		G[u][v] = w;
		G[v][u] = w;
		Adj[u].push_back(Node(v, w));
		Adj[v].push_back(Node(u, w));
	}
}
int main()
{
	int sum=0;
	init();
	Primheap(sum);
	cout << sum;
	return 0;
}