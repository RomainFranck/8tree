#include <Voxel.hpp>

Voxel::Voxel()
{
	color = 0;
}

Voxel::Voxel(int c)
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

std::ostream& operator<<(std::ostream& os, const Voxel& v)  
{  
    os << v.color;  
    return os;  
}  