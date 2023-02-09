#ifndef __TEXTEDIT_H
#define __TEXTEDIT_H

#include <gtk/gtk.h>

#define TEXT_EDIT_TYPE (text_edit_get_type ())
G_DECLARE_FINAL_TYPE (TextEdit, text_edit, TEXT, EDIT, GtkApplication)

TextEdit *text_edit_new (void);

#endif /* __TEXTEDIT_H */
