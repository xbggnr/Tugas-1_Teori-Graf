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

    void johnson(string awal, string akhir){
        vector<string> nodes;
        for (auto const& pair : adjList) {
            nodes.push_back(pair.first);
        }

        string dummy = "__dummy__";
        unordered_map<string, long long> h;
        for (const string& u : nodes) h[u] = LL_MAX;
        h[dummy] = 0;

        vector<pair<pair<string, string>, long long>> all_edges;
        for (const string& u : nodes) {
            for (auto const& edge : adjList[u]) {
                all_edges.push_back({{u, edge.first}, edge.second});
            }
            all_edges.push_back({{dummy, u}, 0});
        }

        int V_total = nodes.size() + 1;
        for (int i = 0; i < V_total - 1; i++) {
            for (auto const& e : all_edges) {
                string u = e.first.first;
                string v = e.first.second;
                long long w = e.second;
                if (h[u] != LL_MAX && h[u] + w < h[v]) {
                    h[v] = h[u] + w;
                }
            }
        }

        for (auto const& e : all_edges) {
            string u = e.first.first;
            string v = e.first.second;
            long long w = e.second;
            if (h[u] != LL_MAX && h[u] + w < h[v]) {
                cout << "Siklus berbobot negatif.\n";
                return;
            }
        }

        unordered_map<string, vector<pair<string, long long>>> adj_reweighted;
        for (const string& u : nodes) {
            for (auto const& edge : adjList[u]) {
                adj_reweighted[u].push_back({edge.first, edge.second + h[u] - h[edge.first]});
            }
        }

        unordered_map<string, unordered_map<string, long long>> resultMatrix;
        unordered_map<string, string> urutan_awal;

        for (const string& s : nodes) {
            unordered_map<string, long long> d_prime;
            unordered_map<string, string> urutan;
            for (const string& n : nodes) {
                d_prime[n] = LL_MAX;
                urutan[n] = "";
            }
            
            priority_queue<pair<long long, string>, vector<pair<long long, string>>, greater<pair<long long, string>>> pq;
            d_prime[s] = 0;
            pq.push({0, s});

            while (!pq.empty()) {
                long long d_curr = pq.top().first;
                string u = pq.top().second;
                pq.pop();

                if (d_curr > d_prime[u]) continue;

                for (auto const& edge : adj_reweighted[u]) {
                    string v = edge.first;
                    long long w = edge.second;
                    if (d_prime[u] + w < d_prime[v]) {
                        d_prime[v] = d_prime[u] + w;
                        urutan[v] = u;
                        pq.push({d_prime[v], v});
                    }
                }
            }

            for (const string& v : nodes) {
                if (d_prime[v] == LL_MAX) {
                    resultMatrix[s][v] = LL_MAX;
                } else {
                    resultMatrix[s][v] = d_prime[v] - h[s] + h[v];
                }
            }
            if (s == awal) urutan_awal = urutan;
        }

        if (resultMatrix[awal].find(akhir) == resultMatrix[awal].end() || resultMatrix[awal][akhir] == LL_MAX) {
            cout << "Tidak ada jalur.\n";
            return;
        }

        vector<string> jalur;
        string now = akhir;
        while (now != "") {
            jalur.push_back(now);
            now = urutan_awal[now];
        }
        cout << "Urutan node yang harus dilalui:\n\n";
        reverse(jalur.begin(), jalur.end());
        for (int i = 0; i < jalur.size(); i++) {
            cout << jalur[i];
            if (i != jalur.size() - 1) cout << " --> ";
        }
        cout << endl;
        cout << "\nTotal jaraknya: " << resultMatrix[awal][akhir] << endl;
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

    g.johnson("v1", "v11");
}