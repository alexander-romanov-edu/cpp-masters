project(
  'bunifdef',
  'cpp',
  default_options: ['cpp_std=c++23', 'warning_level=3'],
)

string_twine_headers_dep = declare_dependency(
  include_directories: include_directories('include'),
)
boost_dep = dependency(
  'boost',
  modules: ['program_options'],
  required: true,
)

concat_args = executable(
  'concat',
  ['concat.cpp'],
  install: true,
  dependencies: [boost_dep, string_twine_headers_dep],
)

gtest_dep = dependency(
  'gtest',
  main: true,
  required: get_option('build_tests'),
)

if get_option('build_tests')
  subdir('tests')
endif

if get_option('build_benchmarks')
  subdir('benchmarks')
endif
