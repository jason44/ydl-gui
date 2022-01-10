#include <gtk/gtk.h>
//#include <adwaita.h>
#include<libhandy-1/handy.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dlp-gui.h"
#include <pthread.h>


/*void shutdown(AdwApplication *app, gpointer user_data){
        free(user_data);
}*/
void activate(GtkApplication *app, gpointer user_data){
        printf("%s\n", ((Options*)user_data)->save_directory);
        // Window

        GtkWidget *window = gtk_application_window_new(app);
        gtk_window_set_title(GTK_WINDOW(window), "dlp-gui");
        gtk_window_set_default_size(GTK_WINDOW(window), 600, 450);
        
        // Boxes
        GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
        GtkWidget *top_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 15);
        GtkWidget *mid_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
        GtkWidget *downl_bin = adw_bin_new();
        GtkWidget *save_row = adw_preferences_group_new();
        GtkWidget *save_row_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);

        GtkWidget *opt_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);

        // Boxes append
        gtk_window_set_child(GTK_WINDOW(window), box);
        gtk_box_append(GTK_BOX(box), top_box);
        gtk_box_append(GTK_BOX(box), mid_box);
        gtk_box_append(GTK_BOX(box), downl_bin);
        adw_preferences_group_add(ADW_PREFERENCES_GROUP(save_row), save_row_box);
        gtk_list_box_append(GTK_LIST_BOX(save_row), save_row_box);
        gtk_box_append(GTK_BOX(box), opt_box);

        // Boxes edit
        gtk_box_set_spacing(GTK_BOX(box), 15);
        adw_preferences_group_set_title(ADW_PREFERENCES_GROUP(save_row), "Save Folder");
        gtk_widget_set_margin_start(save_row_box, 20);
        //gtk_box_set_homogeneous(GTK_BOX(save_row_box), true);

        // Headerbar
        *GtkWidget *headerbar = adw_header_bar_new();
        gtk_window_set_titlebar(GTK_WINDOW(window), headerbar);
        GtkWidget *menubutton = adw_button_content_new();
        adw_button_content_set_icon_name(ADW_BUTTON_CONTENT(menubutton), "Menu");
        adw_button_content_set_label(ADW_BUTTON_CONTENT(menubutton), "Options");
        adw_header_bar_pack_start(ADW_HEADER_BAR(headerbar), menubutton); 

        // Entry
        GtkWidget *entry = gtk_entry_new();
        gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "URL");
        gtk_widget_set_hexpand(entry, true);
        gtk_widget_set_margin_start(entry, 20);
        gtk_widget_set_margin_end(entry, 20);
        gtk_widget_set_margin_top(entry, 25);
        ((Options*)user_data)->entry_p = entry;
        gtk_box_append(GTK_BOX(top_box), entry);


        // Download button
        GtkWidget *button = gtk_button_new_with_label("Download");
        adw_bin_set_child(ADW_BIN(downl_bin), button);
        gtk_widget_set_halign(button, GTK_ALIGN_CENTER);
        gtk_widget_set_margin_start(button, 175);
        gtk_widget_set_margin_end(button, 175);
        gtk_widget_show (window);

         // Download bar
        GtkWidget *pro_bar = gtk_progress_bar_new();
        gtk_progress_bar_set_pulse_step(GTK_PROGRESS_BAR(pro_bar), 1.0);
        gtk_box_append(GTK_BOX(mid_box), pro_bar);
        gtk_widget_set_hexpand(pro_bar, true);
        gtk_widget_set_margin_start(pro_bar, 70);
        gtk_widget_set_margin_end(pro_bar, 70);
        gtk_widget_set_visible(pro_bar, false);
        g_signal_connect_swapped(button, "clicked", G_CALLBACK(download_bar), pro_bar);
        g_signal_connect(button, "clicked", G_CALLBACK(ytdlp_active), user_data);
       
        // File Chooser
        GtkWidget *file_chooser = gtk_file_chooser_dialog_new("Choose Save Directory", 
                                                        GTK_WINDOW(window),
                                                        GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER,
                                                        ("_Cancel"),
                                                        GTK_RESPONSE_CANCEL,
                                                        ("_Select"),
                                                        GTK_RESPONSE_ACCEPT,
                                                        NULL);
        gtk_file_chooser_set_create_folders(GTK_FILE_CHOOSER(file_chooser), true);
        g_signal_connect(file_chooser, "response", G_CALLBACK(choose_folder), user_data);
        // gtk_widget_show(file_chooser);

        // Save Folder Frame
        GtkWidget *save_frame = gtk_frame_new(((Options*)user_data)->save_directory);
        // gtk_widget_set_size_request(save_frame, 400, 16);
        gtk_widget_set_hexpand(save_frame, true);
        GtkLabel *t_label = gtk_label_new("Location where the file will be saved");
        gtk_frame_set_label_widget(GTK_FRAME(save_frame), t_label);
        ((Options*)user_data)->save_frame_p = save_frame;
        gtk_box_append(GTK_BOX(save_row_box), save_frame); 
        gtk_box_append(GTK_BOX(save_row_box), save_frame); 

        // File Chooser button
        GtkWidget *button4 = gtk_button_new_with_label("Choose Folder");
        gtk_widget_set_margin_start(button4, 2);
        gtk_widget_set_margin_end(button4, 100);
        //gtk_box_append(GTK_BOX(save_row_box), button4);
        gtk_box_append(GTK_BOX(save_row_box), button4); 
        g_signal_connect_swapped(button4, "clicked", G_CALLBACK(gtk_widget_show), file_chooser);

        g_signal_connect(file_chooser, "response", G_CALLBACK(set_save_dir_buffer), user_data);

}

