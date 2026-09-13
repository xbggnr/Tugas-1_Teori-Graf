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

    void Astar(string awal, string akhir, unordered_map<string, long long>& heuristik){
        unordered_map<string, long long> gscore;
        unordered_map<string, string> urutan;

        for (auto const& node : adjList){
            gscore[node.first] = LL_MAX;
            urutan[node.first] = "";
        }

        priority_queue<pair<long long, string>, vector<pair<long long, string>>, greater<pair<long long, string>>> pq;
        gscore[awal] = 0;
        pq.push({0 + heuristik[awal], awal});

        while (!pq.empty()){
            string now = pq.top().second;
            pq.pop();
            if (now == akhir){
                vector<string> jalur;
                string temp = akhir;
                while (temp != ""){
                    jalur.push_back(temp);
                    temp = urutan[temp];
                }
                reverse(jalur.begin(), jalur.end());
                cout << "Urutan node yang harus dilalui:\n\n";
                for (int i = 0; i < jalur.size(); i++){
                    cout << jalur[i] << (i != jalur.size() - 1 ? " --> " : "");
                }
                cout << endl;
                cout << "\nJaraknya: " << gscore[akhir] << endl;
                return;
            }

            for (auto edge : adjList[now]) {
                string tetangga = edge.first;
                long long bobot = edge.second;

                long long tentativeg = gscore[now] + bobot;

                if (tentativeg < gscore[tetangga]) {
                    urutan[tetangga] = now;
                    gscore[tetangga] = tentativeg;
                    long long f_score = tentativeg + heuristik[tetangga];
                    pq.push({f_score, tetangga});
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

    unordered_map<string, long long> heuristik = {
        {"v1", 10}, {"v2", 9}, {"v3", 6}, {"v4", 8},
        {"v5", 6}, {"v6", 5}, {"v7", 4}, {"v8", 3},
        {"v9", 2}, {"v10", 2}, {"v11", 0} 
    };

    g.Astar("v1", "v11", heuristik);
}