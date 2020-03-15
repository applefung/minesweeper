/*
 *   pa2.cpp
 *
 *  Created on: 2018¦~11¤ë3¤é
 *      Author: 80411
 */
//  pa2.cpp
//	minesweeper

#include "definition.h"

/* ATTENTION:
 * 1. PLEASE Read the introduction before each function carefully!
 * 2. You can ONLY add your code where you find a comment:
 *   // complete your code here
 * 3. DO NOT modify other things!!
 */

/************* Functions Requires You to Complete. *************/

/* ================================================================
 * Randomly place mines and flowers on the  play board.
 * mine and flower should not exist in the same cell.
 * ----------------------------------------------------------------
 * Input:
 * - cell[MAXSIZE][MAXSIZE]: the play board;
 * - num_mines: number of mines;
 * - num_flowers: number of flowers;
 * - height: height of the play board, which is the number of rows;
 * - width: width of the play board, which is the number of columns;
 * ----------------------------------------------------------------
 */
void generateMineAndFlower(Cell cell[MAXSIZE][MAXSIZE], int num_mines,
                           int num_flowers, int height, int width) {

	cout << "\nPlacing mines and flowers ......" << endl;
	int i=0;
	int j=0;
	while(i<num_mines)
	{
		int x=rand()%height;
		int y=rand()%width;
		if(isOnBoard(x,y,height,width) && cell[x][y].content !=MINE && cell[x][y].content !=FLOWER)
		{
			cell[x][y].content=MINE;
			i+=1;
		}
	}//generate mines
	while(j<num_flowers)
	{
		int a=rand()%height;
		int b=rand()%width;
		if(isOnBoard(a,b,height,width) && cell[a][b].content !=MINE && cell[a][b].content !=FLOWER)
		{
			cell[a][b].content=FLOWER;
			j+=1;
		}
	}//generate flowers
	// complete your code here
}

/* ================================================================
 * Count the number of surrounding mines of all cells on the game board.
 * You should compute this number not just for empty cells,
 * but also the mine cells and flower cells.
 * ----------------------------------------------------------------
 * Input:
 * - cell[MAXSIZE][MAXSIZE]: the play board;
 * - height: height of the play board, which is the number of rows;
 * - width: width of the play board, which is the number of columns;
 * ----------------------------------------------------------------
 */
void generateMinecountMap(Cell cell[MAXSIZE][MAXSIZE], int height,
	                      int width) {

	cout << "\ngenerate real maps ......" << endl;

	// complete your code here
	for(int i=0; i<height; i++)
	{
		for(int j=0; j<width; j++)
		{
			if(cell[i][j].content==MINE && isOnBoard(i, j, height, width))
			{
				cell[i][j].count+=1;
			}
			if (cell[i+1][j].content==MINE && isOnBoard(i+1, j, height, width))
			{
				cell[i][j].count+=1;
			}//horizontal direction right

			if (cell[i-1][j].content==MINE && isOnBoard(i-1, j, height, width))
			{
				cell[i][j].count+=1;
			}//horizontal direction left

			if (cell[i][j+1].content==MINE && isOnBoard(i, j+1, height, width))
			{
				cell[i][j].count+=1;
			}//vertical direction up

			if (cell[i][j-1].content==MINE && isOnBoard(i, j-1, height, width))
			{
				cell[i][j].count+=1;
			}//vertical direction down

			if (cell[i+1][j+1].content==MINE && isOnBoard(i+1, j+1, height, width))
			{
				cell[i][j].count+=1;
			}//diagonal direction right+up

			if (cell[i+1][j-1].content==MINE && isOnBoard(i+1, j-1, height, width))
			{
				cell[i][j].count+=1;
			}//diagonal direction right+down

			if (cell[i-1][j+1].content==MINE && isOnBoard(i-1, j+1, height, width))
			{
				cell[i][j].count+=1;
			}//diagonal direction left+up

			if (cell[i-1][j-1].content==MINE && isOnBoard(i-1, j-1, height, width))
			{
				cell[i][j].count+=1;
			}//diagonal direction left+down

		}
	}
}

/* ================================================================
 * Sweep the empty cell recursively.
 * You are REQUIRED to implement this function using recursion.
 * You will receive NO mark if your implementation is not an recursion.
 * ----------------------------------------------------------------
 * Input:
 * - cell[MAXSIZE][MAXSIZE]: the play board;
 * - height: height of the play board, which is the number of rows;
 * - width: width of the play board, which is the number of columns;
 * - row: index of current row;
 * - col: index of current column;
 * Output:
 * - additional_life: how many additional lives are obtained
 * ----------------------------------------------------------------
 */
