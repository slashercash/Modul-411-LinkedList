#include "stdio.h"
#include "stdlib.h"
#include <time.h>
#include <string.h>

#pragma warning(disable:6011)

typedef struct Person {
	char Gender[3];
	char LastName[50];
	char FirstName[50];
	int Vintage;
	struct Person* pNext;
	struct Person* pPrev;
} struPerson;

Person* CreateList();
Person* DeleteList(Person*);
Person* DeleteSpecificElement(Person*);
Person* Delete(Person*, char[], char[], char[], int);
Person* Delete(Person*);
Person* SortList(Person*);
Person* Sort(void (*f)(Person*&, Person*&, Person*&), Person*);
int GetRandomVintage();
int GetUsersChoice();
char GetRandomGender();
char GetRandomCharacter();
void DisplayList(Person*);
void ShowMenu();
void SortGenderAsc(Person*&, Person*&, Person*&);
void SortGenderDesc(Person*&, Person*&, Person*&);
void SortLastNameAsc(Person*&, Person*&, Person*&);
void SortLastNameDesc(Person*&, Person*&, Person*&);
void SortFirstNameAsc(Person*&, Person*&, Person*&);
void SortFirstNameDesc(Person*&, Person*&, Person*&);
void SortVintageAsc(Person*&, Person*&, Person*&);
void SortVintageDesc(Person*&, Person*&, Person*&);
void SwitchElements(Person*&, Person*&, Person*&);

int main()
{
	// Initialize the pseudo-random number-generator and use the current time since midnight in milliseconds as the seed
	srand((unsigned)time(NULL));
	Person* pHead = NULL;

	int repeat = 1;

	while (repeat == 1)
	{
		ShowMenu();

		switch (GetUsersChoice())
		{
		case 1:
			// Liste erstellen
			pHead = CreateList();
			break;
		case 2:
			// Liste loeschen
			pHead = DeleteList(pHead);
			break;
		case 3:
			// Spezifisches Element loeschen
			pHead = DeleteSpecificElement(pHead);
			break;
		case 4:
			// Liste sortieren
			pHead = SortList(pHead);
			break;
		case 5:
			// Liste ausgeben
			DisplayList(pHead);
			break;
		case 6:
			// Programm beenden
			repeat = 0;
			break;
		case 0:
			printf("Ungueltige Eingabe\n");
			break;
		}
	}

	system("Pause");
}

void ShowMenu()
{
	printf("Liste erstellen   > 1\n");
	printf("Liste loeschen    > 2\n");
	printf("Elemente loeschen > 3\n");
	printf("Liste sortieren   > 4\n");
	printf("Liste ausgeben    > 5\n");
	printf("Programm beenden  > 6\n");
}

int GetUsersChoice()
{
	int command = 0;

	printf("\nIhre Auswahl      > ");
	scanf_s("%i", &command);
	_fgetchar();

	if (command == 1 ||
		command == 2 ||
		command == 3 ||
		command == 4 ||
		command == 5 ||
		command == 6)
	{
		return command;
	}
	else
	{
		return 0;
	}
}

// Liste erstellen
//*****************

Person* CreateList()
{
	int numberOfPersons = 0;
	struPerson* pFirst = NULL;
	struPerson* pStart = NULL;
	struPerson* pEnd = NULL;

	printf("Wie viele Personen moechten Sie generieren? ");
	scanf_s("%i", &numberOfPersons);
	_fgetchar();

	// Elemente erzeugen, mit Daten abfüllen
	for (int i = 0; i < numberOfPersons; i++) {
		struPerson* pElement = (struPerson*)malloc(sizeof(struPerson));

		pElement->Gender[0] = GetRandomGender();
		pElement->Gender[1] = '\0';
		pElement->LastName[0] = GetRandomCharacter();
		pElement->LastName[1] = '\0';
		pElement->FirstName[0] = GetRandomCharacter();
		pElement->FirstName[1] = '\0';
		pElement->Vintage = GetRandomVintage();

		if (i == 0)
		{
			pFirst = pElement;
		}
		else if (i + 1 != numberOfPersons)
		{
			pElement->pPrev = pStart;
			pStart->pNext = pElement;
		}
		else
		{
			pElement->pPrev = pStart;
			pStart->pNext = pElement;
			pElement->pNext = pFirst;
			pFirst->pPrev = pElement;
		}
		pStart = pElement;

	}

	return pFirst;
}

char GetRandomGender()
{
	return "MF"[rand() % 2];
}

