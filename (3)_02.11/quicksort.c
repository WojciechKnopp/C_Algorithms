#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define MLD 1000000000.0
#define C 4
#define ROZMIAR 100

void wypelnij_tablice_losowo(int* A, int* B){
    srand(time(NULL));
    for(int i = 1; i <= ROZMIAR; i++){
        A[i] = rand()%100;
        B[i] = A[i];
    }
}

void wypelnij_tablice_malejaco(int* A, int* B){
    for(int i = 1; i <= ROZMIAR; i++){
        A[i] = ROZMIAR - i;
        B[i] = A[i];
    }
}

void pokaz_tablice(int* A, int n){
    printf("[");
    for(int i = 1; i <= n; i++)
        printf(" %i ", A[i]);
    printf("]\n");
}

void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubblesort(int* A, int p, int r){
    for(int i = r; i > p; i--){
        for(int j = p; j < i; j++){
            if(A[j] > A[j+1])
                swap(&A[j], &A[j+1]);
        }
    }
}

int partition(int* A, int p, int r){
    int x = A[r];
    int i = p - 1;
    for(int j = p; j <= r; j++){
        if(A[j] <= x){
            i++;
            swap(&A[i], &A[j]);
        }
    }
    if(i < r)
        return i;
    else
        return i - 1;
}

void quicksort(int* A, int p, int r){
    if(p < r){
        int q = partition(A, p, r);
        quicksort(A, p, q);
        quicksort(A, q + 1, r);
    }
}

void quicksort_zmieniony(int* A, int p, int r){
    if(p + C < r){
        int q = partition(A, p, r);
        quicksort_zmieniony(A, p, q);
        quicksort_zmieniony(A, q + 1, r);
    }
    else{
        bubblesort(A, p, r);
    }
}

int main(){
    int A[ROZMIAR+1];
    int B[ROZMIAR+1];
    
    wypelnij_tablice_losowo(A,B);
    //wypelnij_tablice_malejaco(A,B);

    struct timespec tp0,tp1;
    double czas;

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0);
    quicksort(A, 1, ROZMIAR);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1);
    czas = (tp1.tv_sec+tp1.tv_nsec/MLD)-(tp0.tv_sec+tp0.tv_nsec/MLD);
    printf("ALGORYTM ZWYKŁY   \tCzas:%lf\n",czas);


    clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1);
    quicksort_zmieniony(B, 1, ROZMIAR);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1);
    czas = (tp1.tv_sec+tp1.tv_nsec/MLD)-(tp0.tv_sec+tp0.tv_nsec/MLD);
    printf("ALGORYTM ZMIENIONY\tCzas:%lf\n",czas);

    //pokaz_tablice(A, ROZMIAR);
    pokaz_tablice(B, ROZMIAR);

    return 0;
}