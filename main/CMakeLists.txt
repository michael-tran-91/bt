idf_component_register(SRCS "app_main.c"
                    INCLUDE_DIRS ".")
target_link_libraries(${COMPONENT_LIB} merry)
target_compile_options(${COMPONENT_LIB} PRIVATE "-Wno-format")
