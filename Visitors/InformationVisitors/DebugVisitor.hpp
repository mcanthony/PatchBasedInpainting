#ifndef DebugVisitor_HPP
#define DebugVisitor_HPP

#include <boost/graph/graph_traits.hpp>

// Custom
#include "Visitors/InpaintingVisitorParent.h"
#include "ImageProcessing/Mask.h"
#include "Helpers/OutputHelpers.h"
#include "Helpers/ITKHelpers.h"

// ITK
#include "itkImage.h"
#include "itkImageRegion.h"

/**
  * This visitor writes out information and images at each iteration.
 */
template <typename TGraph, typename TImage>
struct DebugVisitor : public InpaintingVisitorParent<TGraph>
{
  TImage* Image;
  Mask* MaskImage;

  const unsigned int HalfWidth;
  unsigned int NumberOfFinishedVertices;

  typedef typename boost::graph_traits<TGraph>::vertex_descriptor VertexDescriptorType;

  DebugVisitor(TImage* const image, Mask* const mask, const unsigned int halfWidth) :
  Image(image), MaskImage(mask), HalfWidth(halfWidth), NumberOfFinishedVertices(0)
  {

  }

  void InitializeVertex(VertexDescriptorType v, TGraph& g) const
  {

  };

  void DiscoverVertex(VertexDescriptorType v, TGraph& g) const
  {

  };

  void PotentialMatchMade(VertexDescriptorType target, VertexDescriptorType source, TGraph& g)
  {
    std::cout << "Match made: target: " << target[0] << " " << target[1]
              << " with source: " << source[0] << " " << source[1] << std::endl;
  };

  void PaintVertex(VertexDescriptorType target, VertexDescriptorType source, TGraph& g) const
  {

  };

  bool AcceptMatch(VertexDescriptorType target, VertexDescriptorType source, TGraph& g) const
  {
    return true;
  };

  void FinishVertex(VertexDescriptorType target, VertexDescriptorType sourceNode, TGraph& g)
  {
    {
    itk::Index<2> sourceIndex = ITKHelpers::CreateIndex(sourceNode);

    itk::ImageRegion<2> sourceRegion = ITKHelpers::GetRegionInRadiusAroundPixel(sourceIndex, HalfWidth);

    HelpersOutput::WriteVectorImageRegionAsRGB(Image, sourceRegion,
                                               Helpers::GetSequentialFileName("sourcePatch",
                                                                              this->NumberOfFinishedVertices, "png"));
    }

    {
    // Construct the region around the vertex
    itk::Index<2> indexToFinish = ITKHelpers::CreateIndex(target);

    itk::ImageRegion<2> region = ITKHelpers::GetRegionInRadiusAroundPixel(indexToFinish, HalfWidth);

    HelpersOutput::WriteVectorImageRegionAsRGB(Image, region,
                                               Helpers::GetSequentialFileName("targetPatch",
                                                                              this->NumberOfFinishedVertices, "png"));
    HelpersOutput::WriteRegion(MaskImage, region,
                               Helpers::GetSequentialFileName("maskPatch", this->NumberOfFinishedVertices, "png"));
    }

    HelpersOutput::WriteImage(MaskImage, Helpers::GetSequentialFileName("mask", this->NumberOfFinishedVertices, "png"));
    HelpersOutput::WriteImage(MaskImage, Helpers::GetSequentialFileName("mask", this->NumberOfFinishedVertices, "mha"));
    HelpersOutput::WriteVectorImageAsRGB(Image, Helpers::GetSequentialFileName("output", this->NumberOfFinishedVertices, "png"));
    HelpersOutput::WriteImage(Image, Helpers::GetSequentialFileName("output", this->NumberOfFinishedVertices, "mha"));

    this->NumberOfFinishedVertices++;

    std::cout << "Finished node " << this->NumberOfFinishedVertices << std::endl;
  };

  void InpaintingComplete() const
  {
  }
};

#endif
