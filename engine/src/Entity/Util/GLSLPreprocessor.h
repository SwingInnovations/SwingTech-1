//
// Created by Barry on 11/28/2016.
//

#ifndef GLSLPREPROCESSOR
#define GLSLPREPROCESSOR


#include <string>
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;



static string Process(string source) {
    vector<string> lines;

    std::string delimiter = "\n";

    size_t pos = 0;
    size_t lastPos = 0;

    string token;
    pos = source.find(delimiter, pos)+1;
    while (pos != string::npos) {
        token = source.substr(lastPos,pos-lastPos-1);
        lines.push_back(token);

        lastPos = pos;
        pos = source.find(delimiter, pos) != string::npos ? source.find(delimiter, pos) +1: source.find(delimiter, pos);

    }

    for (int i = 0; i < lines.size(); i++) {
        if (lines.at(i).find("#include") != string::npos) {

            int sourcestart = lines.at(i).find("<") + 1;
            int sourceend = lines.at(i).find(">");
            string path = lines.at(i).substr(sourcestart, sourceend - sourcestart);

            string replacment;

            std::ifstream file(path);
            std::string temp;
            if (file.is_open()){
                while (file.good())
                {
                    getline(file, temp);
                    replacment += temp+"\n";
                }
            }

            lines[i]= replacment;

        }
    }

    string result = "";
    for (int i = 0; i < lines.size(); i++)
        result += lines[i]+"\n";


    return result;
}

#endif //SWINGTECH1_GLSLPREPROCESSOR_H
