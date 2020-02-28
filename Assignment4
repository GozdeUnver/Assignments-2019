#include "HelpStudents.h"
#include <queue>
#include<climits>
#include <set>
#include <set>
#include <list>
#include <vector>

using namespace std;

HelpStudents::HelpStudents(int  N, int  M, int K, vector < pair< pair <int,int> , int > > &ways) {

    this->edges=&ways;
    this->N=N;
    this->M=M;
    this->K=K;
     this->adjList=new vector<pair<int,int>>[this->N+1];
     fill();

}
HelpStudents::~HelpStudents() {

    delete []adjList;
}
void HelpStudents::fill(){

    for(int i=0;i<this->M;i++){
        int first=edges->at(i).first.first;
        int second=edges->at(i).first.second;
        int w=edges->at(i).second;

        adjList[first].push_back(make_pair(second,w));
        adjList[second].push_back(make_pair(first,w));
    }

}
long long int HelpStudents::firstStudent() {

set<pair<long long int,int>> *processed=new set<pair<long long int,int>>();
    vector<long long int> distance(this->N+1,LLONG_MAX);
processed->insert(make_pair(0,1));
    distance[1]=0;

   while(!processed->empty()) {
       int popped = processed->begin()->second;
       processed->erase(processed->begin());

       vector<pair<int, int>>::iterator itr;
       for (itr = adjList[popped].begin(); itr != adjList[popped].end(); ++itr) {
           int neighbor = (*itr).first;
           int weight = (*itr).second;

           if (distance[neighbor] > distance[popped] + weight) {
               long long int t = distance[neighbor];
               distance[neighbor] = distance[popped] + weight;
               
               if(t!=LLONG_MAX)
                   processed->erase(processed->find(make_pair(t, neighbor)));
               processed->insert(make_pair(distance[neighbor], neighbor));


           }
       }
   }
   delete processed;
    return distance[this->K];
}
long long int HelpStudents::secondStudent() {
 vector<int> cost(this->N+1,INT_MAX);
 vector<bool> known(this->N+1,false);
 vector<int> path(this->N+1,-1);
 int maxEdge=-1;
 cost[1]=0;
 set<pair<int,pair<int,int>>> *s=new set<pair<int,pair<int,int>>>();
 s->insert(make_pair(0,make_pair(1,maxEdge)));
 while(!s->empty()){
     int popped=s->begin()->second.first;
     maxEdge=s->begin()->second.second;
     s->erase(s->begin());
     known[popped]=true;
     if(popped==this->K){
         break;
     }
     for(int i=0;i<adjList[popped].size();i++){
         int neighbor=adjList[popped].at(i).first;
         int weight=adjList[popped].at(i).second;
         if(known[neighbor]==false){
             if(cost[neighbor]>weight){
                 cost[neighbor]=weight;
                 path[neighbor]=popped;
                 if(cost[neighbor]>maxEdge){
                     s->insert(make_pair(cost[neighbor],make_pair(neighbor,cost[neighbor])));
                 }else
                 s->insert(make_pair(cost[neighbor],make_pair(neighbor,maxEdge)));
             }
         }
     }
 }
 delete s;

 return maxEdge;
}

