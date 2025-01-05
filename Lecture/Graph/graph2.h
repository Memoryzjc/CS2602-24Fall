#ifndef GRAPH2_H_INCLUDED
#define GRAPH2_H_INCLUDED

#include <iostream>
#include <stack>
#include <queue>
#define DefaultNumVertex 20

class outOfBound{};
class illegalSize{};

template<typename edgeType>
struct edgeNode
{
    int dest;
    edgeType weight;
    edgeNode *link;
};

template<typename verType, typename edgeType>
struct verNode
{
    verType data;
    edgeNode<edgeType> *adj;
};

struct EulerNode {
    int NodeNum;
    EulerNode *next;
    EulerNode(int num) : NodeNum(num), next(nullptr) {}
};

template<typename verType, typename edgeType>
class Graph
{
private:
    bool directed;
    int verts, edges;
    int maxVertex;
    verNode<verType, edgeType> *verList;
    void DFS(int start, bool visited[]) const;
    EulerNode* EulerCircuit(int start, EulerNode *&end);
    verNode<verType, edgeType>* clone();
public:
    Graph(bool directed);
    ~Graph();

    int numberOfVertex() const;  // return the number of vertices
    int numberOfEdge() const;  // return the number of edges
    int getVertex(verType v) const;  // return the index of vertex v
    bool existEdge(verType v1, verType v2) const;  // is there an edge between v1 and v2
    void insertVertex(const verType& v);  // insert a vertex
    void insertEdge(verType v1, verType v2, edgeType e);  // insert an edge between v1 and v2

    void removeVertex(verType v);  // remove a vertex
    void removeEdge(verType v1, verType v2);  // remove an edge between v1 and v2
    int getFirstNeighbor(verType v);  // return the first neighbor of v and -1 if no neighbor
    int getNextNeighbor(verType v1, verType v2);  // return the next neighbor of v1 after v2
    void disp() const;

    void DFS() const;
    void DFS_non_recursive() const;
    void BFS() const;

    bool connected() const;
    void EulerCircuit(verType start);
};

template<typename verType, typename edgeType>
Graph<verType, edgeType>::Graph(bool directed)
{
    this->directed = directed;
    this->verts = 0;
    this->edges = 0;
    this->maxVertex = DefaultNumVertex;

    verList = new verNode<verType, edgeType>[this->maxVertex];
    for (int i = 0; i < this->maxVertex; i++)
    {
        verList[i].adj = nullptr;
    }
}

template<typename verType, typename edgeType>
Graph<verType, edgeType>::~Graph()
{
    edgeNode<edgeType> *p;

    for (int i = 0; i < this->verts; i++)
    {
        while ((p = verList[i].adj) != nullptr)
        {
            verList[i].adj = p->link;
            delete p;
        }
    }

    delete []verList;
}

template<typename verType, typename edgeType>
int Graph<verType, edgeType>::numberOfVertex() const
{
    return this->verts;
}

template<typename verType, typename edgeType>
int Graph<verType, edgeType>::numberOfEdge() const
{
    return this->edges;
}

template<typename verType, typename edgeType>
int Graph<verType, edgeType>::getVertex(verType v) const
{
    for (int i = 0; i < this->verts; i++)
    {
        if (verList[i].data == v)
        {
            return i;
        }
    }

    return -1;
}

template<typename verType, typename edgeType>
bool Graph<verType, edgeType>::existEdge(verType v1, verType v2) const
{
    int u = getVertex(v1);
    int v = getVertex(v2);
    
    if (u == -1 || v == -1)
    {
        return false;
    }

    edgeNode<edgeType> *p = verList[u].adj;

    while (p != nullptr && p->dest != v)
    {
        p = p->link;
    }

    if (p == nullptr)
    {
        return false;
    }
    else
    {
        return true;
    }
}

template<typename verType, typename edgeType>
void Graph<verType, edgeType>::insertVertex(const verType& v)
{
    if (this->verts == this->maxVertex)
    {
        throw outOfBound();
    }

    verList[this->verts++].data = v;
    verList[this->verts].adj = nullptr;
}

template<typename verType, typename edgeType>
void Graph<verType, edgeType>::insertEdge(verType v1, verType v2, edgeType e)
{
    int u = getVertex(v1);
    int v = getVertex(v2);

    if (u == -1 || v == -1)
    {
        throw outOfBound();
    }

    edgeNode<edgeType> *p = verList[u].adj;
    verList[u].adj = new edgeNode<edgeType>;
    verList[u].adj->dest = v;
    verList[u].adj->weight = e;
    verList[u].adj->link = p;

    if (!this->directed)
    {
        p = verList[v].adj;
        verList[v].adj = new edgeNode<edgeType>;
        verList[v].adj->dest = u;
        verList[v].adj->weight = e;
        verList[v].adj->link = p;
    }

    this->edges++;
}

