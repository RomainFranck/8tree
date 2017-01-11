#ifndef EIGTHTREE_HPP_
#define EIGTHTREE_HPP_

#include <iostream>
#include <memory>

template<class T>
class EigthTree
{
public:
	EigthTree(unsigned int size, std::unique_ptr<T> t)
	{
		_size = size + 1;
		_value = std::move(t);
		_parent = nullptr;

		for (int i = 0 ; i < 8 ; i++)
			_children[i].reset();
	};

	EigthTree(EigthTree* vt, unsigned int size, std::unique_ptr<T> t)
	{
		_parent = std::unique_ptr<EigthTree>(vt);
		_value = std::move(t);
		_size = size;

		for (int i = 0 ; i < 8 ; i++)
			_children[i].reset();

	}

	~EigthTree()
	{
		_value.reset();

		for (int i = 0 ; i < 8 ; i++)
			_children[i].reset();
	};

	bool	operator==(EigthTree* a)
	{
		return (a == nullptr ? this == nullptr : a->getValue() == this->getValue());
	};

	template<unsigned int i>
	EigthTree*	getChild() 
		{ return _children[i]; };

	EigthTree*	getChild(unsigned int i)
		{ return _children[i]; };

	EigthTree*	getParent()
		{ return _parent; };

	T& 			getValue()
	{
		return _value != nullptr ? *_value : _parent->getValue(); 
	};

	T& 			getValue(int x, int y, int z)
	{
		int bs = _size - 2;
		int index = (((x >> bs) & 1) << 2) | (((y >> bs) & 1) << 1) | ((z >> bs) & 1);

		if (_children[index] != nullptr)
			return _children[index]->getValue(x, y, z);
		return this->getValue();
	};

	void 		setValue(int x, int y, int z, std::unique_ptr<T> value)
	{
		int bs = _size - 2;
		int index = (((x >> bs) & 1) << 2) | (((y >> bs) & 1) << 1) | ((z >> bs) & 1);

		if (_size == 1)
			_value = std::move(value);
		else
		{
			if (_value == nullptr || *_value != *value)
			{			
				if (_children[index] == nullptr)
					_children[index] = std::make_unique<EigthTree<T>>(this, _size - 1, nullptr);
				return _children[index]->setValue(x, y, z, std::move(value));
			}

			if (this->areChildrenSame(value))
			{
				_value.reset();
				_value = std::move(value);
			
				std::cout << "is this it ?" << std::endl;

				for (int i = 0 ; i < 8 ; i++)
					_children[i].reset();
			}
/*			else if (_parent != nullptr)
			{
				delete _value;
				_value = nullptr;
			}*/
		}
	};

private:

	unsigned int					_size;
	std::unique_ptr<EigthTree> 		_parent;
	std::unique_ptr<EigthTree>		_children[8];
	std::unique_ptr<T>				_value;

	bool		areChildrenSame(std::unique_ptr<T>& value)
	{
		for (int i = 0 ; i < 8 ; i++)
		{
			if (_children[i] == nullptr || _children[i]->getValue() != *value)
				return false;
		}

		return true;
	}
};

#endif