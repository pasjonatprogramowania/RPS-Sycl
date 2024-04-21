#include <iostream>
#include <vector>
#include <sycl/sycl.hpp>
#include <time.h>
#include <cstdlib>
#include <windows.h>


using namespace sycl;

//enum Direction = {LEFT, RIGHT, UP, DOWN};

char mixColors(char a, char b){
    if (a == b) return a;
    if (a < b && b != 'r') return b;
    else return a;
}

class GameEngine{
    

public:
    void getNewState(std::vector<char>& grid){
        
        buffer buffInputGrid(&grid, range<1>(grid.size()));
        buffer buffOutputGrid(&newGrid, range<1>(grid.size()));

        this->q.submit([&](handler& h){
            accessor inputGridAccessor(buffInputGrid, read_only);
            accessor outputGridAccessor(buffOutputGrid, write_only);
            h.parallel_for(range<1>(grid.size()), [=](id<1> i)){
                outputGridAccessor[i] = mixColors(inputGridAccessor[i], inputGridAccessor[(i + 1) % grid.size()]);
            }
        });

        grid = newGrid;
    }
};

int main(){
    int N = 20;
    std::vector<char> grid;
    std::vector<char> newGrid;
    grid.resize(N);
    newGrid.resize(N);

    queue q(device_selector);
    buffer buffInputGrid(&grid, range<1>(grid.size()));
    buffer buffOutputGrid(&newGrid, range<1>(grid.size()));

    char letters[] = {'r', 'g', 'b'};
    srand(time(NULL));
    for (int i = 0; i < N; i++){
        grid[i] = letters[rand() % 3];
    }

    while (true){
        for (int i = 0; i < N; i++) std::cout << grid[i];
        std::cout << std::endl;

        q.submit([&](handler& h){
            accessor inputGridAccessor(buffInputGrid, read_only);
            accessor outputGridAccessor(buffOutputGrid, write_only);
            h.parallel_for(range<1>(grid.size()), [=](id<1> i)){
                outputGridAccessor[i] = mixColors(inputGridAccessor[i], inputGridAccessor[(i + 1) % grid.size()]);
            }
        })
        .wait();

        grid = newGrid;

        Sleep(2);
    }

    return 0;
}