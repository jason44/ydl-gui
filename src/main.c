#include <gtk/gtk.h>
#include <adwaita.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dlp-gui.h"

int main (int argc, char **argv) {
		// yt-dlp options
		Options *options_list = (Options*)malloc(sizeof(struct _Options));
		if (options_list == NULL){return 1;}

		options_list->save_directory = "$HOME/Downloads"; // not allocated with alloc so don't need to free manually
		printf("%sHAHAHLOLOLOL\n", options_list->save_directory);
		char *trash_var = options_list->save_directory;

		GtkApplication *app;
		app = adw_application_new("com.github.jason44", G_APPLICATION_FLAGS_NONE);
		g_signal_connect (app, "activate", G_CALLBACK(activate), options_list);
		//g_signal_connect (app, "shutdown", G_CALLBACK(shutdown), options_list);
		
		int status = g_application_run(G_APPLICATION(app), argc, argv);
		
		printf("%s\n", trash_var);
		if (options_list->save_directory != trash_var){
			free(options_list->save_directory);
		} 
		free(options_list);
		g_object_unref(app);
		return status;
}
