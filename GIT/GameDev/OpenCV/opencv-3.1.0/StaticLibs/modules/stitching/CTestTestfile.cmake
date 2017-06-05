# CMake generated Testfile for 
# Source directory: /Users/Dmitri/Desktop/Programming/opencv-3.1.0/modules/stitching
# Build directory: /Users/Dmitri/Desktop/Programming/opencv-3.1.0/StaticLibs/modules/stitching
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(opencv_perf_stitching "/Users/Dmitri/Desktop/Programming/opencv-3.1.0/StaticLibs/bin/opencv_perf_stitching" "--gtest_output=xml:opencv_perf_stitching.xml")
set_tests_properties(opencv_perf_stitching PROPERTIES  LABELS "Main;opencv_stitching;Performance" WORKING_DIRECTORY "/Users/Dmitri/Desktop/Programming/opencv-3.1.0/StaticLibs/test-reports/performance")
add_test(opencv_sanity_stitching "/Users/Dmitri/Desktop/Programming/opencv-3.1.0/StaticLibs/bin/opencv_perf_stitching" "--gtest_output=xml:opencv_perf_stitching.xml" "--perf_min_samples=1" "--perf_force_samples=1" "--perf_verify_sanity")
set_tests_properties(opencv_sanity_stitching PROPERTIES  LABELS "Main;opencv_stitching;Sanity" WORKING_DIRECTORY "/Users/Dmitri/Desktop/Programming/opencv-3.1.0/StaticLibs/test-reports/sanity")
