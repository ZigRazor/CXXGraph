option(EXAMPLES "Enable Examples Compilation" OFF)
if(EXAMPLES)

add_subdirectory(DialExample)
add_subdirectory(DijkstraExample)
add_subdirectory(PartitionExample)

endif(EXAMPLES)