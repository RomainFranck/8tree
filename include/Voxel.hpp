#ifndef VOXEL_HPP
#define VOXEL_HPP

#include <iostream>

class Voxel
{
public:
	Voxel(int);
	Voxel(const Voxel&);

	bool operator==(Voxel);

	bool operator!=(Voxel);

	int color;
};
#endif