#include "Sort.h"

namespace Sort
{
	namespace
	{
		void merge(Array<Item>& parentArr, const int start, const int middle, const int end)
		{
			//Copy the left and right subarrays from the parent array
			const int leftSize = middle - start + 1;
			const int rightSize = end - middle;

			Item* leftArr = new Item[leftSize];
			Item* rightArr = new Item[rightSize];

			for (int i = 0; i < leftSize; i++)
			{
				leftArr[i] = parentArr[start + i];
			}
			for (int i = 0; i < rightSize; i++)
			{
				rightArr[i] = parentArr[middle + i + 1];
			}

			//Merge the two subarrays into the parent array
			int leftIndex = 0;
			int rightIndex = 0;
			int parentIndex = start;

			while (leftIndex < leftSize && rightIndex < rightSize)
			{
				if (leftArr[leftIndex].uid <= rightArr[rightIndex].uid)
				{
					parentArr[parentIndex] = leftArr[leftIndex];
					leftIndex++;
				}
				else
				{
					parentArr[parentIndex] = rightArr[rightIndex];
					rightIndex++;
				}
				parentIndex++;
			}

			//Merge remaining elements
			while (leftIndex < leftSize)
			{
				parentArr[parentIndex] = leftArr[leftIndex];
				leftIndex++;
				parentIndex++;
			}
			while (rightIndex < rightSize)
			{
				parentArr[parentIndex] = rightArr[rightIndex];
				rightIndex++;
				parentIndex++;
			}

			delete[] leftArr;
			delete[] rightArr;
		}
		void mergeSortItemArray(Array<Item>& arr, int start, int end)
		{
			//Recursion case
			if (start < end)
			{
				//Split the array into 2 parts and sort them 
				int middle = (start + end) / 2;
				mergeSortItemArray(arr, start, middle);
				mergeSortItemArray(arr, middle + 1, end);

				//Merge the 2 parts together
				merge(arr, start, middle, end);
			}
		}
	}

	void mergeSortItemArray(Array<Item>& arr)
	{
		mergeSortItemArray(arr, 0, arr.getSize() - 1);
	}
}