void choose_folder(GtkFileChooserDialog *dialog, int response, gpointer data){
        printf("%s\n", ((Options*)data)->save_directory);
        if (response == GTK_RESPONSE_ACCEPT){
                GFile *file_save_dir = gtk_file_chooser_get_file(GTK_FILE_CHOOSER(dialog));
                //free(((Options*)data)->save_directory);
                ((Options*)data)->save_directory = g_file_get_path(file_save_dir);
                printf("%s\n", ((Options*)data)->save_directory);
                g_object_unref(file_save_dir);
        }
        gtk_widget_hide(GTK_WIDGET(dialog));
}
void set_save_dir_buffer(GtkWidget *dialog, int response, gpointer data){
        if (response == GTK_RESPONSE_ACCEPT){
                gtk_frame_set_label(GTK_FRAME(((Options*)data)->save_frame_p), ((Options*)data)->save_directory);
        }
}

void ytdlp_active(GtkWidget *widget, gpointer data){
        bool valid;
        GtkEntryBuffer *buffer = gtk_entry_get_buffer(GTK_ENTRY(((Options*)data)->entry_p));
        const char *URL = gtk_entry_buffer_get_text(buffer); // don't free 
        // **** user_data not passed in yet
        const char *save_path = gtk_frame_get_label(GTK_FRAME(((Options*)data)->save_frame_p));
        printf("%s\n", save_path);
        if (sizeof(URL) < sizeof(char)){
		valid = false;
                return;
	}
        else {
                char cmd[120] = "python3 yt-dlp -f \"bv*[ext=mp4]+ba[ext=m4a]/b[ext=mp4] / bv*+ba/b\" ";
                int sys_res = system(strcat(cmd, URL));
                printf("%i\n", sys_res);
                if (sys_res == 0){
                        valid = true;
                        printf("TRUELMNSDLF\n");
                }
                else {
                        valid = false;
                        printf("FALJLELJRLK\n");
                        return;
                }
        }
        if (valid == true){
                return;
        }
        g_object_unref(buffer);
}

 void download_bar(GtkWidget *widget, gpointer data){
        //static int i = 0;
        if (gtk_widget_is_visible(widget) == false){
                gtk_widget_set_visible(widget, true);
                //while ()
                pthread_t t1;
                int tc1 = pthread_create(&t1, NULL, gtk_progress_bar_pulse, GTK_PROGRESS_BAR(widget));
                //gtk_progress_bar_pulse(GTK_PROGRESS_BAR(widget));
                pthread_join(t1, NULL);
        }
        else {
                gtk_widget_set_visible(widget, false);
        }
        return;
} 

 
