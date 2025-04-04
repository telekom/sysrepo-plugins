cxx = meson.get_compiler('cpp')

libyang = dependency('libyang', version: '>=2.0')
libyang_cpp = dependency('libyang-cpp', version: '>=alpha')
libsysrepo = dependency('sysrepo', version: '>=2.0')
libsysrepo_cpp = dependency('sysrepo-cpp', version: '>=alpha')

libsensors = dependency('libsensors', required : false)
if not libsensors.found()
    libsensors = cxx.find_library('libsensors', required : true)
endif

thread_dep = dependency('threads')

find_program('lshw', required : true)

inc = include_directories('utils')
shared_library('ietf-hardware-plugin', 'ietf-hardware-plugin.cpp',
                include_directories : inc,
                dependencies : [libyang, libyang_cpp, libsysrepo, libsysrepo_cpp, libsensors, thread_dep],
                install : true,
                install_dir : get_option('prefix'))