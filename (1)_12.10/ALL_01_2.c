#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define MLD 1000000000.0
/////////////////////////////////////////////
//   PROCEDURY POMOCNICZE                  //
/////////////////////////////////////////////
void utworz_MACIERZ(int n, int ***M){
// alokuje pamięć na tablicę rozmiaru nxn
// i wpisuje losowe wartości 0/1 
int i,j;
    (*M) = (int **)malloc(n*sizeof(int *));
    for(i=0;i<n;i++){
        (*M)[i]=(int *)malloc(n*sizeof(int));
    }
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            (*M)[i][j]=rand()% 2;
            }
    }
}
/////////////////////////////////////////////
void utworz_MACIERZ_x(int n, int ***M, int x){
// alokuje pami na tablicę rozmiaru nxn
// i wpisuje wszdzie wartości x
int i,j;
    (*M) = (int **)malloc(n*sizeof(int *));
    for(i=0;i<n;i++){
        (*M)[i]=(int *)malloc(n*sizeof(int));
    }
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            (*M)[i][j]=x;
            }
    }
}
/////////////////////////////////////////////
void wypisz_MACIERZ(int n, int **M){
// wypisuje wartości tablicy
int i,j;

for(i=0;i<n;i++){
    for(j=0;j<n;j++)
        printf("%d",M[i][j]);
    printf("\n");
    }
}
/////////////////////////////////////////////
void zwolnij_MACIERZ(int n, int **M){
// zwalania pamięć zarezerwowaną dla macierzy
int i;
    for(i=0;i<n;i++)
    {
    free(M[i]);
    }
    free(M);
}
/////////////////////////////////////////////
//   ALGORYTM PIERWSZY                     //
/////////////////////////////////////////////
int ALGO_NAIWNY(int n, int **M){
int x1,y1,x2,y2,x,y;
int max=0;
int local_max=0;

for(x1=0;x1<n;x1++)
    for(y1=0;y1<n;y1++)
        for(x2=n-1;x2>x1-1;x2--)
            for(y2=n-1;y2>y1-1;y2--){
                local_max=0;
                for(x=x1;x<x2+1;x++)
                    for(y=y1;y<y2+1;y++)
                        local_max+=M[x][y];
                if ((local_max==(x2-x1+1)*(y2-y1+1)) && (local_max>max)) max=local_max;
                }
return max;
}
/////////////////////////////////////////////
//   ALGORYTM DRUGI                        //
/////////////////////////////////////////////
int REKURENCJA(int **M,int x1, int y1, int x2, int y2){
if ((x2==x1)&&(y2==y1)) return M[x1][y1];
    else if ((x2-x1)>(y2-y1))
        return REKURENCJA(M,x1,y1,(int)(x1+x2)/2,y2)*REKURENCJA(M,(int)(x1+x2+1)/2,y1,x2,y2);
            else return REKURENCJA(M,x1,y1,x2,(int)(y1+y2)/2)*REKURENCJA(M,x1,(int)(y1+y2+1)/2,x2,y2);
}
/////////////////////////////////////////////
int ALGO_REKURENCYJNY(int n, int **M){
int x1,y1,x2,y2;
int max=0;
int local_max;

for(x1=0;x1<n;x1++)
    for(y1=0;y1<n;y1++)
        for(x2=x1;x2<n;x2++)
            for(y2=y1;y2<n;y2++){
                local_max=REKURENCJA(M,x1,y1,x2,y2)*(x2-x1+1)*(y2-y1+1);
                if (local_max>max) max=local_max;
            }
return max;
}
/////////////////////////////////////////////
//   ALGORYTM TRZECI                       //
/////////////////////////////////////////////
int ALGO_DYNAMICZNY(int n, int **M){
int x1,x2,y;
int max=0;
int iloczyn;
int **MM;

utworz_MACIERZ_x(n,&MM,0);

for(y=0;y<n;y++)
    for(x1=0;x1<n;x1++){
        iloczyn=1;
        for(x2=x1;x2<n;x2++){
            iloczyn*=M[x2][y];
            MM[x1][x2]=iloczyn*(x2-x1+1+MM[x1][x2]);
            if (MM[x1][x2]>max) max=MM[x1][x2];
        }
    }
return max;
}
/////////////////////////////////////////////
//   ALGORYTM CZWARTY                      //
/////////////////////////////////////////////
int ALGO_CZULY(int n, int **M){
int x1,y1,x2,y2,ymax;
int max=0;
int local_max=0;

for(x1=0;x1<n;x1++)
    for(y1=0;y1<n;y1++){
        local_max=0;
        x2=x1;
        ymax=n-1;
        while ((x2<n)&&(M[x2][y1]==1)){
            y2=y1;
            while((y2<ymax+1)&&(M[x2][y2]==1)){
                y2++;
            }
            ymax=y2-1;
            local_max=(x2-x1+1)*(ymax-y1+1);
            if (local_max>max) max=local_max;
            x2++;
        }
    }
return max;
}
/////////////////////////////////////////////
/////////////////////////////////////////////
/////////////////////////////////////////////
int main(){
int **Macierz;
srand(time(NULL));

struct timespec tp0, tp1;
double Tn,Fn,Fn2;

printf("ALGORYTM NAIWNY\n");
for(int n=10; n<71; n+=10){
    utworz_MACIERZ(n,&Macierz);
    //utworz_MACIERZ_x(n,&Macierz,0);
    //utworz_MACIERZ_x(n,&Macierz,1);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0);
    printf("Wynik =%d \t",ALGO_NAIWNY(n,Macierz));
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1);
    Tn=(tp1.tv_sec+tp1.tv_nsec/MLD)-(tp0.tv_sec+tp0.tv_nsec/MLD);
    Fn=n*n*n*n*n*sqrt(n);
    printf("n: %d \toszacowanie: Fn=n^5*sqrt(n)\tczas: %3.10lf \twspolczynnik: %3.5lf\n",n,Tn, Fn/Tn);
    zwolnij_MACIERZ(n,Macierz);
}

