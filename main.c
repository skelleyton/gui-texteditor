#include <gtk/gtk.h>

#include "textedit.h"

int main (int argc, char **argv) {
  return g_application_run (G_APPLICATION (text_edit_new ()), argc, argv);
}
