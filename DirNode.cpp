//
// Created by Ding Li on 4/18/18.
//

/*
 * DirNode.cpp
 *
 * Implementation for DirNode class,
 * nodes of the file structure
 *
 *
 */

#include <exception>
#include <stdexcept>
#include "DirNode.h"
using namespace std;

// Default constructor
DirNode::DirNode() {
    parent = NULL;
    name = "";
    directories.clear();
    filenames.clear();
}

// Parameterized constructor, takes a name
// for the DirNode
DirNode::DirNode(string new_name)
{
    name = new_name;
    parent = NULL;
}

// Copy constructor
DirNode::DirNode(const DirNode &other) {
    parent = other.parent;
    name = other.name;
    filenames = other.filenames;
    directories = other.directories;
}

// Assignment operator
DirNode &DirNode::operator=(const DirNode &other)
{
    directories.clear();
    filenames.clear();
    parent = NULL;
    name = "";

    parent = other.parent;
    name = other.name;
    filenames = other.filenames;
    directories = other.directories;

    return *this;
}

// Destructor
DirNode::~DirNode()
{
    directories.clear();
    filenames.clear();
    parent = NULL;
}

// Function add_file
// Inputs: string, name of the file
// Returns: void
// Does: adds the filename to the vector of all files.
void DirNode::add_file(string new_name)
{
    filenames.push_back(new_name);
}

// Function add_subdir
// Inputs: DirNode pointer
// Returns: void
// Does: adds the given DirNode to the vector
//       of all directories.
void DirNode::add_subdir(DirNode *newdir)
{
    directories.push_back(newdir);
}

// Function has_subdir
// Inputs: none, const
// Returns: bool, if size of directories vector
//          is non-zero
bool DirNode::has_subdir() const
{
    return directories.size() != 0;
}

// Function has_files
// Inputs: none, const
// Returns: bool, if size of files vector
//           is non-zero
bool DirNode::has_files() const
{
    return filenames.size() != 0;
}

// Function is_empty
// Inputs: none, const
// Returns: bool, if there are no files
//          AND not subdirs
bool DirNode::is_empty() const
{
    return (!has_files() && !has_subdir());
}

// Function num_subdirs
// Inputs: none, const
// Returns: int, the number of DirNodes in the
//          directories vector
int DirNode::num_subdirs() const
{
    return (int)directories.size();
}

// Function: num_files
// Inputs: none, const
// Returns: int the number of strings in the
//          filenames vectdor
int DirNode::num_files() const
{
    return (int)filenames.size();
}

// Function set_name
// Inputs: string
// Returns: void
// Does: sets the name of this DirNode
void DirNode::set_name(string new_name)
{
    name = new_name;
}

// Function get_name
// Inputs: none, const
// Returns: string, the name of this DirNode
string DirNode::get_name() const
{
    return name;
}

// Function get_subdir
// Input: int n
// Returns: DirNode pointer to the n-th subdir
// Throws out of range exception if necessary
DirNode *DirNode::get_subdir(int n) const
{
    if (n >= (int)directories.size()) {
        throw out_of_range("No sub dir at index:  " + to_string(n));
    }
    return directories[n];
}

// Function get_file
// Input: int n
// Returns: string, the nth file name
// Throws out of range exception if necessary
string DirNode::get_file(int n) const
{
    if (n >= (int)filenames.size()) {
        throw out_of_range("No file at index:  " + to_string(n));
    }
    return filenames[n];
}

// Function get_parent
// Input: none, const
// Returns: DirNode pointer, this object's parent
DirNode *DirNode::get_parent() const
{
    return parent;
}

// Function set_parent
// Input: DirNode pointer
// Returns: void
// Does: sets the parent of this object to ths given
//       DirNode pointer
void DirNode::set_parent(DirNode *new_parent)
{
    parent = new_parent;
}



