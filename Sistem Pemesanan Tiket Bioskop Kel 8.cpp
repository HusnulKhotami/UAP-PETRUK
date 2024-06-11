#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <list>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <iomanip>
#include <stack>
#include <queue>

using namespace std;

struct Film {
    string judul;
    string waktu;
    int harga;
};

class Kursi {
public:
    int nomor;
    bool tersedia;

    Kursi(int n, bool t) : nomor(n), tersedia(t) {}
};

class Tiket {
public:
    string judul;
    string waktu;
    int harga;
    int nomorKursi;

    Tiket(string j, string w, int h, int nK) : judul(j), waktu(w), harga(h), nomorKursi(nK) {}
};

template<typename T>
void cetakAntrian(queue<T> q) {
    while (!q.empty()) {
        cout << q.front() << " ";
        q.pop();
    }
    cout << endl;
} 

void merge(vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; ++i)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; ++j)
        R[j] = arr[m + 1 + j];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            ++i;
        } else {
            arr[k] = R[j];
            ++j;
        }
        ++k;
    }
    while (i < n1) {
        arr[k] = L[i];
        ++i;
        ++k;
    }
    while (j < n2) {
        arr[k] = R[j];
        ++j;
        ++k;
    }
}


void mergeSort(vector<int>& arr, int l, int r) {
    if (l >= r) return;
    int m = l + (r - l) / 2;
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
}
