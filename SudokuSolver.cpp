#include <stdio.h>
#include <iostream>

class grid{
  public:
    bool** sudokuGrid;
    /* ----------------------------
     * |[] [] []|[] [] []|[] [] []|
     * |[] [] []|[] [] []|[] [] []|
     * |[] [] []|[] [] []|[] [] []|
     * ----------------------------
     * |[] [] []|[] [] []|[] [] []| 
     * |[] [] []|[] [] []|[] [] []|
     * |[] [] []|[] [] []|[] [] []|
     * ----------------------------
     * |[] [] []|[] [] []|[] [] []|
     * |[] [] []|[] [] []|[] [] []|
     * |[] [] []|[] [] []|[] [] []|
     * ----------------------------
     */


  public:
    grid(){
      sudokuGrid = new bool* [9];
      for(int i = 0; i < 9; i++)
        sudokuGrid[i] = new bool[9];
    };
};

int main(){
  grid* sudoku = new grid();
  for(int i = 0; i < 9; i++)
    for(int j = 0; j < 9; j++){
      std::cout << &sudoku->sudokuGrid[i][j] << std::endl;
    }
}

