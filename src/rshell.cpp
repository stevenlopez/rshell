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

using namespace std;
using namespace boost;

int Test(char** args, bool &previous){    //pass in the command and previous
    if (strcmp(args[0], "exit") == 0){    //if exit is the command 
        exit(0);                          //then exit
    }
    
    if(previous == false){                //check if the last one was false
        return EXIT_FAILURE;              //will/should only work for &&
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
        //exit(1);
    }

    if(WIFEXITED(status)){               //always goes into here(I think so)
        const int es = WEXITSTATUS(status);  // checks what the exit was
        //cout << "ES " << es << endl;
	      if(es == 1){                               //if exit was 1 then it failed(IMPORTANT)
		        return EXIT_FAILURE;
        }
    //return EXIT_SUCCESS;
    }
return EXIT_SUCCESS;                         //else return 0 for true
}

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
       	    

void Parse(vector<string> &ParseString, int size, bool P_previous){
if(size < 1){                                       //passing in nothing = return
    return;
}


int ParseSize;                                      // will need variables for later
string connector;                                   //will hold the ;/&&/||
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
           connector = "0";                        // 0 connector
           //cout << " in 0" << endl;
        }                                           //sets connnector
            
        else if(ParseString.at(i) == ";"){          // ; connector
              connector = ";";
              //cout << " in ;" << endl;
        }
        else if(ParseString.at(i) == "&&"){         //&& connector
              connector = "&&";
              //cout << " in &&" << endl;
        }
        else if(ParseString.at(i) == "||"){         //|| connector
              connector = "||"; 
              //cout << " in ||" << endl;
        }

char** args = new char*[128];                        //creates new array to store the characters
    for(int i = 0; i < ParseSize; i++){
        char * temp = strdup(S_T_E.at(i).c_str());
        args[i] = temp;  
    }
    
    if(ParseSize > 126){                             // limit of 127 strings as one command
        cout << "INPUT TOO LARGE" << endl;
        return;
    }
    args[ParseSize] = '\0';                          // null terminating character at the end
    
    int temp = Test(args, P_previous);              //checks whether it executed or not      
    if(temp == 0){                                  // sets out boolean P_previous
        P_previous = true;
    }
    else{
        P_previous = false;
    }
    
    
        if(connector == "0"){                   //should be empty but parse will handle it
            ParseString.erase(ParseString.begin(), ParseString.begin() + i);
            
            P_previous = true;
            Parse(ParseString, ParseString.size(), P_previous);
        }   
        if(connector == "&&"){                   //&& case(only one not set to true*******)
            ParseString.erase(ParseString.begin(), ParseString.begin() + i + 1);
            Parse(ParseString, ParseString.size(), P_previous);
            
        }
        
        if(connector == "||"){                   //|| case
            ParseString.erase(ParseString.begin(), ParseString.begin() + i + 1);
            
            P_previous = true;
            Parse(ParseString, ParseString.size(), P_previous);
        }
        if(connector == ";"){                    //; case
            ParseString.erase(ParseString.begin(), ParseString.begin() + i + 1);
            
            P_previous = true;
            Parse(ParseString, ParseString.size(),  P_previous);
            
        }
        return;
}


int main(){

bool MainPrevious = true;   //allows us to run our first command
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
    int size = cmd.size();                                   //gets updated size(if changed)
    Parse(cmd, size, MainPrevious);                          //starts parsing commands
    }

return 0;
}