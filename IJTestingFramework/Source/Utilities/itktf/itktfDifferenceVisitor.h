#ifndef __itktfDifferenceVisitor_h
#define __itktfDifferenceVisitor_h


#include "TestingFramework/tfRegressionTest.h"
#include "TestingFramework/tfMeasurementVisitor.h"
#include "TestingFramework/tfMeasurement.h"

namespace itk {

/// \brief Visitor to print difference between two measurement
///
/// This overides the visitor for measurement files and performs image
/// differencing for "image/itk" type files.
///
/// Others are are handled by the parent
class DifferenceVisitor
  : public testutil::DifferenceVisitor {
public:

  DifferenceVisitor(void);

  virtual void SetImageInsightToleranceOff( void );
  virtual void SetImageInsightTolerance( double intensityTolerance, 
                                         unsigned int numberOfPixelTolerance = 0,
                                         unsigned int radiusTolerance = 0 );

  virtual void Visit(testutil::MeasurementFile &m);

protected:
  

  static int DifferenceTestImage (testutil::MeasurementFile &testMeasurement,
                                  testutil::MeasurementFile &baselineMeasurement,
                                  double intensityTolerance,
                                  unsigned int numberOfPixelsTolerance, 
                                  unsigned int radiusTolerance );

  
  double m_IntensityTolerance;
  unsigned int m_NumberOfPixelsTolerance;
  unsigned int m_RadiusTolerance;
};


}

#endif // __itktfDifferenceVisitor_h
