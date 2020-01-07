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

void ShowMenu();
int GetUsersChoice();

Person* CreateList();
char GetRandomGender();
char GetRandomCharacter();
int GetRandomVintage();

void DeleteList(Person*);

Person* DeleteSpecificElement(Person*);
Person* Delete(Person*, char[], char[], char[], int);
Person* Delete(Person* pHead);

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
			DeleteList(pHead);
			break;
		case 3:
			// Spezifisches Element loeschen
			pHead = DeleteSpecificElement(pHead);
			break;
		case 4:
			// Liste sortieren
			break;
		case 5:
			// Liste ausgeben
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

	//// Liste ausgeben
	Person* pLast = pStart->pPrev;
	for (struPerson* pHead = pStart; pHead != pLast; pHead = pHead->pNext)
	{
		printf("Gender = %c\n", pHead->Gender[0]);
		printf("LastName = %c\n", pHead->LastName[0]);
		printf("FirstName = %c\n", pHead->FirstName[0]);
		printf("Vintage = %i\n", pHead->Vintage);
	}
	printf("Gender = %c\n", pLast->Gender[0]);
	printf("LastName = %c\n", pLast->LastName[0]);
	printf("FirstName = %c\n", pLast->FirstName[0]);
	printf("Vintage = %i\n", pLast->Vintage);


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

void DeleteList(Person* pHead)
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