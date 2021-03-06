#include <iostream>
#include <string>
#include <string.h>
#include <typeinfo>
#include <boost/tokenizer.hpp>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <stack>
#include <sys/stat.h>

using namespace std;
using namespace boost;

void Print(vector<string> pts);                         //forward declarations
void Build_Paren(vector<string> &P_str, int &P_sz, int &Paren_sz);

////////////////////////////////////////////////////////////////////
int checkFlag(vector<string> &str){                     //set flag
    int flag = 0;
    if(str.at(0) == "-e"){
        flag = 1;
        str.erase(str.begin());
    }
    else if(str.at(0) == "-f"){
        flag = 2;
        str.erase(str.begin());
    }
    else if(str.at(0) == "-d"){
        flag = 3;
        str.erase(str.begin());
    }
    return flag;
}


int testFunctionality(vector<string> ParsedString, unsigned index, bool p, int con, int p_con, bool Par_p, int Par_con_p, bool in_par, int size){
if(in_par == true){                                         //checks paranthesis
    
    if((Par_p == false) && (con != 2) && (Par_con_p != 2))  //Case
    {
        return 1;   
    }
    if((Par_p == true) && (Par_con_p == 2)){                //Case
        return 1;
    }
}
   if((p == false) && (p_con != 2)){                        //Case
        return 1;             
    }
    if((p == true) && (p_con == 2)){                        //Case
      return 0;
    }
    int flag = checkFlag(ParsedString);                     //get flag
    unsigned end = ParsedString.size();
    if(index > 0){
       end = index;
    }
    // check what's in vector
    for(unsigned i = 0; i < end; ++i){
        //cout << ParsedString.at(i) << ' ';
    }

    char *path;
    //if(flag == 0){
        path = strdup((ParsedString.at(0)).c_str());
    //}
    //else{
      //  path = strdup((ParsedString.at(1)).c_str());
    //}    
    //cout << "Flag: 0/1 = e, 2 = f, 3 = D :" << flag << endl;
    struct stat s;
    if(flag == 0 || flag == 1){
        if(stat(path, &s) == 0){                      
            cout << "(TRUE)" << endl;
            return 0;
        }
        else{
            cout << "(FALSE)" << endl;
            return 1;
        }
    }
    else if(flag == 2){
        if((stat(path, &s) == 0) && (s.st_mode & S_IFREG)){     //file               
            cout << "(TRUE)" << endl;
            return 0;
        }
        else{
            cout << "(FALSE)" << endl;
            return 1;
        }
    }
    else if(flag == 3){
        if((stat(path, &s) == 0) && (s.st_mode & S_IFDIR)){    //directory
            cout << "(TRUE)" << endl;
            return 0;
        }
        else{
            cout << "(FALSE)" << endl;
            return 1;
        } 
    }
    else{
        cout << "Error" << endl;
        exit(-1);
    }
}


////////////////////////////////////////////////////////////////////

//p = previous
int execute(vector<string> s_t_e, bool p, int con, int p_con, bool Par_p, int Par_con_p, bool in_par, int size){ 
    
    char** args = new char*[128];    //creates new array to store the characters
    for(int i = 0; i < size; i++){
        char * temp = strdup(s_t_e.at(i).c_str());
        args[i] = temp;  
    }
    args[size] = '\0'; 
   
if(in_par == true){                                             //does parenthesis
    
    if((Par_p == false) && (con != 2) && (Par_con_p != 2))      //case
    {
        return EXIT_FAILURE;   
    }
    if((Par_p == true) && (Par_con_p == 2)){                    //case
        return EXIT_FAILURE;
    }
}
   if((p == false) && (p_con != 2)){                            //case
        return EXIT_FAILURE;             
    }
    if((p == true) && (p_con == 2)){                            //case
      return 0;
    }
        if (strcmp(args[0], "exit") == 0){      //if exit is the command 
        exit(0);                                //then exit
    }
    pid_t pid = fork();                         //start forking
        if (pid == -1){                         //fail to fork error
            perror("failed to fork");
            return EXIT_FAILURE;
    }
    else if(pid == 0){                          //start the process              
        if(execvp(args[0], args) == -1){        //checks to see if it failed
            perror("execvp");                   //if so output error and exit
	          exit(1);
	          return EXIT_FAILURE;
        }
    }
    int status;          
    if ( waitpid(pid, &status, 0) == -1 ){      //waitpid waits(not sure what it does)
        perror("waitpid failed");
        exit(1);
        return EXIT_FAILURE;
    }
    if(WIFEXITED(status)){                      //always goes into here(I think so)
        const int es = WEXITSTATUS(status);     // checks what the exit was
        //cout << "ES " << es << endl;
	    if(es != 0){                            //if exit was 1 then it failed(IMPORTANT)
		    return EXIT_FAILURE;
        }
    }
return EXIT_SUCCESS;                             //else return 0 for true
}


