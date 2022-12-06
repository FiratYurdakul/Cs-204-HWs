//
//  main.cpp
//  firaty_Yurdakul_Fırat_1
//
//  Created by Fırat Yurdakul on 10.10.2022.
//

#include <iostream>
#include <fstream>       // for ifstream
#include <cctype>        // for tolower(), isalpha()"
#include <string>
#include <vector>
#include <sstream>
#include <string>
#include <ctype.h>
#include <unistd.h>
#include <stdio.h>
using namespace std;

//by rownucheking function ı am taking the first two integer in the file and by each ı use getliine ı increment the linenum after that ı chek the line number is correct or nıt by comparing the numrows and linenum
void rownumcheking (ifstream &file, int &numrows, int &numcolumns, int &linenum, int &stoping, string &forlinenum ){
    linenum = 0;
    
    file >> numrows; file >> numcolumns;
    while(getline(file, forlinenum )){
        linenum++;//one more
        
    }
    linenum = linenum - 1;
    int rhsrow_cheker = 1;
    for(int i = 1;i < linenum ; i++ ){
        rhsrow_cheker++;
    }
    if(rhsrow_cheker != numrows){
        stoping = 1;
    }

}


void writing_error_to_output(ofstream &output_file){
    output_file.is_open();
    output_file << "Error" << endl;
    output_file.close();
}

void file_opening_checker(string &input_filename, ifstream &input_file, int &stopping){
    //cin.clear();
//    cin >>input_filename;
    input_file.open(input_filename.c_str());
    if(input_file.fail()){
        stopping = 1;
    }
    
}

