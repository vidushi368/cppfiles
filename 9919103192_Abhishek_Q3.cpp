#include <bits/stdc++.h>
#include<iostream>
using namespace std;

template<typename T>
void selection(T arr[], int size) {
    T Maximum;
    int max_ind;

    for (int i = size - 1; i >= 1; --i) {
        Maximum = -1;
        max_ind = i;
        for (int j = i; j >= 0; --j) {
            if (arr[j] > Max) {
                Maximum = arr[j];
                max_ind = j;
            }
        }
        swap(arr[i], arr[max_ind]);
    }
}

template<typename T>
void insertion(T arr[], int size) {
    T key;
    int j;
    for (int i = 1; i < size; ++i) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 and arr[j] > key) {
            arr[j + 1] = arr[j];
            j -= 1;
        }
        arr[j + 1] = key;
    }
}

class obj {
public:
    int value;

    obj() = default;

    obj(int value) : value(value) {}
};

bool operator>(obj a, obj b) {
    return a.value > b.value;
}

int main() {
    int arr[] = {10, 9, 8, 7, 6};
    float arr2[] = {10.1, 9.9, 8.8, 7.7, 6.6};
    string arr3[] = {"f", "d", "c", "b", "a"};
    obj arr4[] = {10, 9, 8, 7, 6};

    cout << "Selection: \n";
    selection(arr, 5);
    selection(arr2, 5);
    selection(arr3, 5);
    selection(arr4, 5);
    for (auto x: arr)
        cout << x << " ";
    cout << "\n";
    for (auto x: arr2)
        cout << x << " ";
    cout << "\n";
    for (const auto &x: arr3)
        cout << x << " ";
    cout << "\n";
    for (auto x: arr4)
        cout << x.value << " ";
    cout << "\n";

    int arr5[] = {10, 9, 8, 7, 6};
    float arr6[] = {10.1, 9.9, 8.8, 7.7, 6.6};
    string arr7[] = {"f", "d", "c", "b", "a"};
    obj arr8[] = {10, 9, 8, 7, 6};


    cout << "\nInsertion: \n";
    selection(arr6, 5);
    selection(arr7, 5);
    selection(arr8, 5);
    selection(arr5, 5);
    for (auto x: arr5)
        cout << x << " ";
    cout << "\n";
    for (auto x: arr6)
        cout << x << " ";
    cout << "\n";
    for (const auto &x: arr7)
        cout << x << " ";
    cout << "\n";
    for (auto x: arr8)
        cout << x.value << " ";
    cout << "\n";
}
