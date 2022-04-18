#include "gtkService.h"

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

static GtkWidget *home;
static GtkWidget *home_fixed;
static GtkWidget *home_background;
static GtkWidget *mask;
static GtkWidget *loading_bar;
static GtkWidget *selectbutton;
static GtkWidget *hoverAnimation;
static GtkWidget *home_clock_label;

static GtkWidget *selectTimewindwos;
static GtkWidget *select_fixed;
static GtkWidget *select_background;
static GtkWidget *select_timer;
static GtkWidget *select_hover;
static GtkWidget *select_label;
static GtkWidget *select_parking_space_label;
static GtkWidget *select_back_btn;
static GtkWidget *select_clock_label;

static GtkWidget *paymentWindow;
static GtkWidget *payment_fixed;
static GtkWidget *payment_background;
static GtkWidget *payment_hover;
static GtkWidget *payment_card;
static GtkWidget *payment_qrcode;
static GtkWidget *payment_parking_space_label;
static GtkWidget *payment_parking_time_label;
static GtkWidget *payment_back_btn;
static GtkWidget *payment_clock_label;

static GtkWidget *confirmWindow;
static GtkWidget *confirm_fixed;
static GtkWidget *confirm_background;
static GtkWidget *confirm_pay_label;
static GtkWidget *confirm_park_label;
static GtkWidget *confirm_time_label;
static GtkWidget *confirm_clock_label;
static GtkWidget *confirm_home_button;

static GtkWidget *connectionWindows;
static GtkWidget *connection_fixed;
static GtkWidget *connection_background;

static ParkingData parkingData[8];
static SelectData selectData;

static GdkPixbuf *home_loading_bar_buffer;
static GdkPixbuf *home_hover_buffer;
static GdkPixbuf *select_hover_buffer;
static GdkPixbuf *payment_hover_buffer;

static cairo_surface_t *spinnerImage;

static gint frame_rate;
static gint press_time;

static int paySuccess;

static gint loaded = 0;

static void changePage(int page);

void changePaySuccess(int status) {
    paySuccess = status;
}

static void initBlockData() {
    struct tm *p;
    parkingData[0].parkingStatus = 1;
    parkingData[1].parkingStatus = 2;
    parkingData[2].parkingStatus = 3;
    parkingData[3].parkingStatus = 3;
    parkingData[4].parkingStatus = 3;
    parkingData[5].parkingStatus = 3;
    parkingData[6].parkingStatus = 3;
    parkingData[7].parkingStatus = 3;

    parkingData[0].parkNum = 21;
    parkingData[1].parkNum = 22;
    parkingData[2].parkNum = 23;
    parkingData[3].parkNum = 24;
    parkingData[4].parkNum = 25;
    parkingData[5].parkNum = 26;
    parkingData[6].parkNum = 27;
    parkingData[7].parkNum = 28;

    parkingData[0].deadline = time(NULL);
    p = localtime(&parkingData[0].deadline);
    p->tm_hour+=4;
    p->tm_min+=13;
    parkingData[0].deadline = mktime(p);
}
static gboolean resetParkingData(gpointer data) {
    initBlockData();
    return GPOINTER_TO_INT(data);
}


void changeParingStatus(int blockNum, int status) {
    parkingData[blockNum].parkingStatus = status;
}

gint settingFrameRate(gint _frame_rate) {
    if (_frame_rate == 0) {
        printf("_frame_rate is NULL!\nPlease follow the arguments input rules\nex:[./diplay_MO_test [Frame rate] [Press time]\n");
        return -1;
    }
    else frame_rate = 1000/_frame_rate;
    return 0;
}

gint settingHoverTime(gint _press_time) {
    if (_press_time == 0) {
        printf("_press_time is NULL!\nPlease follow the arguments input rules\nex:[./diplay_MO_test [Frame rate] [Press time]\n");
        return -1;
    }
    else press_time = _press_time/frame_rate;
    return 0;
}

