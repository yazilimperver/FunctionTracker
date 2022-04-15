cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (function_tracker "main.cpp"  "function_tracker.h")

# Bu projeyi VS icerisinde ayri bir folderda tutalim
set_target_properties(function_tracker PROPERTIES FOLDER Library)
