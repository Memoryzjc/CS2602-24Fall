class illegalSize{};

template<typename elemType>
class staticSearch
{
private:
    elemType *data;
    int len;
public:
    staticSearch(elemType a[], int n)
    {
        this->len = n;
        this->data = new elemType[n + 1];
        
        if (!this->data) {
            throw illegalSize();
        }

        for (int i = 1; i < n + 1; i++) {
            this->data[i] = a[i - 1];
        }
    }

    int Search(const elemType &x) const
    {
        int i;
        this->data[0] = x;

        for (int i = len; data[i] != x; i--) {}

        return i;
    }

    int BSearch(const elemType &x) const
    {
        int mid, low, high;
        
        low = 1;
        high = this->len;

        while (low <= high) {
            mid = (low + high) / 2;
            if (x == data[mid]) {
                break;
            } else if (x > data[mid]) {
                low = mid + 1;
            } else {
                high = mid + 1;
            }
        }

        if (low <= high) {
            return mid;
        }

        return 0;
    }

    ~staticSearch()
    {
        delete []data;
    }
};