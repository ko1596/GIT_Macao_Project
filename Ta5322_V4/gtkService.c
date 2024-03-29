#include "gtkService.h"



static GtkWidget *home;
static GtkWidget *home_fixed;
static GtkWidget *home_background;
static GtkWidget *mask;
static GtkWidget *loading_bar;
static gbutton selectbutton;
static gbutton hoverAnimation;
static GtkWidget *home_clock_label;

static GtkWidget *selectTimewindwos;
static GtkWidget *select_fixed;
static GtkWidget *select_background;
static gbutton select_timer;
static gbutton select_hover;
static gbutton select_label;
static GtkWidget *select_clock_label;

static GtkWidget *paymentWindow;
static GtkWidget *payment_fixed;
static GtkWidget *payment_background;
static gbutton payment_hover;
static gbutton payment_card;
static gbutton payment_qrcode;
static GtkWidget *payment_clock_label;

static GtkWidget *confirmWindow;
static GtkWidget *confirm_fixed;
static GtkWidget *confirm_background;
static GtkWidget *confirm_pay_label;
static GtkWidget *confirm_park_label;
static GtkWidget *confirm_time_label;
static GtkWidget *confirm_clock_label;
static gbutton confirm_home_button;

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

static int paySuccess;

static void changePage(int page);

void changePaySuccess(int status) {
    paySuccess = status;
}

static void initBlockData() {
    struct tm *p;
    parkingData[0].parkingStatus = 0;
    parkingData[1].parkingStatus = 1;
    parkingData[2].parkingStatus = 2;
    parkingData[3].parkingStatus = 3;
    parkingData[4].parkingStatus = 3;
    parkingData[5].parkingStatus = 2;
    parkingData[6].parkingStatus = 1;
    parkingData[7].parkingStatus = 0;

    parkingData[0].parkNum = 21;
    parkingData[1].parkNum = 22;
    parkingData[2].parkNum = 23;
    parkingData[3].parkNum = 24;
    parkingData[4].parkNum = 25;
    parkingData[5].parkNum = 26;
    parkingData[6].parkNum = 27;
    parkingData[7].parkNum = 28;

    parkingData[1].deadline = time(NULL);
    p = localtime(&parkingData[1].deadline);
    p->tm_hour+=2;
    p->tm_min+=13;
    parkingData[1].deadline = mktime(p); 

    parkingData[6].deadline = time(NULL);
    p = localtime(&parkingData[6].deadline);
    p->tm_min+=1;
    parkingData[6].deadline = mktime(p); 
}

