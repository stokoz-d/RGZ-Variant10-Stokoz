// Virus_Spread_Simulation.cpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <set>
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
        adj_list[to].push_back(from);
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

    void show_network()
    {
        cout << endl;
        cout << "=== NETWORK STRUCTURE ===" << endl;

        for (auto& pair : adj_list)
        {
            cout << "Node " << pair.first << " -> ";

            for (auto& node : pair.second)
            {
                cout << node << " ";
            }

            cout << endl;
        }

        cout << endl;
    }
};

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Graph<int> network;

    network.add_edge(1, 2);
    network.add_edge(1, 3);
    network.add_edge(2, 4);
    network.add_edge(2, 5);
    network.add_edge(3, 6);
    network.add_edge(4, 7);
    network.add_edge(5, 8);
    network.add_edge(6, 9);
    network.add_edge(7, 10);

    network.show_network();

    set<int> infected;
    set<int> protected_nodes;

    infected.insert(1);

    int turn = 1;

    while (true)
    {
        cout << "==========================" << endl;
        cout << "TURN " << turn << endl;
        cout << "==========================" << endl;

        cout << endl;

        cout << "INFECTED NODES: ";

        for (int x : infected)
        {
            cout << x << " ";
        }

        cout << endl;

        cout << "PROTECTED NODES: ";

        for (int x : protected_nodes)
        {
            cout << x << " ";
        }

        cout << endl << endl;

        int protect;

        cout << "Choose node to protect: ";
        cin >> protect;

        protected_nodes.insert(protect);

        vector<int> new_infected;

        for (int node : infected)
        {
            vector<int> neigh = network.neighbors(node);

            for (int next : neigh)
            {
                if (infected.find(next) == infected.end() &&
                    protected_nodes.find(next) == protected_nodes.end())
                {
                    new_infected.push_back(next);
                }
            }
        }

        for (int x : new_infected)
        {
            infected.insert(x);
        }

        cout << endl;
        cout << "Virus spread completed..." << endl;

        if (infected.size() >= 10)
        {
            cout << endl;
            cout << "ALL NETWORK INFECTED!" << endl;
            cout << "YOU LOST!" << endl;
            break;
        }

        if (protected_nodes.size() >= 5)
        {
            cout << endl;
            cout << "NETWORK PARTIALLY SAVED!" << endl;
            cout << "YOU WIN!" << endl;
            break;
        }

        turn++;

        cout << endl;
    }

    return 0;
}
