#ifndef GTKSERVICE_H
#define GTKSERVICE_H

#include "serialService.h"
#include <gtk/gtk.h>
#include <time.h>

#define SELECT_BLOCK(x) ((x < 50000) && (x > 300))

/** @defgroup ParkingStatus_group Defines Parking Status
 *  Defines all possible Status
 *  @{
 */
typedef uint8_t ParkingStatus;

/*!< Parking space don't have car>*/
#define PARKING_STATUS_EMPTY                ((ParkingStatus)  0)

/*!< Parking space is have time to parking>*/
#define PARKING_STATUS_DEADLINE             ((ParkingStatus)  1)

/*!< Parking space is expired>*/
#define PARKING_STATUS_EXPIRED              ((ParkingStatus)  2)

/*!< Parking space is waiting for payment>*/
#define PARKING_STATUS_PAYMENT              ((ParkingStatus)  3)    
/** @} ParkingStatus_group */


static GtkWidget *home;
static GtkWidget *selectTimewindwos;
static GtkWidget *paymentWindow;

typedef struct _gbutton {
    GtkWidget *image;
    double opacity;
} gbutton;

typedef struct _widget {
    GtkWidget *home_fixed;
    GtkWidget *home_background;
    GtkWidget *mask;
    GtkWidget *loading_bar;
    gbutton selectbutton;
    gbutton hoverAnimation;

    GtkWidget *select_fixed;
    GtkWidget *select_background;
    gbutton select_timer;
    gbutton select_hover;
    gbutton select_label;

    GtkWidget *payment_fixed;
    GtkWidget *payment_background;
    gbutton payment_hover_left;
    gbutton payment_hover_right;
} Widget;

typedef struct _ParkingData {
    GtkWidget *image;
    GtkWidget *timeLabel;
    GtkWidget *parkNumLabel;

    ParkingStatus parkingStatus;
    time_t deadline;
    gint parkNum;
} ParkingData;

Widget widget;

ParkingData parkingData[8];

pthread_t gtkThread;

int progress;
int presstime;
int lastStatus;

GdkPixbuf *buf;

gboolean settime(gpointer);

gint findMaxArrayIndex(guint16[], gint);

void refreshLoadingBerFrame(GtkWidget *, int, int);

gboolean progressLoadingBar(gpointer);

void loadingCallback(GtkWidget*);

void* run(void*);

void startani(GtkWidget *);

void updateParkingData();

gboolean counter(gpointer);

void showDeadline(ParkingData);

gboolean courseAnimation(gpointer);

void hoverAnimation(gbutton*, int);

gboolean selectTimeAnimation(gpointer);

void selectHoverAnimation(GtkWidget *, int, int);

void selectHoverOpacityAnimation(gbutton *, int );

gboolean paymentAnimation(gpointer);
#endif