#ifndef __TEXTEDITPREFS_H
#define __TEXTEDITPREFS_H

#include <gtk/gtk.h>

#include "texteditwin.h"

#define TEXT_EDIT_PREFS_TYPE (text_edit_prefs_get_type ())
G_DECLARE_FINAL_TYPE (TextEditPrefs, text_edit_prefs, TEXT, EDIT_PREFS, GtkDialog)

TextEditPrefs *text_edit_prefs_new (TextEditWindow *win);

#endif /* __TEXTEDITPREFS_H*/
