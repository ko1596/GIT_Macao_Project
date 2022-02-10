#include "gtkService.h"

gboolean settime(gpointer data)
{
    time_t times;
    struct tm *p_time;
    time(&times);
    p_time = localtime(&times);

    gchar *text_data = g_strdup_printf(\
        "<span font_desc='45' color='#ffffff' weight='bold'>%04d-%02d-%02d</span>",\
        (1900+p_time->tm_year),(1+p_time->tm_mon),(p_time->tm_mday));

    gchar *text_time = g_strdup_printf(\
    "<span font_desc='45' color='#ffffff' weight='bold'>%02d:%02d</span>",\
    (p_time->tm_hour), (p_time->tm_min));

    gchar *text_markup = g_strdup_printf("\n%s\t%s", text_data, text_time);

    gtk_label_set_markup(GTK_LABEL(data), text_markup);

    return TRUE;
}

gint findMaxArrayIndex(guint16 array[], gint array_size) {
    gint maxIndex = 0;
    guint16 maxValue = 0;
    for (gint i = 0; i < array_size; i++)
        if(array[i] > maxValue && array[i] < 60000)
        {
            maxValue = array[i];
            maxIndex = i;
        }
    return maxIndex;
}

void refreshLoadingBerFrame(GtkWidget *loadingBar, int weight ,int height) {
    GdkPixbuf *pixbuf;
    
    pixbuf = gtk_image_get_pixbuf (GTK_IMAGE(loadingBar));
    pixbuf = gdk_pixbuf_scale_simple(pixbuf, weight, height, 
                GDK_INTERP_NEAREST);

    gtk_image_set_from_pixbuf(GTK_IMAGE(loadingBar), pixbuf);
}

gboolean progressLoadingBar(gpointer data)
{   
    progress++;
    gtk_image_set_from_file(GTK_IMAGE(data),"image/loading_bar.png");
    refreshLoadingBerFrame(GTK_WIDGET(data), progress,45);
    gtk_widget_show(GTK_WIDGET(data));
    gtk_widget_show(GTK_WIDGET(widget.mask));
    if(progress < 922) return TRUE;
    else {
        gtk_widget_hide(GTK_WIDGET(data));
        gtk_widget_hide(GTK_WIDGET(widget.mask));
        g_timeout_add(16, courseAnimation, widget.home_fixed);
        return FALSE;
    }
    
}

void loadingCallback(GtkWidget* loading_bar){
    progress = 10;
    printf("\nLoading\n");
    g_timeout_add(5, progressLoadingBar, loading_bar);
    
}

void* run(void* data) {
    presstime = 0;
    lastStatus = 0;
    Widget *widget = (Widget*)(data);

    gtk_init(NULL, NULL);
    progress = 1;

    // GTK_WINDOW_POPUP         show on the top screen without windows
    // GTK_WINDOW_TOPLEVEL      have windows
    home = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_fullscreen(GTK_WINDOW(home));

    GtkWidget *home_fixed = gtk_fixed_new();
    widget->home_fixed = home_fixed;
	gtk_container_add(GTK_CONTAINER(home),home_fixed);

    widget->home_background = gtk_image_new_from_file("image/1.png");
	gtk_fixed_put(GTK_FIXED(home_fixed), widget->home_background, 0, 0);

    widget->hoverAnimation.image = gtk_image_new_from_file("image/hover.png");
    gtk_fixed_put(GTK_FIXED(home_fixed), widget->hoverAnimation.image, 0, 0);

    for(int i = 0; i < 8; i++) {
        parkingData[i].image = gtk_image_new_from_file("image/deadline.png");
        gtk_fixed_put(GTK_FIXED(home_fixed), parkingData[i].image
                , (i/4) * 600 + 240, (i%4) * 270 + 60);

        parkingData[i].timeLabel = gtk_label_new(NULL);
        gtk_label_set_markup(GTK_LABEL(parkingData[i].timeLabel)
                , "<span font_desc='55' color='#DE9C18'>00 : 00</span>");
        gtk_fixed_put(GTK_FIXED(home_fixed), parkingData[i].timeLabel
                , (i/4) * 600 + 257, (i%4) * 270 + 155);

        parkingData[i].parkNumLabel = gtk_label_new(NULL);
        gchar *text_time = g_strdup_printf(\
        "<span font_desc='100' color='#16D2BA'>%02d</span>", i);
        gtk_label_set_markup(GTK_LABEL(parkingData[i].parkNumLabel), text_time);
        gtk_fixed_put(GTK_FIXED(home_fixed), parkingData[i].parkNumLabel
                , (i/4) * 600 + 57, (i%4) * 270 + 29);
    }

    updateParkingData();

    widget->selectbutton.image = gtk_image_new_from_file("image/select.png");
    gtk_fixed_put(GTK_FIXED(home_fixed), widget->selectbutton.image, 0, 0);

    
    

    widget->mask = gtk_image_new_from_file("image/loading_mask.png");
	gtk_fixed_put(GTK_FIXED(home_fixed), widget->mask, 0, 0);

    widget->loading_bar = gtk_image_new_from_file("image/loading_bar.png");
    gtk_fixed_put(GTK_FIXED(home_fixed), widget->loading_bar, 143, 1205);

    g_signal_new("loading",
             G_TYPE_OBJECT, G_SIGNAL_RUN_FIRST,
             0, NULL, NULL,
             g_cclosure_marshal_VOID__POINTER,
             G_TYPE_NONE, 1, G_TYPE_POINTER);

    g_signal_connect(G_OBJECT(widget->loading_bar)
                , "loading", G_CALLBACK(loadingCallback)
                , NULL);

    g_timeout_add(60000, counter, NULL);
    
    g_signal_emit_by_name(GTK_WIDGET(widget->loading_bar), "loading");

    gtk_widget_show_all(home);


    updateParkingData();


    widget->selectbutton.opacity = 0;
    gtk_widget_set_opacity(widget->selectbutton.image
                        , widget->selectbutton.opacity);
                        
    widget->hoverAnimation.opacity = 0;
    gtk_widget_set_opacity(widget->hoverAnimation.image
                        , widget->hoverAnimation.opacity);


    gtk_main();

    return (int*) data;
}


