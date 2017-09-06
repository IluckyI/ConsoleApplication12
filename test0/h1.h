#pragma once
#include<cstdio>
#include<cstdlib>
#include<cstdint>
#include<cstring>

struct Node
{
	char name[256];
	Node *next;

};

int main()
{
	Node *header = (Node*)malloc(sizeof(Node));
	Node* pCurNode = header;

	memset(header, 0, sizeof(Node));

	char name[256];

	while (1)
	{
		fputs("input name:\n", stdout);
		memset(name, 0, 256);
		scanf("%s", name);

		//找到可用节点



		while (pCurNode->name[0] != 0)
		{

			if (pCurNode->next == 0)
			{
				Node* pNode = (Node*)malloc(sizeof(Node));
				memset(pNode, 0, sizeof(Node));
				pCurNode->next = pNode;

			}
			pCurNode = pCurNode->next;
		}

		strcpy(pCurNode->name, name);//赋值


		Node* pNode = header;

		while (pNode != NULL) //遍历单链表，输出数据
		{
			printf("%s\t", pNode->name);
			pNode = pNode->next;
		}

		fputs("\n", stdout);

	}







	return 0;
}



