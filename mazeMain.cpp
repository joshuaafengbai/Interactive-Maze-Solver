#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <ctime>
#include <random>
#include <chrono>
#include <vector>

struct node {
	char id;
	node* north;
	node* south;
	node* east;
	node* west;
};

typedef node* nodeptr;

void build_basic_maze(nodeptr& start, nodeptr& finish);
// builds the basic maze displayed in page 1

nodeptr traverse_maze(const nodeptr& start, const std::string& path);
// traverses the maze using a predefined path

void solve_interactively(const nodeptr& start, const nodeptr& finish, std::string& path);
// allows the user to solve the maze interactively

nodeptr random_walk(const nodeptr& start, const nodeptr& finish, std::string& path);
// simulates a random walk in the maze

void solve_queue(const nodeptr& start, const nodeptr& finish, std::string& path);
// an improvement of the random walk: solves the maze using a queue to store the unvisited neighbours of the current node

void solve_stack(const nodeptr& start, const nodeptr& finish, std::string& path);
// an improvement of the random walk: solves the maze using a stack to store the unvisited neighbours of the current node

std::string filter(std::vector <nodeptr>& check);
bool valid(const nodeptr& current, std::string path_valid);
void deleted( std::vector <char>& delete_visited, char node_id);
bool found(std::vector <char>& search_visited, char node_id);

int main(){

  nodeptr start = NULL;
  nodeptr finish = NULL;
  std::string path;

}

void build_basic_maze(nodeptr& start, nodeptr& finish){
  nodeptr a = new node;
  nodeptr b = new node;
  nodeptr c = new node;
  nodeptr d = new node;
  nodeptr e = new node;
  nodeptr f = new node;
  nodeptr g = new node;
  nodeptr h = new node;
  nodeptr i = new node;
  nodeptr j = new node;
  nodeptr k = new node;
  nodeptr l = new node;

  a->id = 'A';
  a->south = e;
  a->east = b;
  a->north = NULL;
  a->west = NULL;

  b->id = 'B';
  b->west = a;
  b->south = f;
  b->north = NULL;
  b->east = NULL;

  c->id = 'C';
  c->east = d;
  c->south = g;
  c->north = NULL;
  c->west = NULL;

  d->id = 'D';
  d->west = c;
  d->north = NULL;
  d->east = NULL;
  d->south = NULL;

  e->id = 'E';
  e->north = a;
  e->south = i;
  e->east = NULL;
  e->west = NULL;

  f->id = 'F';
  f->north = b;
  f->east = g;
  f->south = NULL;
  f->west = NULL;

  g->id = 'G';
  g->north = c;
  g->east = h;
  g->south = k;
  g->west = f;

  h->id = 'H';
  h->south = l;
  h->west = g;
  h->north = NULL;
  h->east = NULL;

  i->id = 'I';
  i->north = e;
  i->east = j;
  i->west = NULL;
  i->south = NULL;

  j->id = 'J';
  j->west = i;
  j->north = NULL;
  j->east = NULL;
  j->south = NULL;

  k->id = 'K';
  k->north = g;
  k->east = NULL;
  k->south = NULL;
  k->west = NULL;

  l->id = 'L';
  l->north = h;
  l->east = NULL;
  l->south = NULL;
  l->west = NULL;

  start = a;
  finish = l;
}

nodeptr traverse_maze(const nodeptr& start, const std::string& path){
  nodeptr currentnode = start;
  for (int i=0; i<path.size(); i++){
    char direction = path[i];
    if (direction == 'N'){
      currentnode = currentnode->north;
    }
    if (direction == 'E'){
      currentnode = currentnode->east;
    }
    if (direction == 'S'){
      currentnode = currentnode->south;
    }
    if (direction == 'W'){
      currentnode = currentnode->west;
    }
  }
  return currentnode;
}

void solve_interactively(const nodeptr& start, const nodeptr& finish, std::string& path){

  nodeptr currentnode = start;
  std::string direction;

  while (currentnode!= NULL && currentnode != finish && direction!="Q"){
    std::cout << "You are in room " << currentnode->id << " of the maze" << std::endl;
    std::cout << "You can go " << std::endl;

    if (currentnode->north != NULL){
      std::cout << "(N)orth ";
    }
    if (currentnode->east != NULL){
      std::cout << "(E)ast ";
    }
    if (currentnode->south != NULL){
      std::cout << "(S)outh ";
    }
    if (currentnode->west != NULL){
      std::cout << "(W)est ";
    }
    std::cout << "or (Q)uit" << std::endl;

    std::cin >> direction;
    path += direction;

    currentnode = traverse_maze(currentnode, direction);
  }
  if (currentnode == finish){
    std::cout << "Congralutions, you reached the finals!" << std::endl;
  }

}

nodeptr random_walk(const nodeptr& start, const nodeptr& finish, std::string& path){
  srand(time(NULL));
  nodeptr currentnode = start;
  int i = 0;

  while (currentnode != finish && i<100 ){
    int randominteger = rand()%4;

    if (randominteger==0 && currentnode->north != NULL){
      currentnode = currentnode->north;
      path += "N";
    }
    if (randominteger==1 && currentnode->east != NULL){
      currentnode = currentnode->east;
      path += "E";
    }
    if (randominteger==2 && currentnode->south != NULL){
      currentnode = currentnode->south;
      path += "S";
    }
    if (randominteger==3 && currentnode->west != NULL){
      currentnode = currentnode->west;
      path += "W";
    }
    i++;
  }

  return currentnode;
}

