#include "sort.h"

int main()
{
	cout<< "**     排序算法比较          **" << '\n'
		<< "===============================" << '\n'
		<< "**     1---冒牌排序          **" << '\n'
		<< "**     2---选择排序          **" << '\n'
		<< "**     3---直接插入排序      **" << '\n'
		<< "**     4---希尔排序          **" << '\n'
		<< "**     5---快速排序          **" << '\n'
		<< "**     6---堆排序            **" << '\n'
		<< "**     7---归并排序          **" << '\n'
		<< "**     8---基数排序          **" << '\n'
		<< "**     9---退出程序          **" << '\n'
		<< "================================" << endl;

	cout << "请选择要产生的随机数个数: ";
	int n;
	cin >> n;

	vector<int> data;
	srand(time(NULL));

	while (n--)
	{
		data.push_back(rand() % INT_MAX);
	}

	vector< function< void(vector<int>) > > functions =
	{ bubbleSort,selectSort,insertSort,shellSort,
	quickSort,	heapSort , mergeSort,radixSort, exitProgram};

	clock_t start, finish;
	double totalTime;
	int order;

	while (cout << "\n\n请输入排序算法: ", cin >> order)
	{
		start = clock();
		functions[order - 1](data);
		finish = clock();
		totalTime = (double)(finish - start) / CLOCKS_PER_SEC;
		cout << "\n花了 " << totalTime << "s";
	}
	

	system("pause");
	return 0;
	
}



void exitProgram(vector<int> data)
{
	exit(1);
}

void bubbleSort(vector<int> data)
{
	int count = 0;

	for (int i = 0; i < data.size(); i++)
	{
		for (int j = 0 ; j < data.size() - i - 1 ; j++)
		{
			if (data[j] < data[j + 1])
			{
				swap(data[j], data[j + 1]);
				count++;
			}
		}
	}

	cout << "冒泡排序交换 " << count << "次";
}

void selectSort(vector<int> data)
{
	int count = 0;
	int max = 0;

	for (int i = 0; i < data.size(); i++)
	{
		for (int j = i; j < data.size(); j++)
		{
			if (data[max] < data[j])
			{
				max = j;
				count++;
			}
		}
		swap(data[i], data[max]);
		count++;

	}

	cout << "选择排序交换 " << count << "次";

}

void insertSort(vector<int> data)
{
	int count = 0;

	for (int i = 1; i < data.size(); i++)
	{
		int j;
		for (j = i - 1; j >= 0; j--)
		{
			if (data[i] < data[j])
				break;
			count++;
		}

		int temp = data[i];
		for (int k = i; k > j+1; k--)
		{
			data[k] = data[k - 1];
			count++;
		}

		data[j + 1] = temp;
	}

	cout << "插入排序交换 " << count << "次";

}

void shellSort(vector<int> data)
{
	int count = 0 ;
	int j;

	for (int gap = data.size() >> 1; gap > 0; gap >>= 1)
	{
		for (int i = gap; i < data.size(); i++)
		{
			int temp = data[i];
			for (j = i - gap; j >= 0 && data[j] > temp; j -= gap)
			{
				data[j + gap] = data[j];
				count++;
			}
			data[j + gap] = temp;
			count++;
		}
	}

	cout << "希尔排序交换 " << count << "次";

}

void quickSort(vector<int> data)
{
	int count = 0;
	count += quickSortMethod(data, 0, data.size()-1);
	cout << "快速排序交换 " << count << "次";
}

int quickSortMethod(vector<int>& data, int start, int end)
{
	int count = 0;

	if (start >= end)
	{
		return 0;
	}

	int mid = data[end];
	int left = start, right = end - 1;
	while (left < right)
	{
		while (data[left] < mid && left < right)
		{
			left++;
		}
		while (data[right] >= mid && left < right)
		{
			right--;
		}
		swap(data[left], data[right]);
		count++;
	}

	if (data[left] >= data[end])
	{
		swap(data[left], data[end]);
		count++;
	}
	else
		left++;

	count += quickSortMethod(data, start, left - 1);
	count += quickSortMethod(data, left + 1, end);

	return count;
}

int maxbit(vector<int> data, int n )
{
	int maxData = data[0];

	for (int i = 1; i < n; i++)
	{
		if (maxData < data[i])
			maxData = data[i];
	}
	int d = 1;
	int p = 10;

	while (maxData >= p)
	{
		maxData /= 10;
		++d;
	}

	return d;
}

void radixSort(vector<int> data)
{
	int n = data.size();
	int d = maxbit(data, n);
	int *temp = new int[n];
	int *count = new int[10];//计数器

	int k;
	int radix = 1;

	for (int i = 1; i <= d; i++)
	{
		for (int j = 0; j < 10; j++)
			count[j] = 0;
		for (int j = 0; j < n; j++)
		{
			k = (data[j] / radix) % 10;
			count[k]++;
		}
		for (int j = 1; j < 10; j++)
			count[j] = count[j - 1] + count[j];
		for (int j = n - 1; j >= 0; j--)
		{
			k = (data[j] / radix) % 10;
			temp[count[k] - 1] = data[j];
			count[k]--;
		}
		for (int j = 0; j < n; j++)
			data[j] = temp[j];
		radix *= 10;

	}

	delete[] temp;
	delete[] count;

	cout << "基数排序比较 " <<  0 << "次";

}

int mergeSortRecursive(vector<int>& data, int *reg ,int start ,int end )
{
	int count = 0;
	if (start >= end)
	{
		return 0;
	}

	int len = end - start, mid = (len >> 1) + start;
	int start1 = start, end1 = mid;
	int start2 = mid + 1, end2 = end;

	count += mergeSortRecursive(data, reg, start1, end1);
	count += mergeSortRecursive(data, reg, start2, end2);

	int k = start;
	while (start1 <= end1 && start2 <= end2)
	{
		count++;
		reg[k++] = (data[start1] < data[start2]) ? data[start1++] : data[start2++];
	}
	while (start1 <= end1)
	{
		count++;
		reg[k++] = data[start1++];
	}
	while (start2 <= end2)
	{
		count++;
		reg[k++] = data[start2++];
	}

	for (k = start; k <= end; k++)
	{
		data[k] = reg[k];
	}

	return count;
}

void mergeSort(vector<int> data)
{
	int count = 0;

	int *reg = new int[data.size()];
	count += mergeSortRecursive(data, reg, 0, data.size()-1);
	delete []reg;

	cout << "归并排序比较 " << count << "次";
}

int  maxHeapify(vector<int>& data, int start, int end)
{
	int count = 0;

	int dad = start;
	int son = dad * 2 + 1;
	while (son <= end)
	{
		if (son + 1 <= end && data[son] < data[son + 1])
			son++;
		if (data[dad] > data[son])
			return 0;
		else
		{
			swap(data[dad], data[son]);
			dad = son;
			son = dad * 2 + 1;
			count++;

		}
	}
	return count;
}

void heapSort(vector<int> data)
{
	int count = 0;
	int len = data.size();

	for (int i = len / 2 - 1; i >= 0; i--)
	{
		count += maxHeapify(data, i, len - 1);
	}
	for (int i = len - 1; i > 0; i--)
	{
		swap(data[0], data[i]);
		count++;
		count += maxHeapify(data, 0, i - 1);
	}

	cout << "堆排序交换 " << count << "次";
}