char GetRandomCharacter()
{
	return 'A' + (rand() % 26);
}

int GetRandomVintage()
{
	return 1900 + (rand() % 120);
}

// Liste loeschen
//****************

Person* DeleteList(Person* pHead)
{
	int deleteCounter = 0;
	Person* pLast = pHead->pPrev;
	Person* pTmp = pHead;

	while (pTmp != NULL)
	{
		Person* pDelete = pTmp;
		pTmp = pTmp != pLast ? pTmp->pNext : NULL;
		free(pDelete);
		deleteCounter++;
	}
	printf("\nListe wurde geloescht. Anzahl: %i\n", deleteCounter);

	return NULL;
}

// Spezifisches Element loeschen
//*******************************

Person* DeleteSpecificElement(Person* pHead)
{
	char gender[3];
	char lastName[50];
	char firstName[50];
	int vintage;

	printf("\nWelche Personen moechten Sie loeschen?\n");

	printf("\nGeschlecht [m/f]  > ");
	fgets(gender, sizeof(gender), stdin);

	printf("Nachname          > ");
	fgets(lastName, sizeof(lastName), stdin);

	printf("Vorname           > ");
	fgets(firstName, sizeof(firstName), stdin);

	printf("Jahrgang          > ");
	scanf_s("%i", &vintage);
	_fgetchar();

	char* token = NULL;

	return Delete(pHead, strtok_s(gender, "\n", &token), strtok_s(lastName, "\n", &token), strtok_s(firstName, "\n", &token), vintage);
}

Person* Delete(Person* pHead, char gender[], char lastName[], char firstName[], int vintage)
{
	int deleteCounter = 0;
	int loop = 1;
	Person* pLast = pHead->pPrev;

	while (loop == 1)
	{
		loop = pHead == pLast ? 0 : 1;

		if (strcmp(gender, pHead->Gender) == 0 &&
			strcmp(lastName, pHead->LastName) == 0 &&
			strcmp(firstName, pHead->FirstName) == 0 &&
			vintage == pHead->Vintage)
		{
			pHead = Delete(pHead);
			deleteCounter++;
		}

		pHead = pHead->pNext;
	}

	printf("%d %s %s deleted\n\n", deleteCounter, deleteCounter > 1 ? "people" : "person", deleteCounter > 1 ? "were" : "was");

	return pHead;
}

Person* Delete(Person* pHead)
{
	Person* pNewHead = pHead->pNext;

	pHead->pNext->pPrev = pHead->pPrev;
	pHead->pPrev->pNext = pHead->pNext;
	free(pHead);

	return pNewHead;
}

// Liste Sortieren
//*****************

Person* SortList(Person* pHead)
{
	int sortBy = 0;
	int direction = 0;

	printf("\nNach welchem Kriterium moechten Sie sortieren?\n\n");
	printf("Geschlecht        > 1\n");
	printf("Nachname          > 2\n");
	printf("Vorname           > 3\n");
	printf("Jahrgang          > 4\n");
	printf("\nIhre Auswahl      > ");
	scanf_s("%i", &sortBy);
	_fgetchar();

	printf("\nMoechten Sie auf- oder absteigend sortieren?\n\n");
	printf("Aufsteigend       > 1\n");
	printf("Absteigend        > 2\n");
	printf("\nIhre Auswahl      > ");
	scanf_s("%i", &direction);
	_fgetchar();


	switch (sortBy)
	{
	case 1:
		pHead = direction == 1 ? Sort(SortGenderAsc, pHead) : Sort(SortGenderDesc, pHead);
		break;
	case 2:
		pHead = direction == 1 ? Sort(SortLastNameAsc, pHead) : Sort(SortLastNameDesc, pHead);
		break;
	case 3:
		pHead = direction == 1 ? Sort(SortFirstNameAsc, pHead) : Sort(SortFirstNameDesc, pHead);
		break;
	case 4:
		pHead = direction == 1 ? Sort(SortVintageAsc, pHead) : Sort(SortVintageDesc, pHead);
		break;
	}

	return pHead;
}


Person* Sort(void(*f)(Person*&, Person*&, Person*&), Person* pHead)
{
	Person* pHead1 = pHead;
	Person* pHead2 = pHead;
	Person* pLast = pHead;

	do
	{
		pHead1 = pHead1->pNext;
		do
		{
			pHead2 = pHead2->pNext;

			(*f)(pHead1, pHead2, pLast);
		} 
		while (pHead2 != pLast);
	} 
	while (pHead1 != pLast);

	return pLast->pNext;
}

