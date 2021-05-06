// CS4115 Graph Algorithms Project 

#include <vector>
#include <utility>
#include <queue>
#include <iostream>
#include <string>
#include <math.h>
#include <stdio.h>
#include <sstream>
#include <fstream>
#include <list>
#include <iomanip>
#include <climits>
#include <algorithm>
using namespace std;

// Used to describe Coordinates 
struct Coord {
    double x, y;
    Coord(double x_1, double y_1)
        : x(x_1)
        , y(y_1)
    {
    }
    double getX() { return x; }
    double getY() { return y; }
};

// Data types and vector/lists
int Query;
double EDG;
double Vrtx;
list<int> row;
vector<Coord> coords;
vector<list<int> > Rows;
// type definition
typedef pair<int, int> Pair;

// Functions declarations
void Most_Edges();
void Average_Edges();
void BFS(int start, int end);
void Djikstras_Algo(int start, int end);
list<int> Neighbours(int vrtx, int dist);
float Find_DIST(int X1, int Y1, int X2, int Y2);
void Read_In_Graph(vector<list<int> >& Rows, double& Vrtx, double& EDG,
           double& Longest_Row, double& Total_Edges, string basename);

// Main function
int main()
{
    double Total_Edges = 0;
    double Longest_Row = 0;
    string basename;
    cin >> basename;
    Read_In_Graph(Rows, Vrtx, EDG, Longest_Row, Total_Edges, basename);
    cin >> Query;
    switch (Query) {
        // QUERY 1: Order and Size
    case 1: {
        cout << "n= " << Vrtx << "; "
            << "m= " << EDG << "." << endl;
        break;
    }
          // QUERY 2:  the largest amount of edges that a vertex has
    case 2: {
        Most_Edges();
        break;
    }

          // QUERY 3:  average amount of edges that vertices have
    case 3: {
        Average_Edges();
        break;
    } // QUERY 4: the Neighbours 1 edge away
    case 4: {
        int vrtx;
        cin >> vrtx;
        list<int> Outcome = Neighbours(vrtx, 1);
        cout << "N(" << vrtx << ")= ";
        list<int>::const_iterator it;
        for (it = Outcome.begin(); it != Outcome.end(); it++) {
            cout << *it << " ";
        }
        cout << "." << endl;
        break;
    }
          // QUERY 5: the Neibhours k edges away
    case 5: {
        int vrtx, dist;
        cin >> vrtx >> dist;
        cout << "N(" << vrtx << "," << dist << ")= ";
        list<int> Outcome = Neighbours(vrtx, dist);
        list<int>::const_iterator it;
        for (it = Outcome.begin(); it != Outcome.end(); it++) {
            cout << *it << " ";
        }
        cout << "." << endl;
        break;
    } // QUERY 6: shortest path using xyz
    case 6: {
        int start, end;
        cin >> start >> end;
        Djikstras_Algo(start, end);
        break;
    } // QUERY 7 : shortes path using edges
    case 7: {
        int start, end;
        cin >> start >> end;
        BFS(start, end);
        break;
    }
    }
}
//for Query 2 :most edges 
void Most_Edges()
{  
    float total_edges = 0;
    int vertex_maximum = 0;
    int maximum_edges = 0;

    for (unsigned int i = 1; i < Rows.size(); i++) {
        int current_edge = Rows[i].size();
        if (current_edge > maximum_edges) {
            vertex_maximum = i;
            maximum_edges = current_edge;
        }
        total_edges = total_edges+current_edge;
    }
    cout << "v= " << vertex_maximum << "; |N(v)|= " << maximum_edges << "."
            << endl;
}
// for query 3 : average amount of egdes 
void Average_Edges()
{
    float total_edges = 0;
    float average_edges = 0;
    int maximum_edges = 0;

    for (unsigned int i = 1; i < Rows.size(); i++) {
        int current_edge = Rows[i].size();
        if (current_edge > maximum_edges) {
            maximum_edges = current_edge;
        }
        total_edges = total_edges + current_edge;
    }

    average_edges = float(total_edges / (Rows.size() - 1));
    cout << "avg |N(v)|= " << fixed << setprecision(6) << average_edges
            << "." << endl;
}
// Finds neighbours
list<int>Neighbours(int vrtx, int dist)
{
    list<int> neighbours;
    list<int> temp;
    neighbours.push_back(vrtx);

    if (dist < 0)
    {
        return {};
    }
    else if (dist == 0)
    {
        return { vrtx };
    }

    while (dist > 0) {
        dist--;
        list<int>::const_iterator it;
        for (it = neighbours.begin(); it != neighbours.end(); it++) {
            list<int> r = Rows[*it];
            list<int>::const_iterator it_1;
            for (it_1 = r.begin(); it_1 != r.end(); it_1++) {
                if (*it_1 != *it && (!(find(temp.begin(), temp.end(), *it_1) != temp.end()))) {
                    temp.push_back(*it_1);
                }
            }
        }
        neighbours = temp;
        temp.clear();
    }

    neighbours.sort();
    return neighbours;
} 
// For distance used by Djikstras
float Find_DIST(int X1, int Y1, int X2, int Y2)
{   
    int DisX = (X2 - X1) * (X2 - X1);
    int DisY = (Y2 - Y1) * (Y2 - Y1);
    return sqrt(DisX + DisY);
}

