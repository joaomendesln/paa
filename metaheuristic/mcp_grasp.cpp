#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <chrono>
#include <fstream>
#include <thread>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;
using namespace std::chrono;
using namespace std::this_thread;

int l_b;
vector<int> clique, temp_clique;
int vertices, edges;

bool clique_checker(vector<int> adj_list[], int vertices){
    bool result = true;
    for (int i = 0; i < vertices; i++){
        if (adj_list[i].size() != vertices - 1) result = false;
    }
    return result;
}

vector<int> sort_adjcent_v(vector<int> adj_list[], int v){

    // cout << v << "\n";
    vector<int> sorted;
    vector<bool> already_sorted;
    for (int i = 0; i < vertices + 10; i++){
        // cout << i << " ";
        already_sorted.push_back(false);
    }
    // cout << "\n";

    // for (auto i : adj_list[v]) cout << i << " ";
    // cout << "\n";

    int max_degree, max_vertex;
    for (int i = 0; i < adj_list[v].size(); i++){
        // cout << "b\n";

        // cout << i << " - " << max_degree << " - " << max_vertex << "\n";
        max_degree = -1, max_vertex = -1;
        for (int j = 0; j < adj_list[v].size(); j++){
            // cout << "(" << adj_list[v][j] << " - " << adj_list[adj_list[v][j]].size() << ")";
            if(!already_sorted[adj_list[v][j]] && static_cast<int>(adj_list[adj_list[v][j]].size()) > max_degree){
                max_degree = adj_list[adj_list[v][j]].size();
                max_vertex = adj_list[v][j];
            }
        }
        // cout << "\n";
        already_sorted[max_vertex] = true;
        // cout << "blablah\n";
        sorted.push_back(max_vertex);
    }

    return sorted;
}

void grasp(vector<int> adj_list[], vector<int> sorted_vertex, int it, int perc){

    // perc% vertex vector with max degree
    vector<int> perc_sorted;
    // cout << sorted_vertex.size() << "\n";
    for(int i = 0; i < perc * sorted_vertex.size() / 100; i++){
        perc_sorted.push_back(sorted_vertex[i]);
    }

    int cont = 0;
    for (int i = 0; i < it; i++){

        temp_clique.clear();
        // srand(time(NULL));
        // cout << rand() << " - " << perc_sorted.size() << "\n";
        int rand_v = perc_sorted[rand() % perc_sorted.size()];

        vector<int> sorted_rand_v = sort_adjcent_v(adj_list, rand_v);

        // cout << rand_v + 1 << "\n";
        // for (auto i : sorted_rand_v) cout << i + 1 << " ";
        // cout << "\n";
        
        int a = 0;

        while (a < sorted_rand_v.size()){
            temp_clique.clear();
            temp_clique.push_back(rand_v);
            for (int j = 0; j < sorted_rand_v.size(); j++){
                int idx = (j + a) % sorted_rand_v.size();
                // cout << idx << "\n";
                // verify if it forms a clique
                bool is_clique = true;
                int k = 0;
                while(is_clique && k < temp_clique.size()){
                    // cout << "temp_clique: ";
                    // for (auto x : temp_clique) cout << x + 1 << " ";
                    // cout << "\n";
                    is_clique = false;
                    for (int l = 0; l < adj_list[temp_clique[k]].size(); l++){
                        // cout << sorted_rand_v[idx] + 1 << " - " << adj_list[temp_clique[k]][l] + 1 << "\n";
                        if (sorted_rand_v[idx] == adj_list[temp_clique[k]][l]){
                            is_clique = true;
                        }
                    }
                    k++;
                }

                // cout << "is clique: " << is_clique << "\n";

                // if it forms a clique, add it to temporary solution
                if(is_clique){
                    temp_clique.push_back(sorted_rand_v[idx]);
                }

                // verify if the temporary solution is the best solution
                if(temp_clique.size() > clique.size()){
                    clique.clear();
                    for (auto k : temp_clique) clique.push_back(k);
                }
            }
            a += 1;
        }

    }
    
    return;

}

int main(int argc, char* argv[]){

    auto start = high_resolution_clock::now();
    string header;
    getline(cin, header);

    int u, v;
    vertices = 0;
    cin >> vertices >> vertices >> edges;
    vector<int> adj_list[vertices];

    // reading the instance and save it into a adjacency list
    while(edges--){
        cin >> u >> v;

        adj_list[u - 1].push_back(v - 1);
        adj_list[v - 1].push_back(u - 1);
    }
    // sort array by vertex degree
    vector<int> sorted_vertex;
    vector<bool> already_sorted;

    for (int i = 0; i < vertices; i++){
        already_sorted.push_back(false);
    }
    int max_degree, max_vertex;


    
    for(int i = 0; i < vertices; i++){
        max_degree = -1;
        max_vertex = -1;
        for (int j = 0; j < vertices; j++){
            // cout << already_sorted[j] << " " << (static_cast<int>(adj_list[j].size()) > max_degree) << "\n";
            if(!already_sorted[j] && static_cast<int>(adj_list[j].size()) > max_degree){
                // cout << "a\n";
                max_degree = adj_list[j].size();
                max_vertex = j;
            }
        }
        // cout << max_vertex << "\n";
        already_sorted[max_vertex] = true;
        sorted_vertex.push_back(max_vertex);
    }

    // cout << vertices << "\n";

    // for (auto i : sorted_vertex) cout << i + 1 << " ";
    // cout << "\n";

    int it, perc;
    cin >> it;
    cin >> perc;

    srand((unsigned) time(0));

    grasp(adj_list, sorted_vertex, it, perc);

    cout << "Tamanho do clique máximo: " << clique.size() << "\n";
    cout << "Vértices do clique máximo: ";
    for (int i = 0; i < clique.size(); i++) {
        if (i != 0) cout << ", ";
        cout << clique[i] + 1; 
    }
    cout << "\n";
    
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
  
    cout << "Tempo de duração da execução: "
         << duration.count() << " microsegundos" << endl;

}