#include <bits/stdc++.h>
using namespace std;

#define d 256          // Number of characters in input alphabet
#define q 101          // A prime number for modulo operation

// Rabin-Karp pattern searching function
void rabinKarp(string text, string pattern) {
    int n = text.length();
    int m = pattern.length();
    
    int pHash = 0;      // hash value for pattern
    int tHash = 0;      // hash value for text window
    int h = 1;

    // The value of h would be pow(d, m-1) % q
    for (int i = 0; i < m - 1; i++)
        h = (h * d) % q;

    // Calculate hash for pattern and first window of text
    for (int i = 0; i < m; i++) {
        pHash = (d * pHash + pattern[i]) % q;
        tHash = (d * tHash + text[i]) % q;
    }

    // Slide the pattern over text one by one
    for (int i = 0; i <= n - m; i++) {
        // If hash values match, check characters one by one
        if (pHash == tHash) {
            bool match = true;
            for (int j = 0; j < m; j++) {
                if (text[i + j] != pattern[j]) {
                    match = false;
                    break;
                }
            }
            if (match)
                cout << "Pattern found at index " << i << endl;
        }

        // Calculate hash for next window
        if (i < n - m) {
            tHash = (d * (tHash - text[i] * h) + text[i + m]) % q;

            // We might get negative value of tHash, convert it to positive
            if (tHash < 0)
                tHash += q;
        }
    }
}

// Driver code
int main() {
    string text = "ABCCDDAEFG";
    string pattern = "CDD";
    rabinKarp(text, pattern);
    return 0;
}
