#include "stdio.h"
#include "stdlib.h"

#pragma warning(disable:6011)

typedef struct Element {
	int Nummer;
	struct Element* pNext;
} struElement;

void ShowMenu();

int main()
{
	ShowMenu();


	int Anzahl = 10;
	struElement* pStart = NULL;

	// Elemente erzeugen, mit Daten abfüllen
	for (int i = 0; i < Anzahl; i++) {
		struElement* pElement = (struElement*)malloc(sizeof(struElement));
		pElement->Nummer = Anzahl - i;
		pElement->pNext = NULL;
		if (i != 0) pElement->pNext = pStart;
		pStart = pElement;
	}
	// Liste ausgeben
	for (struElement* pElm = pStart; pElm != NULL; pElm = pElm->pNext) {
		printf("Nummer = %i\n", pElm->Nummer);
	}
	// Auf Tastendruck warten
	system("Pause");
};

void ShowMenu()
{
	printf("MENU");
}