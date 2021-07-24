SET(Sources
        glUtils.cpp

        )

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS}")
add_library(ThirdOpengl STATIC ${Sources})