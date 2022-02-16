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
    g_object_unref(pixbuf);
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
        printf("Loading Done!\n");
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
    lastStatus = 12;
    progress = 1;

    Widget *widget = (Widget*)(data);

    gtk_init(NULL, NULL);
    






    // GTK_WINDOW_POPUP         show on the top screen without windows
    // GTK_WINDOW_TOPLEVEL      have windows
    home = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_fullscreen(GTK_WINDOW(home));

    widget->home_fixed = gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(home),widget->home_fixed);

    widget->home_background = gtk_image_new_from_file("image/1.png");
	gtk_fixed_put(GTK_FIXED(widget->home_fixed), widget->home_background, 0, 0);

    widget->hoverAnimation.image = gtk_image_new_from_file("image/hover.png");
    gtk_fixed_put(GTK_FIXED(widget->home_fixed), widget->hoverAnimation.image, 0, 0);

    for(int i = 0; i < 8; i++) {
        parkingData[i].image = gtk_image_new_from_file("image/deadline.png");
        gtk_fixed_put(GTK_FIXED(widget->home_fixed), parkingData[i].image
                , (i/4) * 600 + 240, (i%4) * 270 + 60);

        parkingData[i].timeLabel = gtk_label_new(NULL);
        gtk_label_set_markup(GTK_LABEL(parkingData[i].timeLabel)
                , "<span font_desc='55' color='#DE9C18'>00 : 00</span>");
        gtk_fixed_put(GTK_FIXED(widget->home_fixed), parkingData[i].timeLabel
                , (i/4) * 600 + 257, (i%4) * 270 + 155);

        parkingData[i].parkNumLabel = gtk_label_new(NULL);
        gchar *text_time = g_strdup_printf(\
        "<span font_desc='100' color='#16D2BA'>%02d</span>", i);
        gtk_label_set_markup(GTK_LABEL(parkingData[i].parkNumLabel), text_time);
        gtk_fixed_put(GTK_FIXED(widget->home_fixed), parkingData[i].parkNumLabel
                , (i/4) * 600 + 57, (i%4) * 270 + 29);
    }

    updateParkingData();

    widget->selectbutton.image = gtk_image_new_from_file("image/select.png");
    gtk_fixed_put(GTK_FIXED(widget->home_fixed), widget->selectbutton.image, 0, 0);    

    widget->mask = gtk_image_new_from_file("image/loading_mask.png");
	gtk_fixed_put(GTK_FIXED(widget->home_fixed), widget->mask, 0, 0);

    widget->loading_bar = gtk_image_new_from_file("image/loading_bar.png");
    gtk_fixed_put(GTK_FIXED(widget->home_fixed), widget->loading_bar, 143, 1205);

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






    selectTimewindwos = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_fullscreen(GTK_WINDOW(selectTimewindwos));

    widget->select_fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(selectTimewindwos),widget->select_fixed);

    widget->select_background = gtk_image_new_from_file("image/2.png");
    gtk_fixed_put(GTK_FIXED(widget->select_fixed), widget->select_background, 0, 0);

    widget->select_hover.image = gtk_image_new_from_file("image/select_time_hover.png");
    gtk_fixed_put(GTK_FIXED(widget->select_fixed), widget->select_hover.image, 15, 800);
    buf = gdk_pixbuf_new_from_file("/home/root/display_MO/image/select_time_hover.png", NULL);
    gtk_widget_set_opacity(widget->select_hover.image, 0);

    widget->select_timer.image = gtk_image_new_from_file("image/select_time.png");
    gtk_fixed_put(GTK_FIXED(widget->select_fixed),  widget->select_timer.image, 15, 800);

    widget->select_label.image = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(widget->select_label.image)
                , "<span font_desc='65' color='#FFFFFF' weight='bold'>00:00</span>");
    gtk_fixed_put(GTK_FIXED(widget->select_fixed), widget->select_label.image, 50, 895);
    widget->select_label.opacity = 0;
    gtk_widget_set_opacity(widget->select_label.image, widget->select_label.opacity);


    // g_timeout_add(5, selectTimeAnimation, NULL);

    // gtk_widget_show_all(selectTimewindwos);  







    paymentWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_fullscreen(GTK_WINDOW(paymentWindow));

    widget->payment_fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(paymentWindow),widget->payment_fixed);

    widget->payment_background = gtk_image_new_from_file("image/3.png");
    gtk_fixed_put(GTK_FIXED(widget->payment_fixed), widget->payment_background, 0, 0);

    widget->payment_hover.image = gtk_image_new_from_file("image/select_payment.png");
    gtk_fixed_put(GTK_FIXED(widget->payment_fixed), widget->payment_hover.image,0, 695);
    paymentbuf = gdk_pixbuf_new_from_file("/home/root/display_MO/image/select_payment.png", NULL);

    widget->payment_qrcode.image = gtk_image_new_from_file("image/payment_qrcode.png");
    gtk_fixed_put(GTK_FIXED(widget->payment_fixed), widget->payment_qrcode.image,144, 734);
    gtk_widget_set_opacity(widget->payment_qrcode.image, widget->payment_qrcode.opacity);
    widget->payment_qrcode.opacity = 0;

    widget->payment_card.image = gtk_image_new_from_file("image/payment_card.png");
    gtk_fixed_put(GTK_FIXED(widget->payment_fixed), widget->payment_card.image, 827,739);
    widget->payment_card.opacity = 0;
    gtk_widget_set_opacity(widget->payment_card.image, widget->payment_card.opacity);

    // g_timeout_add(25, paymentAnimation, NULL);
    // gtk_widget_show_all(paymentWindow);  

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
            gtk_image_set_from_file(GTK_IMAGE(parkingData[i].image)
                        , "image/deadline.png");
            gtk_widget_show(parkingData[i].image);
            showDeadline(parkingData[i]);
            gtk_widget_show(parkingData[i].timeLabel);
            break;

        case PARKING_STATUS_EXPIRED:
            gtk_image_set_from_file(GTK_IMAGE(parkingData[i].image)
                        , "image/expired.png");
            gtk_widget_show(parkingData[i].image);
            gtk_widget_hide(parkingData[i].timeLabel);
            break;

        case PARKING_STATUS_PAYMENT:
            gtk_image_set_from_file(GTK_IMAGE(parkingData[i].image)
                        , "image/payment.png");
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
            refreshLoadingBerFrame(widget.hoverAnimation.image
                    , (int)(568 * (float)presstime/80), 40);
            
        }
            
        else {
            presstime = 1;
            printf("Choossing block[%d]\n", status);
            gtk_fixed_move(GTK_FIXED(home_fixed), widget.selectbutton.image
                        , selectBlockX, selectBlockY);

            gtk_fixed_move(GTK_FIXED(home_fixed), widget.hoverAnimation.image
                        , selectBlockX, selectBlockY);
        }
    }

    if (presstime > 80) {
        status = -2;
        gtk_widget_hide(home);
        gtk_widget_show_all(selectTimewindwos);
        g_timeout_add(5, selectTimeAnimation, NULL);
        lastStatus = 12; //防止下一頁位置錯誤
        presstime = 0;
        printf("Go to page 2\n");
        return FALSE;
    }

    hoverAnimation(&widget.selectbutton, status);
    hoverAnimation(&widget.hoverAnimation, status);
    // printf("status [%d]\n", status);
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

