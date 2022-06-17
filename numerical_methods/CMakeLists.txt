file( GLOB APP_SOURCE RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.c)

set (NEED
    "newton_rapshon_root.c"
)

foreach ( testsourcefile ${APP_SOURCES} )
    if ( ${testsourcefile} IN_LIST NEED_COMPLEX AND NOT HAS_COMPLEX_TYPE)
        continue()
    endif()
    string( REPLACE ".c" "" testname ${testsourcefile} )
    string( REPLACE ".C" "" testname ${testname} )
    string( REPLACE " " "_" testname ${testname} )
    add_executable( ${testname} ${testsourcefile} )

    if (OpenMP_C_FOUND)
        target_link_libraries(${testname} OpenMP:OpenMP_C)
    endif()

    if(MATH_LIBRARY)
        target_link_libraries(${testname} ${MATH_LIBRARY})
    endif()
    install(TARGETS ${testname} DESTINATION "bin/numerical_methods")
endforeach( testsourcefile ${APP_SOURCES})

