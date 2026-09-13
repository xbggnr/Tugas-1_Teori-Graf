#include <bits/stdc++.h>
using namespace std;
const long long LL_MAX = 1e18;

struct graph{
    long long edgeCount = 0;
    unordered_map<string, vector<pair<string, long long>>> adjList;

    void add_edge(string v1, string v2, long long w){
        adjList[v1].push_back(make_pair(v2, w));
        adjList[v2].push_back(make_pair(v1, w));
        edgeCount++;
    }

    void bellmanFord(string awal, string akhir){
        unordered_map<string, long long> jarak;
        unordered_map<string, string> urutan;
        jarak[awal] = 0;
        int V = adjList.size();
        for (auto const& node : adjList){
            jarak[node.first] = LL_MAX;
            urutan[node.first] = "";
        }
        jarak[awal] = 0;
        for (int i = 0; i < V-1; i++){
            for(auto const& node : adjList){
                string a = node.first;
                for (auto const& edge : node.second){
                    string b = edge.first;
                    long long w = edge.second;
                    if (jarak[a] != LL_MAX && jarak[a] + w < jarak[b]){
                        jarak[b] = jarak[a] + w;
                        urutan[b] = a;
                    }
                }
            }
        }
        for (auto const& node : adjList){
            string a = node.first;
            for (auto const& edge : node.second){
                string b = edge.first;
                long long w = edge.second;
                if (jarak[a] != LL_MAX && jarak[a] + w < jarak[b]){
                    cout << "Siklus berbobot negatif.\n";
                    return;
                }
                if (jarak[akhir] == LL_MAX){
                    cout << "Tidak ada jalur.\n";
                    return;
                }
            }
        }
        vector<string> jalur;
        string now = akhir;
        while (now != ""){
            jalur.push_back(now);
            now = urutan[now];
        }
        cout << "Urutan node yang harus dilalui:\n\n";
        reverse(jalur.begin(), jalur.end());
        for (int i = 0; i < jalur.size(); i++){
            cout << jalur[i];
            if (i != jalur.size() - 1) cout << " --> ";
        }
        cout << endl;
        cout << "\n\nTotal jaraknya: " << jarak[akhir] << endl;
    }
};


int main(void){
    graph g;
    g.add_edge("v1", "v2", 2);
    g.add_edge("v1", "v3", 8);
    g.add_edge("v1", "v4", 1);
    g.add_edge("v2", "v3", 6);
    g.add_edge("v2", "v5", 1);
    g.add_edge("v3", "v4", 7);
    g.add_edge("v3", "v5", 5);
    g.add_edge("v3", "v6", 1);
    g.add_edge("v3", "v7", 2);
    g.add_edge("v4", "v7", 9);
    g.add_edge("v5", "v6", 3);
    g.add_edge("v5", "v8", 2);
    g.add_edge("v5", "v9", 9);
    g.add_edge("v6", "v7", 4);
    g.add_edge("v6", "v9", 6);
    g.add_edge("v7", "v9", 3);
    g.add_edge("v7", "v10", 1);
    g.add_edge("v8", "v9", 7);
    g.add_edge("v8", "v11", 9);
    g.add_edge("v9", "v10", 1);
    g.add_edge("v9", "v11", 2);
    g.add_edge("v10", "v11", 4);

    g.bellmanFord("v1", "v11");
}