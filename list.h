#ifndef LIST_H
#define LIST_H
#include <gtk/gtk.h>
void inicjuj_liste(); // inicjuje pusta liste dwukierunkowa w ktorej przechowywana jest lista ruchow
struct list *rezerwuj_pamiec(void); // rezerwuje pamiec dla struktury listy
void dodaj_na_koniec(int liczba, int x, int y); // dodaje rekord na koniec listy dwukierunkowej
int usun_z_konca(); // usuwa rekord z konca listy
void usun_liste(); // usuwa cala liste
#endif