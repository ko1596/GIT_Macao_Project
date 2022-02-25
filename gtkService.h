#ifndef GTKSERVICE_H
#define GTKSERVICE_H

#include "serialService.h"
#include <gtk/gtk.h>
#include <time.h>

#define M_PI 3.141592653589793

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

typedef struct _gbutton {
    GtkWidget *image;
    double opacity;
} gbutton;

typedef struct _ParkingData {
    GtkWidget *image;
    GtkWidget *timeLabel;
    GtkWidget *parkNumLabel;

    ParkingStatus parkingStatus;
    time_t deadline;
    gint parkNum;
} ParkingData;

typedef struct _SelectData {
    gint selectBlockNum;
    gint selectTimeHour;
    gint selectTimeMinute;
    gint selectPayment;
} SelectData;


pthread_t gtkThread;

int changedPayment;
int paySuccess;


cairo_surface_t *spinnerImage;

GdkPixbuf *buf;
GdkPixbuf *paymentbuf;

gint findMaxArrayIndex(guint16[], gint);

void refreshLoadingBerFrame(GtkWidget *, int, int);

gboolean progressLoadingBar(gpointer);

void loadingCallback(GtkWidget*);

void* run(void*);

void startani();

void updateParkingData();

gboolean counter(gpointer);

void showDeadline(ParkingData*);

gboolean courseAnimation(gpointer);

void homeAnimation(gbutton*, int);

gboolean selectTimeAnimation(gpointer);

void selectHoverAnimation(GtkWidget *, int, int);

void selectHoverOpacityAnimation(gbutton *, int );

gboolean paymentAnimation(gpointer);

void paymentHoverAnimation(GtkWidget *, int , int);

void paymentOpacityAnimation(gbutton *,gbutton *, int);

gboolean confirmAnimation(gpointer);

void confirmOpacityAnimation(gbutton *, int);

gboolean spinnerAnimation(gpointer);

gboolean spinnerStart(gpointer);

#endif