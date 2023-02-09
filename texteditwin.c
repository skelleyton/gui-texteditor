#include <gtk/gtk.h>

#include "textedit.h"
#include "texteditwin.h"

struct _TextEditWindow {
  GtkApplicationWindow parent;
};

G_DEFINE_TYPE(TextEditWindow, text_edit_window, GTK_TYPE_APPLICATION_WINDOW);

static void text_edit_window_init (TextEditWindow *app) {}

static void text_edit_window_class_init (TextEditWindowClass *class) {}

TextEditWindow *text_edit_window_new (TextEdit *app) {
  return g_object_new (TEXT_EDIT_WINDOW_TYPE, "application", app, NULL);
}

void text_edit_window_open (TextEditWindow *win, GFile *file){}