void SortGenderAsc(Person*& pHead1, Person*& pHead2, Person*& pLast)
{
	if (pHead1->Gender[0] < pHead2->Gender[0])
	{
		SwitchElements(pHead1, pHead2, pLast);
	}
}

void SortGenderDesc(Person*& pHead1, Person*& pHead2, Person*& pLast)
{
	if (pHead1->Gender[0] > pHead2->Gender[0])
	{
		SwitchElements(pHead1, pHead2, pLast);
	}
}

void SortLastNameAsc(Person*& pHead1, Person*& pHead2, Person*& pLast)
{
	if (pHead1->LastName[0] < pHead2->LastName[0])
	{
		SwitchElements(pHead1, pHead2, pLast);
	}
}

void SortLastNameDesc(Person*& pHead1, Person*& pHead2, Person*& pLast)
{
	if (pHead1->LastName[0] > pHead2->LastName[0])
	{
		SwitchElements(pHead1, pHead2, pLast);
	}
}

void SortFirstNameAsc(Person*& pHead1, Person*& pHead2, Person*& pLast)
{
	if (pHead1->FirstName[0] < pHead2->FirstName[0])
	{
		SwitchElements(pHead1, pHead2, pLast);
	}
}

void SortFirstNameDesc(Person*& pHead1, Person*& pHead2, Person*& pLast)
{
	if (pHead1->FirstName[0] > pHead2->FirstName[0])
	{
		SwitchElements(pHead1, pHead2, pLast);
	}
}

void SortVintageAsc(Person* &pHead1, Person* &pHead2, Person* &pLast)
{
	if (pHead1->Vintage < pHead2->Vintage)
	{
		SwitchElements(pHead1, pHead2, pLast);
	}
}

void SortVintageDesc(Person*& pHead1, Person*& pHead2, Person*& pLast)
{
	if (pHead1->Vintage > pHead2->Vintage)
	{
		SwitchElements(pHead1, pHead2, pLast);
	}
}

void SwitchElements(Person*& pHead1, Person*& pHead2, Person*& pLast)
{
	Person* pTmp1Prev = pHead1->pPrev;
	Person* pTmp1Next = pHead1->pNext;
	Person* pTmp2Prev = pHead2->pPrev;
	Person* pTmp2Next = pHead2->pNext;

	if (pHead1->pNext == pHead2)
	{
		pHead1->pNext = pTmp2Next;
		pHead1->pPrev = pHead2;

		pHead2->pNext = pHead1;
		pHead2->pPrev = pTmp1Prev;
	}
	else if (pHead2->pNext == pHead1)
	{
		pHead1->pNext = pHead2;
		pHead1->pPrev = pTmp2Prev;

		pHead2->pNext = pTmp1Next;
		pHead2->pPrev = pHead1;
	}
	else
	{
		pHead1->pNext = pTmp2Next;
		pHead1->pPrev = pTmp2Prev;

		pHead2->pNext = pTmp1Next;
		pHead2->pPrev = pTmp1Prev;
	}

	pHead1->pPrev->pNext = pHead1;
	pHead1->pNext->pPrev = pHead1;

	pHead2->pPrev->pNext = pHead2;
	pHead2->pNext->pPrev = pHead2;

	Person* pTmp = pHead1;
	pHead1 = pHead2;
	pHead2 = pTmp;

	if (pHead1 == pLast) pLast = pHead2;
	else if (pHead2 == pLast) pLast = pHead1;
}

// Liste Ausgeben
//****************

void DisplayList(Person* pHead)
{
	int numberOfElements;
	int counter = 0;

	printf("\nWie viele Elemente moechten Sie ausgeben?\n\n");
	printf("Anzahl Elemente   > ");
	scanf_s("%i", &numberOfElements);
	_fgetchar();

	pHead = pHead->pPrev;
	Person * pLast = pHead;

	printf("\n| Geschlecht  |  Nachname   |   Vorname   |  Jahrgang   |\n");
	printf("|-------------|-------------|-------------|-------------|\n");
	

	do
	{
		pHead = pHead->pNext;

		printf("|      %c      |      %c      |      %c      |    %i     |\n", pHead->Gender[0], pHead->LastName[0], pHead->FirstName[0], pHead->Vintage);

		counter++;

	} while (pHead != pLast || counter == numberOfElements);
}