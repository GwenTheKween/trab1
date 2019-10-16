#ifndef LABIRINTO_H
#define LABIRINTO_H

#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "parede.h"

enum MAP_INFO{
	FREE_SPACE,
	WALL,
	BEGIN,
	END,
	ERROR
};

class labirinto{
	int height, width;
	std::pair<int, int> begin, end;
	std::vector<std::vector<MAP_INFO> > map;
private:
	//Metodo que muda o tamanho do mapa, usando resize nos vectors.
	//Foi feito para ser usado apenas na inicializacao da classe
	void resize(int h,int w);


	/*Funcao que verifica quantas paredes existe a partir de uma posicao*/
	int check_num_wall(int column, int line);

	bool check_start_end(int column, int line);

	//adiciona a parede gerada pelo algoritmo nova_geracao, e retorna ela para o algoritmo
	parede create_wall(std::pair<int, int> start, std::pair<int, int> end);

	//Seta o inicio do mapa como a coordenada passada, e armazena essa coordenada
	void setStart(std::pair<int, int> coord);

	//Seta o fim do mapa como a coordenada passada, e armazena essa coordenada
	void setEnd(std::pair<int,int> coord);
public:

	//Construtor da classe, chama o metodo de resize e prepara para gerar aleatoriamente ou pelo usuario
	labirinto(int h, int w);
	//Construtor da classe, chama resize e depois le do arquivo passado
	labirinto(const char* filename);
	//Destrutor da classe, zera os valores que nao tem o proprio destrutor
	~labirinto(){
		height = 0;
		width = 0;
	}

	/*Funcao que escreve o labirinto criado em um arquivo */
	void write_labirinto(const char* filename);

	//operador para poder ler o mapa fora da classe, mas nao pode editar
	std::vector<MAP_INFO> operator [](int i){
		return map[i];
	}

	//operador para poder ler o mapa sem edita-lo, usando pairs para facilitar a passagem de coordenadas
	int operator [](std::pair<int, int> p){
		return map[p.first][p.second];
	}

	void gera_labirinto_manual(char* filename);
	void gera_labirinto_automatico(char* filename);

	//Geracao aleatoria do mapa, recebe a quantidade de paredes a ser criada.
	//O algoritmo escolhe alguma parede existente, e em algum ponto dessa parede cria uma outra parede, ortogonal a original
	void nova_geracao(int wallCount);

    int getHeight();
    int getWidth();
	//Retorna se a coordenada passada esta livre
	bool isFree(std::pair<int,int> coord);
	//Checa se existem paredes ao redor do ponto passado
	bool wallsAround(std::pair<int,int> coord);

	//Retorna a coordenada de inicio
	std::pair<int, int> getStart(){return begin;}

	//Retorna a coordenada de fim
	std::pair<int, int> getEnd() {return end;}

	void print();
};

#endif
