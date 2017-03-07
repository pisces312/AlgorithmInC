#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include "../common.h"

struct edge {
    int u;
    int v;
    int w;
};

namespace DFS{
void dfsGraph();
}
void bfsGraph();
namespace ShortestPathByDFS {
void shortestPathByDFS();
}

void shortestPathByFloydWarshall();
void shortestPathByDijkstra() ;

void testLinkGraph();
void shortestPathByDijkstraLinkedGraph();
void shortestPathByBellmanFoard();
void shortestPathByBellmanFoardUsingQueue();
void shortestPathByBellmanFoardCheckingNegativeCircle() ;

void mstByKruskal() ;
void mstByPrim();

namespace Cutpoint {
void testCutpoint();
}
namespace Cutpoint2 {
void testCutpoint();
}
namespace Cutedge {
void testCutedge();
}


#endif // GRAPH_H_INCLUDED