printf("\nALGORYTM REKURENCYJNY\n");
for(int n=10; n<51; n+=10){
    utworz_MACIERZ(n,&Macierz);
    //utworz_MACIERZ_x(n,&Macierz,0);
    //utworz_MACIERZ_x(n,&Macierz,1);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0);
    printf("Wynik =%d \t",ALGO_REKURENCYJNY(n,Macierz));
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1);
    Tn=(tp1.tv_sec+tp1.tv_nsec/MLD)-(tp0.tv_sec+tp0.tv_nsec/MLD);
    Fn=n/100000.0*n*n*n*n*n;
    printf("n: %d \toszacowanie: Fn=n^6\tczas: %3.10lf \twspolczynnik: %3.5lf\n",n,Tn, Fn/(Tn/100000.0));
    zwolnij_MACIERZ(n,Macierz);
}

printf("\nALGORYTM DYNAMICZNY\n");
for(int n=10; n<81; n+=10){
    utworz_MACIERZ(n,&Macierz);
    //utworz_MACIERZ_x(n,&Macierz,0);
    //utworz_MACIERZ_x(n,&Macierz,1);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0);
    printf("Wynik =%d \t",ALGO_DYNAMICZNY(n,Macierz));
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1);
    Tn=(tp1.tv_sec+tp1.tv_nsec/MLD)-(tp0.tv_sec+tp0.tv_nsec/MLD);
    Fn=n*n*n;
    printf("n: %d \toszacowanie: Fn=n^3\tczas: %3.10lf \twspolczynnik: %3.5lf\n",n,Tn, Fn/Tn);
    zwolnij_MACIERZ(n,Macierz);
}

printf("\nALGORYTM CZUŁY\n");
for(int n=10; n<401; n+=50){
    utworz_MACIERZ(n,&Macierz);
    //utworz_MACIERZ_x(n,&Macierz,0);
    //utworz_MACIERZ_x(n,&Macierz,1);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0);
    printf("Wynik =%d \t",ALGO_CZULY(n,Macierz));
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1);
    Tn=((tp1.tv_sec+tp1.tv_nsec/MLD)-(tp0.tv_sec+tp0.tv_nsec/MLD));
    Fn=n*n;
    printf("n: %d \toszacowanie: Fn=n^2\tczas: %3.10lf \twspolczynnik: %3.5lf\n",n,Tn, Fn/Tn);
    zwolnij_MACIERZ(n,Macierz);
}
return 1;
}

