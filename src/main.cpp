#include <iostream>
#include "../h/fileReader.h"
#include "../h/tree.h"
#include "../h/graph.h"

int main() {
  FileReader* stacks = FileReader::createFileReader("test.txt");
  stacks->loadStacks();

  Tree* stackTree = new Tree();
  FileReader::StackNode* head = stacks->getHead();
  stackTree->addStacksToTree(head);

  Graph* stackGraph = new Graph();

  string stack;
  int op;
  bool removed;

  while (true) {
    cout << "Unesite zeljenu operaciju: " << endl;
    cout << "1. Ispis stabla" << endl;
    cout << "2. Dodavanje novog programskog steka u stablo" << endl;
    cout << "3. Uklanjanje programskog steka iz stabla" << endl;
    cout << "4. Brisanje stabla iz memorije" << endl;
    cout << "---------------------------------" << endl;
    cout << "5. Konverzija formiranog stabla u graf" << endl;
    cout << "6. Ispis grafa" << endl;
    cout << "7. Detekcija rekurzivnih poziva funkcija" << endl;
    cout << "8. Kraj programa" << endl;

    cin >> op;

    switch (op) {
      case 1:
        cout << endl;
        if (stackTree) stackTree->printTree();
        cout << endl;
        break;
      case 2:
        cout << endl;
        cout << "Unesite programski stek u formatu: main f-ja(1) f-ja(2) ... f-ja(n)" << endl << endl;
        cin.ignore();
        getline(cin, stack);
        if (stackTree) {
          stackTree->addStackToTree(stack);
          stackTree->addStackToLinkedList(stack);
        }
        else {
          stackTree = new Tree();
          stackTree->addStackToTree(stack);
          stackTree->addStackToLinkedList(stack);
        }
        break;
      case 3:
        cout << endl;
        cout << "Unesite programski stek u formatu: main f-ja(1) f-ja(2) ... f-ja(n)" << endl << endl;
        cin.ignore();
        getline(cin, stack);
        if (stackTree) {
          removed = stackTree->removeStackFromLinkedList(stack);
          if (!removed) break;
          stackTree->rebuildTree();
        }
        break;
      case 4:
        delete stackTree;
        stackTree = nullptr;
        break;
      case 5:
        if (stackTree && stackTree->getRoot()) {
          stackGraph->convertTreeToGraph(stackTree->getRoot());
        }
        break;
      case 6:
        cout << endl;
        if (stackGraph) stackGraph->printGraph();
        cout << endl;
        break;
      case 7:
        cout << endl;
        //cycle = hasRecursion(startNode);
        //if (cycle) cout << "Ima rekurzije" << endl << endl;
        //else cout << "Nema rekurzije" << endl << endl;
        break;
      case 8:
        delete stackTree;
        delete stackGraph;
        delete stacks;
        return 0;
        break;
      case 0:
        cout << endl;
        cout << "Greska: neispravan unos" << endl << endl;
        return -1;
      default:
        cout << endl;
        cout << "Greska: nepostojeca operacija" << endl << endl;
      break;
    }
  }

  delete stackTree;
  delete stackGraph;
  delete stacks;

  return 0;
}