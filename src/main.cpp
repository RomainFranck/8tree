#include <iostream>

#include <EigthTree.hpp>
#include <Voxel.hpp>

int main (int argc, char **argv)
{
	EigthTree<Voxel> vTree(8, new Voxel(0));

	for (int i = 0 ; i < 0xff)
	{
		for (int j = 0 ; i < 0xff)
		{
			for (int k = 0 ; i < 0xff)
			{
				vTree.setValue(i, j, k, new Voxel(i << 16 | j << 8 | k));
			}
		}
	}

	std::cout << vTree.getValue(0b011, 0b101, 0b000).color << std::endl;

}