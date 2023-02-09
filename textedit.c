#include <gtk/gtk.h>

#include "textedit.h"
#include "texteditwin.h"

struct _TextEdit {
  GtkApplication parent;
};

G_DEFINE_TYPE(TextEdit, text_edit, GTK_TYPE_APPLICATION);

static void text_edit_init (TextEdit *app){

}

static void text_edit_activate (GApplication *app) {
  TextEditWindow *win;

  win = text_edit_window_new (TEXT_EDIT (app));
  gtk_window_present (GTK_WINDOW (win));
}

static void text_edit_open (GApplication *app, GFile **files, int n_files, const char *hint) {
  GList *windows;
  TextEditWindow *win;
  int i;

  windows = gtk_application_get_windows (GTK_APPLICATION (app));
  if (windows) {
    win = TEXT_EDIT_WINDOW (windows->data);
  } else {
    win = text_edit_window_new (TEXT_EDIT (app));
  }

  for (i = 0; i < n_files; i++) {
    text_edit_window_open (win, files[i]);
  }

  gtk_window_present (GTK_WINDOW (win));
}

static void text_edit_class_init (TextEditClass *class) {
  G_APPLICATION_CLASS (class)->activate = text_edit_activate;
  G_APPLICATION_CLASS (class)->open = text_edit_open;
}

TextEdit *text_edit_new (void) {
  return g_object_new (TEXT_EDIT_TYPE, "application-id", "org.skelleyton.textedit", "flags", G_APPLICATION_HANDLES_OPEN, NULL);
}
