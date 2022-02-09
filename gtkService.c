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

void refreshLoadingBerFrame(GtkWidget *loadingBar) {
    GdkPixbuf *pixbuf;
    gtk_image_set_from_file(GTK_IMAGE(loadingBar),"image/loading_bar.png");
    pixbuf = gtk_image_get_pixbuf (GTK_IMAGE(loadingBar));
    pixbuf = gdk_pixbuf_scale_simple(pixbuf, progress, 45, 
                GDK_INTERP_NEAREST);

    gtk_image_set_from_pixbuf(GTK_IMAGE(loadingBar), pixbuf);
}

gboolean progressLoadingBar(gpointer data)
{   
    progress++;
    refreshLoadingBerFrame(GTK_WIDGET(data));
    gtk_widget_show(GTK_WIDGET(data));
    gtk_widget_show(GTK_WIDGET(widget.mask));
    if(progress < 922) return TRUE;
    else {
        gtk_widget_hide(GTK_WIDGET(data));
        gtk_widget_hide(GTK_WIDGET(widget.mask));
        return FALSE;
    }
    
}

void loadingCallback(GtkWidget* loading_bar){
    progress = 10;
    printf("\nLoading\n");
    g_timeout_add(5, progressLoadingBar, loading_bar);
    
}

void* run(void* data) {


    Widget *widget = (Widget*)(data);

    

    gtk_init(NULL, NULL);
    start = 0;
    progress = 1;

    // GTK_WINDOW_POPUP         show on the top screen without windows
    // GTK_WINDOW_TOPLEVEL      have windows
    home = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_fullscreen(GTK_WINDOW(home));

    GtkWidget *home_fixed = gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(home),home_fixed);

    widget->home_background = gtk_image_new_from_file("image/1.png");
	gtk_fixed_put(GTK_FIXED(home_fixed), widget->home_background, 0, 0);

    widget->mask = gtk_image_new_from_file("image/loading_mask.png");
	gtk_fixed_put(GTK_FIXED(home_fixed), widget->mask, 0, 0);

    widget->loading_bar = gtk_image_new_from_file("image/loading_bar.png");
    gtk_fixed_put(GTK_FIXED(home_fixed), widget->loading_bar, 143, 1205);

    g_signal_new("loading",
             G_TYPE_OBJECT, G_SIGNAL_RUN_FIRST,
             0, NULL, NULL,
             g_cclosure_marshal_VOID__POINTER,
             G_TYPE_NONE, 1, G_TYPE_POINTER);

    g_signal_connect(G_OBJECT(widget->loading_bar), "loading", G_CALLBACK(loadingCallback), NULL);

    gtk_widget_show_all(home);
    gtk_main();

    return (int*) data;
}


void startani(GtkWidget *loading_bar) {
    g_signal_emit_by_name(GTK_WIDGET(loading_bar), "loading");
}


