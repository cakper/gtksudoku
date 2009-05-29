#ifndef INTERFACE_H
#define INTERFACE_H
#include <gtk/gtk.h>
void kojaz_pola(); // kojazy odpowiednie pola tablicy z grą do interfejsu użytkownika
void aktualizuj_interface(int s); // wymusza aktualizację interfejsu po zmianach w tablicy w grą, jako parametr pobiera informację o tym, czy jest to generowanie nowej planszy i należy blokować pola, czy tylko jej wypełnianie
void wypelnij_tablice(); // na podstawie danych zawartych w tablicy z grą wypełnia wszystkie możliwe i w 100% pewne pola
void czytaj_z_pliku(); // odczytuje lamiglowke uzytkownika z pliku "plansza.txt"
GdkPixbuf *create_pixbuf(const gchar * filename); // wcztuje grafikę z pliku do pamięci, potrzebne do wstawienia ikony aplikacji, jako parametr pobiera nazwę pliku
#endif