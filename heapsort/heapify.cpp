#include <iostream>
#define tab '\t'
using namespace std;

void print_array(int *arr, int n)
{
	for(int i = 0; i < n; ++i)
		cout << arr[i] << tab;
	cout << endl;
}

void swap(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
}

void adjust(int *tree, int n, int ptr)
{
	int left = ptr * 2 + 1, right = ptr * 2 + 2;
	int item = tree[ptr];
	while(right < n)
	{
		if(item >= tree[left] && item >= tree[right])
		{
			tree[ptr] = item;
			return;
		}
		else if(tree[left] > tree[right])
		{
			tree[ptr] = tree[left];
			ptr = left;
		}
		else
		{
			tree[ptr] = tree[right];
			ptr = right;
		}
		left = ptr*2 + 1;
		right = ptr*2 + 2;
	}
	if(left == n-1 && tree[left] > item)
	{
		tree[ptr] = tree[left];
		ptr = left;
	}
	tree[ptr] = item;
}

void heap_sort(int *arr, int n)
{
	for(int i = 0; i < n; ++i)
		adjust(arr, n, n-i-1);
	for(int i = 0; i < n; ++i)
	{
		swap(arr[0], arr[n - i - 1]);
		adjust(arr, n - i - 1, 0);
	}
}

int main()
{
	cout << "Enter the length of the array" << endl;
	int n;
	cin >> n;
	int *arr = new int[n];
	for(int i = 0; i < n; ++i)
		cin >> arr[i];

	heap_sort(arr, n);
	print_array(arr, n);
	return 0;
}
