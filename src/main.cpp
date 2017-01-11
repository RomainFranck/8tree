#include <iostream>

#include <EigthTree.hpp>
#include <Voxel.hpp>

int main (int argc, char **argv)
{
	EigthTree<Voxel> vTree(3, new Voxel(0));

	vTree.setValue(0b010, 0b100, 0b001, new Voxel(12));

	std::cout << vTree.getValue(0b010, 0b101, 0b001).color << std::endl;
}