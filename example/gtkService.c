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

gboolean showPage(gpointer data) {
    gint selectBlockX, selectBlockY;
    gint maxIndex;

    last_status = status;
    maxIndex = findMaxArrayIndex(block, 24);

    gchar *text_markup = g_strdup_printf("<span font_desc='120' color='#000000'>%.1f</span>", parkingTime);

    gtk_label_set_markup(GTK_LABEL(ParkingTimeLabel), text_markup);

    if (changeBackground){
        gtk_widget_hide(frame);
        gtk_widget_hide(frame2);

        if(page == 1) { 
            gtk_widget_show(frame);
        }else if(page == 2) {
            gtk_widget_show(frame2);

        }

        
        changeBackground = 0;
    }
    
    if (SELECT_BLOCK(block[maxIndex]))
    {
        selectBlockCount++;
        if(selectBlockCount == 80) {
            // setPage(2);
            if(page == 2){
                if(status == 0){
                    if(parkingTime > 0)
                        parkingTime -= 0.5;
                    printf("m\n");
                }else if(status == 1){
                     parkingTime += 0.5;
                     printf("a\n");
                }
            }
        }

        if(page == 1){
            if(maxIndex < 16){
                selectBlockX = ((maxIndex/2) % 2) * 600 + 20;
                selectBlockY = ((maxIndex/2) / 2) * 270 + 30;
                status = maxIndex;
                if(selectButtonOpacity<1) {
                    selectButtonOpacity += 0.08;
                    gtk_widget_set_opacity(SelectBlockImage, selectButtonOpacity);
                }
            }else if(maxIndex == 21){
                status = 16;
                if(leftButtonOpacity<1) {
                    leftButtonOpacity += 0.08;
                    gtk_widget_set_opacity(leftChangeImage, leftButtonOpacity);
                }
            }else if(maxIndex == 22){
                status = 17;
                if(rightButtonOpacity<1) {
                    rightButtonOpacity += 0.08;
                    gtk_widget_set_opacity(rightChangeImage, rightButtonOpacity);
                }
            }
        }else if(page == 2) { 
            
            if(maxIndex == 10){
                status = 0;
                if(reduceOpacity<1) {
                    reduceOpacity += 0.08;
                    gtk_widget_set_opacity(reduceImage, reduceOpacity);
                }
            }else if(maxIndex == 11){
                status = 1;
                if(addOpacity<1) {
                    addOpacity += 0.08;
                    gtk_widget_set_opacity(addImage, addOpacity);
                }
            }
        }
    }else status = 999;

    if(page == 1) { 
        if(selectButtonOpacity>0 && status > 15) {
            selectButtonOpacity -= 0.08;
            gtk_widget_set_opacity(SelectBlockImage, selectButtonOpacity);
        }else if(selectButtonOpacity == 0) {
            status = 999;
            selectButtonOpacity = -1.0;
            gtk_widget_hide(SelectBlockImage);
        }

        if(leftButtonOpacity>0 && status != 16) { 
            leftButtonOpacity -= 0.08;
            gtk_widget_set_opacity(leftChangeImage, leftButtonOpacity);
        }else if(leftButtonOpacity == 0) {
            status = 999;
            leftButtonOpacity = -1.0;
            gtk_widget_hide(leftChangeImage);
        }

        if(rightButtonOpacity>0 && status != 17) { 
            rightButtonOpacity -= 0.08;
            gtk_widget_set_opacity(rightChangeImage, rightButtonOpacity);
        }else if(rightButtonOpacity == 0) {
            status = 999;
            rightButtonOpacity = -1.0;
            gtk_widget_hide(rightChangeImage);
        }
    }else if(page == 2) { 
        if(reduceOpacity>0 && status != 0) {
            reduceOpacity -= 0.08;
            gtk_widget_set_opacity(reduceImage, reduceOpacity);
        }else if(reduceOpacity == 0) {
            status = 999;
            reduceOpacity = -1.0;
            gtk_widget_hide(reduceImage);
        }

        if(addOpacity>0 && status != 1) {
            addOpacity -= 0.08;
            gtk_widget_set_opacity(addImage, selectButtonOpacity);
        }else if(addOpacity == 0) {
            status = 999;
            addOpacity = -1.0;
            gtk_widget_hide(addImage);
        }
    }
    
            
    if (status != last_status)
    {   
        selectBlockCount = 0;
        printf("status[%d] last_status[%d]\n", status, last_status);
        if(page == 1){
            if(status >=0 && status < 15) {
                selectButtonOpacity = 0.0;
                gtk_widget_show(SelectBlockImage);
                
                // gtk_image_set_from_file(GTK_IMAGE(SelectBlockImage), "image/select_parking_space_frame.png");
                gtk_fixed_move(GTK_FIXED(fixed), SelectBlockImage, selectBlockX, selectBlockY);
            }else if (status == 16) { 
                leftButtonOpacity = 0;
                gtk_widget_show(leftChangeImage);
            }else if (status == 17) {
                rightButtonOpacity = 0;
                gtk_widget_show(rightChangeImage);
                
            }
        }else if(page == 2) { 
            if(status == 0){
                reduceOpacity = 0;
                gtk_widget_show(reduceImage);
            }else if(status == 1){
                addOpacity = 0;
                gtk_widget_show(addImage);
            }
        }
        
    }

    

    return TRUE;
}

