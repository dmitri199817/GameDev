# CMake generated Testfile for 
# Source directory: /Users/Dmitri/Desktop/Programming/opencv-3.1.0/modules/photo
# Build directory: /Users/Dmitri/Desktop/Programming/opencv-3.1.0/SharedLibs/modules/photo
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(opencv_perf_photo "/Users/Dmitri/Desktop/Programming/opencv-3.1.0/SharedLibs/bin/opencv_perf_photo" "--gtest_output=xml:opencv_perf_photo.xml")
set_tests_properties(opencv_perf_photo PROPERTIES  LABELS "Main;opencv_photo;Performance" WORKING_DIRECTORY "/Users/Dmitri/Desktop/Programming/opencv-3.1.0/SharedLibs/test-reports/performance")
add_test(opencv_sanity_photo "/Users/Dmitri/Desktop/Programming/opencv-3.1.0/SharedLibs/bin/opencv_perf_photo" "--gtest_output=xml:opencv_perf_photo.xml" "--perf_min_samples=1" "--perf_force_samples=1" "--perf_verify_sanity")
set_tests_properties(opencv_sanity_photo PROPERTIES  LABELS "Main;opencv_photo;Sanity" WORKING_DIRECTORY "/Users/Dmitri/Desktop/Programming/opencv-3.1.0/SharedLibs/test-reports/sanity")
