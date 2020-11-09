#include <iostream>
#include <tuple>
#include <vector>
#include <cmath>

#include "accessory.h"

/*
Необходимо реализовать две шаблонных функции:
1.  Функция print печати фигур на экран std::cout
    (печататься должны координаты вершин фигур). Функция должна принимать на вход std::tuple с фигурами,
    согласно варианту задания (минимум по одной каждого класса).
2.  Функция square вычисления суммарной площади фигур. Функция должна принимать на вход
    std::tuple с фигурами, согласно варианту задания (минимум по одной каждого класса).


Создать программу, которая позволяет:
·         Создает набор фигур согласно варианту задания (как минимум по одной фигуре каждого типа
с координатами типа int и координатами типа double).
·         Сохраняет фигуры в std::tuple
·         Печатает на экран содержимое std::tuple с помощью шаблонной функции print.
·         Вычисляет суммарную площадь фигур в std::tuple и выводит значение на экран.

вариант 14
*/
template <class T>
using vertex_t = std::pair<T,T>;

template <class T>
class Pentagon {
public:
    vertex_t<T> vertexes[5];
};

template <class T>
class Hexagon {
public:
    vertex_t<T> vertexes[6];
};

template <class T>
class Octagon {
public:
    vertex_t<T> vertexes[8];
};


template <class T>
void print_array(std::stringstream& buffer, const vertex_t<T>* array, size_t size, const char* name){
    buffer << name << ": " << std::endl;
    for(size_t i = 0;i < size;i++){
        buffer << array[i].first << " " << array[i].second << std::endl;
    }
}

double get_det(const double x1, const double y1,
               const double x2, const double y2){
    return x1 * y2 - x2 * y1;
}

template <class T>
double gauss_area(const vertex_t<T>* nodes, size_t size){
    double out = 0.0;
    auto count = size;
    for(size_t i = 0; i < (count - 1); i++){
        out += get_det(static_cast<double>(nodes[i].first),static_cast<double>(nodes[i].second),
                       static_cast<double>(nodes[i+1].first),static_cast<double>(nodes[i+1].second));
    }
    out += get_det(static_cast<double>(nodes[count-1].first),static_cast<double>(nodes[count-1].second),
                   static_cast<double>(nodes[0].first),static_cast<double>(nodes[0].second));
    return fabs(0.5 * out);
}

template <class T>
void assign(vertex_t<T>* nodes,std::vector<vertex_t<T>>& numbers, size_t size){
    for(int i = 0;i < size; i++){
        nodes[i] = numbers[i];
    }
}

template <class T,class K>
void print(std::stringstream& buffer, const std::tuple<Pentagon<T>,Hexagon<T>,Octagon<T>,Pentagon<K>,Hexagon<K>,Octagon<K>>& array){
    Pentagon<T> pentagon1 = std::get<0>(array);
    Hexagon<T> hexagon1 = std::get<1>(array);
    Octagon<T> octagon1 = std::get<2>(array);

    Pentagon<K> pentagon2 = std::get<3>(array);
    Hexagon<K> hexagon2 = std::get<4>(array);
    Octagon<K> octagon2 = std::get<5>(array);

    print_array<T>(buffer, pentagon1.vertexes,5, "Pentagon");
    print_array<T>(buffer, hexagon1.vertexes,6, "Hexagon");
    print_array<T>(buffer, octagon1.vertexes,8, "Octagon");

    print_array<K>(buffer, pentagon2.vertexes,5, "Pentagon");
    print_array<K>(buffer, hexagon2.vertexes,6, "Hexagon");
    print_array<K>(buffer, octagon2.vertexes,8, "Octagon");
}


template <class T,class K>
double square(const std::tuple<Pentagon<T>,Hexagon<T>,Octagon<T>,Pentagon<K>,Hexagon<K>,Octagon<K>>& array){
    double pentagon_area1 = gauss_area(std::get<0>(array).vertexes,5);
    double hexagon_area1 = gauss_area(std::get<1>(array).vertexes,6);
    double octagon_area1 = gauss_area(std::get<2>(array).vertexes,8);

    double pentagon_area2 = gauss_area(std::get<3>(array).vertexes,5);
    double hexagon_area2 = gauss_area(std::get<4>(array).vertexes,6);
    double octagon_area2 = gauss_area(std::get<5>(array).vertexes,8);

    return pentagon_area1 + hexagon_area1 + octagon_area1 +
        pentagon_area2 + hexagon_area2 + octagon_area2;
}


int main(){

    std::string cmd;
    std::vector<std::string> out;
    std::stringstream buffer;
    int count = 0;
    std::tuple<Pentagon<int>,Hexagon<int>,Octagon<int>,Pentagon<double>,Hexagon<double>,Octagon<double>> gtuple;
    help();
    while (true){
        getline(std::cin, cmd);
        std::string prefix = std::string("query ") + int_to_string(count) + ": ";
        if (cmd == "exit"){
            break;
        }
        else if (cmd == "help"){
            help();
        }
        else if (cmd == "area"){
            buffer << prefix << std::endl;
            buffer << "area is " << square(gtuple) << std::endl;
        }
        else if (cmd == "print"){
            buffer << prefix << std::endl;
            print<int,double>(buffer,gtuple);
        }
        else {
            std::vector<std::string> array = split(cmd,' ');
            std::vector<vertex_t<int>> numbers_int;
            numbers_int.resize((array.size() - 1) / 2);

            std::vector<vertex_t<double>> numbers_double;
            numbers_double.resize((array.size() - 1) / 2);


            int j = 0;
            for(size_t i = 0;i < numbers_int.size() * 2 ; i += 2){
                //std::cout << "i is " << i << std::endl;
                //std::cout << "i+1 is " << i + 1 << std::endl;
                if (count >= 0 && count <= 2){
                    numbers_int[j] = {string_to_int(array[i]),string_to_int(array[i+1])};
                }
                else if (count >= 3 && count <= 5){
                    numbers_double[j] = {string_to_double(array[i]),string_to_double(array[i+1])};
                }
                else {
                    std::perror("count error");
                }

                j++;
            }
            //std::cout << "*******" << std::endl;

            if (count >= 0 && count <= 2){
                if (array.back() == "pentagon"){
                    assign<int>(std::get<0>(gtuple).vertexes,numbers_int,5);
                }
                else if (array.back() == "hexagon"){
                    assign<int>(std::get<1>(gtuple).vertexes,numbers_int,6);
                }
                else if (array.back() == "octagon"){
                    assign<int>(std::get<2>(gtuple).vertexes,numbers_int,8);
                }
            }
            else if (count >= 3 && count <= 5){
                if (array.back() == "pentagon"){
                    assign<double>(std::get<3>(gtuple).vertexes,numbers_double,5);
                }
                else if (array.back() == "hexagon"){
                    assign<double>(std::get<4>(gtuple).vertexes,numbers_double,6);
                }
                else if (array.back() == "octagon"){
                    assign<double>(std::get<5>(gtuple).vertexes,numbers_double,8);
                }
            }
        }
        count++;
    }

    std::cout << buffer.str() << std::endl;

}