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

gint findMaxArrayIndex(guint16 array[], gint array_size)
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

void refreshLoadingBerFrame(GtkWidget *loadingBar, int weight, int height)
{
    GdkPixbuf *pixbuf;

    pixbuf = gtk_image_get_pixbuf(GTK_IMAGE(loadingBar));
    pixbuf = gdk_pixbuf_scale_simple(pixbuf, weight, height,
                                     GDK_INTERP_NEAREST);

    gtk_image_set_from_pixbuf(GTK_IMAGE(loadingBar), pixbuf);
    g_object_unref(pixbuf);
}

gboolean progressLoadingBar(gpointer data)
{
    static int progress;
    progress++;
    gtk_image_set_from_file(GTK_IMAGE(data), "image/loading_bar.png");
    refreshLoadingBerFrame(GTK_WIDGET(data), progress, 45);
    gtk_widget_show(GTK_WIDGET(data));
    gtk_widget_show(GTK_WIDGET(mask));
    if (progress < 922)
        return TRUE;
    else
    {
        progress = 0;
        gtk_widget_hide(GTK_WIDGET(data));
        gtk_widget_hide(GTK_WIDGET(mask));
        g_timeout_add(16, courseAnimation, home_fixed);
        printf("Loading Done!\n");
        return FALSE;
    }
}

void loadingCallback(GtkWidget *loading_bar)
{

    printf("\nLoading\n");
    g_timeout_add(5, progressLoadingBar, loading_bar);
}

void *run(void *data)
{
    paySuccess = 0;

    gtk_init(NULL, NULL);

    // GTK_WINDOW_POPUP         show on the top screen without windows
    // GTK_WINDOW_TOPLEVEL      have windows
    home = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_fullscreen(GTK_WINDOW(home));

    home_fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(home), home_fixed);

    home_background = gtk_image_new_from_file("image/1.png");
    gtk_fixed_put(GTK_FIXED(home_fixed), home_background, 0, 0);

    hoverAnimation.image = gtk_image_new_from_file("image/hover.png");
    gtk_fixed_put(GTK_FIXED(home_fixed), hoverAnimation.image, 0, 0);

    for (int i = 0; i < 8; i++)
    {
        parkingData[i].image = gtk_image_new_from_file("image/deadline.png");
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

    selectbutton.image = gtk_image_new_from_file("image/select.png");
    gtk_fixed_put(GTK_FIXED(home_fixed), selectbutton.image, 0, 0);

    mask = gtk_image_new_from_file("image/loading_mask.png");
    gtk_fixed_put(GTK_FIXED(home_fixed), mask, 0, 0);

    loading_bar = gtk_image_new_from_file("image/loading_bar.png");
    gtk_fixed_put(GTK_FIXED(home_fixed), loading_bar, 143, 1205);

    home_clock_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(home_clock_label), "<span font_desc='50' color='#FFFFFF' weight='bold'>00:00</span>");
    gtk_fixed_put(GTK_FIXED(home_fixed), home_clock_label, 0, 1510);

    g_signal_new("loading",
                 G_TYPE_OBJECT, G_SIGNAL_RUN_FIRST,
                 0, NULL, NULL,
                 g_cclosure_marshal_VOID__POINTER,
                 G_TYPE_NONE, 1, G_TYPE_POINTER);

    g_signal_connect(G_OBJECT(loading_bar), "loading", G_CALLBACK(loadingCallback), NULL);

    g_timeout_add(60000, counter, NULL);

    g_signal_emit_by_name(GTK_WIDGET(loading_bar), "loading");

    gtk_widget_show_all(home);

    selectbutton.opacity = 0;
    gtk_widget_set_opacity(selectbutton.image, selectbutton.opacity);

    hoverAnimation.opacity = 0;
    gtk_widget_set_opacity(hoverAnimation.image, hoverAnimation.opacity);

    selectTimewindwos = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_fullscreen(GTK_WINDOW(selectTimewindwos));

    select_fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(selectTimewindwos), select_fixed);

    select_background = gtk_image_new_from_file("image/2.png");
    gtk_fixed_put(GTK_FIXED(select_fixed), select_background, 0, 0);

    select_hover.image = gtk_image_new_from_file("image/select_time_hover.png");
    gtk_fixed_put(GTK_FIXED(select_fixed), select_hover.image, 15, 800);
    buf = gdk_pixbuf_new_from_file("image/select_time_hover.png", NULL);
    gtk_widget_set_opacity(select_hover.image, 0);

    select_timer.image = gtk_image_new_from_file("image/select_time.png");
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

    payment_background = gtk_image_new_from_file("image/3.png");
    gtk_fixed_put(GTK_FIXED(payment_fixed), payment_background, 0, 0);

    payment_hover.image = gtk_image_new_from_file("image/select_payment.png");
    gtk_fixed_put(GTK_FIXED(payment_fixed), payment_hover.image, 0, 750);
    paymentbuf = gdk_pixbuf_new_from_file("image/select_payment.png", NULL);

    payment_qrcode.image = gtk_image_new_from_file("image/payment_qrcode.png");
    gtk_fixed_put(GTK_FIXED(payment_fixed), payment_qrcode.image, 144, 809);
    gtk_widget_set_opacity(payment_qrcode.image, payment_qrcode.opacity);
    payment_qrcode.opacity = 0;

    payment_card.image = gtk_image_new_from_file("image/payment_card.png");
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

    confirm_background = gtk_image_new_from_file("image/4.png");
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

    confirm_home_button.image = gtk_image_new_from_file("image/home.png");
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

    connection_background = gtk_image_new_from_file("image/5_1.png");
    gtk_fixed_put(GTK_FIXED(connection_fixed), connection_background, 0, 0);

    // create the are we can draw in
    GtkWidget *drawingArea;
    drawingArea = gtk_drawing_area_new();
    gtk_widget_set_size_request(drawingArea, 95, 95);
    gtk_fixed_put(GTK_FIXED(connection_fixed), drawingArea, 550, 700);

    spinnerImage = cairo_image_surface_create_from_png("image/spinner.png");

    g_signal_connect(G_OBJECT(drawingArea), "draw", G_CALLBACK(spinnerAnimation), drawingArea);

    // g_timeout_add(500,  spinnerStart, connectionWindows);
    // gtk_widget_show_all(connectionWindows);

    updateParkingData();
    gtk_main();

    return (int *)data;
}

