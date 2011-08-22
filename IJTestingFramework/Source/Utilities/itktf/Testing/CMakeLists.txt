
IF(COMMAND cmake_policy)
  CMAKE_POLICY(SET CMP0003 NEW)
ENDIF(COMMAND cmake_policy)

ADD_EXECUTABLE( itktfMeasurementFileImageInsightTest1 itktfMeasurementFileImageInsightTest1.cxx )
TARGET_LINK_LIBRARIES( itktfMeasurementFileImageInsightTest1 testingframework ITKBasicFilters ITKIO itktf )
ADD_TEST( itktfMeasurementFileImageInsightTest1 ${EXECUTABLE_OUTPUT_PATH}/itktfMeasurementFileImageInsightTest1 -I ${ITK_REGRESSION_XML_BASELINE}/itktfMeasurementFileImageInsightTest1.xml )


ADD_EXECUTABLE( itktfMeasurementFileImageInsightTest2 itktfMeasurementFileImageInsightTest2.cxx )
TARGET_LINK_LIBRARIES( itktfMeasurementFileImageInsightTest2 testingframework ITKBasicFilters ITKIO itktf )
ADD_TEST( itktfMeasurementFileImageInsightTest2 ${EXECUTABLE_OUTPUT_PATH}/itktfMeasurementFileImageInsightTest2 -I ${ITK_REGRESSION_XML_BASELINE}/itktfMeasurementFileImageInsightTest2.xml )


ADD_EXECUTABLE( itktfMeasurementFileImageInsightTest3 itktfMeasurementFileImageInsightTest3.cxx )
TARGET_LINK_LIBRARIES( itktfMeasurementFileImageInsightTest3 testingframework ITKBasicFilters ITKIO itktf )
ADD_TEST( itktfMeasurementFileImageInsightTest3 ${EXECUTABLE_OUTPUT_PATH}/itktfMeasurementFileImageInsightTest3 -I ${ITK_REGRESSION_XML_BASELINE}/itktfMeasurementFileImageInsightTest3.xml )


ADD_EXECUTABLE( itktfMeasurementFileImageInsightTest4 itktfMeasurementFileImageInsightTest4.cxx )
TARGET_LINK_LIBRARIES( itktfMeasurementFileImageInsightTest4 testingframework ITKBasicFilters ITKIO itktf )
ADD_TEST( itktfMeasurementFileImageInsightTest4 
  ${EXECUTABLE_OUTPUT_PATH}/itktfMeasurementFileImageInsightTest4 
  -I ${ITK_REGRESSION_XML_BASELINE}/itktfMeasurementFileImageInsightTest4.xml 
  ${ITK_REGRESSION_DATA_BASELINE}/vm_head_coronal.jpg
  ${ITK_REGRESSION_OUTPUT_DIR}/itktfMeasurementFileImageInsightTest4.mha
  )

ADD_EXECUTABLE( itktfMeasurementInsightRegionTest itktfMeasurementInsightRegionTest.cxx  )
TARGET_LINK_LIBRARIES( itktfMeasurementInsightRegionTest testingframework ITKBasicFilters ITKIO itktf )
ADD_TEST( itktfMeasurementInsightRegionTest 
  ${EXECUTABLE_OUTPUT_PATH}/itktfMeasurementInsightRegionTest 
  -I ${ITK_REGRESSION_XML_BASELINE}/itktfMeasurementInsightRegionTest.xml
  ${ITK_REGRESSION_DATA_BASELINE}/vm_head_coronal.png )
