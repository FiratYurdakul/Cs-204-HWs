//Fırat Yurdakul 29170



#include "sparse_matrix_2d_linked_list.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;
row_node* read_matrix(const string& filename, int& num_rows, int& num_columns){
    ifstream input;
    string files1st_row, numbers;
    int a = 0;
    input.open(filename.c_str());
    
    row_node *head = new row_node;
    row_node *temp = head;
    cell_node *ptr;
    int getlinecheker = 0;
    int tempvariable = 1;
    int tempcondition;
    while(getline(input,files1st_row, '\n')){
        int numvariable = 0;
        if (getlinecheker == 0){//I am taking the first row of the file and initialize them to row and column numbers.
            num_rows = files1st_row[0] - '0';
            num_columns = files1st_row[2] - '0';
            tempcondition = num_columns;
        }
       
        else{
                int variable = 0;
                stringstream ss(files1st_row);
                for (int c = 0; c < num_columns; c++ ){
                    //int variable = 0;
                    ss >> numbers;
                    int num = stoi(numbers);
                    if (num != 0 && variable >= 1){//if variable is bigger or equal to 1 we will create a new node and it will be the at least second cell of the roww because our variable is taking the if we create a node before that or not
                        cell_node * newNode = new cell_node;
                        ptr->right = newNode;
                        newNode->left = ptr;
                        newNode->value = num;
                        newNode->column = c;
                        ptr = newNode;
                        

                    }
                    else if(num != 0 && variable == 0){//if variable is zero it means it is the first column in row so ı create a cell_node and ı did not to anything about left pointer.
                        temp->cell = new cell_node;
                        ptr = temp->cell;
                        ptr->value = num;
                        ptr->column = c;
                        variable++;
                        
                    }
                    
                    if(num == 0){
                        
                    }


                }
                ptr-> right = nullptr;
                 if(tempvariable < tempcondition ){// Since ı create one row node in the begining ı did a if condition to create one less than numrows i there
                    row_node *nexttemp = new row_node;
                    temp->down = nexttemp;
                    temp = nexttemp ;
                }
                tempcondition--;
                
                
            //}
        }
        getlinecheker++;
    }
    
    input.close();
    return head;
    
}

void print_matrix(row_node* head, int num_rows, int num_columns){
    row_node *temp = head;
    cell_node *ptr;
    
    for(int r = 0; r < num_rows; r++){// I search in rows
        ptr = temp->cell;
        if(temp->cell == nullptr){// row is completly empty
            for(int a = 0; a < num_columns; a++){
                cout<< "0 ";
            }
            cout<<endl;
        }
        else{
            int columnfinder = 0;// for finding the column which ı go in the system which is not have zeros 
            while(ptr){
                
                int col = ptr->column - columnfinder;// col is the difference for finding how many zeros in the ow
                
                if(col != 0){// if col difference different from zero ı print that much zeros(equal to difference) 
                    for(int i = 0; i< col; i++ ){
                        cout<<"0 ";
                    }
                    cout<<ptr->value<< " ";
                }
                
                else{// if is zero ı print the value which ı have from ptr->value
                    cout<<ptr->value<< " ";
                }
                
                columnfinder = ptr->column +1;// I initiliaze the columnfinder +1 ptr's column value because ı put the columnfinder to next column
                if(ptr -> right == nullptr){//If the row is completley zero ı print column much zero
                    for(int i = 0; i < (num_columns - ptr->column - 1); i++){
                        cout << "0 ";
                    }
                }
                
                ptr = ptr->right;
                
            }

            cout<<endl;
        }
        temp = temp->down;
    }
    
}

void delete_matrix(row_node* head){
    row_node *temp = head;
    cell_node *ptr;
    
    
    while(head){
        ptr = temp->cell;
        cell_node *tempptr;
        while(ptr){
            tempptr = ptr->right;
            delete ptr;
            ptr = tempptr;
            //tempptr = ptr;
        }

        temp = head->down;
        delete head;
        head = temp;
        
    }
    
}


