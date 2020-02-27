#include<iostream>

using namespace std;

struct Node {
	int data;
	Node* lchild;
	Node* rchild;
};


/*�½���㣺 ���ǵ�ַ�ռ�*/
Node* newNode(int data)
{
	/*����һ����ַ�ռ�*/
	Node* node = new Node;
	node->lchild = node->rchild = NULL;
	node->data = data;
	return node;
}

/*�ҵ�data���޸�Ϊmodify*/
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

/*���룺������Ҷ�ӽڵ����*/
void insert(Node*& node, int data)
{
	if (node == NULL) { // ��㲻���ڣ�����ַΪ�գ� *node =NULL�����ڵ�û������
		node = newNode(data);
		return;
	}
	//�ҿս��
	if (node->lchild == NULL) {
		insert(node->lchild, data);
	}
	else {
		insert(node->rchild, data);
	}
}
/*����һ�Ŷ�����*/
Node* create(int data[], int n) {
	/*�ո���㣬�������Ϊ�գ������ڵ�û������*/
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