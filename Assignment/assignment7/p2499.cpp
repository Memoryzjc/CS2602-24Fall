#include<iostream>
#include<vector>

int main() {
    int n, val;
    int num0 = 0, num1 = 0, num2 = 0;
    int num00[3], num11[3], num22[3];  // store the number in wrong place
    std::vector<int> nums;

    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> val;
        nums.push_back(val);

        if (val == 0) {
            num0++;
        } else if (val == 1) {
            num1++;
        } else if (val == 2) {
            num2++;
        }
    }
    
    num00[0] = 0;
    num00[1] = 0;
    num00[2] = 0;
    for (int i = 0; i < num0; i++) {
        if (nums[i] == 1) {
            num00[1]++;
        } else if (nums[i] == 2) {
            num00[2]++;
        }
    }

    num11[0] = 0;
    num11[1] = 0;
    num11[2] = 0;
    for (int i = num0; i < num0 + num1; i++) {
        if (nums[i] == 0) {
            num11[0]++;
        } else if (nums[i] == 2) {
            num11[2]++;
        }
    }

    num22[0] = 0;
    num22[1] = 0;
    num22[2] = 0;
    for (int i = num0 + num1; i < n; i++) {
        if (nums[i] == 0) {
            num22[0]++;
        } else if (nums[i] == 1) {
            num22[1]++;
        }
    }

    int result = 0, swap01, swap02, swap12;

    swap01 = (num00[1] < num11[0]) ? num00[1] : num11[0];
    result += swap01;
    num00[1] -= swap01;
    num11[0] -= swap01;

    swap02 = (num00[2] < num22[0]) ? num00[2] : num22[0];
    result += swap02;
    num00[2] -= swap02;
    num22[0] -= swap02;

    swap12 = (num11[2] < num22[1]) ? num11[2] : num22[1];
    result += swap12;
    num11[2] -= swap12;
    num22[1] -= swap12;

    result += num00[1] + num00[2] + num11[0] + num11[2] + num22[0] + num22[1];

    std::cout << result;
    return 0;
}