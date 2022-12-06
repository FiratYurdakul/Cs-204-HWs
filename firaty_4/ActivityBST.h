//
//  ActivityBST.h
//  firat4.3
//
//  Created by Fİrat Yurdakul on 1.12.2022.
//

#ifndef ActivityBST_h
#define ActivityBST_h

#include <iostream>

using namespace std;
struct tree_node {
   int time;
   string activity;
   tree_node *right;
   tree_node *left;
   tree_node *parent;
   tree_node(int t, const string &a) : time(t), activity(a),
                                       right(nullptr), left(nullptr),
                                       parent(nullptr) {}
};

class ActivityBST{

public:
    ActivityBST();
    ActivityBST(const ActivityBST & copy);
    ~ActivityBST();
    void add(int time,const string activity);
    bool isempty()const;
    bool inputcheker(int time);//I am cheking input is correct or not
    void copy_helper(tree_node* &ptr);//copy constructor deep copy helper
    void delete_helper(tree_node * node);
    ActivityBST operator+(const ActivityBST &rhs )const;
    void plushelper(const tree_node * rhsnode,ActivityBST &result )const;//recursive plus operator helper
    const ActivityBST & operator=(const ActivityBST & rhs);
    ActivityBST & operator+= (const ActivityBST & rhs);
    void pluseqhelper(tree_node * rhsrootptr);
    tree_node* getroot()const;//getter function for root
private:
    tree_node* root;
};
    ostream& operator<<(ostream &out, const ActivityBST& rhs);
    void operatorhelp(ostream &out, tree_node * temp);//output operator helper
    string number_to_time(int number);
    string number_to_time(int number);
#endif
