# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
cmake_minimum_required (VERSION 3.8)

project (UnitTestSnippets)

# Projeleri organize ederken dizinleri kullanmayi seciyioruz
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Tepe Cmake dosyasinda C++ standardini eklyelim
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# GTesti sisteme kurmaya gerek yok 
# Diger ayarlar icin https://github.com/google/googletest/blob/master/CMakeLists.txt goz atabilirsiniz
set(INSTALL_GTEST OFF)

# Windows uzerinde calisma zamani hatalarini almamak icin bunu ekliyoruz.
# Varsayılan olarak, yeni Visual Studio projeleri C çalışma zamanlarını dinamik olarak birbirine bağlar 
# ancak GoogleTest bunları statik olarak bağlar. Bu durumda asağıdakine benzer hatalar alabilirsiniz:
# "error LNK2038: mismatch detected for 'RuntimeLibrary': value 'MT_StaticRelease' doesn't match value 'MD_DynamicRelease'"
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Include sub-projects.
add_subdirectory (function_tracker)
add_subdirectory (test)
add_subdirectory (googletest-master)

set_target_properties(gtest PROPERTIES FOLDER Ext/gtest)
set_target_properties(gmock PROPERTIES FOLDER Ext/gtest)
set_target_properties(gmock_main PROPERTIES FOLDER Ext/gtest)
set_target_properties(gtest_main PROPERTIES FOLDER Ext/gtest)