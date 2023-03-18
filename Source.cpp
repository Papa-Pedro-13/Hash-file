#include <cstdlib>
#include <cerrno>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <stdexcept>
#pragma warning(disable : 4996)
#include <openssl/sha.h>
#include <openssl/md5.h>
using namespace std;
inline string
SHA256(const char* const path)
{
    ifstream fp(path, ios::in |ios::binary);

    if (not fp.good()) {
        ostringstream os;
        os << "Cannot open \"" << path << "\": " << strerror(errno) << ".";
        throw runtime_error(os.str());
    }

    constexpr const size_t buffer_size{ 1 << 12 };
    char buffer[buffer_size];

    unsigned char hash[SHA256_DIGEST_LENGTH] = { 0 };

    SHA256_CTX ctx;
    SHA256_Init(&ctx);

    while (fp.good()) {
        fp.read(buffer, buffer_size);
        SHA256_Update(&ctx, buffer, fp.gcount());
    }

    SHA256_Final(hash, &ctx);
    fp.close();

    ostringstream os;
    os << hex << setfill('0');

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        os << setw(2) << static_cast<unsigned int>(hash[i]);
    }

    return os.str();
}
using namespace std;
inline string
MD5(const char* const path)
{
    ifstream fp(path, ios::in | ios::binary);

    if (not fp.good()) {
        ostringstream os;
        os << "Cannot open \"" << path << "\": " << strerror(errno) << ".";
        throw runtime_error(os.str());
    }

    constexpr const size_t buffer_size{ 1 << 12 };
    char buffer[buffer_size];

    unsigned char hash[MD5_DIGEST_LENGTH] = { 0 };

    MD5state_st ctx;
    MD5_Init(&ctx);

    while (fp.good()) {
        fp.read(buffer, buffer_size);
        MD5_Update(&ctx, buffer, fp.gcount());
    }

    MD5_Final(hash, &ctx);
    fp.close();

    ostringstream os;
    os << hex << setfill('0');

    for (int i = 0; i < MD5_DIGEST_LENGTH; ++i) {
        os << setw(2) << static_cast<unsigned int>(hash[i]);
    }

    return os.str();
}
int hashes_file(const char* const path) {
    try {
        cout<<"SHA256:" << SHA256(path) << " " << path << endl;
        cout << "MD5:" << MD5(path) << " " << path << endl;
    }
    catch (const exception& e) {
        cerr << "[fatal] " << e.what() << endl;
    }
    return EXIT_SUCCESS;
}
int
main()
{
    hashes_file("C:/Games/Euro Truck Simulator 2/base.scs");
}