static void 
rescaleImage(GtkWidget *widget, 
        GdkPixbuf *buffer, 
        int width, 
        int height) 
{
    GdkPixbuf *pixbuf = gdk_pixbuf_scale_simple(
                                    buffer, 
                                    width, 
                                    height,
                                    GDK_INTERP_NEAREST);

    gtk_image_set_from_pixbuf(GTK_IMAGE(widget), pixbuf);
    g_object_unref(pixbuf); 
}

static gboolean progressLoadingBar(gpointer data)
{
    static int progress;
    progress++;
    gtk_image_set_from_file(GTK_IMAGE(data), PATH(loading_bar));
    rescaleImage(GTK_WIDGET(data), home_loading_bar_buffer, progress, 45);
    gtk_widget_show(GTK_WIDGET(data));
    gtk_widget_show(GTK_WIDGET(mask));
    if (progress < 922)
        return TRUE;
    else
    {
        progress = 0;
        gtk_widget_hide(GTK_WIDGET(data));
        gtk_widget_hide(GTK_WIDGET(mask));
        changePage(1);
        printf("Loading Done!\n");
        return FALSE;
    }
}

static void opacityAnimation(GtkWidget *widget, gboolean hover) {
    if (hover && gtk_widget_get_opacity(widget) < 1)
    {
        gtk_widget_set_opacity(widget, gtk_widget_get_opacity(widget) + 0.05);
    }
    else if (!hover && gtk_widget_get_opacity(widget) > 0)
    {
        gtk_widget_set_opacity(widget, gtk_widget_get_opacity(widget) - 0.05);
    }
}

static void cleanOpacity(GtkWidget *widget) {
    gtk_widget_set_opacity(widget, 0.0);
}

static gint getSelectBlock(){
    static int index=-1;
    if (M0_Status_Update & M0_DEV_UPDATE_ALPS){
        index =  3 - M0_alps.key/6 +  M0_alps.key%6*4;
        M0_Status_Update &= ~M0_DEV_UPDATE_ALPS;
    }
    
    return index;
}

static void showDeadline(ParkingData *data)
{
    int day, hour, minute;
    double elapsed_time;
    time_t start = time(NULL);
    elapsed_time = difftime(data->deadline, start);

    day = (int)(elapsed_time / 60 / 60 / 24);
    hour = (int)(elapsed_time / 60 / 60 - 24 * day);
    minute = (int)(elapsed_time / 60 - 60 * hour - 60 * 24 * day);

    if (day < 0 || minute < 1 || hour < 0)
    {
        data->parkingStatus = PARKING_STATUS_EXPIRED;
    }

    gchar *text_time = g_strdup_printf(
        "<span font_desc='55' color='#DE9C18'>%02d : %02d</span>", hour, minute);
    gtk_label_set_markup(GTK_LABEL(data->timeLabel), text_time);
}

static gboolean updateParkingData(gpointer data)
{
    char *timestamp;
    GDateTime *d = g_date_time_new_now_local();

    timestamp = g_date_time_format(d, "%Y-%m-%d  %H:%M\t\t\t\t     0000000001");
    printf("%s\n", timestamp);

    gchar *text_time = g_strdup_printf("%s", timestamp);
    gtk_label_set_markup(GTK_LABEL(home_clock_label), text_time);
    gtk_label_set_markup(GTK_LABEL(select_clock_label), text_time);
    gtk_label_set_markup(GTK_LABEL(payment_clock_label), text_time);
    gtk_label_set_markup(GTK_LABEL(confirm_clock_label), text_time);
    g_date_time_unref(d);

    for (int i = 0; i < 8; i++)
    {
        switch (parkingData[i].parkingStatus)
        {
        case PARKING_STATUS_EMPTY:
            gtk_widget_hide(parkingData[i].image);
            gtk_widget_hide(parkingData[i].timeLabel);
            break;

        case PARKING_STATUS_DEADLINE:
            gtk_image_set_from_file(GTK_IMAGE(parkingData[i].image), PATH(deadline));
            gtk_widget_show(parkingData[i].image);
            showDeadline(&parkingData[i]);
            gtk_widget_show(parkingData[i].timeLabel);
            break;

        case PARKING_STATUS_EXPIRED:
            gtk_image_set_from_file(GTK_IMAGE(parkingData[i].image), PATH(expired));
            gtk_widget_show(parkingData[i].image);
            gtk_widget_hide(parkingData[i].timeLabel);
            break;

        case PARKING_STATUS_PAYMENT:
            gtk_image_set_from_file(GTK_IMAGE(parkingData[i].image), PATH(payment));
            gtk_widget_show(parkingData[i].image);
            gtk_widget_hide(parkingData[i].timeLabel);
            break;

        default:
            break;
        }
    }
    g_free(timestamp);
    return GPOINTER_TO_INT(data);
}

