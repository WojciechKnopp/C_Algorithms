#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct element{
    int wartosc;
    int wystapienia;
    struct element *ojciec;
    struct element *lewy;
    struct element *prawy;
}element, *wskelement;

typedef struct drzewo{
    wskelement korzen;
}drzewo;

wskelement utworz(int liczba){
    wskelement stworzony = (wskelement)malloc(sizeof(element));
    stworzony->wartosc  = liczba;
    stworzony->lewy=NULL;
    stworzony->prawy=NULL;
    stworzony->ojciec=NULL;
    stworzony->wystapienia=1;
    return stworzony;
}

void wstaw(drzewo *A, int wstawiany){
    bool czy_wstawiono = false;
    if(A->korzen==NULL){
        A->korzen = utworz(wstawiany);
        czy_wstawiono=true;
    }
    wskelement x = A->korzen;
    while(!czy_wstawiono){
        if(wstawiany > x->wartosc){
            if(x->prawy == NULL){
                wskelement nowy = utworz(wstawiany);
                x->prawy = nowy;
                nowy->ojciec = x;
                czy_wstawiono=true;
            }
            else
                x = x->prawy;
        }
        else if(wstawiany < x->wartosc){
            if(x->lewy == NULL){
                wskelement nowy = utworz(wstawiany);
                x->lewy = nowy;
                nowy->ojciec = x;
                czy_wstawiono=true;
            }
            else
                x = x->lewy;
        }
        else{
            x->wystapienia++;
            czy_wstawiono=true;
        }
    }
}

wskelement szukaj(drzewo *A, int szukany){
    bool czy_znaleziono = false;
    wskelement x = A->korzen;
    while(!czy_znaleziono && x != NULL){
        if(x->wartosc == szukany)
            czy_znaleziono = true;
        else{
            if(szukany > x->wartosc)
                x = x->prawy;
            else
                x = x->lewy;
        }
    }
    return x;
}

void usun_korzen(drzewo *A){
    wskelement x = A->korzen;
    if(x->wystapienia>1)
        x->wystapienia--;
    else{
        if(x->lewy==NULL && x->prawy==NULL){    //nie ma synów
            A->korzen=NULL;
            free(x);
        }
        else if(x->lewy!=NULL && x->prawy==NULL){   //ma lewego syna
            A->korzen=x->lewy;
            x->lewy->ojciec=NULL;
            free(x);
        }
        else if(x->lewy==NULL &&x->prawy!=NULL){    //ma prawego syna
            A->korzen=x->prawy;
            x->prawy->ojciec=NULL;
            free(x);
        }
        else{           //ma dwóch synów
            wskelement y = x->prawy;
            while(y->lewy!=NULL)
                y=y->lewy;
            if(y==x->prawy){
                x->prawy=y->prawy;
                y->prawy->ojciec=x;
            }
            else if(y->prawy!=NULL){
                y->prawy->ojciec=y->ojciec;
                y->ojciec->lewy=y->prawy;
            }
            else{
                y->ojciec->lewy=NULL;
            }

            x->lewy->ojciec=y;
            x->prawy->ojciec=y;
            A->korzen=y;
            y->ojciec=NULL;
            y->lewy=x->lewy;
            y->prawy=x->prawy;
            free(x);
        }
    }
}

