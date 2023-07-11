#include <gtk/gtk.h>
#include <webkit2/webkit2.h>

static void go_button_clicked(GtkButton *button, gpointer user_data) {
    GtkEntry *search_bar = GTK_ENTRY(user_data);
    const gchar *url = gtk_entry_get_text(search_bar);

    if (g_str_has_prefix(url, "http://") || g_str_has_prefix(url, "https://")) {
        webkit_web_view_load_uri(WEBKIT_WEB_VIEW(user_data), url);
    } else {
        gchar *search_url = g_strdup_printf("https://www.google.com/search?q=%s", url);
        webkit_web_view_load_uri(WEBKIT_WEB_VIEW(user_data), search_url);
        g_free(search_url);
    }
}

static void back_button_clicked(GtkButton *button, gpointer user_data) {
    webkit_web_view_go_back(WEBKIT_WEB_VIEW(user_data));
}

static void forward_button_clicked(GtkButton *button, gpointer user_data) {
    webkit_web_view_go_forward(WEBKIT_WEB_VIEW(user_data));
}

static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Web Browser");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);

    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    GtkWidget *search_bar = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(search_bar), "Search Google");
    gtk_grid_attach(GTK_GRID(grid), search_bar, 0, 0, 1, 1);

    GtkWidget *go_button = gtk_button_new_with_label("GO");
    gtk_grid_attach(GTK_GRID(grid), go_button, 1, 0, 1, 1);

    GtkWidget *back_button = gtk_button_new_with_label("<");
    gtk_grid_attach(GTK_GRID(grid), back_button, 2, 0, 1, 1);

    GtkWidget *forward_button = gtk_button_new_with_label(">");
    gtk_grid_attach(GTK_GRID(grid), forward_button, 3, 0, 1, 1);

    GtkWidget *webkit_view = webkit_web_view_new();
    gtk_grid_attach(GTK_GRID(grid), webkit_view, 0, 1, 4, 1);

    g_signal_connect(go_button, "clicked", G_CALLBACK(go_button_clicked), search_bar);
    g_signal_connect(back_button, "clicked", G_CALLBACK(back_button_clicked), webkit_view);
    g_signal_connect(forward_button, "clicked", G_CALLBACK(forward_button_clicked), webkit_view);

    gtk_widget_show_all(window);
}

int main(int argc, char *argv[]) {
    GtkApplication *app = gtk_application_new("com.example.webbrowser", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}
