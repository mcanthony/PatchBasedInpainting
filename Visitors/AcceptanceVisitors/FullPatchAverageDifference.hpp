#ifndef FullPatchAverageDifference_HPP
#define FullPatchAverageDifference_HPP

#include <boost/graph/graph_traits.hpp>

// Parent class
#include "Visitors/AcceptanceVisitors/AcceptanceVisitorParent.h"

// Submodules
#include <ITKHelpers/ITKHelpers.h>

// ITK
#include "itkImageRegion.h"

/**

 */
template <typename TGraph, typename TImage>
struct FullPatchAverageDifference : public AcceptanceVisitorParent<TGraph>
{
  typedef typename boost::graph_traits<TGraph>::vertex_descriptor VertexDescriptorType;

  FullPatchAverageDifference(TImage* const image, const unsigned int halfWidth) :
  Image(image), HalfWidth(halfWidth)
  {

  }

  bool AcceptMatch(VertexDescriptorType target, VertexDescriptorType source, float& computedEnergy) const
  {
    itk::Index<2> targetPixel = ITKHelpers::CreateIndex(target);
    itk::ImageRegion<2> targetRegion = ITKHelpers::GetRegionInRadiusAroundPixel(targetPixel, HalfWidth);
    typename TImage::PixelType targetRegionAverage = ITKHelpers::AverageInRegion(Image, targetRegion);

    itk::Index<2> sourcePixel = ITKHelpers::CreateIndex(source);
    itk::ImageRegion<2> sourceRegion = ITKHelpers::GetRegionInRadiusAroundPixel(sourcePixel, HalfWidth);
    typename TImage::PixelType sourceRegionAverage = ITKHelpers::AverageInRegion(Image, sourceRegion);

    // Compute the difference
    computedEnergy = (targetRegionAverage - sourceRegionAverage).GetNorm();
    std::cout << "FullPatchAverageDifference Energy: " << computedEnergy << std::endl;
    return true;
  }

private:
  TImage* Image;

  const unsigned int HalfWidth;
};

#endif
