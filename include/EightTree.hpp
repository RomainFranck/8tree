#ifndef EIGHTTREE_HPP_
#define EIGHTTREE_HPP_

#include <iostream>
#include <memory>
#include <vector>

template<class T>
class EightTree
{
public:
	EightTree(unsigned int size, T value, std::shared_ptr<std::vector<std::shared_ptr<EightTree>>> path = nullptr)
	{
		_size = size;
		_value = value;

		if (path == nullptr)
			_path = std::make_shared<std::vector<std::shared_ptr<EightTree>>>(size, nullptr);
		else
			_path = path;
	};

	~EightTree()
	{
		for (int i = 0 ; i < 8 ; i++)
			if (_children[i] != nullptr)
				_children[i].reset();
	};

	bool	operator==(EightTree* a)
	{
		return (a == nullptr ? this == nullptr : a->getValue() == this->getValue());
	};

	std::weak_ptr<EightTree>	getChild(unsigned int i)
	{
		return std::weak_ptr<EightTree>(_children[i]); 
	}

	T&							getValue()
	{
		return _value;
	}

	T&							getValue(int x, int y, int z)
	{
		int bs = _size - 1;
		int index = (((x >> bs) & 1) << 2) | (((y >> bs) & 1) << 1) | ((z >> bs) & 1);

		if (_children[index] != nullptr)
			return _children[index]->getValue(x, y, z);
		return this->getValue();
	};


	void		setValueOpti(int x, int y, int z, T value)
	{
		unsigned int i = 0;

		while(i < _size && (*_path)[i] == nullptr)
			i++;

		while(i < _size)
		{
			if ((x >> i) == (_lx >> i) && (y >> i) == (_ly >> i) && (z >> i) == (_lz >> i))
			{
				(*_path)[i]->setValue(x, y, z, value);
				return;
			}

			i++;
		}

		this->setValue(x, y, z, value);

		_lx = x;
		_ly = y;
		_lz = z;
	}

	void 		setValue(int x, int y, int z, T value)
	{
		int bs = _size - 1;
		int index = (((x >> bs) & 1) << 2) | (((y >> bs) & 1) << 1) | ((z >> bs) & 1);

		if (_size <= 0)
			_value = value;
		else
		{
			if (_value != value)
			{	
				if (_children[index] == nullptr)
					_children[index] = std::make_shared<EightTree<T>>(_size - 1, _value, _path);

				_children[index]->setValue(x, y, z, value);
				(*_path)[_size - 1] = _children[index];

				if (this->areChildrenSame(value))
				{
					_value = value;
					(*_path)[_size - 1] = nullptr;

					for (int i = 0 ; i < 8 ; i++)
						if (_children[i] != nullptr)
							_children[i].reset();
				}
			}
		}
	};

	void		dump(int padding)
	{
		for(int i = 0 ; i < padding ; i++)
		{
			std::cout << "	";
		}

		std::cout << _value << std::endl;

		for (int i = 0 ; i < 8 ; i++)
			if (_children[i] != nullptr)
				_children[i]->dump(padding + 1);
	};

private:

	unsigned int					_size;
	std::shared_ptr<EightTree>		_children[8];
	T								_value;

	int _lx; // I know, very ugly, it's just to test if my algorithm works
	int _ly;
	int _lz;
	std::shared_ptr<std::vector<std::shared_ptr<EightTree>>> _path;

	bool		areChildrenSame(T value)
	{
		for (int i = 0 ; i < 8 ; i++)
		{
			if (_children[i] == nullptr || _children[i]->getValue() != value)
			{
				return false;
			}
		}

		return true;
	}
};

#endif