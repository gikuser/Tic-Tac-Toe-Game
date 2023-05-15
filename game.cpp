#include<iostream>
#include<conio.h>
using namespace std;
#define PLAYER1 1
#define PLAYER2 2
#define PLAYER1MOVE '0'
#define PLAYER2MOVE 'X'

class Root{
    public:
    virtual void showBoard() = 0; //pure virtual function
};
class Board: public Root
{
	private :
	    int side;
	public : 
        char** gameBoard;
		Board(int side)
		{
			this->side=side; // This pointer is used as data member and variable have same name.
            gameBoard = new char*[side];
            for(int i =0;i<side;i++)
            {
                gameBoard[i] = new char[side];
            }

            for(int i=0;i<side;i++)
            {
                for(int j=0;j<side;j++)
                {
                    gameBoard[i][j]=' ';
                }
            }
		}
		
		void showBoard()
        {

            for(int i =0;i<=side*2;i++)
            {  
                cout<<"\t\t\t\t ";
                for(int j=0;j<side;j++)
                {
                    if(i%2==0)
                    {
                        for(int k =0;k<side;k++)cout<<"----";
                        break;
                    }
                    else
                    {   
                        if(j==0)cout<<"| ";
                        cout<<gameBoard[i/2][j]<<" | ";
                    }
                }
                cout<<"\n";
            }	            
            return;
        }
        

};

class Play : public Board
{   
    private : 
        int side;
        int moveIndex,x,y;
        int place;
        int count,cnt;
    public:
        Play(int side) : Board(side) 
        {
            this->side = side;
            moveIndex = 1;
            count=0;
            cnt=0;
        }
        int turn = PLAYER1;

        bool rowCrossed()
        {
            for(int i = 0; i < side; i++)
            {
                if(gameBoard[i][0]==gameBoard[i][1] && gameBoard[i][1]==gameBoard[i][2] && gameBoard[i][0] !=' ')
                return true;
            }
            return false;
        }
        
        bool columnCrossed()
        {
            for(int i = 0; i < side; i++)
            {
                if(gameBoard[0][i]==gameBoard[1][i] && gameBoard[1][i]==gameBoard[2][i] && gameBoard[0][i] !=' ')
                return true;
            }
            return false;
        }
        
        bool diagonalCrossed()
        {
            if(gameBoard[0][0]==gameBoard[1][1] && gameBoard[1][1]==gameBoard[2][2] && gameBoard[0][0] !=' ')
                return true;
            if(gameBoard[0][2]==gameBoard[1][1] && gameBoard[1][1]==gameBoard[2][0] && gameBoard[0][2] !=' ')
                return true;
                
            return false;
        }
        
        bool gameOver()
        {
            return (this->rowCrossed() || this->columnCrossed() || this->diagonalCrossed());
        }
