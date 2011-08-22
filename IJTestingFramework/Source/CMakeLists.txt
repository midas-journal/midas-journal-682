INCLUDE( ${CMAKE_SOURCE_DIR}/IJMacros.txt )

PROJECT( IJTestingFramework )

CMAKE_MINIMUM_REQUIRED( VERSION 2.6 )

#The following lines are required to use Dart
ENABLE_TESTING()
INCLUDE( CTest )


SET(BUILDNAME "${BUILDNAME}-${PROJECT_NAME}" CACHE STRING "Name of build on the dashboard")

OPTION(BUILD_SHARED_LIBS "Build IJTestingFramework with shared libraries." OFF)


INCLUDE_DIRECTORIES ( "${PROJECT_SOURCE_DIR}/utilities" "${PROJECT_BINARY_DIR}/utilities" "${PROJECT_BINARY_DIR}")
ADD_SUBDIRECTORY ( utilities/FileUtilities )
ADD_SUBDIRECTORY ( utilities/TestingFramework )
ADD_SUBDIRECTORY ( utilities/itktf )

#Declare any external dependencies that your project may have here.
#examples include: ITK, VTK, JPEG, PNG, OpenGL, ZLIB, Perl, Java
#If you're not sure what name to use, look in the Modules directory of your
#cmake install and check that a file named Find(Package).cmake exists
#
# The packages can be specified with a version number, for example:
#
# ITK 2.8.1
# ITK 3.2.0
#
# We need any version of ITK
SET(Required_Packages
ITK
)

#this foreach loads all of the packages that you specified as required.
#It shouldn't need to be modified.
FOREACH(Package ${Required_Packages})
  LOADPACKAGE(${Package})
ENDFOREACH(Package)


SET ( IJ_REGRESSION_OUTPUT_DIR "${IJTestingFramework_BINARY_DIR}/Testing/Temporary" )
SET ( IJ_REGRESSION_XML_BASELINE "${IJTestingFramework_SOURCE_DIR}/Testing/XML" )
SET ( IJ_REGRESSION_DATA_BASELINE "${IJTestingFramework_SOURCE_DIR}/Testing/Data" )

ADD_EXECUTABLE( tfPipeToXML tfPipeToXML.cxx )
TARGET_LINK_LIBRARIES( tfPipeToXML itksys testingframework )

ADD_EXECUTABLE( itktfShiftScaleInPlaceImageFilterTest itktfShiftScaleInPlaceImageFilterTest.cxx  )
TARGET_LINK_LIBRARIES( itktfShiftScaleInPlaceImageFilterTest testingframework ITKBasicFilters ITKIO itktf )
ADD_TEST( itktfShiftScaleInPlaceImageFilterTest ${EXECUTABLE_OUTPUT_PATH}/itktfShiftScaleInPlaceImageFilterTest -I ${IJ_REGRESSION_XML_BASELINE}/itktfShiftScaleInPlaceImageFilterTest.xml )
