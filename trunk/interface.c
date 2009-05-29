#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "logic.h"
#include "list.h"
#include "interface.h"
#include "signals.h"

FILE *plik;
GtkWidget       *entry[9][9];
extern  GtkBuilder      *builder;
extern  int             tab[9][9][10];
int     semafor;


void kojaz_pola(){
    int x, y;
    gchar ent[3];

    for(x = 0; x <= 8; x++){
        for(y = 0; y <= 8; y++){
            sprintf(ent, "%d%d", x, y);
            ent[2] = '\0';
            entry[x][y] = GTK_WIDGET (gtk_builder_get_object (builder, ent));
        }
    }
}

void aktualizuj_interface(int s){
    int x, y;
    gchar e[2];

    semafor = 1;
    for(x = 0; x <=8; x++)
        for(y = 0; y <= 8; y++){
            if(tab[x][y][0] == 0){
                gtk_entry_set_text(GTK_ENTRY(entry[x][y]), "0");
                if(s == 1){
                    gtk_entry_set_editable(GTK_ENTRY(entry[x][y]), TRUE);
                    gtk_entry_set_has_frame(GTK_ENTRY(entry[x][y]), TRUE);
                }
            }
            else{
                sprintf(e, "%d", tab[x][y][0]);
                e[1] = '\0';
                gtk_entry_set_text(GTK_ENTRY(entry[x][y]), e);
                if(s == 1){
                    gtk_entry_set_editable(GTK_ENTRY(entry[x][y]), FALSE);
                    gtk_entry_set_has_frame(GTK_ENTRY(entry[x][y]), FALSE);
                }
            }
        }
    semafor = 0;
}



void wypelnij_tablice(){
    int x, y, i, j, suma;

    for(j = 1; j <= 500; j++){
        sprawdz_tablice();
	for(y=0; y <= 8; y++){
            for(x = 0; x <= 8; x++){
                suma=0;
		for(i=1; i<=9; i++){
                    suma=suma+tab[x][y][i];
	    	}
		if(suma==1){
                    for(i=1; i<=9; i++){
                        if(tab[x][y][i]==1){
                            dodaj_na_koniec(tab[x][y][0], x, y);
                            tab[x][y][0]=i;
			}
                    }
		}
            }
	}
    }
    aktualizuj_interface(0);
}

void czytaj_z_pliku(){
    int x,y;

    char* wiersz = malloc (sizeof(char) * 10);
    wiersz[9]='\0';
    plik = fopen("plansza.txt", "r");
    for (y = 0; y <= 8; y++){
    	wiersz = fgets(wiersz,9,plik);
        for(x = 0; x <= 8; x++){
            tab[x][y][0] = (int)wiersz[x]-48;
	}
    }
    free(wiersz);
    aktualizuj_interface(1);
}

GdkPixbuf *create_pixbuf(const gchar * filename){
   GdkPixbuf *pixbuf;
   GError *error = NULL;

   pixbuf = gdk_pixbuf_new_from_file(filename, &error);
   if(!pixbuf) {
      fprintf(stderr, "%s\n", error->message);
      g_error_free(error);
   }

   return pixbuf;
}