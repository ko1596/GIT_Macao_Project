if (SELECT_BLOCK(block[maxIndex])) {
        if (maxIndex > 11 && maxIndex < 20)
            status = maxIndex;
    }

    if (status != lastStatus){
        if(status >11 && status <16) {
            gtk_fixed_move(GTK_FIXED(widget.select_fixed), widget.select_time, 2, 784);
            gtk_widget_hide(widget.select_time2);
        }  
        else{
            gtk_fixed_move(GTK_FIXED(widget.select_fixed), widget.select_time, 2, 1110);
            gtk_widget_show(widget.select_time2);
        }

        if (status >11 && status <20 ) {
            gchar *text_time = g_strdup_printf(\
                "<span font_desc='65' color='#FFFFFF' weight='bold'>%02d: %02d</span>", ((status+1)/2)-6, ((status+1)%2)*30);
            gtk_label_set_markup(GTK_LABEL(widget.select_label), text_time);
            gtk_fixed_move(GTK_FIXED(widget.select_fixed), widget.select_label
                            , select_time_weight-265, 890 + ((status-12)/4)*316);
        }
        
        presstime = 0;
    }

    goal_dist = (int)(1192*(float) (((status-12)%4)+1)/4);

        

    if (goal_dist - select_time_weight > 100) 
        select_time_weight = goal_dist - 100;
    else if (goal_dist - select_time_weight < -100) 
        select_time_weight = goal_dist + 100;

    // printf("select_time_weight[%d]\tgoal_dist[%d]\n", select_time_weight, goal_dist);

    if(select_time_weight > 0 && select_time_weight < goal_dist-10) {
        select_time_weight+=5;
        selectHoverAnimation(widget.select_time, select_time_weight, 330);
    }else if (select_time_weight > goal_dist && select_time_weight < 1192 ) {
        select_time_weight-=5;
        selectHoverAnimation(widget.select_time, select_time_weight, 330);
    }

    
    presstime++;

    if(presstime > 1500) {
        gtk_widget_hide(selectTimewindwos);
        presstime = 0;
        lastStatus = 12;
        select_time_weight = 0;
        gtk_widget_show(home);
        updateParkingData();
        g_timeout_add(16, courseAnimation, widget.home_fixed);

        
        return FALSE;
    }

    // printf("presstime [%d]\n", presstime);

    lastStatus = status;