void changeParingStatus(int blockNum, int status) {
    parkingData[blockNum].parkingStatus = status;
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

static gint findMaxArrayIndex(guint16 array[], gint array_size)
{
    gint maxIndex = 0;
    guint16 maxValue = 0;
    for (gint i = 0; i < array_size; i++)
        if (array[i] > maxValue && array[i] < 60000)
        {
            maxValue = array[i];
            maxIndex = i;
        }
    return maxIndex;
}

static gboolean progressLoadingBar(gpointer data)
{
    static int progress;
    progress++;
    gtk_image_set_from_file(GTK_IMAGE(data), "/home/root/D88TEST/Ta5322_V4alps/image/loading_bar.png");
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

static void opacityAnimation(gbutton *gb, gboolean hover) {
    if (hover && gb->opacity < 1)
    {
        gb->opacity += 0.05;
        gtk_widget_set_opacity(gb->image, gb->opacity);
    }
    else if (!hover && gb->opacity > 0)
    {
        gb->opacity -= 0.05;
        gtk_widget_set_opacity(gb->image, gb->opacity);
    }
}

static gint getSelectBlock(){
    gint maxIndex = findMaxArrayIndex(block, 24);
    if (SELECT_BLOCK(block[maxIndex]))
        return maxIndex;
    else
        return -1;
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

    timestamp = g_date_time_format(d, "%Y-%m-%d %H:%M\t\t    0000000001");
    printf("%s\n", timestamp);

    gchar *text_time = g_strdup_printf(
        "<span font_desc='50' color='#FFFFFF' weight='bold'>%s</span>", timestamp);
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
            gtk_image_set_from_file(GTK_IMAGE(parkingData[i].image), "/home/root/D88TEST/Ta5322_V4alps/image/deadline.png");
            gtk_widget_show(parkingData[i].image);
            showDeadline(&parkingData[i]);
            gtk_widget_show(parkingData[i].timeLabel);
            break;

        case PARKING_STATUS_EXPIRED:
            gtk_image_set_from_file(GTK_IMAGE(parkingData[i].image), "/home/root/D88TEST/Ta5322_V4alps/image/expired.png");
            gtk_widget_show(parkingData[i].image);
            gtk_widget_hide(parkingData[i].timeLabel);
            break;

        case PARKING_STATUS_PAYMENT:
            gtk_image_set_from_file(GTK_IMAGE(parkingData[i].image), "/home/root/D88TEST/Ta5322_V4alps/image/payment.png");
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

void *run(void *data)
{
    paySuccess = 2;

    gtk_init(NULL, NULL);
    initBlockData();

    // GTK_WINDOW_POPUP         show on the top screen without windows
    // GTK_WINDOW_TOPLEVEL      have windows
    home = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_fullscreen(GTK_WINDOW(home));

    home_fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(home), home_fixed);

    home_background = gtk_image_new_from_file("/home/root/D88TEST/Ta5322_V4alps/image/1.png");
    gtk_fixed_put(GTK_FIXED(home_fixed), home_background, 0, 0);

    hoverAnimation.image = gtk_image_new_from_file("/home/root/D88TEST/Ta5322_V4alps/image/hover.png");
    gtk_fixed_put(GTK_FIXED(home_fixed), hoverAnimation.image, 0, 0);
    home_hover_buffer = gdk_pixbuf_new_from_file("/home/root/D88TEST/Ta5322_V4alps/image/hover.png", NULL);

    for (int i = 0; i < 8; i++)
    {
        parkingData[i].image = gtk_image_new_from_file("/home/root/D88TEST/Ta5322_V4alps/image/deadline.png");
        gtk_fixed_put(GTK_FIXED(home_fixed), parkingData[i].image, (i / 4) * 600 + 240, (i % 4) * 270 + 60);

        parkingData[i].timeLabel = gtk_label_new(NULL);
        gtk_label_set_markup(GTK_LABEL(parkingData[i].timeLabel), "<span font_desc='55' color='#DE9C18'>00 : 00</span>");
        gtk_fixed_put(GTK_FIXED(home_fixed), parkingData[i].timeLabel, (i / 4) * 600 + 257, (i % 4) * 270 + 155);

        parkingData[i].parkNumLabel = gtk_label_new(NULL);
        gchar *text_time = g_strdup_printf(
            "<span font_desc='100' color='#16D2BA'>%02d</span>", parkingData[i].parkNum);
        gtk_label_set_markup(GTK_LABEL(parkingData[i].parkNumLabel), text_time);
        gtk_fixed_put(GTK_FIXED(home_fixed), parkingData[i].parkNumLabel, (i / 4) * 600 + 57, (i % 4) * 270 + 29);
    }

    selectbutton.image = gtk_image_new_from_file("/home/root/D88TEST/Ta5322_V4alps/image/select.png");
    gtk_fixed_put(GTK_FIXED(home_fixed), selectbutton.image, 0, 0);
    

    mask = gtk_image_new_from_file("/home/root/D88TEST/Ta5322_V4alps/image/loading_mask.png");
    gtk_fixed_put(GTK_FIXED(home_fixed), mask, 0, 0);

    loading_bar = gtk_image_new_from_file("/home/root/D88TEST/Ta5322_V4alps/image/loading_bar.png");
    gtk_fixed_put(GTK_FIXED(home_fixed), loading_bar, 143, 1205);
    home_loading_bar_buffer = gdk_pixbuf_new_from_file("/home/root/D88TEST/Ta5322_V4alps/image/loading_bar.png", NULL);

    home_clock_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(home_clock_label), "<span font_desc='50' color='#FFFFFF' weight='bold'>00:00</span>");
    gtk_fixed_put(GTK_FIXED(home_fixed), home_clock_label, 0, 1510);

    g_timeout_add(60000, updateParkingData, (gpointer)1);
    changePage(0);

    gtk_widget_show_all(home);

    selectbutton.opacity = 0;
    gtk_widget_set_opacity(selectbutton.image, selectbutton.opacity);

    hoverAnimation.opacity = 0;
    gtk_widget_set_opacity(hoverAnimation.image, hoverAnimation.opacity);

    selectTimewindwos = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_fullscreen(GTK_WINDOW(selectTimewindwos));

    select_fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(selectTimewindwos), select_fixed);

    select_background = gtk_image_new_from_file("/home/root/D88TEST/Ta5322_V4alps/image/2.png");
    gtk_fixed_put(GTK_FIXED(select_fixed), select_background, 0, 0);

    select_hover.image = gtk_image_new_from_file("/home/root/D88TEST/Ta5322_V4alps/image/select_time_hover.png");
    gtk_fixed_put(GTK_FIXED(select_fixed), select_hover.image, 15, 800);
    select_hover_buffer = gdk_pixbuf_new_from_file("/home/root/D88TEST/Ta5322_V4alps/image/select_time_hover.png", NULL);
    gtk_widget_set_opacity(select_hover.image, 0);

    select_timer.image = gtk_image_new_from_file("/home/root/D88TEST/Ta5322_V4alps/image/select_time.png");
    gtk_fixed_put(GTK_FIXED(select_fixed), select_timer.image, 15, 800);

    select_label.image = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(select_label.image), "<span font_desc='65' color='#FFFFFF' weight='bold'>00:00</span>");
    gtk_fixed_put(GTK_FIXED(select_fixed), select_label.image, 50, 895);
    select_label.opacity = 0;
    gtk_widget_set_opacity(select_label.image, select_label.opacity);

    select_clock_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(select_clock_label), "<span font_desc='50' color='#FFFFFF' weight='bold'>00:00</span>");
    gtk_fixed_put(GTK_FIXED(select_fixed), select_clock_label, 0, 1510);

    // g_timeout_add(5, selectTimeAnimation, NULL);

    // gtk_widget_show_all(selectTimewindwos);

    paymentWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_fullscreen(GTK_WINDOW(paymentWindow));

    payment_fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(paymentWindow), payment_fixed);

    payment_background = gtk_image_new_from_file("/home/root/D88TEST/Ta5322_V4alps/image/3.png");
    gtk_fixed_put(GTK_FIXED(payment_fixed), payment_background, 0, 0);

    payment_hover.image = gtk_image_new_from_file("/home/root/D88TEST/Ta5322_V4alps/image/select_payment.png");
    gtk_fixed_put(GTK_FIXED(payment_fixed), payment_hover.image, 0, 750);
    payment_hover_buffer = gdk_pixbuf_new_from_file("/home/root/D88TEST/Ta5322_V4alps/image/select_payment.png", NULL);

    payment_qrcode.image = gtk_image_new_from_file("/home/root/D88TEST/Ta5322_V4alps/image/payment_qrcode.png");
    gtk_fixed_put(GTK_FIXED(payment_fixed), payment_qrcode.image, 144, 809);
    gtk_widget_set_opacity(payment_qrcode.image, payment_qrcode.opacity);
    payment_qrcode.opacity = 0;

    payment_card.image = gtk_image_new_from_file("/home/root/D88TEST/Ta5322_V4alps/image/payment_card.png");
    gtk_fixed_put(GTK_FIXED(payment_fixed), payment_card.image, 827, 814);
    payment_card.opacity = 0;
    gtk_widget_set_opacity(payment_card.image, payment_card.opacity);

    payment_clock_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(payment_clock_label), "<span font_desc='50' color='#FFFFFF' weight='bold'>00:00</span>");
    gtk_fixed_put(GTK_FIXED(payment_fixed), payment_clock_label, 0, 1510);

    // g_timeout_add(25, paymentAnimation, NULL);
    // gtk_widget_show_all(paymentWindow);

    confirmWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_fullscreen(GTK_WINDOW(confirmWindow));

    confirm_fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(confirmWindow), confirm_fixed);

    confirm_background = gtk_image_new_from_file("/home/root/D88TEST/Ta5322_V4alps/image/4.png");
    gtk_fixed_put(GTK_FIXED(confirm_fixed), confirm_background, 0, 0);

    confirm_pay_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(confirm_pay_label), "<span font_desc='45' color='#000000'>$ 12</span>");
    gtk_fixed_put(GTK_FIXED(confirm_fixed), confirm_pay_label, 230, 1140);

    confirm_park_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(confirm_park_label), "<span font_desc='45' color='#000000'>11</span>");
    gtk_fixed_put(GTK_FIXED(confirm_fixed), confirm_park_label, 544, 1140);

    confirm_time_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(confirm_time_label), "<span font_desc='45' color='#000000'>1.5</span>");
    gtk_fixed_put(GTK_FIXED(confirm_fixed), confirm_time_label, 846, 1140);

    confirm_home_button.image = gtk_image_new_from_file("/home/root/D88TEST/Ta5322_V4alps/image/home.png");
    gtk_fixed_put(GTK_FIXED(confirm_fixed), confirm_home_button.image, 441, 1333);

    confirm_clock_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(confirm_clock_label), "<span font_desc='50' color='#FFFFFF' weight='bold'>00:00</span>");
    gtk_fixed_put(GTK_FIXED(confirm_fixed), confirm_clock_label, 0, 1510);

    // g_timeout_add(100, confirmAnimation, NULL);
    // gtk_widget_show_all(confirmWindow);

    connectionWindows = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_fullscreen(GTK_WINDOW(connectionWindows));

    connection_fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(connectionWindows), connection_fixed);

    connection_background = gtk_image_new_from_file("/home/root/D88TEST/Ta5322_V4alps/image/5_1.png");
    gtk_fixed_put(GTK_FIXED(connection_fixed), connection_background, 0, 0);

    // create the are we can draw in
    GtkWidget *drawingArea;
    drawingArea = gtk_drawing_area_new();
    gtk_widget_set_size_request(drawingArea, 95, 95);
    gtk_fixed_put(GTK_FIXED(connection_fixed), drawingArea, 550, 700);

    spinnerImage = cairo_image_surface_create_from_png("/home/root/D88TEST/Ta5322_V4alps/image/spinner.png");

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
    // static int delayTimes = 0;
    int status = getSelectBlock();
    int selectBlockX = ((status / 2) % 2) * 600 + 20;
    int selectBlockY = ((status / 2) / 2) * 270 + 30;



    if (status > -1 && status < 16)
    {
        if (status == lastStatus)
        {
            presstime++;
            rescaleImage(hoverAnimation.image, 
                        home_hover_buffer, 
                        (int)(568 * (float)presstime / SELECT_BUTTON_TIME), 
                        40);
        }
        else
        {
            presstime = 0;
            gtk_fixed_move(GTK_FIXED(home_fixed), selectbutton.image, selectBlockX, selectBlockY);
            gtk_fixed_move(GTK_FIXED(home_fixed), hoverAnimation.image, selectBlockX, selectBlockY);
        }
    }

    if (presstime > SELECT_BUTTON_TIME)
    {
        presstime = 0;
        if (parkingData[(status / 4) + ((status / 2) % 2 * 4)].parkingStatus == PARKING_STATUS_PAYMENT)
        {
            gtk_widget_hide(home);
            gtk_widget_show_all(selectTimewindwos);
            changePage(2);
            
            selectData.selectBlockNum = (status / 4) + ((status / 2) % 2 * 4);
            printf("select block [%d]\n", selectData.selectBlockNum);
            printf("Go to page 2\n");
            return FALSE;
        }
    }
    opacityAnimation(&selectbutton, status > -1 && status < 16);
    opacityAnimation(&hoverAnimation, status > -1 && status < 16);

    lastStatus = status;

    return TRUE;
}

