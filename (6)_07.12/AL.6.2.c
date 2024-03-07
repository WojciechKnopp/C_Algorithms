#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void zeruj(int *tab, int size){
    for(int i=0; i<size; i++)
        tab[i]=0;
}

int policz_zerowe(int *tab, int size){
    int wynik=0;
    for(int i=0; i<size; i++)
        if(tab[i]==0)
            wynik++;
    return wynik;
}

int max_wartosc(int *tab, int size){
    int max=tab[0];
    for(int i=1; i<size; i++)
        if(tab[i]>max)
            max=tab[i];
    return max;
}

float srednia(int *tab, int size){
    int count = 0;
    int sum = 0;
    for(int i=0; i<size; i++)
        if(tab[i]!=0){
            count++;
            sum+=tab[i];
        }
    return sum*1.0/count;
}

void pokaz(char tab[3744][100], int size){
    for(int i=0; i<size; i++)
        printf("%s\n",tab[i]);
}
void pokaz2(int tab[3744]){
    for(int i=0; i<3744; i++)
        printf("%d\n",tab[i]);
}

int main(){
    //POBIERANIE NAPISÓW//
    char napisy[3744][100];
    FILE *dane;
    dane = fopen("napisy.txt", "r");
    for(int i=0; i<3744; i++)
        fscanf(dane, "%s", napisy[i]);

    //ZAMIANA NAPISÓW NA LICZBY//
    int liczby[3744];
    for(int i=0; i<3744; i++){
        int tmp=123*napisy[i][0]+napisy[i][1];
        for(int j=2; j<strlen(napisy[i]); j++){
            tmp=tmp*123+napisy[i][j];
        }
        liczby[i]=tmp;
        if(liczby[i]<0)
            liczby[i]=abs(liczby[i]);
    }

    //DANE MAŁE KORZYSTNE//
    int T1[251];
    zeruj(T1, 251);
    for(int i=0; i<2*251; i++){
        int tmp = liczby[i]%251;
        printf("%d ",tmp);
        T1[tmp]++;
    }
    printf("\nDANE MAŁE KORZYSTNE:\n");
    printf("Ilość miejsc zerowych: %i\n", policz_zerowe(T1,251));
    printf("Maksymalna wartość w tablicy: %i\n",max_wartosc(T1,251));
    printf("Średnia wartość pozycji niezerowych: %f\n\n",srednia(T1,251));
    
    //DANE MAŁE NIEKORZYSTNE//
    int T2[256];
    zeruj(T2, 256);
    for(int i=0; i<2*256; i++){
        int tmp = liczby[i]%256;
        printf("%d ",tmp);
        T2[tmp]++;
    }
    printf("\nDANE MAŁE NIEKORZYSTNE:\n");
    printf("Ilość miejsc zerowych: %i\n", policz_zerowe(T2,256));
    printf("Maksymalna wartość w tablicy: %i\n",max_wartosc(T2,256));
    printf("Średnia wartość pozycji niezerowych: %f\n\n",srednia(T2,256));

    //DANE DUŻE KORZYSTNE//
    int T3[1021];
    zeruj(T3, 1021);
    for(int i=0; i<2*1021; i++){
        int tmp = liczby[i]%1021;
        printf("%d ",tmp);
        T3[tmp]++;
    }
    printf("\nDANE DUŻE KORZYSTNE:\n");
    printf("Ilość miejsc zerowych: %i\n", policz_zerowe(T3,1021));
    printf("Maksymalna wartość w tablicy: %i\n",max_wartosc(T3,1021));
    printf("Średnia wartość pozycji niezerowych: %f\n\n",srednia(T3,1021));

    //DANE DUŻE NIEKORZYSTNE//
    int T4[1024];
    zeruj(T4, 1024);
    for(int i=0; i<2*1024; i++){
        int tmp = liczby[i]%1024;
        printf("%d ",tmp);
        T4[tmp]++;
    }
    printf("\nDANE DUŻE NIEKORZYSTNE:\n");
    printf("Ilość miejsc zerowych: %i\n", policz_zerowe(T4,1024));
    printf("Maksymalna wartość w tablicy: %i\n",max_wartosc(T4,1024));
    printf("Średnia wartość pozycji niezerowych: %f\n\n",srednia(T4,1024));

    return 0;
}