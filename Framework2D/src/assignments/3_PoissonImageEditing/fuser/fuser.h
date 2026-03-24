#pragma once

#include <memory>
#include <vector>
#include "common/image.h"

namespace USTC_CG
{
class Fuser
{
   public:
    Fuser() = default;
    virtual ~Fuser() = default;

    virtual std::shared_ptr<Image> fuse(
         const Image& source,
         const Image& target,
         const Image& mask,
         int offset_x,
         int offset_y) = 0;
    
    virtual void clear_cache() {}   // clean the cached factorization

   public:
    static bool use_mixed_gradient_;  // whether use mixed gradient
      
};
}