void startani()
{
    g_signal_emit_by_name(GTK_WIDGET(loading_bar), "loading");
}

gboolean counter(gpointer data)
{
    updateParkingData();
    return TRUE;
}

void updateParkingData()
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
            gtk_image_set_from_file(GTK_IMAGE(parkingData[i].image), "image/deadline.png");
            gtk_widget_show(parkingData[i].image);
            showDeadline(&parkingData[i]);
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
    g_free(timestamp);
}

void showDeadline(ParkingData *data)
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

gboolean courseAnimation(gpointer home_fixed)
{
    static int presstime;
    static int lastStatus;
    gint maxIndex = findMaxArrayIndex(block, 24);
    int status = 0;
    int selectBlockX = ((maxIndex / 2) % 2) * 600 + 20;
    int selectBlockY = ((maxIndex / 2) / 2) * 270 + 30;

    if (SELECT_BLOCK(block[maxIndex]))
    {
        status = maxIndex / 2;
    }
    else
    {
        status = -1;
    }

    if (status > -1 && status < 8)
    {
        if (status == lastStatus)
        {
            presstime++;
            refreshLoadingBerFrame(hoverAnimation.image, (int)(568 * (float)presstime / 80), 40);
        }

        else
        {
            presstime = 1;
            gtk_fixed_move(GTK_FIXED(home_fixed), selectbutton.image, selectBlockX, selectBlockY);

            gtk_fixed_move(GTK_FIXED(home_fixed), hoverAnimation.image, selectBlockX, selectBlockY);
        }
    }

    if (presstime > 80)
    {
        if (parkingData[(status / 2) + ((status) % 2 * 4)].parkingStatus == PARKING_STATUS_PAYMENT)
        {
            gtk_widget_hide(home);
            gtk_widget_show_all(selectTimewindwos);
            g_timeout_add(5, selectTimeAnimation, NULL);
            lastStatus = 12; //防止下一頁位置錯誤
            presstime = 0;
            // printf("[%d] [%d] + [%d] = %d\n", status, (status/2), ((status) % 2 * 4), (status/2) + ((status) % 2 * 4) );
            selectData.selectBlockNum = (status / 2) + ((status) % 2 * 4);
            printf("select block [%d]\n", selectData.selectBlockNum);
            printf("Go to page 2\n");
            return FALSE;
        }
        else
        {
            presstime = 0;
        }
    }

    homeAnimation(&selectbutton, status);
    homeAnimation(&hoverAnimation, status);
    // printf("status [%d]\n", status);
    lastStatus = status;

    return TRUE;
}

