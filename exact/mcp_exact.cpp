#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <chrono>
#include <fstream>
#include <thread>

using namespace std;
using namespace std::chrono;
using namespace std::this_thread;

int l_b;
vector<int> clique, temp_clique;

int lower_bound(vector<int> adj_list[], int vertices){
    set<int> rest;
    set<int> sub;

    for (int i = 0; i < vertices; i++){
        rest.insert(i);
    }

    int biggest_vertice, biggest_degree; 

    while(rest.size() > 0){

        int cont = 0;

        // finding the current biggest degree vertex in rest
        for (auto i : rest){
            if(cont == 0){
                biggest_vertice = i;
                biggest_degree = adj_list[i].size();
                cont += 1;
            }
            else {
                if (adj_list[i].size() > biggest_degree){
                    biggest_vertice = i;
                    biggest_degree = adj_list[i].size();
                }
            }
        }

        sub.insert(biggest_vertice);

        set<int> rest_copy;

        for (auto i : rest){
            rest_copy.insert(i);
        }

        rest.erase(rest.begin(),rest.end());

        for (auto i : adj_list[biggest_vertice]){
            // if an adjacent vertex to the current biggest_vertice is in rest but not in sub, then it will remain in rest
            if (rest_copy.find(i) != rest_copy.end() && sub.find(i) == sub.end()){
                rest.insert(i);
            }
        }
    }

    for (auto i : sub){
        clique.push_back(i);
    }
    return sub.size();
}

bool clique_checker(vector<int> adj_list[], int vertices){
    bool result = true;
    for (int i = 0; i < vertices; i++){
        if (adj_list[i].size() != vertices - 1) result = false;
    }
    return result;
}

void branching(vector<int> adj_list[], vector<int> ordered_vertices, int size){
    // check if it is a leave
    if(ordered_vertices.size() == 0){
        if(size > l_b){
            clique.clear();
            for (auto i : temp_clique) clique.push_back(i);
            l_b = size;
        }
        return;
    }


    while(ordered_vertices.size() > 0){
        // prunning
        if (size + ordered_vertices.size() <= l_b){
            temp_clique.clear();
            return;
        }
        int min = ordered_vertices[0];
        temp_clique.push_back(min);

        vector<int> neighbours;
        for(int i = 1; i < ordered_vertices.size(); i++){
            for (auto j : adj_list[min]){
                if (j == ordered_vertices[i]){
                    neighbours.push_back(j);
                }
            }
        }
        vector<int> new_ordered_vertices;        
        for(int i = 1; i < ordered_vertices.size(); i++){
            new_ordered_vertices.push_back(ordered_vertices[i]);
        }

        ordered_vertices.clear();

        for(int i = 0; i < new_ordered_vertices.size(); i++){
            ordered_vertices.push_back(new_ordered_vertices[i]);
        }

        branching(adj_list, neighbours, size + 1);
    }

    return;
}

int main(int argc, char* argv[]){

    auto start = high_resolution_clock::now();
    string header;
    getline(cin, header);

    int vertices = 0, edges, u, v;
    cin >> vertices >> vertices >> edges;
    vector<int> adj_list[vertices];

    // reading the instance and save it into a adjacency list
    while(edges--){
        cin >> u >> v;

        adj_list[u - 1].push_back(v - 1);
        adj_list[v - 1].push_back(u - 1);
    }

    l_b = lower_bound(adj_list, vertices);

    vector<int> clique_ordered_vertex;
    set<int> temp_ordered_vertex_set;
    int min_degree, min_vertex, current_degree;

    for(int i = 0; i < vertices; i++){
        min_degree = numeric_limits<int>::max();;
        min_vertex = -1;
        for (int j = 0; j < vertices; j++){
            if (temp_ordered_vertex_set.find(j) == temp_ordered_vertex_set.end()){
                current_degree = 0;
                for (auto k : adj_list[j]) {
                    if (temp_ordered_vertex_set.find(k) == temp_ordered_vertex_set.end()) current_degree++;
                }
                if (current_degree < min_degree) {
                    min_degree = current_degree;
                    min_vertex = j;
                }
            }
        }
        clique_ordered_vertex.push_back(min_vertex);
        temp_ordered_vertex_set.insert(min_vertex);
    }

    branching(adj_list, clique_ordered_vertex, 0);

    cout << "Tamanho do clique máximo: " << l_b << "\n";
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
