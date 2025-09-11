option(PYTHON_BINDINGS "Enable Python Bindings Compilation" OFF)
if(PYTHON_BINDINGS)

add_subdirectory(bindings)


endif(PYTHON_BINDINGS)