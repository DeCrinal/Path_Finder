#include "AStarSearch.h"

int AStarSearch::ROW=0;
int AStarSearch::COL=0;

bool AStarSearch::isValid(const vector<vector<int>>& grid,
                               const Pair& point) {

    // Возвращает true, если клетка в допустимой зоне
    if (AStarSearch::ROW > 0 && AStarSearch::COL > 0)
        return (point.first >= 0) && (point.first < ROW)
                && (point.second >= 0)
                && (point.second < COL);
    return false;
}

bool AStarSearch::isUnBlocked(const vector<vector<int>>& grid,
                const Pair& point) {
    // Возвращает true, если клетка не в заблокированной зоне
    return isValid(grid, point) && grid[point.first][point.second] == 1;
}

AStarSearch::AStarSearch(){

}

//Функция, проверяющая, достигнута ли конечная точка
bool AStarSearch::isDestination(const Pair& position, const Pair& dest)
{
    return position == dest;
}

//Функция для проверки условий выше
int AStarSearch::isSomethingWrong(const vector<vector<int>>&grid,
                     const Pair& src, const Pair& dest)
{
    if (!isValid(grid,src))
    {
        std::cout<<"Source is invalid"<<std::endl;
        return 1;
    }

    if (!isValid(grid,dest))
    {
        cout<<"Destination is invalid\n";
        return 1;
    }

    if (!isUnBlocked(grid,src) || !isUnBlocked(grid,dest))
    {
        printf("Source or the destination is blocked\n");
        return 1;
    }

    if (isDestination(src,dest))
    {
        cout<<"We are already at the destination\n";
        return 1;
    }
    return 0;
}

double AStarSearch::calculateHValue(const Pair& src, const Pair& dest)
{
    return sqrt(pow((src.first - dest.first), 2.0)
                + pow((src.second - dest.second), 2.0));
}

void AStarSearch::tracePath(
    const vector<vector<cell>>& cellDetails,
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

void AStarSearch::aStarSearch(const vector<vector<int>>& grid,
                 const Pair& src, const Pair& dest, stack<Pair>&res)
{

    ROW = grid.size();
    COL = grid[0].size();
    if(isSomethingWrong(grid,src,dest))
    {
        return;
    }

    //Создание closedList. closedList - информация о пройденных клетках
    bool closedList[ROW][COL];
    memset(closedList, false, sizeof(closedList));

    vector<vector<cell>>cellDetails;

    cellDetails.resize(ROW);
    for(int i = 0; i<ROW;i++)
    {
        cellDetails[i].assign(COL,cell());
    }

    int i, j;

    i = src.first, j = src.second;
    cellDetails[i][j].f = 0.0;
    cellDetails[i][j].g = 0.0;
    cellDetails[i][j].h = 0.0;
    cellDetails[i][j].parent = { i, j };

    std::priority_queue<Tuple, std::vector<Tuple>, std::greater<Tuple>> openList;

    openList.emplace(0.0, i, j);

    while (!openList.empty())
    {
        const Tuple& p = openList.top();

        i = get<1>(p);
        j = get<2>(p);

        openList.pop();
        closedList[i][j] = true;

        for (int add_x = -1; add_x <= 1; add_x++)
        {
            for (int add_y = -1; add_y <= 1; add_y++)
            {
                Pair neighbour(i + add_x, j + add_y);

                if (isValid(grid, neighbour))
                {
                    if (isDestination( neighbour, dest))
                    {

                        cellDetails[neighbour.first][neighbour.second].parent
                                = { i, j };
                        cout<<"The destination cell is found\n";
                        return tracePath(cellDetails, dest, res);
                        return;
                    }
                    else if (!closedList[neighbour.first][neighbour.second]
                            && isUnBlocked(grid, neighbour))
                    {
                        double gNew, hNew, fNew;
                        gNew = cellDetails[i][j].g + 1.0;
                        hNew = calculateHValue(neighbour, dest);
                        fNew = gNew + hNew;

                        if (cellDetails[neighbour.first][neighbour.second].f == -1
                            || cellDetails[neighbour.first][neighbour.second].f > fNew)
                        {
                            openList.emplace( fNew, neighbour.first, neighbour.second);

                            //Обновление информации о клетках
                            cellDetails[neighbour.first][neighbour.second].g = gNew;
                            cellDetails[neighbour.first][neighbour.second].h = hNew;
                            cellDetails[neighbour.first][neighbour.second].f = fNew;
                            cellDetails[neighbour.first][neighbour.second].parent =
                                { i, j };
                        }
                    }
                }
            }
        }
    }

    cout<<("Failed to find the Destination Cell\n");
}
