file(GLOB BLE_FILES BLE/*.c)
idf_component_register(SRCS "app_main.c" ${BLE_FILES} 
                    INCLUDE_DIRS ".")
target_link_libraries(${COMPONENT_LIB} merry)
target_compile_options(${COMPONENT_LIB} PRIVATE "-Wno-format")
