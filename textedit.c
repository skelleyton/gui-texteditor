#include <gtk/gtk.h>
#include <stdio.h>

#include "textedit.h"
#include "texteditwin.h"
#include "texteditprefs.h"

struct _TextEdit {
  GtkApplication parent;
};

G_DEFINE_TYPE(TextEdit, text_edit, GTK_TYPE_APPLICATION);

static void text_edit_init (TextEdit *app){

}

static void quit_activated (GSimpleAction *action, GVariant *paramemter, gpointer app) {
  g_application_quit (G_APPLICATION (app));
}

static void preferences_activated (GSimpleAction *action, GVariant *parameter, gpointer app) {
  TextEditPrefs *prefs;
  GtkWindow *win;

  win = gtk_application_get_active_window (GTK_APPLICATION (app));
  prefs = text_edit_prefs_new (TEXT_EDIT_WINDOW (win));
  gtk_window_present (GTK_WINDOW (prefs));
}

static GActionEntry app_entries[] = {
  { "preferences", preferences_activated, NULL, NULL, NULL },
  { "quit", quit_activated, NULL, NULL, NULL }
};

static void text_edit_startup (GApplication *app) {
  GtkBuilder *builder;
  const char *quit_accels[2] = { "<Ctrl>Q", NULL };

  G_APPLICATION_CLASS (text_edit_parent_class)->startup (app);

  g_action_map_add_action_entries (G_ACTION_MAP (app), app_entries, G_N_ELEMENTS (app_entries), app);
  gtk_application_set_accels_for_action (GTK_APPLICATION (app), "app.quit", quit_accels);
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
  G_APPLICATION_CLASS (class)->startup = text_edit_startup;
  G_APPLICATION_CLASS (class)->activate = text_edit_activate;
  G_APPLICATION_CLASS (class)->open = text_edit_open;
}

TextEdit *text_edit_new (void) {
  return g_object_new (TEXT_EDIT_TYPE, "application-id", "org.kelleynet.textedit", "flags", G_APPLICATION_HANDLES_OPEN, NULL);
}
