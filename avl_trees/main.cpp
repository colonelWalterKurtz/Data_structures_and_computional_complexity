#include <iostream>
#include <fstream>
#include <chrono>
#include <string>

using namespace std;

// section of global variables
string data_file_name;
int instances[13];
int number_of_measurements;
string measurements_file_name;
// int algo_choice;
string algorithm;

// section of functions
void initialize();
void check_initialize();
void create_mesurements_file(string file_name, int number_of_measures, string algorithm);
void append_measure_file(string file_name, string alg, int instantion, int number_of_mesures, unsigned long int* ptr);
void read_words(string file_name, int quantity_of_words, string* words);
void load_numbers(int* ptr, int quantity_of_num, string file_name);
void print_numbers(int* ptr, int quantity_of_numbers);
void print_words(int quantity_of_words, string* words);

// avl tree section
class Node {
   public:
  int key;
  Node *left;
  Node *right;
  int height;
};

int max(int a, int b);

// Calculate height
int height(Node *N) {
  if (N == NULL)
    return 0;
  return N->height;
}

int max(int a, int b) {
  return (a > b) ? a : b;
}

// New node creation
Node *newNode(int key) {
  Node *node = new Node();
  node->key = key;
  node->left = NULL;
  node->right = NULL;
  node->height = 1;
  return (node);
}

// Rotate right
Node *rightRotate(Node *y) {
  Node *x = y->left;
  Node *T2 = x->right;
  x->right = y;
  y->left = T2;
  y->height = max(height(y->left),
          height(y->right)) +
        1;
  x->height = max(height(x->left),
          height(x->right)) +
        1;
  return x;
}

// Rotate left
Node *leftRotate(Node *x) {
  Node *y = x->right;
  Node *T2 = y->left;
  y->left = x;
  x->right = T2;
  x->height = max(height(x->left),
          height(x->right)) +
        1;
  y->height = max(height(y->left),
          height(y->right)) +
        1;
  return y;
}

// Get the balance factor of each node
int getBalanceFactor(Node *N) {
  if (N == NULL)
    return 0;
  return height(N->left) -
       height(N->right);
}

// Insert a node
Node *insertNode(Node *node, int key) {
  // Find the correct postion and insert the node
  if (node == NULL)
    return (newNode(key));
  if (key < node->key)
    node->left = insertNode(node->left, key);
  else if (key > node->key)
    node->right = insertNode(node->right, key);
  else
    return node;

  // Update the balance factor of each node and
  // balance the tree
  node->height = 1 + max(height(node->left),
               height(node->right));
  int balanceFactor = getBalanceFactor(node);
  if (balanceFactor > 1) {
    if (key < node->left->key) {
      return rightRotate(node);
    } else if (key > node->left->key) {
      node->left = leftRotate(node->left);
      return rightRotate(node);
    }
  }
  if (balanceFactor < -1) {
    if (key > node->right->key) {
      return leftRotate(node);
    } else if (key < node->right->key) {
      node->right = rightRotate(node->right);
      return leftRotate(node);
    }
  }
  return node;
}

// Node with minimum value
Node *nodeWithMimumValue(Node *node) {
  Node *current = node;
  while (current->left != NULL)
    current = current->left;
  return current;
}

// Delete a node
Node *deleteNode(Node *root, int key) {
  // Find the node and delete it
  if (root == NULL)
    return root;
  if (key < root->key)
    root->left = deleteNode(root->left, key);
  else if (key > root->key)
    root->right = deleteNode(root->right, key);
  else {
    if ((root->left == NULL) ||
      (root->right == NULL)) {
      Node *temp = root->left ? root->left : root->right;
      if (temp == NULL) {
        temp = root;
        root = NULL;
      } else
        *root = *temp;
      free(temp);
    } else {
      Node *temp = nodeWithMimumValue(root->right);
      root->key = temp->key;
      root->right = deleteNode(root->right,
                   temp->key);
    }
  }

  if (root == NULL)
    return root;

  // Update the balance factor of each node and
  // balance the tree
  root->height = 1 + max(height(root->left),
               height(root->right));
  int balanceFactor = getBalanceFactor(root);
  if (balanceFactor > 1) {
    if (getBalanceFactor(root->left) >= 0) {
      return rightRotate(root);
    } else {
      root->left = leftRotate(root->left);
      return rightRotate(root);
    }
  }
  if (balanceFactor < -1) {
    if (getBalanceFactor(root->right) <= 0) {
      return leftRotate(root);
    } else {
      root->right = rightRotate(root->right);
      return leftRotate(root);
    }
  }
  return root;
}

// Print the tree
void printTree(Node *root, string indent, bool last) {
  if (root != nullptr) {
    cout << indent;
    if (last) {
      cout << "R----";
      indent += "   ";
    } else {
      cout << "L----";
      indent += "|  ";
    }
    cout << root->key << endl;
    printTree(root->left, indent, false);
    printTree(root->right, indent, true);
  }
}

void avl_tree(int build_count, Node* root , int* ptr)
{
    for (int i = 0; i < build_count; i++)
    {
        root = insertNode(root, ptr[i]);
    }
    
}
void delete_avl_tree(int del_count, Node* root, int* ptr)
{
    for (int i = 0; i <  del_count/10*2; i++)
    {
        root = deleteNode(root, ptr[i]);
    }
}