void homeAnimation(gbutton *opacityWidget, int status)
{
    if (status > -1 && status < 8 && opacityWidget->opacity < 1)
    {
        opacityWidget->opacity += 0.05;
        gtk_widget_set_opacity(opacityWidget->image, opacityWidget->opacity);
    }
    else if ((status < 0 || status > 7) && opacityWidget->opacity > 0)
    {
        opacityWidget->opacity -= 0.05;
        gtk_widget_set_opacity(opacityWidget->image, opacityWidget->opacity);
    }
    // printf("Opacity: %f\n", opacityopacity);
}

gboolean selectTimeAnimation(gpointer data)
{
    gint maxIndex = findMaxArrayIndex(block, 24);
    static int lastStatus;
    static int presstime;
    int status = 0;
    int selectBlockX;
    int selectBlockY;

    if (SELECT_BLOCK(block[maxIndex]))
    {
        status = maxIndex;
        if (status < 12 || status > 19)
            presstime = 0;
        else
        {
            presstime++;
        }
    }
    else
    {
        status = -1;
        presstime = 0;
    }

    selectBlockX = 15 + (296 * (status % 4));
    selectBlockY = 800 + (315 * ((status - 12) / 4));

    if (status > 11 && status < 20)
    {

        if (status == lastStatus)
        {
            presstime++;
            selectHoverAnimation(select_hover.image, 310 * presstime / 500, 330);
        }
        else
        {
            presstime = 0;
            // printf("\nChoossing block[%d]\nX[%d]\ty[%d]", status, selectBlockX, selectBlockY);
            gtk_fixed_move(GTK_FIXED(select_fixed), select_timer.image, selectBlockX, selectBlockY);

            gtk_fixed_move(GTK_FIXED(select_fixed), select_hover.image, selectBlockX - 14, selectBlockY - 14);

            gtk_fixed_move(GTK_FIXED(select_fixed), select_label.image, selectBlockX + 50, selectBlockY + 95);

            gchar *text_time = g_strdup_printf(
                "<span font_desc='65' color='#FFFFFF' weight='bold'>%d:%02d</span>", ((status + 1) / 2) - 6, ((status + 1) % 2) * 30);

            gtk_label_set_markup(GTK_LABEL(select_label.image), text_time);
        }
    }

    if (presstime > 500)
    {
        presstime = 0;
        select_label.opacity = 0;
        select_hover.opacity = 0;

        selectData.selectTimeHour = ((status + 1) / 2) - 6;
        selectData.selectTimeMinute = ((status + 1) % 2) * 30;

        printf("setting time %d : %d\n", selectData.selectTimeHour, selectData.selectTimeMinute);

        gtk_widget_hide(selectTimewindwos);
        gtk_widget_show_all(paymentWindow);
        g_timeout_add(25, paymentAnimation, NULL);

        printf("Go to page 3\n");
        return FALSE;
    }

    selectHoverOpacityAnimation(&select_hover, status);
    selectHoverOpacityAnimation(&select_label, status);
    lastStatus = status;

    return TRUE;
}

void selectHoverAnimation(GtkWidget *select, int weight, int height)
{
    GdkPixbuf *pixbuf = gdk_pixbuf_scale_simple(buf, weight, height,
                                                GDK_INTERP_NEAREST);

    gtk_image_set_from_pixbuf(GTK_IMAGE(select), pixbuf);
    g_object_unref(pixbuf);
}

void selectHoverOpacityAnimation(gbutton *opacityWidget, int status)
{
    if (status > 11 && status < 20 && opacityWidget->opacity < 1)
    {
        opacityWidget->opacity += 0.005;
        gtk_widget_set_opacity(opacityWidget->image, opacityWidget->opacity);
    }
    else if ((status < 12 || status > 19) && opacityWidget->opacity > 0)
    {
        opacityWidget->opacity -= 0.05;
        gtk_widget_set_opacity(opacityWidget->image, opacityWidget->opacity);
    }
    // printf("Opacity: %f\n", opacityopacity);
}

