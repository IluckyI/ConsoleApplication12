#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstring>
#include <cstdbool>



typedef struct _Node
{
	char name[256];
	struct _Node* next;
} Node, *NodePtr;

int insertData(NodePtr *ppNode, const char* data);
void instructions(void)
{
	printf(/*"Enter your choice:\n"*/
		"1 to insert an element into the list.\n"
		"2 to delete an element from the list.\n"
		"3 to display List.\n"
		"4 to end.\n");
}

void processList(NodePtr list)
{
	//�����������������
	Node* pNode = list;
	printf("processlist is:\n");
	while (pNode)
	{
		printf("%s\t", pNode->name);
		pNode = pNode->next;
	}

	fputs("\n", stdout);
}

bool isEmpty(NodePtr list)
{
	return list == 0;
}

/**
* ��ָ���ڵ��׷�ӽڵ㣬�������ݸ�ֵ������ڵ㡣
* 1. ����б�Ϊ�գ������½ڵ㣬 ��ֵ
* 2. ֱ�������б�ĩ�ˣ������½ڵ�
*
* @author zf (09/01/2017)
*
* @param NodePtr   �б�ͷ�ڵ�ָ��
*
* @param const char*   ����
*
* @return int  ʧ�ܷ���-1�� �ɹ�����0
*/
int appendData(NodePtr *ppNode, const char* data)
{
	if (*ppNode == 0)
	{
		return insertData(ppNode, data);
	}

	NodePtr pNode = *ppNode;

	while (pNode->next != 0)
	{
		pNode = pNode->next;
	}


	Node* pNewNode = (Node*)malloc(sizeof(Node));
	if (pNewNode == 0)
	{
		return -1;
	}
	memset(pNewNode, 0, sizeof(Node));

	pNode->next = pNewNode;

	strcpy(pNewNode->name, data);

	return 0;

}
int insertData(NodePtr *ppNode, const char* data)
{
	NodePtr pCurNode = *ppNode;
	//if (pCurNode->name[0]==0)
	//{
	//	strcpy(pCurNode->name, data);
	//	return 0;
	//}
	if (pCurNode == 0) //��Ϊ�յ����������ڵ�λ��Ϊ�գ�
	{
		*ppNode = (NodePtr)malloc(sizeof(Node));
		memset(*ppNode, 0, sizeof(Node));
		pCurNode = *ppNode;
		//strcpy((*ppNode)->name, data);
		//strcpy(pNode->name, data);/??	
		//�������ݣ����ڵ����ݸ�ֵ��
		strcpy(pCurNode->name, data);
	}
	else
	{
		//1. ������Node
		Node* pNewNode = (Node*)malloc(sizeof(Node));
		memset(pNewNode, 0, sizeof(Node));
		//2. ����ڵ��next��ֵ����Node
		pNewNode->next = pCurNode->next;
		//3. 
		pCurNode->next = pNewNode;
		//�������ݣ����ڵ����ݸ�ֵ��
		strcpy(pNewNode->name, data);
	}
	//�������ݣ����ڵ����ݸ�ֵ��
	//strcpy(pCurNode->name, data);

	return 0;
}

int deleteData(NodePtr *ppNode, const char* data)
{
	if (ppNode == 0 || *ppNode == 0)
	{
		return -1;
	}
	NodePtr pNode = *ppNode;
	NodePtr preNode = 0;
	while (pNode != 0)
	{
		if (strcmp(pNode->name, data) == 0)
		{
			//1.��Ҫɾ���ڵ��next��ֵ����ǰһ���ڵ��next
			if (preNode == 0)//�����ͷ��㣬�͸����б�ͷָ��
			{
				*ppNode = (*ppNode)->next;
			}
			else
			{
				preNode->next = pNode->next;
			}
			//2. �ͷ�Ҫɾ���ڵ�ռ�õ��ڴ�
			free(pNode);
			break;
		}
		preNode = pNode;
		pNode = pNode->next;
	}
	return 0;
}

int main()
{
	NodePtr header = (Node*)malloc(sizeof(Node));
	Node* pCurNode = header;

	memset(header, 0, sizeof(Node));

	char name[256];
	
	int a = 0;
	
	instructions();
  
	while (a!=4)
	{
	    printf("Enter your choice:\n");		
		scanf("%d", &a);
		switch (a)
		{
		case 1:fputs("input insert name:\n", stdout);
			memset(name, 0, 256);
			scanf("%s", name);
			appendData(&header, name);
			//insertData(&header, name); 
			break;//�����½ڵ�	
		case 2:fputs("input delete name:\n", stdout);
			memset(name, 0, 256);
			scanf("%s", name);
			deleteData(&header, name);
			break;
		case 3: processList(header); break;

		}
		//fputs("input name:\n", stdout);
		//memset(name, 0, 256);
		//scanf("%s", name);
		//insertData(&header, name);//�����½ڵ�
		//processList(header);      //�������

	}


	return 0;
}