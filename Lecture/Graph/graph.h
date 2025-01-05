#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <iostream> 
#include <stack>
#define DefaultNumVertex 20

class outOfBound{};

template<typename edgeType>
struct keyEdge {
    int u, v;
    edgeType weight;
    edgeType early, last;
};

template<typename verType, typename edgeType>
class Graph
{
private:
    int verts, edges;  // number of vertices and edges
    int maxVertex;  // maximum possible number of vertex
    verType *verList;  // store the vertex
    edgeType **edgeMatrix;  // store the adjacent matrix
    edgeType noEdge;  // flag of no edge usually infinity(a large number)
    bool directed;  // 1 for directed graph; 0 for non-directed

public:
    Graph(bool direct, edgeType e);
    int numberOfVertex() const;
    int numberOfEdge() const;
    int getVertex(verType vertex) const;
    bool existEdge(verType vertex1, verType vertex2) const;
    void insertVertex(verType vertex);  // insert a vertex
    void insertEdge(verType vertex1, verType vertex2, edgeType edge);  // insert an edge
    void removeVertex(verType vertex);  // remove a vertex
    void removeEdge(verType vertex1, verType vertex2);  // remove an edge
    // return the first adjacent node of vertex or -1 if it not exist
    int getFirstNeighbor(verType vertex) const;
    // return the next adjacent node of vertex1 to vertex2 or -1 if it not exist
    int getNextNeighbor(verType vertex1, verType vertex2) const;
    void topoSort() const;  // topological sort
    void keyActivity(verType start, verType end) const;
    void disp() const;  // display the value of adjacent matrix
    ~Graph();
};

template<typename verType, typename edgeType>
Graph<verType, edgeType>::Graph(bool direct, edgeType e) {
    this->directed = direct;
    this->noEdge = e;
    this->verts = 0;
    this->edges = 0;
    this->maxVertex = DefaultNumVertex;
    this->verList = new verType[maxVertex];
    this->edgeMatrix = new edgeType* [maxVertex];

    int i, j;
    for (i = 0; i < maxVertex; i++) {
        this->edgeMatrix[i] = new edgeType[maxVertex];
    }

    for (i = 0; i < this->maxVertex; i++) {
        for (j = 0; j < this->maxVertex; j++) {
            if (i == j) {
                this->edgeMatrix[i][j] = 0;
            } else {
                this->edgeMatrix[i][j] = this->noEdge;
            }
        }
    }
}

template<typename verType, typename edgeType>
int Graph<verType, edgeType>::numberOfVertex() const {
    return this->verts;
}

template<typename verType, typename edgeType>
int Graph<verType, edgeType>::numberOfEdge() const {
    return this->edges;
}

template<typename verType, typename edgeType>
int Graph<verType, edgeType>::getVertex(verType vertex) const {
    int i;
    for (i = 0; i < this->verts; i++) {
        if (this->verList[i] == vertex) {
            return i;
        }
    }

    return -1;
}

template<typename verType, typename edgeType>
bool Graph<verType, edgeType>::existEdge(verType vertex1, verType vertex2) const {
    int i, j;
    
    for (i = 0; i < this->verts; i++) {
        if (this->verList[i] == vertex1) {
            break;
        }
    }

    for (j = 0; j < this->verts; j++) {
        if (verList[j] == vertex2) {
            break;
        }
    }

    if (i == this->verts || j == this->verts) {
        return false;
    }
    if (i == j) {
        return false;
    }
    if (this->edgeMatrix[i][j] == noEdge) {
        return false;
    }

    return true;
}

template<typename verType, typename edgeType>
void Graph<verType, edgeType>::insertVertex(verType vertex) {
    int i;
    if (this->verts == this->maxVertex) {
        outOfBound();
    }

    this->verts++;
    this->verList[this->verts - 1] = vertex;

    for (i = 0; i < this->verts; i++) {
        edgeMatrix[this->verts - 1][i] = noEdge;
    }
    for (i = 0; i < this->verts; i++) {
        edgeMatrix[i][this->verts - 1] = noEdge;
    }
    edgeMatrix[this->verts - 1][this->verts - 1] = 0;  // diagonal
}

