#ifndef EIGTHTREE_HPP_
#define EIGTHTREE_HPP_

#include <iostream>
#include <cstddef>

template<class T>
class EigthTree
{
public:
	EigthTree(unsigned int size, T* t)
	{
		_size = size + 1;
		_value = t;

		for (int i = 0 ; i < 8 ; i++)
			_children[i] = NULL;
	};

	EigthTree(EigthTree* vt, unsigned int size, T* t)
	{
		_parent = vt;
		_value = t;
		_size = size;

		for (int i = 0 ; i < 8 ; i++)
			_children[i] = NULL;
	}

	~EigthTree()
	{
		if (_value != NULL)
			delete _value;

		for (EigthTree* vt : _children)
		{
			delete vt;
		}
	};

	bool	operator==(EigthTree* a)
	{
		return (a == NULL ? this == NULL : a->getValue() == this->getValue());
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
		return _value != NULL ? *_value : _parent->getValue(); 
	};

	T& 			getValue(int x, int y, int z)
	{
		int bs = _size - 2;
		int index = (((x >> bs) & 1) << 2) | (((y >> bs) & 1) << 1) | ((z >> bs) & 1);

		if (_children[index] != NULL)
			return _children[index]->getValue(x, y, z);
		return this->getValue();
	};

	void 		setValue(int x, int y, int z, T* value)
	{
		int bs = _size - 2;
		int index = (((x >> bs) & 1) << 2) | (((y >> bs) & 1) << 1) | ((z >> bs) & 1);

		if (_size == 1)
			_value = value;
		else
		{
			if (_children[index] == NULL)
				_children[index] = new EigthTree<T>(this, _size - 1, NULL);

			if (_value == NULL || *_value != *value)
				return _children[index]->setValue(x, y, z, value);

			if (_value != NULL) //this == _children[index]
			{
				delete _children[index];
				return;
			}

			if (this->areChildrenSame(value))
			{
				_value = new T(*value);
			
				for (EigthTree* vt : _children)
					delete vt;
			}
			else
				_value = NULL;
		}
	};

private:

	unsigned int	_size;
	EigthTree* 		_parent;
	EigthTree* 		_children[8];
	T* 				_value;

	bool		areChildrenSame(T* value)
	{
		for (int i = 0 ; i < 8 ; i++)
		{
			if (_children[i] == NULL || _children[i]->getValue() != *value)
				return false;
		}

		return true;
	}
};

#endif