#include <Voxel.hpp>

Voxel::Voxel(int c = 0)
{
	color = c;
}

Voxel::Voxel(const Voxel& v)
{
	color = v.color;
}

bool Voxel::operator==(Voxel other)
{
	return (other.color == color);
}

bool Voxel::operator!=(Voxel other)
{
	return (!(*this == other));
}