row_node* transpose(row_node* head, int num_rows, int num_columns){//I am going through all the values in the given matrix, ı did not going through zero values sincein the given matrix they dont exist. I am doing this process in a sequencel way, row by row.
//I take the values in the given metrix and put them in the correct row and collumn. I am putting them in the rows by putting to end and for the transpose metrix if ı take another value for that row ı add to end too so ı dont have a problem to reach them im the transpose metrix.
//However for adding to end ı need to have atleast 1 value so if the rowpointer is empty ı create a node and put the value in there
    row_node *temp = head;
    cell_node *ptr;
    row_node *newhead = new row_node;
    newhead->cell = nullptr;
    row_node *newtemp = newhead;
    int rowcounter = 0;
    for(int a = 0; a < num_columns -1; a++){// I create the new transpose metrix's row nodes and make every node's cell nullptr.
        row_node *newtemp2 = new row_node; 
        newtemp->down = newtemp2;
        newtemp = newtemp2;
        newtemp2->cell = nullptr;
    }
    
    newtemp = newhead;
    while(temp){// since all the rows' head pointing somwhere, for searching row bu row
        ptr = temp->cell;

        while(ptr){//for searching every collumn in the row
            int columnnum = ptr->column;
            int value = ptr->value;
            for(int i = 0; i < columnnum; i++){//for go the correct row in the new transpose metrix ı am doing for the each value in the row. There will be no problem because ı back to head in every value
                newtemp = newtemp->down;
            }
            
            cell_node *newptr = newtemp->cell;
            
            if(newptr == nullptr){//if row is empty ı create a new node and put the correct value in the transpose metrix.
                cell_node *newptr2 = new cell_node;
                newtemp->cell = newptr2;
                newptr2->value = value;
                newptr2->column = rowcounter;// ı increase it in the row searching while so in every row ı can initilze the column numbers of the new nodes in the transpose metrix.
                newptr2->left = nullptr;
                
            }
            else{
                while(newptr->right != nullptr){// while in transpose metrix's row is not empty ı put the correct value to end. Since in this while ı am creating the minimum the second node of that row ı initialize the left pointers too.  
                    newptr = newptr->right;
                }
                cell_node *newptr2 = new cell_node;
                newptr->right = newptr2;
                newptr2->value = value;
                newptr2->column = rowcounter;
                newptr2->left = newptr;

            }          
            newtemp = newhead;
            ptr= ptr->right;
        }
        temp = temp->down;
        rowcounter++;
        
    }
    
    return newhead;
}


bool is_symmetric(row_node* head, int num_rows, int num_columns){// If a one matrix's transpose is equal to itself(means before the transpose) it means it is symetrical so I am cheking the transpose metrix and first metrix is equal to themselfs.
    row_node* transposedmatrix = transpose(head, num_rows, num_columns);
    row_node *temp;
    row_node *transtemp;
    temp = head;
    transtemp = transposedmatrix;
    cell_node *ptr;
    cell_node *transptr;
    
    while (temp){// ı am doing while loop to check the matrices
        ptr = temp->cell;
        transptr = transtemp->cell;

        while(ptr){
            if(ptr->value == transptr->value){//if values are correct continue to while loop
                ptr = ptr->right;
                transptr = transptr->right;
            }
            else{// if the values are not equal return false
                return false;
            }

        }
        temp = temp->down;
        transtemp = transtemp->down;
        
    }


    return true;
    
}


