#ifndef __TEXTEDITWIN_H
#define __TEXTEDITWIN_H

#include <gtk/gtk.h>

#include "textedit.h"

#define TEXT_EDIT_WINDOW_TYPE (text_edit_window_get_type ())
G_DECLARE_FINAL_TYPE (TextEditWindow, text_edit_window, TEXT, EDIT_WINDOW, GtkApplicationWindow)

TextEditWindow *text_edit_window_new (TextEdit *app);

void text_edit_window_open (TextEditWindow *win, GFile *file);

#endif /* __TEXTEDITWIN_H */
