#include <stdio.h>
#include "DLinkedList.h"

void ListInit(List* plist)
{
	plist->head = (Node*)malloc(sizeof(Node));		// ���� ����� ����
	plist->head->next = NULL;
	plist->comp = NULL;
	plist->numOfData = 0;
}

void FInsert(List* plist, LData data)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;

	newNode->next = plist->head->next;				// �� ��尡 �ٸ� ��带 ����Ű�� ��
	plist->head->next = newNode;					// ���� ��尡 �� ��带 ����Ű�� ��

	(plist->numOfData)++;
}

void SInsert(List* plist, LData data)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	Node* pred = plist->head;		// pred�� ���̸� ����Ű�� �� (�ٽ�!)
	newNode->data = data;

	// pred�� ����Ʈ ���� �������� �����鼭 comp���ػ� ������ �Ǳ� ������ pred�� �ű�
	while (pred->next != NULL && plist->comp(data, pred->next->data) != 0)
		pred = pred->next;

	newNode->next = pred->next;
	pred->next = newNode;

	(plist->numOfData)++;
}

void LInsert(List* plist, LData data)
{
	if (plist->comp == NULL)		// ���� ������ ���õ��� �ʾҴٸ�,
		FInsert(plist, data);		// �Ӹ��� ��带 �߰�
	else
		SInsert(plist, data);		// �׷��� ������, ���ı��ؿ� �ٰ��Ͽ� �߰�
}

int LFirst(List* plist, LData* pdata)
{
	if (plist->head->next == NULL)	// ���̳�尡 NULL�� ����ų ��
		return FALSE;

	plist->before = plist->head;
	plist->cur = plist->head->next;

	*pdata = plist->cur->data;

	return TRUE;
}

int LNext(List* plist, LData* pdata)
{
	if (plist->cur->next == NULL)	// cur�� NULL�� ����ų ��
		return FALSE;

	plist->before = plist->cur;
	plist->cur = plist->cur->next;

	*pdata = plist->cur->data;

	return TRUE;
}

LData LRemove(List* plist)
{
	Node* rpos = plist->cur;
	LData rdata;

	plist->before->next = plist->cur->next;
	plist->cur = plist->before;					// ���� ��ġ�� �������ؾ� �Ѵ�.
	free(rpos);
	(plist->numOfData)--;

	return rdata;
}

int LCount(List* plist)
{
	return plist->numOfData;
}

void SetSortRule(List* plist, int (*comp)(LData d1, LData d2))
{
	plist->comp = comp;		// �Լ� ���
}