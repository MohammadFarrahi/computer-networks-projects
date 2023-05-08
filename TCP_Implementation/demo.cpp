#include <iostream>
#include <iomanip>
#include <sstream>
#include <string.h>
#include <fstream>

using namespace std;

string slice(char *buffer, int start, int size)
{
  char sliced[size];

  strncpy(sliced, buffer + start, size);
  return string(sliced);
}

int main(void)
{
  char buffer[3];

  std::ifstream infile("./fuck.txt");
  // infile.read(buffer, 3);
  // printf("%s\n", buffer);
  // infile.read(buffer, 3);
  // printf("%s\n", buffer);
  // infile.read(buffer, 3);
  // printf("%s\n", buffer);
  // infile.read(buffer, 3);
  // printf("%s\n", buffer);
  // infile.read(buffer, 3);
  // printf("%s\n", buffer);
  // infile.read(buffer, 3);
  // printf("%s\n", buffer);

  // infile.read(buffer, 3);

  while (infile.read(buffer, 3))
  {
    printf("%s\n", buffer);
    memset(buffer, 0, strlen(buffer));
  }
  printf("%s", buffer);

  return 0;
}