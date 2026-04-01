cmake_minimum_required(VERSION 3.10)
project(RayTracing)

set(CMAKE_CXX_STANDARD 17)

# 添加选项，允许用户手动关闭 AVX2
option(ENABLE_AVX2 "Enable AVX2 instruction set" ON)

find_package(OpenMP REQUIRED)

add_executable(RayTracing main.cpp Object.hpp Vector.cpp Vector.hpp Sphere.hpp global.hpp Triangle.hpp Scene.cpp
        Scene.hpp Light.hpp AreaLight.hpp BVH.cpp BVH.hpp Bounds3.hpp Ray.hpp Material.hpp Intersection.hpp
        Renderer.cpp Renderer.hpp)

target_link_libraries(RayTracing OpenMP::OpenMP_CXX)

# 根据编译器添加 AVX2 编译标志
if(ENABLE_AVX2)
    if(MSVC)
        target_compile_options(RayTracing PRIVATE /arch:AVX2 /arch:SSE)
    else()
        # GCC / Clang / Intel 等通用选项
        target_compile_options(RayTracing PRIVATE -mavx2 -msse)
    endif()
endif()