//Oszacowanie zmienia się dla algorytmu czułego gdy macierz składa się z samych 1. Wynosi ono wtedy n^4 zamiast n^2

/*

WYNIKI ZWYKŁE
ALGORYTM NAIWNY
Wynik =6        n: 10   oszacowanie: Fn=n^5*sqrt(n)     czas: 0.0005885100      wspolczynnik: 537336266.19231
Wynik =9        n: 20   oszacowanie: Fn=n^5*sqrt(n)     czas: 0.0070684510      wspolczynnik: 2024606955.04555
Wynik =11       n: 30   oszacowanie: Fn=n^5*sqrt(n)     czas: 0.0483800480      wspolczynnik: 2751063444.04113
Wynik =13       n: 40   oszacowanie: Fn=n^5*sqrt(n)     czas: 0.2683046430      wspolczynnik: 2413802674.30737
Wynik =12       n: 50   oszacowanie: Fn=n^5*sqrt(n)     czas: 0.9460240230      wspolczynnik: 2335784966.85592
Wynik =15       n: 60   oszacowanie: Fn=n^5*sqrt(n)     czas: 2.7287677840      wspolczynnik: 2207319998.18339
Wynik =10       n: 70   oszacowanie: Fn=n^5*sqrt(n)     czas: 6.7427858730      wspolczynnik: 2085450336.22755

ALGORYTM REKURENCYJNY
Wynik =6        n: 10   oszacowanie: Fn=n^6     czas: 0.0005548370      wspolczynnik: 1802331135.08967
Wynik =9        n: 20   oszacowanie: Fn=n^6     czas: 0.0290831490      wspolczynnik: 2200587013.46269
Wynik =10       n: 30   oszacowanie: Fn=n^6     czas: 0.3053878860      wspolczynnik: 2387128086.67204
Wynik =12       n: 40   oszacowanie: Fn=n^6     czas: 1.6588034520      wspolczynnik: 2469249744.48389
Wynik =13       n: 50   oszacowanie: Fn=n^6     czas: 6.4606226890      wspolczynnik: 2418497527.58406

ALGORYTM DYNAMICZNY
Wynik =8        n: 10   oszacowanie: Fn=n^3     czas: 0.0000044710      wspolczynnik: 223663609.90815
Wynik =9        n: 20   oszacowanie: Fn=n^3     czas: 0.0000203530      wspolczynnik: 393062447.79584
Wynik =11       n: 30   oszacowanie: Fn=n^3     czas: 0.0000646740      wspolczynnik: 417478430.28764
Wynik =12       n: 40   oszacowanie: Fn=n^3     czas: 0.0001499820      wspolczynnik: 426717872.81158
Wynik =15       n: 50   oszacowanie: Fn=n^3     czas: 0.0003530500      wspolczynnik: 354057498.93853
Wynik =15       n: 60   oszacowanie: Fn=n^3     czas: 0.0004814210      wspolczynnik: 448671744.68923
Wynik =14       n: 70   oszacowanie: Fn=n^3     czas: 0.0008201610      wspolczynnik: 418210570.85131
Wynik =20       n: 80   oszacowanie: Fn=n^3     czas: 0.0012380230      wspolczynnik: 413562591.32534

ALGORYTM CZUŁY
Wynik =6        n: 10   oszacowanie: Fn=n^2     czas: 0.0000033390      wspolczynnik: 29949086.54448
Wynik =12       n: 60   oszacowanie: Fn=n^2     czas: 0.0001292170      wspolczynnik: 27860111.28576
Wynik =16       n: 110  oszacowanie: Fn=n^2     czas: 0.0002869460      wspolczynnik: 42168212.83458
Wynik =14       n: 160  oszacowanie: Fn=n^2     czas: 0.0006734700      wspolczynnik: 38012086.65574
Wynik =16       n: 210  oszacowanie: Fn=n^2     czas: 0.0008678880      wspolczynnik: 50813008.13007
Wynik =18       n: 260  oszacowanie: Fn=n^2     czas: 0.0013199060      wspolczynnik: 51215768.39559
Wynik =18       n: 310  oszacowanie: Fn=n^2     czas: 0.0019366420      wspolczynnik: 49621974.53116
Wynik =18       n: 360  oszacowanie: Fn=n^2     czas: 0.0031481780      wspolczynnik: 41166668.46665
*/

