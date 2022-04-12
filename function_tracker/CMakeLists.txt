cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (function_tracker_app "main.cpp"  "function_tracker.h")

# Bu projeyi VS icerisinde ayri bir folderda tutalim
set_target_properties(function_tracker_app PROPERTIES FOLDER Library)
