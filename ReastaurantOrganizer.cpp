#include "RestaurantOrganizer.h"

using namespace std;

RestaurantOrganizer::RestaurantOrganizer(const vector<int>& tableCapacityInput){
    numberOfTables = tableCapacityInput.size();
    for(int i=0;i<numberOfTables;i++){
        tableCapacity[i] = tableCapacityInput[i];
        heap[i] = i;
        heapUp(i);
    }
}

void RestaurantOrganizer::addNewGroup(int groupSize, ofstream& outFile){

    /* If the incoming group size is bigger than the capacity of the table that has the maximum capacity
    of all tables in the restaurant, it writes -1 and returns */
    if(groupSize>tableCapacity[heap[0]]){
        outFile<<-1<<endl;
    }
    /* The table with the maximum capacity decreases by the size of the group,
    heapDown method assigns a new table to the beginning of the list if there is another table with bigger capacity */
    else{
        tableCapacity[heap[0]]-=groupSize;
        outFile<<heap[0]<<endl;
        heapDown(0);
    }
}

void RestaurantOrganizer::heapUp(int index){
    // Stores the place where the table will be kept
    int hole=index;

    //If it is not the root, checks whether the parent has a smaller capacity than the child and swaps them
        for (; hole > 0; hole=(hole-1)/2 ){
            if (tableCapacity[heap[(hole-1)/2]] < tableCapacity[heap[hole]]) {
                swap(heap[(hole-1)/2], heap[hole]);
            } else
                break;
        }

}

void RestaurantOrganizer::heapDown(int index){
    // Stores the place where the table will be kept
    int hole=index;
    int child;

    //If the hole is not a leaf, checks whether its children have a bigger capacity
    while((hole*2)+1<numberOfTables){
        child=(hole*2)+1;

        /* If the hole has a right child and the capacity of the right child is bigger than the left child, or
         * their capacities are equal but the table number of the right one is smaller than the left one than
         * the variable named child stores the index of the right child otherwise left*/
        if((hole*2)+2<numberOfTables&&(tableCapacity[heap[(hole*2)+2]]>tableCapacity[heap[(hole*2)+1]]||
                (tableCapacity[heap[(hole*2)+2]]==tableCapacity[heap[(hole*2)+1]]&&heap[(hole*2)+2]<heap[(hole*2)+1]))){
            child++;
        }

        /* If the capacity of the hole is less than the child or their capacities are equal but
         * the table number of the child is less than the hole than they swap */
        if(tableCapacity[heap[hole]]<tableCapacity[heap[child]]||
        ((tableCapacity[heap[hole]]==tableCapacity[heap[child]])&&(heap[hole]>heap[child]))){
            swap(heap[hole],heap[child]);
            hole=child;
        }else{
            break;
        }
    }

}

void RestaurantOrganizer::printSorted(ofstream& outFile){

    // Stores the size of the initial configuration of the tables
    int size= numberOfTables;

    /* After the table with the biggest capacity is printed and deleted, the last element
     * of the list is assigned to the beginning of the list later to be percolated down
     * since the size has decreased by 1 and a new table with the biggest capacity
     * should be assigned to the beginning */
    for(int i=0;i<size;i++){
       outFile<<tableCapacity[heap[0]]<<" ";
        tableCapacity[heap[0]]=tableCapacity[heap[numberOfTables-1]];
        numberOfTables--;
        heapDown(0);

    }

}
