#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void clearScreen()
{
    system("cls");
}

bool isValidPlacement(int arr[][7], int x, int y, int size, int orientation, int n)
{
    if ((orientation==0 && y+size-1 >= n) || (orientation == 1 && x + size - 1 >= n))
        return false;

    for (int i = x - 1; i <= x + size; ++i)
    {
        for (int j = y - 1; j <= y + size; ++j)
        {
            if (i >= 0 && i < n && j >= 0 && j < n && arr[i][j] != 0)
                return false;
        }
    }

    return true;
}

int main()
{
    int n = 7, game = 0, x, y, r, c;
    int arr[7][7] = {0};
    int singleMasted = 1, doubleMasted = 2, tripleMasted = 3;

    srand(time(0));

    for (int i = 0; i < 1; i++)
    {
        x = rand() % (n - 2);
        y = rand() % n;
        int orientation = rand() % 2;

        while (!isValidPlacement(arr, x, y, 3, orientation, n))
        {
            x = rand() % (n - 2);
            y = rand() % n;
            orientation = rand() % 2;
        }

        if (orientation == 0)
        {
            arr[x][y] = tripleMasted;
            arr[x][y + 1] = tripleMasted;
            arr[x][y + 2] = tripleMasted;
        }
        else
        {
            arr[x][y] = tripleMasted;
            arr[x + 1][y] = tripleMasted;
            arr[x + 2][y] = tripleMasted;
        }
    }

    for (int i = 0; i < 2; i++)
    {
        x = rand() % (n - 1);
        y = rand() % n;
        int orientation = rand() % 2;

        while (!isValidPlacement(arr, x, y, 2, orientation, n))
        {
            x = rand() % (n - 1);
            y = rand() % n;
            orientation = rand() % 2;
        }

        if (orientation == 0)
        {
            arr[x][y] = doubleMasted;
            arr[x][y + 1] = doubleMasted;
        }
        else
        {
            arr[x][y] = doubleMasted;
            arr[x + 1][y] = doubleMasted;
        }
    }


    for (int i = 0; i < 4; i++)
    {
        x = rand() % n;
        y = rand() % n;

        while (!isValidPlacement(arr, x, y, 1, 0, n))
        {
            x = rand() % n;
            y = rand() % n;
        }

        arr[x][y] = singleMasted;
    }

    while (game != 9)
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
                cout << arr[i][j] << " ";
            }
            cout << endl;
        }

        cin >> r >> c;
        if (arr[r-1][c-1]==singleMasted)
        {
            cout << "Sunk!" << endl;
            arr[r - 1][c - 1] = 0;
            game++;

            clearScreen();
        }
        else if((arr[r-1][c-1]==doubleMasted && arr[r-1][c]==doubleMasted)
                || (arr[r-1][c-1]==doubleMasted && arr[r-1][c-2]==doubleMasted)
                || (arr[r-1][c-1]==doubleMasted && arr[r][c-1]==doubleMasted)
                || (arr[r-1][c-1]==doubleMasted && arr[r-2][c-1]==doubleMasted))
        {
            cout << "Hit!" << endl;
            arr[r - 1][c - 1] = 0;
            game++;
            clearScreen();
        }
        else if(arr[r-1][c-1]==tripleMasted)
        {
            cout << "Hit!" << endl;
            arr[r - 1][c - 1] = 0;
            game++;
            clearScreen();
        }
        else
        {
            cout << "Miss" << endl;
        }
    }

    cout << "You win the game! Congrats!" << endl;
    cin.get();
    return 0;
}