static gboolean spinnerAnimation(gpointer data)
{
    static int ratio;
    GdkWindow *gwindow = gtk_widget_get_window(GTK_WIDGET(data));

    cairo_region_t *cairoRegion = cairo_region_create();

    GdkDrawingContext *drawingContext;
    drawingContext = gdk_window_begin_draw_frame(gwindow, cairoRegion);

    cairo_t *cr = gdk_drawing_context_get_cairo_context(drawingContext);

    cairo_translate(cr, 95 / 2, 95 / 2);
    cairo_rotate(cr, ratio * M_PI / 180);
    cairo_translate(cr, -0.5 * 95, -0.5 * 95);

    cairo_set_source_surface(cr, spinnerImage, 0, 0);
    cairo_paint(cr);

    gdk_window_end_draw_frame(gwindow, drawingContext);
    cairo_region_destroy(cairoRegion);

    ratio += 5;
    return FALSE;
}

static gboolean countLoaded(void) {
    if (loaded < 94)
        loaded++;
    else
        return TRUE;

    return FALSE;
}

void *run(void *data)
{
    paySuccess = 2;

    gtk_init(NULL, NULL);
    initBlockData();
    GError *error;
    GtkCssProvider *cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(cssProvider, "/home/root/smart_city/theme.css", &error);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                GTK_STYLE_PROVIDER(cssProvider),
                                GTK_STYLE_PROVIDER_PRIORITY_USER);
    
    if (error != NULL)
       g_warning ("Error loading stylesheet from file %s. %s", "theme.css", error->message);

    // GTK_WINDOW_POPUP         show on the top screen without windows
    // GTK_WINDOW_TOPLEVEL      have windows
    home = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_fullscreen(GTK_WINDOW(home));

    home_fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(home), home_fixed);

    home_background = gtk_image_new_from_file(PATH(1));
    gtk_fixed_put(GTK_FIXED(home_fixed), home_background, 0, 0);

    hoverAnimation = gtk_image_new_from_file(PATH(hover));
    gtk_fixed_put(GTK_FIXED(home_fixed), hoverAnimation, 0, 0);
    home_hover_buffer = gdk_pixbuf_new_from_file(PATH(hover), NULL);

    for (int i = 0; i < 8; i++)
    {
        parkingData[i].image = gtk_image_new_from_file(PATH(deadline));
        gtk_fixed_put(GTK_FIXED(home_fixed), parkingData[i].image, (i / 4) * 600 + 255, (i % 4) * 270 + 341);

        parkingData[i].timeLabel = gtk_label_new(NULL);
        gtk_label_set_markup(GTK_LABEL(parkingData[i].timeLabel), "<span font_desc='55' color='#DE9C18'>00 : 00</span>");
        gtk_fixed_put(GTK_FIXED(home_fixed), parkingData[i].timeLabel, (i / 4) * 600 + 255, (i % 4) * 270 + 444);

        parkingData[i].parkNumLabel = gtk_label_new(NULL);
        gchar *text_time = g_strdup_printf(
            "<span font_desc='100' color='#16D2BA'>%02d</span>", parkingData[i].parkNum);
        gtk_label_set_markup(GTK_LABEL(parkingData[i].parkNumLabel), text_time);
        gtk_fixed_put(GTK_FIXED(home_fixed), parkingData[i].parkNumLabel, (i / 4) * 600 + 57, (i % 4) * 270 + 308);
    }

    selectbutton = gtk_image_new_from_file(PATH(select));
    gtk_fixed_put(GTK_FIXED(home_fixed), selectbutton, 0, 0);
    

    mask = gtk_image_new_from_file(PATH(loading_mask));
    gtk_fixed_put(GTK_FIXED(home_fixed), mask, 0, 0);

    loading_bar = gtk_image_new_from_file(PATH(loading_bar));
    gtk_fixed_put(GTK_FIXED(home_fixed), loading_bar, 143, 1205);
    home_loading_bar_buffer = gdk_pixbuf_new_from_file(PATH(loading_bar), NULL);

    home_clock_label = gtk_label_new("00:00");
    gtk_widget_set_name(home_clock_label,"inch10clock");
    gtk_fixed_put(GTK_FIXED(home_fixed), home_clock_label, 23, 1526);

    g_timeout_add(180000, resetParkingData, (gpointer)1);
    g_timeout_add(60000, updateParkingData, (gpointer)1);
    changePage(1);

    gtk_widget_show_all(home);

    gtk_widget_hide(GTK_WIDGET(mask));
    gtk_widget_hide(GTK_WIDGET(loading_bar));

    cleanOpacity(selectbutton);
    cleanOpacity(hoverAnimation);

    selectTimewindwos = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_fullscreen(GTK_WINDOW(selectTimewindwos));

    select_fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(selectTimewindwos), select_fixed);

    select_background = gtk_image_new_from_file(PATH(2));
    gtk_fixed_put(GTK_FIXED(select_fixed), select_background, 0, 0);

    select_hover = gtk_image_new_from_file(PATH(select_time_hover));
    gtk_fixed_put(GTK_FIXED(select_fixed), select_hover, 15, 800);
    select_hover_buffer = gdk_pixbuf_new_from_file(PATH(select_time_hover), NULL);
    gtk_widget_set_opacity(select_hover, 0);

    select_timer = gtk_image_new_from_file(PATH(select_time));
    gtk_fixed_put(GTK_FIXED(select_fixed), select_timer, 20, 540);

    select_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(select_label), "<span font_desc='65' color='#FFFFFF' weight='bold'>00:00</span>");
    gtk_fixed_put(GTK_FIXED(select_fixed), select_label, 50, 895);

    cleanOpacity(select_label);

    select_parking_space_label = gtk_label_new("00");
    gtk_fixed_put(GTK_FIXED(select_fixed), select_parking_space_label, 678, 1183);
    gtk_widget_set_name(select_parking_space_label,"select_parking_space_label");

    select_back_btn = gtk_image_new_from_file(PATH(Back_to_previous_page));
    gtk_fixed_put(GTK_FIXED(select_fixed), select_back_btn, 385, 1375);
    cleanOpacity(select_back_btn);

    select_clock_label = gtk_label_new(NULL);
    gtk_widget_set_name(select_clock_label,"inch10clock");
    gtk_fixed_put(GTK_FIXED(select_fixed), select_clock_label, 23, 1526);

    // g_timeout_add(5, selectTimeAnimation, NULL);

    // gtk_widget_show_all(selectTimewindwos);

    paymentWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_fullscreen(GTK_WINDOW(paymentWindow));

    payment_fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(paymentWindow), payment_fixed);

    payment_background = gtk_image_new_from_file(PATH(3));
    gtk_fixed_put(GTK_FIXED(payment_fixed), payment_background, 0, 0);

    payment_hover = gtk_image_new_from_file(PATH(select_payment));
    gtk_fixed_put(GTK_FIXED(payment_fixed), payment_hover, 0, 554);
    payment_hover_buffer = gdk_pixbuf_new_from_file(PATH(select_payment), NULL);
    rescaleImage(payment_hover, payment_hover_buffer, 1, 535);

    payment_qrcode = gtk_image_new_from_file(PATH(payment_qrcode));
    gtk_fixed_put(GTK_FIXED(payment_fixed), payment_qrcode, 77, 685);

    cleanOpacity(payment_qrcode);

    payment_card = gtk_image_new_from_file(PATH(payment_card));
    gtk_fixed_put(GTK_FIXED(payment_fixed), payment_card, 828, 695);

    cleanOpacity(payment_card);

    payment_parking_space_label = gtk_label_new("00");
    gtk_fixed_put(GTK_FIXED(payment_fixed), payment_parking_space_label, 386, 1183);
    gtk_widget_set_name(payment_parking_space_label,"select_parking_space_label");

    payment_parking_time_label = gtk_label_new("00");
    gtk_fixed_put(GTK_FIXED(payment_fixed), payment_parking_time_label, 873, 1183);
    gtk_widget_set_name(payment_parking_time_label,"select_parking_space_label");

    payment_back_btn = gtk_image_new_from_file(PATH(Back_to_previous_page));
    gtk_fixed_put(GTK_FIXED(payment_fixed), payment_back_btn, 385, 1375);
    cleanOpacity(payment_back_btn);

    payment_clock_label = gtk_label_new(NULL);
    gtk_widget_set_name(payment_clock_label,"inch10clock");
    gtk_fixed_put(GTK_FIXED(payment_fixed), payment_clock_label, 23, 1526);

    // g_timeout_add(25, paymentAnimation, NULL);
    // gtk_widget_show_all(paymentWindow);

    confirmWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_fullscreen(GTK_WINDOW(confirmWindow));

    confirm_fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(confirmWindow), confirm_fixed);

    confirm_background = gtk_image_new_from_file(PATH(4));
    gtk_fixed_put(GTK_FIXED(confirm_fixed), confirm_background, 0, 0);

    confirm_pay_label = gtk_label_new("$ 100");
    gtk_widget_set_name(confirm_pay_label,"confirm_red");
    gtk_fixed_put(GTK_FIXED(confirm_fixed), confirm_pay_label, 850, 1061);

    confirm_park_label = gtk_label_new("11");
    gtk_widget_set_name(confirm_park_label,"confirm_black");
    gtk_fixed_put(GTK_FIXED(confirm_fixed), confirm_park_label, 214, 1061);

    confirm_time_label = gtk_label_new("0:30");
    gtk_widget_set_name(confirm_time_label,"confirm_black");
    gtk_fixed_put(GTK_FIXED(confirm_fixed), confirm_time_label, 511, 1061);

    confirm_home_button = gtk_image_new_from_file(PATH(home));
    gtk_fixed_put(GTK_FIXED(confirm_fixed), confirm_home_button, 385, 1370);
    cleanOpacity(confirm_home_button);

    confirm_clock_label = gtk_label_new(NULL);
    gtk_widget_set_name(confirm_clock_label,"inch10clock");
    gtk_fixed_put(GTK_FIXED(confirm_fixed), confirm_clock_label, 23, 1526);

    // g_timeout_add(100, confirmAnimation, NULL);
    // gtk_widget_show_all(confirmWindow);

    connectionWindows = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_fullscreen(GTK_WINDOW(connectionWindows));

    connection_fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(connectionWindows), connection_fixed);

    connection_background = gtk_image_new_from_file(PATH(5_1));
    gtk_fixed_put(GTK_FIXED(connection_fixed), connection_background, 0, 0);

    // create the are we can draw in
    GtkWidget *drawingArea;
    drawingArea = gtk_drawing_area_new();
    gtk_widget_set_size_request(drawingArea, 95, 95);
    gtk_fixed_put(GTK_FIXED(connection_fixed), drawingArea, 550, 700);

    spinnerImage = cairo_image_surface_create_from_png(PATH(spinner));

    g_signal_connect(G_OBJECT(drawingArea), "draw", G_CALLBACK(spinnerAnimation), drawingArea);

    // g_timeout_add(500,  spinnerStart, connectionWindows);
    // gtk_widget_show_all(connectionWindows);

    g_timeout_add(1, updateParkingData, (gpointer)0);
    gtk_main();

    return (int *)data;
}

