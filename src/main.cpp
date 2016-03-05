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

using namespace std;
using namespace boost;



void Print(vector<string> pts);

void Build_Paren(vector<string> &P_str, int &P_sz, int &Paren_sz);
//Par_prev_prev = Par previous prev or the previous connection
// Par_prev = the next connection


int execute(vector<string> s_t_e, bool &prev, bool &prev_prev, int con, int prev_con, bool Par_prev, bool Par_prev_prev, int Par_connn, int Par_connnn_prev, int paren_size_e, bool in_paren_e, int parseSize){ 
   //pass in the command and previous
   //cout << "PAR_prev: " << Par_prev << endl;
   //cout << "PAR_prev_prev: " << Par_prev_prev << endl;
   //cout << "PAR_CONNECTION: " << Par_connnn_prev << endl;
   //cout << "connection: " << con << endl;
   char** args = new char*[128];                        //creates new array to store the characters
    for(int i = 0; i < parseSize; i++){
        char * temp = strdup(s_t_e.at(i).c_str());
        args[i] = temp;  
    }
    args[parseSize] = '\0'; 
   
   
   if(in_paren_e == true){
   //cout << "IN PAREN executing: \n";
    
    if((Par_prev == false) && (con != 2) && (Par_connnn_prev != 2))                //may need to get rid of the last condition
    {
        //cout << "FAIL 1: \n";
        return EXIT_FAILURE;   
    }
    if((Par_prev == true) && (Par_connnn_prev == 2)){        //might need just par_prev_prev
        //cout << "FAIL 2: \n";
        return EXIT_FAILURE;
    }
   }
    if((prev == false) && (con != 2) && (prev_con != 2)){                //check if the last one was false
    //cout << "FAILED normal: \n";
        return EXIT_FAILURE;              //will/should only work for &&
    }
    if((prev == true) && (prev_con == 2)){
        //cout << "FAILED normal: \n";
      return 0;//EXIT_FAILURE;
    }
        if (strcmp(args[0], "exit") == 0){    //if exit is the command 
        exit(0);                          //then exit
    }
    pid_t pid = fork();                   //start forking
        if (pid == -1){                       //fail to fork error
            perror("failed to fork");
            return EXIT_FAILURE;
    }
    else if(pid == 0){                     //start the process              
        if(execvp(args[0], args) == -1){   //checks to see if it failed
            perror("execvp");              //if so output error and exit
	          exit(1);
	          return EXIT_FAILURE;
        }
    }
    int status;          
    if ( waitpid(pid, &status, 0) == -1 ) { //waitpid waits(not sure what it does)
        perror("waitpid failed");
        exit(1);
        return EXIT_FAILURE;
    }
    if(WIFEXITED(status)){               //always goes into here(I think so)
        const int es = WEXITSTATUS(status);  // checks what the exit was
        //cout << "ES " << es << endl;
	      if(es != 0){                               //if exit was 1 then it failed(IMPORTANT)
		        return EXIT_FAILURE;
        }
    }
return EXIT_SUCCESS;                         //else return 0 for true
}
       	    
