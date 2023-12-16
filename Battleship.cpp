#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void clearScreen()
{
    cin.clear();
    cin.get();  
    system("cls");
}

bool isValidPlacement(int arr[][7], int x, int y, int size, int orientation, int n)
{
    if ((orientation==0 && y+size-1>=n) || (orientation==1 && x+size-1>=n))
        return false;

    for (int i=x-1; i<=x+size; ++i)
    {
        for (int j=y-1; j<=y+size; ++j)
        {
            if (i>=0 && i<n && j>=0 && j<n && arr[i][j]!=0)
                return false;
        }
    }
    return true;
}

void arrEmpty(int arr[][7], int n)
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            arr[i][j] = 0;
        }
    }
}

bool isShipSunk(int arr[][7], int playerView[][7], int X, int Y, int n)
{
    int shipType = arr[X][Y];
    int hit = 0;

    switch (shipType)
    {
    case 2: 
        hit = 2;
        break;
    case 3:
        hit = 3;
        break;
    }
    int count = 0;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (arr[i][j] == shipType && playerView[i][j] == shipType)
            {
                count++;
            }
        }
    }
    return count == hit;
}


int main()
{
    int n = 7, game = 0, x, y, r, c, shots=0;
    int arr[7][7] = {0};
    int playerView[7][7] = {0};
    int singleMasted = 1, doubleMasted = 2, tripleMasted = 3;

    string playerName;
    cout << "Enter your name: ";
    cin >> playerName;
    cout << "Hello, " << playerName << "! Welcome to the game." << endl;

    srand(time(0));
    
    for (int i = 0; i < 1; i++)
    {
        x = rand() % (n-2);
        y = rand() % n;
        int orientation = rand() % 2;

        while (!isValidPlacement(arr, x, y, 3, orientation, n))
        {
            x = rand() % (n-2);
            y = rand() % n;
            orientation = rand() % 2;
        }

        if (orientation == 0)
        {
            arr[x][y] = tripleMasted;
            arr[x][y+1] = tripleMasted;
            arr[x][y+2] = tripleMasted;
        }
        else
        {
            arr[x][y] = tripleMasted;
            arr[x+1][y] = tripleMasted;
            arr[x+2][y] = tripleMasted;
        }
    } //tripleMasted is placed

    for (int i = 0; i < 2; i++)
    {
        x = rand() % (n-1);
        y = rand() % n;
        int orientation = rand() % 2;

        while (!isValidPlacement(arr, x, y, 2, orientation, n))
        {
            x = rand() % (n-1);
            y = rand() % n;
            orientation = rand() % 2;
        }

        if (orientation == 0)
        {
            arr[x][y] = doubleMasted;
            arr[x][y+1] = doubleMasted;
        }
        else
        {
            arr[x][y] = doubleMasted;
            arr[x+1][y] = doubleMasted;
        }
    } //two doubleMasted is placed

    for (int i = 0; i < 4; i++)
    {
        x = rand() % n;
        y = rand() % n;

        while (!isValidPlacement(arr, x, y, 1, 0, n))
        {
            x = rand() % n;
            y = rand() % n;
        }
        arr[x][y]=singleMasted;
    } //four singleMasted is placed

    while (game != 11)
    {
        cout << "  ";
        for (int i = 1; i <= n; i++)
        {
            cout << i << " ";
        }
        cout << endl;

        for (int i = 0; i < n; i++)
        {
            cout << i + 1 << " ";
            for (int j = 0; j < n; j++)
            {
                if (playerView[i][j] == 0)
                {
                    cout << ". "; // Empty
                }
                else if (playerView[i][j] == -1)
                {
                    cout << "* "; // Missed
                }
                else
                {
                    cout << "X "; // Ship (hit or sunk) 
                }
            }
            cout << endl;
        }
        cout<<"Enter the coordinates where you want to shoot: ";
        cin >> r >> c;
        if (arr[r-1][c-1] == doubleMasted || arr[r-1][c-1] == tripleMasted)
        {
            clearScreen();
            cout << "Hit!";
            game++;
            shots++;
            playerView[r-1][c-1] = arr[r-1][c-1];
            if (isShipSunk(arr, playerView, r - 1, c - 1, n))
            {
                cout << " Ship Sunk!" << endl;
            }
            else
            {
                cout << endl;
            }
        }
        else if (arr[r-1][c-1]==singleMasted)
        {
            clearScreen();
            cout << " Ship Sunk!" << endl;
            game++;
            shots++;
            playerView[r-1][c-1] = arr[r-1][c-1];
        }
        else
        {
            clearScreen();
            cout << "Miss!" << endl;
            shots++;
            playerView[r - 1][c - 1] = -1;
        }
    }
    cout <<"You win the game! Congrats! There is the ships!"<< endl;
    cout <<"You made "<<shots<<" shots"<<endl;
    for (int i = 0; i < n; i++)
        {
            cout << i + 1 << " ";
            for (int j = 0; j < n; j++)
            {
                if (playerView[i][j] == 0)
                {
                    cout << ". "; // Empty
                }
                else if (playerView[i][j] == -1)
                {
                    cout << ". "; // Missed
                }
                else
                {
                    cout << "X "; // Ship (hit or sunk) 
                }
            }
            cout << endl;
        }
    cin.get();
    return 0;
}
