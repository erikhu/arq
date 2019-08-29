#include <iostream>

int main(int argc, char *argv[]){
  _asm {
    x DWORD 0
    i DWORD 0
    j DWORD ?
    k DWORD ?
    DX DWORD ?
    for1:
      CMP x,20
      JG fin
      INC x
      for2:
        MOV j, i
        CMP j, 21
        JG for1
        INC j
        MOV eax, 0
        ADD eax, i
        ADD eax, j
        MOV k, eax
        for3:
          CMP k,42
          JG for2
          CMP x, 100
          JL else3
          JMP 
          else3:
          
    fin:
  }
  
  return 0;
}
