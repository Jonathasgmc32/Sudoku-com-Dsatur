#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <cmath>
#include <chrono>
#include <utility>
#include "vertice.cpp"

using namespace std;
using namespace std::chrono;

void imprimir_tempo(long long tempo){
    cout << "Tempo de execução: " <<  tempo << " milissegundos" << endl;
}

void imprimir_em_tela(vector<vertice> grafo){
    int por_linha = floor(sqrt(grafo.size()));
    int impressos = 0;
    for(int i = 0; i< grafo.size(); i++){
        if(impressos < por_linha - 1){
            cout << grafo[i].get_cor() << "-";
            impressos++;
        }
        else{
            cout << grafo[i].get_cor() << endl;
            impressos = 0;
        }
    }
}

void salva_em_arquivo(int caso, vector<vertice> grafo, long long tempo){
    string nome_arquivo = "resultados/";
    if (caso < 31){
        nome_arquivo = nome_arquivo + "sudoku4x4_";
        if(caso < 11){
            nome_arquivo = nome_arquivo + "easy_" + to_string((caso - 1) % 10 + 1);
        }
        else if(caso < 21){
            nome_arquivo = nome_arquivo + "medium_" + to_string((caso - 1) % 10 + 1);
        } else{
            nome_arquivo = nome_arquivo + "difficult_" + to_string((caso - 1) % 10 + 1);
        }
    }
    else{
        nome_arquivo = nome_arquivo + "sudoku9x9_";
        if(caso < 41){
            nome_arquivo = nome_arquivo + "easy_" + to_string((caso - 1) % 10 + 1);
        }
        else if(caso < 51){
            nome_arquivo = nome_arquivo + "medium_" + to_string((caso - 1) % 10 + 1);
        } else{
            nome_arquivo = nome_arquivo + "difficult_" + to_string((caso - 1) % 10 + 1);
        }
    }
    nome_arquivo = nome_arquivo + "_resultado.txt";

    ofstream arquivo(nome_arquivo); 

    if (arquivo.is_open()) {
        int por_linha = floor(sqrt(grafo.size()));
        int impressos = 0;
        for(int i = 0; i< grafo.size(); i++){
            if(impressos < por_linha - 1){
                arquivo << grafo[i].get_cor() << "-";
                impressos++;
            }
            else{
                arquivo << grafo[i].get_cor() << endl;
                impressos = 0;
            }
        }
        arquivo << "Tempo de execução: " <<  tempo << " milissegundos" << endl;

        arquivo.close();
        cout << "Arquivo salvo com sucesso no seguinte caminho: " << nome_arquivo << endl;
    } else {
        cout << "Não foi possível abrir o arquivo." << endl;
    }
}
vector<int> ler_arquivo(int caso){
    string nome_arquivo = "casos_testes/";
    if (caso < 31){
        nome_arquivo = nome_arquivo + "sudoku4x4_";
        if(caso < 11){
            nome_arquivo = nome_arquivo + "easy_" + to_string((caso - 1) % 10 + 1);
        }
        else if(caso < 21){
            nome_arquivo = nome_arquivo + "medium_" + to_string((caso - 1) % 10 + 1);
        } else{
            nome_arquivo = nome_arquivo + "difficult_" + to_string((caso - 1) % 10 + 1);
        }
    }
    else{
        nome_arquivo = nome_arquivo + "sudoku9x9_";
        if(caso < 41){
            nome_arquivo = nome_arquivo + "easy_" + to_string((caso - 1) % 10 + 1);
        }
        else if(caso < 51){
            nome_arquivo = nome_arquivo + "medium_" + to_string((caso - 1) % 10 + 1);
        } else{
            nome_arquivo = nome_arquivo + "difficult_" + to_string((caso - 1) % 10 + 1);
        }
    }
    nome_arquivo = nome_arquivo + ".txt";
    ifstream arquivo(nome_arquivo);
    vector<int> numeros;
    string linha;
    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo.\n";
        return numeros;
    }

    while (getline(arquivo, linha)) {
        stringstream ss(linha);
        string numero_str;

        while (getline(ss, numero_str, '-')) {
            try {
                int numero = stoi(numero_str);
                numeros.push_back(numero);
            } catch (invalid_argument& e) {
                cerr << "Valor inválido encontrado: " << numero_str << '\n';
            }
        }
    }
    arquivo.close();
    return numeros;
}

