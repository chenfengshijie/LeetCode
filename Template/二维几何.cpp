#include <iostream>
#include <cstdio>

/**
 *!如何表示二维平面的一条直线。一般通过记录直线上一点和直线的方向向量。
 * !通过记录线段的两个端点记录线段信息
 * !按照一定顺序记录多边形端点来记录多边形
 */

struct Point
{
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
};

int main()
{
}