#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct lista{
    char napis[20];
    struct lista *nast, *pop;
}lista, *wsklista;

wsklista nowywezel(char n[20]){
    
    wsklista nowy = (wsklista) malloc(sizeof(lista));
    strcpy(nowy->napis, n);
    nowy->nast=NULL;
    nowy->pop=NULL;
    return nowy;
}

wsklista wartownik(){
    wsklista n = nowywezel("");
    n->nast = n;
    n->pop = n;
    return n;
}

void drukuj(wsklista L){
    L=L->nast;
    while(strcmp(L->napis,"")!=0){ //przez całą liste dopóki nie wróci do wartownika
        printf("%s ", L->napis);
        L=L->nast;
    }
    printf("\n");
}

void wstaw(wsklista L, char slowo[20]){
    wsklista nowy = nowywezel(slowo);
    nowy->pop = L;
    nowy->nast = L->nast;
    L->nast->pop=nowy;
    L->nast=nowy;
}

wsklista szukaj(wsklista L, char szukane[20]){
    L=L->nast;
    while(strcmp(L->napis,"")!=0){
        if(strcmp(L->napis,szukane)==0){
            return L;
        }
        L=L->nast;
    }
    return NULL;
}

void usun(wsklista L, char slowo[20]){
    wsklista usuwane = szukaj(L,slowo);
    if(usuwane != NULL){
        usuwane->pop->nast=usuwane->nast;
        usuwane->nast->pop=usuwane->pop;
        free(usuwane);
        printf("Usunięto %s z listy.\n", slowo);
    }
    else
        printf("Nie znaleziono %s w liście.\n", slowo);
}

void kasuj(wsklista L){
    L=L->nast;
    while(strcmp(L->napis, "")!=0){
        L=L->nast;
        free(L->pop);
    }
    L->nast=L;
    L->pop=L;
}

wsklista bezpowtorzen(wsklista L){
    wsklista nowy = wartownik();
    L=L->pop;
    while(strcmp(L->napis, "")!=0){
        if(szukaj(nowy, L->napis)==NULL){
            wstaw(nowy,L->napis);
        }
        L=L->pop;
    }
    return nowy;
}

wsklista scal(wsklista L1, wsklista L2){
    L1->pop->nast=L2->nast; //następny dla konca 1 listy jest 1 elem w L2
    L2->nast->pop=L1->pop; //poprzedni dla pierwszego elementu L2 jest ostatni z L1
    L1->pop=L2->pop; //poperzdni dla wartownika z L1 jest ostatni elem z L2
    L2->pop->nast=L1; //następny dla ostatniego elem z L2 jest wartownik z L1
    free(L2); //zwolnienie pamięci z nieużywanego wartownika w L2
    return L1;
}

int main(){
    wsklista L1 = wartownik();
    wsklista Lkopia, L2;
    char slowo[20];
    int choice = 0;
    while(choice != 8){
        printf("Co chcesz zrobić:\n1. wstaw\n2. drukuj\n3. szukaj\n4. usuń\n5. kasuj (całą listę)\n6. kopia bez powtórzeń słów\n7. scal 2 listy\n8. zakończ\n");
        scanf("%d", &choice);
        switch(choice){
            case 1:
                printf("\nJakie słowo chcesz wstawić na początek listy?\n");
                scanf("%s",slowo);
                wstaw(L1, slowo);
                printf("Wstawiono %s do listy\n", slowo);
                break;
            case 2:
                printf("\nLista:\n");
                drukuj(L1);
                break;
            case 3:
                printf("\nJakiego słowa szukasz?\n");
                scanf("%s", slowo);
                wsklista szukane = szukaj(L1,slowo);
                if(szukane != NULL)
                    printf("Znaleziono szukane słowo. Wskaźnik na element listy to %p\n", szukane);
                else
                    printf("Nie znaleziono szukanego słowa\n");
                break;
            case 4:
                printf("\nJakie słowo chcesz usunąć?\n");
                scanf("%s", slowo);
                usun(L1, slowo);
                break;
            case 5:
                kasuj(L1);
                printf("\nSkasowano listę.\n");
                break;
            case 6:
                Lkopia = bezpowtorzen(L1);
                printf("\nUtworzono kopie listy pomijając powtórzenia słów.\n");
                printf("Lista oryginalna:\n");
                drukuj(L1);
                printf("Lista utworzona:\n");
                drukuj(Lkopia);
                break;
            case 7:
                L2 = wartownik();
                printf("\nStwórz liste, z którą chcesz scalić pierwotną listę.\n");
                strcpy(slowo,"");
                while(strcmp(slowo,"koniec")!=0){
                    printf("Podaj słowo które chcesz dodać do listy (podanie 'koniec' kończy dopisywanie): ");
                    scanf("%s", slowo);
                    if(strcmp(slowo,"koniec")!=0)
                        wstaw(L2, slowo);
                }
                printf("Pierwotna lista:\n");
                drukuj(L1);
                printf("Utworzona lista:\n");
                drukuj(L2);
                L1 = scal(L1,L2);
                printf("Scalona lista:\n");
                drukuj(L1);
                break;
            case 8:
                printf("Wychodzenie z programu.\n");
                break;
            default:
                printf("Nie ma takiej opcji.\n");
                choice = 0;
        }
        printf("\n");
    }
    return 0;
}
