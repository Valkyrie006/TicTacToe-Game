#include<bits/stdc++.h>
using namespace std;

class Move
{
	public :
		int row, col, score;
};

class TicTacToe
{
	public :
		char player, computer, grid[3][3];
		
		TicTacToe()
		{
			for(int r = 0; r < 3; r++)
			{
				for(int c = 0; c < 3; c++)
				{
					grid[r][c] = ' ';
				}
			}
		}
		
		bool win()
		{
			int win_states[8][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6}};	
			for(int state = 0; state < 8; state++)
			{
				bool win = 1;
				int first_row = win_states[state][0] / 3, first_col = win_states[state][0] % 3;
				for(int j = 0; j < 3; j++)
				{
					int row = win_states[state][j] / 3, col = win_states[state][j] % 3;
					if(grid[first_row][first_col] == ' ' || grid[first_row][first_col] != grid[row][col])
					{
						win = 0;
					}
				}
				if(win)
					return 1;
			}
			return 0;
		}
		
		bool tie()
		{
			if(win())
				return 0;
			for(int r = 0; r < 3; r++)
			{
				for(int c = 0; c < 3; c++)
				{
					if(grid[r][c] == ' ')
					{
						return 0;
					}
				}
			}
			return 1;
		}
		
		void player_move()
		{
			bool f = 0;
			while(1)
			{
				if(f)
				{
					cout<<"Please enter a valid empty cell (1-9) which is not occupied : ";
				}
				else
				{
					cout<<"Enter an empty cell (1-9) : ";
				}
				int cell;
				cin>>cell;
				int row = (cell - 1) / 3, col = (cell - 1) % 3;
				if(cell >= 1 && cell <= 9 && grid[row][col] == ' ')
				{
					grid[row][col] = player;
					break;
				}
				else
				{
					f = 1;
				}
			}
		}
		
		void computer_move()
		{
			Move best_move = minimax();
			grid[best_move.row][best_move.col] = computer;
		}
		
		Move minimax(bool maximizing_player = 1)
		{
			Move best_move;
			if(win())
			{
				if(maximizing_player)
				{
					best_move.score = -1;
				}
				else
				{
					best_move.score = 1;
				}
				return best_move;
			}
			else if(tie())
			{
				best_move.score = 0;
				return best_move;
			}
			
			best_move.score = maximizing_player ? -2 : 2;
			for(int r = 0; r < 3; r++)
			{
				for(int c = 0; c < 3; c++)
				{
					if(grid[r][c] == ' ')
					{
						grid[r][c] = maximizing_player ? computer : player;
						Move board_state = minimax(!maximizing_player);
						if(maximizing_player)
						{
							if(board_state.score > best_move.score)
							{
								best_move.score = board_state.score;
								best_move.row = r;
								best_move.col = c;
							}
						}
						else
						{
							if(board_state.score < best_move.score)
							{
								best_move.score = board_state.score;
								best_move.row = r;
								best_move.col = c;
							}
						}
						grid[r][c] = ' ';
					}
				}
			}
			return best_move;
		}
		
		void play()
		{
			bool f = 0;
			while(1)
			{
				if(f)
				{
					cout<<"Please enter a valid symbol (only out of X and O). ";
				}
				else
				{
					cout<<"Which symbol do you choose (X or O), with X going first? ";
				}
				cin>>player;
				if(player == 'X' || player == 'O')
				{
					break;
				}	
				else
				{
					f = 1;
				}
			}	
			computer = player == 'X' ? 'O' : 'X';
			if(player == 'O')
			{
				computer_move();
			}
			print();
			while(1)
			{
				player_move();
				print();
				if(win())
				{
					cout<<"Player wins!"<<endl;
					return;
				}
				else if(tie())
				{
					cout<<"Tie!"<<endl;
					return;
				}
				cout<<"Computer is making a move..."<<endl;
				computer_move();
				print();
				if(win())
				{
					cout<<"Computer wins!"<<endl;
					return;
				}
				else if(tie())
				{
					cout<<"Tie!"<<endl;
					return;
				}
			}
		}
		
		void print()
		{
			cout<<endl;
			for(int r = 0; r < 3; r++)
			{
				if(r)
				{
					cout<<"-----------"<<endl;
				}
				for(int c = 0; c < 3; c++)
				{
					if(c)
					{
						cout<<"|";
					}
					cout<<' ';
					if(grid[r][c] == ' ')
					{
						cout<<3 * r + c + 1;
					}
					else
					{
						cout<<grid[r][c];
					}
					cout<<' ';
				}
				cout<<endl;
			}
			cout<<endl;
		}
};

int main()
{
	TicTacToe game;
	game.play();
	return 0;
}

