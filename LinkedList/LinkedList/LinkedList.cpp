#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "string.h"

#pragma warning(disable:6011)

typedef struct Person {
	char Gender[3];
	char LastName[50];
	char FirstName[50];
	int Vintage;
	struct Person* pNext;
	struct Person* pPrev;
} struPerson;

Person* CreateList(Person*, int&);
Person* DeleteList(Person*, int&);
Person* DeleteSpecificElement(Person*, int&);
Person* Delete(Person*, char[], char[], char[], int, int&);
Person* Delete(Person*);
Person* SortList(Person*);
Person* Sort(void (*f)(Person*&, Person*&, Person*&), Person*);
int GetRandomVintage();
int GetUsersChoice();
char GetRandomGender();
char GetRandomCharacter();
void DisplayList(Person*);
void ShowMenu(int);
void SortGenderAsc(Person*&, Person*&, Person*&);
void SortGenderDesc(Person*&, Person*&, Person*&);
void SortLastNameAsc(Person*&, Person*&, Person*&);
void SortLastNameDesc(Person*&, Person*&, Person*&);
void SortFirstNameAsc(Person*&, Person*&, Person*&);
void SortFirstNameDesc(Person*&, Person*&, Person*&);
void SortVintageAsc(Person*&, Person*&, Person*&);
void SortVintageDesc(Person*&, Person*&, Person*&);
void SwitchElements(Person*&, Person*&, Person*&);


// Autor:    David Zweili
// Funktion: Menu anzeigen, Benutzereingabe einlesen und reagieren
int main()
{
	srand((unsigned)time(NULL));
	Person* pHead = NULL;
	int numberOfElements = 0;

	int repeat = 1;

	while (repeat == 1)
	{
		ShowMenu(numberOfElements);

		switch (GetUsersChoice())
		{
		case 1:
			// Liste erstellen
			pHead = CreateList(pHead, numberOfElements);
			break;
		case 2:
			// Liste loeschen
			pHead = DeleteList(pHead, numberOfElements);
			break;
		case 3:
			// Spezifisches Element loeschen
			pHead = DeleteSpecificElement(pHead, numberOfElements);
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
			// ungueltige Eingabe
			printf("\n  ----ungueltige Eingabe---- \n");
			break;
		}
	}

	printf("\n  --------------------------\n");
	printf("       Programm beendet\n");
	printf("  --------------------------\n\n");
	system("Pause");
}

// Autor:    David Zweili
// Funktion: Menukopf anzeigen
void ShowMenu(int numberOfElements)
{
	printf("  __  __                     \n");
	printf(" |  \\/  |  ___  _ __   _   _ \n");
	printf(" | |\\/| | / _ \\| '_ \\ | | | |\n");
	printf(" | |  | ||  __/| | | || |_| |\n");
	printf(" |_|  |_| \\___||_| |_| \\__,_|\n\n");
	printf("  %i Elemente in der Liste\n\n", numberOfElements);
	printf("  Neue Liste erstellen   > 1\n");
	printf("  Liste loeschen         > 2\n");
	printf("  Elemente loeschen      > 3\n");
	printf("  Liste sortieren        > 4\n");
	printf("  Liste ausgeben         > 5\n");
	printf("  Programm beenden       > 6\n");
}

// Autor:    David Zweili
// Funktion: Eingabe des Benutzers auslesen
int GetUsersChoice()
{
	int command = 0;

	// Eingabe auslesen
	printf("\n  Ihre Auswahl           > ");
	scanf_s("%i", &command);
	_fgetchar();

	// Eingabe pruefen
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

// Autor:    David Zweili
// Funktion: Liste generieren
Person* CreateList(Person* pHead, int &numberOfElements)
{
	// Alte Liste loeschen falls eine existiert
	if(numberOfElements > 0) pHead = DeleteList(pHead, numberOfElements);

	struPerson* pFirst = pHead;
	struPerson* pStart = NULL;
	struPerson* pEnd = NULL;

	printf("\n\n  ------ Liste erstellen ------\n");

	// Anzahl zu erstellende Elemente per Benutzereingabe auslesen und Eingabe ueberpruefen
	while (numberOfElements <= 0)
	{
		printf("\n  Anzahl Personen          > ");
		scanf_s("%i", &numberOfElements);
		_fgetchar();

		if(numberOfElements <= 0) printf("\n  ----ungueltige Eingabe---- \n");
	}

	// Elemente erzeugen und mit Daten abfüllen
	for (int i = 0; i < numberOfElements; i++) {
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
			// Das erste Element zwischenspeichern, um es am Schluss mit dem letzten Element wieder zu verlinken.
			pFirst = pElement;
		}
		else if (i + 1 != numberOfElements)
		{
			// Generiertes Element in die Liste verlinken
			pElement->pPrev = pStart;
			pStart->pNext = pElement;
		}
		else
		{
			// letztes Element mit dem ersten verlinken
			pElement->pPrev = pStart;
			pStart->pNext = pElement;
			pElement->pNext = pFirst;
			pFirst->pPrev = pElement;
		}
		pStart = pElement;
	}

	if (numberOfElements == 1)
	{
		// Wenn nur ein Element generiert wird, dieses mit sich selber verlinken
		pFirst->pNext = pFirst;
		pFirst->pPrev = pFirst;
	}

	printf("\n  %i Personen wurden generiert", numberOfElements);
	printf("\n  -----------------------------\n\n");

	return pFirst;
}

