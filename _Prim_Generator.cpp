#include "Generator.h"


Map* _Prim_Generator::generate(Size _size) {
	Map* maze = new Map;
    // �ȳ�ʼ����ͼ�����γɻ���
    for (int i = 0; i < _size.first; ++i)
        maze->push_back(std::vector<int>());
    for (auto& row : *maze)
        for (int j = 0; j < _size.second; ++j)
            row.push_back(Cell::WALL);
    for (int i = 1; i <= _size.first - 2; i += 2)
        for (int j = 1; j <= _size.second - 2; j += 2)
            (*maze)[i][j] = Cell::PATH;
    // �������
    srand(static_cast<unsigned int>(time(NULL)));
    // ��¼����
    std::vector<Point> vp;
    // �����ʼ����ǽ���
    Point digger((rand() % (_size.first - 2) + 1) | 1, (rand() % (_size.second - 2) + 1) | 1);
    if (digger.x - 1 >= 2) vp.push_back(Point(digger.x - 1, digger.y));
    if (digger.x + 1 <= _size.first - 3) vp.push_back(Point(digger.x + 1, digger.y));
    if (digger.y - 1 >= 2) vp.push_back(Point(digger.x, digger.y - 1));
    if (digger.y + 1 <= _size.second - 3) vp.push_back(Point(digger.x, digger.y + 1));

    // ��Ǹ�ͨ·
    (*maze)[digger.x][digger.y] = Cell::FLAG;
    int pos = 0;
    // �������������Թ�
    while (!vp.empty())
    {
        // ��ǽ���������ѡȡһ��ǽ
        pos = rand() % vp.size();
        digger = vp[pos];
        // ��¼��ǽ�Ƿ��ͨ
        bool flag = false;
        if ((*maze)[digger.x + 1][digger.y] == Cell::WALL) // �ж��������л��������е�ǽ
        {
            if ((*maze)[digger.x][digger.y - 1] != (*maze)[digger.x][digger.y + 1]) //�ж������Ƿ�һ��ΪPATH����һ��ΪCell::FLAG
            {
                (*maze)[digger.x][digger.y] = Cell::PATH;
                // ���¼����ͨ·���б��
                if ((*maze)[digger.x][digger.y - 1] == Cell::FLAG) { (*maze)[digger.x][digger.y + 1] = Cell::FLAG; ++digger.y; }
                else { (*maze)[digger.x][digger.y - 1] = Cell::FLAG; --digger.y; }
                flag = true;
            }
        }
        else
        {
            if ((*maze)[digger.x - 1][digger.y] != (*maze)[digger.x + 1][digger.y])
            {
                (*maze)[digger.x][digger.y] = Cell::PATH;
                // ���¼����ͨ·���б��
                if ((*maze)[digger.x - 1][digger.y] == Cell::FLAG) { (*maze)[digger.x + 1][digger.y] = Cell::FLAG; ++digger.x; }
                else { (*maze)[digger.x - 1][digger.y] = Cell::FLAG; --digger.x; }
                flag = true;
            }
        }
        if (flag)
        {
            if (digger.x - 1 >= 2 && (*maze)[digger.x - 1][digger.y] == Cell::WALL) vp.push_back(Point(digger.x - 1, digger.y));
            if (digger.x + 1 <= _size.first - 3 && (*maze)[digger.x + 1][digger.y] == Cell::WALL) vp.push_back(Point(digger.x + 1, digger.y));
            if (digger.y - 1 >= 2 && (*maze)[digger.x][digger.y - 1] == Cell::WALL) vp.push_back(Point(digger.x, digger.y - 1));
            if (digger.y + 1 <= _size.second - 3 && (*maze)[digger.x][digger.y + 1] == Cell::WALL) vp.push_back(Point(digger.x, digger.y + 1));
        }
        // �����һ��Ԫ�����������Ԫ��
        vp[pos] = *(vp.end() - 1);
        vp.pop_back();
    }
    // ������ǵ�ͨ·��ԭ
    for (auto& v1 : (*maze))
        for (auto& v2 : v1)
            if (v2 == Cell::FLAG) v2 = Cell::PATH;
    return maze;
}


