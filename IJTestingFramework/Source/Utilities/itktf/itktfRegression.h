#ifndef __itktfRegression_h
#define __itktfRegression_h

#include "TestingFramework/tfRegressionTest.h"

#include "itktfRegressionSupport.h"
#include "itktfCompareVisitor.h"
#include "itktfDifferenceVisitor.h"

#include <sstream>

#include "itkSize.h"
#include "itkIndex.h"
#include "itkImageRegion.h"
#include "itkPoint.h"
#include "itkVector.h"
#include "itkMatrix.h"


namespace itk {


// \brief a base class of implementing itk tests with the TestingFramework
class Regression 
  : public testutil::RegressionTest 
{
public:
  Regression(void); 

  virtual ~Regression(void);

  //@{
  // \brief setting the tolerance for comparing Insight image file
  // measurements 
  // 
  // These values are passed to itk::DifferenceImageFilter. 
  // \param intensityTolerance the difference between two value before the pixels are considered different
  // \param numberOfPixelTolerance the number of different pixel before the images are considered different
  // \param radiusTolerance a search radius to find a simular pixel
  //
  // \sa itk::DifferenceImageFilter
  virtual void SetImageInsightToleranceOff( void );
  virtual void SetImageInsightTolerance( double intensityTolerance, 
                                         unsigned int numberOfPixelTolerance = 0,
                                         unsigned int radiusTolerance = 0 );
  //@}

  
  int Main( int argc, char *argv[] );

protected:
    
  // \brief Performs a measurement for an itk image file
  //
  // \param fileName the name of an image file for the measurement
  // \param name gives this measuement a name
  int MeasurementInsightFileImage( const std::string &fileName, const std::string &name); 

  template <unsigned int Dimension>
  int MeasurementInsightSize( const Size<Dimension> &size, const std::string &name, bool tolerant = false ) 
  {
    int ret = 0;
    for (unsigned int i = 0; i < Dimension; ++i) 
      {
      std::ostringstream nameWithIndex;
      nameWithIndex << name << "_" << i;
      ret += this->MeasurementNumericInteger( size[i], nameWithIndex.str(), tolerant);
      }
    return ret;
  }

  template <unsigned int Dimension>
  int MeasurementInsightIndex( const Index<Dimension> &index, const std::string &name, bool tolerant = false ) 
  {
    
    int ret = 0;
    for (unsigned int i = 0; i < Dimension; ++i) 
      {
      std::ostringstream nameWithIndex;
      nameWithIndex << name << "_" << i;
      ret += this->MeasurementNumericInteger( index[i], nameWithIndex.str(), tolerant);
      }
    return ret;
  }

  template <unsigned int Dimension>
  int MeasurementInsightRegion( const ImageRegion<Dimension> &region, const std::string &name, bool tolerant = false )
  {
    int ret = 0;
    ret += this->MeasurementInsightIndex( region.GetIndex(), name + " Index", tolerant );
    ret += this->MeasurementInsightSize( region.GetSize(), name + " Size", tolerant );
    return ret;
  }

  template <typename T, unsigned int Dimension>
  int MeasurementInsightPoint( const Point<T, Dimension> &point, const std::string &name, bool tolerant = true ) 
  {    
    int ret = 0;
    for (unsigned int i = 0; i < Dimension; ++i) 
      {
      std::ostringstream nameWithIndex;
      nameWithIndex << name << "_" << i;
      ret += this->MeasurementNumericDouble( point[i], nameWithIndex.str(), tolerant);
      }
    return ret;
  }

  template <typename T, unsigned int Dimension>
  int MeasurementInsightVector( const Vector<T, Dimension> &vector, const std::string &name, bool tolerant = true ) 
  {    
    int ret = 0;
    for (unsigned int i = 0; i < Dimension; ++i) 
      {
      std::ostringstream nameWithIndex;
      nameWithIndex << name << "_" << i;
      ret += this->MeasurementNumericDouble( vector[i], nameWithIndex.str(), tolerant);
      }
    return ret;
  }

  template <typename T, unsigned int NRows, unsigned int NColumns>
  int MeasurementInsightMatrix( const Matrix<T, NRows, NColumns> &matrix, const std::string &name, bool tolerant = true ) 
  {    
    int ret = 0;
    for (unsigned int i = 0; i < NRows; ++i) 
      {
      for (unsigned int j = 0; j < NColumns; ++j) 
        {
        std::ostringstream nameWithIndex;
        nameWithIndex << name << "_" << i << "_" << j;
        ret += this->MeasurementNumericDouble( matrix[i][j], nameWithIndex.str(), tolerant);
        }
      }
    return ret;
  }

  // overridden to return itk::DiferenceVisitor to allow differencing of "image/itk"
  testutil::DifferenceVisitor *CreateDifferenceVisitor(void) const;

  // overridden to return itk::CompareVisitor to allow comparing of "image/itk"
  testutil::CompareVisitor *CreateCompareVisitor(void) const;

  // \brief overriden to parse insight specific arguemnts
  //
  // todo this is currently not implemented, arguments such as number
  // of threads, debug mode, and tollerance could be placed here
//  void ParseAndRemoveArguments(int &argc, char *argv[]);

private:
  double m_IntensityTolerance;
  unsigned int m_NumberOfPixelsTolerance;
  unsigned int m_RadiusTolerance;

};

}

#endif // __itktfRegression_h
