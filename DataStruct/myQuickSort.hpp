#ifndef MYSORT_HPP
#define MYSORT_HPP

template<typename T>
void _swap(T& a, T& b) {
	T temp = a;
	a = b;
	b = temp;
}

template<typename T>
void _quick_sort(T* items, int l, int r) {
	if (r <= l)
		return;

	int m = (l + r) / 2;
	if (items[m] < items[l])
		_swap(items[m], items[l]);
	if (items[r] < items[m])
		_swap(items[r], items[m]);
	if (items[m] < items[l])
		_swap(items[m], items[l]);

	if (2 < r - l) {
		int pivot = l + 1;
		int left = pivot + 1;
		int right = r - 1;

		_swap(items[m], items[pivot]);

		while (left <= right) {
			while (left <= right && items[left] <= items[pivot])
				left++;
			while (left <= right && items[pivot] <= items[right])
				right--;
			if (left <= right)
				_swap(items[left], items[right]);
		}
		_swap(items[pivot], items[right]);

		_quick_sort(items, l, right - 1);
		_quick_sort(items, right + 1, r);
	}
}

template <typename T>
void myQuickSort(T* items, int size) {
	_quick_sort<T>(items, 0, size - 1);
}

#endif