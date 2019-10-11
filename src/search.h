#ifndef __SEARCH__HPP__
#define __SEARCH__HPP__ value

#include <functional>
#include <deque>
#include <vector>
#include <utility>

class labirinto;

/*
 *
 * Essa classe abstrata é para que as buscas herdem dela, dessa forma a gente padroniza as buscas para calcular o
 * tempo de execução.
 *
 * Pensei em uma classe bem genérica, por isso não tem nenhum atributo, na implementação do algoritmo você específica
 * como armazenar o labirinto, e o vetor do caminho percorrido.
 *
 * A função getSequeciaDeVisitados, eu pensei em fazer um vetor diferente do visitados para guardar a ordem das casas percorridas,
 * pq no caso da BFS a quantidade de
 * casas visitadas vai ser muito grande, então utilizar uma outra estrutura para armazenagem que torne a busca mais rápida, como
 * por exemplo uma outra matriz para marcar visitados, será mais eficiente, mas ai não da para saber o caminho percorrido.
 *
 *
 * também pensei na possibilidade de colocar uma flag de adiciona ou não o caminho para a interface, já que para o teste de tempo
 * isso não é necessário.
 *
 *
 */

class Search {
    public:
        Search(){};
        virtual ~Search(){};

        /*
         * função para armazenar o labirinto(na implementação da busca você decide onde vai salvar esse lab).
         */
        virtual void setMap(labirinto &map) = 0;

        /*
         * função para armazenar o caminho percorrido para ser usado na interface, você também decide como salvar na implementação
         */
        virtual const std::deque<std::pair<int,int>> &getSequenciaDeVisitados() const = 0;

        //Essa função que vai iniciar e terminar a busca, dessa forma fica facil posicionar o contador do tempo de
        //execução do algoritmo.
        //O retorno é o caminho para a solução.
        virtual std::vector<std::pair<int,int>> executar() = 0;

        // reinicia os valores da classe.
        virtual void reset() = 0;


};

#endif /* ifndef __SEARCH__HPP__ */
