#ifndef EIGHTTREE_HPP_
#define EIGHTTREE_HPP_

#include <iostream>
#include <memory>

template<class T>
class EightTree
{
public:
	EightTree(unsigned int size, T value)
	{
		_size = size;
		_value = value;
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
					_children[index] = std::make_shared<EightTree<T>>(_size - 1, _value);

				_children[index]->setValue(x, y, z, value);

				if (this->areChildrenSame(value))
				{
					_value = value;

					for (int i = 0 ; i < 8 ; i++)
						if (_children[i] != nullptr)
							_children[i].reset();
				}//*/
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