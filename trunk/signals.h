#ifndef SIGNALS_H
#define SIGNALS_H
#include <gtk/gtk.h>
G_MODULE_EXPORT void on_window_destroy (GtkObject *object, gpointer user_data); // sygnał wysyłany w przypadku zamknięcia okna
G_MODULE_EXPORT void on_czytajzpliku_clicked (GtkObject *object, gpointer user_data); // sygnał wysyłany w przypadku ządania wczytania planszy z pliku
G_MODULE_EXPORT void on_zakoncz_clicked (GtkObject *object, gpointer user_data); // sygnał wysyłany w przypadku kliknięcia przycisku zakończ
G_MODULE_EXPORT void on_cofnij_clicked (GtkObject *object, gpointer user_data); // sygnał wysyłany w przypadku ządania cofnięcia ruchu
G_MODULE_EXPORT void on_rozwiaz_clicked (GtkObject *object, gpointer user_data); // sygnał wysyłany w przypadku kliknięcia przycisku rozwiąż
G_MODULE_EXPORT void on_sprawdz_clicked (GtkWidget *widget,gpointer data); // sygnał wysyłany w przypadku kliknięcia przycisku sprawdź
G_MODULE_EXPORT void on_wyczysc_clicked (GtkObject *object, gpointer user_data); // sygnał wysyłany w przypadku kliknięcia przycisku wyczyść
G_MODULE_EXPORT void on_generuj_clicked (GtkObject *object, gpointer user_data); // sygnał wysyłany w przypadku kliknięcia przycisku generuj
G_MODULE_EXPORT void on_input_changed (GtkObject *object, gpointer user_data); // sygnał wysyłany w przypadku zmiany wartości w jednym z pól wejściowych
#endif