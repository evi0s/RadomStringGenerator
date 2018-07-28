#include <iostream>
#include <ctime>
#include <fstream>
#include "cmdline.h"
using namespace std;

clock_t start__;
#define tic start__ = clock()
#define toc cout << "Time usage: " << (clock() - start__) * 1000 / CLOCKS_PER_SEC << " ms\n"

const char CCH[] = "_0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_";

ofstream fout;

inline string getrand(int size){
    string ch;
    ch.resize(size + 1);
    for (int i = 0; i < size; i++){
        int x = rand() / (RAND_MAX / (sizeof(CCH) - 1));
        ch[i] = CCH[x];
    }
    return ch;
}

int main(int argc, char *argv[]){
    cmdline::parser a;
    int n, size;
    string outfile;
    bool cases = true;
    char flag;
    
    a.add<int>("number", 'n', "number of strings", false, 100);
    a.add<int>("length", 'l', "length of strings", false, 1000);
    a.add<string>("path", 'p', "path of output file", false, "./testcase.in");
    a.add("interactive", 'i', "interactive mode");
    a.add<bool>("cases", 'c', "insert the number of strings to the first line of the file", false, true);
    a.add("help", 0, "print this message");
    a.set_program_name("RandomStringGenerator");
    
    bool ok = a.parse(argc, argv);
    
    if(!ok){
        cerr << a.error() << endl << a.usage();
        return 0;
    }
    
    if(a.exist("interactive")){
        cout << "Using interactive mode..." << endl;
        cout << "The number of strings: " << endl;
        cin >> n;
        cout << "The length of each string:" << endl;
        cin >> size;
        cout << "The path of output file:" << endl;
        cin >> outfile;
        cout << "insert the number of strings to the first line of the file? (Y/N)" << endl;
        cin >> flag;
        
        if(flag == 'n' || flag == 'N')
            cases = false;
        
        fout = ofstream (outfile);
    }else if(a.exist("help")){
        cerr << a.usage();
        return 0;
    }else{
        if(argc == 1){
            cout << a.usage() << endl;
            cout << "Generating using default settings..." << endl;
        }
        n = a.get<int>("number");
        size = a.get<int>("length");
        outfile = a.get<string>("path");
        cases = a.get<bool>("cases");
        
        fout = ofstream (outfile);
    }
    
    srand((unsigned)time(NULL));
    tic;
    if(cases)
        fout << n << "\n";
    for(int i = 0; i < n; i++)
        fout << getrand(size) << "\n";
    cout << "Generated!" << endl;
    toc;
    return 0;
}
