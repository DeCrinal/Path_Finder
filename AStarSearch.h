#ifndef ASTARSEARCH_H
#define ASTARSEARCH_H
#include <iostream>
#include <array>
#include <vector>
#include <stack>
#include <set>
#include <tuple>
#include <queue>
#include <cmath>
#include <cstring>
#include <iostream>

using std::vector;
using std::pair;
using std::stack;
using std::tuple;
using std::array;
using std::get;
using std::cout;
using std::endl;

typedef std::pair<int,int> Pair;
typedef tuple<double,int,int> Tuple;

struct cell {
    // Индексы родителя
    Pair parent;
    // f = g + h
    double f, g, h;
    cell():parent(-1, -1), f(-1), g(-1), h(-1) {}
};

class AStarSearch{
private:
    static int ROW;
    static int COL;

    static bool isValid(const vector<vector<int>>& field, const Pair& point);

    //Функция проверяет, находится ли данная точка в недоступной зоне
    static bool isUnBlocked(const vector<vector<int>>& field, const Pair& point);

    //Функция проверяет достигнута ли конечная точка
    static bool isDestination(const Pair& position, const Pair& dest);

    //Функция для проверки условий выше
    static int isSomethingWrong(const vector<vector<int>>&field, const Pair& src,
                    const Pair& dest);
    //Функция вычисления эвристики 'h'
    static double calculateHValue(const Pair& src, const Pair& dest);

    // Функция для генерации пути по информации о предках
    static void tracePath( const vector<vector<cell>>& cellDetails, const Pair& dest,
                    stack<Pair>&Path);
    AStarSearch();
public:
// A* алгоритм для поиска кратчайшего пути
static void aStarSearch(const vector<vector<int>>& grid,
                    const Pair& src, const Pair& dest, stack<Pair>&res);

};
#endif // ASTARSEARCH_H