row_node* add_matrices(row_node* left, row_node* right, int num_rows, int num_columns){// I am doing add two matrices by looking node their column number if their column number is equal, I take the values of that node and add two of them and ı put the value in the new matrix. 
//If the two cloumn numbers not equal, ı take the little node and put it in the new result metrix and ı shift pointer to the right and go on until end one of the right or left and side metrices showing something.  
    row_node *templ = left; //head
    row_node *tempr = right; //head
    cell_node *ptrl;
    cell_node *ptrr;
    cell_node *newptr;
    row_node *newhead = new row_node;
    row_node *newtemp = newhead;
    for(int a = 0; a < num_rows - 1; a++){
        row_node *newtemp2 = new row_node;
        newtemp->down = newtemp2;
        newtemp = newtemp2; 

    }
    int tempvariable = 1;
    int tempcondition = num_columns;
    newtemp = newhead;
    while(templ){
        ptrl = templ->cell;
        ptrr = tempr->cell;
        int variable = 0;
        newptr = newtemp->cell;
        while(ptrl || ptrr){//continue the while loop until both of the pointers nullptrs which means until both of the metrices' row finished
            
            
            if(ptrl == nullptr){//if left and side metrix is empty but right and side is not we take right and side's value to new metrix 
                    cell_node *newptr2 = new cell_node;
                    newptr2->value = ptrr->value;
                    newptr2->column = ptrr->column;
                    
                    if(variable >= 1){
                        newptr2->left = newptr; 
                        newptr->right = newptr2;  
                    }
                    else{
                        newtemp->cell = newptr2;
                    }


                    cout<<newptr2->value;
                    newptr = newptr2;
                    ptrr = ptrr->right;
                
            }
            else if(ptrr == nullptr){//if right and side metrix is empty but left and side is not we take right and side's value to new metrix 
                
                    cell_node *newptr2 = new cell_node;
                    newptr2->value = ptrl->value;
                    newptr2->column = ptrl->column;
                    
                    if(variable >= 1){
                        newptr2->left = newptr; 
                        newptr->right = newptr2;
                    }
                    else{
                        newtemp->cell = newptr2;
                    }
                    cout <<newptr2->value;
                    newptr = newptr2;
                    ptrl = ptrl->right;
                
            }
            else{
                if(ptrl->column == ptrr->column){//If both column numbers are equal in both right and left metrices we add both and put the value to new one
                        if(ptrl->value + ptrr->value == 0){
                        ptrl = ptrl->right;
                        ptrr = ptrr->right;
                        }
                        else {
                            cell_node *newptr2 = new cell_node;
                            newptr2->value = ptrl->value + ptrr->value;
                            newptr2->column = ptrl->column;
                            if(variable >= 1){
                                newptr2->left = newptr; 
                                newptr->right = newptr2;
                            }
                            else{
                                newtemp->cell = newptr2;
                            }
                            newptr = newptr2;
                            ptrl = ptrl->right;
                            ptrr = ptrr->right;
                        }
                     
                }
                else if(ptrl->column < ptrr->column){//If left column value is smaller than the right one we take left one value and put in the new metrix
                    
                        cell_node *newptr2 = new cell_node;
                        newptr2->value = ptrl->value;
                        newptr2->column = ptrl->column;
                        
                        if(variable >= 1){
                            newptr2->left = newptr; 
                            newptr->right = newptr2;
                        }
                        else{
                            newtemp->cell = newptr2;
                        }
                        cout<<newptr2->value;
                        newptr = newptr2;
                        ptrl = ptrl->right;
                }
                else if(ptrl->column > ptrr->column){// for the right column value is smaller than the left
                        cell_node *newptr2 = new cell_node;
                        newptr2->value = ptrr->value;
                        newptr2->column = ptrr->column;
                        if(variable >= 1){
                            newptr2->left = newptr; 
                            newptr->right = newptr2;
                        }
                        else{
                            newtemp->cell = newptr2;
                        }
                        cout << newptr2->value ;
                        newptr = newptr2;
                        ptrr = ptrr->right;
                    
                }
                
            }    
            variable++;// variable for the finding firts node in the row ı use it if ı create new cellnnode and ı check it by if
        }
        
        templ = templ->down;
        tempr = tempr->down;
        
        newtemp = newtemp->down; 
    }
    
    return newhead;
}
