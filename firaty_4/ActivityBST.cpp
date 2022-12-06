//
//  ActivityBST.cpp
//  firat4.3
//
//  Created by Firat Yurdakul on 2.12.2022.
//

#include "ActivityBST.h"

ActivityBST::ActivityBST(){// defult constructor
    root = nullptr;
}
ActivityBST::ActivityBST(const ActivityBST & copy){// copy construcotor,it is using deep copy
    root = nullptr;
    tree_node* ptr = copy.root;
    copy_helper(ptr);
}

void ActivityBST::copy_helper(tree_node* &ptr){// I am using preorder recursion for copying binary tree
    if(ptr == nullptr){
        return;
    }
    add(ptr->time, ptr->activity);
    copy_helper(ptr->left);
    copy_helper(ptr->right);
}

void ActivityBST::delete_helper(tree_node * node){// it is a helper funciton for the delete function. I am using recursion to deleting the binary tree
    if(node == nullptr){
        return;
    }
    delete_helper(node->left);
    delete_helper(node->right);
}

ActivityBST::~ActivityBST(){//deletes the binary tree after the scope end
    
    delete_helper(this->root);
}


bool ActivityBST::inputcheker(int time){//it is a inputchker for the input froom user it is cheking by using string as a list
    string times = to_string(time);
    string numhour = "012345";
    if(time < 0 || time >= 2400){
        return false;
    }
    
    if(times.size() == 4 ){
        if(numhour.find(times[2] ) == string::npos){
            return false;
        }
    }
    if(times.size() == 2){
        if(time >= 60 && time <= 99 ){
            return false;
        }
    }
    if(times.size() == 3 ){
        if(numhour.find(times[1] ) == string::npos){
            return false;
        }
    }
    return true;
}

void  ActivityBST::add(int time,const string activity){//it is the binary search tree add function
    if (inputcheker(time) == false){
        return;
    }
    if (isempty()){
        root = new tree_node(time, activity);
    }
    else{
        tree_node *temp = root;
        while(temp){
            if(time < temp->time){
                if(temp->left){// if given time is smaller than the nodeptr's time we searh the if there is node or note if there is we go left afterthat back to while loop when it will no node we add to right place in our tree
                    temp = temp->left;
                }
                else{//so we find the correct space for our value in tree and we are adding
                    temp->left = new tree_node(time, activity);
                    break;
                }
            }

            if(time > temp->time){//if given time is bigger than the nodeptr's time we searh the if there is node or note if there is we go right afterthat back to while loop when it will no node we add to right place in our tree
                if(temp->right){
                    temp = temp->right;
                }
                else{
                    temp->right = new tree_node(time, activity);
                    break;
                }
            }
        }
    }
}
bool ActivityBST::isempty()const{return root == nullptr;}//if root is empty retrun bool type


ActivityBST ActivityBST::operator+(const ActivityBST &rhs )const{//since there is cascading rhs and lhs must be const and we need these to be constant. Since I am lhs as a constant I create a new lhs which is not a constant and I add a the right part the new left which is "result"
    ActivityBST result(*this);
    tree_node * temp = rhs.root;
    plushelper(temp,result);
    return result;

}
void ActivityBST::plushelper(const tree_node * rhsnode,ActivityBST &result )const{
    if(rhsnode == nullptr){//in this helper recursion I add rhs to the result with preorder recursion
        return;
    }

    result.add(rhsnode->time,rhsnode->activity);
    plushelper(rhsnode->left,result);
    plushelper(rhsnode->right,result);
}
const ActivityBST & ActivityBST::operator=(const ActivityBST & rhs){//in there I delete the lhs named as newlhs and I asigned lhs's root to this's root
    delete_helper(root);
    ActivityBST newlhs(rhs);
    
    this->root = newlhs.root;//
    return *this;
}
    
ActivityBST & ActivityBST:: operator+= (const ActivityBST & rhs){// in this function I only take rhs as a constant because I will do chainging on lhs object after that I send the rhs's temp to the helper function to add lhs object which is this and return this
    tree_node * temp = rhs.root;
    pluseqhelper(temp);
    return *this;
}

void ActivityBST::pluseqhelper(tree_node * rhsrootptr){
    if(rhsrootptr == nullptr){
        return;
    }

    (*this).add(rhsrootptr->time,rhsrootptr->activity);
    pluseqhelper(rhsrootptr->left);
    pluseqhelper(rhsrootptr->right);
}
tree_node* ActivityBST::getroot()const{
    
    return root;
}

string fill_with_zeros(int num_zeros, const string& input){
   int zeros_to_add = num_zeros - input.length();
   if (zeros_to_add < 0) zeros_to_add = 0;
   return string(zeros_to_add, '0') + input;
}
string number_to_time(int number){
    return fill_with_zeros(2, to_string(number/100))+":"+ fill_with_zeros(2,
   to_string(number%100));
}

ostream& operator<<(ostream &out, const ActivityBST& rhs){//I will use helper recursion function to outputing the binary tree
    tree_node * temp = rhs.getroot();
    operatorhelp(out, temp);
    return out;
}
 void operatorhelp(ostream &out, tree_node * temp){//I use in order recursion to output
    if(temp == nullptr){
        return;
    }
    operatorhelp(out,temp->left);
    out<< "["<<number_to_time(temp->time)<< "] - "<< temp->activity<<endl;
    operatorhelp(out,temp->right);

}



