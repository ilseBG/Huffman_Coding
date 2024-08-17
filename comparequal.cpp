#include <iostream>
#include <fstream>

using namespace std;

int compareFiles(const string& file1, const string& file2) {
    ifstream f1(file1, ios::binary);
    ifstream f2(file2, ios::binary);

    if (!f1.is_open() || !f2.is_open()) {
        cerr << "Error opening one or both files." << endl;
        return false;
    }

    char ch1, ch2;
    int bitcnt = 0;
    while (f1.get(ch1) && f2.get(ch2)) {
        if (ch1 != ch2) {
            return false;
        }
        bitcnt++;
    }
    int cnt1 = bitcnt;
    while(f1.get(ch1))
        cnt1++;
    cout << "file1 cnt " << cnt1 << endl;

    int cnt2 = bitcnt;
    while(f2.get(ch1))
        cnt1++;
    cout << "file2 cnt " << cnt2 << endl;
    // Check if both files reached the end at the same time
    return bitcnt;
}

int countbitfile(const string& file) {
    ifstream f1(file, ios::binary);
    int bitcnt = 0;
    char byte;
    while (f1.get(byte)) {
        bitcnt+=8;
    }
    // cout << "bit cnt " << bitcnt << endl;
    return bitcnt;
}

int main() {
    string file1 = "output.txt";
    string file2 = "bitstring.txt";

    cout << "the same bit cnt " << compareFiles(file1, file2) << endl;
    
    cout << "coded file bit cnt "  << countbitfile("output.huf") << endl;

    return 0;
}
