file (GLOB APP_SOURCES RELTIVE ${CMAKE_CURRENT_SOURCE_DIR} *.c)

add_library(malloc_dbg malloc_dbg.c)

foreach( testsourcefile ${APP_SOURCES})
  string( REPLACE ".c" "" testname ${testsourcefile})
  string( REPLACE ".C" "" testname ${testname})
  string( REPLACE " " "_" testname ${testname})

  if ("${testsourcefile}" STREQUAL "malloc_dbg.c")
    continue()
  endif()

  add_executable( ${testname} ${testsourcefile} )
  
  if ("${testname}" STREQUAL "test_malloc_dbg")
    target_link_libraries(${testname} malloc_dbg)
  endif()

  if(OpenMP_C_FOUND)
    target_link_libraries(${testname} OpenMP::OpenMP_C)
  endif()
    
  if(MATH_LIBRARY)
    target_link_libraries(${testname} ${MATH_LIBRARY})
  endif()

  install(TARGETS ${testname} DESTINATION "bin/developer_tool")

endforeach(testsourcefile ${APP_SOURCES})
