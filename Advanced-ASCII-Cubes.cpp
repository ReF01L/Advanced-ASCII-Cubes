#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

#define fullSize 401

using namespace std;

ifstream fin;
ofstream fout;

vector <vector<char>> P(fullSize, vector<char>(fullSize, '.'));
vector<string> cube(6);

void paint(int posX, int posY, int *minX, int *maxX, int *minY, int *maxY)
{
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 7; j++)
        {
            if(cube[i][j] == '*');
            else
            {
                P[posX-i][posY+j] = cube[i][j];

                *minX = min(posX - i, *minX);
                *minY = min(posY + j, *minY);
   
                *maxX = max(posX - i, *maxX);
                *maxY = max(posY + j, *maxY);
            }  
        }
}

int main()
{
    fin.open("input.txt");
    fout.open("output.txt");

    int n, m, x, y,
        deep = -1,
        minX = 10000,
        minY = 10000,
        maxX = -1,
        maxY = -1;

    fin >> n >> m;

    vector<vector<int>> matrix(n, vector<int>(m));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            fin >> matrix[i][j];
            deep = max(deep, matrix[i][j]);
        }

    cube[5] = "**+---+";
    cube[4] = "*/   /|";
    cube[3] = "+---+ |";
    cube[2] = "|   | +";
    cube[1] = "|   |/*";
    cube[0] = "+---+**";

    for (int i = 0; i < n; i++)
        for (int d = 1; d <= deep; d++)
            for (int j = 0; j < m; j++)
                if(matrix[i][j] >= d)
                {

                    y = (4 * j) + (2 * (n - i - 1)) + 1,
                    x = fullSize - (2 * (n - i - 1)) - (3 * (d-1)) - 1;

                    paint(x, y, &minX, &maxX, &minY, &maxY);
                }

    for (int i = minX; i <= maxX; i++)
    {
        for (int j = minY; j <= maxY; j++)
            fout << P[i][j];
        fout << endl;
    }

    fin.close();
    fout.close();

    return 0;
}
