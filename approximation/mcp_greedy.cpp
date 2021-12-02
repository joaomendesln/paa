#include <iostream>
#include <vector>
#include <set>
#include <string>

using namespace std;

int main(){
    string header;
    getline(cin, header);

    int vertices = 0, edges, u, v;
    cin >> vertices >> vertices >> edges;
    vector<int> adj_list[vertices];

    while(edges--){
        cin >> u >> v;

        adj_list[u - 1].push_back(v - 1);
        adj_list[v - 1].push_back(u - 1);
    }

    set<int> rest;
    set<int> sub;

    for (int i = 0; i < vertices; i++){
        rest.insert(i);
    }

    int biggest_vertice, biggest_degree; 

    while(rest.size() > 0){

        int cont = 0;
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

        for(auto i : rest){
            rest_copy.insert(i);
        }

        rest.erase(rest.begin(),rest.end());

        for (auto i : adj_list[biggest_vertice]){
            if (rest_copy.find(i) != rest_copy.end() && sub.find(i) == sub.end()){
                rest.insert(i);
            }
        }
    }

    // cout << "sub - ";
    // for (auto i : sub){
    //     cout << i << " ";
    // }
    cout << sub.size() << "\n";
    
}