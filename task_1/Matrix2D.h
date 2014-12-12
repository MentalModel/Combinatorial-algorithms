#pragma once
#include <iostream>
#include <vector>

template<class T> class Matrix2D;

template<class T>
std::ostream& operator<<(std::ostream& ostr, const Matrix2D<T> &matrix);

template<class T>
class Matrix2D {

	public:
		Matrix2D(int size);
		Matrix2D();
		~Matrix2D();

		int getSize() const {return quantity;}
		void setAt(int, int, T);
		T getAt(int, int);

		friend std::ostream &operator<< <T>(std::ostream& ostr, const Matrix2D<T> &matrix);

	private:
		int quantity;
		std::vector<std::vector<T>> matrix;
};

template<class T>
Matrix2D<T>::Matrix2D(int size):quantity(size)
{
	for(int idx = 0; idx < quantity; ++idx)
    {
        std::vector<T> tempVec;
        for(int j = 0; j < quantity; ++j)
            tempVec.push_back(0);
        matrix.push_back(tempVec);
    }
}

template<class T>
Matrix2D<T>::Matrix2D():quantity(0)
{
	Matrix2D(0);
}

template<class T>
Matrix2D<T>::~Matrix2D(){}

template<class T>
void Matrix2D<T>::setAt(int i, int j, T value)
{
	matrix[i][j] = value;
}

template<class T>
T Matrix2D<T>::getAt(int i, int j)
{
	return matrix[i][j];
}

template<class T>
std::ostream &operator<< <T>(std::ostream& ostr, const Matrix2D<T> &mat)
{
	int size_of_matrix = mat.getSize(); 
	for(int i = 0 ; i < size_of_matrix; ++i) 
	{
		for(int j = 0 ; j < size_of_matrix; ++j)
			ostr<<mat.matrix[i][j]<<"   ";
		ostr<<"\n";
	}
	return ostr;
}