// Autor:    David Zweili
// Funktion: Gibt zufaelliges Geschlecht zurueck
char GetRandomGender()
{
	return "MF"[rand() % 2];
}

// Autor:    David Zweili
// Funktion: Gibt zufaelligen Grossbuchstabe zurueck
char GetRandomCharacter()
{
	return 'A' + (rand() % 26);
}

// Autor:    David Zweili
// Funktion: Gibt zufaelligen Jahrgang zurueck
int GetRandomVintage()
{
	return 1900 + (rand() % 120);
}

// Liste loeschen
//****************

// Autor:    David Zweili
// Funktion: Gesamte Liste loeschen
Person* DeleteList(Person* pHead, int &numberOfElements)
{
	printf("\n\n  ----- Liste loeschen -----\n\n");

	// Ueberpruefen ob die Liste Elemente beinhaltet.
	if (pHead == NULL)
	{
		printf("    Liste ist bereits leer\n");
		printf("  --------------------------\n\n");
		return NULL;
	}

	int deleteCounter = 0;
	Person* pLast = pHead->pPrev;
	Person* pTmp = pHead;

	// Speicher von jedem Element in der Liste freigeben
	while (pTmp != NULL)
	{
		Person* pDelete = pTmp;
		pTmp = pTmp != pLast ? pTmp->pNext : NULL;
		free(pDelete);
		deleteCounter++;
	}
	printf("  %i Elemente geloescht\n", deleteCounter);
	printf("  --------------------------\n\n");

	numberOfElements = 0;

	return NULL;
}

// Spezifisches Element loeschen
//*******************************

// Autor:    David Zweili
// Funktion: Elemente aufgrund Eingrenzung des Benutzers loeschen
Person* DeleteSpecificElement(Person* pHead, int &numberOfElements)
{
	char gender[3] {'x','x','x'};
	char lastName[50];
	char firstName[50];
	int vintage = 0;

	printf("\n\n  ---- Elemente loeschen ---\n\n");

	// Geschlecht aus Benutzereingabe auslesen und ueberpruefen
	while (gender[0] != 'M' && gender[0] != 'F')
	{
		printf("  Geschlecht [M/F]       > ");
		fgets(gender, sizeof(gender), stdin);
		if (gender[0] != 'M' && gender[0] != 'F') printf("\n  ----ungueltige Eingabe---- \n\n");
	}

	// Nachname und Vorname aus Benutzereingabe auslesen
	printf("  Nachname               > ");
	fgets(lastName, sizeof(lastName), stdin);

	printf("  Vorname                > ");
	fgets(firstName, sizeof(firstName), stdin);

	// Jahrgang aus Benutzereingabe auslesen und ueberpruefen
	while (vintage < 1900 || vintage > 2020)
	{
		printf("  Jahrgang [1990 - 2020] > ");
		scanf_s("%i", &vintage);
		_fgetchar();
		if (vintage < 1900 || vintage > 2020) printf("\n  ----ungueltige Eingabe---- \n\n");
	}

	// Elemente loeschen und HEAD zurueckgeben
	char* token = NULL;
	return Delete(pHead, strtok_s(gender, "\n", &token), strtok_s(lastName, "\n", &token), strtok_s(firstName, "\n", &token), vintage, numberOfElements);
}

// Autor:    David Zweili
// Funktion: Elemente mit zutreffenden Parametern loeschen
Person* Delete(Person* pHead, char gender[], char lastName[], char firstName[], int vintage, int &numberOfElements)
{
	int deleteCounter = 0;
	int loop = 1;
	Person* pLast = pHead->pPrev;

	// Alle Elemente aus Liste mit den Parametern vergleichen und bei Ueberenstimmung loeschen
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

	printf("\n  %i Elemente geloescht", deleteCounter);
	printf("\n  --------------------------\n\n");

	numberOfElements = numberOfElements - deleteCounter;

	return pHead;
}

