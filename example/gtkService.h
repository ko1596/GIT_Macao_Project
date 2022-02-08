#ifndef GTKSERVICE_H
#define GTKSERVICE_H

#include "serialService.h"
#include <gtk/gtk.h>

#include <gdk/gdkkeysyms.h>

#define SELECT_BLOCK(x) ((x < 50000) && (x > 300))

typedef struct _gbutton {
    GtkWidget *image;
    double opacity;
} gbutton;

static GtkWidget *fixed;
static GtkWidget *fixed2;
static GtkWidget *SelectBlockImage;
static GtkWidget *window;
static GtkWidget *vbox;
static GtkWidget *frame;
static GtkWidget *frame2;
static GtkWidget *background;
static GtkWidget *background2;
static GtkWidget *label;

static GtkWidget *leftChangeImage;
static GtkWidget *rightChangeImage;

static GtkWidget *Timelabel;
static GtkWidget *ParkingTimeLabel;

static GtkWidget *addImage;
static GtkWidget *reduceImage;

gint status;
gint last_status;

gint selectBlockCount;
gint changeBackground;
gint page;

double selectButtonOpacity;
double leftButtonOpacity;
double rightButtonOpacity;

gdouble parkingTime;

double addOpacity;
double reduceOpacity;


pthread_t gtkThread;

gboolean settime(gpointer);

gint findMaxArrayIndex(guint16[], gint);

gboolean showPage(gpointer);

void* run(void*);

void setPage(gint p);




#endif