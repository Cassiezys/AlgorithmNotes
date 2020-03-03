#include<iostream>
#include<vector>
#include<set>
#include<queue>
using namespace std;
const int maxn = 100;
const int INF = 0x3fffffff;

int N, M, st, ed;
int G[maxn][maxn], W[maxn];
int dist[maxn], path[maxn], weight[maxn],num[maxn];
bool book[maxn] = { false };
void Dijkstra(int s)
{
	fill(dist, dist + N, INF);
	memset(path, -1, sizeof(path));
	memset(book, false, sizeof(book));
	memset(weight, 0, sizeof(weight));
	memset(num, 0, sizeof(num));
	dist[s] = 0;
	num[s] = 1;
	path[s] = -1;
	weight[s] = W[s];
	for (int i = 0; i < N; i++)
	{
		int u = -1, min = INF;
		for (int  j = 0; j < N; j++)
		{
			if (book[j] == false && min > dist[j]) {
				u = j;
				min = dist[j];
			}
		}
		if (u == -1)return;
		book[u] = true;
		for (int j = 0; j < N; j++)
		{
			if (book[j] == false && G[u][j] < INF) {
				if (dist[j] > dist[u] + G[u][j]) {
					dist[j] = dist[u] + G[u][j];
					weight[j] = weight[u] + W[j];
					path[j] = u;
					num[j] = num[u];
				}
				else if (dist[j] == dist[u] + G[u][j]) {
					if (weight[j] < weight[u] + W[j]) {
						weight[j] = weight[u] + W[j];
						path[j] = u;
					}
					num[j] += num[u];
				}
			}
		}
	}
}
///dijsktra+dfs
vector<int> pre[maxn];//记录每个点的前驱
void dijkstra(int s)
{
	fill(dist, dist + N, INF);
	memset(book, false, sizeof(book));
	dist[s] = 0;
	for (int i = 0; i < N; i++)
	{
		int u = -1, min = INF;
		for (int j = 0; j < N; j++)
		{
			if (book[j] == false && min > dist[j]) {
				u = j;
				min = dist[j];
			}
		}
		if (u == -1)return;
		book[u] = true;
		for (int j = 0; j < N; j++)
		{
			if (book[j] == false && G[u][j] < INF) {
				if (dist[j] > dist[u] + G[u][j]) {
					dist[j] = dist[u] + G[u][j];
					pre[j].clear();
					pre[j].push_back(u);
				}
				else if (dist[j] == dist[u] + G[u][j]) {
					pre[j].push_back(u);
				}
			}
		}
	}
}
vector<int> bestpath, temppath;
int value, tempvalue;
void dfs(int v)
{
	if (v == st) {
		temppath.push_back(st);
		tempvalue = 0;
		for (int i = temppath.size() - 1; i >= 0; i--)
		{
			tempvalue += W[i];
		}
		if (tempvalue > value) {
			value = tempvalue;
			bestpath = temppath;
		}
		temppath.pop_back();
		return;
	}
	temppath.push_back(v);
	for (int i = 0; i < pre[v].size(); i++)
	{
		dfs(pre[v][i]);
	}
	temppath.pop_back();
}
/*看有没有负边；并且邻接表比较适用,*/
struct Node
{
	int vertex;
	int distance;
	Node(int v,int d):vertex(v),distance(d){}
};
vector<Node> Adj[maxn];
set<int> preset[maxn];//记录前驱
bool bellman(int s)
{
	fill(dist, dist + N, INF);
	memset(num, 0, sizeof(num));
	dist[s] = 0;
	num[s] = 1;
	weight[s] = W[s];
	for (int i = 0; i < N-1; i++)
	{
		for (int u = 0; u < N; u++) {
			for (int j = 0; j < Adj[u].size(); j++)
			{
				int v = Adj[u][j].vertex;
				int dis = Adj[u][j].distance;
				if (dist[v] > dist[u] + dis) {
					dist[v] = dist[u] + dis;
					weight[v] = weight[u] + W[v];
					preset[v].clear();
					preset[v].insert(u);
					num[v] = num[u];
				}
				else if (dist[v] == dist[u] + dis) {
					if (weight[v] < weight[u] + W[v]) {
						weight[v] = weight[u] + W[v];
					}
					preset[v].insert(u);
					num[v] = 0;
					for (set<int>::iterator it=preset[v].begin();it!=preset[v].end(); it++)
					{
						num[v] += num[*it];
					}
				}
			}
		}
	}
	for (int u = 0; u < N; u++) {
		for (int j = 0; j < Adj[u].size(); j++)
		{
			int v = Adj[u][j].vertex;
			int dis = Adj[u][j].distance;
			if (dist[v] > dist[u] + dis) {
				return false;//有负边
			}
		}
	}
	return true;
}
int show[maxn];//每个数字出现的次数
/* 改进bellman 并且判断又没有环 */
bool SPFA(int s)
{
	memset(book, false, sizeof(book));
	memset(weight, 0, sizeof(weight));
	memset(show, 0, sizeof(show));
	memset(num, 0, sizeof(num));
	fill(dist, dist + N, INF);
	memset(path, -1, sizeof(path));
	queue<int> Q;
	dist[s] = 0;
	weight[s] = W[s];
	show[s]++;
	book[s] = true;
	Q.push(s);
	num[s] = 1;
	while (!Q.empty())
	{
		int u = Q.front(); Q.pop();
		book[u] = false;
		for (int j = 0; j < Adj[u].size(); j++)
		{
			int v = Adj[u][j].vertex;
			int dis = Adj[u][j].distance;
			if (dist[v] > dist[u] + dis) {
				dist[v] = dist[u] + dis;
				weight[v]=weight[u] + W[v];
				path[v] = u;
				num[v] = num[u];
				if (book[v] == false) {
					book[v] = true;
					show[v]++;
					Q.push(v);
					if (show[v] >= N)return false;
				}
			}
			else if (dist[v] == dist[u] + dis) {
				if (weight[v] < weight[u] + W[v]) {
					weight[v] = weight[u] + W[v];
				}
				path[v] = u;
				num[v] += num[u];
				if (book[v] == false) {
					book[v] = true;
					show[v]++;
					Q.push(v);
					if (show[v] >= N)return false;
				}
			}
		}
	}
	return true;
}
void init()
{
	cin >> N >> M>> st>> ed;
	for (int i = 0; i < N; i++)
	{
		cin >> W[i];
	}
	fill(G[0], G[0] + maxn * maxn, INF);
	int v1, v2, w;
	for (int i = 0; i < M; i++)
	{
		cin >> v1 >> v2 >> w;
		G[v1][v2] = w;
		G[v2][v1] = w;
		Adj[v1].push_back(Node(v2, w));
		Adj[v2].push_back(Node(v1, w));
	}
}
void printdfs(int s)
{
	if (path[s] == -1) {
		cout << s << " ";
		return;
	}
	printdfs(path[s]);
	cout << s << " ";
}
void iteraPath()
{
	for (vector<int>::iterator it=bestpath.begin();it!=bestpath.end();it++)
	{
		cout << *it << " ";
	}
	cout << endl << value;
}
int main()
{
	init();

	Dijkstra(st);
	printdfs(ed);

	cout << endl;
	cout << num[ed] << " " << weight[ed];

//	dijkstra(st);
//	dfs(ed);
//	iteraPath();

//	bellman(st);
//	cout << num[ed] << " " << weight[ed];

//	SPFA(st);
//	printdfs(ed);
//	cout <<endl << num[ed] << " " << weight[ed];
	return 0;
}