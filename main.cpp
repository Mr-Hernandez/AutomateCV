#include <fstream>
#include <iostream>
#include <stdio.h>
#include <sstream>
#include <vector>
#include <ctime> // for getting date
#include <sstream>

std::string getTime();
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

    // Get user input for keywords replacements
    std::string businessName, location, positionTitle;
    std::cout << "Enter the Business Name: ";
    std::getline(std::cin >> std::ws, businessName);
    std::cout << "Enter location as \"City, State\":";
    std::getline(std::cin >> std::ws, location);
    std::cout << "Enter Position Title: ";
    std::getline(std::cin >> std::ws, positionTitle);

    // Open document.xml file in the zip -----------------------------
    std::ifstream src2;
    src2.open("document.xml");
    if(src2.is_open()){ std::cout << "document.xml opened" << std::endl;}
    else { std::cout << "error, document.xml could not be opened" << std::endl;}
    // ---------------------------------------------------------------


    // Read and Parse XML file ---------------------------------------
    std::string mainLine;
    std::string line;
    std::string Start = "<w:t>";
    std::string End = "</w:t>";
    int i = 0;
    while(std::getline(src2, line)){ mainLine = mainLine + line;}
    int S = 0;
    while(mainLine.find(Start, S) != std::string::npos){
        i++;
        std::cout << i << std::endl;
        std::cout << "mainLine characters: " << mainLine.size() << std::endl;
        S = mainLine.find(Start, S);
        int E = mainLine.find(End, S);
        std::cout << "Start: "  << S << std::endl;
        std::cout << "End: " << E << std::endl;

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
//        if("[Date]" == mainLine.substr(S + Start.size(), E - S - Start.size())){
//            std::cout << "Date found" << std::endl;
//            std::string Date = "March 12, 2022";
//            mainLine.erase(S + Start.size(), 6);
//            E = E - 6; // removed characters "[Date]"
//            mainLine.insert(S + Start.size(), Date);
//            E = E + Date.size();
//        }

        std::string text = mainLine.substr(S + Start.size(), E - S - Start.size());
        std::cout << "[" << text << "]" << std::endl;
        S = E + End.size(); // update position past what was read.
    }


    // use xml parser move file out, but I can't read in if the file
    // is in a zipped folder so could make a script outside that can do that
    // or use some zipping library to unzip and then zip back up.
    // ---------------------------------------------------------------

    // Call batch file to unzip file----------------------------------
    system("automatecv.bat");
    // consider using CreateProcess() to call the batch file since I
    // hear that it is better in some ways. look into it.
    // also consider making the batch file from here.
    // ---------------------------------------------------------------


    // take job ad input
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
