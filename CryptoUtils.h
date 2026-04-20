#ifndef CRYPTOUTILS_H
#define CRYPTOUTILS_H

#include <string>
#include <random>
#include <sstream>
#include <iomanip>

// Simplified ZKP using smaller primes for simulation
// In production, use proper cryptographic libraries
class CryptoUtils {
private:
    static const long long PRIME = 2147483647LL;  // Large Mersenne prime
    static const long long GENERATOR = 16807LL;    // Primitive root
    
public:
    // Modular exponentiation: (base^exp) mod mod
    static long long modPow(long long base, long long exp, long long mod) {
        long long result = 1;
        base = base % mod;
        while (exp > 0) {
            if (exp % 2 == 1) {
                result = (result * base) % mod;
            }
            exp = exp >> 1;
            base = (base * base) % mod;
        }
        return result;
    }
    
    // Generate random number in range [min, max]
    static long long random(long long min, long long max) {
        static std::random_device rd;
        static std::mt19937_64 gen(rd());
        std::uniform_int_distribution<long long> dis(min, max);
        return dis(gen);
    }
    
    // Convert number to string
    static std::string toString(long long num) {
        return std::to_string(num);
    }
    
    // Convert string to number
    static long long fromString(const std::string& str) {
        return std::stoll(str);
    }
    
    // Get prime p
    static long long getPrime() {
        return PRIME;
    }
    
    // Get generator g
    static long long getGenerator() {
        return GENERATOR;
    }
    
    // Generate private key
    static long long generatePrivateKey() {
        return random(2, PRIME - 2);
    }
    
    // Generate public key: y = g^x mod p
    static long long generatePublicKey(long long privateKey) {
        return modPow(GENERATOR, privateKey, PRIME);
    }
};

#endif
