/*
  This code generates a tree and then creates an RC tree out of this tree.
*/


#include <iostream>
#include <string>
#include "/scratch/parlaylib/include/parlay/primitives.h"
#include "/scratch/parlaylib/include/parlay/sequence.h"
#include "/scratch/parlaylib/include/parlay/internal/get_time.h"
#include "RC.h"
#include "/scratch/parlaylib/examples/samplesort.h"

#include <cmath>



// **************************************************************
// Driver
// **************************************************************
using vertex = long;
using utils = graph_utils<vertex>;
using graph = parlay::sequence<parlay::sequence<vertex> >;

const vertex max_degree = 8;


int main(int argc, char* argv[]) {
    auto usage = "Usage: RC <n>";
   
    if (argc != 2) {std::cout << usage << std::endl;
        return -1;
    }

    vertex n = 0;
    try { n = std::stoi(argv[1]); }
    catch (...) {}
    if (n == 0) {
        std::cout << "n should be an integer greater than 1" << std::endl;
        return -1;
    }

    auto old_n = n;

    n = pow(2, floor(log2(n)));

    std::cout << "Setting n to closest (lower) power of 2, so "  << old_n << " => " << n <<  std::endl;

    auto parents = generate_tree_graph(n);

    degree_cap_parents(parents, max_degree);

    graph G;

    G = convert_parents_to_graph(G, parents);

    utils::print_graph_stats(G);

    // degree_cap_graph(G, max_degree);
    parlay::sequence<cluster<vertex> > clusters;

    create_base_clusters(G, clusters);

    create_RC_tree(clusters, n);


    return 0;
}
