//
// Created by Ding Li on 4/18/18.
//

/*
 * FSTree.cpp
 *
 * Implementation for File System Tree class.
 * N-ary tree to represent a file system
 *
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <exception>
#include <fstream>
#include <iomanip>
#include "FSTree.h"
using namespace std;


// Default constructor
FSTree::FSTree()
{
    root = NULL;
}

// Parameterized constructor
FSTree::FSTree(string root_name)
{
    root = build_tree(root_name);
    root->set_name(root_name);
}

// Copy constructor
FSTree::FSTree(const FSTree &other)
{
    root = pre_order_copy(other.root, NULL);
}

// Assignment operator
FSTree &FSTree::operator=(const FSTree &other)
{
    this->burn_tree();
    root = pre_order_copy(other.root, NULL);
    return *this;
}

// Destructor
FSTree::~FSTree() {
    burner(root);
}

// Function get_root
// Parameters: none
// Returns: pointer to DirNode
// Does: Returns the root USE WITH CAUTION
DirNode *FSTree::get_root() const
{
    return root;
}

// Function burn_tree
// Parameters: none
// Returns: void
// Does: makes first call to helper function
//       that recursively destroys the tree
void FSTree::burn_tree()
{
    burner(root);
    root = NULL;
}


// Function is_empty
// Parameters: none
// Returns: bool, if root is NULL
bool FSTree::is_empty() const
{
    return root == NULL;
}

/*
 * Non-member helper Functions
 *
 */

// Function burn_tree
// Input: pointer to current root
// Returns: void
// Does: recursively deallocates the tree
void burner(DirNode *root)
{
    if (root == NULL)
    {
        return;
    }
    for (int i = 0; i < root->num_subdirs(); i++)
        burner(root->get_subdir(i));

    delete root;
}


// Function build_tree
// Recursively builds the tree and returns the root.
// Throws an exception if the root directory could not be found.
DirNode *build_tree(string root_name)
{
    struct dirent *entry;
    DIR *dp;

    dp = opendir(root_name.c_str());
    if (dp == NULL) {
        cerr << "Could not build index, exiting.\n";
        exit(1);
    }

    /* /root/la/a/b/c/hello.c -> hello.c */
    DirNode *current_dir = new DirNode(base_name(root_name));
    vector<string> todo;

    while ((entry = readdir(dp)))
    {
        string entry_string = string(entry->d_name);

        /* Ignore hidden files */
        if (entry_string[0] != '.') {
            todo.push_back(entry_string);
        }
    }
    closedir(dp);

    for (string child_name : todo) {
        string full_path = root_name + "/" + child_name;
        if (is_file(full_path.c_str()))
        {
            current_dir->add_file(child_name);
        }
        else {
            /* NOTE: does not handle links, etc */
            DirNode *new_child = build_tree(full_path);
            new_child->set_parent(current_dir);
            current_dir->add_subdir(new_child);
        }
    }

    return current_dir;
}

// Function pre_order_copy
// Recursively copy the n-ary tree
DirNode *pre_order_copy(DirNode *curr_node, DirNode *parent_node)
{
    DirNode *new_node = new DirNode();
    new_node->set_name(curr_node->get_name());
    new_node->set_parent(parent_node);

    for (int i = 0; i < curr_node->num_files(); i++)
        new_node->add_file(curr_node->get_file(i));

    for (int i = 0; i < curr_node->num_subdirs(); i++)
        new_node->add_subdir(pre_order_copy(curr_node->get_subdir(i), new_node));

    return new_node;
}


// Function base_name
// Parameters: string reference
// Returns: string
// Does: returns the basename of the given path
//       e.g. /root/la/a/b/c/hello.c -> hello.c
string base_name(string const &path)
{
    return path.substr(path.find_last_of("/\\") + 1);
}

// Function is_file
// Parameters: char *
// Returns: bool
// Does: checks if file @ path is a a file.
//       Throws an exception if a file is invalid or if stat has an error
bool is_file(const char *path)
{
    struct stat s;
    if (stat(path,&s) == 0)
    {
        if (s.st_mode & S_IFDIR)
            return false;
        else if (s.st_mode & S_IFREG)
            return true;
        else
            throw runtime_error("Invalid file found: could not build tree");

    }
    else
    {
        throw runtime_error("stat error: could not build tree");
    }
}

// Function is_dir
// Parameters: char *
// Returns: bool
// Does: Determines if the given char * is a file
//       if not, it must be a directory!
bool is_dir(const char *path)
{
    return !is_file(path);
}

//Function print_path
//parameters: DirNode *, ofstream &
//Returns: nothing
//Does: write all file names under a directory into the input.txt
void print_path(DirNode *node, ofstream &input)
{
    if (!node->has_subdir() && node->has_files())
    {
        for (int i =0; i < node->num_files(); i++)
        {

            input << node->get_file(i)<<endl;
        }
        return;
    }
    else if (node -> has_subdir() && !node->has_files())
    {
        for (int i = 0; i < node->num_subdirs(); i++)
        {
            print_path(node->get_subdir(i), input);
        }
        return;
    }
    else if (node -> has_subdir() && node->has_files())
    {
        for (int i =0; i < node->num_files(); i++)
        {

            input << node->get_file(i)<<endl;
        }

        for (int j = 0; j < node->num_subdirs(); j++)
        {
            print_path(node->get_subdir(j), input);
        }
        return;
    }
}

//Function Get_path
//parameters: nothing
//Returns: nothing
//Does: take the user input as file path and perform the print_path function
string Get_path(){
    cout<<"Please enter the path you want to check\n";
//    string Path = "/Users/liding/Desktop/Proj2";
    string Path, Res;
    cin>>Path;
    Res = Path;
    FSTree tree(Path);

    DirNode *root = tree.get_root();
    ofstream input;
    input.open(Path.append("/metadata.txt"),ios::trunc);
//    cout<<Path<<endl;
    print_path(root, input);
    input.close();
    return Res;
}


