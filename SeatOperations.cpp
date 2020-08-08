#include "SeatOperations.h"

using namespace std;

//Creates line vectors with N and M seats
SeatOperations::SeatOperations(int N, int M){
    this->N=N;
    this->M=M;
    Person p=Person();
    if(M>N){
        for(int i=0;i<N;i++){
            lines[0].push_back(p);
            lines[1].push_back(p);
        }
        for(int i=0;i<M-N;i++){
            lines[1].push_back(p);
        }
    }else if(N>M){
        for(int i=0;i<M;i++){
            lines[0].push_back(p);
            lines[1].push_back(p);
        }
        for(int i=0;i<N-M;i++){
            lines[0].push_back(p);
        }
    }else{
        for(int i=0;i<M;i++){
            lines[0].push_back(p);
            lines[1].push_back(p);
        }
    }

}

//Adds a new person to the lines and deals with collusions
void SeatOperations::addNewPerson(int personType, const string& ticketInfo){
    char seatLine=ticketInfo.at(0);
    int seatNo=stoi(ticketInfo.substr(1));
    int key=0;
    int line=0;
    int originalLine=0;
    int type3LastOp=0;

    //Calculates the key where the person will sit
    if(seatLine=='A'){
        key=seatNo % N;
        if(key==0){
            key=N;
        }
        line=0;
        originalLine=0;
    }else {
        key = seatNo % M;
        if(key==0){
            key=M;
        }
        line=1;
        originalLine=1;
    }


    int tmpPersonType=0;
    int tmpSeatNo=0;
    int tmpLine=0;
    int tmpOriginalLine=0;
    int tmpType3LastOp=0;

//Deals with collusions, the former passenger that sat on that seat is moved to the next available seat
    while (lines[line].at(key-1).type != 0) {
        Person &tmp = lines[line].at(key-1);
        tmpPersonType = tmp.type;
        tmpSeatNo = tmp.seatNumber;
        tmpLine = tmp.line;
        tmpOriginalLine=tmp.originalLine;
        tmpType3LastOp = tmp.type3LastOperation;

        lines[line].at(key-1).type=personType;
        lines[line].at(key-1).line=line;
        lines[line].at(key-1).originalLine=originalLine;
        lines[line].at(key-1).seatNumber=seatNo;
        lines[line].at(key-1).type3LastOperation=type3LastOp;

        if (tmpPersonType == 1) {
            tmpLine = (tmpLine == 0 ? 1 : 0);
            key = tmpSeatNo % lines[tmpLine].size();
            if(key==0){
                key=lines[tmpLine].size();
            }

        } else if (tmpPersonType== 2) {
            key++;
            if (key > lines[tmpLine].size()) {
                key = 1;
                tmpLine = (tmpLine == 0 ? 1 : 0);
            }
        }else{
            key+=((tmpType3LastOp+1)*(tmpType3LastOp+1))-(tmpType3LastOp*tmpType3LastOp);
            tmpType3LastOp++;
            while( key>lines[tmpLine].size()) {
                key-=lines[tmpLine].size();
                tmpLine=(tmpLine == 0 ? 1 : 0);
            }
        }
        personType=tmpPersonType;
        seatNo=tmpSeatNo;
        line=tmpLine;
        originalLine=tmpOriginalLine;
        type3LastOp=tmpType3LastOp;

    }


    lines[line].at(key-1).type = personType;
    lines[line].at(key-1).line = line;
    lines[line].at(key-1).originalLine=originalLine;
    lines[line].at(key-1).seatNumber = seatNo;
    lines[line].at(key-1).type3LastOperation=type3LastOp;

}
//Prints the seat numbers of the passengers according to their latest location
void SeatOperations::printAllSeats(ofstream& outFile){
    for(int i=0;i<lines[0].size();i++){
        if(lines[0].at(i).type==0){
            outFile<<"0"<<endl;
        }else {
            char c;
            if(lines[0].at(i).originalLine==0)
                c='A';
            else
                c='B';
            outFile << lines[0].at(i).type << " " << c<< lines[0].at(i).seatNumber << endl;
        }
    }
    for(int i=0;i<lines[1].size();i++){
        if(lines[1].at(i).type==0){
            outFile<<"0"<<endl;
        }else {
            char c;
            if(lines[1].at(i).originalLine==0)
                c='A';
                else
                    c='B';

            outFile << lines[1].at(i).type << " " << c << lines[1].at(i).seatNumber << endl;
        }
    }
}