int main()
{
    initialize();
    // check_initialize();

    // checking if works correctly
    Node *root = NULL;
    root = insertNode(root, 33);
    root = insertNode(root, 13);
    root = insertNode(root, 53);
    root = insertNode(root, 9);
    root = insertNode(root, 21);
    root = insertNode(root, 61);
    root = insertNode(root, 8);
    root = insertNode(root, 11);
    printTree(root, "", true);
    
    
    for (int i = 0; i < 13; i++)
    {   
        unsigned long int* build_meas = new unsigned long int[number_of_measurements];
        unsigned long int* delete_meas = new unsigned long int[number_of_measurements];
        for (int j = 0; j < number_of_measurements; j++)
        {
            int* words = new int[instances[i]];
            load_numbers(words, instances[i], data_file_name);
            
              // avl tree building time
              Node *root = NULL;
              chrono::steady_clock::time_point begin = chrono::steady_clock::now();
              avl_tree(instances[i], root, words);
              chrono::steady_clock::time_point end = chrono::steady_clock::now();
              unsigned long int time_dif = chrono::duration_cast<chrono::microseconds>(end-begin).count();
              build_meas[j] = time_dif;

              // avl nodes delete time
              chrono::steady_clock::time_point begin_del = chrono::steady_clock::now();
              delete_avl_tree(instances[i], root, words);
              chrono::steady_clock::time_point end_del = chrono::steady_clock::now();
              unsigned long int time_dif_del = chrono::duration_cast<chrono::microseconds>(end_del-begin_del).count();
              delete_meas[j] = time_dif_del;
          
            delete[] words;
        }
        append_measure_file(measurements_file_name, algorithm, instances[i], number_of_measurements, build_meas);
        append_measure_file(measurements_file_name, algorithm+"_del", instances[i], number_of_measurements, delete_meas);
        delete[] build_meas, delete_meas;
    }
    
    
    return 0;
}


void initialize()
{
    fstream file;
    file.open("inicjalizacja.ini", ios::in);
    if (file.good() == true)
    {
        file >> data_file_name;
        for (int i = 0; i < 13; i++)
        {
            file >> instances[i];
        }
        file >> number_of_measurements;
        file >> measurements_file_name;
        // file >> algo_choice;
    }
    else
    {
        cout<<"Problem with reading .ini file"<<endl;
        exit(-1);
    }
    file.close();

    algorithm = "avl_tree";
    create_mesurements_file(measurements_file_name, number_of_measurements, algorithm);
    create_mesurements_file(measurements_file_name, number_of_measurements, algorithm+"_del");
}

void check_initialize()
{
    cout<<"Cheking initialize"<<endl;
    cout<<data_file_name<<endl;
    for (int i = 0; i < 13; i++)
    {
        cout << instances[i]<<endl;
    }
    cout << number_of_measurements << endl;
    cout << measurements_file_name << endl;
    // cout << algo_choice << endl;
}

void read_words(string file_name, int quantity_of_words, string* words)
{
    fstream file;
    file.open(file_name, ios::in);
    if (file.good() == true)
    {
        for (int i = 0; i < quantity_of_words; i++)
        {
            file >> words[i];
        }
    }
    else
    {
        cout<<"Problem with reading words from "<<data_file_name<<endl;
        exit(-1);
    }
    file.close();
}

void print_words(int quantity_of_words, string* words)
{
    for (int i = 0; i < quantity_of_words; i++)
    {
        cout << i+1 << ".\t" << words[i] << endl;
    }
}

void load_numbers(int* ptr, int quantity_of_num, string file_name)
{
    ifstream file;
    file.open(file_name, ios::in);
    if(file.good() == true)
    {
        for(int i=0; i<quantity_of_num; i++)
        {
            string buff;
            int conversion;
            getline(file, buff, ',');
            conversion=stoi(buff);
            ptr[i]=conversion; // konwersja string do int
        }
    }
    else
    {
        cout<<"Problem with loading numbers"<<endl;
        exit(-1);
    }
    file.close();
}
void print_numbers(int* ptr, int quantity_of_numbers)
{
    for (int i = 0; i < quantity_of_numbers; i++)
    {
        cout<<i+1<<".\t"<<ptr[i]<<endl;
    }
    
}

void create_mesurements_file(string file_name, int number_of_measures, string alg)
{
    fstream file;
    file.open(file_name+"_"+alg+".csv", ios::trunc | ios::out);
    if (file.good() == true)
    {
        file << "licznosc instancji";
        for (int i = 0; i < number_of_measures; i++)
        {
            file << "; pomiar "<<i+1;
        }
        file << endl;
    }
    else
    {
        cout<<"Problem during creation of measurements file"<<endl;
        exit(-1);
    }
    file.close();
}

void append_measure_file(string file_name, string alg, int instantion, int number_of_mesures, unsigned long int* ptr)
{
    fstream file;
    file.open(file_name+"_"+alg+".csv", ios::app);
    if (file.good() == true)
    {
        file << instantion;
        for (int i = 0; i < number_of_mesures; i++)
        {
            file << ';' << ptr[i];
        }
        file << endl;
    }
    else
    {
        cout<<"Problem with appending measurements file"<<endl;
        exit(-1);
    }

    file.close();
}