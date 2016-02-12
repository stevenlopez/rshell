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

int Test(char** args, bool &previous){////////////////////
    if (strcmp(args[0], "exit") == 0){
            exit(0);
    }
    
    if(previous == false){
    return EXIT_FAILURE;
    }
    pid_t pid = fork();
    if (pid == -1){
    perror("failed to fork");
    return EXIT_FAILURE;
    }
    
    
    else if(pid == 0){
            if(execvp(args[0], args) == -1){
            perror("execvp");
	    exit(1);
	    return EXIT_FAILURE;
            }
    }
    int status;
    if ( waitpid(pid, &status, 0) == -1 ) {
        perror("waitpid failed");
        exit(1);
        return EXIT_FAILURE;
        //exit(1);
    }

    if ( WIFEXITED(status) ) {
        const int es = WEXITSTATUS(status);
        cout << "ES " << es << endl;
	if(es == 1){
		return EXIT_FAILURE;
    }
    //return EXIT_SUCCESS;
}
return EXIT_SUCCESS;
}

void string_check(string &s, bool &Is_Comment){///////////////////////////////////////////////
        for(unsigned i = 0; i < s.size(); ++i){
            char temp = s.at(i);
            //string str(temp);
            //cout << "TEMP: " << temp << endl; 
            if(temp == '#'){
                Is_Comment = false;
            }
        }
}

void Delete_Comment(vector<string> &CC){//////////////////////////////////////////////
        vector<string>::iterator it;
        bool Comment_Checker = true;
        int i = 0;
       	for(it = CC.begin(); it != CC.end(); ++it){
       	    string test = "";
            test = *it;
            ++i;
            string str(test);
            string_check(test, Comment_Checker);
            if(Comment_Checker == false){
                CC.erase(CC.begin() + i - 1, CC.end());
                return;
            }
       	}
}

void Print(vector<string> pts){////////////////////////////////////////////////
	vector<string>::iterator it;
       	for(it = pts.begin(); it != pts.end(); ++it){
        cout << *it << " ";
    }
}
       	    

void Parse(vector<string> &ParseString, int size, bool P_previous){
if(size < 1){
    return;
}


int ParseSize;
string connector;
unsigned i = 0;
vector<string> S_T_E;

while((i < ParseString.size())
    && (ParseString.at(i) != ";")                   //creates the string 
    && (ParseString.at(i) != "||")                  //that will execute
    && (ParseString.at(i) != "&&")){                //stops when connector/empty
        S_T_E.push_back(ParseString.at(i));
        ++i;
        ParseSize = i;
    }

string SP = ParseString.at(0);                  //if input is ;/&&/|| then error
    if((SP == ";") || (SP == "||") || (SP == "&&")){
        ParseString.erase(ParseString.begin(), ParseString.end()); 
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

char** args = new char*[25];
    for(int i = 0; i < ParseSize; i++){
        char * temp = strdup(S_T_E.at(i).c_str());
        args[i] = temp;//temp.c_str();
        
}
    args[ParseSize] = '\0';
    
    int temp = Test(args, P_previous);
    cout << "TEMP: " << temp << endl;
    if(temp == 0){
        P_previous = true;
    }
    else{
        P_previous = false;

    }
        if(connector == "0"){                   //; case
            ParseString.erase(ParseString.begin(), ParseString.begin() + i);
            
            P_previous = true;
            Parse(ParseString, ParseString.size(), P_previous);
        }   
        if(connector == "&&"){// && P_previous != false){                   //&& case
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

bool MainPrevious = true;         //keeps the terminal running
vector<string> cmd;         //vector to hold our string
string str;
while(1){/////////////////////////////////////////////////////////
cout << "$ ";
   
cmd.erase(cmd.begin(), cmd.end()); 
getline(cin, str);          //gets input from user
char_separator<char> delim(" ", ";" "#");   // parameters for our input
tokenizer< char_separator<char> > mytok(str, delim);

for(tokenizer<char_separator<char> >::iterator it = mytok.begin(); it != mytok.end(); ++it){
cmd.push_back(*it);                                     //push to our cmd vector
}

Delete_Comment(cmd);
int size = cmd.size();
Parse(cmd, size, MainPrevious);
}////////////////////////////////////////////////////////////////////////////// 

return 0;
}
