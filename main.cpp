#include <bits/stdc++.h>
using namespace std;
#include "mrtdata.h"

int find_distance(string source_stop, string target_stop, unordered_map<string, vector<pair<string,int>>> mrt_adjacency_list) {
    for (pair<string,int> current_target: mrt_adjacency_list[source_stop]) {
        if (current_target.first == target_stop) {
            return current_target.second;
        }
    }
}

//mrt_adjacency_list and mrt_names are available!!
int main() {
    init_mrt_adjacency_list();
    init_mrt_dictionary_formatter();

    string start_stop, end_stop;
    cin >> start_stop >> end_stop;

    unordered_map<string, int> distance;
    for (auto stop : mrt_names)
        distance[stop] = INT_MAX;
    distance[start_stop] = 0;

    unordered_map<string, string> parent;
    parent[start_stop] =  "TERMINATE";

    unordered_map<string, bool> visited;

    auto compare_by_second = [](const pair<string, int>& left, const pair<string, int>& right) {
        return left.second > right.second;
    };

    priority_queue<pair<string,int>, vector<pair<string,int>>, decltype(compare_by_second)> mrt_stop_queue(compare_by_second);

    mrt_stop_queue.push(make_pair(start_stop, 0));

    while (!mrt_stop_queue.empty()) { //processing mrt_stop_queue.top() is a mistake
        pair<string, int> current_source = mrt_stop_queue.top();
        visited[mrt_stop_queue.top().first] = true;
        mrt_stop_queue.pop();
        
        for (pair<string, int> current_target : mrt_adjacency_list[current_source.first]) {
            if (visited[current_target.first]) {
                continue;
            }

            if (distance[current_source.first] + find_distance(current_source.first, current_target.first, mrt_adjacency_list) < distance[current_target.first]) {
                parent[current_target.first] = current_source.first;
                distance[current_target.first] = distance[current_source.first] + find_distance(current_source.first, current_target.first, mrt_adjacency_list);
            }

            mrt_stop_queue.push(make_pair(current_target.first, distance[current_target.first]));
        }
    }

    deque<string> stop_list;

    string process_stop = end_stop;

    while (parent[process_stop] != "TERMINATE") {
        stop_list.push_front(process_stop);
        process_stop = parent[process_stop];
    }

    stop_list.push_front(start_stop);

    for (auto iterat0r = stop_list.begin(); iterat0r != stop_list.end(); ++iterat0r) {
        cout << mrt_dictionary_formatter[*iterat0r] << (*iterat0r != end_stop?" -> ":"");
    }

    cout << '\n';

    cout << "Total trip time = " << distance[end_stop] << " minutes";
}