void startani(GtkWidget *loading_bar) {
    g_signal_emit_by_name(GTK_WIDGET(loading_bar), "loading");
}

gboolean counter(gpointer data) {
    updateParkingData();
    return TRUE;
}

void updateParkingData() {
    for (int i = 0; i < 8; i++) {
        switch (parkingData[i].parkingStatus)
        {
        case PARKING_STATUS_EMPTY:
            gtk_widget_hide(parkingData[i].image);
            gtk_widget_hide(parkingData[i].timeLabel);
            break;

        case PARKING_STATUS_DEADLINE:
            gtk_image_set_from_file(GTK_IMAGE(parkingData[i].image), "image/deadline.png");
            gtk_widget_show(parkingData[i].image);
            showDeadline(parkingData[i]);
            gtk_widget_show(parkingData[i].timeLabel);
            break;

        case PARKING_STATUS_EXPIRED:
            gtk_image_set_from_file(GTK_IMAGE(parkingData[i].image), "image/expired.png");
            gtk_widget_show(parkingData[i].image);
            gtk_widget_hide(parkingData[i].timeLabel);
            break;

        case PARKING_STATUS_PAYMENT:
            gtk_image_set_from_file(GTK_IMAGE(parkingData[i].image), "image/payment.png");
            gtk_widget_show(parkingData[i].image);
            gtk_widget_hide(parkingData[i].timeLabel);
            break;

        default:
            break;
        }
    }
}

void showDeadline(ParkingData data) {
    int day,hour,minute;
    double elapsed_time; 
    time_t start = time(NULL);
    elapsed_time = difftime( data.deadline, start );

    day = (int)(elapsed_time/60/60/24); 
    hour = (int)(elapsed_time/60/60-24*day); 
    minute = (int)(elapsed_time/60-60*hour-60*24*day);

    gchar *text_time = g_strdup_printf(\
        "<span font_desc='55' color='#DE9C18'>%02d : %02d</span>", hour, minute);
    gtk_label_set_markup(GTK_LABEL(data.timeLabel), text_time);
}

gboolean courseAnimation(gpointer home_fixed) {
    
    gint maxIndex = findMaxArrayIndex(block, 24);
    int status = 0;
    int selectBlockX = ((maxIndex/2) % 2) * 600 + 20;
    int selectBlockY = ((maxIndex/2) / 2) * 270 + 30;

    if (SELECT_BLOCK(block[maxIndex])) {
        status = maxIndex/2;
    }else {
        status = -1;
    }


    if(status > -1 && status < 8) {
        if (status == lastStatus)
        {
            presstime++;
            refreshLoadingBerFrame(widget.hoverAnimation.image, (int)(568 * (float)presstime/80), 239);
        }
            
        else {
            presstime = 1;
            gtk_fixed_move(GTK_FIXED(home_fixed), widget.selectbutton.image
                        , selectBlockX, selectBlockY);

            gtk_fixed_move(GTK_FIXED(home_fixed), widget.hoverAnimation.image
                        , selectBlockX, selectBlockY);
        }
    }

    if (presstime > 80) {
        status = -2;
        return FALSE;
    }

    hoverAnimation(&widget.selectbutton, status);
    hoverAnimation(&widget.hoverAnimation, status);
    printf("status [%d]\n", status);
    lastStatus = status;

    return TRUE;
}

void hoverAnimation(gbutton *opacityWidget, int status) {
    if(status > -1 && status < 8 && opacityWidget->opacity < 1) {
        opacityWidget->opacity += 0.05;
        gtk_widget_set_opacity(opacityWidget->image, opacityWidget->opacity);
    }
    else if((status < 0 || status > 7) && opacityWidget->opacity > 0) {
        opacityWidget->opacity -= 0.05;
        gtk_widget_set_opacity(opacityWidget->image, opacityWidget->opacity);
    }
    // printf("Opacity: %f\n", opacityWidget->opacity);
}