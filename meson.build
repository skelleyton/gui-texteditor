project('textedit', 'c',
  version : '0.1',
  default_options : ['warning_level=3'])

gnome = import('gnome')

gtk_dep = dependency('gtk4')

texteditresources = gnome.compile_resources(
  'resources',
  'textedit.gresource.xml',
  source_dir: './',
  c_name: 'textedit'
)

texteditschema = gnome.compile_schemas()

executable('textedit',
           'main.c',
           'textedit.c',
           'texteditwin.c',
           'texteditprefs.c',
           texteditresources,
           texteditschema,
           dependencies: gtk_dep,
           install : true)
