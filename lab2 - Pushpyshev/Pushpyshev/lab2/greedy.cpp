#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


struct Edge
{
    char bgn;
    char end;
    double wt;
};


class Greedy_graph
{
private:
    vector <Edge> graph;
    vector <char> result;
    vector <char> current;
    char source;
    char estuary;

public:
    Greedy_graph()
    {

    }
    void input_graph(){
        cin >> source >> estuary;
        char temp;
        while(cin >> temp)
        {
            Edge element;
            element.bgn = temp;
            if(!(cin >> element.end))
                break;
            if(!(cin >> element.wt))
                break;
            graph.push_back(element);
        }
        sort(graph.begin(), graph.end(), [](Edge first, Edge second)
        {
            return first.wt < second.wt;
        });
    }

    bool is_visible(char value)
    {
        for(char i : current)
            if(i == value)
                return true;
        return false;
    }


    void to_search()
    {
        if(source != estuary)
            Search(source);
    }

    bool Search(char value)
    {
        if(value == estuary)
        {
            result.push_back(value);
            return true;
        }
        current.push_back(value);
        for(auto & i : graph)
        {
            if(value == i.bgn)
            {
                if(is_visible(i.end))
                    continue;
                result.push_back(i.bgn);
                bool flag = Search(i.end);
                if(flag)
                   return true;
                result.pop_back();
            }
        }
        return false;
    }

    void Print()
    {
        for(char i : result)
            cout << i;
    }
};

int main()
{
    Greedy_graph element;
    element.input_graph();
    element.to_search();
    element.Print();
    return 0;
}