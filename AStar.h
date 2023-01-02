#include "math.h"
#include <array>
#include <chrono>
#include <cstring>
#include <iostream>
#include <queue>
#include <set>
#include <stack>
#include <tuple>

using std::vector;
using std::pair;
using std::stack;
using std::tuple;
using std::array;
using std::get;
using std::cout;
using std::endl;

typedef pair<int, int> Pair;
typedef tuple<double, int, int> Tuple;

// A structure to hold the necessary parameters
struct cell {
    // Row and Column index of its parent
    Pair parent;
    // f = g + h
    double f, g, h;
    cell() : parent(-1, -1)
        , f(-1)
        , g(-1)
        , h(-1)
    {
    }
};

// A function to check whether given cell (row, col)
// is a valid cell or not.
template <size_t ROW, size_t COL>
bool isValid(const array<array<int, COL>, ROW>& grid,
             const Pair& point)
{ // Returns true if row number and column number is in
  // range
    if (ROW > 0 && COL > 0)
        return (point.first >= 0) && (point.first < ROW)
               && (point.second >= 0)
               && (point.second < COL);

    return false;
}
// A function to check whether the given cell is
// blocked or not
template <size_t ROW, size_t COL>
bool isUnBlocked(const array<array<int, COL>, ROW>& grid,
                 const Pair& point)
{
    // Returns true if the cell is not blocked else false
    return isValid(grid, point)
           && grid[point.first][point.second] == 1;
}


//Функция, проверяющая, достигнута ли конечная точка
bool isDestination(const Pair& position, const Pair& dest)
{
    return position == dest;
}

//Функция для проверки условий выше
template<size_t ROW, size_t COL>
int isSomethingWrong(const array<array<int,COL>, ROW>&grid,
                     const Pair& src, Pair& dest)
{
    // If the source is out of range
    if (!isValid(grid,src,dest)) {
        //printf("Source is invalid\n");
        std::cout<<"Source is invalid"<<std::endl;
        return 1;
    }

    // If the destination is out of range
    if (!isValid(grid,dest)) {
        printf("Destination is invalid\n");
        return 1;
    }

    // Either the source or the destination is blocked
    if (!isUnBlocked(grid,src)
        || !isUnBlocked(grid,dest)) {
        printf("Source or the destination is blocked\n");
        return 1;
    }

    // If the destination cell is the same as source cell
    if (isDestination(src,dest)){
        printf("We are already at the destination\n");
        return 1;
    }
    return 0;
}
// A Utility Function to calculate the 'h' heuristics.
double calculateHValue(const Pair& src, const Pair& dest)
{
    // h is estimated with the two points distance formula
    return sqrt(pow((src.first - dest.first), 2.0)
                + pow((src.second - dest.second), 2.0));
}

// A Utility Function to trace the path from the source to
// destination
template <size_t ROW, size_t COL>
void tracePath(
    const array<array<cell, COL>, ROW>& cellDetails,
    const Pair& dest, stack<Pair>&Path)
{
    int row = dest.first;
    int col = dest.second;;
    Path.push(dest);
    Pair next_node = cellDetails[row][col].parent;
    do {
        next_node = cellDetails[row][col].parent;
        Path.push(next_node);
        row = next_node.first;
        col = next_node.second;
    } while (cellDetails[row][col].parent != next_node);

}

// A* алгоритм
template <size_t ROW, size_t COL>
void aStarSearch(const array<array<int, COL>, ROW>& grid,
                 const Pair& src, const Pair& dest, stack<Pair>&res)
{
    /* If the source is out of range
    if (!isValid(grid, src)) {
        cout<<"Source is invalid"<<endl;
        //return;
    }

     If the destination is out of range
    if (!isValid(grid, dest)) {
        cout<<"Destination is invalid"<<endl;
        return;
    }

     Either the source or the destination is blocked
    if (!isUnBlocked(grid, src)
        || !isUnBlocked(grid, dest)) {
        cout<<"Source or the destination is blocked"<<endl;
        return;
    }

     If the destination cell is the same as source cell
    if (isDestination(src, dest)) {
        cout<<"We are already at the destintaion"<<endl;
        return;
    }*/

    /*if(isSomethingWrong(grid,src,dest)){
        return;
    }*/
    // Create a closed list and initialise it to false which
    // means that no cell has been included yet This closed
    // list is implemented as a boolean 2D array
    bool closedList[ROW][COL];
    memset(closedList, false, sizeof(closedList));

    array<array<cell, COL>, ROW> cellDetails;

    int i, j;

    i = src.first, j = src.second;
    cellDetails[i][j].f = 0.0;
    cellDetails[i][j].g = 0.0;
    cellDetails[i][j].h = 0.0;
    cellDetails[i][j].parent = { i, j };

    std::priority_queue<Tuple, std::vector<Tuple>, std::greater<Tuple>> openList;

    openList.emplace(0.0, i, j);

    // We set this boolean value as false as initially
    // the destination is not reached.
    while (!openList.empty()) {
        const Tuple& p = openList.top();
        // Add this vertex to the closed list
        i = get<1>(p);
        j = get<2>(p);

        // Remove this vertex from the open list
        openList.pop();
        closedList[i][j] = true;

        for (int add_x = -1; add_x <= 1; add_x++) {
            for (int add_y = -1; add_y <= 1; add_y++) {
                Pair neighbour(i + add_x, j + add_y);
                // Only process this cell if this is a valid
                // one
                if (isValid(grid, neighbour)) {
                    // If the destination cell is the same
                    // as the current successor
                    if (isDestination(
                            neighbour,
                            dest)) { // Set the Parent of
                                     // the destination cell
                        cellDetails[neighbour.first]
                                   [neighbour.second]
                                       .parent
                            = { i, j };
                        printf("The destination cell is "
                               "found\n");
                        return tracePath(cellDetails, dest, res);
                        return;
                    }
                    // If the successor is already on the
                    // closed list or if it is blocked, then
                    // ignore it.  Else do the following
                    else if (!closedList[neighbour.first]
                                        [neighbour.second]
                             && isUnBlocked(grid,
                                            neighbour)) {
                        double gNew, hNew, fNew;
                        gNew = cellDetails[i][j].g + 1.0;
                        hNew = calculateHValue(neighbour,
                                               dest);
                        fNew = gNew + hNew;

                        // If it isn’t on the open list, add
                        // it to the open list. Make the
                        // current square the parent of this
                        // square. Record the f, g, and h
                        // costs of the square cell
                        //             OR
                        // If it is on the open list
                        // already, check to see if this
                        // path to that square is better,
                        // using 'f' cost as the measure.
                        if (cellDetails[neighbour.first]
                                       [neighbour.second]
                                           .f
                                == -1
                            || cellDetails[neighbour.first]
                                          [neighbour.second]
                                              .f
                                   > fNew) {
                            openList.emplace(
                                fNew, neighbour.first,
                                neighbour.second);

                            // Update the details of this
                            // cell
                            cellDetails[neighbour.first] [neighbour.second].g = gNew;
                            cellDetails[neighbour.first] [neighbour.second].h = hNew;
                            cellDetails[neighbour.first] [neighbour.second].f = fNew;
                            cellDetails[neighbour.first] [neighbour.second].parent = { i, j };
                        }
                    }
                }
            }
        }
    }

    cout<<("Failed to find the Destination Cell\n");
}
