#ifndef T1_POLYGON_H
#define T1_POLYGON_H
class Polygon
{
  // Триангуляция Делоне
  // Алгоритм триангуляции:
  //1. Берем три вершины A1, A2, A3
  //2. Проверяем образуют ли вектора A1A3, A1A2 левую тройку векторов (векторное произведение положительно).
  //3. Проверяем нет ли внутри треугольника A1A2A3 какой-либо из оставшихся вершин многоугольника.
  //4. Если оба условия выполняются, то строим треугольник A1A2A3, а вершину A2 исключаем из многоугольника, не трогая вершину A1, сдвигаем вершины A2 (A2 на A3), A3 (A3 на A4)
  //5. Если хоть одно условие не выполняется переходим к следующим трем вершинам.
  //6. Повторяем с 1 шага, пока не останется три вершины.
};
#endif
