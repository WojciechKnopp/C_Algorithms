#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct nazwiska{
    int liczba;
    char napis[23];
}nazwiska, *wsknazwiska;

void wyczysc(wsknazwiska *T, int size){
    for(int i=0; i<size;i++)
        T[i]= NULL;
}

void pokaz(wsknazwiska *T, int size){
    printf("INDEKS LICZBA NAZWISKO\n");
    for(int i=0; i<size; i++)
    if(T[i] != NULL)
        printf("%d %d %s\n", i, T[i]->liczba, T[i]->napis);
    else
        printf("%d NULL NULL\n", i);
}

void wstaw(wsknazwiska *T, wsknazwiska wstawiane, int klucz, int m, wsknazwiska del){
    bool czy_wstawiono = false;
    for(int i=0; !czy_wstawiono && i<m; i++){
        int pozycja = ((klucz%m)+i*(1+(klucz%(m-2))))%m;
        if(T[pozycja] == del || T[pozycja] == NULL){
            T[pozycja] = wstawiane;
            czy_wstawiono = true;
        }
    }
    if(czy_wstawiono == false)
        printf("Nie udalo się wstawić elementu %s\n", wstawiane->napis);
}

int szukaj(wsknazwiska *T, wsknazwiska szukane, int klucz, int m){
    for(int i=0; i<m; i++){
        int pozycja = ((klucz%m)+i*(1+(klucz%(m-2))))%m;
        if(T[pozycja] == NULL)
            break;
        else{
            if(strcmp(T[pozycja]->napis, szukane->napis)==0 && T[pozycja]->liczba == szukane->liczba){
                return pozycja;
            }
        }
    }
    return -1; //nie znaleziono
}

void usun(wsknazwiska *T, wsknazwiska usuwane, int klucz, int m, wsknazwiska del){
    int indeks = szukaj(T, usuwane, klucz, m);
    if(indeks != -1){
        T[indeks] = del;
    }else
        printf("Nie znaleziono elementu %s do usuniecia\n", usuwane->napis);
}

int main(){

    // POBIERANIE DANYCH //
    FILE *plik;
    plik = fopen("nazwiskaASCII.txt","r");
    if(plik == NULL){
        printf("Błąd pliku!\n");
        return 0;
    }

    nazwiska del = {0, "DEL"}; //znacznik usunietego elementu
    wsknazwiska dane[20000];
    for(int i=0; i<20000; i++){
        dane[i] = (wsknazwiska) malloc(sizeof(nazwiska));
        fscanf(plik,"%d",&(dane[i]->liczba));
        fscanf(plik,"%s",dane[i]->napis);
    }

    int zmienione_klucze[20000];
    for(int i=0; i<20000; i++){
        int tmp=123*dane[i]->napis[0]+dane[i]->napis[1];
        for(int j=2; j<strlen(dane[i]->napis); j++){
            tmp=tmp*123+dane[i]->napis[j];
        }
        zmienione_klucze[i]=tmp;
        if(zmienione_klucze[i]<0)
            zmienione_klucze[i]=abs(zmienione_klucze[i]);
    }

    // HASZOWANIE TESTOWE [U + OD] //
    wsknazwiska T1[50];
    wyczysc(T1,50);
    for(int i=0; i<40; i++)
        wstaw(T1, dane[i], zmienione_klucze[i], 50, &del);
    for(int i=0; i<40; i+=2)
        usun(T1, dane[i], zmienione_klucze[i], 50, &del);
    for(int i=40; i<60; i++)
        wstaw(T1, dane[i], zmienione_klucze[i], 50, &del);
    
    pokaz(T1, 50);
    
    // HASZOWANIE PEŁNE [U + OD] //
    wsknazwiska T2[5000];
    wyczysc(T2, 5000);
    for(int i=0; i<4000; i++)
        wstaw(T2,dane[i],zmienione_klucze[i],5000,&del);
    for(int i=0; i<4000; i+=2)
        usun(T2,dane[i],zmienione_klucze[i],5000,&del);
    for(int i=4000; i<6000; i++){
        wstaw(T2,dane[i],zmienione_klucze[i],5000,&del);
    }
    int count = 0;
    for(int i=0; i<5000; i++)
        if(T2[i] == &del)
            count++;
    printf("\nIlość pozycji ze znacznikiem DEL: %d\n", count);
    return 0;
}