gboolean paymentAnimation(gpointer data)
{
    static int lastStatus;
    static int presstime;
    gint maxIndex = findMaxArrayIndex(block, 24);
    int status = 0;
    if (SELECT_BLOCK(block[maxIndex]))
    {
        status = maxIndex;
        if (status < 12 || status > 19)
            presstime = 0;
        else
        {
            presstime++;
        }
    }
    else
    {
        status = -1;
        presstime = 0;
    }

    if (status != -1 && status % 4 < 2 && status != lastStatus)
    {
        gtk_fixed_move(GTK_FIXED(payment_fixed), payment_hover.image, 0, 750);
    }
    else if (status != -1 && status % 4 > 1 && status != lastStatus)
    {
        gtk_fixed_move(GTK_FIXED(payment_fixed), payment_hover.image, 600, 750);
    }

    if (presstime == 40)
    {
        presstime = 0;
        selectData.selectPayment = status % 4 > 1;
        changedPayment = 1;
        printf("select payment %d\n", selectData.selectPayment);
        gtk_widget_hide(paymentWindow);
        gtk_widget_show_all(confirmWindow);
        g_timeout_add(100, confirmAnimation, NULL);
        return FALSE;
    }

    if (status != lastStatus)
    {
        paymentHoverAnimation(payment_hover.image, 1, 535);
        presstime = 0;
    }
    else if (presstime != 0 && presstime != 40)
    {
        paymentHoverAnimation(payment_hover.image, 600 * presstime / 40, 535);
    }
    paymentOpacityAnimation(&payment_qrcode, &payment_card, status);

    lastStatus = status;

    return TRUE;
}

void paymentHoverAnimation(GtkWidget *select, int weight, int height)
{

    GdkPixbuf *pixbuf = gdk_pixbuf_scale_simple(paymentbuf, weight, height,
                                                GDK_INTERP_NEAREST);

    gtk_image_set_from_pixbuf(GTK_IMAGE(select), pixbuf);
    g_object_unref(pixbuf);
}

void paymentOpacityAnimation(gbutton *opacityWidgetA, gbutton *opacityWidgetB, int status)
{
    if (status < 20 && status > 11 && status % 4 < 2 && opacityWidgetA->opacity < 1)
    {
        opacityWidgetA->opacity += 0.03;
        gtk_widget_set_opacity(opacityWidgetA->image, opacityWidgetA->opacity);
    }
    else if ((!(status % 4 < 2) || status < 12 || status > 19) && opacityWidgetA->opacity > 0)
    {
        opacityWidgetA->opacity -= 0.05;
        gtk_widget_set_opacity(opacityWidgetA->image, opacityWidgetA->opacity);
    }

    if (status < 20 && status > 11 && status % 4 > 1 && opacityWidgetB->opacity < 1)
    {
        opacityWidgetB->opacity += 0.03;
        gtk_widget_set_opacity(opacityWidgetB->image, opacityWidgetB->opacity);
    }
    else if ((!(status % 4 > 1) || status < 12 || status > 19) && opacityWidgetB->opacity > 0)
    {
        opacityWidgetB->opacity -= 0.05;
        gtk_widget_set_opacity(opacityWidgetB->image, opacityWidgetB->opacity);
    }
}