static gboolean selectTimeAnimation(gpointer fix)
{
    static int lastStatus;
    static int presstime;
    int status = getSelectBlock();
    int selectBlockX = 15 + (296 * (status % 4));
    int selectBlockY = 800 + (315 * ((status - 12) / 4));

    if (status > 11 && status < 20)
    {
        if (status == lastStatus)
        {
            presstime++;
            rescaleImage(select_hover.image, select_hover_buffer, 310 * presstime / SELECT_BUTTON_TIME, 330);
        }
        else
        {
            presstime = 0;

            gtk_fixed_move(GTK_FIXED(fix), select_timer.image, selectBlockX, selectBlockY);
            gtk_fixed_move(GTK_FIXED(fix), select_hover.image, selectBlockX - 14, selectBlockY - 14);
            gtk_fixed_move(GTK_FIXED(fix), select_label.image, selectBlockX + 50, selectBlockY + 95);

            gchar *text_time = g_strdup_printf(
                "<span font_desc='65' color='#FFFFFF' weight='bold'>%d:%02d</span>", ((status + 1) / 2) - 6, ((status + 1) % 2) * 30);

            gtk_label_set_markup(GTK_LABEL(select_label.image), text_time);
        }
    }

    if (presstime > SELECT_BUTTON_TIME)
    {
        presstime = 0;

        gtk_widget_hide(selectTimewindwos);
        gtk_widget_show_all(paymentWindow);
        changePage(3);

        selectData.selectTimeHour = ((status + 1) / 2) - 6;
        selectData.selectTimeMinute = ((status + 1) % 2) * 30;

        printf("setting time %d : %d\n", selectData.selectTimeHour, selectData.selectTimeMinute);
        printf("Go to page 3\n");
        return FALSE;
    }

    opacityAnimation(&select_hover, status > 11 && status < 20);
    opacityAnimation(&select_label, status > 11 && status < 20);
    lastStatus = status;

    return TRUE;
}

