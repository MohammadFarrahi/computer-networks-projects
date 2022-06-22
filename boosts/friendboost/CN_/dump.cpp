#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string>
#include <string.h>
#include <sstream> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

string readFile(string fileName) {
    string line;
    string input = "";
    ifstream MyReadFile(fileName);
    while(getline(MyReadFile, line)) {
        input += line + "\n";
    }
    MyReadFile.close(); 
    input.pop_back();
    return input;
}

vector<string> breakIntoFrames(int frameSize, string input) {
    vector<string> frames;
    int i = 0;
    for(i = 0; i < input.size(); i += frameSize) 
        frames.push_back(input.substr(i, frameSize));
    // if(input.size()%frameSize != 0) 
    //     frames.push_back(input.substr(i-frameSize));

    return frames;
}

int main() {
    string s = readFile("gistfile1.txt");
    vector<string> v = breakIntoFrames(1536, s);
    for(int i = 0; i < v.size(); i++) {
        cout << v[i];
    }
}