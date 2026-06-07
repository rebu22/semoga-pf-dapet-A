#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <stdexcept>
#include <string>
#include <iomanip>

//  Konstanta
static const long long DEFAULT_N = 2'000'000;
static const long long MAX_N     = 20'000'000;

std::vector<bool> sieve(long long n) {
    std::vector<bool> is_prime(n + 1, true);

    is_prime[0] = false;
    is_prime[1] = false;

    long long limit = static_cast<long long>(std::sqrt(static_cast<double>(n)));

    // Nested loop
    for (long long i = 2; i <= limit; ++i) {
        if (is_prime[i]) {
            for (long long j = i * i; j <= n; j += i) {
                is_prime[j] = false;   // eliminasi satu per satu
            }
        }
    }

    return is_prime;
}

//  Hitung jumlah prima dari vector hasil sieve
long long countPrimes(const std::vector<bool>& is_prime, long long n) {
    long long count = 0;
    for (long long i = 2; i <= n; ++i) {
        if (is_prime[i]) ++count;
    }
    return count;
}

//  Tampilkan banner
void printBanner() {
    std::cout << "============================================";
    std::cout << "   Sieve of Eratosthenes  C++ Version   ";
    std::cout << "   Minggu 2: Implementasi C++ & Manajemen  ";
    std::cout << "   Memori | Opsi 3                         ";
    std::cout << "============================================";
}

//  Main
int main(int argc, char* argv[]) {
    printBanner();

    long long N = DEFAULT_N;
    if (argc >= 2) {
        try {
            N = std::stoll(argv[1]);
            if (N < 2) {
                std::cerr << "[ERROR] N harus >= 2.";
                return 1;
            }
            if (N > MAX_N) {
                std::cerr << "[ERROR] N melebihi batas maksimal " << MAX_N << ".";
                return 1;
            }
        } catch (const std::exception& e) {
            std::cerr << "[ERROR] Argumen tidak valid: " << e.what() << "";
            return 1;
        }
    }

    std::cout << "Batas N          : " << N << "";
    std::cout << "Memori dialokasi : std::vector<bool> ukuran "
              << (N + 1) << " elemen\n";
    std::cout << "                   (~" << std::fixed << std::setprecision(2)
              << static_cast<double>(N + 1) / 8.0 / 1024.0 / 1024.0
              << " MB — bitset internal)\n\n";

    //  Mulai pengukuran waktu
    auto start = std::chrono::high_resolution_clock::now();

    // Jalankan sieve (alokasi + komputasi)
    std::vector<bool> is_prime = sieve(N);

    // Hitung jumlah prima
    long long jumlah_prima = countPrimes(is_prime, N);

    auto end = std::chrono::high_resolution_clock::now();

    //  Hitung durasi dalam berbagai satuan
    auto duration_ns  = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    double duration_us = duration_ns / 1'000.0;
    double duration_ms = duration_ns / 1'000'000.0;
    double duration_s  = duration_ns / 1'000'000'000.0;

    //  Output 
    std::cout << "============================================";
    std::cout << "  HASIL\n";
    std::cout << "============================================";
    std::cout << "Batas N              : " << N << "";
    std::cout << "Jumlah bilangan prima: " << jumlah_prima << "";
    std::cout << "";
    std::cout << "Waktu eksekusi:";
    std::cout << "  " << std::fixed << std::setprecision(2)
              << duration_us << " mikrodetik";
    std::cout << "  " << std::fixed << std::setprecision(4)
              << duration_ms << " milidetik";
    std::cout << "  " << std::fixed << std::setprecision(6)
              << duration_s  << " detik";
    std::cout << "============================================";

    // is_prime otomatis didealokasi di sini saat keluar scope
    // → tidak ada memory leak (RAII)

    return 0;
}

