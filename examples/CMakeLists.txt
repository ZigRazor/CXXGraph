option(EXAMPLES "Enable Examples Compilation" OFF)
if(EXAMPLES)

add_subdirectory(DialExample)
add_subdirectory(DijkstraExample)
add_subdirectory(NetworkDynamicsExample)
add_subdirectory(PartitionExample)
add_subdirectory(PrimExample)

endif(EXAMPLES)