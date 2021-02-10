#include <gtk/gtk.h>

//Function invoked when copy option is used
void copy_to_clipboard(GtkWidget *widget, GtkTextBuffer *buffer){
  GtkClipboard *clipboard;
  clipboard = gtk_clipboard_get(GDK_NONE);
  gtk_text_buffer_copy_clipboard(buffer, clipboard);
}

//Function invoked when paste option is used
void paste_from_clipboard(GtkWidget *widget, GtkTextBuffer *buffer){
  GtkClipboard *clipboard;
  clipboard = gtk_clipboard_get(GDK_NONE);
  gtk_text_buffer_paste_clipboard(buffer, clipboard,NULL,TRUE);
}


int main(int argc, char *argv[]) {

	//Definitions
	GtkWidget *window;
	GtkWidget *vbox;
	GtkWidget *menubar;
	GtkWidget *fileMenu;
	GtkWidget *editMenu;
	GtkWidget *formatMenu;
	GtkWidget *fileMi;
	GtkWidget *editMi;
	GtkWidget *formatMi;
	GtkWidget *openMi;
	GtkWidget *saveMi;
	GtkWidget *exitMi;
	GtkWidget *copyMi;
	GtkWidget *pasteMi;
	GtkWidget *deleteMi;
	GtkWidget *asciiMi;
	GtkWidget *ansiMi;
	GtkWidget *utf8Mi;
	GtkWidget *sep;
	GtkWidget *text_view;
	GtkWidget *scrolled_window;
	GtkTextBuffer *buffer;

	//initialize our gtk engine
	gtk_init(&argc, &argv);

	//properties for the main window
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(window), 500, 400);
	gtk_window_set_title(GTK_WINDOW(window), "GTK Editor");

	//Setting up vbox
	vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
	gtk_container_add(GTK_CONTAINER(window), vbox);

	//initialize menu bar
	menubar = gtk_menu_bar_new();
	fileMenu = gtk_menu_new();
	editMenu = gtk_menu_new();
	formatMenu = gtk_menu_new();

	// Setting File Menu //
	//initialize file menu and define file items in it
	fileMi = gtk_menu_item_new_with_label("File");
	editMi = gtk_menu_item_new_with_label("Edit");
	formatMi = gtk_menu_item_new_with_label("Format");
	openMi = gtk_menu_item_new_with_label("Open");
	saveMi = gtk_menu_item_new_with_label("Save");
	exitMi = gtk_menu_item_new_with_label("Exit");
	copyMi = gtk_menu_item_new_with_label("Copy");
	pasteMi = gtk_menu_item_new_with_label("Paste");
 	deleteMi = gtk_menu_item_new_with_label("Delete");
	asciiMi = gtk_menu_item_new_with_label("ASCii");
	ansiMi = gtk_menu_item_new_with_label("ANSI");
	utf8Mi = gtk_menu_item_new_with_label("UTF-8");
	sep = gtk_separator_menu_item_new();  

	//linking menu and its respective menu items
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(fileMi), fileMenu);
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(editMi), editMenu);
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(formatMi), formatMenu);
	gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), openMi);
	gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), saveMi);
	gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), sep);
	gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), exitMi);
	gtk_menu_shell_append(GTK_MENU_SHELL(editMenu), copyMi);
	gtk_menu_shell_append(GTK_MENU_SHELL(editMenu), pasteMi);
	gtk_menu_shell_append(GTK_MENU_SHELL(editMenu), deleteMi);
	gtk_menu_shell_append(GTK_MENU_SHELL(formatMenu), asciiMi);
	gtk_menu_shell_append(GTK_MENU_SHELL(formatMenu), ansiMi);
	gtk_menu_shell_append(GTK_MENU_SHELL(formatMenu), utf8Mi);
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), fileMi);
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), editMi);
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), formatMi);

	//connecting layout of verticalbox to menubar
	gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 0);

	//Initializing scrolledwindows
	scrolled_window = gtk_scrolled_window_new(NULL,NULL);

	//Initializing textviewer and displaying it.
	text_view = gtk_text_view_new ();
	gtk_container_set_border_width (GTK_CONTAINER (scrolled_window), 5);
	gtk_container_add(GTK_CONTAINER(scrolled_window),text_view);
	gtk_box_pack_start (GTK_BOX (vbox), scrolled_window, 1, 1, 0);

	// Initializing buffer
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
//	buffer = gtk_text_buffer_new (NULL);
//	text_view = gtk_text_view_new_with_buffer (buffer);
	gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW (text_view), GTK_WRAP_WORD); 

	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC); 


	//connect functions to events that is signalled by gtk
	g_signal_connect(G_OBJECT(window), "destroy",G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(G_OBJECT(exitMi), "activate", G_CALLBACK(gtk_main_quit), NULL);


	g_signal_connect(G_OBJECT(copyMi),"activate", G_CALLBACK(copy_to_clipboard),buffer);
	g_signal_connect(G_OBJECT(pasteMi),"activate", G_CALLBACK(paste_from_clipboard),buffer);
	// display all the windows and enter into event loop
	gtk_widget_show_all(window);
	gtk_main();

	return 0;
}
