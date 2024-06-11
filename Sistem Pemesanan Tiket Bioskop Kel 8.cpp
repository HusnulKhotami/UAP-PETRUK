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
