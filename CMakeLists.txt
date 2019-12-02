add_definitions(-DUNICODE -D_UNICODE)
set(CMAKE_CXX_FLAGS_RELEASE "/MD")
include_directories("C:/Program Files/Windows Kits/10/Include/um" "C:/Program Files/Windows Kits/10/Include/shared"
  "d:/Program Files/Microsoft DirectX SDK (June 2010)/Include" "e:/usr/include")
link_directories("D:/Program Files/Microsoft DirectX SDK (June 2010)/Lib/x86" "e:/usr/lib"  "e:/usr/lib/boost")
add_executable(main main.cpp mypaint.cpp util.cpp)
add_library(imgui STATIC imgui.cpp imgui_demo.cpp imgui_draw.cpp
  imgui_widgets.cpp imgui_impl_dx11.cpp imgui_impl_win32.cpp image.cpp )
add_library(mylua STATIC mylua.cpp)
add_library(util STATIC util.cpp)
target_link_libraries(main imgui d3d11 d3dcompiler lua_static mylua fmt util)
add_executable(test test.cpp)
add_library(bg STATIC bg.cpp)
target_link_libraries(test bg fmt "libboost_thread-vc141-mt-x32-1_71")