void Parse(vector<string> &P_str, int size, bool p, bool pp, int P_con, bool Par_p, int Par_con, int Par_con_p, int Par_con_n, int &Par_size, bool in_paren){
if(size < 1){                                       //passing in nothing = return
    return;
}
if((P_con == 3) && (in_paren != true)){                        //////May need to change this back, erase in paren
    cout << "RESETTING: \n";
    Par_p = true;
}
//int Par_size = Par_size;
if(Par_size <= 0){
    in_paren = false;
    Par_size = 0;
}

if(in_paren == false){
    //cout << "changing par connection: \n";
    Par_con_p = P_con; 
}
while(P_str.at(0).at(0) == '('){                        //Magical loop
    in_paren = true;
    Build_Paren(P_str, size, Par_size);                 //build the parenthesis
}

/*
if(P_str.at(0).at(0) == '('){
    //cout << "parenthesis: " << endl;
    in_paren = true;
    Build_Paren(P_str, size, Par_size);
}
*/

int P_size;                                      // will need variables for later
string connector;                                   //will hold the ;/&&/||

int P_con_p = P_con;                            //the next connector is now prev



unsigned i = 0;                                     //basic counter
vector<string> S_T_E;                               //empty vector to be filled in

while((i < P_str.size())
    && (P_str.at(i) != ";")                   //creates the string 
    && (P_str.at(i) != "||")                  //that will execute
    && (P_str.at(i) != "&&")){                //stops when connector/empty
        S_T_E.push_back(P_str.at(i));
        ++i;
        P_size = i;
    }

string SP = P_str.at(0);                       //if input is ;/&&/|| then error
    if((SP == ";") || (SP == "||") || (SP == "&&")){
        P_str.erase(P_str.begin(), P_str.end());  //delete full string 
        cout << "bash: syntax error near unexpected token '" <<  SP << "'" << endl;
        return;
    }
    
        if(i == ((P_str.size()))){            //checks the last character
           connector = "0";
           P_con = 0;                        // 0 connector
           //cout << " in 0" << endl;
        }                                           //sets connnector
        else if(P_str.at(i) == "&&"){         //&& connector
              connector = "&&";
              P_con = 1;
              //cout << " in &&" << endl;
        }
        else if(P_str.at(i) == "||"){         //|| connector
              connector = "||"; 
              P_con = 2;
              //cout << " in ||" << endl;
        }
        else if(P_str.at(i) == ";"){          // ; connector
              connector = ";";
              P_con = 3;
              //cout << " in ;" << endl;
        }




if(P_size > 126){                             // limit of 127 strings as one command
        cout << "INPUT TOO LARGE" << endl;
        return;
}

    int temp;
    unsigned index = 0;
    unsigned itr = 0;
    bool matching = false;
    bool paren1 = false;
    bool paren2 = false;
    bool if_test = true;
    bool if_paren = false;
    //cout << S_T_E.at(0) << S_T_E.at(P_size - 1) << endl;
    if(S_T_E.at(0) == "]"){
        cout << "Error: no matching bracket" << endl;
        return;
    }
    if((S_T_E.at(0) == "test") || (S_T_E.at(0) == "[")){
        vector<string> P_T_S = S_T_E;
        if(S_T_E.at(0) == "test"){
            if_test = true;
            while(index < S_T_E.size()){
                if(S_T_E.at(index) == "[" || S_T_E.at(index) == "]" ){
                    if_paren = true;
                    break;
                }
                ++index;
            }
        }
        if(S_T_E.at(0) == "["){
            if_paren = true;
            if_test = false;
            paren1 = true;
        }
        while(itr < S_T_E.size()){
            if(S_T_E.at(itr) == "]"){
                if_paren = true;
                if_test = false;
                paren2 = true;
                break;
            }
            ++itr;
        }
        if(paren1 && paren2){
            matching = true;
        }
        if( (if_test == false && matching == false) || 
            (if_test == true && if_paren == true) ){
            if(matching == false){
                cout << "Error: no matching bracket" << endl;
                return;
            }
        }
        P_T_S.erase(P_T_S.begin());
   
    temp = testFunctionality(P_T_S, 0, p, P_con, P_con_p, Par_p, Par_con_p, in_paren, P_size);
        
    }
    else{
    temp = execute(S_T_E, p, P_con, P_con_p, Par_p, Par_con_p, in_paren, P_size);  
    }
    
    pp = p;  
   
    if(temp == 0){                                  // sets out boolean p
        p = true;
    }
    else{
        p = false;
    }
    
    if(in_paren != true){                           //updates parenthesis con
        Par_con_n = P_con_p;
    }
    
    if(in_paren != true){
    //cout << "changing par previous: \n ";
        Par_p = p;
    }
        if(connector == "0"){       //should be empty but parse will handle it
            P_str.erase(P_str.begin(), P_str.begin() + i);
            if(in_paren == true){
                Par_size = Par_size - i;
                    if(Par_size <= 0){
                        Par_con_p = Par_con_n;
                        Par_con_n = 0;
                         Par_p = p;
                    }
            }
            
            p = true;
            Parse(P_str, P_str.size(), p, pp, P_con, Par_p, Par_con, Par_con_p,  Par_con_n, Par_size, in_paren);
        }   
        if(connector == "&&"){      //&& case(only one not set to true*******)
            P_str.erase(P_str.begin(), P_str.begin() + i + 1);
            if(in_paren == true){
                Par_size = Par_size - i - 1;
                    if(Par_size <= 0){
                        Par_con_p = Par_con_n;
                        Par_con_n = 1;
                        Par_p = p;
                    }
            }
            
        Parse(P_str, P_str.size(), p, pp, P_con, Par_p, Par_con, Par_con_p,  Par_con_n, Par_size, in_paren);
        }
        if(connector == "||"){                   //|| case
            P_str.erase(P_str.begin(), P_str.begin() + i + 1);
            if(in_paren == true){
                Par_size = Par_size - i - 1;
                    if(Par_size <= 0){
                        Par_con_p = Par_con_n;
                        Par_con_n = 2;
                        Par_p = p;
                    }
            }
            
            if((pp == true) && (P_con_p == 2)){
            p = true;
            }
            Parse(P_str, P_str.size(), p, pp, P_con, Par_p, Par_con, Par_con_p, Par_con_n, Par_size, in_paren);
        }
        if(connector == ";"){                    //; case
            P_str.erase(P_str.begin(), P_str.begin() + i + 1);
            if(in_paren == true){
                Par_size = Par_size - i - 1;
                    if(Par_size <= 0){
                        Par_con_p = Par_con_n;
                        Par_con_n = 3;
                         Par_p = p;
                    }
            }
            p = true;
            Parse(P_str, P_str.size(),  p, pp, P_con, Par_p, Par_con, Par_con_p, Par_con_n, Par_size, in_paren);
        }
        return;
}

