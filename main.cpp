// Project Name: Automate CV
// Author: Mr.Hernandez
// Date: 3/15/2022
// Supported OS: Windows 10
// Developed in Code::Blocks 20.03
// gcc (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0
// Windows 10

// Description: ------------------------------------------------------
// This program searches for a docx file named "cv_template.docx" in
// the same directory as the .exe file. It unzips it and reads in the
// document.xml file in the unzipped folder's word subdirectery. Then
// it searches for all text between <w:t> and </w:t> and if the only
// text between a pair of these delimiters matches a keyword
// (including the brackets), then it replaces that keyword with the
// appropriate string. We get the string at the start of the program
// by getting user input.
// -------------------------------------------------------------------

#include <fstream>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <ctime>
#include <sstream>

std::string getTime();
int main(){

    // Get user input for keywords replacements ----------------------
    std::string businessName, location, positionTitle, outputName;
    std::cout << "Enter the output name of the document: ";
    std::getline(std::cin >> std::ws, outputName);
    std::cout << "Enter the Business Name: ";
    std::getline(std::cin >> std::ws, businessName);
    std::cout << "Enter location as \"City, State\":";
    std::getline(std::cin >> std::ws, location);
    std::cout << "Enter Position Title: ";
    std::getline(std::cin >> std::ws, positionTitle);
    // ---------------------------------------------------------------


    // make copy of file ---------------------------------------------
    std::ifstream src("cv_template.docx", std::ios::binary);
    std::ofstream dst("moddedFile.zip", std::ios::binary);
    dst << src.rdbuf();
    src.close();
    // ---------------------------------------------------------------


    // rename the file to zip file------------------------------------
    dst.close(); // make sure file is closed before renaming
    if(rename("moddedFile.docx", "moddedFile.zip")){
        std::cout << "Rename Successful" << std::endl;
    };
    // ---------------------------------------------------------------


    // Call batch file to unzip file----------------------------------
    system("unzipper.bat");
    // consider using CreateProcess() to call the batch file since I
    // hear that it is better in some ways. look into it.
    // also consider making the batch file from here.
    // ---------------------------------------------------------------

    // Open document.xml file in the zip -----------------------------
    std::ifstream src2;
    src2.open("moddedFile/word/document.xml");
    if(src2.is_open()){ std::cout << "document.xml opened" << std::endl;}
    else { std::cout << "error, document.xml could not be opened" << std::endl;
        return 0;}
    // ---------------------------------------------------------------


    // Read and Parse XML file ---------------------------------------
    std::string mainLine;
    std::string line;
    std::string Start = "<w:t>";
    std::string End = "</w:t>";
    while(std::getline(src2, line)){ mainLine = mainLine + line;}
    int S = 0;
    while(mainLine.find(Start, S) != std::string::npos){
        S = mainLine.find(Start, S);
        int E = mainLine.find(End, S);

        std::vector<std::string> keywords;
        keywords.push_back("[Date]");
        keywords.push_back("[Business Name]");
        keywords.push_back("[City], [State]");
        keywords.push_back("[Position Title]");

        for(auto itr: keywords){
            if(itr == mainLine.substr(S + Start.size(), E - S - Start.size())){
                std::cout << itr << " found" << std::endl;
                std::string stringInsert;
                if("[Date]" == itr){
                    stringInsert = getTime();
                }
                else if("[Business Name]" == itr){
                    stringInsert = businessName;
                }
                else if("[City], [State]" == itr){
                    stringInsert = location;
                }
                else if("[Position Title]" == itr){
                    stringInsert = positionTitle;
                }
                mainLine.erase(S + Start.size(), itr.size());
                E = E - itr.size(); // removed characters "[Date]" or w/e
                mainLine.insert(S + Start.size(), stringInsert);
                E = E + stringInsert.size();
            }
        }
        S = E + End.size(); // update position past what was read.
    }
    src2.close();
    // ---------------------------------------------------------------


    // Create output file --------------------------------------------
    if(std::remove("moddedFile/word/document.xml") != 0){
        std::cout << "error deleting document.xml" << std::endl;
    }
    std::ofstream outFile;
    outFile.open("moddedFile/word/document.xml");
    outFile << mainLine;
    outFile.close();
    // ---------------------------------------------------------------


    // Zip the file back up to get a zip folder-----------------------
    std::remove("moddedFile.zip");
    system("zipper.bat");
    // ---------------------------------------------------------------


    // Rename the new zip to docx ------------------------------------
    outputName = outputName + ".docx";
    char* cOutputName = &outputName[0];
    std::remove(cOutputName);
    if(rename("moddedFile.zip", cOutputName)){
    std::cout << "Rename Successful" << std::endl;
    };
    // ---------------------------------------------------------------

    std::cout << "Process Complete" << std::endl;
    return 0;
}

// Return the date as string in form "month day, year"
std::string getTime(){
    time_t now = time(0);
    char* d = ctime(&now);
    std::string dt(d);
    std::string day, month, year;
    std::stringstream word(dt);
    word >> month;
    word >> month;
    word >> day;
    word >> year;
    word >> year;

    if("Jan" == month){ month = "January";}
    else if("Feb" == month){ month = "February";}
    else if("Mar" == month){ month = "March";}
    else if("Apr" == month){ month = "April";}
    else if("Jun" == month){ month = "June";}
    else if("Jul" == month){ month = "July";}
    else if("Aug" == month){ month = "August";}
    else if("Sep" == month){ month = "September";}
    else if("Oct" == month){ month = "October";}
    else if("Nov" == month){ month = "November";}
    else if("Dec" == month){ month = "December";}

    return (month + " " + day + ", " + year);

}
