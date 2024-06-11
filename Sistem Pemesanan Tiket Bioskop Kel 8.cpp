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

void cetakCString(const char* cstr) {
    cout << cstr << endl;
}


map<string, string> pengguna;
map<string, vector<Film>> jadwalFilm;
list<Kursi> kursiList;
vector<Tiket> tiketList;

void setCursorPosition(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void clearScreen() {
    system("cls");
}

void printHeader() {
    cout << "+----------------------------------------------+" << endl;
    cout << "|        Sistem Pemesanan Tiket Bioskop        |" << endl;
    cout << "+----------------------------------------------+" << endl;
}

void printHeaderTambah() {
    cout << " ==============================================" << endl;
    cout << "||                TAMBAH FILM                 ||" << endl;
    cout << " ==============================================" << endl;
}

void printHeaderJadwal() {
    cout << " ====================================================================================" << endl;
    cout << "||                                    Jadwal Film                                   ||" << endl;
    cout << " ====================================================================================" << endl;
}

void printHeaderCek() {
    cout << " ========================================================================================================" << endl;
    cout << "||                                             Cek Tiket                                                ||" << endl;
    cout << " ========================================================================================================" << endl;
}

void printMenu() {
    cout << "+----------------------------------------------+" << endl;
    cout << "| 1. Register                                  |" << endl;
    cout << "| 2. Login                                     |" << endl;
    cout << "| 3. Exit                                      |" << endl;
    cout << "+----------------------------------------------+" << endl;
    cout << "Pilih Opsi: ";
}

void printTable(const vector<string>& headers, const vector<vector<string>>& rows) {
    int colWidth = 20;
    int tableWidth = headers.size() * colWidth + headers.size() + 1;

    cout << "+";
    for (int i = 0; i < tableWidth - 2; i++) cout << "-";
    cout << "+" << endl;

    cout << "|";
    for (const auto& header : headers) {
        cout << " " << header << string(colWidth - header.size() - 1, ' ') << "|";
    }
    cout << endl;

    cout << "+";
    for (int i = 0; i < tableWidth - 2; i++) cout << "-";
    cout << "+" << endl;

    for (const auto& row : rows) {
        cout << "|";
        for (const auto& cell : row) {
            cout << " " << cell << string(colWidth - cell.size() - 1, ' ') << "|";
        }
        cout << endl;
    }

    cout << "+";
    for (int i = 0; i < tableWidth - 2; i++) cout << "-";
    cout << "+" << endl;
}

void registrasi() {
    string username, password;
    clearScreen();
    printHeader();
    cout << "Registrasi Pengguna" << endl;
    cout << "Masukkan username: ";
    cin >> username;
    cout << "Masukkan password: ";
    cin >> password;
    pengguna[username] = password;
    cout << "Registrasi berhasil!" << endl;
    system("pause");
}

bool login() {
    string username, password;
    clearScreen();
    printHeader();
    cout << "Login Pengguna" << endl;
    cout << "Masukkan username: ";
    cin >> username;
    cout << "Masukkan password: ";
    cin >> password;

    if ((username == "messi" && password == "123") ||
        (pengguna.find(username) != pengguna.end() && pengguna[username] == password)) {
        cout << "Login berhasil!" << endl;
        system("pause");
        return true;
    } else {
        cout << "Username atau password salah!" << endl;
        system("pause");
        return false;
    }
}

int timeToMinutes(const string& time) {
    int hours = stoi(time.substr(0, 2));
    int minutes = stoi(time.substr(3, 2));
    return hours * 60 + minutes;
}

void sortFilms(const string& bioskop) {
    if (jadwalFilm.find(bioskop) != jadwalFilm.end()) {
        sort(jadwalFilm[bioskop].begin(), jadwalFilm[bioskop].end(), [](const Film& a, const Film& b) {
            return timeToMinutes(a.waktu) < timeToMinutes(b.waktu);
        });
    }
}