long long int HelpStudents::thirdStudent() {
    vector<long long int> distance(this->N+1,-1);
    vector<int> parent(this->N+1,-1);
    queue<int> q;
    q.push(1);
    distance[1]=0;
    int popped=0;
    while(!q.empty()) {
        popped = q.front();
        q.pop();
        if (popped == this->K) {
            break;
        }
        vector<pair<int, int>>::iterator itr;
        for (itr = adjList[popped].begin(); itr != adjList[popped].end(); ++itr) {
            int neighbor = (*itr).first;
            if (distance[neighbor] == -1) {
                distance[neighbor] = distance[popped] + 1;
                parent[neighbor] = popped;
                q.push(neighbor);
            }
        }
    }
    return distance[this->K];
}
void HelpStudents::createVisited(){
    this->visited=new vector<pair<int,int>>[this->N+1];
}
long long int HelpStudents::fourthStudent() {
    if(adjList[this->K].size()==0)
        return-1;
    int place = 1;
createVisited();
    long long int distance = 0;

    while (place!=this->K&&place!=adjList->size()) {
        int minEdge = INT_MAX;
        int minNode = INT_MAX;
        for (int i = 0; i < adjList[place].size(); i++) {
            int neighbor = adjList[place].at(i).first;
            int weight = adjList[place].at(i).second;
            int visit=0;
            if(!this->visited[place].empty()){
                vector<pair<int,int>>::iterator itr;
                for(itr=this->visited[place].begin();itr!=this->visited[place].end();++itr){
                    if((*itr).first==neighbor&&(*itr).second==1){
                        visit=1;
                        break;
                    }
                }
            }
            if ((weight < minEdge && visit==0)||(weight==minEdge&&visit==0&&neighbor<minNode)) {
                minEdge = weight;
                minNode = neighbor;
            }
        }
        if(minEdge==INT_MAX){
            return -1;
        }
        visited[place].push_back(make_pair(minNode,1));
        visited[minNode].push_back(make_pair(place,1));
        distance += minEdge;
        place = minNode;
    }
    delete [] visited;
    if(place==this->K)
    return distance;
    else
        return  -1;
}
long long int HelpStudents::fifthStudent() {
  set<int> *forbidden=new set<int>();
  int A=1;
  int parent=0;
  long long int results=0;
  fifthStudentUtil(A,0,parent,0,*forbidden,results,0);
  delete forbidden;
  return results;

}
void HelpStudents::fifthStudentUtil(int &A,int count,int &parent,long long int distance,set<int> &forbidden,long long int &results,int repetition) {
if(A==this->K){

  if(results==0)
      results=distance;
  else if(results>distance)
      results=distance;
  return;

}else{
    for(int i=0;i<adjList[A].size();i++) {
        int neighbor = adjList[A].at(i).first;
        int weight = adjList[A].at(i).second;
        forbidden.insert(A);
        if (count == 2) {
            if(repetition==1){
                if(neighbor==parent) {
                    for (int j = 0; j < adjList[neighbor].size(); j++) {
                        if (adjList[neighbor].at(j).first != A && adjList[neighbor].at(j).second > 4 * weight) {
                            fifthStudentUtil(neighbor, 0, A, distance, forbidden, results, repetition + 1);
                            break;
                        }
                    }
                }else if(forbidden.find(neighbor)==forbidden.end()){
                    fifthStudentUtil(neighbor, 0, A, distance, forbidden, results, 0);
                }
            }else {
                set<int>::iterator itr=forbidden.find(neighbor);
                if (repetition == 4 && neighbor != parent && itr== forbidden.end()) {
                    fifthStudentUtil(neighbor, 0, A, distance, forbidden, results, 0);
                } else if(repetition==2&&itr==forbidden.end())
                    fifthStudentUtil(neighbor, 0, A, distance, forbidden, results, 0);
                else if (repetition == 0) {
                    if(itr==forbidden.end()){
                        fifthStudentUtil(neighbor, 0, A, distance, forbidden, results, 0);
                    }else if(neighbor==parent){
                        fifthStudentUtil(neighbor, 0, A, distance, forbidden, results, repetition+1);
                    }
                }
            }
        } else if (count == 1) {
            if(repetition==3&&neighbor==parent){
                fifthStudentUtil(neighbor, count+1,A, distance+weight, forbidden,results,repetition+1);
            }else if(repetition==1&&neighbor==parent){
                fifthStudentUtil(neighbor, count+1,A, distance+weight, forbidden,results,repetition+1);
            }
            else if(repetition==0&&neighbor==parent){
                fifthStudentUtil(neighbor, count+1,A, distance+weight, forbidden,results,repetition+1);
            }else if(repetition==0&&forbidden.find(neighbor)==forbidden.end()) {
                fifthStudentUtil(neighbor, count+1,A, distance+weight, forbidden,results,0);
            }

        } else if (count==0) {
            if(repetition==2&&neighbor==parent){
                fifthStudentUtil(neighbor, count+1,A, distance+weight, forbidden,results,repetition+1);
            }
            else if(repetition==0&&neighbor==parent){
                for(int j=0;j<adjList[neighbor].size();j++){
                    if(adjList[neighbor].at(j).first!=A&&adjList[neighbor].at(j).second>2*weight){
                        fifthStudentUtil(neighbor, count+1,A, distance+weight, forbidden,results,repetition+1);
                        break;
                    }
                }
            }
            else if(repetition==0&&forbidden.find(neighbor)==forbidden.end())
                fifthStudentUtil(neighbor, count+1,A, distance+weight, forbidden,results,0);
        }

    }
    set<int>::iterator itr=forbidden.find(A);
     if(itr!=forbidden.end())
    forbidden.erase(*itr);
}

}
