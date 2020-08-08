#include <iostream>
#include <vector>
#include <bits/stdc++.h>


using namespace std;

void parseInput(ifstream& inFile,int prices[],int &M,int &N);
void printResults(ofstream &outFile,int prices[],int &M,int &N);
int main(int argc, char* argv[]){

    if (argc != 3) {
        cerr << "Run the code with the following command: ./cmpe250-assignment5 [input_file] [output_file]" << endl;
        return 1;
    }

    ifstream inFile(argv[1]);
    if (!inFile) {
        cerr << "There was a problem opening \"" << argv[1] << "\" as input file" << endl;
        return 1;
    }

    ofstream outFile(argv[2]);
    if (!outFile) {
        cerr << "There was a problem opening \"" << argv[2] << "\" as output file" << endl;
        return 1;
    }
    int prices[200001];
    int M=0;
    int N=0;
   parseInput(inFile, prices, M, N);

    printResults(outFile, prices, M, N);
    outFile.close();

    return 0;
}
//Parses the input and initializes required variables
void parseInput(ifstream &inFile,int prices[],int &M,int &N){
    string line, tmp;
    getline(inFile, line);
    istringstream lineStream(line);
    getline(lineStream, tmp, ' ');
    //the number of chocolates
     N = stoi(tmp);
    getline(lineStream, tmp, ' ');
    //the max number of chocolates she can buy per day
    M = stoi(tmp);
    getline(inFile, line);
    istringstream lineStream2(line);
    for (int i=1;i<=N;i++){
        getline(lineStream2, tmp, ' ');
        prices[i]=stoi(tmp);
    }
   inFile.close();

}
//Prints the results into the file, the main algorithm is here
void printResults(ofstream &outFile,int prices[],int &M,int &N){

    vector<int> sortedPrices(200001,0);
for(int i=1;i<=N;i++){
    sortedPrices[prices[i]]++;
}
//Calculates the prices for each purchase
    long long int groupSum[M+1];
    long long int sum=0;
    int count=0;
    for(int i=1;i<=200000;i++){
        if(sortedPrices.at(i)!=0){
            count++;
            if(count<=M){
                sum+=i;
                groupSum[count]=i;
                outFile<<sum<<" ";
            }else {
                sum+=i;
                int a=count%M;
                if(a==0)
                    a=M;
                //shifts some prices to the next day
                sum+=groupSum[a];
                groupSum[a]+=i;
                outFile<<sum<<" ";
            }
            if(sortedPrices.at(i)>1){
                sortedPrices[i]--;
                i--;
            }
        }

    }
}
