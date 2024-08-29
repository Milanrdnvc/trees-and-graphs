#include <iostream>
#include "../h/fileReader.h"
#include "../h/tree.h"

int main() {
  FileReader* stacks = FileReader::createFileReader("test.txt");
  stacks->loadStacks();

  Tree* stackTree = new Tree();

  string* stackArray = stacks->getStackArray();

  for (int i = 0; i < stacks->getStackArrayLen(); i++) {
    stackTree->addStackToTree(stackArray[i]);
  }

  stackTree->printTree();

  delete stackTree;
  delete stacks;
  return 0;
}