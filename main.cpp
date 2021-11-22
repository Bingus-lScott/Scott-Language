#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

int main(){
    map<int, pair<string, string>> tokens{};

    // File Buisness

    cout << "Enter full file path here: ";
    char fPath[100];
    cin.getline(fPath, sizeof(fPath)); 

    vector<string> textLines;
    string line;
    vector<string> words{};

    ifstream inFile;
    inFile.open(fPath);
    
    if(inFile.fail()){
        cerr << "Error Opening File" << endl;
        exit(1);
    }

    // The lexing will be done in here -----------------------------------------------------------------------------------------------------------------------

    // Adds all lines in text file to vector
    while(getline(inFile, line))
    {
        // store each line as vector element
        textLines.push_back(line);
    }

    // Sorts lines in vector into individual words
    for(int i = 0; i < textLines.size(); i++)
    {
        //std::cout<<textLines[i]<< " " << "|";

        string text = textLines[i];
        string delim = " ";

        size_t pos = 0;
        while ((pos = text.find(delim)) != string::npos) {
            words.push_back(text.substr(0, pos));
            text.erase(0, pos + delim.length());
        }
        if (!text.empty())
            words.push_back(text.substr(0, pos));
      //  for (const auto &str : words) {
      //      cout << str << endl;
      //  }
    }

    // Creates tokens from words
    int tempspot;
    for(int j = 0; j < words.size(); j++){

        // String Find
        if(words.at(j) == "string"){
            // Set string and string name
            tempspot = j;
            j++;
            if(words.at(j) != "\""){
                tokens[tempspot] = make_pair(words[tempspot], words[j]);
            }

            // String data assignment
            tempspot = j;
            j++;
            size_t found = words.at(tempspot).find("\"");
            if(found){
                tokens[j] = make_pair(words[tempspot], words[j]);
            } 
        }

        // Int Find
        else if(words.at(j) == "int"){
            // Set int and int name
            tempspot = j;
            j++;
            if(words.at(j) != "09"){
                tokens[tempspot] = make_pair(words[tempspot], words[j]);
            }

            // Int data assignment
            tempspot = j;
            j++;
            size_t found = words.at(tempspot).find("09");
            if(found){
                tokens[j] = make_pair(words[tempspot], words[j]);
            }
        }
    
        // Print Find
        else if(words.at(j) == "Print"){
            // Set Print and Print data
            tempspot = j;
            j++;
            if(words.at(j) != "09azAZ"){
                tokens[tempspot] = make_pair(words[tempspot], words[j]);
            }

        }

        // Nothing Found
        else{
            cout << "Error" << endl; 
        }
    }
/*
    // Prints out lexed code
    for(auto it = tokens.cbegin(); it != tokens.cend(); ++it)
    {
        cout << it -> second.first << " " << it -> second.second << std::endl;
    }
*/
// ----------------------------------------------------------------------------------------------------------------------------------------------------------

    
// Transpiler -----------------------------------------------------------------------------------------------------------------------------------------------
    vector<string> code;
    
    ofstream outFile;
    
    for(auto it = tokens.cbegin(); it != tokens.cend(); ++it){
        // Int interpreting
       if(it -> second.first == "int"){
            code.push_back("int");
            code.push_back(it -> second.second);
            code.push_back(";");
            ++it;
            code.push_back(it -> second.first);
            code.push_back("=");
            code.push_back(it -> second.second);
            code.push_back(";");
        } 
        // String interpreting
        else if(it -> second.first == "string"){
            code.push_back("string");
            code.push_back(it -> second.second);
            code.push_back(";");
            ++it;
            code.push_back(it -> second.first);
            code.push_back("=");
            code.push_back(it -> second.second);
            code.push_back(";");
        }
        // Print interpreting
        else if(it -> second.first == "Print"){
            code.push_back("cout");
            code.push_back("<<");
            code.push_back(it -> second.second);
            code.push_back(";");
        }
    }

    outFile.open("temp.cpp");

    outFile << "#include <iostream>\n#include <string>\nusing namespace std;\nint main(){"; 

    for(int p = 0; p < code.size(); p++){
        outFile << " " << code.at(p) << " ";
    }

    outFile << "return 0;}";
    outFile.close();
// ----------------------------------------------------------------------------------------------------------------------------------------------------------
    // Compile and Run Code
    system("g++ temp.cpp -o temp.exe");
    system("temp.exe");

    return EXIT_SUCCESS;
}