//////////////////////IGNORE THIS CODE, JUST DELETES THE COMMENT AND PRINTS////////////////////////////////////
void string_check(string &s, bool &Is_Comment){//helper function for the comment delete
        for(unsigned i = 0; i < s.size(); ++i){
            char temp = s.at(i);               //takes in a string 
            if(temp == '#'){                   //compares it to the #
                Is_Comment = false;            //if true then set flag/boolean
            }
        }
}
void Delete_Comment(vector<string> &CC){       //takes in our full vector
        vector<string>::iterator it;           //iterates through the vector
        bool Comment_Checker = true;
        int i = 0;
       	for(it = CC.begin(); it != CC.end(); ++it){
       	    string test = "";
            test = *it;
            ++i;
            string str(test);                   //passes each individual string 
            string_check(test, Comment_Checker);//to our helper function
            if(Comment_Checker == false){       //deletes everything past the #
                CC.erase(CC.begin() + i - 1, CC.end());
                return;
            }
       	}
}
void Print(vector<string> pts){                  //function that prints string vector
	vector<string>::iterator it;                   //helped when doing the first steps
	    for(it = pts.begin(); it != pts.end(); ++it){
      cout << *it << " ";                      //not really needed(the print function)
      }
      cout << endl;
}

bool Prec_checker(vector<string> prec){
stack<char>  S;
	for(unsigned j = 0; j < prec.size(); ++j){
    for(unsigned i = 0; i < prec.at(j).size(); ++i){
		if(prec.at(j).at(i) == '(')
			S.push(prec.at(j).at(i));
      
		else if(prec.at(j).at(i) == ')'){
			if(S.empty())
				return false;
			else
				S.pop();
		}
    }
	}
	return S.empty() ? true:false;
}

