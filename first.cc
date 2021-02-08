#include <gtk/gtk.h>

int main(int argc, char *argv[]) {

  GtkWidget *window;
  GtkWidget *vbox;

  GtkWidget *menubar;
  GtkWidget *fileMenu;
  GtkWidget *editMenu;
  GtkWidget *formatMenu;
  GtkWidget *fileMi;
  GtkWidget *editMi;
  GtkWidget *formatMi;
  GtkWidget *saveMi;
  GtkWidget *exitMi;
  GtkWidget *copyMi;
  GtkWidget *pasteMi;
  GtkWidget *deleteMi;
  GtkWidget *asciiMi;
  GtkWidget *ansiMi;
  GtkWidget *utf8Mi;
  GtkWidget *sep;

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), 500, 400);
  gtk_window_set_title(GTK_WINDOW(window), "GTK Editor");

  vbox = gtk_vbox_new(FALSE, 0);
  gtk_container_add(GTK_CONTAINER(window), vbox);

  menubar = gtk_menu_bar_new();
  fileMenu = gtk_menu_new();
  editMenu = gtk_menu_new();
  formatMenu = gtk_menu_new();

  fileMi = gtk_menu_item_new_with_label("File");
  editMi = gtk_menu_item_new_with_label("Edit");
  formatMi = gtk_menu_item_new_with_label("Format");
  saveMi = gtk_menu_item_new_with_label("Save");
  exitMi = gtk_menu_item_new_with_label("Exit");
  copyMi = gtk_menu_item_new_with_label("Copy");
  pasteMi = gtk_menu_item_new_with_label("Paste");
  deleteMi = gtk_menu_item_new_with_label("Delete");
  asciiMi = gtk_menu_item_new_with_label("ASCii");
  ansiMi = gtk_menu_item_new_with_label("ANSI");
  utf8Mi = gtk_menu_item_new_with_label("UTF-8");
  sep = gtk_separator_menu_item_new();  

  gtk_menu_item_set_submenu(GTK_MENU_ITEM(fileMi), fileMenu);
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(editMi), editMenu);
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(formatMi), formatMenu);
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
  gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 0);

  g_signal_connect(G_OBJECT(window), "destroy",G_CALLBACK(gtk_main_quit), NULL);

  g_signal_connect(G_OBJECT(exitMi), "activate", G_CALLBACK(gtk_main_quit), NULL);

  gtk_widget_show_all(window);

  gtk_main();

  return 0;
}
