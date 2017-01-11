#include <iostream>
#include <memory>

#include <EigthTree.hpp>
#include <Voxel.hpp>

int main (int argc, char **argv)
{
	std::unique_ptr<EigthTree<Voxel>> vTree = std::make_unique<EigthTree<Voxel>>(4, std::make_unique<Voxel>(0));

	for (int i = 0 ; i < ((1 << 4) - 1) ; i++)
	{
		for (int j = 0 ; j < ((1 << 4) - 1) ; j++)
		{
			for (int k = 0 ; k < ((1 << 4) - 1) ; k++)
			{
				vTree->setValue(i, j, k, std::make_unique<Voxel>(i & 1 ? 1 : 2));
			}
		}
	}
}