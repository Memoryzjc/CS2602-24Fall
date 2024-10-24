#include<iostream>

void quickSort(int arr[], int begin, int end)
{
	int i, j, t, pivot;
	if (begin > end) 
		return;

	pivot = arr[begin];
	i = begin;
	j = end;
	while (i != j)
	{
		while (arr[j] >= pivot && i < j) {
            j--;
        }
		while (arr[i] <= pivot && i < j) {
            i++;
        }
		if (i < j)
		{
			t = arr[i];
			arr[i] = arr[j];
			arr[j] = t;
		}
	}

	arr[begin] = arr[i];
	arr[i] = pivot;
	quickSort(arr, begin, i - 1);
	quickSort(arr, i + 1, end); 
}



int main() {
    int n;
    std::cin >> n;

    int num[n];
    for (int i = 0; i < n; i++) {
        std::cin >> num[i];
    }

    // if there is only one number, the result is 1
    if (n == 1) {
        std::cout << 1;
        return 0;
    }
    
    // first sort the array
    quickSort(num, 0, n - 1);

    // then find the max number of the same number
    int maxNum = 1, result = 1;
    for (int i = 0; i < n - 1; i++) {
        if (num[i] == num[i + 1]) {
            maxNum++;
        } else {
            result = (result >= maxNum) ? result : maxNum;
            maxNum = 1;
        }
    }
    
    // make sure compare the last number
    result = (result >= maxNum) ? result : maxNum;

    std::cout << result;
    return 0;
}