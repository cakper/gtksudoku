#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "logic.h"
#include "list.h"
#include "interface.h"
#include "signals.h"

GtkBuilder      *builder;

int main (int argc, char *argv[]){
    GtkWidget       *window;
    GtkWidget       *poziom;

    gtk_init (&argc, &argv);
    inicjuj_liste();

    builder = gtk_builder_new ();
    gtk_builder_add_from_file (builder, "interface.xml", NULL);

    window = GTK_WIDGET (gtk_builder_get_object (builder, "window"));
    poziom = GTK_WIDGET (gtk_builder_get_object (builder, "poziom"));
    gtk_window_set_icon(GTK_WINDOW(window), create_pixbuf("sudoku.png"));
    gtk_window_set_title(GTK_WINDOW(window), "GTKSudoku");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_builder_connect_signals (builder, NULL);
    kojaz_pola();
    generuj_tablice(1);
    gtk_combo_box_set_active(GTK_COMBO_BOX(poziom), 0);
    gtk_widget_show_all (window);
    gtk_main ();
    g_object_unref (G_OBJECT (builder));
    usun_liste();
    
    return 0;
}