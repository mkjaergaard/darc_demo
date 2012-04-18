include_directories(include)
include_directories(/usr/include/opencv-2.3.1)
include_directories(${darc_INCLUDE_DIRS})
include_directories(${ROS_INCLUDE_DIRS})

add_library(OpenCVTestComponent SHARED src/opencv_img_file_component.cpp src/cv_bridge.cpp)
target_link_libraries(OpenCVTestComponent ${darc_LIBRARIES} ${ROS_LIBRARIES} -lopencv_core -lopencv_highgui -lopencv_imgproc)

add_executable(OpenCVImgFileComponentNode src/opencv_img_file_component.cpp src/cv_bridge.cpp src/opencv_node.cpp)
target_link_libraries(OpenCVImgFileComponentNode ${darc_LIBRARIES} ${ROS_LIBRARIES} -lopencv_core -lopencv_highgui -lopencv_imgproc)

#darc_pybindings(OpenCVImgFileComponent src/my_subscriber_component.cpp)
