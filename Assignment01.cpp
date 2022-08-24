/*
CS 302 Assignment 1

Name: Keith Beauvais, 5005338658, CS 302 Assignment 1
*/
#include "LinkedList.h"
#include <iostream> 
#include <fstream>


using namespace std;

int main(){
    string filename;
    ifstream infile;
    int userInteger;
    LL<int> list;
    LL<int>::iterator it;
    LL<int>::iterator nil;

    // Prompts user
    cout<< "Enter file with list: ";
    cin >> filename;
    // Reads in file
    infile.open(filename);
    infile >> userInteger;
    cout<<"Original List"<<endl;

    // reads in file and does a tail insert 
    while(!infile.eof()){
        
        list.tailInsert(userInteger);
        infile >> userInteger;
        
    }
    infile.close();
    // prints out list as it was read in 
    it = list.begin();
    
    while(it != nil){
        cout<< *it << " ";
        it++;
    }
    cout<<endl;
    cout<<endl;
    cout<<"Sorted List"<<endl;


    LL<int>::iterator i;
    LL<int>::iterator j;
    LL<int>::iterator k;
   
    j = list.begin();
    k = list.begin();


    // bubble sort no counters used
    while(i != list.begin()){
    
        j = list.begin();
        k = list.begin();
        k++;
        while(k != i){
            
            if (*j > *k){
                list.swapNodes(j,k);
            }
            j++;
            k++;
        }
        if(i == nil){
            i = list.end(); 
        }
        else{
            i--;
        }
    }

    // prints out sorted list
    it = list.begin();
    while(it != NULL){
        cout<< *it << " ";
        it++;
    }
    cout << endl;
    cout << endl;

    return 0;
}

