#ifndef __itktfCompareVisitor_h
#define __itktfCompareVisitor_h

#include "TestingFramework/tfRegressionTest.h"
#include "TestingFramework/tfMeasurementVisitor.h"
#include "TestingFramework/tfMeasurement.h"

namespace itk {

/// \brief Visitor to compare two measurements
///
/// This overides the visitor for measurement files and compares
/// measurements of type "image/itk"
///
/// \note This may modifiy both Measurement objects.
class CompareVisitor 
  : public testutil::CompareVisitor 
{
public:
  CompareVisitor( void );
  
  /// \brief set the tolerance for comparing "image/itk" measurements
  ///
  /// intensityTolerance, numberOfPixelTolerance and radiusTolerance
  /// are parameters passed to itk::DifferenceImageFilter
  ///
  /// \sa itk::DifferenceImageFilter
  //@}
  virtual void SetImageInsightToleranceOff( void );
  virtual void SetImageInsightTolerance( double intensityTolerance, 
                                         unsigned int numberOfPixelTolerance = 0,
                                         unsigned int radiusTolerance = 0 );
  //@}
    
  /// Check to see if the measurements are "image/itk" otherwise calls
  /// the parents visit method
  virtual void Visit(testutil::MeasurementFile &m);

protected:
    
  static int RegressionTestImage (const char *testImageFilename, 
                                  const char *baselineImageFilename, 
                                  bool reportErrors,
                                  double intensityTolerance,
                                  unsigned int numberOfPixelsTolerance, 
                                  unsigned int radiusTolerance );

  
  double m_IntensityTolerance;
  unsigned int m_NumberOfPixelsTolerance;
  unsigned int m_RadiusTolerance;

};

}

#endif // __itktfCompareVisitor_h
