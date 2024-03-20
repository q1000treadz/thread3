#include<iostream>
#include<vector>
#include "windows.h" 
#include "omp.h"
#include<chrono>
using namespace std;
long long test = 0;

int main() {
    srand(time(0));
   
	vector<vector<int>> data;
	for (int i = 0; i < 42; i++) {
		data.push_back({});
		for (int j = 0; j < 42; j++) {
			data[i].push_back(0);
		}
	}
    for (int y = 1; y <= 40; y++)
    {
        for (int x = 1; x <= 40; x++)
        {
            int rand1 = rand() % 4;
            if (rand1 == 3) {
                data[y][x] = 1;
            }
        }
    }
    int x, y, z = 0;
    vector<vector<int>>nextIter = data;
    for (int i = 1; i <= 100; i++)
    {
        system("cls");
        data = nextIter;
        std::chrono::high_resolution_clock::time_point start2 = std::chrono::high_resolution_clock::now();
        //#pragma omp parallel for reduction(+:y,x)

        #pragma omp parallel
        #pragma omp for
        for (int y = 1; y <= 40; y++)
        {
            for (int x = 1; x <= 40; x++)
            {
                if (data[x][y - 1] == 1) z++;
                if (data[x][y + 1] == 1) z++;
                if (data[x + 1][y - 1] == 1) z++;
                if (data[x + 1][y] == 1) z++;
                if (data[x + 1][y + 1] == 1) z++;
                if (data[x - 1][y - 1] == 1) z++;
                if (data[x - 1][y] == 1) z++;
                if (data[x - 1][y + 1] == 1) z++;
                if ((data[x][y] == 0 && z == 3) || (data[x][y] != 0 && (z == 2) || (z == 3))) nextIter[x][y] = 1;
                else nextIter[x][y] = 0;
                z = 0;
            }
        }
        std::chrono::high_resolution_clock::time_point end2 = std::chrono::high_resolution_clock::now();
        std::chrono::nanoseconds duration2 = std::chrono::duration_cast<std::chrono::nanoseconds>(end2 - start2);
        cout << duration2.count() << endl;
        test += duration2.count();
        for (y = 1; y <= 40; y++)
        {
            for (x = 1; x <= 40; x++)
            {
                cout<<nextIter[x][y];
            }
            printf("\n");
        }
        Sleep(500);
    }
    cout << test << ' '<<test/100<<endl;
    //188647 with parallel
    //202990 without
}