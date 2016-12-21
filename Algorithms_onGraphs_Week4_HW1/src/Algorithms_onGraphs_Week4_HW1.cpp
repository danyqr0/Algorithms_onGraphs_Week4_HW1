//============================================================================
// Name        : Algorithms_onGraphs_Week4_HW1.cpp
// Author      : Daniel Ramirez
// Version     :
// Copyright   : HW1_Week4
// Description : Computing the Minimum Cost of a Flight
/*
  Task. Given an directed graph with positive edge weights and with n vertices and m edges as well as two vertices u and v, compute the weight of a shortest path between u and v (that is, the minimum total weight of a path from u to v).

   Input Format. A graph is given in the standard format. The next line contains two vertices u and v.

   Constraints. 1 <= n <= 1e3, 0 <= m <= 1e5, u != v, 1 <= u, v <= n, edge weights are non-negative integers not exceeding 1e3.

   Output Format. Output the minimum weight of a path from u to v, or -1 if there is no path.*/

//============================================================================

#include <iostream>
#include <vector>
#include <climits>
#include <queue>
#include <algorithm>
#include <utility>

#define INF INT_MAX/2

using namespace std;
using std::vector;

typedef pair<int, int> Pair;
typedef vector<Pair> v_pair;

struct Compare{
   bool operator()(Pair const&a, Pair const&b) const
   {
        if(a.second==b.second)
            return a.first>b.first;
        return a.second>b.second;
   };
};

class Graph{
  int V;  //# of vertices
  vector<v_pair> adj;
  public:
    Graph(int v);
    void addEdge(int u, int v,int w);
    void printEdges(void);
    int dijsktra(int n, int s, int t);
};

Graph::Graph(int v):V(v),adj(v,v_pair()){
}

void Graph::addEdge(int u, int v,int w){
   adj[u].push_back(make_pair(v,w));
}

int Graph::dijsktra(int n, int s, int t){
    vector<int> dist(n,INF);
    vector<int> prev (n,-1);
    v_pair::iterator it;
    Pair pq;int u; int v; int w;
    priority_queue<Pair,v_pair,Compare> v_dist;
    pq=make_pair(s,0);
    dist[s]=0;
    v_dist.push(pq);

    while(!v_dist.empty()){
        u=v_dist.top().first; v_dist.pop();
        for(it=adj[u].begin();it!=adj[u].end();it++){
           v=(*it).first;
           w=(*it).second;
           if(dist[v]>dist[u]+w){
              dist[v]=dist[u]+w;
              prev[v]=u;
              v_dist.push(std::make_pair(v,dist[v]));
           }
        }
    }
    if(dist[t]!=INF) return dist[t];
    return -1;
}

void Graph::printEdges(void){
     v_pair::iterator it;
     for(int i=0;i<adj.size();i++){
     for(it=adj[i].begin();it!=adj[i].end();it++)
  	      cout<<"("<<(*it).first<<" "<<(*it).second<<")"<<" ";
         cout<<endl<<endl;
     }
}

int main(){
  int n,m;
  int s,t;
  cin >> n >> m;
  Graph *g=new Graph(n);
  if( (n>=1 && n<=1e3) && (m>=0 && m<=1e5)){
    for (int i = 0; i < m; i++) {
      int x,y,w;
      cin>>x>>y>>w;
      if(w>=0 && abs(w)<1e3)
         g->addEdge(--x,--y,w);
    }
    cin>>s>>t;
    if((s>=1 && t>=1)&&(n>=s && s!=t))
       cout<<g->dijsktra(n, --s, --t)<<endl;
    else cout<<0<<endl;
  }
  return 0;
}