template<typename verType, typename edgeType>
void Graph<verType, edgeType>::insertEdge(verType vertex1, verType vertex2, edgeType edge) {
    int i, j;
    for (i = 0; i < this->verts; i++) {
        if (this->verList[i] == vertex1) {
            break;
        }
    }

    for (j = 0; j < this->verts; j++) {
        if (this->verList[j] == vertex2) {
            break;
        }
    }

    // if vertex1 or vertex2 not exist
    if (i == this->verts || j == this->verts) {
        return;
    }

    if (i == j) {
        return;
    }

    if (this->edgeMatrix[i][j] == noEdge) {
        this->edges++;
    }

    this->edgeMatrix[i][j] = edge;

    if (!directed) {
        this->edgeMatrix[j][i] = edge;
    }
}

template<typename verType, typename edgeType>
void Graph<verType, edgeType>::removeVertex(verType vertex) {
    int i, j, k;

    for (i == 0; i < this->verts; i++) {
        if (this->verList[i] == vertex) {
            break;
        }
    }

    if (i == this->verts) {
        return;
    }

    for (j == i; j < this->verts - 1; j++) {
        this->verList[j] = verList[j + 1];
    }

    for (j = 0; j < verts; j++) {
        if (j != i && this->edgeMatrix[i][j] != noEdge) {
            edges--;
        }
    }

    if (directed) {
        for (k = 0; k < this->verts; k++) {
            if (k != i && this->edgeMatrix[k][i] != noEdge) {
                edges--;
            }
        }
    }

    for (j = i; j < this->verts; k++) {
        this->edgeMatrix[j][k] = this->edgeMatrix[j + 1][k];
    }
    for (j = i; j < this->verts - 1; j++) {
        for (k = 0; k < this->verts; k++) {
            this->edgeMatrix[k][j] = this->edgeMatrix[k][j + 1];
        }
    }

    verts--;
}

template<typename verType, typename edgeType>
void Graph<verType, edgeType>::removeEdge(verType vertex1, verType vertex2) {
    int i, j;
    for (i = 0; i < this->verts; i++) {
        if (this->verList[i] == vertex1) {
            break;
        }
    }

    for (j = 0; j < this->verts; j++) {
        if (this->verList[j] == vertex2) {
            break;
        }
    }

    if (i == this->verts || j == this->verts) {
        return;
    }

    if (i == j) {
        return;
    }

    if (this->edgeMatrix[i][j] != noEdge) {
        this->edges--;
    }

    this->edgeMatrix[i][j] = noEdge;

    if (!directed) {
        this->edgeMatrix[j][i] = noEdge;
    }
}

template<typename verType, typename edgeType>
int Graph<verType, edgeType>::getFirstNeighbor(verType vertex) const {
    int i;
    for (i = 0; i < this->verts; i++) {
        if (this->verList[i] == vertex) {
            break;
        }
    }

    if (i == this->verts) {
        return -1;
    }

    for (int j = 0; j < this->verts; j++) {
        if (this->edgeMatrix[i][j] != noEdge && i != j) {
            return j;
        }
    }

    return -1;
}

template<typename verType, typename edgeType>
int Graph<verType, edgeType>::getNextNeighbor(verType vertex1, verType vertex2) const {
    int i, j;
    for (i = 0; i < this->verts; i++) {
        if (this->verList[i] == vertex1) {
            break;
        }
    }

    for (j = 0; j < this->verts; j++) {
        if (this->verList[j] == vertex2) {
            break;
        }
    }

    if (i == this->verts || j == this->verts) {
        return -1;
    }

    for (int k = j + 1; k < this->verts; k++) {
        if (this->edgeMatrix[i][k] != noEdge && i != k) {
            return k;
        }
    }

    return -1;
}