void Parse(vector<string> &ParseString, int size, bool P_previous, bool P_previous_prev, int P_conn, int P_conn_prev, bool Par_previous, bool Par_previous_prev, int Par_conn, int Par_conn_prev, int Par_conn_next, int &Paren_size, bool in_paren){
if(size < 1){                                       //passing in nothing = return
    return;
}
cout << in_paren << endl;
if((P_conn == 3) && (in_paren != true)){                        //////May need to change this back, erase in paren
    cout << "RESETTING: \n";
    Par_previous = true;
    Par_previous_prev = false;
}
int paren_size = Paren_size;
if(paren_size <= 0){
    in_paren = false;
    paren_size = 0;
}

if(in_paren == false){
    //cout << "changing par connection: \n";
    Par_conn_prev = P_conn; 
}

if(ParseString.at(0).at(0) == '('){
    //cout << "parenthesis: " << endl;
    in_paren = true;
    if(in_paren == true){
        Build_Paren(ParseString, size, paren_size);
    }    
}
//Print(ParseString);
//cout << endl;
//cout << "SIZE: " << paren_size << endl;

int ParseSize;                                      // will need variables for later
string connector;                                   //will hold the ;/&&/||

int Par_con = Par_conn_next;
int Par_con_next = Par_conn_next;

int Par_con_prev = Par_conn_prev;
    
int P_con_prev = P_conn;
int P_con;




unsigned i = 0;                                     //basic counter
vector<string> S_T_E;                               //empty vector to be filled in

while((i < ParseString.size())
    && (ParseString.at(i) != ";")                   //creates the string 
    && (ParseString.at(i) != "||")                  //that will execute
    && (ParseString.at(i) != "&&")){                //stops when connector/empty
        S_T_E.push_back(ParseString.at(i));
        ++i;
        ParseSize = i;
    }

string SP = ParseString.at(0);                       //if input is ;/&&/|| then error
    if((SP == ";") || (SP == "||") || (SP == "&&")){
        ParseString.erase(ParseString.begin(), ParseString.end());  //delete full string 
        cout << "bash: syntax error near unexpected token '" <<  SP << "'" << endl;
        return;
    }
    
        if(i == ((ParseString.size()))){            //checks the last character
           connector = "0";
           P_con = 0;                        // 0 connector
           //cout << " in 0" << endl;
        }                                           //sets connnector
        else if(ParseString.at(i) == "&&"){         //&& connector
              connector = "&&";
              P_con = 1;
              //cout << " in &&" << endl;
        }
        else if(ParseString.at(i) == "||"){         //|| connector
              connector = "||"; 
              P_con = 2;
              //cout << " in ||" << endl;
        }
        else if(ParseString.at(i) == ";"){          // ; connector
              connector = ";";
              P_con = 3;
              //cout << " in ;" << endl;
        }






if(ParseSize > 126){                             // limit of 127 strings as one command
        cout << "INPUT TOO LARGE" << endl;
        return;
    }
/*    
char** args = new char*[128];                        //creates new array to store the characters
    for(int i = 0; i < ParseSize; i++){
        char * temp = strdup(S_T_E.at(i).c_str());
        args[i] = temp;  
    }
*/
    cout << "Executing this string: \n";
    Print(S_T_E);
    cout << endl;
    cout << "END STRING: \n";
    //args[ParseSize] = '\0';                          // null terminating character at the end
    
    
    
    
    
    
    
    
    
    
    
    
    //cout << "Par previous: " << Par_previous << endl;
    //cout << "Par previous previous: " << Par_previous_prev << endl;
    int temp;
    //cout << S_T_E.at(0) << S_T_E.at(ParseSize - 1) << endl;
    if((S_T_E.at(0) == "test") || ((S_T_E.at(0) == "[") && (S_T_E.at(ParseSize - 1) == "]"))){
        cout << "Create test  case: \n";
    }
    //INERT MAGIC HERE
    else{
    temp = execute(S_T_E, P_previous, P_previous_prev, P_con, P_con_prev, Par_previous, Par_previous_prev, Par_con, Par_con_prev, paren_size, in_paren, ParseSize);              //checks whether it executed or not 
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    //bool Par_temp = P_previous_prev;                //might need to edit this
    P_previous_prev = P_previous;  
   
    if(temp == 0){                                  // sets out boolean P_previous
        P_previous = true;
    }
    else{
        P_previous = false;
    }
    //if(in_paren == true){
    //    Par_previous = P_previous;
    //}
    //else{
    //    Par_previous = Par_temp;                 //FIX HERE
    //}
    //Par_previous_prev
    
    if(in_paren != true){
        Par_con_next = P_con_prev;
    }
    
    if(in_paren != true){
    //cout << "changing par previous: \n ";
        Par_previous = P_previous;
    }
        if(connector == "0"){                   //should be empty but parse will handle it
            ParseString.erase(ParseString.begin(), ParseString.begin() + i);
            if(in_paren == true){
                paren_size = paren_size - i;
                    if(paren_size <= 0){
                        Par_con_prev = Par_con_next;
                        Par_con_next = 0;
                         Par_previous = P_previous;
                    }
            }
            //cout << Par_con_prev << " " << Par_con << " " << P_con << endl;
            
            P_previous = true;
            Parse(ParseString, ParseString.size(), P_previous, P_previous_prev, P_con, P_con_prev, Par_previous, Par_previous_prev, Par_con, Par_con_prev,  Par_con_next, paren_size, in_paren);
        }   
        if(connector == "&&"){                   //&& case(only one not set to true*******)
            ParseString.erase(ParseString.begin(), ParseString.begin() + i + 1);
            if(in_paren == true){
                paren_size = paren_size - i - 1;
                    if(paren_size <= 0){
                        Par_con_prev = Par_con_next;
                        Par_con_next = 1;
                        Par_previous = P_previous;
                    }
            }
            //cout << Par_con_prev << " " << Par_con << " " << P_con << endl;
            
            Parse(ParseString, ParseString.size(), P_previous, P_previous_prev, P_con, P_con_prev, Par_previous, Par_previous_prev, Par_con, Par_con_prev,  Par_con_next, paren_size, in_paren);
        }
        if(connector == "||"){                   //|| case
            ParseString.erase(ParseString.begin(), ParseString.begin() + i + 1);
            if(in_paren == true){
                paren_size = paren_size - i - 1;
                    if(paren_size <= 0){
                        Par_con_prev = Par_con_next;
                        Par_con_next = 2;
                        Par_previous = P_previous;
                    }
            }
            //cout << Par_con_prev << " " << Par_con << " " << P_con << endl;
            
            if((P_previous_prev == true) && (P_con_prev == 2)){
            P_previous = true;
            }
            Parse(ParseString, ParseString.size(), P_previous, P_previous_prev, P_con, P_con_prev, Par_previous, Par_previous_prev, Par_con, Par_con_prev, Par_con_next, paren_size, in_paren);
        }
        if(connector == ";"){                    //; case
            ParseString.erase(ParseString.begin(), ParseString.begin() + i + 1);
            if(in_paren == true){
                paren_size = paren_size - i - 1;
                    if(paren_size <= 0){
                        Par_con_prev = Par_con_next;
                        Par_con_next = 3;
                         Par_previous = P_previous;
                    }
            }
            //cout << Par_con_prev << " " << Par_con << " " << P_con << endl;
            
            P_previous = true;
            Parse(ParseString, ParseString.size(),  P_previous, P_previous_prev, P_con, P_con_prev, Par_previous, Par_previous_prev, Par_con, Par_con_prev, Par_con_next, paren_size, in_paren);
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

void erase_end_paren(string &s, bool &end_par){
    for(unsigned i = 0; i < s.size(); ++i){
        if(s.at(i) == ')'){
            s.erase(s.begin()+i, s.end());
            end_par = true;
        }
    }
}



void Build_Paren(vector<string> &P_str, int &P_sz, int &Paren_sz){
string temp = P_str.at(0);
temp.erase(temp.begin());

P_str.at(0) = temp;
vector<string> change_parse;
bool build_end_par = false;
for(int i = 0; i < P_sz; ++i)
{
    if(build_end_par == false){
        string find_end = P_str.at(i);
        erase_end_paren(find_end, build_end_par);
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

//////////////////////IGNORE THIS CODE, JUST DELETES THE COMMENT, CHECKS PARANTHESIS BALANCE, AND PRINTS////////////////////////////////////

int main(){

bool MainPrevious = true;   //allows us to run our first command
bool MainPrevious_prev = false;

bool Par_MainPrevious = true;   //allows us to run our first command
bool Par_MainPrevious_prev = false;

bool in_paren = false;
int Begin_size = 0;
vector<string> cmd;         //vector to hold our string
string str;                 //will simply be our input string


while(1){
    cout << "$ ";                                           //outputs the $ every iteration
       
    cmd.erase(cmd.begin(), cmd.end());               
    getline(cin, str);                                      //gets input from user
    char_separator<char> delim(" ", ";" "#");               // parameters for our input
    tokenizer< char_separator<char> > mytok(str, delim);
    
    for(tokenizer<char_separator<char> >::iterator it = mytok.begin(); it != mytok.end(); ++it){
    cmd.push_back(*it);                                     //push to our cmd vector
    }
    
    Delete_Comment(cmd);                                     // checks for #
    bool done = Prec_checker(cmd);                                       //makes sure even number of precedence
    if(done == false){
    cout << "unmatched paranthesis: " << endl;
    cmd.erase(cmd.begin(), cmd.end());
    }
    int size = cmd.size();                                   //gets updated size(if changed)
    Parse(cmd, size, MainPrevious, MainPrevious_prev, 0, 0,  Par_MainPrevious, Par_MainPrevious_prev, 0, 0, 0, Begin_size, in_paren);                          //starts parsing commands
    }

return 0;
}