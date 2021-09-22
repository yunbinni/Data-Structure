#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "NameCard.h"

NameCard* MakeNameCard(char* name, char* phone)
{
	NameCard* newCard = (NameCard*)malloc(sizeof(NameCard));
	strcpy(newCard->name, name);
	strcpy(newCard->phone, phone);

	return newCard;
}

void showNameCardInfo(NameCard* pcard)
{
	printf("[�̸�] %s \n", pcard->name);
	printf("[��ȣ] %s \n\n", pcard->phone);
}

int NameCompare(NameCard* pcard, char* name)
{
	strcmp(pcard->name, name);
}

void ChangePhoneNum(NameCard* pcard, char* phone)
{
	strcpy(pcard->phone, phone);
}