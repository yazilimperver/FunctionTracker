# Kaynak kod dosyalari
set(SOURCE_FILES function_tracker_tests.cpp main.cpp)
set(HEADER_FILES class_under_test.h dummy_service.h function_tracker_stub.h function_tracker_tests.h)

# Baslik dosyalarini ayri tutma kararimiz isiginda ilgili dosyalari ekleyelim
set(INCLUDE_FOLDER "${UnitTestSnippets_SOURCE_DIR}/function_tracker")

# Test calistirilabilir dosyamiz
add_executable(function_tracker_test ${SOURCE_FILES} ${HEADER_FILES})

# Kaynak dosyalarini nereden bulacagimizi belirleyelim
target_include_directories(function_tracker_test PUBLIC ${INCLUDE_FOLDER})

# Google test kutuphanelerini ekleyelim
target_link_libraries(function_tracker_test gtest)

# Bu projeyi VS icerisinde ayri bir folderda tutalim
set_target_properties(function_tracker_test PROPERTIES FOLDER Test)