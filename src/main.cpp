#include <iostream>

#include <EigthTree.hpp>
#include <Voxel.hpp>

int main (int argc, char **argv)
{
	Voxel* v0 = new Voxel(0);
	EigthTree<Voxel>* vTree = new EigthTree<Voxel>(4, v0);

	for (int i = 0 ; i < ((1 << 4) - 1) ; i++)
	{
		for (int j = 0 ; j < ((1 << 4) - 1) ; j++)
		{
			for (int k = 0 ; k < ((1 << 4) - 1) ; k++)
			{
				vTree->setValue(i, j, k, new Voxel(i & 1 ? 1 : 2));
			}
		}
	}

	delete vTree;
}