void* run(void* data) { 
    selectBlockCount = 0;
    selectButtonOpacity = 0.0;
    leftButtonOpacity = 0.0;
    rightButtonOpacity = 0.0;
    changeBackground = 0;
    addOpacity = 0;
    reduceOpacity = 0;
    page = 1;
    parkingTime = 0.0;

    pthread_create(&serialThread, NULL, UartLoop, NULL);

    gtk_init(NULL, NULL);

    // GTK_WINDOW_POPUP         show on the top screen without windows
    // GTK_WINDOW_TOPLEVEL      have windows
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_fullscreen(GTK_WINDOW(window));

    vbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    frame = gtk_frame_new(NULL);
    gtk_frame_set_shadow_type(GTK_FRAME(frame), GTK_SHADOW_NONE);

    frame2 = gtk_frame_new(NULL);
    gtk_frame_set_shadow_type(GTK_FRAME(frame2), GTK_SHADOW_NONE);

    fixed = gtk_fixed_new();
    gtk_widget_set_has_window(fixed, TRUE);

    fixed2 = gtk_fixed_new();
    gtk_widget_set_has_window(fixed2, TRUE);

    gtk_container_add(GTK_CONTAINER(frame), fixed);
    gtk_container_add(GTK_CONTAINER(frame2), fixed2);
    gtk_box_pack_start(GTK_BOX(vbox), frame, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), frame2, TRUE, TRUE, 0);

    background = gtk_image_new_from_file("image/1.png");
    gtk_fixed_put(GTK_FIXED(fixed), background, 0, 0);
    // gtk_fixed_put(GTK_FIXED(fixed2), background, 0, 0);

    background2 = gtk_image_new_from_file("image/2.png");
    gtk_fixed_put(GTK_FIXED(fixed2), background2, 0, 0);


    SelectBlockImage = gtk_image_new_from_file("image/select_parking_space_frame.png");
    gtk_fixed_put(GTK_FIXED(fixed), SelectBlockImage, 100, 100);
    gtk_widget_hide(SelectBlockImage);

    leftChangeImage = gtk_image_new_from_file("image/left_button.png");
    gtk_fixed_put(GTK_FIXED(fixed), leftChangeImage, 472, 1379);
    // gtk_widget_hide(leftChangeImage);

    rightChangeImage = gtk_image_new_from_file("image/right_button.png");
    gtk_fixed_put(GTK_FIXED(fixed), rightChangeImage, 636, 1379);
    // gtk_widget_hide(rightChangeImage);

    Timelabel = gtk_label_new (NULL);
    gtk_fixed_put(GTK_FIXED(fixed), Timelabel, 350, 1500);

    ParkingTimeLabel = gtk_label_new (NULL);
    gtk_fixed_put(GTK_FIXED(fixed2), ParkingTimeLabel, 650, 695);

    addImage = gtk_image_new_from_file("image/increase_selected.png");
    gtk_fixed_put(GTK_FIXED(fixed2), addImage, 897, 755);

    reduceImage = gtk_image_new_from_file("image/decrease_selected.png");
    gtk_fixed_put(GTK_FIXED(fixed2), reduceImage, 536, 755);
    
    gint s = g_timeout_add(16, showPage, NULL);

    gint g = g_timeout_add (1000, settime, (void *)Timelabel);
    
    gtk_widget_show_all(window);
    gtk_widget_hide(frame2);
    gtk_main();
    // g_signal_connect(button01,"pressed",G_CALLBACK(settime),NULL);
    g_signal_new("child-finished",
            G_TYPE_OBJECT, G_SIGNAL_RUN_FIRST,
            0, NULL, NULL,
            g_cclosure_marshal_VOID__BOXED,
            G_TYPE_NONE, 1, GDK_TYPE_EVENT);

    return FALSE;
}