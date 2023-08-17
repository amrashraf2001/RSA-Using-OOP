#include<iostream>
#include <fstream>
#include <sstream>
#include <string>
#include<vector>
#include<cmath>
using namespace std;

bool isPrime(int number) {
    if (number <= 1) {  
        return false;
    }

    for (int i = 2; i * i <= number; ++i) {
        if (number % i == 0) {
            return false;
        }
    }

    return true;
}

class sender {
private:
    string message;
    int public_key;

public:

    bool read_message() {
        string msg;
        cin >> msg;
        message = msg;
        if (msg == "") { return false; }
        else { return true; }
        
    }

    string get_message() {
        return message;
    }

    int get_public_key() {
        return public_key;
    }

    void read_public_key() {
        ifstream inputFile("shared_public_key.txt");

        if (!inputFile) {
            cout << "Error opening file!" << std::endl;
            return;
        }

        string line;
        if (getline(inputFile, line)) {
            istringstream iss(line);
            iss >> public_key;
        }
        else {
            cout << "Empty file!" << endl;
            return;
        }
        inputFile.close();

    }

    int encrypt(int mess, int e, long long n)
    {

        //int c =(int) pow(mess, e);
        //c = c % n;
        long long m = 1;
        for (int i = 0; i < e; i++) {
            m = (m * mess) % n;
        }
        return m;
    }
    vector<int> encoder(int e, long long n)
    {
        vector<int> form;
        for (auto& letter : message) {

            form.push_back(encrypt((int)letter, e, n));
        }
            
        return form;
    }


};

class receiver {
private:
    long long p, q, n, e, k, d, phi;

public:

    int gcd(int a, int h)
    {
        int temp;
        while (1) {
            temp = a % h;
            if (temp == 0)
                return h;
            a = h;
            h = temp;
        }
    }
    int decrypt(int c, long long n, long long d)
    {

       /* long long m = pow(c, d);
        m = m % (long long)n;*/
        long long m = 1;
        for (int i = 0; i < d; i++) {
            m = (m * c) % n;
        }
        return (int)m;
    }

    string decoder(vector<int> encoded, long long n, long long d)
    {
        string s;
        for (auto& num : encoded)
            s += decrypt(num, n, d);
        return s;
    }

    long long get_n() {
        return n;
    }

    long long get_d() {
        return d;
    }

    pair<bool,string> generate_keys_and_share_public_key() {
        ifstream inputFile("receiver_input.txt");

        if (!inputFile) {
            cout << "Error opening file!" << std::endl;
            return make_pair(false,"f");
        }

        string line;
        if (getline(inputFile, line)) {
            istringstream iss(line);
            iss >> p >> q;
        }
        else {
            cout << "Empty file!" << endl;
            return make_pair(false, "f");
        }
        inputFile.close();
        if (p<=0) {
            return make_pair(false, "pnz");
        }
        if (q <= 0) {
            return make_pair(false, "qnz");
        }
        if (!isPrime(p)) {
            return make_pair(false, "pnotp");
        }
        if (!isPrime(q)) {
            return make_pair(false, "qnotp");
        }
        n = p * q;
        e = 2;
        phi = (p - 1) * (q - 1);
        while (e < phi) {

            if (gcd(e, phi) == 1)
                break;
            else
                e++;
        }
        k = 2;
        d = (1 + (k * phi)) / e;
        ofstream fileclear("shared_public_key.txt", ofstream::trunc);
        ofstream filewrite("shared_public_key.txt");
        if (filewrite.is_open()) {
            filewrite << e;
            filewrite.close();
        }
        else {
            cout << "Failed to open the file." << endl;
        }
       
        return make_pair(true, "");
        
    }

    void display_in_receiver(string str1, string str2)
    {
        ofstream outputFile;
        outputFile.open("output.txt");
        if (outputFile.is_open()) {
            outputFile << str1 << endl;
            outputFile << str2 << endl;
            outputFile.close();
            cout << "File created and data written successfully." << endl;
        }
        else {
            cout << "Unable to create or open the file." << endl;
        }
    }
};


int main() {


    //while (1)
    //{
        receiver ayman;
        sender amr;
        pair<bool, string> temp;
        temp=ayman.generate_keys_and_share_public_key();
        if (!temp.first) {
            if (temp.second=="pnz") {
                cout << "the value of p is below or equal zero, please try again"<<endl;
                //continue;
                return 0;
            }
            if (temp.second == "qnz") {
                cout << "the value of q is below or equal zero, please try again" << endl;
                //continue;
                return 0;
            }
            if (temp.second == "pnotp") {
                cout << "the value of p is not a prime number, please try again" << endl;
                //continue;
                return 0;
            }
            if (temp.second == "qnotp") {
                cout << "the value of q is not a prime number, please try again" << endl;
                //continue;
                return 0;
            }
        }
        amr.read_public_key();
        bool temp2=amr.read_message();
        if (!temp2)return 0;//continue;
        vector<int> encrypted = amr.encoder(amr.get_public_key(), ayman.get_n());
        string encrpted_mess;
        for (int i = 0; i < encrypted.size(); i++)
        {
            encrpted_mess += encrypted[i];
        }
        string decrypted = ayman.decoder(encrypted, ayman.get_n(), ayman.get_d());
        ayman.display_in_receiver(encrpted_mess, decrypted);
        
    //}
   
    return 0;
}