vector<vertice> criar_grafo_sudoku(vector<int> valores_vertices, int tamanho_linha){
    vector<vertice> grafo;
    int qtd_vertice = tamanho_linha * tamanho_linha;
    int tam_bloco = floor(sqrt(tamanho_linha));
    for (int i = 0; i < qtd_vertice; i++) {
    vertice v;
    v.set_id(i);
    v.set_cor(valores_vertices[i]);
    int linha_i = i / tamanho_linha;
    int coluna_i = i % tamanho_linha;
    int bloco_i = (linha_i /tam_bloco) * tam_bloco + (coluna_i /tam_bloco);

    for (int j = 0 ; j < qtd_vertice; j++) {
        int linha_j = j / tamanho_linha;
        int coluna_j = j % tamanho_linha;
        int bloco_j = (linha_j /tam_bloco) * tam_bloco + (coluna_j /tam_bloco);

        if ((i != j) && (linha_i == linha_j || coluna_i == coluna_j || bloco_i == bloco_j)) {
            v.add_adjacente(j);
        }
    }
    grafo.push_back(v);
    }
    return grafo;
}

int get_indice_to_remove(vector<int> lista, int indice){
    for (int i = 0; i < lista.size(); i++)
    {
        if(lista[i] == indice){
            return i;
        }
    }
    return -1;
}


vector<int> obter_cores_adjacentes(vector<vertice> grafo, int indice){
    vector<int> cores_adjacentes;
    vector<int> adjacentes = grafo[indice].get_vertices_adjacentes();
    for(int i = 0; i < adjacentes.size(); i++){
        if(grafo[adjacentes[i]].get_cor() !=0 && count(cores_adjacentes.begin(), cores_adjacentes.end(), grafo[adjacentes[i]].get_cor()) == 0){
            cores_adjacentes.push_back(grafo[adjacentes[i]].get_cor());
        }
    }
    return cores_adjacentes;
}


int menor_cor(vector<vertice> grafo, int indice){
    vector<int> cores_adjacentes;
    cores_adjacentes = obter_cores_adjacentes(grafo, indice);
    int  menor_cor = 1;
    for(int i = 0; i < cores_adjacentes.size(); i++){
        if(count(cores_adjacentes.begin(), cores_adjacentes.end(), menor_cor) == 0){
            return menor_cor;
        }
        else{
            menor_cor++;
        }
    }
    return menor_cor;
}

