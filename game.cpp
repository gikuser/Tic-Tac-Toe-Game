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
	int getData(int turn)
        {
            int val;
            if(turn==PLAYER1)cout<<"\t\tPlayer 1 Turn\n";
            else
                cout<<"\t\tPlayer 2 Turn\n";
            cout<<"Enter the place where you want to mark : ";
            cin>>val;

            if(val>side*side)
            {   
                cnt++;//if invalid attempts more then 3 return end game and
                if(cnt<3)
                {
                    cout<<"\t\t You Entered Invalid Place \n";
                    cout<<"\t\t Enter Again...\n";
                    return getData(turn);
                }
                else
                {
                    cout<<"You have tried Invalid place for three times \n\n";
                    cout<<"You have to start the game again\n";
                    cout<<"Press ANY KEY for menu\n";
                    return -1;
                }

            }
            cnt=0;
            return val;
        }

        void winner(int turn)
        {
            showBoard();
            if(turn == PLAYER1)
            {
                cout<<"\t\t\tCongratualtions Player 1 !!!\n\t\t\tYou have won the match\n\n";
            }
            else
            {
                cout<<"\t\t\tCongratualtions Player 2 !!!\n\t\t\tYou have won the match\n\n";
            }
            return;
        }

        void gameStart(int turn)
        {
            while(this->gameOver()==false && moveIndex != side*side)
            {
                if(turn == PLAYER1)
                {
                    showBoard();
                    place = this->getData(turn);
                    if(place == -1)return;
                    x=(place-1)/side;
                    y=(place-1)%side;
                    
                    if(gameBoard[x][y]!=' ')
                    {
                        count++;
                        if(count<3)
                        {
                            cout<<"This place is already marked\n";
                            cout<<"Try Again\n";
                            
                        }
                        else
                        {
                            cout<<"You have tried 3 times in a wrong place\n\n";
                            cout<<"You have to again start the game\n";
                            cout<<"Press ANY KEY for menu\n";
                            return;
                        }
                    }
                    else
                    {
                        count=0;
                        gameBoard[x][y] = PLAYER1MOVE;
                        cout<<"Player 1 has put "<<PLAYER1MOVE<<" in a cell "<<place<<"\n";
                        moveIndex++;
                        turn = PLAYER2;
                    }
               }

                else if(turn == PLAYER2)
                {
                    showBoard();
                    place = this->getData(turn);
                    x=(place-1)/side;
                    y=(place-1)%side;
                    
                    if(gameBoard[x][y]!=' ')
                    {
                        count++;
                        if(count<3)
                        {
                            showBoard();
                            cout<<"This place is already marked\n";
                            cout<<"Try Again\n";
                            
                        }
                        else
                        {
                            showBoard();
                            cout<<"You have tried 3 times in a wrong place\n\n";
                            cout<<"You have to again start the game\n";
                            cout<<"Press ENTER for menu\n";
                            return;
                        }
                    }
                    else
                    {
                        count=0;
                        gameBoard[x][y] = PLAYER2MOVE;
                        cout<<"Player 2 has put "<<PLAYER2MOVE<<" in a cell "<<place<<"\n";

                        moveIndex++;
                        turn = PLAYER1;
                    }
                }
            }
