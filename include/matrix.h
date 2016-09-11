#ifndef Matrix_H
#define Matrix_H

#include <initializer_list>

/* 
 *
 * --------->colCount
 *| [ 1 2 3 ]
 *| [ 4 5 6 ]
 *| [ 7 8 9 ]
 *v [ 3 7 9 ]
 *rowCount
 *
 * Can init Matrix{{1,2,3},{4,5,6}......}
 *
 */

void merge_recursive(int in[], int reg[], int start, int end);
void arrange(int in[], int len);

namespace Math
{

/*
template<class Type>
Type det(const Matrix&)
{}

template<class Type>
Type dot_Product(Matrix first, Matrix second)
{}
*/

enum operate{Add, Minus, Mutiply, Divide};

template<class Type>
class Matrix
{

public:

	Matrix(int col = 0, int row = 0) : rowCount{row} , colCount{col}
	{
		if(col && row)
		{
			this->mainData = new Type*[rowCount];

			for(int i=0; i<rowCount ;++i)
			{
				this->mainData[i] = new Type[colCount];
		
				for(int j=0; j<colCount ;++j)
					this->mainData[i][j] = 0;

			}
		}
		else
			this->mainData = nullptr;
		
	}

	Matrix(const Matrix<Type>& matrix) : rowCount{matrix.rowCount} , colCount{matrix.colCount}
	{
	
		this->mainData = new Type*[rowCount];

		for(int i=0; i<rowCount ;++i)
		{
		
			this->mainData[i] = new Type[colCount];

			for(int j=0; j<colCount ;++j)
				this->mainData[i][j] = matrix[i][j];
		
		}
	
	}

	Matrix(std::initializer_list<std::initializer_list<Type>> initList)
	   	: rowCount{(int)initList.size()} , colCount{(int)(*initList.begin() ).size()}
	{

		this->mainData = new Type*[rowCount];

		for(int i=0; i<rowCount ;++i)
		{
			this->mainData[i] = new Type[colCount];

			for(int j=0; j<colCount ;++j)
				this->mainData[i][j] = *(((initList.begin()+i)->begin()) + j);
		}
	}

	~Matrix()
	{
	
		for	(int i=0; i<rowCount ;++i)
			delete this->mainData[i];
		
		delete this->mainData;
	}

	inline bool set(int row, int col, Type val)
	{
		if(!(0 <= row < rowCount || 0 <= col < colCount))
			return false;
		this->mainData[row][col] = val;
		return true;
	}

	inline bool is_same_size(const Matrix<Type>& matched)
	{

		if(this->colCount != matched.colCount)
			return false;
		else if(this->rowCount != matched.rowCount)
			return false;
		
		return true;

	}

//Operator For Matrix======================================================

	Type* operator[](int row) const
	{
		if(row >= rowCount)
			return nullptr;
		return this->mainData[row];
	}

	Matrix<Type> operator+(const Matrix<Type>& added)
	{
		if(!is_same_size(added))
			return Matrix<Type>();

		Matrix rt{this->colCount, this->rowCount};

		for(int i=0; i<added.rowCount ;++i)
			for(int j=0; j<added.colCount ;++j)
				rt.set(i, j, this->mainData[i][j] + added[i][j]);
		return rt;
	}

	Matrix<Type>  operator-(const Matrix<Type>& minus)
	{
		if(!is_same_size(minus))
			return Matrix<Type>();

		Matrix rt{this->colCount, this->rowCount};

		for(int i=0; i<minus.rowCount ;++i)
			for(int j=0; j<minus.colCount ;++j)
				rt.set(i, j, this->mainData[i][j] - minus[i][j]);
		return rt;
	}

	Matrix<Type>  operator*(const Matrix<Type>& mutiplied)
	{
		if(this->rowCount != mutiplied.colCount)
			return Matrix<Type>();
	
		Matrix rt{this->rowCount, mutiplied.colCount};

		for(int i=0; i<this->rowCount;++i)
			for(int j=0; j<mutiplied.colCount ;++j)
				for(int k=0; k<this->colCount ;++k)
					rt.set(i, j, rt[i][j] + (this->mainData[i][k] * mutiplied[k][j]) );
		return rt;
	}

//	Matrix<Type>  operator/(const Matrix<Type>& devided)
//	{return (*this)*reciprocal(devided);}
//	A/B = A*(1/B)
	
	Matrix<Type>& operator=(const Matrix<Type>& designated)
	{
		for(int i=0; i<this->rowCount ;++i)
			for(int j=0; j<this->colCount ;++j)
				this->mainData[i][j] = designated[i][j];
		return *this;
	}

	bool 	  	  operator==(const Matrix<Type>& matched)
	{
		if(this->rowCount != matched.rowCount ||
		   this->colCount != matched.colCount)
			return false;
	
		for(int i=0; i<this->rowCount ;++i)
			for(int j=0; j<this->colCount ;++j)
				if(this->mainData[i][j] != matched[i][j])
					return false;
		return true;
	}

	bool		  operator!=(const Matrix<Type>& matched)
	{return !(*this == matched);}

//==================================================================

	int colCount ,rowCount;

protected:
	Type** mainData;
};

};

#endif
