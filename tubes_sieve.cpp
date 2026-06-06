#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <stdexcept>
#include <string>
#include <iomanip>

// ============================================================
//  Konstanta
// ============================================================
static const long long DEFAULT_N = 2'000'000;
static const long long MAX_N     = 20'000'000;

std::vector<bool> sieve(long long n) {
    // Alokasi dinamis: std::vector<bool> dioptimasi compiler
    // menjadi bitset internal (~2.5 MB untuk N=20.000.000)
    std::vector<bool> is_prime(n + 1, true);

    // 0 dan 1 bukan bilangan prima
    is_prime[0] = false;
    is_prime[1] = false;

    long long limit = static_cast<long long>(std::sqrt(static_cast<double>(n)));

    // Nested loop: eliminasi kelipatan satu per satu
    for (long long i = 2; i <= limit; ++i) {
        if (is_prime[i]) {
            // Mulai dari i*i karena kelipatan lebih kecil
            // sudah ditandai oleh faktor prima sebelumnya
            for (long long j = i * i; j <= n; j += i) {
                is_prime[j] = false;   // eliminasi satu per satu
            }
        }
    }

    return is_prime;  // move semantics — efisien, tidak copy
}

// ============================================================
//  Hitung jumlah prima dari vector hasil sieve
// ============================================================
long long countPrimes(const std::vector<bool>& is_prime, long long n) {
    long long count = 0;
    for (long long i = 2; i <= n; ++i) {
        if (is_prime[i]) ++count;
    }
    return count;
}

// ============================================================
//  Tampilkan banner
// ============================================================
void printBanner() {
    std::cout << "============================================\n";
    std::cout << "   Sieve of Eratosthenes  C++ Version   \n";
    std::cout << "   Minggu 2: Implementasi C++ & Manajemen  \n";
    std::cout << "   Memori | Opsi 3                         \n";
    std::cout << "============================================\n\n";
}

// ============================================================
//  Main
// ============================================================
int main(int argc, char* argv[]) {
    printBanner();

    // Baca N dari argumen baris perintah (opsional)
    long long N = DEFAULT_N;
    if (argc >= 2) {
        try {
            N = std::stoll(argv[1]);
            if (N < 2) {
                std::cerr << "[ERROR] N harus >= 2.\n";
                return 1;
            }
            if (N > MAX_N) {
                std::cerr << "[ERROR] N melebihi batas maksimal " << MAX_N << ".\n";
                return 1;
            }
        } catch (const std::exception& e) {
            std::cerr << "[ERROR] Argumen tidak valid: " << e.what() << "\n";
            return 1;
        }
    }

    std::cout << "Batas N          : " << N << "\n";
    std::cout << "Memori dialokasi : std::vector<bool> ukuran "
              << (N + 1) << " elemen\n";
    std::cout << "                   (~" << std::fixed << std::setprecision(2)
              << static_cast<double>(N + 1) / 8.0 / 1024.0 / 1024.0
              << " MB — bitset internal)\n\n";

    // ----------------------------------------------------------
    //  Mulai pengukuran waktu
    // ----------------------------------------------------------
    auto start = std::chrono::high_resolution_clock::now();

    // Jalankan sieve (alokasi + komputasi)
    std::vector<bool> is_prime = sieve(N);

    // Hitung jumlah prima
    long long jumlah_prima = countPrimes(is_prime, N);

    auto end = std::chrono::high_resolution_clock::now();

    // ----------------------------------------------------------
    //  Hitung durasi dalam berbagai satuan
    // ----------------------------------------------------------
    auto duration_ns  = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    double duration_us = duration_ns / 1'000.0;
    double duration_ms = duration_ns / 1'000'000.0;
    double duration_s  = duration_ns / 1'000'000'000.0;

    // ----------------------------------------------------------
    //  Output hasil
    // ----------------------------------------------------------
    std::cout << "============================================\n";
    std::cout << "  HASIL\n";
    std::cout << "============================================\n";
    std::cout << "Batas N              : " << N << "\n";
    std::cout << "Jumlah bilangan prima: " << jumlah_prima << "\n";
    std::cout << "\n";
    std::cout << "Waktu eksekusi:\n";
    std::cout << "  " << std::fixed << std::setprecision(2)
              << duration_us << " mikrodetik\n";
    std::cout << "  " << std::fixed << std::setprecision(4)
              << duration_ms << " milidetik\n";
    std::cout << "  " << std::fixed << std::setprecision(6)
              << duration_s  << " detik\n";
    std::cout << "============================================\n\n";

    // is_prime otomatis di-dealokasi di sini saat keluar scope
    // → tidak ada memory leak (RAII)

    return 0;
}

