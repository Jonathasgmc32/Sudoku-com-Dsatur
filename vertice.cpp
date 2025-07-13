#include <iostream>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

class vertice{
    private:
        int id_vertice;
        int cor_preencher;
        vector<int> vertices_adjacentes;
        int grau_sat;
    public:
        int get_adjacente(int position){
            return vertices_adjacentes[position];
        }
        vector<int> get_vertices_adjacentes(){
            return vertices_adjacentes;
        }
        void set_grau_sat(int grau_sat){
            this->grau_sat = grau_sat;
        }
        int get_cor(){
            return this-> cor_preencher;
        }
        int get_id_vertice(){
            return this-> id_vertice;
        }
        int get_grau_sat(){
            return this->grau_sat;
        }
        void set_cor(int nova_cor){
            this->cor_preencher = nova_cor;
        }
        void set_sat(int novo_sat){
            this->grau_sat = novo_sat;
        }
        int get_grau_conjunto(vector<int> conjunto){
            int grau = 0;
            for (int i = 0; i < conjunto.size(); i++)
            {
                if(count(vertices_adjacentes.begin(), vertices_adjacentes.end(), conjunto[i]) > 0){
                    grau++;
                }
            }
            return grau;
        }
        void set_id(int new_id){
            this->id_vertice = new_id;
        }
        void add_adjacente(int adjacente){
            if(count(vertices_adjacentes.begin(), vertices_adjacentes.end(), adjacente) == 0){
                vertices_adjacentes.push_back(adjacente);
            }
        }
};