template<typename verType, typename edgeType>
void Graph<verType, edgeType>::disp() const {
    int i, j;
    for (i = 0; i < this->verts; i++) {
        for (j = 0; j < this->verts; j++) {
            std::cout << this->edgeMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

template<typename verType, typename edgeType>
Graph<verType, edgeType>::~Graph() {
    int i;
    delete []verList;
    for (i = 0; i < maxVertex; i++) {
        delete []edgeMatrix[i];
    }

    delete []edgeMatrix;
}

template<typename verType, typename edgeType>
void Graph<verType, edgeType>::topoSort() const {
    int *inDegree = new int[this->verts];
    std::stack<int> s;
    int i, j;

    for (j = 0; j < this->verts; j++) {
        inDegree[j] = 0;
        for (i = 0; i < this->verts; i++) {
            if (this->edgeMatrix[i][j] != noEdge && i != j) {
                inDegree[j]++;
            }
        }
        if (inDegree[j] == 0) {
            s.push(j);
        }
    }

    while (!s.empty()) {
        i = s.top();
        s.pop();
        std::cout << i << " ";

        for (j = 0; j < this->verts; j++) {
            if (this->edgeMatrix[i][j] != noEdge && i != j) {
                inDegree[j]--;
                if (inDegree[j] == 0) {
                    s.push(j);
                }
            }
        }
    }

}

template<typename verType, typename edgeType>
void Graph<verType, edgeType>::keyActivity(verType start, verType end) const {
    int *inDegree = new int[this->verts];
    edgeType *verEarly, *verLast;  // event-vertex's early and last time
    keyEdge<edgeType> *edgeEL;  // activity-edge's early and last time
    std::stack<int> s1;  // store the vertex of 0 in-degree
    std::stack<int> s2;  // store the order of vertex
    int i, j, k;
    int u, v;
    int intStart, intEnd;

    verEarly = new edgeType[this->verts];
    verLast = new edgeType[this->verts];
    edgeEL = new keyEdge<edgeType>[this->edges];

    // find the start and end vertex's index
    intStart = intEnd = -1;
    for (i = 0; i < this->verts; i++) {
        if (this->verList[i] == start) {
            intStart = i;
        }
        if (this->verList[i] == end) {
            intEnd = i;
        }
    }
    if (intStart == -1 || intEnd == -1) {
        throw outOfBound();
    }

    // calculate the in-degree of each vertex
    for (j = 0; j < this->verts; j++) {
        inDegree[j] = 0;
        for (i = 0; i < this->verts; i++) {
            if (this->edgeMatrix[i][j] != noEdge && i != j) {
                inDegree[j]++;
            }
        }
    }

    // initialize the earliest time of each vertex
    for (i = 0; i < this->verts; i++) {
        verEarly[i] = 0;
    }

    // calculate the earliest time of each vertex
    // initialize the earliest time of start vertex
    verEarly[intStart] = 0;
    i = intStart;
    s2.push(i);

    // calculate the earliest time of other vertices
    while (i != intEnd) {
        for (j = 0; j < this->verts; j++) {
            if (this->edgeMatrix[i][j] != noEdge && i != j) {
                inDegree[j]--;
                if (inDegree[j] == 0) {
                    s1.push(j);
                }
                if (verEarly[j] < verEarly[i] + this->edgeMatrix[i][j]) {
                    verEarly[j] = verEarly[i] + this->edgeMatrix[i][j];
                }
            }
        }

        i = s1.top();
        s1.pop();
        s2.push(i);
    }

    // initialize the last time of each vertex
    for (i = 0; i < this->verts; i++) {
        verLast[i] = verEarly[intEnd];
    }

    // calculate the last time of each vertex in reverse order
    while (!s2.empty()) {
        j = s2.top();
        s2.pop();
        for (i = 0; i < this->verts; i++) {
            if (this->edgeMatrix[i][j] != noEdge && i != j) {
                if (verLast[i] > verLast[j] - this->edgeMatrix[i][j]) {
                    verLast[i] = verLast[j] - this->edgeMatrix[i][j];
                }
            }
        }
    }

    // build the array of activity-edge
    k = 0;
    for (i = 0; i < this->verts; i++) {
        for (j = 0; j < this->verts; j++) {
            if (this->edgeMatrix[i][j] != noEdge && i != j) {
                edgeEL[k].u = i;
                edgeEL[k].v = j;
                edgeEL[k].weight = this->edgeMatrix[i][j];
                edgeEL[k].early = verEarly[i];
                edgeEL[k].last = verLast[j] - this->edgeMatrix[i][j];
                k++;
            }
        }
    }

    // set the earliest time of <u, v> to the earliest time of u
    // set the last time of <u, v> to the last time of v - weight of <u, v>
    for (k = 0; k < this->edges; k++) {
        u = edgeEL[k].u;
        v = edgeEL[k].v;
        edgeEL[k].early = verEarly[u];
        edgeEL[k].last = verLast[v] - edgeEL[k].weight;
    }

    // output the result
    std::cout << "The key activities are: " << std::endl;
    for (k = 0; k < this->edges; k++) {
        if (edgeEL[k].early == edgeEL[k].last) {
            u = edgeEL[k].u;
            v = edgeEL[k].v;
            std::cout << this->verList[u] << " -> " << this->verList[v] << std::endl;
            std::cout << "Early time: " << edgeEL[k].early << " Last time: " << edgeEL[k].last << std::endl;
            std::cout << std::endl << std::endl;
        }
    }
}


#endif // GRAPH_H_INCLUDED  