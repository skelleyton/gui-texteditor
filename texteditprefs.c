#include <gtk/gtk.h>

#include "textedit.h"
#include "texteditwin.h"
#include "texteditprefs.h"

struct _TextEditPrefs {
  GtkDialog parent;

  GSettings *settings;
  GtkWidget *font;
  GtkWidget *transition;
};

G_DEFINE_TYPE (TextEditPrefs, text_edit_prefs, GTK_TYPE_DIALOG);

static void text_edit_prefs_init (TextEditPrefs *prefs) {
  gtk_widget_init_template (GTK_WIDGET (prefs));
  prefs->settings = g_settings_new ("org.gtk.exampleapp");

  g_settings_bind (prefs->settings, "font", prefs->font, "font", G_SETTINGS_BIND_DEFAULT);
  g_settings_bind (prefs->settings, "transition", prefs->transition, "active-id", G_SETTINGS_BIND_DEFAULT);
}

static void text_edit_prefs_dispose (GObject *object) {
  TextEditPrefs *prefs;

  prefs = TEXT_EDIT_PREFS (object);
  g_clear_object (&prefs->settings);
  G_OBJECT_CLASS (text_edit_prefs_parent_class)->dispose (object);
}

static void text_edit_prefs_class_init (TextEditPrefsClass *class) {
  G_OBJECT_CLASS (class)->dispose = text_edit_prefs_dispose;

  gtk_widget_class_set_template_from_resource (GTK_WIDGET_CLASS (class), "/org/kelleynet/textedit/preferences.ui");
  gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS (class), TextEditPrefs, font);
  gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS (class), TextEditPrefs, transition);
}

TextEditPrefs *text_edit_prefs_new (TextEditWindow *win) {
  return g_object_new (TEXT_EDIT_PREFS_TYPE, "transient-for", win, "use-header-bar", TRUE, NULL);
}
