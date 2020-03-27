#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <cfloat>
#include <algorithm>

using namespace std;


struct Edge//ребро графа
{
    char bgn;//начальная вершина
    char end;//конечная вершина
    double wt;//вес ребра
};

struct Step//возможные пути
{
    string path;//путь
    double length;//длина пути
    char estuary;
};

class Graph
{
private:
    vector <Edge> graph;//список смежности
    vector <Step> result;//преоброзовываемый список конечных путей
    vector <char> current;
    char source;
    char estuary;

public:

    Graph()
    {
        cin >> source >> estuary;
        char temp;
        while(cin >> temp)
        {
            Edge element;
            element.bgn = temp;
            cin >> element.end;
            cin >> element.wt;
            graph.push_back(element);
        }
        string buf = "";
        buf += source;
        for(auto & i : graph)
        {
            if(i.bgn == source)
            {
                buf += i.end;
                result.push_back({buf, i.wt});
                result.back().estuary = estuary;
                buf.resize(1);
            }
        }
        current.push_back(source);
    }

    size_t min_elem() //возвращает индекс минимального элемента из непросмотренных
    {
        double min;
        min = DBL_MAX;
        size_t temp = -1;
        for(size_t i(0); i < result.size(); i++)
        {
            if(result.at(i).length + abs(estuary - result.at(i).path.back()) < min)
            {
                if(is_visible(result.at(i).path.back()))
                {
                    result.erase(result.begin() + i);
                }
                else
                {
                    min = result.at(i).length + abs(estuary - result.at(i).path.back());
                    temp = i;
                }
            }
        }
        return temp;
    }

    bool is_visible(char value)//проверка доступа к вершине
    {
        for(char i : current) {
            if (i == value) {
                return true;
            }
        }
        return false;
    }

    void Search()
    {
        sort(result.begin(), result.end(), [](const Step & a, const Step & b) -> bool
        {
            return a.length + a.estuary - a.path.back() > b.length + b.estuary - b.path.back();
        });
        while(true)
        {
            size_t min = min_elem();
            if(min == -1){
                cout << "Wrong graph";
                break;
            }
            if(result.at(min).path.back() == estuary)
            {
                cout << result.at(min).path;
                return;
            }
            for(auto & i : graph)
            {
                if(i.bgn == result.at(min).path.back())
                {
                    string buf = result.at(min).path;
                    buf += i.end;
                    //cout << buf << endl;
                    result.push_back({buf, i.wt + result.at(min).length});
                }
            }
            current.push_back(result.at(min).path.back());
            result.erase(result.begin() + min);
        }
    }
};



int main()
{
    Graph element;
    element.Search();
    return 0;
}