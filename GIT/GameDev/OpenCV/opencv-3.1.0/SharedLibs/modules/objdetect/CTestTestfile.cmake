# CMake generated Testfile for 
# Source directory: /Users/Dmitri/Desktop/Programming/opencv-3.1.0/modules/objdetect
# Build directory: /Users/Dmitri/Desktop/Programming/opencv-3.1.0/SharedLibs/modules/objdetect
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(opencv_perf_objdetect "/Users/Dmitri/Desktop/Programming/opencv-3.1.0/SharedLibs/bin/opencv_perf_objdetect" "--gtest_output=xml:opencv_perf_objdetect.xml")
set_tests_properties(opencv_perf_objdetect PROPERTIES  LABELS "Main;opencv_objdetect;Performance" WORKING_DIRECTORY "/Users/Dmitri/Desktop/Programming/opencv-3.1.0/SharedLibs/test-reports/performance")
add_test(opencv_sanity_objdetect "/Users/Dmitri/Desktop/Programming/opencv-3.1.0/SharedLibs/bin/opencv_perf_objdetect" "--gtest_output=xml:opencv_perf_objdetect.xml" "--perf_min_samples=1" "--perf_force_samples=1" "--perf_verify_sanity")
set_tests_properties(opencv_sanity_objdetect PROPERTIES  LABELS "Main;opencv_objdetect;Sanity" WORKING_DIRECTORY "/Users/Dmitri/Desktop/Programming/opencv-3.1.0/SharedLibs/test-reports/sanity")
