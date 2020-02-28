#include<iostream>
#include<queue>
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

//int pre[6] = { 1,2,4,5,3,6 }, in[6] = { 4,2,5,1,6,3 };
///* ��������ȷ��һ�Ŷ����� */
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
//	ans = k - inL;//�������Ľ�����
//	/*[preL+1,preL+ans]������������� [inL,k-1]�������������*/
//	root->lchild = recreate(preL + 1, preL + ans, inL, k - 1);//�������
//	root->rchild = recreate(preL + ans + 1, preR, k + 1, inR);//����Һ���
//	return root;
//
//}
int post[7] = { 2,3,1,5,7,6,4 }, in[7] = { 1,2,3,4,5,6,7 };
/*��������ȷ��һ�Ŷ�����*/
Node* recreateback(int postL, int postR, int inL, int inR)
{
	if (postL > postR)return NULL;
	Node* root = new Node;
	root->data = post[postR];
	int k, ans;
	for (k = inL; k <= inR; k++)	{
		if (in[k] == post[postR]) break;
	}
	ans = inR - k;//��������������//[postR-ans,posR-1]����������[postL,postR-ans-1]����������
	root->lchild = recreateback(postL, postR - 1 - ans, inL, k - 1);
	root->rchild = recreateback(postR - ans, postR - 1, k - 1, inR);
	return root;
}
int ans = 0, n = 7;
/*��α���*/
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
		if (ans < n) cout << "*"; // ���һƬҶ�Ӻ���û�пո�
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