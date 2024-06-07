#include <iostream>
using namespace std;

// swap function
void swap(int arr[], int i, int j)
{
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

// partition function
int partition(int arr[], int low, int high, int pivot){
	int i = low;
	int j = low;
	while( i <= high){
		if(arr[i] > pivot){
			i++;
		}
		else{
			swap(arr,i,j);
			i++;
			j++;
		}
	}
    cout << "vale of i : " << i << endl;
    cout << "vale of j : " << j << endl;
    
    cout << "vale of j-1 : " << j-1 << endl;
    for (int k = low; k < j-1; k++){
        cout << arr[k] << " ";
    }
    cout << endl;
	return j-1;
}

void quickSort(int arr[], int low, int high){
	if(low < high){
	int pivot = arr[high];
	int pos = partition(arr, low, high, pivot);
	
	quickSort(arr, low, pos-1);
	quickSort(arr, pos+1, high);
	}
}

int main()
{
    system("cls");
    int arr[] = {8, 15, 4, 3, 18, 7, 1, 4};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Array before sorting: " << endl;
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    
    quickSort(arr, 0, n - 1);

    cout << "Array after sorting: ";
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    

    return 0;
}
