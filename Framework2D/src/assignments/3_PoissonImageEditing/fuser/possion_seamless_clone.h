#pragma once

#include <Eigen/Sparse>
#include <Eigen/SparseCholesky>
#include <memory>
#include <vector>

#include "fuser.h"

namespace USTC_CG
{
class PossionSeamlessClone : public Fuser
{
   public:
    PossionSeamlessClone() = default;
    ~PossionSeamlessClone() override = default;

    std::shared_ptr<Image> fuse(
        const Image& source,
        const Image& target,
        const Image& mask,
        int offset_x,
        int offset_y) override;

    void clear_cache() override;

   private:
    int index(int x, int y, int w) const
    {
        return y * w + x;
    }

    // build and factorize the matrix A (Ax = b)
    bool build_and_factorize_A(const Image& mask);

   private:
    Eigen::SparseMatrix<double> A_;
    Eigen::SimplicialLDLT<Eigen::SparseMatrix<double>> solver_;
};

}  // namespace USTC_CG