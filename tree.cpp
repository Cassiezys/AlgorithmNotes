#include<iostream>
#include<queue>
using namespace std;

struct Node {
	int data;
	Node* lchild;
	Node* rchild;
};


/*新建结点： 都是地址空间*/
Node* newNode(int data)
{
	/*申请一个地址空间*/
	Node* node = new Node;
	node->lchild = node->rchild = NULL;
	node->data = data;
	return node;
}

/*找到data并修改为modify*/
void search(Node* node, int data, int modify)
{
	if (node == NULL) {
		return;
	}
	if (node->data == data) {
		node->data = modify;
	}
	search(node->lchild, data, modify);
	search(node->rchild, data, modify);
}

/*插入：总是在叶子节点插入*/
void insert(Node*& node, int data)
{
	if (node == NULL) { // 结点不存在，结点地址为空； *node =NULL结点存在但没有内容
		node = newNode(data);
		return;
	}
	//找空结点
	if (node->lchild == NULL) {
		insert(node->lchild, data);
	}
	else {
		insert(node->rchild, data);
	}
}
/*创建一颗二叉树*/
Node* create(int data[], int n) {
	/*空根结点，结点内容为空，结点存在但没有内容*/
	Node* root = NULL;
	for (int i = 0; i < n; i++)
	{
		insert(root, data[i]);
	}
	return root;
}

//int pre[6] = { 1,2,4,5,3,6 }, in[6] = { 4,2,5,1,6,3 };
///* 先序中序确定一颗二叉树 */
//Node* recreate(int preL, int preR, int inL, int inR)
//{
//	if (preL > preR) return NULL;
//	Node* root = new Node;
//	root->data = pre[preL];
//	int k, ans;
//	for ( k = inL; k <= inR; k++)
//	{
//		if (in[k] == pre[preL])break;
//	}
//	ans = k - inL;//左子树的结点个数
//	/*[preL+1,preL+ans]先序遍历左子树 [inL,k-1]中序遍历左子树*/
//	root->lchild = recreate(preL + 1, preL + ans, inL, k - 1);//结点左孩子
//	root->rchild = recreate(preL + ans + 1, preR, k + 1, inR);//结点右孩子
//	return root;
//
//}
int post[7] = { 2,3,1,5,7,6,4 }, in[7] = { 1,2,3,4,5,6,7 };
/*后序中序确定一颗二叉树*/
Node* recreateback(int postL, int postR, int inL, int inR)
{
	if (postL > postR)return NULL;
	Node* root = new Node;
	root->data = post[postR];
	int k, ans;
	for (k = inL; k <= inR; k++)	{
		if (in[k] == post[postR]) break;
	}
	ans = inR - k;//右子树结点个数；//[postR-ans,posR-1]后序右子树[postL,postR-ans-1]后序左子树
	root->lchild = recreateback(postL, postR - 1 - ans, inL, k - 1);
	root->rchild = recreateback(postR - ans, postR - 1, k - 1, inR);
	return root;
}
int ans = 0, n = 7;
/*层次遍历*/
void bfs(Node* root)
{
	queue<Node*> Q;
	Node* p=NULL;
	Q.push(root);
	while (!Q.empty())
	{
		p = Q.front();
		cout << p->data;
		++ans;
		Q.pop();
		if (ans < n) cout << "*"; // 最后一片叶子后面没有空格
		if (p->lchild != NULL)Q.push(p->lchild);
		if (p->rchild != NULL)Q.push(p->rchild);
	}
}
int main()
{
	int data[5] = { 5,4,3,2,1 };
	Node* root = recreateback(0,6,0,6);
	bfs(root);
	return 0;
}