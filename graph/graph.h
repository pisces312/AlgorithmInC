#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED



namespace graphmatrix {

//For weighted graph -> network
typedef struct GraphMatrix {
    int** arc;//matrix,map,edge
    int n;//vertex number
    int* vertex;//store vertexes
} GraphMatrix;

GraphMatrix* emptyUnweightedGraph(const int verNum);
GraphMatrix* createUnweightedGraph(int vertNum, int* arcs,int arrSize,int directed);

void dfsOnlyConnected(GraphMatrix* g,int cur) ;
void dfs(GraphMatrix* g,int cur);

void bfsOnlyConnected(GraphMatrix* g,int cur) ;
void bfsOnlyConnected2(GraphMatrix* g,int cur) ;
void bfs(GraphMatrix* g,int cur) ;


GraphMatrix* emptyNetwork(const int verNum);
//Each arc is triple <i,j,w>
GraphMatrix* createNetwork(int vertNum, int* arcsValue,int arrSize,int directed);


}



struct edge {
    int u;
    int v;
    int w;
};

namespace simplegraph {
void bfsGraph();
void mstByKruskal() ;
void mstByPrim();
}

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
