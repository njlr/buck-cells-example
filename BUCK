cxx_binary(
  name = 'example',
  header_namespace = '',
  headers = subdir_glob([
    ('include', '**/*.hpp'),
  ]),
  srcs = glob([
    'src/**/*.cpp',
  ]),
  compiler_flags = [
    '-std=c++14',
  ],
  deps = [
    'neither//:neither',
  ],
)
