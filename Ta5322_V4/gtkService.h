#ifndef GTKSERVICE_H
#define GTKSERVICE_H

#include "serialService.h"
#include <gtk/gtk.h>
#include <time.h>

#define M_PI 3.141592653589793

#define SELECT_BLOCK(x) ((x < 50000) && (x > 300))

#define SELECT_BUTTON_TIME 45       //60 * 16 ~= 960ms

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



void changePaySuccess(int);

void changeParingStatus(int, int);

void* run(void*);

gboolean spinnerAnimation(gpointer);
#endif