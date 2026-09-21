#include <iostream>
using namespace std;

// Display the game board
void displayBoard(char board[3][3])
{
    cout << "\n";
    cout << "     |     |     \n";
    cout << "  " << board[0][0] << "  |  "
         << board[0][1] << "  |  " << board[0][2] << "\n";
    cout << "_____|_____|_____\n";

    cout << "     |     |     \n";
    cout << "  " << board[1][0] << "  |  "
         << board[1][1] << "  |  " << board[1][2] << "\n";
    cout << "_____|_____|_____\n";

    cout << "     |     |     \n";
    cout << "  " << board[2][0] << "  |  "
         << board[2][1] << "  |  " << board[2][2] << "\n";
    cout << "     |     |     \n";
}

// Check whether a player has won
bool checkWin(char board[3][3], char player)
{
    // Check rows
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == player &&
            board[i][1] == player &&
            board[i][2] == player)
        {
            return true;
        }
    }

    // Check columns
    for (int j = 0; j < 3; j++)
    {
        if (board[0][j] == player &&
            board[1][j] == player &&
            board[2][j] == player)
        {
            return true;
        }
    }

    // Check first diagonal
    if (board[0][0] == player &&
        board[1][1] == player &&
        board[2][2] == player)
    {
        return true;
    }

    // Check second diagonal
    if (board[0][2] == player &&
        board[1][1] == player &&
        board[2][0] == player)
    {
        return true;
    }

    return false;
}

// Check whether the board is full
bool checkDraw(char board[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] != 'X' && board[i][j] != 'O')
            {
                return false;
            }
        }
    }

    return true;
}

// Main function
int main()
{
    char playAgain;

    do
    {
        // Initialize board
        char board[3][3] = {
            {'1', '2', '3'},
            {'4', '5', '6'},
            {'7', '8', '9'}
        };

        char currentPlayer = 'X';
        int choice;
        int moves = 0;

        cout << "\n=============================\n";
        cout << "       TIC TAC TOE\n";
        cout << "=============================\n";

        cout << "\nPlayer 1: X\n";
        cout << "Player 2: O\n";

        // Game loop
        while (true)
        {
            displayBoard(board);

            cout << "\nPlayer " << currentPlayer;
            cout << ", enter position (1-9): ";
            cin >> choice;

            // Check valid position
            if (choice < 1 || choice > 9)
            {
                cout << "Invalid position! Try again.\n";
                continue;
            }

            // Convert position into row and column
            int row = (choice - 1) / 3;
            int col = (choice - 1) % 3;

            // Check whether position is already occupied
            if (board[row][col] == 'X' ||
                board[row][col] == 'O')
            {
                cout << "Position already occupied! Try again.\n";
                continue;
            }

            // Place player's symbol
            board[row][col] = currentPlayer;
            moves++;

            // Display updated board
            displayBoard(board);

            // Check winner
            if (checkWin(board, currentPlayer))
            {
                cout << "\n*****************************\n";
                cout << " Player " << currentPlayer << " WINS!\n";
                cout << "*****************************\n";
                break;
            }

            // Check draw
            if (moves == 9 || checkDraw(board))
            {
                cout << "\n*****************************\n";
                cout << "       GAME DRAW!\n";
                cout << "*****************************\n";
                break;
            }

            // Change player
            if (currentPlayer == 'X')
            {
                currentPlayer = 'O';
            }
            else
            {
                currentPlayer = 'X';
            }
        }

        // Replay option
        cout << "\nDo you want to play again? (Y/N): ";
        cin >> playAgain;

    } while (playAgain == 'Y' || playAgain == 'y');

    cout << "\nThank you for playing!\n";

    return 0;
}