/*  Project Name : Wrestler Rivalries Determinator
    Date: 5/11/2020
    Programmer: Jacob Mast
    Description: The program to runs the wrestler rivalries list problem given in 
                CS 325 HW5 Problem 5.  The program has a BFS function which
                checks if the graph of wrestlers' rivalries is bipartite.
                The user input sets the list of wrestler names, as well as the list
                of wrestler rivalries, by listing two names from the names list on the
                same line in a rivalries list.  The main function prints a message to the
                terminal to tell user if wrestler list with rivalries is bipartite and,
                if so, prints two lists of wrestler names in two rivalrous groups.  
                All input from user is received through an input file specified in the
                command line at runtime.
                All output is written to the terminal.
*/


#include<iostream>
#include<fstream>
#include<bits/stdc++.h>
#define SIZE 100010 //define size
using namespace std;

// declare globals for graph
vector<int> adj[SIZE];//define a vector (adjacency matrix)
int babyFaces[SIZE];
bool visited[SIZE];

/* function declaration
   This function checks if the graph of wrestler rivalries is bipartite */
bool bfs(int pos, int parent);


// main function takes command line arguments
int main(int argc, char * args[]){
    
    // declare variables
    int n, j, k, u, v, r;
    string babyFacesNames, rival1, rival2;
    bool possible = 1;

    // declare map variable
    map<string, int> data;
   
    // open input file
    ifstream infile(args[1]);

    // If file doesn't exist, give error message.
    if (!infile) {
        cout << "Error opening file.  Check to make sure file is in current directory\n";
        return 0;
    }

    // read number of wrestlers.
    infile >> n;

    // create an array of strings to store names
    string names[n + 1];

    // store wrestler names in array
    for (int i = 0; i < n; i++){
        infile >> babyFacesNames;
        data[babyFacesNames] = i;
        names[i] = babyFacesNames;
    }

    // read number of rivalries
    infile >> r;
    
    // read rivalries listed in pairs.
    for (int i = 0; i < r; i++){
        infile >> rival1 >> rival2;
        //set u to index value of rival1
        u = data[rival1];
        //set v to index value of rival2
        v = data[rival2];
        // add edges to the graph
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // close input file
    infile.close();

    // gets a pointer to the destination string
    // make all wrestlers as heels first
    memset(babyFaces, 0, sizeof babyFaces);
    
    // set all nodes as unvisited for BFS
    memset(visited, 0, sizeof visited);

    // assign all values to 0
    babyFaces[0] = 0;

    // Run BFS on completed graph
    for (int i = 0;i < n;i++){
       
        if (visited[i]){
            continue;
        }
        
        // call the function bfs() to determine if data is bipartite
        possible = bfs(i, 0);

        // if data is not bipartite then function prints "Not possible" message
        // and exits loop
        if (!possible){
            cout << "No" << endl;
            break;
        }
    }

    if (possible){

        // declare vectors for storing names
        vector<string> faces, heels;

        for (int i = 0;i < n;i++){

            // push the names to either babyfaces or heels list, depending on if present
            // in babyFaces array
            if (babyFaces[i]){
                faces.push_back(names[i]);
            }
            else{
               heels.push_back(names[i]);
            }
        }

        // Print message with wrestler names in groups
        cout << "Yes\n";
        cout << "BabyFaces: ";

        // print Babyfaces' names
        for (int i = 0;i<faces.size();i++){
            cout << faces[i] << " ";
        }
        cout << endl;

        // print Heels' names
        cout << "Heels: ";
        for (int i = heels.size() - 1;i >= 0;i--){
            cout << heels[i] << " ";
        }
        cout << endl;
    }

    return 0;
}


/* function definition
   This function checks if the graph of wrestler rivalries is bipartite */

bool bfs(int pos, int parent){

    //mark the position as visited
    visited[pos] = 1;

    // declare variables
    int i, value;

    // assign the node to be opposite to its parent
    babyFaces[pos] = 1 - babyFaces[parent];

    // iterate the adjacency matrix
    for (i = 0;i<adj[pos].size();i++){
        value = adj[pos][i];
        // if the value is not visted recursively call bfs function
        if (!visited[value]){
            bfs(value, pos);
        }
        else{
           // if two adjacent nodes have same value graph is not bipartite
           if (babyFaces[value] == babyFaces[pos])
               return false;
        }
    }
    
    return true;
}