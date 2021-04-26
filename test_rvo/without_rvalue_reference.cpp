#include <iostream>
#include <algorithm>
#include <cstring>
#include <ctime>
#define DIM 256
#define LIMIT 10 //1000000

using namespace std;

class Vector
{
private:
  const int size;
	int *array;

public:
	Vector(const int new_size) : size(new_size), array(new int [new_size]) {}
	
	// copy constructor
	Vector(const Vector &rhs) : size(rhs.size)
	{
		// deep copy is required
		array = new int [rhs.size];
		memcpy(array, rhs.array, rhs.size * sizeof(int));
	}

	int& operator[] (const int index)
	{
		return array[index];
	}

	int operator[] (const int index) const
	{
		return array[index];
	}

	Vector& operator+= (const Vector &rhs)
	{
		for(int index=0; index<size; ++index)
			array[index] += rhs[index];
		return *this;
	}

	Vector operator+ (const Vector &rhs) const
	{
		Vector temp(*this);
		temp += rhs;
		return temp;
	}
	
	~Vector() { delete [] array; }
};

double runtime_without_move_semantic (const int iterative_limit)
{
	clock_t begin, end;
	Vector a(DIM), b(DIM), c(DIM);

	for(int i=0; i<DIM; ++i) {
		a[i] = 0;
		b[i] = 1;
		c[i] = 2;
	}

	begin = clock();

	for (int iter; iter<iterative_limit; ++iter) {
		Vector d = a+b+c;
		d[iter&DIM] = 2;
	}

	end = clock();

	return (static_cast<double>(end-begin) / static_cast<double>(CLOCKS_PER_SEC) );
}

int main()
{
	cout << runtime_without_move_semantic(LIMIT) << '\n';
	return 0;
}