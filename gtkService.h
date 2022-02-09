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

typedef struct _widget {
    GtkWidget *home_fixed;
    GtkWidget *home_background;
    GtkWidget *mask;
    GtkWidget *loading_bar;
} Widget;

Widget widget;

pthread_t gtkThread;

int progress;
int start;

gboolean settime(gpointer);

gint findMaxArrayIndex(guint16[], gint);

void refreshLoadingBerFrame(GtkWidget *);

gboolean progressLoadingBar(gpointer);

void loadingCallback(GtkWidget*);

void* run(void*);

void startani(GtkWidget *);

#endif