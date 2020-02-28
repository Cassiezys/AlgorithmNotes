#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;

struct Node {
	int data;
	int height;
	Node* lchild;
	Node* rchild;
};

/*获得该点的高度*/
int getHeight(Node* node) {
	if (node == NULL) return 0;
	return node->height;
}
/*求该点的平衡因子*/
int getBalanceFator(Node* node) {
	return (getHeight(node->lchild) - getHeight(node->rchild));
}
/*只是更新其中高度，不需要改变结点排列，不需要取地址符号& */
void updateHeight(Node* node)
{
	node->height = max(getHeight(node->lchild), getHeight(node->rchild)) + 1;
}
/*新建结点，默认为1*/
Node* newNode(int data)
{
	Node* node = new Node;
	node->height = 1;
	node->lchild = NULL;
	node->rchild = NULL;
	node->data = data;
	return node;
}
/*左旋，右旋操作，需要修改二叉树结点的排列顺序，要带取地址符号& */
void L(Node* &root)
{
	Node* temp = root->rchild;
	root->rchild = temp->lchild;
	temp->lchild = root;
	updateHeight(root);
	updateHeight(temp);
	root = temp;
}
void R(Node*& root)
{
	Node* temp = root->lchild;
	root->lchild = temp->rchild;
	temp->rchild = root;
	updateHeight(root);
	updateHeight(temp);
	root = temp;
}
Node* leftMax(Node* root)
{
	while (root->rchild != NULL) {
		root = root->rchild;
	}
	return root;
}
Node* rightMin(Node* root)
{
	while (root->lchild != NULL) {
		root = root->lchild;
	}
	return root;
}
void delNode(Node* &root, int data)
{
	if (root == NULL)return;
	if (root->data == data) {
		if (root->lchild == NULL && root->rchild == NULL)root = NULL;
		else if (root->lchild != NULL) {
			Node* pre = leftMax(root->lchild);
			root->data = pre->data;
			delNode(root->lchild, pre->data);
		}
		else if (root->rchild != NULL) {
			Node* post = rightMin(root->rchild);
			root->data = post->data;
			delNode(root->rchild, post->data);
		}
	}else if (root->data > data) {
		delNode(root->lchild, data);
	}
	else {
		delNode(root->rchild, data);
	}
}
/*插入，每次插入之后更新结点高度并判断平衡因子平衡与否；
插左边可能+2，右边可能 -2；正负有别,注意区分*/
void insert(Node*& root, int data)
{
	if (root == NULL) {
		root = newNode(data);
	}
	if (root->data == data) return;
	if (root->data < data) {
		insert(root->rchild, data);
		updateHeight(root);
		if (getBalanceFator(root) == -2) {
			if (getBalanceFator(root->rchild) == -1) {//都在右边 对根左旋
				L(root);
			}
			else if (getBalanceFator(root->rchild) == 1) {//先右子树右旋，再根左旋
				R(root->rchild);
				L(root);
			}
		}
	}
	else {
		insert(root->lchild, data);
		updateHeight(root);
		if (getBalanceFator(root) == 2) {
			if (getBalanceFator(root->lchild) == 1) {
				R(root);
			}
			else if (getBalanceFator(root->lchild) == -1) {
				L(root->lchild);
				R(root);
			}
		}
	}
}
/*创建avl*/
Node* create(vector<int> a, int n)
{
	Node* root = NULL;
	for (int i = 0; i < n; i++)
	{
		insert(root, a[i]);
	}
	return root;
}
/*层次遍历*/
void bfs(Node* root)
{
	int Nto = 1;
	Node* p=NULL;
	queue<Node*> Q;
	Q.push(root);
	while (!Q.empty())
	{
		p = Q.front(); Q.pop();
		if (Nto != p->height)cout << endl;
		cout << p->data<<"("<<p->height<<")"<<" ";
		if (p->lchild != NULL)Q.push(p->lchild);
		if (p->rchild != NULL)Q.push(p->rchild);
	}
	cout << endl;
}
/*中序遍历：二叉排序树中序单调*/
void midOrde(Node* root)
{
	if (root == NULL) return;
	midOrde(root->lchild);
	cout << root->data << " ";
	midOrde(root->rchild);
}
int main()
{
	vector<int> a = { 3,2,5,1,8 };
	Node* root = create(a, 5);
	midOrde(root);
	cout << endl;
	delNode(root, 2);
	midOrde(root);
}