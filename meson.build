project('result', 'cpp',
  version : '0.1.0',
  default_options : [
    'warning_level=3',
    'cpp_std=c++20',
    'buildtype=debug',
    'cpp_args=-D_FORTIFY_SOURCE=2,-Wall,-Wextra,-pedantic,-Werror'
  ]
)

inc = include_directories('.')

examples = [
  'and_then',
  'arithmetic',
  'complex_data',
  'error_codes',
  'file_operation',
  'or_else',
  'transform'
]

if get_option('buildtype') == 'debug'
  cpp_args = ['-O1', '-g']
else
  cpp_args = ['-O3', '-DNDEBUG']
endif

foreach example : examples
  exe = executable(example,
    'examples/' + example + '.cpp',
    include_directories : inc,
    install : false,  # Don't install to system
    cpp_args : cpp_args
  )
  test(example, exe)
endforeach
