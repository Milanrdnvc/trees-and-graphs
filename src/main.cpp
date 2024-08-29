#include <iostream>
#include "../h/fileReader.h"

int main() {

  FileReader* stacks = FileReader::createFileReader("test.txt");
  stacks->loadStacks();




  delete stacks;
  return 0;
}