#include "iostream"

long long find_power(long long f, long long s, long long m) {
    long long ans;
    if (s == 0) {
        return 1;
    } else if (s % 2 != 0) {
        ans = f * find_power(f, s - 1, m);
        return ans % m;
    }
    long long temp = find_power(f, s / 2, m);
    ans = temp * (temp % m);

    return ans % m;
}

int main() {
    int n;
    std::cin >> n;

    long long m, p, q, d;
    m = 999999893;

    p = 2 * (find_power(2, n / 2, m) - 1) % m;
    q = find_power(2, (n + 1) / 2, m);
    d = (p * p + (m - q) * q * 2) % m;

    std::cout << 2 * (m - p) * find_power(d, m - 2, m) % m;
}
