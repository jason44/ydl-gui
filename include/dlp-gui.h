#include <gtk/gtk.h>
//#include <adwaita.h>
#include <libhandy-1/handy.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#ifndef DLP_GUI
#define DLP_GUI

enum Quality{
    WORST, 
    BEST
};

typedef struct _Options{
    char *save_directory;
    enum Quality quality;
    GtkWidget* save_frame_p;
    GtkWidget* entry_p;
} Options;

//void shutdown(AdwApplication *app, gpointer user_data);

// Application 
void activate(GtkApplication *app, gpointer user_data);

// Save directory
void choose_folder(GtkFileChooserDialog *dialog, int response, gpointer user_data);
void set_save_dir_buffer(GtkWidget *dialog, int response, gpointer user_data);

// Download Button & Bar
void ytdlp_active(GtkWidget *widget, gpointer data);
void download_bar(GtkWidget *widget, gpointer data);

#endif

