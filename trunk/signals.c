#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "logic.h"
#include "list.h"
#include "interface.h"
#include "signals.h"

extern  GtkWidget       *entry[9][9];
extern  int             tab[9][9][10], semafor;
extern  GtkBuilder      *builder;

struct list {
	int liczba[3];
	struct list *prev;
	struct list *next;
};

extern struct list *tail;

G_MODULE_EXPORT void on_window_destroy (GtkObject *object, gpointer user_data){
    gtk_main_quit ();
}

G_MODULE_EXPORT void on_czytajzpliku_clicked (GtkObject *object, gpointer user_data){
    czytaj_z_pliku();
}

G_MODULE_EXPORT void on_zakoncz_clicked (GtkObject *object, gpointer user_data){
    gtk_main_quit ();
}
G_MODULE_EXPORT void on_cofnij_clicked (GtkObject *object, gpointer user_data){
    gchar e[2];

    if(tail != NULL){
        int x,y, l;

        x = tail->liczba[1];
        y = tail->liczba[2];
        l = tail->liczba[0];
        tab[x][y][0] = l;
        sprintf(e, "%d", tab[x][y][0]);
        e[1] = '\0';
        semafor = 1;
        gtk_entry_set_text(GTK_ENTRY(entry[x][y]), e);
        semafor = 0;
        usun_z_konca();
    }
}

G_MODULE_EXPORT void on_rozwiaz_clicked (GtkObject *object, gpointer user_data){
//    wypelnij_tablice();
    recursive(1, 1);
    if(sprawdz()){
        GtkWidget *dialog = gtk_message_dialog_new (user_data,
                                                    GTK_DIALOG_MODAL,
                                                    GTK_MESSAGE_INFO,
                                                    GTK_BUTTONS_OK,
                                                    "Plansza jest poprawnie rozwiazana! :)");
        gtk_dialog_run (GTK_DIALOG(dialog));
        gtk_widget_destroy (dialog);
    }
    else{
        GtkWidget *dialog = gtk_message_dialog_new (user_data,
                                                    GTK_DIALOG_MODAL,
                                                    GTK_MESSAGE_INFO,
                                                    GTK_BUTTONS_OK,
                                                    "Niestety, nie udalo sie poprawnie rozwiazac lamiglowki");
        gtk_dialog_run (GTK_DIALOG(dialog));
        gtk_widget_destroy (dialog);
    }
}

G_MODULE_EXPORT void on_sprawdz_clicked (GtkWidget *widget,gpointer data){
    if(sprawdz()){
        GtkWidget *dialog = gtk_message_dialog_new (data,
                                                    GTK_DIALOG_MODAL,
                                                    GTK_MESSAGE_INFO,
                                                    GTK_BUTTONS_OK,
                                                    "Plansza jest poprawnie rozwiazana! :)");
        gtk_dialog_run (GTK_DIALOG(dialog));
        gtk_widget_destroy (dialog);
    }
    else{
        GtkWidget *dialog = gtk_message_dialog_new (data,
                                                    GTK_DIALOG_MODAL,
                                                    GTK_MESSAGE_INFO,
                                                    GTK_BUTTONS_OK,
                                                    "Plansza nie jest poprawnie rozwiazana.");
        gtk_dialog_run (GTK_DIALOG(dialog));
        gtk_widget_destroy (dialog);
    }
}

G_MODULE_EXPORT void on_wyczysc_clicked (GtkObject *object, gpointer user_data){
    int x, y;

    semafor = 1;
    for(x = 0; x <= 8; x++)
        for(y = 0; y <= 8; y++){
            if(gtk_entry_get_has_frame(GTK_ENTRY(entry[x][y]))) tab[x][y][0] = 0;
        }
    aktualizuj_interface(1);
    semafor = 0;
}

G_MODULE_EXPORT void on_generuj_clicked (GtkObject *object, gpointer user_data){
    GtkWidget       *poziom;

    poziom = GTK_WIDGET(gtk_builder_get_object (builder, "poziom"));
    generuj_tablice(gtk_combo_box_get_active(GTK_COMBO_BOX(poziom)) + 1);
}

G_MODULE_EXPORT void on_input_changed (GtkObject *object, gpointer user_data){
    gchar e[2], f[2], g[2];
    int ix, iy, x = 100, y = 0;

    if(semafor == 0){
        for(ix = 0; ix <= 8; ix++){
            for(iy = 0; iy <= 8; iy++){
                sprintf(f, "%d", tab[ix][iy][0]);
                f[1] = '\0';
                sprintf(g, "%s", gtk_entry_get_text(GTK_ENTRY(entry[ix][iy])));
                g[1] = '\0';
                if((g[0] != f[0])){
                    x = ix;
                    y = iy;
                }
            }
        }
        if(x != 100) {
            sprintf(g, "%s", gtk_entry_get_text(GTK_ENTRY(entry[x][y])));
            g[1] = '\0';
            if(g[0]){
                if((g[0] >= '1') && (g[0] <= '9')){
                    if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(gtk_builder_get_object (builder, "podpowiedzi")))){
                        int xy;

                        xy = (x+1)*10 + y + 1;
                        if(sprawdz_poprawnosc(xy, g[0] - '0')) {
                            dodaj_na_koniec(tab[x][y][0], x, y);
                            tab[x][y][0] = g[0] - '0';
                        }
                        else{
                            GtkWidget *dialog = gtk_message_dialog_new (user_data,
                                                                        GTK_DIALOG_MODAL,
                                                                        GTK_MESSAGE_INFO,
                                                                        GTK_BUTTONS_OK,
                                                                        "Wpisana przez Ciebie cyfra nie jest poprawna wartoscia w tym miejscu!");
                            gtk_dialog_run (GTK_DIALOG(dialog));
                            gtk_widget_destroy (dialog);
                            e[1] = '\0';
                            sprintf(e, "%d", tab[x][y][0]);
                            semafor = 1;
                            gtk_entry_set_text(GTK_ENTRY(entry[x][y]), e);
                            semafor = 0;
                        }
                    }
                    else{
                        dodaj_na_koniec(tab[x][y][0], x, y);
                        tab[x][y][0] = g[0] - '0';
                    }
                }
                else if(g[0] == '0'){
                    semafor = 1;
                    tab[x][y][0] = 0;
                    semafor = 0;
                }
                else{
                    GtkWidget *dialog = gtk_message_dialog_new (user_data,
                                                                GTK_DIALOG_MODAL,
                                                                GTK_MESSAGE_INFO,
                                                                GTK_BUTTONS_OK,
                                                                "Wpisany przez Ciebie znak nie jest cyfra!");
                    gtk_dialog_run (GTK_DIALOG(dialog));
                    gtk_widget_destroy (dialog);
                    e[1] = '\0';
                    sprintf(e, "%d", tab[x][y][0]);
                    semafor = 1;
                    gtk_entry_set_text(GTK_ENTRY(entry[x][y]), e);
                    semafor = 0;
                }
            }
        }
    }
}