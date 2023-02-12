#include <gtk/gtk.h>

#include "textedit.h"
#include "texteditwin.h"

struct _TextEditWindow {
  GtkApplicationWindow parent;

  GSettings *settings;
  GtkWidget *stack;
  GtkWidget *menu;
};

G_DEFINE_TYPE(TextEditWindow, text_edit_window, GTK_TYPE_APPLICATION_WINDOW)

static void text_edit_window_init (TextEditWindow *win) {
  GtkBuilder *builder;
  GMenuModel *menu;

  gtk_widget_init_template (GTK_WIDGET (win));

  builder = gtk_builder_new_from_resource ("/org/kelleynet/textedit/menu.ui");
  menu = G_MENU_MODEL (gtk_builder_get_object (builder, "menu"));
  gtk_menu_button_set_menu_model (GTK_MENU_BUTTON (win->menu), menu);
  g_object_unref(builder);

  win->settings = g_settings_new ("org.kelleynet.textedit");
  g_settings_bind (win->settings, "transition", win->stack, "transition-type", G_SETTINGS_BIND_DEFAULT);
}

static void text_edit_window_dispose (GObject *object) {
  TextEditWindow *win;
  win = TEXT_EDIT_WINDOW (object);
  g_clear_object (&win->settings);
  G_OBJECT_CLASS (text_edit_window_parent_class)->dispose (object);
}

static void text_edit_window_class_init (TextEditWindowClass *class) {
  G_OBJECT_CLASS (class)->dispose = text_edit_window_dispose;

  gtk_widget_class_set_template_from_resource (GTK_WIDGET_CLASS (class), "/org/kelleynet/textedit/window.ui");
  gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS (class), TextEditWindow, stack);
  gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS (class), TextEditWindow, menu);
}

TextEditWindow *text_edit_window_new (TextEdit *app) {
  return g_object_new (TEXT_EDIT_WINDOW_TYPE, "application", app, NULL);
}

void text_edit_window_open (TextEditWindow *win, GFile *file){
  char *basename;
  GtkWidget *scrolled, *view;
  char *contents;
  gsize length;
  GtkTextBuffer *buffer;
  GtkTextTag *tag;
  GtkTextIter start_iter, end_iter;

  basename = g_file_get_basename (file);

  scrolled = gtk_scrolled_window_new ();
  gtk_widget_set_hexpand (scrolled, TRUE);
  gtk_widget_set_vexpand (scrolled, TRUE);
  view = gtk_text_view_new ();
  gtk_text_view_set_editable (GTK_TEXT_VIEW (view), FALSE);
  gtk_text_view_set_cursor_visible (GTK_TEXT_VIEW (view), FALSE);
  gtk_scrolled_window_set_child (GTK_SCROLLED_WINDOW (scrolled), view);
  gtk_stack_add_titled (GTK_STACK (win->stack), scrolled, basename, basename);

  buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (view));

  if (g_file_load_contents (file, NULL, &contents, &length, NULL, NULL)) {

    gtk_text_buffer_set_text (buffer, contents, length);
    g_free (contents);
  }

  tag = gtk_text_buffer_create_tag (buffer, NULL, NULL);
  g_settings_bind (win->settings, "font", tag, "font", G_SETTINGS_BIND_DEFAULT);

  gtk_text_buffer_get_start_iter (buffer, &start_iter);
  gtk_text_buffer_get_end_iter (buffer, &end_iter);
  gtk_text_buffer_apply_tag (buffer, tag, &start_iter, &end_iter);

  g_free (basename);
}