int main(){
    char cwd[1024];
    chdir("/path/to/change/directory/to");
    getcwd(cwd, sizeof(cwd));
    printf("Current working dir: %s\n", cwd);

    string lhsfilename, rhsfilename,resfilename, output_name, error_output, lhsforline_num, rhsforline_num, lhslines, rhslines, reslines;
    int lhsnumrows, lhsnumcolumns,lhslinenum = 0;
    int stopping = 0;
    ifstream lhs,rhs, res, outputin_file;
    ofstream outputout_file("output.txt");
   
    
 
    lhsfilename = "/Users/gunesyurdakul/Downloads/the_1_objection/firaty_Yurdakul_Firat_1/firaty_Yurdakul_Firat_1/inputs-2/tc1/lhs.txt";
    cout << "Enter LHS matrix filename:";
    file_opening_checker(lhsfilename, lhs, stopping);
    cout << "Enter RHS matrix filename:";
    rhsfilename = "/Users/gunesyurdakul/Downloads/the_1_objection/firaty_Yurdakul_Firat_1/firaty_Yurdakul_Firat_1/inputs-2/tc1/rhs.txt";
    file_opening_checker(rhsfilename, rhs, stopping);
    cout << "Enter RES filename:";
    resfilename = "/Users/gunesyurdakul/Downloads/the_1_objection/firaty_Yurdakul_Firat_1/firaty_Yurdakul_Firat_1/inputs-2/tc1/res.txt";
    file_opening_checker(resfilename, res, stopping);
    cout << "Enter output filename:";
    
    
    
    
    //cin.clear();
    //cin >>output_name;
    output_name = "/Users/gunesyurdakul/Downloads/the_1_objection/firaty_Yurdakul_Firat_1/firaty_Yurdakul_Firat_1/inputs-2/tc1/output.txt";

    if (stopping == 1){
        writing_error_to_output(outputout_file);
        
    }
    
    rownumcheking(lhs, lhsnumrows, lhsnumcolumns, lhslinenum, stopping, lhsforline_num);
    if (stopping == 1 ){
        writing_error_to_output(outputout_file);
        
    }
    
    int rhsnumrows, rhsnumcolumns, rhsline_num = 0;
    string forrhsline_num;
    rownumcheking(rhs, rhsnumrows, rhsnumcolumns, rhsline_num, stopping, rhsforline_num);
    if (stopping == 1 ){
        writing_error_to_output(outputout_file);
        
    }
    int resnumrows, resnumcolumns, resline_num = 0;
    string forresline_num;
    
    rownumcheking(res, resnumrows, resnumcolumns, resline_num, stopping, forresline_num);
    if (stopping == 1 ){
        writing_error_to_output(outputout_file);
        
      
    }
    
    
    lhs.clear();
    
    lhs.seekg(0);
    
    vector<int> lhs_column; // vector for cheking the number in rows so we can check the column numbers are correct or not
    vector<int> lhs_numbers(2);// vector for all the numbers in lhs
    lhs_numbers[0] = lhsnumrows;
    lhs_numbers[1] = lhsnumcolumns; // ı put the column and row numbers which is given in the begining of the text, which ı took it in rownumcheking function.
    int rows_number = 0;
    while(getline(lhs, lhslines)){// I take lines of the function
        cout << lhslines;
        stringstream lhs_str_lines = stringstream(lhslines);
        int numfrom_row;
        lhs_column.push_back(rows_number);//ı am taking the column number for each column by line by getline running times and putting to column vector
        int b = 0; //b is how many number in that line
        while(lhs_str_lines >> numfrom_row){// I am taking the number from lines and putting numbers vector by pushbacking
            b++;
            lhs_column[rows_number] = b;
            lhs_numbers.push_back(numfrom_row);
        }
        rows_number++;
    }
    
    for(int i = 1; i < lhsnumrows +1; i++){
        if(lhs_column[i] != lhsnumcolumns){
            writing_error_to_output(outputout_file);
            //return 0;
        }
        
    }
    
    rhs.clear();
    rhs.seekg(0);
    vector<int> rhs_column; // vector for cheking the number in rows, so we can check the column numbers are correct or not
    vector<int> rhs_numbers(2); // vector for all the numbers in rhs
    rhs_numbers[0] = rhsnumrows;
    rhs_numbers[1] =rhsnumcolumns; // ı put the column and row numbers which is given in the begining of the text, which ı took it in rownumcheking function.
    int rhs_row_number = 0;
    while(getline(rhs, rhslines)){// I take lines of the function
        cout <<rhslines;
        stringstream rhs_str_lines = stringstream(rhslines);
        int rhs_numfrom_row;
        rhs_column.push_back(rhs_row_number);//ı am taking the column number for each column by line by getline running times and putting to column vector
        int c = 0; //c is how many number in that line
        while(rhs_str_lines >> rhs_numfrom_row){// I am taking the number from lines and putting numbers vector by pushbacking
            c++;
            rhs_numbers.push_back(rhs_numfrom_row);
            rhs_column[rhs_row_number] = c;
        }
        rhs_row_number++;
    }
    for(int i = 1; i < rhsnumrows + 1 ; i++){
        if(rhs_column[i] != 1){
            writing_error_to_output(outputout_file);
    
        }
    }
    
    
    res.clear();
    res.seekg(0);
    vector<int> rescolumn; // vector for cheking the number in rows, so we can check the column numbers are correct or not
    vector<int> resnumbers(1); // vector for all the numbers in rhs
    resnumbers.push_back(1);
    resnumbers[0] = resnumrows; resnumbers[1] = resnumcolumns;// ı put the column and row numbers which is given in the begining of the text, which ı took it in rownumcheking function.
    int resrownumber = 0;
    while(getline(res, reslines)){
        cout<< reslines;
        istringstream input(reslines);
        int res_numfrom_row;
        rescolumn.push_back(resrownumber);//ı am taking the column number for each column by line by getline running times and putting to column vector
        int c = 0; //c is how many number in that line
        while(input >> res_numfrom_row){// I am taking the number from lines and putting numbers vector by pushbacking
            c++;
            rescolumn[resrownumber] = c;
            resnumbers.push_back(res_numfrom_row);
        }
        resrownumber++;
        
        
    }
    for(int i = 1; i < resnumrows + 1; i++){//ı am cheking the if res file have just 1 column or not
        if(rescolumn[i] != 1){
            writing_error_to_output(outputout_file);
                        //return 0;
        }
        
    }

    
    int cheking_the_value = 0; // if the numbers in rhs are different from [0,9] and -1 this will be increment to 1.
    for(int i = 0; i <= lhs_numbers.size();i++ ){
        if(0 >(lhs_numbers[i]) && (lhs_numbers[i] > 9) ){
            cheking_the_value = 1;
        }
        if( lhs_numbers[i] != 1){
            cheking_the_value = 1;
        }
    }
    
    if(cheking_the_value == 1){
        writing_error_to_output(outputout_file);
        //return 0;
    }
    
    for(int i = 0; i <= rhs_numbers.size(); i++){// cheking for the if the rhs numbers are between 1 and 9
        if( 1<=(rhs_numbers[i]) && (rhs_numbers[i]) <=9 ){
        }
        else{
            writing_error_to_output(outputout_file);
            
            //return 0;
        }
    }
     
    for(int i = 0; i <= resnumbers.size(); i++){//cheking if the result numbers are bigger or equal the 1
        if( resnumbers[i] >= 1 ){
        }
        else{
            writing_error_to_output(outputout_file);
            //return 0;
        }
    }
    
    res.close();
    res.open(resfilename.c_str());
    string ressolution;
    vector<int>resvalues;
    int counter = 0;
    while(getline(res, ressolution )){// ı am taking the result file numbers as a integer like in the file for example 156,218 not like char by char
        if (counter == 0){
            counter++;
        }
        else{
            stringstream a(ressolution);
            int newressolution;
            a >> newressolution;
            resvalues.push_back(newressolution);
        }
    }
    
    int numberplaceinvector = 4;
    for(int i = 0; i < lhsnumrows ; i++){ // to shortening the code running time I am recalculating the result column by substracting with known numbers
        int sum = 0;
        for(int d= 0; d < lhsnumcolumns; d++ ){
            int lhnb =lhs_numbers[numberplaceinvector];
            if(lhnb!= -1){
                int sumation = lhnb * rhs_numbers[d+4];
                sum = sumation + sum;
                
        }
        numberplaceinvector ++;
        }
        resvalues[i] = resvalues[i] - sum;
    }
    int unkownnum = 0;
    vector<vector<int>> mat(lhsnumrows,vector<int>(lhsnumcolumns)); // here I send the -1 numbers to a matrix by exact locatin in lhs file
    for(int row = 0; row < lhsnumrows ; row++){
        for(int column = 4*(row+1); column < 4*(row+1) + lhsnumcolumns; column++ ){
            if (lhs_numbers[column] == -1){
                mat[row][(column-4)-(4*row)] = 1;
                resvalues[row] = resvalues[row] - rhs_numbers[(column-4)-(4*row)+4];
                unkownnum ++;
            }
        }
        
    }
    for(int i = 0; i < resvalues.size(); i++ ){
    
    
        
   //* This loop tries to increment of the last -1 value of the row and increse it until the 9 after it goes before the final -1 and increase it by 1 and increase it again final element of row until to 9 and it is go on. for doing this when ı increase the unkonwn ı substract from result by taking that unknown's coefficent from res_numbers after ıo break because ı can able to itarate over to same element of my vector and ı did not break in the else because in the for loop ı can decrease my unkonw to left in the row so ı can increase it.
        
        
        
    while(resvalues[i] != 0){
        int index;
        for(index = lhs_column.size() -1; index >= 0; index--  ){
            if(mat[i][index] != 0 && resvalues[i] != 0){
                if(mat[i][index] != 9 ){
                    mat[i][index]++;
                    resvalues[i] -= rhs_numbers[i+4];
                    break;
                }
                else{
                    mat[i][index]= 1;
                    resvalues[i]+= 8 * rhs_numbers[i+4];
                }
            }
        }
    }
            
            
    }
    
    for(int a= 0; a < lhsnumrows; ){
        for(int b= 0; b <lhsnumcolumns; b++){
            if(mat[a][b] != 0){
                outputout_file<<a;
                outputout_file<<b;
                outputout_file<<mat[a][b]<<endl;
            }
    }
        a++;
}
    
    return 0;
}

