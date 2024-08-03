project('p64', 'c')

sources = [
    'src/main.c',
]

argtable3 = subproject('argtable3')
argtable3_dep = argtable3.get_variable('argtable3_dep')

inc_dirs = include_directories('include')

executable('p64', 
           sources,
           include_directories : inc_dirs,
           dependencies : [argtable3_dep],
           install: true
)