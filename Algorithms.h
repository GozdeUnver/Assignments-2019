#ifndef CMPE250_ASSIGNMENT3_HELPSTUDENTS_H
#define CMPE250_ASSIGNMENT3_HELPSTUDENTS_H
#include <vector>
#include <iostream>
#include <fstream>
#include <list>
#include <set>

using namespace std;


class HelpStudents{

public:
    vector < pair< pair <int,int> , int > >*edges;
    vector<pair<int,int>> *adjList;
    vector<pair<int,int>> *visited;
    int N;
    int M;
    int K;
    HelpStudents(int  N, int  M, int K, vector < pair< pair <int,int> , int > > &ways);
    long long int firstStudent();
    long long int secondStudent();
    long long int thirdStudent();
    long long int fourthStudent();
    long long int fifthStudent();
    void fill();
    ~HelpStudents();
    void createVisited();
    void fifthStudentUtil(int &A,int count,int &parent,long long int distance,set<int> &forbidden,long long int &results,int repetition);

};

#endif //CMPE250_ASSIGNMENT3_HELPSTUDENTS_H
