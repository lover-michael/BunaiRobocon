add_executable(target.out main.cpp)

#ターゲットにライブラリをlinkする
target_link_libraries(target.out module)