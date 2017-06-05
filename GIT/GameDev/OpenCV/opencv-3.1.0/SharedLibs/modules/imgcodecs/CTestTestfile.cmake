# CMake generated Testfile for 
# Source directory: /Users/Dmitri/Desktop/Programming/opencv-3.1.0/modules/imgcodecs
# Build directory: /Users/Dmitri/Desktop/Programming/opencv-3.1.0/SharedLibs/modules/imgcodecs
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(opencv_perf_imgcodecs "/Users/Dmitri/Desktop/Programming/opencv-3.1.0/SharedLibs/bin/opencv_perf_imgcodecs" "--gtest_output=xml:opencv_perf_imgcodecs.xml")
set_tests_properties(opencv_perf_imgcodecs PROPERTIES  LABELS "Main;opencv_imgcodecs;Performance" WORKING_DIRECTORY "/Users/Dmitri/Desktop/Programming/opencv-3.1.0/SharedLibs/test-reports/performance")
add_test(opencv_sanity_imgcodecs "/Users/Dmitri/Desktop/Programming/opencv-3.1.0/SharedLibs/bin/opencv_perf_imgcodecs" "--gtest_output=xml:opencv_perf_imgcodecs.xml" "--perf_min_samples=1" "--perf_force_samples=1" "--perf_verify_sanity")
set_tests_properties(opencv_sanity_imgcodecs PROPERTIES  LABELS "Main;opencv_imgcodecs;Sanity" WORKING_DIRECTORY "/Users/Dmitri/Desktop/Programming/opencv-3.1.0/SharedLibs/test-reports/sanity")