template<typename verType, typename edgeType>
void Graph<verType, edgeType>::removeVertex(verType v)
{
    int u = getVertex(v);
    int count = 0;

    if (u == -1)
    {
        throw outOfBound();
    }

    edgeNode<edgeType> *p, *q;
    p = verList[u].adj;
    while (p) {
        verList[u].adj = p->link;
        delete p;
        p = verList[u].adj;
        count++;
    }

    // check other vertices, if dest is u, remove the edge
    for (int i = 0; i < this->verts; i++) {
        p = verList[i].adj;
        q = nullptr;

        while (p) {
            if (p->dest == u) {
                break;
            }
            q = p;
            p = p->link;
        }

        if (!p) {
            continue;
        }
        if (!q) {
            verList[i].adj = p->link;
        } else {
            q->link = p->link;
        }
        delete p;
        count++;
    }

    for (int i = 0; i < this->verts; i++) {
        p = verList[i].adj;
        while (p) {
            if (p->dest > u) {
                p->dest--;
            }
            p = p->link;
        }
    }

    if (this->directed) {
        edges -= count;
    } else {
        edges -= count / 2;
    }
    
    for (int i = u; i < this->verts - 1; i++) {
        verList[i] = verList[i + 1];
    }
    this->verts--;
}

template<typename verType, typename edgeType>
void Graph<verType, edgeType>::removeEdge(verType v1, verType v2)
{
    int u = getVertex(v1);
    int v = getVertex(v2);

    if (u == -1 || v == -1)
    {
        return;
    }

    edgeNode<edgeType> *p = verList[u].adj;
    edgeNode<edgeType> *q = nullptr;

    while (p != nullptr && p->dest != v) {
        q = p;
        p = p->link;
    }

    if (p == nullptr) {
        return;
    }

    if (q == nullptr) {
        verList[u].adj = p->link;
    } else {
        q->link = p->link;
    }
    delete p;
    this->edges--;

    if (!this->directed)
    {
        p = verList[v].adj;
        q = nullptr;

        while (p != nullptr && p->dest != u)
        {
            q = p;
            p = p->link;
        }

        if (p == nullptr)
        {
            return;
        }

        if (q == nullptr)
        {
            verList[v].adj = p->link;
        }
        else
        {
            q->link = p->link;
        }

        delete p;
    }

    this->edges--;
}

template<typename verType, typename edgeType>
int Graph<verType, edgeType>::getFirstNeighbor(verType v)
{
    int u = getVertex(v);

    if (u == -1)
    {
        return -1;
    }

    edgeNode<edgeType> *p = verList[u].adj;

    if (p != nullptr)
    {
        return p->dest;
    }
    else
    {
        return -1;
    }
}

template<typename verType, typename edgeType>
int Graph<verType, edgeType>::getNextNeighbor(verType v1, verType v2)
{
    int u = getVertex(v1);
    int v = getVertex(v2);

    if (u == -1 || v == -1)
    {
        return -1;
    }

    edgeNode<edgeType> *p = verList[u].adj;

    while (p != nullptr && p->dest != v)
    {
        p = p->link;
    }

    if (p != nullptr && p->link != nullptr)
    {
        return p->link->dest;
    }
    else
    {
        return -1;
    }
}

template<typename verType, typename edgeType>
void Graph<verType, edgeType>::disp() const
{
    edgeNode<edgeType> *p;

    for (int i = 0; i < this->verts; i++) {
        p = verList[i].adj;
        std::cout << verList[i].data << ": ";
        while (p != nullptr) {
            std::cout << p->dest << ",";
            p = p->link;
        }

        std::cout << std::endl;
    }
}

template<typename verType, typename edgeType>
void Graph<verType, edgeType>::DFS(int start, bool visited[]) const
{
    edgeNode<edgeType> *p = verList[start].adj;
    visited[start] = true;
    std::cout << verList[start].data << " ";

    while (p != nullptr)
    {
        if (!visited[p->dest])
        {
            DFS(p->dest, visited);
        }

        p = p->link;
    }
}

template<typename verType, typename edgeType>
void Graph<verType, edgeType>::DFS() const
{
    bool *visited = new bool[this->verts];
    if (visited == nullptr)
    {
        throw illegalSize();
    }

    for (int i = 0; i < this->verts; i++)
    {
        visited[i] = false;
    }

    for (int i = 0; i < this->verts; i++)
    {
        if (!visited[i])
        {
            DFS(i, visited);
        }
    }

    delete []visited;
}

template<typename verType, typename edgeType>
void Graph<verType, edgeType>::DFS_non_recursive() const
{
    std::stack<int> s;
    edgeNode<edgeType> *p;
    bool *visited = new bool[this->verts];
    if (visited == nullptr)
    {
        throw illegalSize();
    }

    for (int i = 0; i < this->verts; i++)
    {
        visited[i] = false;
    }

    for (int i = 0; i < this->verts; i++) {
        if (visited[i]) {
            continue;
        }

        s.push(i);
        while (!s.empty()) {
            int start = s.top();
            s.pop();
            if (visited[start]) {
                continue;
            }
            std::cout << verList[start].data << " ";
            visited[start] = true;

            p = verList[start].adj;
            while (p) {
                if (!visited[p->dest]) {
                    s.push(p->dest);
                }
                p = p->link;
            }
        }
        std::cout << std::endl;
    }
}

