#include <iostream>

#include <cmath>

namespace algo
{
	class MergeSort {
	private:
		static inline void Combiner(int *src, int *dst, int left, int mid, int right) {
			int it1 = left, it2 = mid, it3 = left;
			for (;(it1 < mid) && (it2 < right); it3++) {
				if (src[it1] < src[it2]) {
					dst[it3] = src[it1];
					it1++;
				} else {
					dst[it3] = src[it2];
					it2++;
				}
			}
			for (; it1 < mid; it3++, it1++) {
				dst[it3] = src[it1];
			}
			for (; it2 < right; it3++, it2++) {
				dst[it3] = src[it2];
			}
		}
	public:
		static void Sort(int* freeMem, int* array, int size)
		{
			int *src = array, *dst = freeMem;
			for (int i = 1; i < size; i *= 2) {
				memcpy(dst, src, size*4); // TODO bad place
				for (int j = 0, step = 2*i, end = size - i; j < end; j += step) {
					Combiner(src, dst, j, j + i, __min(j + step, size));
				}
				if (src == freeMem) {
					src = array;
					dst = freeMem;
				} else {
					src = freeMem;
					dst = array;
				}
			}
			if (src == freeMem)
				memcpy(array, src, size*4);
		}
	};
}

int main() {
	const int size = 18;

	int *freeMem = new int[size];
	int *array = new int[size];

	std::cout << "Array Start: ";
	for (int i = 0; i < size; i++) {
		freeMem[i] = 0;
		array[i] = rand() % (size * 2 - 1) + 10;
		std::cout << array[i] << " ";
	}
	std::cout << std::endl;

	algo::MergeSort::Sort(freeMem, array, size);

	std::cout << "Sorted Array: ";
	for (int i = 0; i < size; i++) {
		std::cout << array[i] << " ";
	}
	std::cout << std::endl;

	std::cout << "Hello, World!" << std::endl;

	delete[] freeMem;
	delete[] array;
	system("pause");
	return 0;
}