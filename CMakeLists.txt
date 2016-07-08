#                          Implementation of the papers
#
#                "Exact Acceleration of Linear Object Detectors"
#               12th European Conference on Computer Vision, 2012.
#
#             "Deformable Part Models with Individual Part Scaling"
#                  24th British Machine Vision Conference, 2013.
#
#      Copyright (c) 2013 Idiap Research Institute, <http://www.idiap.ch/>
#              Written by Charles Dubout <charles.dubout@idiap.ch>

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(FFLD)
SET(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/" ${CMAKE_MODULE_PATH})

# The build options
OPTION(FFLD_HOGPYRAMID_DOUBLE "Use doubles instead of floats (slower, uses twice more memory, and the increase in precision is not necessarily useful)." ON)
OPTION(FFLD_HOGPYRAMID_EXTRA_FEATURES "Use extra features (LBP + color) in addition to HOG." OFF)
OPTION(FFLD_MODEL_3D "Allow parts to also deform across scales." OFF)
OPTION(FFLD_MIXTURE_STANDARD_CONVOLUTION "Use standard convolutions instead of the optimized Fourier ones." OFF)
OPTION(BUILD_TEST_LIB "Build a test using lib" ON)

# Select a default build configuration if none was chosen
IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build, options are: None (CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel." FORCE)
ENDIF()

# Also list the headers so that they are displayed along the .cpp files in the IDE
SET(HEADERS lib/ffld2.h HOGPyramid.h Intersector.h JPEGImage.h LBFGS.h Mixture.h Model.h Object.h Patchwork.h Rectangle.h Scene.h)
SET(SOURCES lib/ffld2.cpp HOGPyramid.cpp JPEGImage.cpp LBFGS.cpp Mixture.cpp Model.cpp Object.cpp Patchwork.cpp Rectangle.cpp Scene.cpp)

# Add a library version of the software that we can link against
ADD_LIBRARY(ffld2 SHARED ${HEADERS} ${SOURCES} )

# Define the options
IF(FFLD_HOGPYRAMID_DOUBLE)
  MESSAGE("Use doubles instead of floats.")
  ADD_DEFINITIONS(-DFFLD_HOGPYRAMID_DOUBLE)
ENDIF()

IF(FFLD_HOGPYRAMID_EXTRA_FEATURES)
  MESSAGE("Use extra features (LBP + color) in addition to HOG.")
  ADD_DEFINITIONS(-DFFLD_HOGPYRAMID_EXTRA_FEATURES)
ENDIF()

IF(FFLD_MODEL_3D)
  MESSAGE("Allow parts to also deform across scales.")
  ADD_DEFINITIONS(-DFFLD_MODEL_3D)
ENDIF()

IF(FFLD_MIXTURE_STANDARD_CONVOLUTION)
  MESSAGE("Use standard convolutions instead of the optimized Fourier ones.")
  ADD_DEFINITIONS(-DFFLD_MIXTURE_STANDARD_CONVOLUTION)
ENDIF()

# The FindEigen3.cmake and FindFFTW.cmake are copied from Eigen3
FIND_PACKAGE(Eigen3 REQUIRED)
add_definitions     ( ${EIGEN3_DEFINITIONS} )
INCLUDE_DIRECTORIES(${EIGEN3_INCLUDE_DIR})

FIND_PACKAGE(FFTW REQUIRED)
INCLUDE_DIRECTORIES(${FFTW_INCLUDES})
IF(FFLD_HOGPYRAMID_DOUBLE)
  TARGET_LINK_LIBRARIES(ffld2 ${FFTW_LIB})
ELSE()
  TARGET_LINK_LIBRARIES(ffld2 ${FFTWF_LIB})
ENDIF()


# Not required, but stronlgy recommended on multi-core systems
FIND_PACKAGE(OpenMP)
IF(OPENMP_FOUND)
  SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
  SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_C_FLAGS}")
ENDIF()

IF(BUILD_TEST_LIB)
  ADD_EXECUTABLE(testlib lib/ffld2.h testlib.cpp)
  FIND_PACKAGE(OpenCV)
  INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIRS})
  TARGET_LINK_LIBRARIES( testlib ${OpenCV_LIBS})
  TARGET_LINK_LIBRARIES( testlib ffld2)
ENDIF()