pair<vector<vertice>, long long> dsatur(int caso){
    vector<vertice> grafo;
    vector<int> cores_atuais;
    cores_atuais = ler_arquivo(caso);
    grafo = criar_grafo_sudoku(cores_atuais, floor(sqrt(cores_atuais.size())));
    cout<< "Aqui está o caso de teste " << caso << endl;
    imprimir_em_tela(grafo);
    auto inicio = high_resolution_clock::now();
    vector<int> vertices_nao_coloridos;
    vector<int> vertices_coloridos;
    int indice_maior_grau = -1;
    for (int i = 0; i < grafo.size(); i++){
        if(grafo[i].get_cor() == 0){
            vertices_nao_coloridos.push_back(grafo[i].get_id_vertice());
        }
        else{
            vertices_coloridos.push_back(grafo[i].get_id_vertice());
        }
    }
    for(int i = 0; i < vertices_nao_coloridos.size(); i++){
            if (indice_maior_grau == -1){
                indice_maior_grau = vertices_nao_coloridos[i];
            }
            else if(obter_cores_adjacentes(grafo, i).size() > obter_cores_adjacentes(grafo, indice_maior_grau).size()){
                indice_maior_grau = vertices_nao_coloridos[i];
            }
            else if(obter_cores_adjacentes(grafo, i).size() > obter_cores_adjacentes(grafo, indice_maior_grau).size()){
                if(grafo[vertices_nao_coloridos[i]].get_grau_conjunto(vertices_nao_coloridos) > grafo[indice_maior_grau].get_grau_conjunto(vertices_nao_coloridos)){
                    indice_maior_grau = vertices_nao_coloridos[i];
                }
            }
    }
    grafo[indice_maior_grau].set_cor(menor_cor(grafo, indice_maior_grau));
    vertices_coloridos.push_back(indice_maior_grau);
    vertices_nao_coloridos.erase(vertices_nao_coloridos.begin() + get_indice_to_remove(vertices_nao_coloridos, indice_maior_grau));
    
    while(vertices_nao_coloridos.size() != 0){
        for (int i = 0; i < grafo[indice_maior_grau].get_vertices_adjacentes().size(); i++)
        {
            if(count(vertices_nao_coloridos.begin(), vertices_nao_coloridos.end(), 
            grafo[indice_maior_grau].get_vertices_adjacentes().at(i)) > 0){
                int sat = obter_cores_adjacentes(grafo, grafo[indice_maior_grau].get_vertices_adjacentes().at(i)).size();
                grafo[grafo[indice_maior_grau].get_vertices_adjacentes().at(i)].set_grau_sat(sat);
            }
        }
        int prox_vertice = 0;
        for(int i = 0; i < vertices_nao_coloridos.size(); i++){
            if (prox_vertice == 0){
                prox_vertice = vertices_nao_coloridos[i];
            }
            else if(grafo[vertices_nao_coloridos[i]].get_grau_sat() > grafo[prox_vertice].get_grau_sat()){
                prox_vertice = vertices_nao_coloridos[i];
            }
            else if(grafo[vertices_nao_coloridos[i]].get_grau_sat() == grafo[prox_vertice].get_grau_sat()){
                if(grafo[vertices_nao_coloridos[i]].get_grau_conjunto(vertices_nao_coloridos) > grafo[prox_vertice].get_grau_conjunto(vertices_nao_coloridos)){
                    prox_vertice = vertices_nao_coloridos[i];
                }
            }
        }
        grafo[prox_vertice].set_cor(menor_cor(grafo, prox_vertice));
        vertices_coloridos.push_back(prox_vertice);
        vertices_nao_coloridos.erase(vertices_nao_coloridos.begin() + get_indice_to_remove(vertices_nao_coloridos, prox_vertice));
        indice_maior_grau = prox_vertice;
    }
    auto fim = high_resolution_clock::now();
    long long duracao = duration_cast<milliseconds>(fim - inicio).count();
    pair<vector<vertice>, long long> resultado = {grafo, duracao};
    return resultado;
}


int main(){
    int opcaoMenu;
    while (true) {
        cout << "Boas vindas a implementação de DSatur para jogos de Sudoku" << endl;
        cout << "Escolha uma opção: " << endl;
        cout << "1 - Selecionar caso teste" << endl;
        cout << "2 - Sair" << endl;
        cin >> opcaoMenu;

        if (opcaoMenu == 1) {
            int numeroCaso;
            cout << "Os casos testes estão separados nas categorias 4x4 e 9x9, onde: " << endl;
            cout << "4x4 fácil: casos de 1 a 10" << endl;
            cout << "4x4 médio: casos de 11 a 20" << endl;
            cout << "4x4 díficil: casos de 21 a 30" << endl;
            cout << "9x9 fácil: casos de 31 a 40" << endl;
            cout << "9x9 médio: casos de 41 a 50" << endl;
            cout << "9x9 díficil: casos de 51 a 60" << endl;
            cout << "Selecione um caso de 1 a 60:" << endl;
            cin >> numeroCaso;

            if (numeroCaso < 1 || numeroCaso > 60) {
                cout << "O caso selecionado é invalido! Retornando ao menu." << endl;
                continue;
            }
            pair<vector<vertice>, long long> resultado = dsatur(numeroCaso);
            int opcaoSaida;
            cout << "Deseja que o resultado seja:" << endl;;
            cout << "1 - Impresso na tela" << endl;
            cout << "2 - Salvo em arquivo .txt" << endl;
            cin >> opcaoSaida;

            if (opcaoSaida == 1) {
                imprimir_em_tela(resultado.first);
                imprimir_tempo(resultado.second);
            } else if (opcaoSaida == 2) {
                salva_em_arquivo(numeroCaso, resultado.first, resultado.second);
            } else {
                cout << "Opcao invalida!" << endl;
            }

        } else if (opcaoMenu == 2) {
            cout << "Obrigado por participar. Encerrando o programa." << endl;
            break;
        } else {
            cout << "Opcao invalida!" << endl;
        }
    }

    return 0;
}
