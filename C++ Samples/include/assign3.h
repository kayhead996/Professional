#ifndef _ASSIGN3_H_
#define _ASSIGN3_H_

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "trnode.h"
#include "ldnode.h"

using namespace std;


/*
 * Constants for indexing the arg array
 */
#define FILE_IND 1
#define FILE_NAME_IND 2
#define DIR_IND 3
#define DIR_NAME_IND 4
#define DISK_IND 5
#define DISK_SIZE_IND 6
#define BLK_IND 7
#define BLK_SIZE_IND 8

/*
 * Constants for comparing the arg array
 */
const string FILE_ARG = "-f";
const string DIR_ARG = "-d";
const string DISK_ARG = "-s";
const string BLK_ARG = "-b";


string **process_args(int argc, char *argv[]);
void run_sim(string **arg_list);
ld_node *init_disk(int d_size, int b_size);
tr_node *init_dir_tree(string dir_fname);
string get_parent_from_path(string dstring, bool dir);
void init_files(string file_fname, tr_node *&dtree, ld_node *&ldisk, int b_size, int d_size, int &b_used, int &d_used);
void split(const string& s, const string& delim, vector<string>& parts);
#endif
