#ifndef LOGIC_H
#define LOGIC_H
typedef enum {ETRUE = 1, EFALSE = 0} bool;
#include <gtk/gtk.h>
bool sprawdz_wiersze(); // sprawdza czy iloczyn liczb wpisanych w wierszach rozwiazanego sudoku jest prawidlowy
bool sprawdz_kolumny(); // sprawdza czy iloczyn liczb wpisanych w kolumnach rozwiazanego sudoku jest prawidlowy
bool sprawdz_kwadraty(); // sprawdza czy iloczyn liczb wpisanych w malych kwadratach rozwiazanego sudoku jest prawidlowy
bool sprawdz(); // sprawdza uzywajac wczesniej zadeklarowanych funkcji czy sudoku jest poprawnie rozwiazane
bool sprawdz_kolumne(int xy, int liczba); // sprawdza czy liczba moze zostac wpisana w danej kolumnie
bool sprawdz_wiersz(int xy, int liczba); // sprawdza czy liczba moze byc wpisana w danym wierszu
bool sprawdz_kwadrat(int xy, int liczba); // sprawdza czy dana liczba moze byc wpisana w danym malym kwadracie
bool sprawdz_poprawnosc(int xy, int liczba); // sprawdza korzystajac z wczesniej zadeklarowanych funkcji czy dana liczba moze byc wpisana w konkretnym polu
void sprawdz_propozycje(int xy); // sprawdza wszystkie mozliwe propozycje do wpisania w danym polu
void sprawdz_tablice(); // sprawdza cale sudoku w poszukiwaniu propozycji
void generuj_puzzle(); // generuje podstawową planszę sudoku
void zamien_kolumny(int pierwsza, int druga); // zamienia kolumny w podstawowym sodoku w ramach trójek logicznych
void zamien_wiersze(int pierwszy, int drugi); // zamienia wierszy w podstawowym sodoku w ramach trójek logicznych
void mieszaj_tablice(); // wywołuje funkcje zamien_kolumny() i zamien_wiersze()
void komplikuj_tablice(int poziom); // usuwa z wygenerowanej i wymieszanej tablicy zadana wg poziomu ilosc cyfr tworzac lamiglowke
void generuj_tablice(int poziom); // genereuje lamiglowke o zadanym poziomie w oparciu o wczesniej napisane funkcje
#endif