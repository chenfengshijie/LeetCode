#include <iostream>
#include <vector>

/**
 * @brief 判断点是否在多边形内部
 *
 */

struct Point
{
    double x;
    double y;
    Point(double xCoord, double yCoord) : x(xCoord), y(yCoord) {}
};

class Polygon
{
private:
    std::vector<Point> vertices;

public:
    // 构造函数，传入多边形的顶点
    Polygon(const std::vector<Point> &points) : vertices(points) {}

    // 判断点是否在多边形内部
    bool isPointInside(const Point &target)
    {
        int numIntersections = 0;
        int n = vertices.size();

        // 遍历多边形的边
        for (int i = 0; i < n; i++)
        {
            Point v1 = vertices[i];
            Point v2 = vertices[(i + 1) % n];

            // 检查点与边的相对位置
            if ((v1.y > target.y) != (v2.y > target.y))
            {
                double intersectionX = (v2.x - v1.x) * (target.y - v1.y) / (v2.y - v1.y) + v1.x;
                if (target.x < intersectionX)
                {
                    numIntersections++;
                }
            }
        }

        // 奇数个交点则在多边形内部
        return numIntersections % 2 != 0;
    }
};

int main()
{
    // 构建一个示例多边形
    std::vector<Point> polygonVertices = {
        Point(1.0, 1.0),
        Point(4.0, 1.0),
        Point(4.0, 4.0),
        Point(1.0, 4.0)};

    Polygon polygon(polygonVertices);

    // 要判断的点
    Point targetPoint(2.5, 2.5);

    // 判断点是否在多边形内部
    if (polygon.isPointInside(targetPoint))
    {
        std::cout << "点在多边形内部" << std::endl;
    }
    else
    {
        std::cout << "点在多边形外部" << std::endl;
    }

    return 0;
}
