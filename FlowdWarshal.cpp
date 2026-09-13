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

    void FloydWarshal(string awal, string akhir){
        unordered_map<string, unordered_map<string, long long>> jarak;
        unordered_map<string, unordered_map<string, string>> nextNode;
        vector<string> nodes;
        
        for (auto const& node : adjList){
            nodes.push_back(node.first);
        }

        for (auto const& a : nodes){
            for (const string& b : nodes){
                jarak[a][b] = LL_MAX;
            }
            jarak[a][a] = 0;
        }
        for (auto const& node : adjList){\
            string a = node.first;
            for(auto const& edge : node.second){
                string a = node.first;
                for (auto const& edge : node.second){
                    string b = edge.first;
                    long long w = edge.second;
                    jarak[a][b] = w;
                    nextNode[a][b] = b;
                }
            }
        }
        for (const string& k : nodes){
            for (const string& i : nodes){
                for (const string& j : nodes){
                    if (jarak[i][k] != LL_MAX && jarak[k][j] != LL_MAX){
                        if (jarak[i][k] + jarak[k][j] < jarak[i][j]){
                            jarak[i][j] = jarak[i][k] + jarak[k][j];
                            nextNode[i][j] = nextNode[i][k];
                        }
                    }
                }
            }
        }

        for (const string& i : nodes) {
            if (jarak[i][i] < 0) {
                cout << "Siklus berbobot negatif.\n";
                return;
            }
        }
        if (jarak[awal][akhir] == LL_MAX){
            cout << "Tidak ada jalur dari " << awal << " ke " << akhir << ".\n";
            return;
        }
        cout << "Urutan node yang harus dilalui (Floyd-Warshall):\n\n";
        
        string now = awal;
        cout << now;
        while (now != akhir){
            now = nextNode[now][akhir];
            cout << " --> " << now;
        }
        cout << "\n\nTotal jaraknya: " << jarak[awal][akhir] << endl;
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

    g.FloydWarshal("v1", "v11");
}