void solve_queue(const nodeptr& start, const nodeptr& finish, std::string& path){
    //creating a vector containing the 12 IDs of the path nodes
    std::vector <char> visited;
    std::vector <nodeptr> check;

    visited.push_back('J');
    visited.push_back('I');
    visited.push_back('E');
    visited.push_back('A');
    visited.push_back('B');
    visited.push_back('F');
    visited.push_back('G');
    visited.push_back('K');
    visited.push_back('C');
    visited.push_back('D');
    visited.push_back('H');
    visited.push_back('L');

    nodeptr tmp = start;
    nodeptr print;
    nodeptr variable;
    nodeptr currentnode;

    deleted(visited,tmp->id);// We mark start as visited
    std::queue <nodeptr> children;//We create a queue to store unvisited neighbours
    children.push(tmp);
    while(children.front() != finish){
        print = children.front();
        check.push_back(print);

        currentnode = children.front();

        children.pop(); //dequeue node from the front

        variable = currentnode-> east;
        if(variable != NULL && found(visited, variable->id) == true)
        {
            children.push(variable); //store child in queue
            deleted(visited,variable->id); //delete child node
        }

        variable = currentnode-> west;
        if(variable != NULL && found(visited, variable->id) == true)
        {
            children.push(variable);
            deleted(visited, variable->id);
        }

        variable = currentnode-> north;
        if(variable != NULL && found(visited, variable->id) == true)
        {
            children.push(variable);
            deleted(visited, variable->id);
        }

        variable = currentnode-> south;
        if(variable != NULL && found(visited, variable->id) == true)
        {
            children.push(variable);
            deleted(visited, variable->id);
        }
    }
    check.push_back(finish);

    path = filter(check);

}

void solve_stack(const nodeptr& start, const nodeptr& finish, std::string& path){

    std::vector <char> visited;
    std::vector <nodeptr> check;

    visited.push_back('J');
    visited.push_back('I');
    visited.push_back('E');
    visited.push_back('A');
    visited.push_back('B');
    visited.push_back('F');
    visited.push_back('G');
    visited.push_back('K');
    visited.push_back('C');
    visited.push_back('D');
    visited.push_back('H');
    visited.push_back('L');

    nodeptr tmp = start;
    nodeptr print;
    nodeptr variable;
    nodeptr currentnode;

    deleted(visited,tmp->id);

    std::stack <nodeptr> children;

    children.push(tmp);

    while(children.top() != finish)
    {
        print = children.top();
        check.push_back(print);

        currentnode = children.top();

        children.pop();
        variable = currentnode-> east;
        if(variable != NULL && found(visited, variable->id) == true)
        {
            children.push(variable);
            deleted(visited,variable->id);
        }

        variable = currentnode-> west;
        if(variable != NULL && found(visited, variable->id) == true)
        {
            children.push(variable);
            deleted(visited, variable->id);
        }

        variable = currentnode-> north;
        if(variable != NULL && found(visited, variable->id) == true)
        {
            children.push(variable);
            deleted(visited, variable->id);
        }

        variable = currentnode-> south;
        if(variable != NULL && found(visited, variable->id) == true)
        {
            children.push(variable);
            deleted(visited, variable->id);
        }
    }
    check.push_back(finish);

    path = filter(check);
}

void deleted(std::vector <char>& delete_visited, char node_id){
    for(int i = 0; i < delete_visited.size(); i++){
        if(delete_visited[i] == node_id){
            delete_visited.erase (delete_visited.begin()+i);
            //This line marks that the node has been visited by first deleting it
        }
    }
}

bool found(std::vector <char>& search_visited, char node_id){
    for(int i = 0; i < search_visited.size(); i++){
        if(search_visited[i] == node_id){
            return true;
        }
    }
    return false;
}

std::string filter(std::vector <nodeptr>& check){
    std::string pathfiltered;
    std::vector <nodeptr> filternode;

    filternode.push_back(check.back()); //We store the last element from check into filtered
    for(int i = check.size()-1; i >= 0; i--){ //Starting with finish if the node above is not in the main path to start, delete it
        if(filternode.back() -> east == check[i]){
            filternode.push_back(check[i]);
        }
        if(filternode.back() -> north == check[i]){
            filternode.push_back(check[i]);
        }
        if(filternode.back() -> west ==  check[i]){
            filternode.push_back(check[i]);
        }
        if(filternode.back() -> south == check[i]){
            filternode.push_back(check[i]);
        }
        else{
            check.erase(check.begin()+i);
        }
    }
    for(int i = 0; i<filternode.size(); i++){
        nodeptr pointr = filternode[i];
    }

    for(int i = filternode.size()-1; i > 0; i--){ //starting with finish if the node above is not in the main path to start, delete it
        if(filternode[i] -> east == filternode[i-1]){
            pathfiltered.append("E ");
        }
        if(filternode[i] -> north == filternode[i-1]){
            pathfiltered.append("N ");
        }
        if(filternode[i] -> west ==  filternode[i-1]){
            pathfiltered.append("W ");
        }
        if(filternode[i] -> south == filternode[i-1])
        {
            pathfiltered.append("S ");
        }
    }
    return pathfiltered;
}
