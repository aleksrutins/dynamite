project('dynamite', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3', 'cpp_std=c++14'])

# These arguments are only used to build the shared library
# not the executables that use the library.
lib_args = [
  '-DBUILDING_DYNAMITE',
  '-fvisibility=hidden',
  '-fPIC',
  '-Wl,-Bstatic',
  '-Wl,-Bdynamic',
  '-Wl,--as-needed',
  '-shared'
]

cc = meson.get_compiler('cpp')

lv2peg = find_program('lv2peg')

peg = custom_target('dynamite.peg', 
  output: 'dynamite.peg',
  input: 'dynamite.ttl',
  command: [lv2peg, '@INPUT@', '@OUTPUT@'],
  install: false
)

srcs = [
  'dynamite.cc',
  'plugin.cc',
  peg
]

shlib = shared_library('dynamite', srcs,
  install : true,
  install_dir : 'lib64/lv2/dynamite.lv2',
  cpp_args : lib_args,
  gnu_symbol_visibility : 'hidden',
  name_prefix : '',
  dependencies : [
    dependency('lv2'),
    dependency('lv2-plugin'),
    cc.find_library('m'),
    dependency('threads')
  ]
)

guilib = shared_library('dynamite_gui', ['gui.cc', peg],
  install: true,
  install_dir: 'lib64/lv2/dynamite.lv2',
  cpp_args: lib_args,
  gnu_symbol_visibility: 'hidden',
  name_prefix: '',
  dependencies: [
    dependency('lv2'),
    dependency('lv2-plugin'),
    dependency('lv2-gui'),
    dependency('threads'),
    dependency('gtkmm-2.4')
  ]
)

install_data(['manifest.ttl', 'dynamite.ttl'], install_dir: 'lib64/lv2/dynamite.lv2')

# test_exe = executable('dynamite_test', 'dynamite_test.cpp',
#  link_with : shlib)
# test('dynamite', test_exe)

# Make this library usable as a Meson subproject.
#dynamite_dep = declare_dependency(
#  include_directories: include_directories('.'),
#  link_with : shlib)

# Make this library usable from the system's11
# package manager.
# install_headers('dynamite.hpp', subdir : 'dynamite')

# pkg_mod = import('pkgconfig')
# pkg_mod.generate(
#   name : 'dynamite',
#   filebase : 'dynamite',
#   description : 'Meson sample project.',
#   subdirs : 'dynamite',
#   libraries : shlib,
#   version : '0.1',
# )
