#ifndef SORT_H_INCLUDED
#define SORT_H_INCLUDED

template<typename elemType>
class sort
{
private:
    void insert(elemType a[], int n, const elemType &x) {
        int i;

        for (i = n - 1; i >= 0; i--) {
            if (a[i] <= x) {
                break;
            } else {
                a[i + 1] = a[i];
            }
        }

        a[i + 1] = x;
    }

    void merge(elemType a[], int low, int mid, int high) {
        int i, j, k;
        elemType *c;

        c = new elemType[high - low + 1];
        i = low;
        j = mid + 1;
        k = 0;

        while (i <= mid && j <= high) {
            if (a[i] <= a[j]) {
                c[k] = a[i];
                i++;
            } else {
                c[k] = a[j];
                j++
            }

            k++;
        }

        while (i <= mid) {
            c[k] = a[i];
            i++;
            k++;
        }

        while (j <= high) {
            c[k] = a[j];
            j++;
            k++;
        }

        for (int i = 0; i < high - low + 1; i++) {
            a[i + low] = c[i];
        }

        delete []c;
    }

    void mergeSort(elemType a[], int low, int high) {
        int mid;
        
        if (low >= high) {
            return;
        }

        mid = (low + high) / 2;

        mergeSort(a, low, mid);
        mergeSort(a, mid + 1, high);
        merge(a, low, mid, high);
    }
  
    void quickSort(elemType a[], int start, int end) {
        int i, j, hole;
        elemType tmp;

        if (end <= start) {
            return;
        }

        tmp = a[start];
        hole = start;
        i = start;
        j = end;

        while (i < j) {
            while ((j > i) && (a[j] >= tmp)) {
                j--;
            }
            if (i == j) {
                break;
            }
            a[hole] = a[j];
            hole = j;

            while ((i < j) && (a[i] < tmp)) {
                i++;
            }
            if (i == j) {
                break;
            }
            a[hole] = a[i];
            hole = i;
        }
        a[hole] = tmp;

        this->quickSort(a, start, hole - 1);
        this->quickSort(a, hole + 1, end);
    }

    template<typename elemType>
    void adjust(elemType a[], int n, int i) {
        int maxChild;
        elemType temp;
        
        while (true) {
            maxChild = 2 * i + 1;

            if (maxChild > n - 1) {
                return;
            }
            if (maxChild + 1 <= n - 1) {
                if (a[maxChild + 1] >= a[maxChild]) {
                    maxChild++;
                }
            }

            if (a[i] > a[maxChild]) {
                return;
            }

            temp = a[i];
            a[i] = a[maxChild];
            a[maxChild] = temp;

            i = maxChild;
        }
    }
public:
    void bubbleSort(elemType a[], int n);
    void insertSort(elemType a[], int n);
    void shellSort(elemType a[], int n);
    void mergeSort(elemType a[], int n);
    void quickSort(elemType a[], int n);    
    void selectSort(elemType a[], int n);
    void heapSort(elemType a[], int n);
};

template<typename elemType>
void sort<elemType>::bubbleSort(elemType a[], int n) {
    int i, j;
    bool change = true;
    elemType tmp;

    for (j = n - 1; j > 0 && change; j--) {
        change = false;
        for (i = 0; i < j; i++) {
            if (a[i] > a[i + 1]) {
                tmp = a[i];
                a[i] = a[i + 1];
                a[i + 1] = tmp;
                change = true;
            }
        }
    }
}

template<typename elemType>
void sort<elemType>::insertSort(elemType a[], int n) {
    int i;
    elemType tmp;

    for (i = 1; i < n; i++) {
        tmp = a[i];
        this->insert(a, i, tmp);
    }
}

template<typename elemType>
void sort<elemType>::shellSort(elemType a[], int n) {
    int step, i, j;
    elemType tmp;

    for (step = n / 2; step > 0; step /= 2) {
        for (i = step; i < n; i++) {
            tmp = a[i];
            j = i;
            
            while ((j - step >= 0) && (tmp < a[j - step])) {
                a[j] = a[j - step];
                j -= step;
            }

            a[j] = tmp;
        }
    }
}

template<typename elemType>
void sort<elemType>::mergeSort(elemType a[], int n) {
    this->mergeSort(a, 0, n - 1);
}

template<typename elemType>
void sort<elemType>::quickSort(elemType a[], int n) {
    this->quickSort(a, 0, n - 1);
}

template<typename elemType>
void sort<elemType>::selectSort(elemType a[], int n) {
    int i, j, minI;
    elemType tmp;

    for (i = 0; i < n; i++) {
        minI = i;
        for (j = i + 1; j < n; j++) {
            if (a[j] < a[minI]) {
                minI = j;
            }
        }

        if (minI == i) {
            continue;
        }

        tmp = a[i];
        a[i] = a[minI];
        a[minI] = tmp;
    }
}

template<typename elemType>
void sort<elemType>::heapSort(elemType a[], int n) {
    int i, j;
    elemType temp;

    for (i = n / 2 - 1; i >= 0; i--) {
        this->adjust(a, n, i);
    }

    for (j = n - 1; j >= 1; j--) {
        temp = a[0];
        a[0] = a[j];
        a[j] = temp;
        adjust(a, j, 0);
    }
}

#endif // SORT_H_INCLUDED