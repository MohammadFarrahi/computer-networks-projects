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
    
#define PORT     8080 
#define MAXLINE 1024 


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

    return frames;
} 

// Driver code 
int main() { 
    int sockfd; 
    char buffer[MAXLINE]; 
    struct sockaddr_in servaddr; 
    
    // Creating socket file descriptor 
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
    
    memset(&servaddr, 0, sizeof(servaddr)); 
        
    // Filling server information 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(PORT); 
    servaddr.sin_addr.s_addr = INADDR_ANY; 

    // if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
	// {
	// 	perror("bind failed");
	// 	exit(EXIT_FAILURE);
	// }
        
    int n;
    socklen_t len; 
    char *hello =  (char*)"Hi from pc A";

    string input = readFile("gistFile1.txt");
    vector<string> frames = breakIntoFrames(1536, input);


    for(int i = 0; i < frames.size(); i++) {
        int n = frames[i].length();
        char char_array[n + 1];
        strcpy(char_array, frames[i].c_str());
 
        sendto(sockfd, char_array, strlen(hello), 
        MSG_CONFIRM, (const struct sockaddr *) &servaddr,  
            sizeof(servaddr)); 
 
    
        // printf("%s\n", buffer);
        // n = recvfrom(sockfd, (char *)buffer, MAXLINE,  
        //         MSG_WAITALL, (struct sockaddr *) &servaddr, 
        //         (socklen_t*)&len); 
    }
    

    //printf("buffer is: %s\n", buffer);
       
    close(sockfd); 
    return 0; 
}