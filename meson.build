project('ps64', 'cpp')

sources = [
    'src/machine_memory/machine_memory_slice.cpp',
    'src/machine_memory/machine_memory.cpp',
    'src/machine/machine.cpp',
    'src/utils/args/arg_slice.cpp',
    'src/machine_core/machine_core.cpp',
    'src/core_executor/core_executor.cpp',
    'src/core_executor/asm_functions.cpp'
]

# Dependency for spdlog
fmt = dependency('fmt')


argtable3 = subproject('argtable3')
argtable3_dep = argtable3.get_variable('argtable3_dep')

spdlog = subproject('spdlog', default_options: {'compile_library': true})
spdlog_dep = spdlog.get_variable('spdlog_dep')


inc_dirs = include_directories('include')

exe = executable('p64',
           sources: sources + ['src/main.cpp'],
           include_directories : inc_dirs,
           dependencies : [argtable3_dep, spdlog_dep],
           install: true
)

test_sources = [
    'tests/test_setup.cpp'
]


gtest = subproject('gtest')
gtest_dep = gtest.get_variable('gtest_dep')


test_executable = executable('p64_tests',
                 sources: sources + test_sources,
                 include_directories : inc_dirs,
                 dependencies : [argtable3_dep, spdlog_dep, gtest_dep],
                 install: true
)

test('gtest', test_executable, protocol: 'gtest')