static gboolean paymentAnimation(gpointer fix)
{
    static int lastSelections;
    static int presstime;
    static int selections;
    int status = getSelectBlock();

    if (status > 11 && status < 20) {
        selections = !(status % 4 < 2);
        if(selections == lastSelections) {
            presstime++;
            rescaleImage(payment_hover.image, payment_hover_buffer, 600 * presstime / SELECT_BUTTON_TIME, 535);
        }else {
            presstime = 0;
            gtk_fixed_move(GTK_FIXED(fix), payment_hover.image, selections ? 600 : 0, 750);
            rescaleImage(payment_hover.image, payment_hover_buffer, 1, 535);
        }
    }else {
        selections = 2;
        if(selections != lastSelections)
            rescaleImage(payment_hover.image, payment_hover_buffer, 1, 535);
        presstime = 0;
    }

    if (presstime == SELECT_BUTTON_TIME)
    {
        presstime = 0;

        gtk_widget_hide(paymentWindow);
        gtk_widget_show_all(confirmWindow);
        changePage(4);
        
        selectData.selectPayment = status % 4 > 1;
        
        printf("select payment %d\n", selectData.selectPayment);
        printf("Go to page 4\n");
        return FALSE;
    }

    opacityAnimation(&payment_qrcode, selections == 0);
    opacityAnimation(&payment_card, selections == 1);

    lastSelections = selections;

    return TRUE;
}