//Finds the shortest path using BFS
void BFS(int start, int end)
{ 
    list<int> temp;
    temp.push_back(start);

    vector<bool> visited(Vrtx + 1, false);
    vector<int> prev(Vrtx + 1, 0);

    visited[start] = true;
    while (!temp.empty()) {
        int vrtx = temp.front();
        temp.pop_front();
        list<int>::const_iterator it;
        list<int> temp_2 = Neighbours(vrtx, 1);
        for (it = temp_2.begin(); it != temp_2.end(); it++) {
            int next = *it;
            if (!visited[next]) {
                prev[next] = vrtx;
                visited[next] = true;
                temp.push_back(next);
            }
            if (next == end)
                break;
        }
    }

    list<int> path;
    for (int i = end; i != 0; i = prev[i]) {
        path.push_back(i);
    }

    path.reverse();
    cout << "ed(" << start << "," << end << ")= " << path.size() - 1 << "."
        << endl;
}
//Shortest path using Djikstras Algorithm
void Djikstras_Algo(int start, int end)
{
    vector<int> disT(Vrtx + 1, INT_MAX);
    vector<int> prev(Vrtx + 1, 0);

    priority_queue<Pair, vector<Pair>, greater<Pair> > Priority;

    Priority.push(make_pair(0, start));

    disT[start] = 0;

    while (!Priority.empty()) {
        int TEMP = Priority.top().second;
        Priority.pop();
        list<int>::iterator it;
        list<int> temp_2 = Rows[TEMP];
        for (it = temp_2.begin(); it != temp_2.end(); it++) {
            int TEMP2 = *it;
            int cost = Find_DIST(coords[TEMP].getX(), coords[TEMP].getY(), coords[TEMP2].getX(),
                coords[TEMP2].getY());
            if (disT[TEMP2] > disT[TEMP] + cost) {
                disT[TEMP2] = disT[TEMP] + cost;
                prev[TEMP2] = TEMP;
                Priority.push(make_pair(disT[TEMP2], TEMP2));
            }
        }
    }
    list<int> path;
    for (int i = end; i != 0; i = prev[i]) {
        path.push_back(i);
    }

    path.reverse();
    vector<int> Outcome;
    float dist;
    list<int>::const_iterator c;
    for (c = path.begin(); c != path.end(); c++) {
        Outcome.push_back(*c);
    }

    for (unsigned int i = 0; i < Outcome.size() - 1; i++) {
        Coord TEMP2 = coords[Outcome[i]];
        Coord TEMP = coords[Outcome[i + 1]];
        float currentDistance = Find_DIST(TEMP2.getX(), TEMP2.getY(), TEMP.getX(), TEMP.getY());
        dist += currentDistance;
    }

    cout << "d(" << start << "," << end << ")=  " << fixed << setprecision(6)
        << dist << "." << endl;
}
// Reads in .graph & .xyz and gets Order and Size for Query 1 
void Read_In_Graph(vector<list<int> >& Rows, double& Vrtx, double& EDG,
    double& Longest_Row, double& Total_Edges, string basename)
{
    string filename = basename + ".osm.graph";
    string line;
    ifstream Input_Graph;
    Input_Graph.open(filename);

    if (!Input_Graph) {
        cout << "Error:Cannot Open File/.graph";
        exit(1);
    }

  
    string filename_coordinates = basename + ".osm.xyz";
    ifstream Input_XYZ;
    Input_XYZ.open(filename_coordinates);

    if (!Input_XYZ) {
        cout << "Error:Cannot Open File/.xyz";
        exit(1);
    }
    coords.push_back(Coord(0, 0));
    while (getline(Input_XYZ, line)) {
        std::istringstream lstream(line);
        double x, y, z;
        lstream >> x >> y >> z;
        coords.push_back(Coord(x, y));
    }

    Input_XYZ.close();

    

    while (getline(Input_Graph, line)) {
        if (line.length() == 0 || line[0] == '%' || line[0] == '=') {
            continue;
        }
        else {
            std::istringstream lstream(line);
            lstream >> Vrtx >> EDG;
            break;
        }
    }

    for (int i = 0; i < Vrtx + 1; i++) {
        Rows.push_back(row);
    }

    int index = 1;
    while (getline(Input_Graph, line)) {
        int temp = 0;
        if (line.length() == 0 || line[0] == '%' || line[0] == '=') {
            continue;
        }
        else {
            std::istringstream lstream(line);
            int value;

            while (lstream >> value) {
                Rows[index].push_back(value);
                Total_Edges++;
                temp++;
            }
            index++;
            if (temp > Longest_Row)
                Longest_Row = temp;
        }
    }

    Input_Graph.close();
}