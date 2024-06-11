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

void tambahFilm() {
    string bioskop, judulFilm, waktuTayang;
    int harga;

    clearScreen();
    printHeaderTambah();

    // Pilih Bioskop
    cout << endl;
    cout << "+----------------------------------------------+" << endl;
    cout << "|                Pilih Bioskop                 |" << endl;
    cout << "+----------------------------------------------+" << endl;
    cout << "| 1. XXI BOEMI KEDATON                         |" << endl;
    cout << "| 2. CGV CIPLAZ                                |" << endl;
    cout << "+----------------------------------------------+" << endl;
    cout << "Pilih Opsi: ";
    int pilihan;
    cin >> pilihan;

    if (pilihan == 1) {
        bioskop = "A";
    } else if (pilihan == 2) {
        bioskop = "B";
    } else {
        cout << "Pilihan tidak valid!" << endl;
        system("pause");
        return tambahFilm(); 
    }

cout << "Masukkan judul film: ";
    cin.ignore(); 
    getline(cin, judulFilm);
    cout << "Masukkan waktu tayang: ";
    getline(cin, waktuTayang);
    cout << "Masukkan harga tiket: ";
    cin >> harga;

    jadwalFilm[bioskop].push_back({judulFilm, waktuTayang, harga});
    sortFilms(bioskop); 
    cout << "Film berhasil ditambahkan!" << endl;
    system("pause");
}
void tampilkanJadwal(const string& bioskop) {
    clearScreen();
    printHeaderJadwal();

    vector<string> headers = {"No", "Judul", "Waktu", "Harga"};
    vector<vector<string>> rows;
    if (jadwalFilm.find(bioskop) != jadwalFilm.end()) {
        for (size_t i = 0; i < jadwalFilm[bioskop].size(); ++i) {
            rows.push_back({
                to_string(i + 1),
                jadwalFilm[bioskop][i].judul,
                jadwalFilm[bioskop][i].waktu,
                "Rp" + to_string(jadwalFilm[bioskop][i].harga)
            });
        }
    }

    printTable(headers, rows);
    system("pause");
}

void displaySeatChart() {
    clearScreen();
    printHeaderCek();
    cout << "Kursi Tersedia" << endl;

    cout << "+------------------------+" << endl;
    cout << "|         Screen         |" << endl;
    cout << "+------------------------+" << endl;
    for (int i = 1; i <= 4; ++i) {
        for (int j = 1; j <= 5; ++j) {
            int seatNumber = (i-1)*5+ j;
            string seatNumberString = (seatNumber < 10) ? "0" + to_string(seatNumber) : to_string(seatNumber); 
            auto it = find_if(kursiList.begin(), kursiList.end(), [seatNumber](const Kursi& k) { return k.nomor == seatNumber; });
            if (it != kursiList.end() && !it->tersedia) {
                setColor(4); // Merah untuk kursi yang sudah dipesan
            } else {
                setColor(2); // Hijau untuk kursi yang tersedia
            }
            cout << "| " << setw(2) << seatNumber << " ";
            setColor(15); // Mengembalikan warna ke default
        }
        cout << "|" << endl;
    }
    cout << "+------------------+" << endl;
    cout << "Tekan Enter Untuk Melanjutkan...";
    cin.ignore();
    cin.get();
}

string pilihBioskop() {
    clearScreen();
    printHeader();
    cout << "Pilih Bioskop" << endl;
    cout << "+----------------------------------------------+" << endl;
    cout << "| 1. XXI BOEMI KEDATON                         |" << endl;
    cout << "| 2. CGV CIPLAZ                                |" << endl;
    cout << "+----------------------------------------------+" << endl;
    cout << "Pilih Opsi: ";
    int pilihan;
    cin >> pilihan;

    if (pilihan == 1) {
        return "A";
    } else if (pilihan == 2) {
        return "B";
    } else {
        cout << "Pilihan tidak valid!" << endl;
        system("pause");
        return pilihBioskop();
    }
}

