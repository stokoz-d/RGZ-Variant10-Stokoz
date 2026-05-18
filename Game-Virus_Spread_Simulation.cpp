// Game-Virus_Spread_Simulation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <set>
#include <cstdlib>
#include <ctime>
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
        cout << "========== NETWORK ==========" << endl;

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

    srand(time(0));

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

    set<int> infected;
    set<int> protected_nodes;

    infected.insert(1);

    int turn = 1;
    int difficulty;
    int infection_chance;

    cout << "==============================" << endl;
    cout << " VIRUS SPREAD SIMULATION " << endl;
    cout << "==============================" << endl;

    cout << endl;

    cout << "Choose difficulty:" << endl;
    cout << "1 - Easy" << endl;
    cout << "2 - Medium" << endl;
    cout << "3 - Hard" << endl;

    cout << endl;
    cout << "Your choice: ";
    cin >> difficulty;

    if (difficulty == 1)
    {
        infection_chance = 40;
    }
    else if (difficulty == 2)
    {
        infection_chance = 65;
    }
    else
    {
        infection_chance = 85;
    }

    network.show_network();

    while (true)
    {
        cout << endl;
        cout << "==============================" << endl;
        cout << "TURN " << turn << endl;
        cout << "==============================" << endl;

        cout << endl;

        cout << "INFECTED NODES: ";

        for (int x : infected)
        {
            cout << "[INFECTED:" << x << "] ";
        }

        cout << endl << endl;

        cout << "PROTECTED NODES: ";

        for (int x : protected_nodes)
        {
            cout << "[PROTECTED:" << x << "] ";
        }

        cout << endl << endl;

        int protect;

        cout << "Choose node to protect: ";
        cin >> protect;

        if (infected.find(protect) == infected.end())
        {
            protected_nodes.insert(protect);
        }
        else
        {
            cout << endl;
            cout << "This node is already infected!" << endl;
        }

        vector<int> new_infected;

        for (int node : infected)
        {
            vector<int> neigh = network.neighbors(node);

            for (int next : neigh)
            {
                if (infected.find(next) == infected.end() &&
                    protected_nodes.find(next) == protected_nodes.end())
                {
                    int chance = rand() % 100;

                    if (chance < infection_chance)
                    {
                        new_infected.push_back(next);

                        cout << endl;
                        cout << "Node " << next << " was infected!" << endl;
                    }
                    else
                    {
                        cout << endl;
                        cout << "Node " << next << " resisted infection!" << endl;
                    }
                }
            }
        }

        for (int x : new_infected)
        {
            infected.insert(x);
        }

        cout << endl;
        cout << "========== NETWORK STATUS ==========" << endl;

        for (int i = 1; i <= 10; i++)
        {
            if (infected.find(i) != infected.end())
            {
                cout << "Node " << i << " -> INFECTED" << endl;
            }
            else if (protected_nodes.find(i) != protected_nodes.end())
            {
                cout << "Node " << i << " -> PROTECTED" << endl;
            }
            else
            {
                cout << "Node " << i << " -> SAFE" << endl;
            }
        }

        if (infected.size() >= 8)
        {
            cout << endl;
            cout << "==============================" << endl;
            cout << " ALL NETWORK INFECTED! " << endl;
            cout << " YOU LOST! " << endl;
            cout << "==============================" << endl;
            break;
        }

        if (protected_nodes.size() >= 5)
        {
            cout << endl;
            cout << "==============================" << endl;
            cout << " NETWORK PARTIALLY SAVED! " << endl;
            cout << " YOU WIN! " << endl;
            cout << "==============================" << endl;
            break;
        }

        turn++;

        cout << endl;
    }

    return 0;
}
