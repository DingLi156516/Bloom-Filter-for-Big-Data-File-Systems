//
// Created by Ding Li on 4/18/18.
//

#ifndef BF_PROJECT_DIRNODE_H
#define BF_PROJECT_DIRNODE_H

/*
 * DirNode.h
 *
 * Interface for DirNode class,
 * nodes that make up the n-ary file tree
 *
 *
 */


#include <vector>
#include <string>
using namespace std;

#ifndef DIRNODE_H
#define DIRNODE_H

class DirNode {

public:

    DirNode();
    DirNode(string);

    // Rule of Three
    DirNode(const DirNode &);
    DirNode& operator = (const DirNode &);
    ~DirNode();

    void add_file(string);
    void add_subdir(DirNode *);
    bool has_subdir() const;
    bool has_files() const;
    bool is_empty() const;

    int num_subdirs() const;
    int num_files() const;

    void set_name(string);
    string get_name() const;

    DirNode* get_subdir(int) const;
    string get_file(int) const;

    DirNode* get_parent() const;
    void set_parent(DirNode*);

private:

    vector<DirNode *> directories;
    vector<string> filenames;

    string name;
    DirNode *parent;
};


#endif


#endif //BF_PROJECT_DIRNODE_H