int recursiveSweep(Cell cell[MAXSIZE][MAXSIZE], int height, int width,
	               int row, int col) {

	// complete your code here
	int additional_life=0;
	if (cell[row][col].marked==true || !isOnBoard(row, col, height, width) || cell[row][col].content==MINE)
	{
		return 0;
	}//check whether the cell is marked before or is on board or it is a mine
	if(cell[row][col].content==FLOWER && cell[row][col].count>0 && cell[row][col].swept==false)
	{
		cell[row][col].swept=true;
		return 1;
	}//check whether a mine is adjacent to the flower
	if(cell[row][col].content==FLOWER && cell[row][col].swept==true && cell[row][col].count>0)
	{
		return additional_life;
	}
	if (cell[row][col].swept==true)
	{
		return additional_life;
	}//check whether the cell is swept before
	if (cell[row][col].count > 0 && cell[row][col].content!=FLOWER)
	{
		cell[row][col].swept=true;
		return additional_life;
	}//check whether the cell contains the number or not
	if(cell[row][col].content==FLOWER && cell[row][col].swept==false)
	{
		cell[row][col].swept=true;
		additional_life+=1;
		return additional_life+=recursiveSweep(cell,height,width,row+1,col)+recursiveSweep(cell,height,width,row,col+1)+recursiveSweep(cell,height,width,row,col-1)+recursiveSweep(cell,height,width,row-1,col)+recursiveSweep(cell,height,width,row+1,col+1)+recursiveSweep(cell,height,width,row+1,col-1)+recursiveSweep(cell,height,width,row-1,col-1)+recursiveSweep(cell,height,width,row-1,col+1);

	}//check the flower
	if(cell[row][col].content==EMPTY)
	{
			cell[row][col].swept=true;
			return additional_life+=recursiveSweep(cell,height,width,row+1,col)+recursiveSweep(cell,height,width,row,col+1)+recursiveSweep(cell,height,width,row,col-1)+recursiveSweep(cell,height,width,row-1,col)+recursiveSweep(cell,height,width,row+1,col+1)+recursiveSweep(cell,height,width,row+1,col-1)+recursiveSweep(cell,height,width,row-1,col-1)+recursiveSweep(cell,height,width,row-1,col+1);
	}//sweep recursively when it is an empty cell

}

/* ================================================================
 * Run the game according to the operation chosen
 * ATTENTION:
 * 1. you will use recursiveSweep() in this function.
 * 2. you will use isOnBoard() to help validate the input.
 * ----------------------------------------------------------------
 * Input:
 * - cell[MAXSIZE][MAXSIZE]: the play board;
 * - height: height of the play board, which is the number of rows;
 * - width: width of the play board, which is the number of columns;
 * - row: index of current row;
 * - col: index of current column;
 * - life: record number of lives remaining;
 * - num_mines: number of mines;
 * - num_marked_mines: number of mines marked as mine by player;
 * - op: operation taken. { 0: sweep; 1: mark; 2: unmark}
 * ----------------------------------------------------------------
 */
void operation(Cell cell[MAXSIZE][MAXSIZE], int height, int width,
	           int row , int col, int& life, int num_mines,
	           int& num_marked_mines, int op) {

	/* choose to sweep */
	if (op == 0) {
		// complete your code here
		if(!isOnBoard(row, col, height, width))
		{
			return;
		}//check the input is inside the board or not
		else if(cell[row][col].content==MINE)
		{
			cell[row][col].swept=true;
			life-=1;
			num_marked_mines+=1;
		}
		else if(cell[row][col].marked==true)
		{
			return;
		}
		else if(isOnBoard(row, col, height, width) || cell[row][col].content != MINE)
		{
			int x=recursiveSweep(cell, height, width, row, col);
			life+=x;
		}
	}

	/* choose to mark */
	if (op == 1) {
	 	// complete your code here
		if(!isOnBoard(row, col, height,width))
		{
			return;
		}//check the input is inside the board or not
		else if(isOnBoard(row, col, height, width) && num_marked_mines<10)
		{

				if(cell[row][col].content==FLOWER)
				{
					cout<<"Ooooops!! This is a FLOWER!! You lose a chance to have an additional life!!"<<endl;
					cell[row][col].swept=true;
					return;
				}//check whether a flower is accidentally marked
				if(cell[row][col].content==MINE && cell[row][col].swept==true)
				{
					return;
				}//check whether a mine is swept or not and it cannot be marked
				cell[row][col].marked=true;
				num_marked_mines+=1;

		}
	}


	/* choose to unmark */
	if (op == 2) {

		// complete your code here
		if(!isOnBoard(row, col, height, width))
		{
			return;
		}//check the input is inside the board or not
		else if (isOnBoard(row, col, height, width) && cell[row][col].marked==true && num_marked_mines>0)
		{
			cell[row][col].marked=false;
			num_marked_mines-=1;

		}

	}
}

/* ================================================================
 * Check game state: win/lose/continue
 * ----------------------------------------------------------------
 * Input:
 * - cell[MAXSIZE][MAXSIZE]: the play board;
 * - num_mines: number of mines;
 * - height: height of the play board, which is the number of rows;
 * - width: width of the play board, which is the number of columns;
 * - life: record number of lives remaining;
 * Output:
 * - {return -1: lose; return 0: continue; return 1: win}
 * ----------------------------------------------------------------
 */
int checkWin(const Cell cell[MAXSIZE][MAXSIZE], int num_mines,
             int height, int width, int life) {

	// complete your code here
	int swept_mines=0;
	int marked_mines=0;
	for(int i=0; i<height; i++)
	{
		for(int j=0; j<width; j++)
		{
			if (cell[i][j].content==MINE && cell[i][j].marked==true)
			{
				marked_mines+=1;
			}
			if(cell[i][j].content==MINE && cell[i][j].swept==true)
			{
				swept_mines+=1;
			}
		}
	}//calculate how many empty cell is swept
	if(life==0)
	{
		return -1;
	}//check lose
	else if(life>0)
	{

		if (marked_mines==num_mines)
		{
			return 1;
		}//check win with only marked mines
		else if(swept_mines+marked_mines==num_mines)
		{
			return 1;
		}//check win with swept mines and marked mines
		else
		{
			return 0;
		}//check continue
	}
}