void pesanTiket() {
    int pilihanFilm, pilihanKursi;
    string bioskop = pilihBioskop();
    tampilkanJadwal(bioskop);
    cout << "Pilih film (nomor): ";
    cin >> pilihanFilm;

    if (pilihanFilm < 1 || pilihanFilm > jadwalFilm[bioskop].size()) {
cout << "Pilihan film tidak valid!" << endl;
system("pause");
return;
}
Film filmDipilih = jadwalFilm[bioskop][pilihanFilm - 1];
cout << "Film: " << filmDipilih.judul << endl;
cout << "Waktu: " << filmDipilih.waktu << endl;
cout << "Harga: Rp" << filmDipilih.harga << endl;

displaySeatChart();
cout << "Pilih kursi (nomor): ";
cin >> pilihanKursi;

auto it = find_if(kursiList.begin(), kursiList.end(), [pilihanKursi](const Kursi& k) { return k.nomor == pilihanKursi; });

if (it == kursiList.end() || !it->tersedia) {
    cout << "Pilihan kursi tidak valid!" << endl;
    system("pause");
    return;
}

it->tersedia = false;

cout << "Konfirmasi pembelian tiket sebesar Rp. " << filmDipilih.harga<<"(y/n):";
char konfirmasi;
cin >> konfirmasi;

if (konfirmasi == 'y' || konfirmasi == 'Y') {
    Tiket tiket(filmDipilih.judul, filmDipilih.waktu, filmDipilih.harga, pilihanKursi);
    tiketList.push_back(tiket);
    cout << "Tiket berhasil dipesan!" << endl;
    cout << "Tiket Anda:" << endl;
    cout << "Film: " << tiket.judul << endl;
    cout << "Waktu: " << tiket.waktu << endl;
    cout << "Harga: Rp" << tiket.harga << endl;
    cout << "Nomor Kursi: " << tiket.nomorKursi << endl;
    system("pause");
} else {
    it->tersedia = true;
    cout << "Pemesanan dibatalkan." << endl;
    system("pause");
}
}

void cetakTiket(const Tiket& tiket) {
clearScreen();
printHeaderCek();
cout << "Cetak Tiket" << endl;
// Membuat kotak menyerupai tiket bioskop
cout << "+-------------------------------------------------------------------------------------------------+" << endl;
cout << "|                                Sistem Pemesanan Tiket Bioskop                                   |" << endl;
cout << "+-------------------------------------------------------------------------------------------------+" << endl;
cout << "| Nama Bioskop : Cinema XXI                                                                       |" << endl;
cout << "| Judul Film  : " << tiket.judul << string(40 - tiket.judul.size(), ' ') <<"                                          |" << endl;
cout << "| Waktu Tayang: " << tiket.waktu << string(40 - tiket.waktu.size(), ' ') <<"                                          |" << endl;
cout << "| Harga       : Rp" << tiket.harga << string(37 - to_string(tiket.harga).size(), ' ') <<"                                           |" << endl;
cout << "| Nomor Kursi : " << tiket.nomorKursi << string(40 - to_string(tiket.nomorKursi).size(), ' ') <<"                                          |" << endl;
cout << "+-------------------------------------------------------------------------------------------------+" << endl;
cout << "| Barcode      : ";

// Menampilkan barcode menggunakan karakter ASCII
string barcode = "|| |||  || |||| | || | ||| ||| |"; // Contoh pola barcode        
cout << barcode << "                                                 |" << endl;
cout << "+-------------------------------------------------------------------------------------------------+" << endl;

system("pause");
}

void cekTiket() {
clearScreen();
printHeaderCek();
cout << "Daftar Tiket" << endl;
vector<string> headers = {"No", "Judul Film", "Waktu", "Harga", "Nomor Kursi"};
vector<vector<string>> rows;
for (size_t i = 0; i < tiketList.size(); ++i) {
    rows.push_back({
        to_string(i + 1),
        tiketList[i].judul,
        tiketList[i].waktu,
        "Rp" + to_string(tiketList[i].harga),
        to_string(tiketList[i].nomorKursi)
    });
}
printTable(headers, rows);

if (!tiketList.empty()) {
    cout << "Pilih tiket yang ingin dicetak (nomor): ";
    int pilihan;
    cin >> pilihan;

    if (pilihan < 1 || pilihan > tiketList.size()) {
        cout << "Pilihan tidak valid!" << endl;
    } else {
        cetakTiket(tiketList[pilihan - 1]);
    }
}

system("pause");
}