template<typename verType, typename edgeType>
void Graph<verType, edgeType>::BFS() const
{
    std::queue<int> q;
    edgeNode<edgeType> *p;
    bool *visited = new bool[this->verts];
    if (visited == nullptr)
    {
        throw illegalSize();
    }

    for (int i = 0; i < this->verts; i++)
    {
        visited[i] = false;
    }

    for (int i = 0; i < this->verts; i++) {
        if (visited[i]) {
            continue;
        }

        q.push(i);
        while (!q.empty()) {
            int start = q.front();
            q.pop();
            if (visited[start]) {
                continue;
            }
            std::cout << verList[start].data << " ";
            visited[start] = true;

            p = verList[start].adj;
            while (p) {
                if (!visited[p->dest]) {
                    q.push(p->dest);
                }
                p = p->link;
            }
        }
        std::cout << std::endl;
    }
}

template<typename verType, typename edgeType>
bool Graph<verType, edgeType>::connected() const {
    std::queue<int> q;
    edgeNode<edgeType> *p;
    bool *visited = new bool[this->verts];
    int i, start, count = 0;

    if (visited == nullptr) {
        throw illegalSize();
    }

    // initialize visited
    for (i = 0; i < this->verts; i++) {
        visited[i] = false;
    }

    for (i = 0; i < this->verts; i++) {
        if (visited[i]) {
            continue;
        }
        q.push(i);
        visited[i] = true;
        count++;

        while (!q.empty()) {
            start = q.front();
            q.pop();
            std::cout << verList[start].data << " ";

            p = verList[start].adj;
            while (p) {
                if (!visited[p->dest]) {
                    q.push(p->dest);
                    visited[p->dest] = true;
                    count++;
                }
                p = p->link;
            }
        }
        std::cout << std::endl;
    }

    if (count == 1) {
        return true;
    }
    return false;
}

template<typename verType, typename edgeType>
verNode<verType, edgeType> *Graph<verType, edgeType>::clone() {
    verNode<verType, edgeType> *tmp = new verNode<this->verts>;
    edgeNode<edgeType> *p;

    for (int i = 0; i < this->verts; i++) {
        tmp[i].data = verList[i].data;
        p = verList[i].adj;
        while (p) {
            tmp[i].adj = new edgeNode(p->dest, p->weight, tmp[i].adj);
            p = p->link;
        }
    }

    return tmp;
}

template<typename verType, typename edgeType>
EulerNode *Graph<verType, edgeType>::EulerCircuit(int start, EulerNode *&end) {
    EulerNode *beg;
    int nextNode;
    beg = end = new EulerNode(start);
    while (this->verList[start].adj) {
        nextNode = this->verList[start].adj->dest;
        remove(start, nextNode);
        remove(nextNode, start);
        start = nextNode;
        end->next = new EulerNode(start);
        end = end->next;
    }
    return beg;
}

template<typename verType, typename edgeType>
void Graph<verType, edgeType>::EulerCircuit(verType start) {
    EulerNode *beg, *end, *p, *q, *tBeg, *tEnd;
    int numOfDegree;
    edgeNode<edgeType> *r;
    verNode<verType, edgeType> *tmp;

    // check if the graph contains Euler circuit
    for (int i = 0; i < this->verts; i++) {
        numOfDegree = 0;
        r = this->verList[i].adj;
        while (r) {
            numOfDegree++;
            r = r->link;
        }
        if (numOfDegree % 2 || numOfDegree == 0) {
            std::cout << "No Euler circuit" << std::endl;
            return;
        }
    }

    // find the start node
    i = getVertex(start);
    if (i == -1) {
        return;
    }

    // clone the graph
    tmp = clone();

    // find the path starting from i, and the start and end address of the path is beg and end
    beg = EulerCircuit(i, end);
    while (true) {
        p = beg;
        while (p->next) {
            if (this->verList[p->next->NodeNum].adj) {
                break;
            } else {
                p = p->next;
            }
        }
        if (!p->next) {
            break;
        }
        q = p->next;
        tBeg = EulerCircuit(q->NodeNum, tEnd);
        tEnd->next = q->next;
        p->next = tBeg;
        delete q;
    }

    // recover the graph
    delete []this->verList;
    this->verList = tmp;

    // output the path
    std::cout << "Euler circuit: " << std::endl;
    while (beg) {
        std::cout << this->verList[beg->NodeNum].data << " ";
        p = beg;
        beg = beg->next;
        delete p;
    }
    std::cout << std::endl;
}

#endif // GRAPH2_H_INCLUDED