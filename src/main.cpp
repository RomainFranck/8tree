#include <iostream>
#include <memory>

#include <EightTree.hpp>
#include <Voxel.hpp>

int main (int argc, char **argv)
{
	int size = argc == 2 ? atoi(argv[1]) : 4;

	std::shared_ptr<EightTree<Voxel>> vTree = std::make_shared<EightTree<Voxel>>(size, Voxel(0));

	for (int i = 0 ; i < ((1 << (size + 1)) - 1) ; i++)
	{
		for (int j = 0 ; j < ((1 << (size + 1)) - 1) ; j++)
		{
			for (int k = 0 ; k < ((1 << (size + 1)) - 1) ; k++)
			{
				vTree->setValue(i, j, k, Voxel((i & 6) ? 1 : 2));
			}
		}
	}

	vTree->dump(0);
}