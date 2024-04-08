/*
  This code is a heavily modified version of the hotspots assignment
*/


#include <iostream>
#include <string>

#include "/scratch/parlaylib/include/parlay/primitives.h"
#include "/scratch/parlaylib/include/parlay/sequence.h"
#include "/scratch/parlaylib/include/parlay/internal/get_time.h"

#include "MIS.h"
#include "/scratch/parlaylib/examples/helper/graph_utils.h"


/*
    MAXIMUM DEGREE
    I will figure out how to make this dynamic later
*/

const int max_degree = 100;

// **************************************************************
// Driver
// **************************************************************
using vertex = int;
using nested_seq = parlay::sequence<parlay::sequence<vertex>>;
using graph = nested_seq;
using utils = graph_utils<vertex>;

int main(int argc, char* argv[]) {
    auto usage = "Usage: BFS <n>";
   
    if (argc != 2) {std::cout << usage << std::endl;
        return -1;
    }

    int n = 0;
    graph G;
    try { n = std::stoi(argv[1]); }
    catch (...) {}
    if (n == 0) {
        std::cout << "n should be an integer greater than 1" << std::endl;
        return -1;
    }
    std::cout << "using graph with vertices = " << n << std::endl;
    G = utils::rmat_graph(n, 2000*n);
    
    for(uint i = 0; i < G.size(); i++)
    {
        std::cout << G[i].size() << " ";
    }
    std::cout << std::endl;
    
    remove_higher_degree(G, max_degree);

    for(uint i = 0; i < G.size(); i++)
    {
        std::cout << G[i].size() << " ";
    }
    std::cout << std::endl;


    return 0;
}