static gboolean courseAnimation(gpointer home_fixed)
{
    static int presstime;
    static int lastStatus;
    int status = getSelectBlock();
    int selectBlockX = ((status / 2) % 2) * 600 + 20;
    int selectBlockY = ((status / 2) / 2) * 270 + 40;



    if (status > 3 && status < 20)
    {
        if (status == lastStatus)
        {
            presstime++;
            if ((int)(568 * (float)presstime / press_time) < 568)
                rescaleImage(hoverAnimation, 
                            home_hover_buffer, 
                            (int)(568 * (float)presstime / press_time), 
                            40);
            // printf("Press time %d\n", (int)(568 * (float)presstime / press_time));
        }
        else
        {
            presstime = 0;
            gtk_fixed_move(GTK_FIXED(home_fixed), selectbutton, selectBlockX, selectBlockY);
            gtk_fixed_move(GTK_FIXED(home_fixed), hoverAnimation, selectBlockX, selectBlockY);
        }
    }

    if (presstime >= press_time)
    {
        presstime = 0;
        if (parkingData[(status / 4) + ((status / 2) % 2 * 4)-1].parkingStatus == PARKING_STATUS_PAYMENT)
        {
            gtk_widget_hide(home);
            gtk_widget_show_all(selectTimewindwos);
            changePage(2);
            
            selectData.selectBlockNum = (status / 4) + ((status / 2) % 2 * 4) - 1;

            gchar *text_time = g_strdup_printf("%2d", parkingData[selectData.selectBlockNum].parkNum);
            gtk_label_set_markup(GTK_LABEL(select_parking_space_label), text_time);

            printf("select block [%d]\n", selectData.selectBlockNum);
            cleanOpacity(selectbutton);
            cleanOpacity(hoverAnimation);
            return FALSE;
        }
    }
    opacityAnimation(selectbutton, status > 3 && status < 20);
    opacityAnimation(hoverAnimation, status > 3 && status < 20);

    lastStatus = status;

    return TRUE;
}