gboolean selectTimeAnimation(gpointer data) {
    gint maxIndex = findMaxArrayIndex(block, 24);
    int status = 0;
    int selectBlockX;
    int selectBlockY;
    
    if (SELECT_BLOCK(block[maxIndex])) {
        status = maxIndex;
        if (status < 12 || status > 19)
            presstime = 0;
        else {
            presstime++;
        }
    }
    else {
        status = -1;
        presstime = 0;
    }

    selectBlockX = 15 + (296 * (status%4));
    selectBlockY = 800 + (315 * ((status-12)/4));
    
    if (status > 11 && status < 20) {

        if (status == lastStatus)
        {
            presstime++;
            selectHoverAnimation(widget.select_hover.image, 310*presstime/500, 330);
        }
        else {
            presstime = 0;
            printf("\nChoossing block[%d]\nX[%d]\ty[%d]", status, selectBlockX, selectBlockY);
            gtk_fixed_move(GTK_FIXED(widget.select_fixed), widget.select_timer.image
                        , selectBlockX, selectBlockY);

            gtk_fixed_move(GTK_FIXED(widget.select_fixed), widget.select_hover.image
                        , selectBlockX-14, selectBlockY-14);

            gtk_fixed_move(GTK_FIXED(widget.select_fixed), widget.select_label.image
                        , selectBlockX+50, selectBlockY+95);

            gchar *text_time = g_strdup_printf(\
                "<span font_desc='65' color='#FFFFFF' weight='bold'>%d:%02d</span>"
                , ((status+1)/2)-6, ((status+1)%2)*30);

            gtk_label_set_markup(GTK_LABEL(widget.select_label.image), text_time);
        }
    }
    
    if(presstime > 500) {
        presstime = 0;
        widget.select_label.opacity = 0;
        widget.select_hover.opacity = 0;

        gtk_widget_hide(selectTimewindwos);
        gtk_widget_show_all(paymentWindow);  
        g_timeout_add(25, paymentAnimation, NULL);
        
        printf("Go to page 3\n");
        return FALSE;
    }

    selectHoverOpacityAnimation(&widget.select_hover , status);
    selectHoverOpacityAnimation(&widget.select_label , status);
    lastStatus = status;

    return TRUE;
}