//////////////////////////////////////////////////////////////////////////////////////////////////////

/*
WYNIKI DLA MACIERZY 0
ALGORYTM NAIWNY
Wynik =0        n: 10   oszacowanie: Fn=n^5*sqrt(n)     czas: 0.0005646110      wspolczynnik: 560080774.22657
Wynik =0        n: 20   oszacowanie: Fn=n^5*sqrt(n)     czas: 0.0071357490      wspolczynnik: 2005512673.72194
Wynik =0        n: 30   oszacowanie: Fn=n^5*sqrt(n)     czas: 0.0477085380      wspolczynnik: 2789785372.87718
Wynik =0        n: 40   oszacowanie: Fn=n^5*sqrt(n)     czas: 0.2509169720      wspolczynnik: 2581070780.66638
Wynik =0        n: 50   oszacowanie: Fn=n^5*sqrt(n)     czas: 0.9148843320      wspolczynnik: 2415287500.19949
Wynik =0        n: 60   oszacowanie: Fn=n^5*sqrt(n)     czas: 2.6414251310      wspolczynnik: 2280308318.91929
Wynik =0        n: 70   oszacowanie: Fn=n^5*sqrt(n)     czas: 6.4977772890      wspolczynnik: 2164085415.75642

ALGORYTM REKURENCYJNY
Wynik =0        n: 10   oszacowanie: Fn=n^6     czas: 0.0005626510      wspolczynnik: 1777300671.28621
Wynik =0        n: 20   oszacowanie: Fn=n^6     czas: 0.0284179790      wspolczynnik: 2252095407.62910
Wynik =0        n: 30   oszacowanie: Fn=n^6     czas: 0.3034896650      wspolczynnik: 2402058732.37891
Wynik =0        n: 40   oszacowanie: Fn=n^6     czas: 1.6565114890      wspolczynnik: 2472666218.85772
Wynik =0        n: 50   oszacowanie: Fn=n^6     czas: 6.4634067930      wspolczynnik: 2417455762.94566

ALGORYTM DYNAMICZNY
Wynik =0        n: 10   oszacowanie: Fn=n^3     czas: 0.0000040010      wspolczynnik: 249937515.69197
Wynik =0        n: 20   oszacowanie: Fn=n^3     czas: 0.0000202180      wspolczynnik: 395687011.58330
Wynik =0        n: 30   oszacowanie: Fn=n^3     czas: 0.0000648630      wspolczynnik: 416261967.52891
Wynik =0        n: 40   oszacowanie: Fn=n^3     czas: 0.0001500870      wspolczynnik: 426419343.44820
Wynik =0        n: 50   oszacowanie: Fn=n^3     czas: 0.0003796710      wspolczynnik: 329232414.38047
Wynik =0        n: 60   oszacowanie: Fn=n^3     czas: 0.0005607380      wspolczynnik: 385206638.39386
Wynik =0        n: 70   oszacowanie: Fn=n^3     czas: 0.0007593190      wspolczynnik: 451720554.86552
Wynik =0        n: 80   oszacowanie: Fn=n^3     czas: 0.0012185700      wspolczynnik: 420164619.18454

ALGORYTM CZUŁY
Wynik =0        n: 10   oszacowanie: Fn=n^2     czas: 0.0000008670      wspolczynnik: 115340253.65788
Wynik =0        n: 60   oszacowanie: Fn=n^2     czas: 0.0000081280      wspolczynnik: 442913385.76951
Wynik =0        n: 110  oszacowanie: Fn=n^2     czas: 0.0000251070      wspolczynnik: 481937308.33910
Wynik =0        n: 160  oszacowanie: Fn=n^2     czas: 0.0000520730      wspolczynnik: 491617536.91107
Wynik =0        n: 210  oszacowanie: Fn=n^2     czas: 0.0001026640      wspolczynnik: 429556611.86039
Wynik =0        n: 260  oszacowanie: Fn=n^2     czas: 0.0001495020      wspolczynnik: 452167863.97718
Wynik =0        n: 310  oszacowanie: Fn=n^2     czas: 0.0002093780      wspolczynnik: 458978498.21638
Wynik =0        n: 360  oszacowanie: Fn=n^2     czas: 0.0002587010      wspolczynnik: 500964433.84464
*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
WYNIKI DLA MACIERZY 1
ALGORYTM NAIWNY
Wynik =100      n: 10   oszacowanie: Fn=n^5*sqrt(n)     czas: 0.0001371320      wspolczynnik: 2306010019.66600
Wynik =400      n: 20   oszacowanie: Fn=n^5*sqrt(n)     czas: 0.0054973950      wspolczynnik: 2603202981.77567
Wynik =900      n: 30   oszacowanie: Fn=n^5*sqrt(n)     czas: 0.0483211030      wspolczynnik: 2754419357.39247
Wynik =1600     n: 40   oszacowanie: Fn=n^5*sqrt(n)     czas: 0.2512899270      wspolczynnik: 2577240053.09009
Wynik =2500     n: 50   oszacowanie: Fn=n^5*sqrt(n)     czas: 0.9164801540      wspolczynnik: 2411081878.38398
Wynik =3600     n: 60   oszacowanie: Fn=n^5*sqrt(n)     czas: 2.6353055700      wspolczynnik: 2285603524.91562
Wynik =4900     n: 70   oszacowanie: Fn=n^5*sqrt(n)     czas: 6.5043185160      wspolczynnik: 2161909050.32828

ALGORYTM REKURENCYJNY
Wynik =100      n: 10   oszacowanie: Fn=n^6     czas: 0.0006539070      wspolczynnik: 1529269452.68921
Wynik =400      n: 20   oszacowanie: Fn=n^6     czas: 0.0283496890      wspolczynnik: 2257520355.86707
Wynik =900      n: 30   oszacowanie: Fn=n^6     czas: 0.3005062040      wspolczynnik: 2425906654.49289
Wynik =1600     n: 40   oszacowanie: Fn=n^6     czas: 1.6491425200      wspolczynnik: 2483714991.47327
Wynik =2500     n: 50   oszacowanie: Fn=n^6     czas: 6.4705141830      wspolczynnik: 2414800363.32377

ALGORYTM DYNAMICZNY
Wynik =100      n: 10   oszacowanie: Fn=n^3     czas: 0.0000042780      wspolczynnik: 233754090.67100
Wynik =400      n: 20   oszacowanie: Fn=n^3     czas: 0.0000207520      wspolczynnik: 385505011.54532
Wynik =900      n: 30   oszacowanie: Fn=n^3     czas: 0.0000650730      wspolczynnik: 414918629.84631
Wynik =1600     n: 40   oszacowanie: Fn=n^3     czas: 0.0001868640      wspolczynnik: 342495076.63366
Wynik =2500     n: 50   oszacowanie: Fn=n^3     czas: 0.0003812300      wspolczynnik: 327886053.03855
Wynik =3600     n: 60   oszacowanie: Fn=n^3     czas: 0.0004926030      wspolczynnik: 438486976.32811
Wynik =4900     n: 70   oszacowanie: Fn=n^3     czas: 0.0007884540      wspolczynnik: 435028549.54110
Wynik =6400     n: 80   oszacowanie: Fn=n^3     czas: 0.0012278510      wspolczynnik: 416988706.28458

ALGORYTM CZUŁY
Wynik =100      n: 10   oszacowanie: Fn=n^4     czas: 0.0000090960      wspolczynnik: 1099384344.83569
Wynik =3600     n: 60   oszacowanie: Fn=n^4     czas: 0.0069712140      wspolczynnik: 1859073613.29031
Wynik =12100    n: 110  oszacowanie: Fn=n^4     czas: 0.0701327970      wspolczynnik: 2087611021.70212
Wynik =25600    n: 160  oszacowanie: Fn=n^4     czas: 0.3164507600      wspolczynnik: 2070969903.81696
Wynik =44100    n: 210  oszacowanie: Fn=n^4     czas: 0.9301606030      wspolczynnik: 2090832479.60352
Wynik =67600    n: 260  oszacowanie: Fn=n^4     czas: 2.1880930760      wspolczynnik: 2088466916.75194
Wynik =96100    n: 310  oszacowanie: Fn=n^4     czas: 4.4225074810      wspolczynnik: 2088229367.54236
Wynik =129600   n: 360  oszacowanie: Fn=n^4     czas: 8.0373803430      wspolczynnik: 2089755527.69856
*/