void usun(drzewo *A, int usuwany){ //do zrobienia kiedy usuwamy korzen!!!
    wskelement x = szukaj(A, usuwany);
    if(x != NULL){
        if(x==A->korzen)
            usun_korzen(A);
        else{
            if(x->wystapienia>1)
                    x->wystapienia--;
            else{
                if(x->lewy==NULL && x->prawy==NULL){    //nie ma synów
                    if(x->ojciec->lewy==x)
                        x->ojciec->lewy=NULL;
                    else
                        x->ojciec->prawy=NULL;
                    free(x);
                }
                else if(x->lewy!=NULL && x->prawy==NULL){   //ma lewego syna
                    if(x->ojciec->lewy==x)
                        x->ojciec->lewy=x->lewy;
                    else
                        x->ojciec->prawy=x->lewy;
                    x->lewy->ojciec=x->ojciec;
                    free(x);
                }
                else if(x->lewy==NULL &&x->prawy!=NULL){    //ma prawego syna
                    if(x->ojciec->lewy==x)
                        x->ojciec->lewy=x->prawy;
                    else
                        x->ojciec->prawy=x->prawy;
                    x->prawy->ojciec=x->ojciec;
                    free(x);
                }
                else{           //ma dwóch synów
                    wskelement y = x->prawy;
                    while(y->lewy!=NULL)
                        y=y->lewy;
                    if(y==x->prawy){
                        x->prawy=y->prawy;
                        y->prawy->ojciec=x;
                    }
                    else if(y->prawy!=NULL){
                        y->prawy->ojciec=y->ojciec;
                        y->ojciec->lewy=y->prawy;
                    }
                    else{
                        y->ojciec->lewy=NULL;
                    }

                    if(x->ojciec->lewy==x)
                        x->ojciec->lewy=y;
                    else
                        x->ojciec->prawy=y;

                    x->lewy->ojciec=y;
                    x->prawy->ojciec=y;
                    y->ojciec=x->ojciec;
                    y->lewy=x->lewy;
                    y->prawy=x->prawy;
                    free(x);
                }
            }
        }
        printf("Usunięto element %d z drzewa.\n", usuwany);
    }
    else
        printf("Nie można usunąć elementu %d, ponieważ nie ma go w drzewie.\n", usuwany);
}

void drukuj(wskelement x){
    if(x != NULL){
        drukuj(x->lewy);
        if(x->ojciec != NULL)
            printf(" [%d]%d(%d) ", x->ojciec->wartosc, x->wartosc, x->wystapienia);
        else
            printf(" []%d(%d) ", x->wartosc, x->wystapienia);

        drukuj(x->prawy);
    }
}

int main(){
    drzewo A = {NULL};
    wskelement x;
    int wybor=0;
    int wartosc;
    while(wybor!=5){
        printf("Co chcesz zrobić?\n1. Wstaw\n2. Szukaj\n3. Usuń\n4. Drukuj\n5. Zakończ\n");
        scanf("%d", &wybor);
        switch (wybor){
        case 1:
            printf("Jaki element chcesz stawić?\n");
            scanf("%d", &wartosc);
            wstaw(&A, wartosc);
            break;

        case 2:
            printf("Jakią wartość chcesz wyszukać w drzewie?\n");
            scanf("%d", &wartosc);
            x=szukaj(&A, wartosc);
            if(x!=NULL){
                printf("Znaleziono element %d w drzewie\n", wartosc);
                printf("Ilość powtórzeń elementu: %d\n", x->wystapienia);
                if(x->ojciec != NULL)
                    printf("Ojciec: %d\n", x->ojciec->wartosc);
                else
                    printf("Element jest korzeniem drzewa\n");
                if(x->lewy != NULL)
                    printf("Lewy syn: %d\n", x->lewy->wartosc);
                else
                    printf("Brak lewego syna\n");
                if(x->prawy != NULL)
                    printf("Prawy syn: %d\n", x->prawy->wartosc);
                else
                    printf("Brak prawego syna\n");
            }
            else
                printf("Nie znaleziono elementu %d w drzewie\n", wartosc);
            break;

        case 3:
            printf("Podaj element do usunięcia\n");
            scanf("%d", &wartosc);
            usun(&A, wartosc);
            break;

        case 4:
            printf("Schemat wyświetlania: [ojciec]wartość(ilość wystąpień)\n");
            drukuj(A.korzen);
            break;

        case 5:
            printf("Kończenie.\n");
            break;
        default:
            printf("Nie ma takiego polecenia.\n");
        }
        printf("\n");
    }

    return 0;
}