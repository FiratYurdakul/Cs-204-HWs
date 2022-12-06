//
//  yeni.cpp
//  the 3
//
//  Created by Fırat Yurdakul on 10.11.2022.
//

#include <iostream>
#include <string>
#include <sstream>
#include <list>

#include "activity_bst.h"




using namespace std;
string fill_with_zeros(int num_zeros, const string& input){
   int zeros_to_add = num_zeros - input.length();
   if (zeros_to_add < 0) zeros_to_add = 0;
   return string(zeros_to_add, '0') + input;
}
string number_to_time(int number){
   
    return fill_with_zeros(2, to_string(number/100))+":"+ fill_with_zeros(2,
   to_string(number%100));
}

bool inputcheker(int time){
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


void add_activity(tree_node *&root, int time, const string &activity){
    
    if(inputcheker(time) == false ){
        cout<<"ERROR! Could not add '"<<activity<<"' at specific time due to illegal time"<<endl;
        return;
    }
    
    if (!root){
        root = new tree_node(time, activity);
        cout<<"Added activity '"<<activity <<"' at " << number_to_time(time)<<endl;    }
    else{
        tree_node *nodeparentptr;
        tree_node *nodeptr;
        nodeptr = root;
            while(nodeptr){
                if(time < nodeptr->time){
                    if(nodeptr->left){// if given time is smaller than the nodeptr's time we searh the if there is node or note if there is we go left afterthat back to while loop when it will no node we add to right place in our tree
                        nodeptr = nodeptr->left;
                    }
                    else{//so we find the correct space for our value in tree and we are adding
                        nodeparentptr = nodeptr;
                        nodeptr->left = new tree_node(time, activity);
                        nodeptr->parent = nodeparentptr;
                        cout<<"Added activity '"<<activity <<"' at " << number_to_time(time)<<endl;

                        break;
                    }
                }
                else if(time > nodeptr->time){//if given time is bigger than the nodeptr's time we searh the if there is node or note if there is we go right afterthat back to while loop when it will no node we add to right place in our tree
                    if(nodeptr->right)
                        nodeptr= nodeptr->right;
                    else{
                        nodeptr->right = new tree_node(time, activity);
                        nodeparentptr = nodeptr;
                        nodeptr = nodeptr->right;
                        nodeptr->parent = nodeparentptr;
                        cout<<"Added activity '"<<activity <<"' at " << number_to_time(time)<<endl;                        break;
                    }
                }
                
            }
    }

}
// Print the name of the activity occurring at time 'time'
void print_activity(tree_node *root, int time){//
    
    tree_node *nodeparentptr;
    tree_node *nodeptr;
    nodeptr = root;
    
    if(inputcheker(time) == false){
        cout<<"ERROR! Could not print '"<<nodeptr->activity<<"' at specific time due to illegal time"<<endl;
        return;
    }
    
    if (nodeptr == nullptr){
        cout<<"Time: "<<number_to_time(time)<<", Activity: free"<<endl;
        
    }
            while(nodeptr ){
                if(time < nodeptr->time){
                    if(nodeptr->left == nullptr){//if we are in smallest part in the tree
                        if (time < nodeptr->time ){// if the given value is smaller then the nodeptr's time value it mean we are in free time before the first activity if there is exist or not
                            cout<<"Time: "<<number_to_time(time)<<", Activity: free"<<endl;
                            break;
                        }
                        
                    }
                    if(nodeptr->left){
                        nodeparentptr = nodeptr;
                        nodeptr = nodeptr->left;
                        nodeptr->parent = nodeparentptr;
                    }
                    
                    if(time > nodeptr->time && time < nodeptr->right->time){// if the given value is in interval of this node time value
                        cout<<"Time: "<<number_to_time(time)<<", Activity: "<<nodeptr->activity<<endl;
                        break;
                    }
                    
                    if(nodeptr->left == nullptr){//if after the changing the nodeptr value we are cheking the if are in the smallest point or we just dont have the left value
                        if (time < nodeptr->time){// we are in the smallest part and the given value is smaller than nodes value
                            cout<<"Time: "<<number_to_time(time)<<", Activity: free"<<endl;
                            break;
                        }
                        if (time == nodeptr->time){//if the value is equal to the nodeptr's value
                            cout<<"Time: "<<number_to_time(time)<<", Activity: "<<nodeptr->activity<<endl;
                            break;
                        }
                    }
                }
                
                
                if(time < nodeptr->time && time > nodeptr->left->time){//for example we have 1020 and there is 1000 node which is has left(900) and right(1000) childs if we go the if after that if nodeptr will go the 1100's node so ı am cheking if it is in interval of 1000 - 1100
                    cout<<"Time: "<<number_to_time(time)<<", Activity: "<<nodeptr->left->activity<<endl;
                    break;
                }
                
                
                if(time > nodeptr->time){
                    if(nodeptr->right == nullptr) {//the activity which user going to do activty  rest of the day
                        cout<<"Time: "<<number_to_time(time)<<", Activity: "<<nodeptr->activity<<endl;
                        break;
                        }
                    
                    if(time < nodeptr->right->time){//if it is smaller than right'S value we are printing before the nodeptr's change
                        cout<<"Time: "<<number_to_time(time)<<", Activity: "<<nodeptr->activity<<endl;
                        break;
                    }
                    if(nodeptr->right){
                        nodeparentptr = nodeptr;
                        nodeptr = nodeptr->right;
                        nodeptr->parent = nodeparentptr;
                    }
                    if(nodeptr->right == nullptr) {//the activity which user going to do activty  rest of the day
                        cout<<"Time: "<<number_to_time(time)<<", Activity: "<<nodeptr->activity<<endl;
                        break;

                        }
                        
                    if(time > nodeptr->time && time < nodeptr->right->time){//if it bigger than the node's value and smaller than the right's so we printing it
                        cout<<"Time: "<<number_to_time(time)<<", Activity: "<<nodeptr->activity<<endl;
                        break;
                    }
                }
            
                
            }
}


void print_activity_and_duration(tree_node *root, int time){// ı am using two separate nodes for finding duration in the binary tree in two separate nodes in two different while nodes one for startnode and econd for endnode.
    //treenode eşit ya da küçük başlangıç
    //ikinic treemode büyük olması lazım
    tree_node* nodeptr = root;
    if(inputcheker(time) == false){
        cout<<"ERROR! Could not print '"<<nodeptr->activity<<"' at specific time due to illegal time"<<endl;
        return;
    }
    
    tree_node startnode(0, "free");//ı initilaze it time 0 and activity free because if there is no  activity in tree it should give us the time 0 and activity as free
    tree_node endnode(0, "free");// it is same like in startnode as well we initlizae time as zero because we are in 24 hour loop it should start at 00:00 and end in 24 hour later
    
    while(nodeptr){//for startnode ı search the wanted value's starting time
        if(time < nodeptr->time){
            nodeptr = nodeptr->left;
            
        }
        else if(time >= nodeptr->time){
            startnode = *nodeptr;//in there we initilizae the start time to startnode's value.
            nodeptr = nodeptr->right;
        }
    }
    nodeptr = root;//we are initilizing the nodeptr to root again we will search the biniary tree again for ending node
    while(nodeptr){
        if (time < nodeptr->time){
            endnode = *nodeptr;// we initilzing teh ending node here because we need the bigger value then the given time it will be no problem because in while loop we will find the smallest value which is bigger then the given time
            nodeptr = nodeptr->left;
        }
        else if (time >= nodeptr->time){
            nodeptr = nodeptr->right;
        }
    }
    cout << "Time period: ["<<number_to_time(startnode.time)<<" - "<<number_to_time(endnode.time)<<"]: "<<startnode.activity<< endl;
    
    
}
    
void displayinorder(tree_node *nodeptr,tree_node * root, string activity){
    if (activity == "free"){
        tree_node *tempptr = root;
        if (tempptr == nullptr){//if given activity is free ı will check if tree is empty so ı will write all free
            cout<<"Time period: [00:00 - 00:00] - free "<<endl;
            return;
        }
        
        else if (tempptr->left == nullptr && tempptr->right == nullptr){//if tree is not empty and if node's inside is empty
            cout<<"Time period: [00:00 - "<<number_to_time(tempptr->time)<<"] free"<<endl;
            return;
        }
        else{
            while(tempptr){//ı am searching for the smallest part of the tree and ı use it for the ending point of free
                if(tempptr->left == nullptr && tempptr->time != 0){
                    cout<<"Time period: [00:00 - "<<number_to_time(tempptr->time)<<"] free "<<endl;
                    return;
                }
                tempptr = tempptr->left;

            }
        }
    }
    if(nodeptr== nullptr){
        return;
    }
    displayinorder(nodeptr->left,root,activity);
    if (activity == "free" && nodeptr->left){//if given activity is free ı will check if tree and nodeptr left is not null
        tree_node *tempptr = root;
        if (tempptr == nullptr){
            cout<<"Time period: [00:00 - 00:00] - free"<<endl;
        }
        else if (tempptr->left == nullptr && tempptr->right == nullptr){
            if(tempptr->activity == ""){
                cout<<"Time period: [00:00 - 00:00] - free "<<endl;
                
            }
        }
        else{
            while(tempptr){
                tempptr = tempptr->left;
                if(tempptr == nullptr){
                    cout<<"Time period: [00:00 - "<<number_to_time(nodeptr->time)<<"] - free "<<endl;
                }
            }
        }
    }
    if (activity == nodeptr->activity){
        print_activity_and_duration(root, nodeptr->time);
    }
    displayinorder(nodeptr->right,root, activity);
}


// Print the duration of every occurrence of activity 'activity'
void print_single_activity(tree_node *root, const string &activity){
    
    displayinorder(root, root, activity);
    
}

void displayallactivities(tree_node *nodeptr){// simple inorder recursion like in our slides
    
    if(nodeptr== nullptr){
        return;
    }
    displayallactivities(nodeptr->left);
    cout<<"[" <<number_to_time(nodeptr->time)<<"]"<< " - "<< nodeptr->activity<<endl;
    displayallactivities(nodeptr->right);

    
    
}
// Print the starting time of every activity
void print_all_activities(tree_node *root){
    
    displayallactivities(root);
    
}
    
// Delete the tree pointed at by `root`
void deletepostorder(tree_node *nodeptr){
    
    if(nodeptr== nullptr){
        return;
    }
    deletepostorder(nodeptr->left);
    deletepostorder(nodeptr->right);
    delete nodeptr;
}
void delete_tree(tree_node *root){
    deletepostorder(root);
}
 

