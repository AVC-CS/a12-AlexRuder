#include <iostream>
using namespace std;
int globlInt = 100;

void printAddresses(int *addr){
  int localint = 20;
  cout << "value of var addr: " << *addr << endl;
  cout << "Address of var addr: " << &addr << endl;
  *addr =30;
  cout << "Address of localint: " << &localint << endl;
}

int main (){
  int num = 10;
  static int staticInt = 1000;
  cout << "Address of num: " << &num << endl;
  cout << "address of globlInt: " << &globlInt << endl;
  cout << "address of staticInt: " << &staticInt << endl;
  printAddresses(&num);

  cout << "==============" << endl;
  cout << "address of main: " << &main << endl;
  cout << "address of printAddresses: " << &printAddresses << endl;
  cout << "==============" << endl;

  char* heap1 = (char*)malloc(1024);
  char* heap2 = (char*)malloc(1024);
  cout << "Address of heap1: " << (void*)heap1 << endl;
  cout << "Address of heap2: " << (void*)heap2 << endl;

}
