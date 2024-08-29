#include <iostream>
#include "../h/fileReader.h"

int main() {

  FileReader* fileReader = FileReader::createFileReader("test.txt");
  fileReader->loadStacks();
  delete fileReader;

  return 0;
}