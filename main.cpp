#include <fstream>
#include <iostream>
#include <stdio.h>
#include <sstream>

int main(){
    // take file location as full path
    // 7zip source code to uncompress and compress
    //

    // make copy of file ---------------------------------------------
    std::ifstream src("generalFile.docx", std::ios::binary);
    std::ofstream dst("moddedFile.docx", std::ios::binary);
    dst << src.rdbuf();

    // ---------------------------------------------------------------

    // rename the file to zip file------------------------------------
    dst.close(); // make sure file is closed before renaming
    if(rename("moddedFile.docx", "moddedFile.zip")){
        std::cout << "Rename Successful" << std::endl;
    };
    // ---------------------------------------------------------------

    // Open document.xml file in the zip -----------------------------
    std::ifstream src2;
    src2.open("document.xml");
    if(src2.is_open()){ std::cout << "document.xml opened" << std::endl;}
    else { std::cout << "error, document.xml could not be opened" << std::endl;}
    // ---------------------------------------------------------------


    // Read and Parse XML file ---------------------------------------
    std::string mainLine = "";
    std::string line;
    std::string Start = "<w:t>";
    std::string End = "</w:t>";
    int i = 0;
    std::getline(src2, line);
    std::getline(src2, line);
    mainLine = line;
    while(mainLine.find(Start) != std::string::npos){
        i++;
        std::cout << i << std::endl;
        std::cout << "mainLine characters: " << mainLine.size() << std::endl;
        int S = mainLine.find(Start);
        int E = mainLine.find(End);
        std::cout << "Start: "  << S << std::endl;
        std::cout << "End: " << E << std::endl;
        std::string text = mainLine.substr(S + Start.size(), E - S - Start.size());
        std::cout << "[" << text << "]" << std::endl;
        mainLine = mainLine.substr(E + End.size());
//        std::cout << "printing Mainline:\n" << mainLine << std::endl;
    }


    // use xml parser move file out, but I can't read in if the file
    // is in a zipped folder so could make a script outside that can do that
    // or use some zipping library to unzip and then zip back up.
    // ---------------------------------------------------------------

    // take job ad input
    return 0;
}
