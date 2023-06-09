project('raylib-meson', 'c', 'cpp')

cc = meson.get_compiler('c')
cxx = meson.get_compiler('cpp')

c_args = ['-Wall', '-Wextra', '-Ofast']
debug_args = ['Wall', '-Wextra', '-g']
link_args = []
name_suffix = []
dependencies = []

# Raylib configuration
cmake = import('cmake')
raylib_opts = cmake.subproject_options()
raylib_opts.set_install(false)
raylib_opts.add_cmake_defines({
  'BUILD_EXAMPLES': 'OFF',
  # Add other CMake options for Raylib, if needed
})
if cc.get_id() == 'emscripten'
  raylib_opts.add_cmake_defines({
    'PLATFORM': 'Web',
  })
else
  raylib_opts.add_cmake_defines({
    'PLATFORM': 'Desktop',
  })
endif
raylib_subproject = cmake.subproject('raylib', options: raylib_opts)
dependencies += raylib_subproject.dependency('raylib')

# General configuration
if host_machine.system() == 'windows'
  dependencies += [
    cc.find_library('winmm'),
  ]
elif host_machine.system() == 'darwin'
  # TODO
elif host_machine.system() == 'linux'
  dependencies += [
    cc.find_library('m'),
    cc.find_library('dl'),
  ]
elif host_machine.system() == 'emscripten'
  link_args += [
    '-s', 'ENVIRONMENT=web',
    '-s', 'USE_GLFW=3',
  ]
  name_suffix = 'html'
endif

# Project files
inc_dir = include_directories(
  'src',
  'src/cells',
  'src/cells/sand',
  'src/cells/water',
  'src/cells/wood',
  'src/cells/fire',
)

sources = files(
  'src/main.c',
  'src/constants.h',
  'src/cells/sand/sand.c',
  'src/cells/water/water.c',
  'src/cells/wood/wood.c',
  'src/cells/cell.c',
  'src/cells/fire/fire.c',
  'src/utils.c',
)

executable('raylib-meson',
  sources,
  c_args: c_args,
  dependencies: dependencies,
  include_directories: inc_dir,
  link_args: link_args,
  name_suffix: name_suffix,
)

