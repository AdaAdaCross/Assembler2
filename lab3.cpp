#include <iostream>
#include <ctime>
#include <cstring>

#define MAX_NUMBER 10
#define MAX_SIZE   3

using namespace std;

int* ASM(int** array, int w, int h)
{
  int* result = new int[w];
  memset(result, 0, w);
  asm(
      "mov %[array], %%rax\n\t"  //сохраняем начальную ячейку
      "mov %[w], %%r14d\n\t"     //сохраняем ширину массива
      "mov %[h], %%r15d\n\t"     //сохраняем высоту массива
      "mov %[result], %%rdi\n\t"
      "mov $0, %%r8d\n\t"        //инициализируем счетчик 1
       "loop_w:\n\t"
        "cmp %%r8d, %%r14d\n\t"
        "je end_w\n\t"
        "mov (%%rax), %%rbx\n\t"
        "mov $0, %%r9d\n\t"
        "mov $0, %%edx\n\t"
         "loop_h:\n\t"
          "cmp %%r9d, %%r15d\n\t"
          "je end_h\n\t"
          "mov (%%rbx), %%ecx\n\t"
          "cmp %%edx, %%ecx\n\t"
          "jl bigger\n\t"
          "mov %%ecx, %%edx\n\t"
          "bigger:\n\t"
          "add $1, %%r9d\n\t"
          "add $4, %%rbx\n\t"
          "jmp loop_h\n\t"
         "end_h:\n\t"
        "mov %%edx, (%%rdi)\n\t"
        "add $4, %%rdi\n\t"
        "add $8, %%rax\n\t"
        "add $1, %%r8d\n\t"
        "jmp loop_w\n\t"
       "end_w:\n\t"
      :
      :[array]"m"(array), [w]"m"(w), [h]"m"(h), [result]"m"(result)
      :"%rax", "%rbx", "%rcx"
  );

  return result;
}

int main()
{
  srand(time(0));
  int w = rand() % MAX_SIZE + 2;
  int h = rand() % MAX_SIZE + 2;
  int** array = new int*[w];
  cout<<"\tArray"<<endl;
  for (int i = 0; i < w; i++)
  {
    array[i] = new int[h];
    for (int j = 0; j < h; j++)
    {
      array[i][j] = rand() % MAX_NUMBER;
      cout<<array[i][j]<<" ";
    }
    cout<<endl;
  }

  int* res = ASM(array, w, h);
  cout<<endl<<"--------------------------------"<<endl;
  cout<<"\tMaxs array"<<endl;
  for (int i = 0; i < w; i++)
  {
    cout<<res[i]<<endl;
  }
  return 0;
}