static gboolean confirmAnimation(gpointer fix)
{
    static int presstime;
    static int successCount;
    static int connected;
    static int changedPayment = 1;
    int status = getSelectBlock();

    int money = 8 * selectData.selectTimeHour + 4 * selectData.selectTimeMinute / 30;

    if (changedPayment)
    {
        gchar *text_time = g_strdup_printf(
            "<span font_desc='45' color='#000000'>$ %d</span>", money);
        gtk_label_set_markup(GTK_LABEL(confirm_pay_label), text_time);

        text_time = g_strdup_printf(
            "<span font_desc='45' color='#000000'>%d</span>",
            parkingData[selectData.selectBlockNum].parkNum);
        gtk_label_set_markup(GTK_LABEL(confirm_park_label), text_time);

        text_time = g_strdup_printf(
            "<span font_desc='45' color='#000000'>%02d:%02d</span>",
            selectData.selectTimeHour,
            selectData.selectTimeMinute);
        gtk_label_set_markup(GTK_LABEL(confirm_time_label), text_time);

        changedPayment = 0;


        gtk_image_set_from_file(GTK_IMAGE(confirm_background), 
                    selectData.selectPayment ? "/home/root/D88TEST/Ta5322_V4alps/image/5.png" : "/home/root/D88TEST/Ta5322_V4alps/image/4.png" );

        int fix_y = selectData.selectPayment ? 549 : 1140;
        gtk_fixed_move(GTK_FIXED(fix), confirm_pay_label, 230, fix_y);
        gtk_fixed_move(GTK_FIXED(fix), confirm_park_label, 544, fix_y);
        gtk_fixed_move(GTK_FIXED(fix), confirm_time_label, 846, fix_y);

        if(selectData.selectPayment && !connected) {
            gtk_image_set_from_file(GTK_IMAGE(connection_background), "/home/root/D88TEST/Ta5322_V4alps/image/5_1.png");
            changePage(5);
            gtk_widget_hide(confirmWindow);
            gtk_widget_show_all(connectionWindows);
            connected = 1;
            return FALSE;
        }
        
    }

    if (status == 21 || status == 22)
        presstime++;
    else
        presstime = 0;

    if (presstime > SELECT_BUTTON_TIME || successCount > 300)
    {
        presstime=0;
        successCount = 0;
        connected = 0;
        gtk_widget_hide(confirmWindow);
        gtk_widget_show(home);
        g_timeout_add(10, updateParkingData, (gpointer)0);
        changePage(1);
        changedPayment = 1;
        return FALSE;
    }

    opacityAnimation(&confirm_home_button, status == 21 || status == 22);

    if (paySuccess != 2)
    {
        if (connected == 1 && selectData.selectPayment)
        {
            connected = 2;
            gtk_image_set_from_file(GTK_IMAGE(connection_background), "/home/root/D88TEST/Ta5322_V4alps/image/5_3.png");
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
            "/home/root/D88TEST/Ta5322_V4alps/image/%d_%d.png", selectData.selectPayment ? 5 : 4, page );

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

        gtk_widget_hide(confirm_home_button.image);
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

gboolean spinnerAnimation(gpointer data)
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
    switch (page)
    {
    case 0:
        g_timeout_add(5, progressLoadingBar, loading_bar);
        break;

    case 1:
        g_timeout_add(16, courseAnimation, home_fixed);
        break;
    
    case 2:
        g_timeout_add(16, selectTimeAnimation, select_fixed);
        break;

    case 3:
        g_timeout_add(16, paymentAnimation, payment_fixed);
        break;

    case 4:
        g_timeout_add(16, confirmAnimation, confirm_fixed);
        break;

    case 5:
        g_timeout_add(16, spinnerStart, connectionWindows);
        break;
    
    default:
        break;
    }
}