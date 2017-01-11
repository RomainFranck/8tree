#include <iostream>

#include <VoxelTree.hpp>
#include <Voxel.hpp>

void init(void);
void display(void);
void keyboard(unsigned char, int, int);
void resize(int, int);
void drawcube(int, int, int);

int is_depth; /* depth testing flag */

int main (int argc, char **argv)
{
	Voxel v(0xff44aa);

	VoxelTree<Voxel> vTree(32, new Voxel(0));

	vTree.setValue(0b0100000000, 0b0111011100, 0b0001110001, new Voxel(12));

	std::cout << vTree.getValue(0b0100000001, 0b0111011100, 0b0001110000).color << std::endl;
}