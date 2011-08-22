/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: itkShiftScaleInPlaceImageFilterTest.cxx,v $
  Language:  C++
  Date:      $Date: 2003-09-10 14:30:07 $
  Version:   $Revision: 1.5 $

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

// based on Testing/Code/BasicFilters/itkShiftScaleInPlaceImageFilterTest.cxx

#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif
#include <iostream>
#include <sstream>

#include "itkImageRegionIterator.h"

#include "itkShiftScaleImageFilter.h"
#include "itkShiftScaleInPlaceImageFilter.h"
#include "itkRandomImageSource.h"

#include "itktfFilterWatcher.h"
#include "itktfRegression.h"


namespace itk 
{

class ShiftScaleInPlaceImageFilterTest:
    public itk::Regression
{
protected:
  virtual int Test(int, char* [] )
  {
    // the output string stream to use as a measurement
    std::ostringstream progressOS;
    
    typedef itk::Image<char,3> ImageType;
    
    // Now generate a real image
    typedef itk::RandomImageSource<ImageType> SourceType;
    SourceType::Pointer source = SourceType::New();
    unsigned long randomSize[3] = {17, 8, 20};

    // Set up Start, End and Progress callbacks
    itk::tf::FilterWatcher sourceWatch(source, progressOS, "source");

    // Set up source
    source->SetSize(randomSize);
    double minValue = -10.0;
    double maxValue = 10.0;

    source->SetMin( static_cast< ImageType::PixelType >( minValue ) );
    source->SetMax( static_cast< ImageType::PixelType >( maxValue ) );


    // Define two standard shift scale filters so we can check whether the
    // in place filtering works
    typedef itk::ShiftScaleImageFilter<ImageType,ImageType> FilterType;
    FilterType::Pointer zeroFilter = FilterType::New();
    itk::tf::FilterWatcher zeroFilterWatch(zeroFilter, progressOS, "zeroFilter");
    zeroFilter->SetInput(source->GetOutput());
    zeroFilter->SetScale(0.0);

    FilterType::Pointer filter = FilterType::New();
    itk::tf::FilterWatcher filterWatch(filter, progressOS, "filter");
    filter->SetInput(zeroFilter->GetOutput());
    filter->SetShift(20);
  
  
    // Define two consumers of the shift scale filter, one another shift scale
    // and the other an in place shift scale
    typedef itk::ShiftScaleInPlaceImageFilter<ImageType> InPlaceFilterType;
    InPlaceFilterType::Pointer inPlaceFilter = InPlaceFilterType::New();
    itk::tf::FilterWatcher inPlaceWatch(inPlaceFilter, progressOS, "inPlaceFilter");
    inPlaceFilter->SetInput( filter->GetOutput() );
    inPlaceFilter->SetShift( 100 );

    FilterType::Pointer secondFilter = FilterType::New();
    itk::tf::FilterWatcher secondFilterWatch( secondFilter, progressOS, "secondFilter" );
    secondFilter->SetInput( filter->GetOutput() );
    secondFilter->SetShift( 50 );
  

    // Test itkSetMacros and itkGetMacros  
    this->MeasurementNumericInteger( inPlaceFilter->GetShift(), "inPlaceFilter->GetShift()" );
    this->MeasurementNumericInteger( inPlaceFilter->GetScale(), "inPlaceFilter->GetScale()" );
    this->MeasurementNumericInteger( inPlaceFilter->GetUnderflowCount(), "inPlaceFilter->GetUnderflowCount()" );  
    this->MeasurementNumericInteger( inPlaceFilter->GetUnderflowCount(), "inPlaceFilter->GetOverflowCount()" );

  
    try
      {
      // update the in place filter
      progressOS << "=========== Updating the in place filter. ==============="
                 << std::endl;
      inPlaceFilter->UpdateLargestPossibleRegion();


      progressOS << "=========== Updating the second filter. This should cause the first filter to re-execute ==============="
                 << std::endl;
      secondFilter->UpdateLargestPossibleRegion();


      // check the images
      itk::Index<3> index;
      index.Fill( 5 );

      this->MeasurementNumericInteger( filter->GetOutput()->GetPixel(index), "filter Pixel" );
      this->MeasurementNumericInteger( inPlaceFilter->GetOutput()->GetPixel(index) ,"inPlaceFilter Pixel");    
      this->MeasurementNumericInteger( secondFilter->GetOutput()->GetPixel(index), "secondFilter Pixel" );
    
      progressOS << "=========== Updating the in place filter again. This should only update the in place filter.  ==============="
                 << std::endl;
      inPlaceFilter->UpdateLargestPossibleRegion();


      this->MeasurementNumericInteger( filter->GetOutput()->GetPixelContainer()->Size(), "filter container size");
      this->MeasurementNumericInteger( inPlaceFilter->GetOutput()->GetPixel(index) ,"inPlaceFilter Pixel");
      this->MeasurementNumericInteger( secondFilter->GetOutput()->GetPixel(index), "secondFilter Pixel" );

      }
    catch (itk::ExceptionObject& e)
      {
      std::cerr << "Exception detected: "  << e;
      return -1;
      }


    this->MeasurementTextPlain(progressOS.str(), "progress");


    return 0;
  }


};
}


int main(int argc, char * argv[]) 
{
  itk::ShiftScaleInPlaceImageFilterTest test;
  return test.Main(argc, argv);
}
