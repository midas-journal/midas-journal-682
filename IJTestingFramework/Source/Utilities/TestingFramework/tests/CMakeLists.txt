
SET ( TESTINGFRAMEWORK_XML_BASELINE ${CMAKE_CURRENT_SOURCE_DIR}/xml )
SET ( TESTINGFRAMEWORK_DATA_BASELINE ${CMAKE_CURRENT_SOURCE_DIR}/data )

CONFIGURE_FILE("${TESTINGFRAMEWORK_SOURCE_DIR}/tests/tfTestSupport.h.in"
  "${TESTINGFRAMEWORK_BINARY_DIR}/tfTestSupport.h" IMEDIATE) 

#create the testing file and list of tests
CREATE_TEST_SOURCELIST ( TestingFrameworkTests1_SRC
  tfTests1.cxx
  tfHeaderTest.cxx  
)

# create the testing file and list of tests
# these tests utilize XML comparison
CREATE_TEST_SOURCELIST ( TestingFrameworkTests2_SRC
  tfTests2.cxx    
  tfRegressionTestOutputTest1.cxx
  tfRegressionTestOutputTest2.cxx
  tfRegressionTestTest1.cxx
  tfRegressionTestTest2.cxx
  tfRegressionTestTest3.cxx
  tfRegressionTestTest4.cxx
)

INCLUDE_DIRECTORIES( ${TESTINGFRAMEWORK_SOURCE_DIR} )

ADD_EXECUTABLE( tfTests1 ${TestingFrameworkTests1_SRC} )
TARGET_LINK_LIBRARIES (tfTests1 testingframework fileutil )

ADD_EXECUTABLE( tfTests2 ${TestingFrameworkTests2_SRC} )
TARGET_LINK_LIBRARIES (tfTests2 testingframework fileutil )


SET ( TESTINGFRAMEWORK_TEST1 ${EXECUTABLE_OUTPUT_PATH}/tfTests1 )

SET ( TestsToRun ${TestingFrameworkTests1_SRC} )
REMOVE ( TestsToRun tfTests1.cxx ) 
FOREACH ( test ${TestsToRun} )
  GET_FILENAME_COMPONENT ( TName ${test} NAME_WE )
  ADD_TEST ( ${TName} ${TESTINGFRAMEWORK_TEST1} ${TName} )
ENDFOREACH ( test )


SET ( TESTINGFRAMEWORK_TEST2 ${EXECUTABLE_OUTPUT_PATH}/tfTests2 )

SET ( TestsToRun ${TestingFrameworkTests2_SRC} )
REMOVE ( TestsToRun tfTests2.cxx ) 
FOREACH ( test ${TestsToRun} )
  GET_FILENAME_COMPONENT ( TName ${test} NAME_WE )

  # This is the line which executes the test it also set the input XML file
  ADD_TEST ( ${TName} ${TESTINGFRAMEWORK_TEST2} ${TName} -I ${TESTINGFRAMEWORK_XML_BASELINE}/${TName}.xml )
ENDFOREACH ( test )

