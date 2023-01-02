#include <bits/stdc++.h>
using namespace std;

int NO_PARENT = -1;

void dijkstra(vector<vector<int>> graph_matix,
              int start_node)
{
    int total_node = graph_matix[0].size();

    vector<int> shortestDistances(total_node);

    vector<bool> added(total_node);

    for (int node_index = 0; node_index < total_node;
         node_index++)
    {
        shortestDistances[node_index] = INT_MAX;
        added[node_index] = false;
    }

    shortestDistances[start_node] = 0;

    for (int i = 1; i < total_node; i++)
    {
        int nearest_node = -1;
        int shortestDistance = INT_MAX;
        for (int node_index = 0; node_index < total_node;
             node_index++)
        {
            if (!added[node_index] && shortestDistances[node_index] < shortestDistance)
            {
                nearest_node = node_index;
                shortestDistance = shortestDistances[node_index];
            }
        }
        // node 編號並不是順序流水號，跳過不處理
        if (nearest_node == -1)
            continue;

        added[nearest_node] = true;

        for (int node_index = 0; node_index < total_node;
             node_index++)
        {
            int edgeDistance = graph_matix[nearest_node]
                                          [node_index];

            if (edgeDistance > 0 && ((shortestDistance + edgeDistance) < shortestDistances[node_index]))
            {
                shortestDistances[node_index] = shortestDistance + edgeDistance;
            }
        }
    }

    for (int node_index = 0; node_index < total_node;
         node_index++)
    {
        if (node_index != start_node && shortestDistances[node_index] != INT_MAX)
        {
            cout << endl;
            cout << "ID: " << node_index << ", ";
            cout << "Next Hop: " << node_index << ", ";
            cout << "Cost: " << shortestDistances[node_index];
        }
        else if (node_index == start_node)
        {
            cout << endl;
            cout << "ID: " << start_node << ", ";
            cout << "Next Hop: " << start_node << ", ";
            cout << "Cost: " << 0;
        }
    }
}

int main()
{

    string input_file_path = "C:\\Users\\chi_t\\Desktop\\HW2_test_data\\Q3\\OSPF_in_5.txt";
    int start_id;
    int router_in_topology;
    ifstream file(input_file_path, ifstream::in);

    vector<vector<int>> graph_matix(65536, vector<int>(65536, 0));

    file >> router_in_topology;
    cout << "total: " << router_in_topology << " routers" << endl;
    int read_router = 0;
    while (router_in_topology > read_router)
    {
        int current_id;
        file >> current_id;

        int link_of_read_router = 0; // 單一router 連接的router 總數
        file >> link_of_read_router;
        cout << "router: " << current_id << " ,total linked: " << link_of_read_router << endl;

        int processed_count = 0; // 目前已經處理過的link數
        while (link_of_read_router > processed_count)
        {
            int current_linked_id;
            int current_cost;
            file >> current_linked_id;
            file >> current_cost;
            // 建立2d graph matrix
            graph_matix[current_id][current_linked_id] = current_cost;
            processed_count++;
        }

        read_router++;
    }

    file >> start_id;
    dijkstra(graph_matix, start_id);
    return 0;
}