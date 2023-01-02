#include <bits/stdc++.h>
using namespace std;

void find_path(map<pair<int, int>, int> graph_matix,
               int start_node, int max_id, string output_path)
{
    int total_node = max_id + 1; // 紀錄一下最大的id，作為迴圈上限

    vector<int> shortest_dists(total_node); // 紀錄到各node的最短路徑
    vector<bool> processed(total_node);     // 紀錄處理過的node

    for (int node_index = 0; node_index < total_node;
         node_index++)
    {
        shortest_dists[node_index] = INT_MAX;  // 所有cost 先預設成最大值
        processed[node_index] = false; // 所有node都還沒處理過，預設false
    }

    shortest_dists[start_node] = 0; // 自己node code 是0

    for (int i = 0; i < total_node; i++)
    {
        int nearest_node = -1;
        int shortest_dist = INT_MAX;
        for (int node_index = 0; node_index < total_node;
             node_index++)
        {
            if (!processed[node_index] && shortest_dists[node_index] < shortest_dist)
            {
                nearest_node = node_index;
                shortest_dist = shortest_dists[node_index];
            }
        }
        // node 編號並不是順序流水號，找不到路徑就跳過不處理
        if (nearest_node == -1)
            continue;

        // 紀錄哪些node 已經找到最短距離
        processed[nearest_node] = true;

        for (int node_index = 0; node_index < total_node;
             node_index++)
        {
            int cost = graph_matix[{nearest_node, node_index}];

            if (cost > 0 && ((shortest_dist + cost) < shortest_dists[node_index]))
            {
                // 找到更近的路線
                shortest_dists[node_index] = shortest_dist + cost;
            }
        }
    }

    ofstream ofs;
    ofs.open(output_path);

    for (int node_index = 0; node_index < total_node;
         node_index++)
    {
        if (node_index != start_node && shortest_dists[node_index] != INT_MAX) // 只要不用最大值表示有找到最短路徑/或是node存在有處理到
        {
            ofs << "ID: " << node_index << ", ";
            ofs << "Next Hop: " << node_index << ", ";
            ofs << "Cost: " << shortest_dists[node_index] << endl;
        }
        else if (node_index == start_node) // 自己的距離是0
        {
            ofs << "ID: " << start_node << ", ";
            ofs << "Next Hop: " << start_node << ", ";
            ofs << "Cost: " << 0 << endl;
        }
    }
    ofs.close();
}

void task(string input_path, string output_path)
{
    string input_file_path = input_path;
    int start_node;
    int router_in_topology;
    ifstream file(input_file_path, ifstream::in);
    map<pair<int, int>, int> graph_matix;

    file >> router_in_topology;
    cout << "total: " << router_in_topology << " routers" << endl;
    int read_router = 0;
    int max_id = 0;
    while (router_in_topology > read_router)
    {
        int current_node;
        file >> current_node;

        int link_of_read_router = 0; // 單一router 連接的router 總數
        file >> link_of_read_router;
        cout << "router: " << current_node << " ,total linked: " << link_of_read_router << endl;

        int processed_count = 0; // 目前已經處理過的link數
        while (link_of_read_router > processed_count)
        {
            int current_linked_node;
            int current_cost;
            file >> current_linked_node;
            file >> current_cost;
            // 建立2d graph matrix
            graph_matix[{current_node, current_linked_node}] = current_cost;
            processed_count++;

            if (max_id < current_node)
                max_id = current_node;
            else if (max_id < current_linked_node)
                max_id = current_linked_node;
        }

        read_router++;
    }

    file >> start_node;
    find_path(graph_matix, start_node, max_id, output_path);
}

int main()
{
    task(".\\Q3\\OSPF_in_1.txt", ".\\OSPF_out_1.txt");  // task(input_path, output_path)
    task(".\\Q3\\OSPF_in_2.txt", ".\\OSPF_out_2.txt");
    task(".\\Q3\\OSPF_in_3.txt", ".\\OSPF_out_3.txt");
    task(".\\Q3\\OSPF_in_4.txt", ".\\OSPF_out_4.txt");
    task(".\\Q3\\OSPF_in_5.txt", ".\\OSPF_out_5.txt");
    return 0;
}