gboolean confirmAnimation(gpointer data)
{
    static int presstime;
    static int successCount;
    static int connected;
    gint maxIndex = findMaxArrayIndex(block, 24);
    int status = 0;

    int money;

    if (selectData.selectPayment && !connected)
    {
        gtk_image_set_from_file(GTK_IMAGE(connection_background), "image/5_1.png");
        g_timeout_add(500, spinnerStart, connectionWindows);
        gtk_widget_hide(confirmWindow);
        gtk_widget_show_all(connectionWindows);
        connected = 1;
        return FALSE;
    }

    if (changedPayment)
    {
        changedPayment = 0;
        if (selectData.selectPayment)
        {
            gtk_image_set_from_file(GTK_IMAGE(confirm_background), "image/5.png");
            gtk_fixed_move(GTK_FIXED(confirm_fixed), confirm_pay_label, 230, 549);
            gtk_fixed_move(GTK_FIXED(confirm_fixed), confirm_park_label, 544, 549);
            gtk_fixed_move(GTK_FIXED(confirm_fixed), confirm_time_label, 846, 549);
        }
        else
        {
            gtk_image_set_from_file(GTK_IMAGE(confirm_background), "image/4.png");
            gtk_fixed_move(GTK_FIXED(confirm_fixed), confirm_pay_label, 230, 1140);
            gtk_fixed_move(GTK_FIXED(confirm_fixed), confirm_park_label, 544, 1140);
            gtk_fixed_move(GTK_FIXED(confirm_fixed), confirm_time_label, 846, 1140);
        }
    }

    money = 8 * selectData.selectTimeHour + 4 * selectData.selectTimeMinute / 30;

    gchar *text_time = g_strdup_printf(
        "<span font_desc='45' color='#000000'>$ %d</span>", money);
    gtk_label_set_markup(GTK_LABEL(confirm_pay_label), text_time);

    text_time = g_strdup_printf(
        "<span font_desc='45' color='#000000'>%d</span>", parkingData[selectData.selectBlockNum].parkNum);
    gtk_label_set_markup(GTK_LABEL(confirm_park_label), text_time);

    text_time = g_strdup_printf(
        "<span font_desc='45' color='#000000'>%d:%d</span>", selectData.selectTimeHour, selectData.selectTimeMinute);
    gtk_label_set_markup(GTK_LABEL(confirm_time_label), text_time);

    if (SELECT_BLOCK(block[maxIndex]))
    {
        status = maxIndex;
        if (status == 21 || status == 22)
            presstime++;
        else
        {
            presstime = 0;
        }
    }
    else
    {
        status = -1;
        presstime = 0;
    }

    if (presstime > 20 || successCount > 50)
    {
        successCount = 0;
        connected = 0;
        gtk_widget_hide(confirmWindow);
        gtk_widget_show(home);
        updateParkingData();
        g_timeout_add(16, courseAnimation, home_fixed);
        return FALSE;
    }

    if (paySuccess)
    {
        printf("pay Success!\n");
        if (selectData.selectPayment)
        {
            if (connected == 1)
            {
                connected = 2;
                gtk_image_set_from_file(GTK_IMAGE(connection_background), "image/5_3.png");
                g_timeout_add(500, spinnerStart, connectionWindows);
                gtk_widget_hide(confirmWindow);
                gtk_widget_show_all(connectionWindows);
                return FALSE;
            }
            if (paySuccess == 1)
            {
                parkingData[selectData.selectBlockNum].parkingStatus = PARKING_STATUS_DEADLINE;
                struct tm *p;
                parkingData[selectData.selectBlockNum].deadline = time(NULL);
                p = localtime(&parkingData[selectData.selectBlockNum].deadline);
                p->tm_hour += selectData.selectTimeHour;
                p->tm_min += selectData.selectTimeMinute;
                parkingData[selectData.selectBlockNum].deadline = mktime(p);
                gtk_image_set_from_file(GTK_IMAGE(confirm_background), "image/5_4.png");
            }
            else if (paySuccess == 2)
                gtk_image_set_from_file(GTK_IMAGE(confirm_background), "image/5_5.png");
        }
        else
        {
            if (paySuccess == 1)
            {
                parkingData[selectData.selectBlockNum].parkingStatus = PARKING_STATUS_DEADLINE;
                struct tm *p;
                parkingData[selectData.selectBlockNum].deadline = time(NULL);
                p = localtime(&parkingData[selectData.selectBlockNum].deadline);
                p->tm_hour += selectData.selectTimeHour;
                p->tm_min += selectData.selectTimeMinute;
                parkingData[selectData.selectBlockNum].deadline = mktime(p);
                gtk_image_set_from_file(GTK_IMAGE(confirm_background), "image/4_1.png");
            }
            else if (paySuccess == 2)
                gtk_image_set_from_file(GTK_IMAGE(confirm_background), "image/4_2.png");
        }

        gtk_widget_hide(confirm_home_button.image);
        gtk_widget_hide(confirm_park_label);
        gtk_widget_hide(confirm_pay_label);
        gtk_widget_hide(confirm_time_label);
        paySuccess = 0;
        successCount = 1;
    }

    if (successCount)
    {
        successCount++;
    }

    confirmOpacityAnimation(&confirm_home_button, status);
    return TRUE;
}

void confirmOpacityAnimation(gbutton *opacityWidget, int status)
{
    if ((status == 21 || status == 22) && opacityWidget->opacity < 1)
    {
        opacityWidget->opacity += 0.5;
        gtk_widget_set_opacity(opacityWidget->image, opacityWidget->opacity);
    }
    else if (!(status == 21 || status == 22) && opacityWidget->opacity > 0)
    {
        opacityWidget->opacity -= 0.5;
        gtk_widget_set_opacity(opacityWidget->image, opacityWidget->opacity);
    }
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

    ratio += 10;
    // printf("update spinner\n");
    return FALSE;
}

gboolean spinnerStart(gpointer data)
{
    static int skipTime = 0;
    gtk_widget_queue_draw(GTK_WIDGET(data));

    if (skipTime++ >= 10)
    {
        gtk_widget_hide(connectionWindows);
        gtk_widget_show(confirmWindow);
        g_timeout_add(100, confirmAnimation, NULL);
        skipTime = 0;
        return FALSE;
    }

    return TRUE;
}