cmake_minimum_required(VERSION 3.1)

file(GLOB mpi_function_files mpi_funcs/*.c mpi_funcs/*.h)

add_executable(mpi-interceptor-bin
  mpi_interceptor.c
)

target_include_directories(mpi-interceptor-bin
  PRIVATE
    ${MPI_C_INCLUDE_PATH}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(mpi_pythia SHARED
  pythia.cpp
)

target_link_libraries(mpi_pythia
  PUBLIC
    eta_factorizer
  PRIVATE
    ${MPI_CXX_LIBRARIES}
)

add_library(mpi-interceptor SHARED
  ${mpi_function_files}
  mpi.c
  mpi3_f.f90
  fortran_utils.f90
  mpi_f.f90
  mpi_fortran.c
  openMP.c
)

target_include_directories(mpi-interceptor
  PRIVATE
    ${MPI_C_INCLUDE_PATH}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(mpi-interceptor
  PUBLIC
  dl
  PRIVATE
    mpi_pythia
    ${MPI_Fortran_LIBRARIES}
    ${MPI_C_LIBRARIES}
)

target_compile_options(mpi-interceptor
  PRIVATE
    -Wall -Wextra -Wpedantic
    -DUSE_MPI3
    ${MPI_COMPILE_FLAGS}
)

set_target_properties(mpi-interceptor
  PROPERTIES LINK_FLAGS
  ${MPI_LINK_FLAGS}
)

#----------------------------------------------------

install(TARGETS mpi-interceptor
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(TARGETS mpi_pythia
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

set_target_properties(mpi-interceptor-bin
        PROPERTIES OUTPUT_NAME mpi_interceptor)

install(TARGETS mpi-interceptor-bin
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
