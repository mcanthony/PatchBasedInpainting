/*=========================================================================
 *
 *  Copyright David Doria 2011 daviddoria@gmail.com
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

#ifndef BoundaryNormals_H
#define BoundaryNormals_H

// Submodules
#include <Mask/Mask.h>
#include <ITKHelpers/ITKHelpers.h>

class BoundaryNormals
{
public:
  typedef itk::Image<unsigned char, 2> UnsignedCharScalarImageType;
  
  /** Constructor. */
  BoundaryNormals(const UnsignedCharScalarImageType* const boundaryImage, const Mask* const mask) :
    BoundaryImage(boundaryImage), MaskImage(mask){}

//  /** Comput the boundary normals. */
  template <typename TNormalsImage>
  void ComputeBoundaryNormals(const float blurVariance, TNormalsImage* const boundaryNormals);

private:
  const UnsignedCharScalarImageType* BoundaryImage;
  const Mask* MaskImage;
};

#include "BoundaryNormals.hpp"

#endif