static gboolean selectTimeAnimation(gpointer fix)
{
    static int lastStatus;
    static int presstime;
    int status = getSelectBlock();
    int selectBlockX = 20 + (295 * (status % 4));
    int selectBlockY = 540 + (282 * ((status - 8) / 4));

    if (countLoaded()){
        if (status > 7 && status < 16)
        {
            if (status == lastStatus)
            {
                presstime++;
                rescaleImage(select_hover, select_hover_buffer, 280 * (float)presstime / press_time, 255);
            }
            else
            {
                presstime = 0;

                gtk_fixed_move(GTK_FIXED(fix), select_timer, selectBlockX, selectBlockY);
                gtk_fixed_move(GTK_FIXED(fix), select_hover, selectBlockX, selectBlockY);
                gtk_fixed_move(GTK_FIXED(fix), select_label, selectBlockX + 60, selectBlockY + 75);

                gchar *text_time = g_strdup_printf(
                    "<span font_desc='65' color='#FFFFFF' weight='bold'>%d:%02d</span>", ((status + 1) / 2) - 4, ((status + 1) % 2) * 30);
                cleanOpacity(select_label);
                gtk_label_set_markup(GTK_LABEL(select_label), text_time);
            }
        }else if (status == 21 || status == 22) {
            if (status == lastStatus) {
                presstime++;
            }else {
                presstime = 0;
            }

        }

        if (presstime >= press_time)
        {
            presstime = 0;
            if (status > 7 && status < 16) {
                gtk_widget_hide(selectTimewindwos);
                gtk_widget_show_all(paymentWindow);
                changePage(3);

                selectData.selectTimeHour = ((status + 1) / 2) - 4;
                selectData.selectTimeMinute = ((status + 1) % 2) * 30;

                printf("setting time %d : %d\n", selectData.selectTimeHour, selectData.selectTimeMinute);

                gchar *text_time = g_strdup_printf("%02d", parkingData[selectData.selectBlockNum].parkNum);
                gtk_label_set_markup(GTK_LABEL(payment_parking_space_label), text_time);

                text_time = g_strdup_printf("%02d : %02d", selectData.selectTimeHour, selectData.selectTimeMinute);
                gtk_label_set_markup(GTK_LABEL(payment_parking_time_label), text_time);
            }else if (status == 21 || status == 22) {
                gtk_widget_hide(selectTimewindwos);
                gtk_widget_show(home);
                changePage(1);
            }
            


            loaded = 0;
            cleanOpacity(select_hover);
            cleanOpacity(select_label);
            cleanOpacity(select_back_btn);
            return FALSE;
        }

        opacityAnimation(select_back_btn, status == 21 || status == 22);
        opacityAnimation(select_hover, status > 7 && status < 16);
        opacityAnimation(select_label, status > 7 && status < 16);
        lastStatus = status;
    }
    

    return TRUE;
}