void erase_end_paren(string &s, bool &end_par, int &B_count){
    for(unsigned i = 0; i < s.size(); ++i){
        if(s.at(i) == ')'){
            --B_count;
        }
        if(s.at(i) == '('){
            ++B_count;
        }
        if((s.at(i) == ')') && (B_count == 0)){
            s.erase(s.begin()+i);                  //may need to delete the second parameter since it deletes extra stuff
            end_par = true;
        }
    }
}

void Build_Paren(vector<string> &P_str, int &P_sz, int &Paren_sz){
string temp = P_str.at(0);              //creates the paranthesis
temp.erase(temp.begin());               //erases begining

P_str.at(0) = temp;                     //starts constructing
vector<string> change_parse;
bool build_end_par = false;
int B_count = 1;
for(int i = 0; i < P_sz; ++i)
{
    if(build_end_par == false){
        string find_end = P_str.at(i);
        erase_end_paren(find_end, build_end_par, B_count);
        change_parse.push_back(find_end);
        Paren_sz = i + 1;
    }
    else{
        string find_finish = P_str.at(i);
        change_parse.push_back(find_finish);
    }
}
P_str = change_parse;
}


//delete if it messes up                //should check for special cases
/*bool special_check(vector<string> S){
    for(int i = 0; i < S.size(); ++i){
        for(int j = 1; j < S.at(i).size(); ++j){
            if((S.at(i).at(j) == '(') && 
            ((S.at(i).at(j - 1) != ((';') || ('&') || ('|') || (' ') )))){
                cout << "WRONG INPUT: \n";
                return false;
            }
        }
    }
}*/
//////////////////////IGNORE THIS CODE, JUST DELETES THE COMMENT, CHECKS PARANTHESIS BALANCE, AND PRINTS////////////////////////////////////

int main(){

int Begin_size = 0;
vector<string> cmd;                                                             //vector to hold our string
string str;                                                                     //will simply be our input string


while(1){
    cout << "$ ";                                                               //outputs the $ every iteration
       
    cmd.erase(cmd.begin(), cmd.end());               
    getline(cin, str);                                                          //gets input from user
    char_separator<char> delim(" ", ";" "#");                                   // parameters for our input
    tokenizer< char_separator<char> > mytok(str, delim);
    
    for(tokenizer<char_separator<char> >::iterator it = mytok.begin(); it != mytok.end(); ++it){
    cmd.push_back(*it);                                                         //push to our cmd vector
    }
    
    Delete_Comment(cmd);                                                        // checks for #
    bool done = Prec_checker(cmd);                                              //makes sure even number of precedence
    if(done == false){
        cout << "unmatched paranthesis: " << endl;
        cmd.erase(cmd.begin(), cmd.end());
    }
    
    Parse(cmd, cmd.size(), 1, 0, 0, 1, 0, 0, 0, Begin_size, 0);                          //starts parsing commands
}
return 0;
}


