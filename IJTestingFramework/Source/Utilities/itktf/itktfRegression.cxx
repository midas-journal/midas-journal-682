
#include "itktfRegression.h"


#include "itkSize.h"
#include "itkIndex.h"
#include "itkImageRegion.h"
#include "itkPoint.h"
#include "itkVector.h"
#include "itkMatrix.h"

#include "itktfRegressionSupport.h"
#include "itktfCompareVisitor.h"
#include "itktfDifferenceVisitor.h"

namespace itk {

Regression::Regression(void)
{
  fileutil::PathList pathList = this->GetInFileSearchPath();
  pathList.push_front( fileutil::PathName( ITK_REGRESSION_DATA_BASELINE ) );
  this->SetInFileSearchPath(pathList);
  
  this->SetImageInsightToleranceOff();
}

Regression::~Regression(void) 
{
}

void Regression::SetImageInsightToleranceOff( void ) 
{ 
  this->SetImageInsightTolerance( 0.0, 0, 0 ); 
}

void Regression::SetImageInsightTolerance( double intensityTolerance, 
                               unsigned int numberOfPixelTolerance,
                               unsigned int radiusTolerance ) 
{
  m_IntensityTolerance = intensityTolerance;
  m_NumberOfPixelsTolerance = numberOfPixelTolerance;
  m_RadiusTolerance = radiusTolerance;
}

int Regression::Main( int argc, char *argv[] ) 
{
  int ret = testutil::RegressionTest::Main( argc, argv );
  return ret;
}


int Regression::MeasurementInsightFileImage( const std::string &fileName, const std::string &name) 
{
  testutil::MeasurementFile mf;
  mf.SetAttributeType("image/itk");
  mf.SetAttributeName(name);
  
  if (this->GetCompareMode()) 
    {
    mf.SetFileName(fileName);
    return this->CompareMeasurement(mf);
    } 
  else 
    {
    mf.SetFileName(fileutil::PathName(fileName).Tail().GetPathName());
    
    this->GetOutStream() << mf << std::endl;
    }    
  return 0;
}


testutil::DifferenceVisitor *Regression::CreateDifferenceVisitor(void) const 
{
  itk::DifferenceVisitor * temp = new itk::DifferenceVisitor;
  temp->SetImageInsightTolerance( m_IntensityTolerance, m_NumberOfPixelsTolerance, m_RadiusTolerance );
  return temp;
}

testutil::CompareVisitor *Regression::CreateCompareVisitor(void) const {
  itk::CompareVisitor * temp = new itk::CompareVisitor;
  temp->SetImageInsightTolerance( m_IntensityTolerance, m_NumberOfPixelsTolerance, m_RadiusTolerance );
  return temp;
}
  
}
