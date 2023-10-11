
# Hal
file(GLOB_RECURSE HAL_SRCS
    hal/*.c
    hal/*.cpp
)
set(HAL_INCS
    hal/
)

# App
file(GLOB_RECURSE APP_SRCS
    apps/*.c
    apps/*.cpp
)
set(APP_INCS
    apps/
)



idf_component_register(SRCS "main.cpp" ${HAL_SRCS} ${APP_SRCS}
                    INCLUDE_DIRS "." ${HAL_INCS} ${APP_INCS})
