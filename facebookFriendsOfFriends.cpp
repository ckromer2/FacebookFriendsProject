#include <iostream>
#include <vector>
#include<fstream>
#include<unordered_map>
#include<forward_list>

using namespace std;

const string FACEBOOK_FILE = "facebook-links2.txt"; 

class Graph{

public:
    unordered_map<int, forward_list<int> > verticies; 

    Graph(){} 

    void addEdge(int x, int y){
        //make sure we do not add duplicates
        for (int& a : verticies[x]){
            if(a == y)
                return; 
        }

        verticies[x].push_front(y); 
        verticies[y].push_front(x); 
    }

    void printEdge(int index){
        int f = verticies.at(index).front(); 
        cout << f; 
    }

    void takeOff(int index){
        verticies.at(index).pop_front(); 
    }

    int getVerticies(){
        numVerticies = 0;
        unordered_map<int, forward_list<int> >:: iterator itr;
        for (itr = verticies.begin(); itr != verticies.end(); itr++){
            numVerticies++; 
        }
        return numVerticies; 
    }

    int getVertexDegree(forward_list<int> list){
        int degree = 0; 
        for(int a: list){
            degree++; 
        }
        return degree; 
    }

    double homework4Help(forward_list<int> list){
        double totalDegree = 0; 
        double numVert = 0; 

        for(int a: list){
            numVert++; 
            totalDegree += getVertexDegree(verticies[a]); 
        }
        
        return totalDegree / numVert; 
    }

    double homework4(){
        int vert = numVerticies; 
        double totalOfAvgs = 0; 
        unordered_map<int, forward_list<int> >:: iterator itr;
        for (itr = verticies.begin(); itr != verticies.end(); itr++)
        {           
            totalOfAvgs += homework4Help(itr->second); 
        }

        return totalOfAvgs / vert; 
    }

    int getEdges(){
        numEdges = 0;
        unordered_map<int, forward_list<int> >:: iterator itr;
        for (itr = verticies.begin(); itr != verticies.end(); itr++)
        {            
            for(int a: itr->second){
                numEdges++; 
            }
         }
         
        return numEdges; 
    }

    void printEdges(){    
        unordered_map<int, forward_list<int> >:: iterator itr;
        for (itr = verticies.begin(); itr != verticies.end(); itr++)
        {
            cout << "Vertex: " << itr->first << " Adj: "; 
            
            for(int a: itr->second){
                cout << a << " "; 
            }
            cout << endl; 
         }
    }

    forward_list<int> getEdgeList(int x){
        return verticies[x]; 
    }

    int getOver100Friends(){
        over100Friends = 0; 
        unordered_map<int, forward_list<int> >:: iterator itr;
        for (itr = verticies.begin(); itr != verticies.end(); itr++)
        {      
            int numFriends = 0;       
            for(int a: itr->second){
                numFriends++; 
            }
            if(numFriends >= 100)
                over100Friends++; 
        }

        return over100Friends; 
    }

private:
    int numVerticies = 0; 
    int numEdges = 0; 
    int over100Friends = 0; 

}; 




int main(){

    ifstream inFS; 
    inFS.open(FACEBOOK_FILE); 
    if(inFS.fail())
        return EXIT_FAILURE; 
    
    Graph g; 

    /*
    int x, y; 
    string z; 
    for(int i = 0; i < 200; i++){
        inFS >> x;
        inFS >> y; 
        inFS >> z; 
        cout << z << endl; 
        cout << x << " " << y << endl;  

    } 
    */ 
    int x, y; 
    string z;   
    while(inFS >> x && inFS >> y && inFS >> z){
        g.addEdge(x,y); 
    }

    int vert = g.getVerticies();
    int edges = g.getEdges(); 
    cout << "Edges: " << edges << endl; 
    cout << "Verticies: " << vert << endl; 
    cout << "Average Degree: " << (double)edges / (double)vert << endl; 
    cout << "Number of Verticies Over Degree 100: " << g.getOver100Friends() << endl; 
    cout << "The answer to number 4 is: " << g.homework4() << endl; 



}