static gboolean paymentAnimation(gpointer fix)
{
    static int lastSelections;
    static int presstime;
    static int selections;
    int status = getSelectBlock();
    if (countLoaded()){
        if (status > 7 && status < 16) {
            selections = !(status % 4 < 2);
            if(selections == lastSelections) {
                presstime++;
                rescaleImage(payment_hover, payment_hover_buffer, 600 * presstime / press_time, 535);
            }else {
                presstime = 0;
                gtk_fixed_move(GTK_FIXED(fix), payment_hover, selections ? 600 : 0, 554);
                rescaleImage(payment_hover, payment_hover_buffer, 1, 535);
            }
        }else if (status == 21 || status == 22) {
                presstime++;
                selections = 2;
        }else {
            selections = 2;
            if(selections != lastSelections)
                rescaleImage(payment_hover, payment_hover_buffer, 1, 535);
            presstime = 0;
        }

        if (presstime >= press_time)
        {
            presstime = 0;
            if (status > 7 && status < 16) {
                gtk_widget_hide(paymentWindow);
                gtk_widget_show_all(confirmWindow);
                changePage(4);
                printf("select payment %d\n", selectData.selectPayment);
                selectData.selectPayment = status % 4 > 1;
            }else if (status == 21 || status == 22) {
                gtk_widget_hide(paymentWindow);
                gtk_widget_show_all(selectTimewindwos);
                changePage(2);
            }

            loaded = 0;
            rescaleImage(payment_hover, payment_hover_buffer, 1, 535);
            cleanOpacity(payment_qrcode);
            cleanOpacity(payment_card);
            cleanOpacity(payment_back_btn);

            return FALSE;
        }
        opacityAnimation(payment_back_btn, status == 21 || status == 22);
        opacityAnimation(payment_qrcode, selections == 0);
        opacityAnimation(payment_card, selections == 1);

        lastSelections = selections;
    }


    return TRUE;
}

