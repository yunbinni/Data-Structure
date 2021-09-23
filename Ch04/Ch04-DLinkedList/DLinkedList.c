#include <stdio.h>
#include "DLinkedList.h"

void ListInit(List* plist)
{
	plist->head = (Node*)malloc(sizeof(Node));		// 더미 노드의 생성
	plist->head->next = NULL;
	plist->comp = NULL;
	plist->numOfData = 0;
}

void FInsert(List* plist, LData data)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;

	newNode->next = plist->head->next;				// 새 노드가 다른 노드를 가리키게 함
	plist->head->next = newNode;					// 더미 노드가 새 노드를 가리키게 함

	(plist->numOfData)++;
}

void SInsert(List* plist, LData data)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	Node* pred = plist->head;		// pred가 더미를 가리키게 함 (핵심!)
	newNode->data = data;

	// pred가 리스트 끝에 도달하지 않으면서 comp기준상 역순이 되기 전까지 pred를 옮김
	while (pred->next != NULL && plist->comp(data, pred->next->data) != 0)
		pred = pred->next;

	newNode->next = pred->next;
	pred->next = newNode;

	(plist->numOfData)++;
}

void LInsert(List* plist, LData data)
{
	if (plist->comp == NULL)		// 정렬 기준이 마련되지 않았다면,
		FInsert(plist, data);		// 머리에 노드를 추가
	else
		SInsert(plist, data);		// 그렇지 않으면, 정렬기준에 근거하여 추가
}

int LFirst(List* plist, LData* pdata)
{
	if (plist->head->next == NULL)	// 더미노드가 NULL을 가리킬 때
		return FALSE;

	plist->before = plist->head;
	plist->cur = plist->head->next;

	*pdata = plist->cur->data;

	return TRUE;
}

int LNext(List* plist, LData* pdata)
{
	if (plist->cur->next == NULL)	// cur가 NULL을 가리킬 때
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
	plist->cur = plist->before;					// 참조 위치도 재조정해야 한다.
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
	plist->comp = comp;		// 함수 등록
}