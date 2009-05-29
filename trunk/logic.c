#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "logic.h"
#include "list.h"
#include "interface.h"
#include "signals.h"

int     tab[9][9][10];

bool sprawdz_wiersze(){
    int x, y, i = 0;
    long int iloczyn;

    for(y = 0; y <= 8; y++){
        iloczyn = 1;
        for(x = 0; x <= 8; x++){
            iloczyn = iloczyn * tab[x][y][0];
        }
        if(iloczyn == 362880) i++;
    }
    if(i == 9) return TRUE;

    return FALSE;
}

bool sprawdz_kolumny(){
    int x, y, i = 0;
    long int iloczyn;

    for(x = 0; x <= 8; x++){
        iloczyn = 1;
	for(y = 0; y <= 8; y++){
            iloczyn = iloczyn * tab[x][y][0];
	}
	if(iloczyn == 362880) i++;
    }
    if(i == 9) return TRUE;

    return FALSE;
}

bool sprawdz_kwadraty(){
    int x, y, ix, iy, i = 0;
    long int iloczyn;

    for(x = 0; x <= 6; x=x+3){
	for(y = 0; y <= 6; y=y+3){
            iloczyn = 1;
            for(ix = x; ix <= (x + 2); ix++){
                for(iy = y; iy <= (y + 2); iy++){
                    iloczyn = iloczyn * tab[ix][iy][0];
        	}
            }
            if(iloczyn == 362880) i++;
	}
    }
    if(i == 9) return TRUE;

    return FALSE;
}

bool sprawdz(){
    if(sprawdz_wiersze() && sprawdz_kolumny() && sprawdz_kwadraty()) return TRUE;

    return FALSE;
}


bool sprawdz_kolumne(int xy, int liczba){
    int x, i;

    x = ((int) xy / 10)-1;
    for(i = 0 ; i <= 8; i++){
        if((tab[x][i][0] == liczba) && (liczba !=0)) return FALSE;
    }

    return TRUE;
}

bool sprawdz_wiersz(int xy, int liczba){
    int y, i;

    y = (xy % 10) - 1;
    for(i = 0; i <= 8; i++){
        if((tab[i][y][0] == liczba) && (liczba !=0)) return FALSE;
    }

    return TRUE;
}

bool sprawdz_kwadrat(int xy, int liczba){
    int x, y, ix, iy;

    x = ((int)((int)(xy / 10)-1)/3)*3;
    y = ((int)((int)(xy % 10)-1)/3)*3;
    for(iy = y; iy <= (y + 2); iy++){
        for(ix = x; ix <= (x + 2); ix++){
            if(liczba == tab[ix][iy][0]) return FALSE;
        }
    }

    return TRUE;
}


bool sprawdz_poprawnosc(int xy, int liczba){
    int x, y;

    x = (int) xy / 10;
    y = xy % 10;
    if (sprawdz_kolumne(xy, liczba) && sprawdz_wiersz(xy, liczba) && sprawdz_kwadrat(xy, liczba) && (tab[x-1][y-1][0] == 0))
        return TRUE;
    else
        return FALSE;
}

void sprawdz_propozycje(int xy){
    int x, y, liczba;

    x = (int) xy / 10;
    y = xy % 10;
    for(liczba = 1; liczba <=9; liczba++){
	tab[x-1][y-1][liczba] = 0;
	if(sprawdz_poprawnosc(xy, liczba)){
	   tab[x-1][y-1][liczba] = 1;
    	}
    }
}


void sprawdz_tablice(){
    int x,y;

    for(y = 1; y <= 9; y++){
        for(x = 1; x <= 9; x++){
            sprawdz_propozycje(x*10 + y);
        }
    }
}

void generuj_puzzle(){
    int n = 3, i, j, k, x  = 0;

    for(i = 0; i < n; i++, x++)
        for(j = 0; j < n; j++, x+=n)
            for(k = 0; k < n*n; k++, x++)
                tab[n*i+j][k][0] = (x % (n*n)) + 1;
}

void zamien_kolumny(int pierwsza, int druga){
    int kolumna[9], y;

    pierwsza--;
    druga--;
    for(y = 0; y <= 8; y++){
        kolumna[y]=tab[pierwsza][y][0];
    }
    for(y = 0; y <= 8; y++){
        tab[pierwsza][y][0]=tab[druga][y][0];
    }
    for(y = 0; y <= 8; y++){
        tab[druga][y][0]=kolumna[y];
    }
}

void zamien_wiersze(int pierwszy, int drugi){
    int wiersz[9], x;

    pierwszy--;
    drugi--;
    for(x = 0; x <= 8; x++){
        wiersz[x]=tab[x][pierwszy][0];
    }
    for(x = 0; x <= 8; x++){
        tab[x][pierwszy][0]=tab[x][drugi][0];
    }
    for(x = 0; x <= 8; x++){
        tab[x][drugi][0]=wiersz[x];
    }
}

void mieszaj_tablice(){
    int n, m, j, k, x = 0, i;

    for(i = 1; i <= 256; i++){
        srand((unsigned)time(NULL) + i);
	n = rand() % 2;
        if(n==1){
            m = rand() % 3;
            k = (rand()>>2) % 3;
            j = k;
            while(k == j){
                x++;
                j = (rand()+x) % 3;
            }
	zamien_wiersze((m*3)+k+1,(m*3)+j+1);
	}
        else {
            m = rand() % 3;
            k = (rand()>>2) % 3;
            j = k;
            while(k == j){
                x++;
                j = (rand()+x) % 3;
            }
	zamien_kolumny((m*3)+k+1,(m*3)+j+1);
	}
    }
}

void komplikuj_tablice(int poziom){
    int x, y;

    if(poziom == 1){ poziom = 40;}
    else if(poziom == 2){ poziom = 46 ;}
    else if(poziom == 3){ poziom = 50 ;}
    else { poziom = 40;}
    while(poziom != 0){
        srand((unsigned)time(NULL) + rand());
        x = (rand() % 9);
	srand((unsigned)time(NULL) + rand());
	y = (rand() % 9);
        if(tab[x][y][0] != 0){
            tab[x][y][0] = 0;
            poziom--;
	}
    }
}

void generuj_tablice(int poziom){
    generuj_puzzle();
    mieszaj_tablice();
    komplikuj_tablice(poziom);
    aktualizuj_interface(1);
}