static gboolean confirmAnimation(gpointer fix)
{
    static int presstime;
    static int successCount;
    static int connected;
    static int changedPayment = 1;
    static int successTime = 0;
    int status = getSelectBlock();
    int money = 8 * selectData.selectTimeHour + 4 * selectData.selectTimeMinute / 30;

    if(successTime == 312){
        paySuccess = 0;
    }
    successTime++;


    if (changedPayment)
    {
        gchar *text_time = g_strdup_printf("$ %d", money);
        gtk_label_set_markup(GTK_LABEL(confirm_pay_label), text_time);

        text_time = g_strdup_printf("%d", parkingData[selectData.selectBlockNum].parkNum);
        gtk_label_set_markup(GTK_LABEL(confirm_park_label), text_time);

        text_time = g_strdup_printf(
            "%02d:%02d",
            selectData.selectTimeHour,
            selectData.selectTimeMinute);
        gtk_label_set_markup(GTK_LABEL(confirm_time_label), text_time);

        changedPayment = 0;


        gtk_image_set_from_file(GTK_IMAGE(confirm_background), 
                    selectData.selectPayment ? PATH(5) : PATH(4) );

        if(selectData.selectPayment && !connected) {
            gtk_image_set_from_file(GTK_IMAGE(connection_background), PATH(5_1));
            changePage(5);
            gtk_widget_hide(confirmWindow);
            gtk_widget_show_all(connectionWindows);
            connected = 1;
            return FALSE;
        }
        
    }
    if (countLoaded()){
        if ((status == 21 || status == 22) && countLoaded())
            presstime++;
        else
            presstime = 0;

        if (presstime >= press_time || successCount > 300)
        {
            presstime=0;
            successCount = 0;
            connected = 0;
            gtk_widget_hide(confirmWindow);
            gtk_widget_show(home);
            g_timeout_add(10, updateParkingData, (gpointer)0);
            changePage(1);
            changedPayment = 1;
            successTime = 0;
            loaded = 0;
            cleanOpacity(confirm_home_button);
            return FALSE;
        }

        opacityAnimation(confirm_home_button, status == 21 || status == 22);
    }
    

    if (paySuccess != 2 || successTime == 312)
    {
        if (connected == 1 && selectData.selectPayment)
        {
            connected = 2;
            gtk_image_set_from_file(GTK_IMAGE(connection_background), PATH(5_3));
            changePage(5);
            gtk_widget_hide(confirmWindow);
            gtk_widget_show_all(connectionWindows);
            return FALSE;
        }
        int page;
        printf("pay Success!\n");

        if (selectData.selectPayment)
            page = paySuccess ? 5 : 4;
        else 
            page = paySuccess ? 2 : 1;
        
        gchar *text_buf = g_strdup_printf(
            "/home/root/smart_city/image/%d_%d.png", selectData.selectPayment ? 5 : 4, page );

        gtk_image_set_from_file(GTK_IMAGE(confirm_background), text_buf);

        if (!paySuccess) {
            parkingData[selectData.selectBlockNum].parkingStatus = PARKING_STATUS_DEADLINE;
            struct tm *p;
            parkingData[selectData.selectBlockNum].deadline = time(NULL);
            p = localtime(&parkingData[selectData.selectBlockNum].deadline);
            p->tm_hour += selectData.selectTimeHour;
            p->tm_min += selectData.selectTimeMinute;
            parkingData[selectData.selectBlockNum].deadline = mktime(p);
        }

        gtk_widget_hide(confirm_home_button);
        gtk_widget_hide(confirm_park_label);
        gtk_widget_hide(confirm_pay_label);
        gtk_widget_hide(confirm_time_label);
        paySuccess = 2;
        successCount = 1;
    }

    if (successCount)
        successCount++;
    
    return TRUE;
}



static gboolean spinnerStart(gpointer data)
{
    static int skipTime = 0;
    gtk_widget_queue_draw(GTK_WIDGET(data));

    if (skipTime++ >= 50)
    {
        gtk_widget_hide(connectionWindows);
        gtk_widget_show(confirmWindow);
        changePage(4);
        skipTime = 0;
        return FALSE;
    }

    return TRUE;
}

static void changePage(int page) {
    printf("Show page %d\n", page);
    switch (page)
    {
    case 0:
        g_timeout_add(5, progressLoadingBar, loading_bar);
        break;

    case 1:
        g_timeout_add(frame_rate, courseAnimation, home_fixed);
        break;
    
    case 2:
        g_timeout_add(frame_rate, selectTimeAnimation, select_fixed);
        break;

    case 3:
        g_timeout_add(frame_rate, paymentAnimation, payment_fixed);
        break;

    case 4:
        g_timeout_add(frame_rate, confirmAnimation, confirm_fixed);
        break;

    case 5:
        g_timeout_add(frame_rate, spinnerStart, connectionWindows);
        break;
    
    default:
        break;
    }
}