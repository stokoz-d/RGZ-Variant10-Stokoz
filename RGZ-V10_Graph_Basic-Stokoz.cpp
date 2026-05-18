// RGZ-V10-Stokoz.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include "windows.h"

using namespace std;

template <class T>
class Graph
{
private:

    unordered_map<T, vector<T>> adj_list;

public:

    void add_node(T node)
    {
        if (adj_list.find(node) == adj_list.end())
        {
            adj_list[node] = vector<T>();
        }
    }

    void add_edge(T from, T to)
    {
        add_node(from);
        add_node(to);

        adj_list[from].push_back(to);
    }

    void remove_node(T node)
    {
        adj_list.erase(node);

        for (auto& pair : adj_list)
        {
            vector<T>& neighbors = pair.second;

            neighbors.erase(
                remove(neighbors.begin(), neighbors.end(), node),
                neighbors.end()
            );
        }
    }

    vector<T> neighbors(T node) const
    {
        auto it = adj_list.find(node);

        if (it != adj_list.end())
        {
            return it->second;
        }

        return vector<T>();
    }

    void show()
    {
        for (auto& pair : adj_list)
        {
            cout << pair.first << " -> ";

            for (auto& neighbor : pair.second)
            {
                cout << neighbor << " ";
            }

            cout << endl;
        }
    }
};

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Graph<int> g;

    g.add_node(1);
    g.add_node(2);
    g.add_node(3);

    g.add_edge(1, 2);
    g.add_edge(1, 3);
    g.add_edge(2, 3);
    g.add_edge(3, 4);
    g.add_edge(4, 5);
    g.add_edge(5, 1);

    cout << "Граф:" << endl;
    g.show();

    cout << endl;

    vector<int> n = g.neighbors(1);

    cout << "Сусіди вузла 1: ";

    for (int x : n)
    {
        cout << x << " ";
    }

    cout << endl << endl;

    cout << "Видалення вузла 3" << endl;

    g.remove_node(3);

    cout << endl;

    g.show();

    return 0;
}