// Autor:    David Zweili
// Funktion: Person loeschen und neuen HEAD zurueckgeben
Person* Delete(Person* pHead)
{
	Person* pNewHead = pHead->pNext;

	// Element vor und Element nach dem zu loeschenden Element miteinander verlinken
	pHead->pNext->pPrev = pHead->pPrev;
	pHead->pPrev->pNext = pHead->pNext;

	// Speicherplatz von zu loeschendem Element freigeben
	free(pHead);

	return pNewHead;
}

// Liste Sortieren
//*****************

// Autor:    David Zweili
// Funktion: 
Person* SortList(Person* pHead)
{
	int sortBy = 0;
	int direction = 0;

	printf("\n\n  ---- Liste sortieren -----\n\n");

	// Ueberpruefen ob die Liste Elemente enthaelt
	if (pHead == NULL)
	{
		printf("   Keine Elemente in Liste\n");
		printf("  --------------------------\n\n");
		return NULL;
	}

	printf("  Geschlecht             > 1\n");
	printf("  Nachname               > 2\n");
	printf("  Vorname                > 3\n");
	printf("  Jahrgang               > 4\n\n");

	// Sortierparameter aus Benutzereingabe auslesen und ueberpruefen
	while (sortBy < 1 || sortBy > 4)
	{
		printf("  Sortieren nach         > ");
		scanf_s("%i", &sortBy);
		_fgetchar();
		if (sortBy < 1 || sortBy > 4) printf("\n  ----ungueltige Eingabe---- \n\n");
	}

	printf("\n  --------------------------\n\n");
	printf("  Aufsteigend            > 1\n");
	printf("  Absteigend             > 2\n\n");

	// Sortierrichtung aus Benutzereingabe auslesen und ueberpruefen
	while (direction < 1 || direction > 2)
	{
		printf("  Ihre Auswahl           > ");
		scanf_s("%i", &direction);
		_fgetchar();
		if (direction < 1 || direction > 2) printf("\n  ----ungueltige Eingabe---- \n\n");
	}

	printf("\n  Sortierung laeuft...\n");

	// ausgewaehlter Sortieralgorithmus anstossen
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

// Autor:    David Zweili
// Funktion: Sortierung der Liste durchfuehren
Person* Sort(void(*f)(Person*&, Person*&, Person*&), Person* pHead)
{
	Person* pHead1 = pHead;
	Person* pHead2 = pHead;
	Person* pLast = pHead;

	// Startzeit merken
	clock_t startTime = clock();

	// Bubblesort (Alle Elemente kubisch miteinander vergleichen)
	do
	{
		pHead1 = pHead1->pNext;
		do
		{
			pHead2 = pHead2->pNext;

			// Funktion aufrufen um Elemente zu vergleichen
			(*f)(pHead1, pHead2, pLast);
		} 
		while (pHead2 != pLast);
	} 
	while (pHead1 != pLast);

	// Endzeit mit Startzeit vergleichen um Dauer der Sortierung auszugeben
	clock_t endTime = clock();
	double timeSpent = ((double)endTime - (double)startTime) / CLOCKS_PER_SEC;
	printf("\n  ----- Liste sortiert -----\n");
	printf("\n  Dauer %.2f Sekunden", timeSpent);
	printf("\n  --------------------------\n\n");

	return pLast->pNext;
}

// Autor:    David Zweili
// Funktion: Sortieren nach Geschlaecht aufsteigend
void SortGenderAsc(Person*& pHead1, Person*& pHead2, Person*& pLast)
{
	if (pHead1->Gender[0] < pHead2->Gender[0])
	{
		SwitchElements(pHead1, pHead2, pLast);
	}
}

// Autor:    David Zweili
// Funktion: Sortieren nach Geschlaecht absteigend
void SortGenderDesc(Person*& pHead1, Person*& pHead2, Person*& pLast)
{
	if (pHead1->Gender[0] > pHead2->Gender[0])
	{
		SwitchElements(pHead1, pHead2, pLast);
	}
}

// Autor:    David Zweili
// Funktion: Sortieren nach Nachname aufsteigend
void SortLastNameAsc(Person*& pHead1, Person*& pHead2, Person*& pLast)
{
	if (pHead1->LastName[0] < pHead2->LastName[0])
	{
		SwitchElements(pHead1, pHead2, pLast);
	}
}

// Autor:    David Zweili
// Funktion: Sortieren nach Nachname absteigend
void SortLastNameDesc(Person*& pHead1, Person*& pHead2, Person*& pLast)
{
	if (pHead1->LastName[0] > pHead2->LastName[0])
	{
		SwitchElements(pHead1, pHead2, pLast);
	}
}

// Autor:    David Zweili
// Funktion: Sortieren nach Vorname aufsteigend
void SortFirstNameAsc(Person*& pHead1, Person*& pHead2, Person*& pLast)
{
	if (pHead1->FirstName[0] < pHead2->FirstName[0])
	{
		SwitchElements(pHead1, pHead2, pLast);
	}
}

// Autor:    David Zweili
// Funktion: Sortieren nach Vorname absteigend
void SortFirstNameDesc(Person*& pHead1, Person*& pHead2, Person*& pLast)
{
	if (pHead1->FirstName[0] > pHead2->FirstName[0])
	{
		SwitchElements(pHead1, pHead2, pLast);
	}
}

// Autor:    David Zweili
// Funktion: Sortieren nach Jahrgang aufsteigend
void SortVintageAsc(Person* &pHead1, Person* &pHead2, Person* &pLast)
{
	if (pHead1->Vintage < pHead2->Vintage)
	{
		SwitchElements(pHead1, pHead2, pLast);
	}
}

// Autor:    David Zweili
// Funktion: Sortieren nach Jahrgang absteigend
void SortVintageDesc(Person*& pHead1, Person*& pHead2, Person*& pLast)
{
	if (pHead1->Vintage > pHead2->Vintage)
	{
		SwitchElements(pHead1, pHead2, pLast);
	}
}

// Autor:    David Zweili
// Funktion: Position zweier Elemente in Liste tauschen
void SwitchElements(Person*& pHead1, Person*& pHead2, Person*& pLast)
{
	Person* pTmp1Prev = pHead1->pPrev;
	Person* pTmp1Next = pHead1->pNext;
	Person* pTmp2Prev = pHead2->pPrev;
	Person* pTmp2Next = pHead2->pNext;

	if (pHead1->pNext == pHead2)
	{
		// zu tauschende Elemente befinden sich nacheinander
		pHead1->pNext = pTmp2Next;
		pHead1->pPrev = pHead2;

		pHead2->pNext = pHead1;
		pHead2->pPrev = pTmp1Prev;
	}
	else if (pHead2->pNext == pHead1)
	{
		// Pointerverlinkung wenn zu tauschende Elemente sich nacheinander befinden
		pHead1->pNext = pHead2;
		pHead1->pPrev = pTmp2Prev;

		pHead2->pNext = pTmp1Next;
		pHead2->pPrev = pHead1;
	}
	else
	{
		// Pointerverlinkung wenn zu tauschende Elemente mindestens ein Element dazwischen haben
		pHead1->pNext = pTmp2Next;
		pHead1->pPrev = pTmp2Prev;

		pHead2->pNext = pTmp1Next;
		pHead2->pPrev = pTmp1Prev;
	}

	// Pointer der Anliegenden Elemente anpassen
	pHead1->pPrev->pNext = pHead1;
	pHead1->pNext->pPrev = pHead1;

	pHead2->pPrev->pNext = pHead2;
	pHead2->pNext->pPrev = pHead2;

	// pHead1 und pHead2 tauschen, um die Bubbesort Vergleichreihenfolge nicht zu veraendern
	Person* pTmp = pHead1;
	pHead1 = pHead2;
	pHead2 = pTmp;

	// pLast ebenfalls tauschen, damit der Bubblesort weiss wann er das letzte zu vergleichende Element erreicht hat
	if (pHead1 == pLast) pLast = pHead2;
	else if (pHead2 == pLast) pLast = pHead1;
}

// Liste Ausgeben
//****************

// Autor:    David Zweili
// Funktion: gesamte Liste anzeigen
void DisplayList(Person* pHead)
{
	int numberOfElements = -1;
	int counter = 0;

	printf("\n\n  -------- Liste ausgeben --------\n\n");

	// ueberpruefen ob Liste Elemente enthaelt.
	if (pHead == NULL)
	{
		printf("      Keine Elemente in Liste\n");
		printf("  --------------------------------\n\n");
		return;
	}

	// Anzahl auszugebende Elemente aus Benutzereingabe auslesen und ueberpruefen
	while (numberOfElements < 0)
	{
		printf("  Anzahl Elemente [0 = alle] > ");
		scanf_s("%i", &numberOfElements);
		_fgetchar();
		if (numberOfElements < 0) printf("\n  -------ungueltige Eingabe------- \n\n");
	}

	printf("  --------------------------------\n\n");
	printf("\n  | Geschlecht  |  Nachname   |   Vorname   |  Jahrgang   |\n");
	printf("  |-------------|-------------|-------------|-------------|\n");

	// alle Elemente ausgeben
	pHead = pHead->pPrev;
	Person* pLast = pHead;
	do
	{
		pHead = pHead->pNext;

		printf("  |      %c      |      %c      |      %c      |    %i     |\n", pHead->Gender[0], pHead->LastName[0], pHead->FirstName[0], pHead->Vintage);

		counter++;

	} while (pHead != pLast && counter != numberOfElements);

	printf("\n\n  --------------------------\n");
	printf("  %i Elemente ausgegeben\n", counter);
	printf("  --------------------------\n\n");
}