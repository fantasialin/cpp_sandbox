#include <iostream>
#include <algorithm>
#include <cstring>
#include <ctime>
#define DIM 256
#define LIMIT 1000 //1000000

using namespace std;

class VectorWithRvalue
{
private:
	const int size;
	int *array;

public:
	VectorWithRvalue(const int new_size) : size(new_size), array(new int [new_size]) {}
	
	// copy constructor
	VectorWithRvalue(const VectorWithRvalue &rhs) : size(rhs.size)
	{
		// deep copy is required
		array = new int [rhs.size];
		memcpy(array, rhs.array, rhs.size * sizeof(int));
	}

	// move constructor
	VectorWithRvalue(VectorWithRvalue &&rhs) : size(rhs.size), array(rhs.array)
	{
		rhs.array = nullptr;
	}

	int& operator[] (const int index)
	{
		return array[index];
	}

	int operator[] (const int index) const
	{
		return array[index];
	}

	VectorWithRvalue& operator+= (const VectorWithRvalue &rhs)
	{
		for(int index=0; index<size; ++index)
			array[index] += rhs[index];
		return *this;
	}

	VectorWithRvalue operator+ (const VectorWithRvalue &rhs) const
	{
		VectorWithRvalue temp(*this);
		temp += rhs;
		return temp;
	}
	
	~VectorWithRvalue() { delete [] array; }
};

VectorWithRvalue&& operator+ (VectorWithRvalue &&lhs, const VectorWithRvalue &rhs) 
{
	lhs += rhs;
	return std::move(lhs);
}

double runtime_with_move_semantic (const int iterative_limit)
{
	clock_t begin, end;
	VectorWithRvalue a(DIM), b(DIM), c(DIM);

	for(int i=0; i<DIM; ++i) {
		a[i] = 0;
		b[i] = 1;
		c[i] = 2;
	}

	begin = clock();

	for (int iter=0; iter<iterative_limit; ++iter) {
		VectorWithRvalue d = a+b+c;
		d[iter&DIM] = 2;
	}

	end = clock();

	return (static_cast<double>(end-begin) / static_cast<double>(CLOCKS_PER_SEC) );
}

int main()
{
	cout << runtime_with_move_semantic(LIMIT) << '\n';
	return 0;
}