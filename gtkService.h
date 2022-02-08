#ifndef GTKSERVICE_H
#define GTKSERVICE_H

#include "serialService.h"
#include <gtk/gtk.h>

#define SELECT_BLOCK(x) ((x < 50000) && (x > 300))

static GtkWidget *home;

typedef struct _gbutton {
    GtkWidget *image;
    double opacity;
} gbutton;

pthread_t gtkThread;

int progress;
int start;

gboolean settime(gpointer);

gint findMaxArrayIndex(guint16[], gint);

void refreshLoadingBerFrame(GtkWidget *);

void loadingCallback(GtkWidget*, gpointer);

void startCallback(GtkWidget*, gpointer);

void* run(void*);

void startani();

#endif