void selectHoverAnimation(GtkWidget * select, int weight ,int height) {
    GdkPixbuf *pixbuf = gdk_pixbuf_scale_simple(buf, weight, height, 
                GDK_INTERP_NEAREST);

    gtk_image_set_from_pixbuf(GTK_IMAGE(select), pixbuf);
    g_object_unref(pixbuf);
    
}

void selectHoverOpacityAnimation(gbutton *opacityWidget, int status) {
    if(status > 11 && status < 20 && opacityWidget->opacity < 1) {
        opacityWidget->opacity += 0.005;
        gtk_widget_set_opacity(opacityWidget->image, opacityWidget->opacity);
    }
    else if((status < 12 || status > 19) && opacityWidget->opacity > 0) {
        opacityWidget->opacity -= 0.05;
        gtk_widget_set_opacity(opacityWidget->image, opacityWidget->opacity);
    }
    // printf("Opacity: %f\n", opacityWidget->opacity);
}

gboolean paymentAnimation(gpointer data) {
    gint maxIndex = findMaxArrayIndex(block, 24);
    int status = 0;
    
    if (SELECT_BLOCK(block[maxIndex])) {
        status = maxIndex;
        if (status < 12 || status > 19)
            presstime = 0;
        else {
            presstime++;
        }
    }
    else {
        status = -1;
        presstime = 0;
    }

    if (status != -1 && status%4 < 2 && status != lastStatus) {
        gtk_fixed_move(GTK_FIXED(widget.payment_fixed), widget.payment_hover.image
                        , 0, 695);
    }else if(status != -1 && status%4 > 1 && status != lastStatus) {
        gtk_fixed_move(GTK_FIXED(widget.payment_fixed), widget.payment_hover.image
                        , 600, 695);
    }

    
    if(presstime == 40 || status != lastStatus) {
        paymentHoverAnimation(widget.payment_hover.image, 1,515);
        presstime = 0;
    }else if (presstime != 0 && presstime != 40)
    {
        paymentHoverAnimation(widget.payment_hover.image, 600*presstime/40, 515);
        
    }
    paymentOpacityAnimation(&widget.payment_qrcode, &widget.payment_card, status);

    lastStatus = status;  
    
    return TRUE;
}

void paymentHoverAnimation(GtkWidget * select, int weight ,int height) {
    GdkPixbuf *pixbuf = gdk_pixbuf_scale_simple(paymentbuf, weight, height, 
                GDK_INTERP_NEAREST);

    gtk_image_set_from_pixbuf(GTK_IMAGE(select), pixbuf);
    g_object_unref(pixbuf);
    
}

void paymentOpacityAnimation(gbutton *opacityWidgetA, gbutton *opacityWidgetB, int status) {
    if( status!=-1 && status%4 < 2 && opacityWidgetA->opacity < 1) {
        opacityWidgetA->opacity += 0.03;
        gtk_widget_set_opacity(opacityWidgetA->image, opacityWidgetA->opacity);
    }
    else if((!(status%4 < 2) || status == -1) && opacityWidgetA->opacity > 0) {
        opacityWidgetA->opacity -= 0.05;
        gtk_widget_set_opacity(opacityWidgetA->image, opacityWidgetA->opacity);
    }

    if(status!=-1 && status%4 > 1 && opacityWidgetB->opacity < 1) {
        opacityWidgetB->opacity += 0.03;
        gtk_widget_set_opacity(opacityWidgetB->image, opacityWidgetB->opacity);
    }
    else if((!(status%4 > 1) || status == -1) && opacityWidgetB->opacity > 0) {
        opacityWidgetB->opacity -= 0.05;
        gtk_widget_set_opacity(opacityWidgetB->image, opacityWidgetB->opacity);
    }
}