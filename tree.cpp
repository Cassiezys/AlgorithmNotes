#include<iostream>

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
int main()
{
	int data[5] = { 5,4,3,2,1 };
	Node* root = create(data, 5);
}