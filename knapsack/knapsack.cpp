#include <iostream>
#define tab '\t'
using namespace std;

struct object
{
	int profit;
	int weight;
	double ratio;
	object(int p = 0, int w = 0, int r = 0) 
		: profit(p), weight(w), ratio(r) {}
};

class knapsack
{
	int total_weight;
	double total_profit;
	object * arr;
	int n;
	void scan_objects();
	void sort();
	public:
	knapsack();
	void maximize();
	void display();
	~knapsack() {delete [] arr;}
};

knapsack :: knapsack()
{
	total_profit = 0;
	cout << "Enter the weight of the bag" << endl;
	cin >> total_weight;
	cout << "Enter the no. of total Objects" << endl;
	cin >> n;
	arr = new object[n];
	scan_objects();
}

void knapsack :: scan_objects()
{
	for(int i = 0; i < n; ++i)
	{
		cout << "Enter the weight of object:" << tab;
		cin >> arr[i].weight;
		cout << "Enter the profit of object:" << tab;
		cin >> arr[i].profit;
		arr[i].ratio = (double) arr[i].profit / arr[i].weight;
	}
}

void swap(object &a, object &b)
{
	object temp = a;
	a = b;
	b = temp;
}

void adjust(object *tree, int n, int ptr)
{
	int left = ptr * 2 + 1, right = ptr * 2 + 2;
	object item = tree[ptr];
	while(right < n)
	{
		if(item.ratio >= tree[left].ratio
				&& item.ratio >= tree[right].ratio)
		{
			tree[ptr] = item;
			return;
		}
		else if(tree[left].ratio
				> tree[right].ratio)
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
	if(left == n-1 && tree[left].ratio
			> item.ratio)
	{
		tree[ptr] = tree[left];
		ptr = left;
	}
	tree[ptr] = item;
}

void knapsack :: sort()
{
	for(int i = 0; i < n; ++i)
		adjust(arr, n, n-i-1);
	for(int i = 0; i < n; ++i)
	{
		swap(arr[0], arr[n - i - 1]);
		adjust(arr, n - i - 1, 0);
	}
}


void knapsack :: maximize()
{
	sort();
	double sum = 0, diff = 0, w = 0;
	double *x = new double[n];
	for(int i = n - 1; i >= 0; --i)
	{
		diff = total_weight - sum;
		w = arr[i].weight;
		if(diff >= w)
			x[i] = 1;
		else
			x[i] = diff / w;
		total_profit += x[i] * arr[i].profit;
		sum += x[i] * w;
	}
	display();
	delete [] x;
}

void knapsack :: display()
{
	for(int i = 0; i < n; ++i)
	{
		cout << "Profit : " << arr[i].profit << tab
			<< "Weight : " << arr[i].weight << tab
			<< "Ratio : " << arr[i].ratio << endl;
	}
	cout << endl << "Maximum profit : " 
		<< total_profit << endl;
}

int main()
{
	knapsack a;
	a.maximize();
	return 0;
}
