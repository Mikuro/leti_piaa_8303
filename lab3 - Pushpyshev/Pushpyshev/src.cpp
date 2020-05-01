#include <iostream>
#include <map>
#include <cmath>
#include <set>
#include <queue>
#include <ctime>


class FordFalk {
public:
    std::map< char, std::map< char, int > > graph;

    void input_graph(int count) {
        char from;
        char to;
        int weight;
        for(int i = 0; i < count; i++) {
            std::cin >> from >> to >> weight;
            graph[from][to] = weight;
        }
    }

    void maxFlow(char source, char estuary){
        std::map< char, std::map< char, int > > network = graph;
        std::map< char, std::pair< char, int > > way = BFS(network, source, estuary);

        while( !way.empty() ){
            update_net(network, way, source, estuary);
            way = BFS(network, source, estuary);
        }

        int max_flow = 0;

        for(auto i : graph[source]){
            max_flow += i.second - network[source][i.first];
        }

        std::cout << max_flow << std::endl;

        for(const auto& neighbour : graph)
            for(auto node : neighbour.second){
                std::cout << neighbour.first << " " << node.first << " ";
                if(node.second - network[neighbour.first][node.first] >= 0)
                    std::cout << node.second - network[neighbour.first][node.first] << std::endl;
                else
                    std::cout << 0 << std::endl;
            }
    }

    int get_min_flow(std::map< char, std::pair< char, int > > way, char source, char stock){
        int min_flow = way[stock].second;
        for(char node = stock; node != source; node = way[node].first) {
            if (min_flow > way[node].second)
                min_flow = way[node].second;
        }
        return min_flow;
    }

    //перестройка графа после очередного прохода
    void update_net(std::map< char, std::map< char, int > > &network, std::map< char, std::pair< char, int > > way, char source, char stock){
        int min_flow = get_min_flow(way, source, stock);
        for(char node = stock; node != source; node = way[node].first){
            if(way[node].second - min_flow == 0)
                network[way[node].first].erase(node);
            else
                network[way[node].first][node] -= min_flow;
            network[node][way[node].first] += min_flow;
        }
    }
    //Поиск в ширину
    std::map< char, std::pair< char, int > > BFS(std::map< char, std::map< char, int > > net, char source, char stock){
        std::set<char> visited_nodes;//множество посещенных вершин
        std::queue<char> queue_nodes;//Очередь вершин
        std::map< char, std::pair< char, int > > way;//путь
        std::map< char, std::map< char, int > >::iterator current;//Текущий обрабатывваемый элемент
        visited_nodes.insert(source);
        queue_nodes.push(source);
        while(queue_nodes.front() != stock && !queue_nodes.empty()){
            current = net.find(queue_nodes.front());
            queue_nodes.pop();
            for(auto elem : current->second)
                if(visited_nodes.find(elem.first) == visited_nodes.end()){
                    queue_nodes.push(elem.first);
                    visited_nodes.insert(elem.first);
                    way[elem.first] = std::pair< char, double >(current->first, elem.second);
                }
        }
        if(visited_nodes.find(stock) == visited_nodes.end())
            return std::map<char,std::pair< char, int > >();
        return way;
    }
};

int main() {
    int count;
    char source;
    char estuary;
    std::cin >> count;
    std::cin >> source;
    std::cin >> estuary;
    time_t start, end;
    time (&start);
    FordFalk graph;
    graph.input_graph(count);
    graph.maxFlow(source, estuary);
    time (&end);
    std::cout << std::endl << "Time for algorithm: " << difftime(end, start) << " сек";
    return 0;
}