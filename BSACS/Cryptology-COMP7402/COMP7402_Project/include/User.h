#ifndef COMP7402_PROJECT_USER_H
#define COMP7402_PROJECT_USER_H

#include <string>
#include <csignal>
#include <openssl/ec.h>
#include <openssl/ecdh.h>
#include <openssl/evp.h>
#include <cassert>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

class User {
private:
    string data;
    string hex_data;
    string bin_data;

    int fd_;
    string ip_;

    EC_KEY *server_private_key;              // server private key
    EC_POINT *client_public_key;      // client public key
    EC_POINT *server_public_key;      // server public key
    vector<string> reverse_round_keys;
    string iv;

    string server_hex_pub;
    string client_hex_pub;
    string shared_secret_key;
    string file_name;
    string extension;
    string file_hdr;
    unsigned long file_size;
    bool file_name_flag = false;
    bool file_size_flag = false;
    bool key_flag = false;
    bool EOC_flag = false;


public:
    User() {
        server_private_key = nullptr;
        server_public_key = nullptr;
        client_public_key = nullptr;
        data.reserve(3000000);
        hex_data.reserve(6000000);
        bin_data.reserve(12000000);
    }

    void set_fd(int fd) { fd_ = fd; }
    void set_ip(char* userIP) { ip_ = userIP; }
    void set_server_private_key(EC_KEY * pk) { server_private_key = pk; }
    void set_server_public_key(EC_POINT * pk) { server_public_key = pk; }
    void set_server_hex_pub(string pub) { server_hex_pub = std::move(pub); }
    void set_client_hex_pub(string pub) { client_hex_pub = std::move(pub); }
    void set_shared_secret_key(string ssk) { shared_secret_key = std::move(ssk); }
    void set_iv(string str_iv) { iv = std::move(str_iv); }
    void set_key_flag(bool flag) { key_flag = flag; }
    void set_file_name_flag(bool flag) { file_name_flag = flag; }
    void set_file_size_flag(bool flag) { file_size_flag = flag; }
    void set_EOC_flag(bool flag) { EOC_flag = flag; }
    void set_file_name(string str_name) { file_name = std::move(str_name); }
    void set_file_size(unsigned long fs) { file_size = fs; }
    void set_reverse_round_keys(vector<string> rks) { reverse_round_keys = std::move(rks); }

    int get_fd() const { return fd_; }
    string get_ip() const { return ip_; }
    string get_server_hex_pup() const { return server_hex_pub; }

    EC_KEY* get_server_private_key() { return server_private_key; }
    string get_shared_key()  { return shared_secret_key; }
    string get_iv() const { return iv; }
    vector<string> get_reverse_round_keys() const { return reverse_round_keys; }
    string get_file_name() const { return file_name; }
    string get_hex_data() const  { return hex_data; }
    bool is_key_flag() const { return key_flag; }
    bool is_EOC_flag() const { return EOC_flag; }
    bool is_file_name_flag() const { return file_name_flag; }
    bool is_file_size_flag() const { return file_size_flag; }

    void append_bin_string(const std::string& bin_str) {
        bin_data += bin_str;
    }
    void append_hex_string(const std::string& hex_str) {
        hex_data += hex_str;
    }
};
#endif //COMP7402_PROJECT_USER_H
