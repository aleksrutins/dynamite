project('dynamite', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3', 'cpp_std=c++14'])

srcs = [
  'dynamite.cc',
  'plugin.cc',
]

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

shlib = shared_library('dynamite', srcs,
  install : false,
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
