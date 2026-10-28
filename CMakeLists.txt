cmake_minimum_required(VERSION 3.16)

project(practica3_potencia_pr
        VERSION 1.0.0
        DESCRIPTION "Potencia como funcion primitiva recursiva"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Tipo de compilacion" FORCE)
endif()

# ---------------------------------------------------------------------------
# Libreria con el nucleo de funciones primitivas recursivas
# ---------------------------------------------------------------------------
add_library(pr_core
    src/FuncionPR.cpp
    src/FuncionesBasicas.cpp
    src/Composicion.cpp
    src/RecursionPrimitiva.cpp
    src/PotenciaPR.cpp
    src/AnalizadorArgumentos.cpp
)

target_include_directories(pr_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(pr_core PRIVATE -Wall -Wextra -Wpedantic)
endif()

# ---------------------------------------------------------------------------
# Programa principal
# ---------------------------------------------------------------------------
add_executable(potencia_pr src/main.cpp)
target_link_libraries(potencia_pr PRIVATE pr_core)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(potencia_pr PRIVATE -Wall -Wextra -Wpedantic)
endif()

# ---------------------------------------------------------------------------
# Pruebas
# ---------------------------------------------------------------------------
enable_testing()
add_executable(pruebas_pr tests/pruebas.cpp)
target_link_libraries(pruebas_pr PRIVATE pr_core)
add_test(NAME pruebas_pr COMMAND pruebas_pr)