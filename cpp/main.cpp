#include <iostream>
#include <chrono>

int main() {
    // DEKLARASI
    int  N, limit, i, j, count;
    long long start_time, end_time, duration;
    bool* prima = nullptr;

    // INPUT
    // Input nilai batas N maks = 20.000.000
    std::cout << "Masukkan nilai batas atas N (maks 20.000.000): ";
    std::cin >> N;

    // VALIDASI
    // N valid? → Tidak → Menampilkan Pesan Error → Selesai
    if (N < 2 || N > 20000000) {
        std::cout << "Menampilkan Pesan Error: N harus antara 2 sampai 20.000.000!";
        return 0;  // → Selesai (bukan exit paksa)
    }

    // ALOKASI DINAMIS
    prima = new bool[N + 1];

    // INISIALISASI SEMUA ELEMEN TRUE
    for (i = 0; i <= N; i++)
        prima[i] = true;

    // ELIMINASI ANGKA 0 DAN 1
    prima[0] = false;
    prima[1] = false;

    // NYALAKAN STOPWATCH
    start_time = std::chrono::duration_cast<std::chrono::nanoseconds>(
        std::chrono::high_resolution_clock::now().time_since_epoch()).count();

    // PROSES NESTED LOOP
    // Outer Loop i = 2, cek i <= √N
    limit = 0;
    while ((limit + 1) * (limit + 1) <= N) limit++;  // limit = √N

    i = 2;
    while (i <= limit) {                  // i <= √N ?
        if (prima[i] == true) {           // prima[i] == TRUE ?
            j = i * i;                    // Loop Dalam j = i x i
            while (j <= N) {              // j <= N ?
                prima[j] = false;         // prima[j] = FALSE (coret kelipatan)
                j = j + i;               // j += i
            }
        }
        i = i + 1;                        // i = i + 1
    }

    // END STOPWATCH
    end_time = std::chrono::duration_cast<std::chrono::nanoseconds>(
        std::chrono::high_resolution_clock::now().time_since_epoch()).count();

    // HITUNG JUMLAH PRIMA
    count = 0;
    for (i = 2; i <= N; i++) {
        if (prima[i] == true)
            count = count + 1;
    }

    // HITUNG DURASI
    duration = end_time - start_time;

    // OUTPUT
    std::cout << "Total jumlah bilangan prima ditemukan: " << count << "\n";
    std::cout << "Total waktu eksekusi algoritma: " << duration / 1000 << " microseconds\n";

    // DEALOKASI MEMORI
    delete[] prima;
    prima = nullptr;

    return 0;
}
