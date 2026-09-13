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

    void dijkstra(string awal, string akhir){
        unordered_map<string, long long> jarak;
        unordered_map<string, string> urutan;

        for (auto const& node: adjList){
            jarak[node.first] = LL_MAX;
            urutan[node.first] = "";
        }

        priority_queue<pair<long long, string>, vector<pair<long long, string>>, greater<pair<long long, string>>> pq;
        jarak[awal] = 0;
        pq.push({0, awal});

        while (!pq.empty()){
            long long jarak_sekarang = pq.top().first;
            string node_sekarang = pq.top().second;
            pq.pop();

            if (jarak_sekarang > jarak[node_sekarang]) continue;
            if (node_sekarang == akhir){
                vector<string> jalur;
                string now = akhir;
                while(now != ""){
                    jalur.push_back(now);
                    now = urutan[now];
                }
                reverse(jalur.begin(), jalur.end());
                cout << "Urutan node yang harus dilalui:\n\n";
                for (int i = 0; i < jalur.size(); i++){
                    cout << jalur[i];
                    if (i != jalur.size() - 1) cout << " --> ";
                }
                cout << "\n\nJarak totalnya: " << jarak[akhir] << endl;
                return;
            }

            for (auto edge : adjList[node_sekarang]){
                string n = edge.first;
                long long w = edge.second;

                if (jarak[node_sekarang] + w < jarak[n]){
                    jarak[n] = jarak[node_sekarang] + w;
                    urutan[n] = node_sekarang;
                    pq.push({jarak[n], n});
                }
            }
        }
        cout << "Tidak ada jalan" << endl;
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

    g.dijkstra("v1", "v11");
}