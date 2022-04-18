#ifndef GTKSERVICE_H
#define GTKSERVICE_H

#include "M0Service.h"
#include <gtk/gtk.h>
#include <time.h>

#define IDENT(x) x
#define XSTR(x) #x
#define STR(x) XSTR(x)

#define PATH(k) STR(IDENT(Dir)IDENT(k)IDENT(File))
 
#define Dir /home/root/smart_city/image/    \

#define Dir2 /home/root/grids/disp_patterns/disp_mo/    \

#define File .png

#define M_PI 3.141592653589793

#define SELECT_BUTTON_TIME 30       //SELECT_BUTTON_TIME * 16 ~= 960ms

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

pthread_t gtkThread;

void changePaySuccess(int);

void changeParingStatus(int, int);

gint settingFrameRate(gint);

gint settingHoverTime(gint);

void* run(void*);

#endif