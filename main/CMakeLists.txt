idf_component_register(SRCS "object/object.c" "object/string_buffer.c" "object/array.c" "app_main.c"
                    INCLUDE_DIRS ".")
target_compile_options(${COMPONENT_LIB} PRIVATE "-Wno-format")
