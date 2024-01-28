#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <cstdio> 
#include <limits>
using namespace std;

// funcion declaration
void menu();
void configuration();
void readFile (string filename);
int fileLineCount(string filename);
bool checkFileName(fstream &configfile);
vector<string> tokenizeString (string input, string delimiter);
string** initializeMap();
void displayMatrix(string** cityMap);
void displayCityMap();
void displayCloudIdx();
void displayCloudLMH();
void displayPressureIdx();
void displayPressureLMH();
void displayReport();
string checkLMH(double &value);
string checkLMH(int &value);
int checkIdx(int &value);
void deleteMap(string** delArray);
void resetData();

// static varible declaration
static int callCount = 0;
static int gridCallCount = 0;

// struct declaration
struct cityLocationStruct{
    int xPoint;
    int yPoint;
    int id;
    string value;
    int lineCount;

};
struct cloudCoverStruct{
    int xPoint;
    int yPoint;
    int value;
    int lineCount;

};
struct pressureStruct{
    int xPoint;
    int yPoint;
    int value;
    int lineCount;

};
struct coordinateStruct{
    int gridXmax;
    int gridXmin;
    int gridXsize;
    int gridYmax;
    int gridYmin;
    int gridYsize;
};

// pointer declaration
cityLocationStruct *cityLocationArray;
cloudCoverStruct *cloudCoverArray;
pressureStruct *pressureArray;
coordinateStruct *coordinatearray;



int main(){

    menu();
    resetData();
}

// Display Menu Function
void menu(){
    bool loop_menu = true;
    while (loop_menu)
    {
        int choice;
        cout << "Student ID     : 8219035" << endl;
        cout << "Student Name   : Khant Ko Ko Zaw" << endl;
        cout << "--------------------------------------" << endl;
        cout << "Welcome to Weather Information Processing System!" << endl;
        cout << "\n1)   Read in and process a configuration file" << endl;
        cout << "2)   Display city map"<< endl;
        cout << "3)   Display cloud coverage map (cloudiness index)" << endl;
        cout << "4)   Display cloud coverage map (LMH symbols)" << endl;
        cout << "5)   Display atmospheric pressure map (pressure index)" << endl;
        cout << "6)   Display atmospheric pressure map (LMH symbols)" << endl;
        cout << "7)   Show weather forecast summary report" << endl;
        cout << "8)   Quit" << endl;
        cout << "\nPlease enter your choice : ";
        cin >> choice;
        
      if(!(cin.peek() == '\n')){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << endl;
        cout << "Enter a valid option number only"<<endl;
        cout << endl;
        }else{
        switch (choice)
        {
        case 1:
            cout << "\n[ Read in and process a configuration file ]" << endl;
            configuration();
            break;
        case 2:
            cout << "2" << endl;
            displayCityMap();
            break;
        case 3:
            cout << "3" << endl;
            displayCloudIdx();
            break;
        case 4:
            cout << "4" << endl;
            displayCloudLMH();
            break;
        case 5:
            cout << "5" << endl;
            displayPressureIdx();
            break;
        case 6:
            cout << "6" << endl;
            displayPressureLMH();
            break;
        case 7:
            cout << "7" << endl;
            displayReport();
            break;
        case 8:
            cout << "8" << endl;
            cout << "Program is shuting down ...."<< endl;
            loop_menu = false;
            break;
        
        default:
            cout << endl;
            cout << "Wrong Option.Try again!!!" << endl;
            cout << endl;
            break;
        }
        }
      
    }
}

// config file read function
void configuration(){
    string configfile;
    int min;
    int max;
    int gridsize;

    cout << endl;
    cout << "Please enter your config filename : ";
    cin >> configfile;
    fstream targetFile (configfile.c_str(), fstream::in);
    bool filecheck = checkFileName(targetFile);
    if (filecheck)
    {
        return;
    }
    string aLine;
    cout << endl;
    while (getline (targetFile, aLine))
    {
        size_t pos = aLine.find(".txt");
        size_t gridPos = aLine.find("=");
        
        if (pos != string::npos){
            readFile (aLine);
        }
        else if(gridPos != string::npos){
            vector<string> tokenStringVector = tokenizeString (aLine, "=");
            vector<string> tokenStringVector1 = tokenizeString (tokenStringVector[1], "-");
            min = stoi(tokenStringVector1[0]);
            max = stoi(tokenStringVector1[1]);
            gridsize =(max-min)+1;
          
            if(gridCallCount == 0){
                coordinatearray = new coordinateStruct[1];
                coordinatearray[0].gridXmax = max;
                coordinatearray[0].gridXmin = min;
                coordinatearray[0].gridXsize = gridsize;
                cout<<endl;
                cout << "Reading in " << tokenStringVector[0] <<" : " << min << "-" << max <<"...done!"<<endl;
                gridCallCount++;
            }else if(gridCallCount == 1){
                coordinatearray[0].gridYmax = max;
                coordinatearray[0].gridYmin = min;
                coordinatearray[0].gridYsize = gridsize;
                cout << "Reading in " << tokenStringVector[0] <<" : " << min << "-" << max <<"...done!"<<endl;
                cout<<endl;
                cout << "Storing Data from input file :"<<endl;
                gridCallCount = 0;
            }
            tokenStringVector.clear();
            tokenStringVector1.clear();
        }
	}
    targetFile.ignore();
    targetFile.close();
    cout << endl;
    cout <<"All records successfully stored. Going back to main menu" <<endl;
    cout << endl;

    
}

// read a single file from config file function
void readFile(string filename){
    
    fstream targetFile (filename.c_str(), fstream::in);
    cout << "Reading file : " << filename <<"...done!"<< endl;
    string aLine;
    string coordinates;
    vector<string> tokenStringVector;
    vector<string> tokenCoordinates;
    int arrayCount = 0;
    int lineCount = fileLineCount(filename);
    if(callCount == 0){
        
        cityLocationArray = new cityLocationStruct [lineCount];
        callCount++;
        while (getline(targetFile, aLine))
    {
        tokenStringVector = tokenizeString (aLine, "-");
        coordinates = tokenStringVector[0];
        tokenCoordinates = tokenizeString (coordinates, ",");
        cityLocationArray[arrayCount].xPoint = stoi(tokenCoordinates[0]);
        cityLocationArray[arrayCount].yPoint = stoi(tokenCoordinates[1]);
        cityLocationArray[arrayCount].id = stoi(tokenStringVector[1]);
        cityLocationArray[arrayCount].value = tokenStringVector[2];
        cityLocationArray[arrayCount].lineCount = lineCount;
        arrayCount++;
        targetFile.ignore();
       
    }
    
    }else if(callCount == 1){
       
        cloudCoverArray = new cloudCoverStruct [lineCount];
        callCount++;
        while (getline(targetFile, aLine))
    {
        vector<string> tokenStringVector = tokenizeString (aLine, "-");
        string coordinates = tokenStringVector[0];
        vector<string> tokenCoordinates = tokenizeString (coordinates, ",");
        cloudCoverArray[arrayCount].xPoint = stoi(tokenCoordinates[0]);
        cloudCoverArray[arrayCount].yPoint = stoi(tokenCoordinates[1]);
        cloudCoverArray[arrayCount].value = stoi(tokenStringVector[1]);
        cloudCoverArray[arrayCount].lineCount = lineCount;
        arrayCount++;
        targetFile.ignore();
       
    }
       
    }else if (callCount == 2){
         
       pressureArray = new pressureStruct[lineCount];
       callCount=0; // reset call count
        while (getline(targetFile, aLine))
    {
        vector<string> tokenStringVector = tokenizeString (aLine, "-");
        string coordinates = tokenStringVector[0];
        vector<string> tokenCoordinates = tokenizeString (coordinates, ",");
        pressureArray[arrayCount].xPoint = stoi(tokenCoordinates[0]);
        pressureArray[arrayCount].yPoint = stoi(tokenCoordinates[1]);
        pressureArray[arrayCount].value = stoi(tokenStringVector[1]);
        pressureArray[arrayCount].lineCount = lineCount;
        arrayCount++;
        targetFile.ignore();
    }}

    tokenCoordinates.clear();
    tokenStringVector.clear();
}

// calculate the total size of file function
int fileLineCount(string filename){
    fstream targetFile (filename.c_str(), fstream::in);
    string aLine;
    int lineCount = 0;
    while (getline(targetFile, aLine)){
        lineCount++;
        targetFile.ignore();
    }
    return lineCount;
}

//config filename check
bool checkFileName(fstream &configfile){
    bool result = false;
    if (!configfile.is_open())
    {
        result = true;
        cout << endl;
        cout << "File does not exist !!!" << endl;
        cout << endl;
    }
    return result;
}

// separate string function
vector<string> tokenizeString (string input, string delimiter){
	size_t pos = 0;
	string token;
	vector<string> result;
    if(delimiter == ","){
        input.erase(remove(input.begin(), input.end(), '['), input.end());
	    input.erase(remove(input.begin(), input.end(), ']'), input.end());
	    input.erase(remove(input.begin(), input.end(), ' '), input.end());
    }
    while ((pos = input.find(delimiter)) != string::npos) 
	{
    	token = input.substr(0, pos);
    	result.push_back (token);
		input.erase(0, pos + delimiter.length());
	}

	result.push_back (input);
    return (result);
}

// initialize the coordinate
string ** initializeMap(){
    string** cityMap = new string*[coordinatearray[0].gridXsize];
    
    for (int x = coordinatearray[0].gridXmin; x < coordinatearray[0].gridXsize; ++x) {
        cityMap[x] = new string[coordinatearray[0].gridYsize];
        for (int y = coordinatearray[0].gridYmin; y < coordinatearray[0].gridYsize; ++y) {
            cityMap[x][y] = " ";
        }
    }
    return cityMap;
}

// template for display Matrix on terminal
void displayMatrix(string** cityMap){

    cout << "\n\n\n\n";
    string Border = " \t";
    for (int i = coordinatearray->gridXmin; i < coordinatearray->gridXsize+1; i++)
    {
       Border += "#\t";
    }
    cout <<Border<<endl;
    cout << "\n\n\n";
    
    for(int y =coordinatearray->gridYmax; y>=coordinatearray->gridYmin;y--){
        cout << to_string(y) + "\t#\t";
            
        for(int x =coordinatearray->gridXmin; x<coordinatearray->gridXsize;x++){
             cout <<  (cityMap)[x][y] <<"\t";
        }
        cout << "#";
        cout << "\n\n\n";
    }
    cout <<Border<<endl;
    cout << "\n\n\n";
    cout << " \t \t";
    for (int i = coordinatearray->gridXmin; i < coordinatearray->gridXsize; i++)
    {
        cout <<to_string(i)+"\t";
    }
   cout << "\n\n\n\n";

}

//Insert Data to show CityMap  
void displayCityMap(){

    if(cityLocationArray == nullptr){
        cout << endl;
        cout << "No data to display city map.Please insert data first!!" << endl;
        cout << endl;

    }else{
        string** cityMap = initializeMap();

        for (int i = 0; i < cityLocationArray->lineCount; i++)
        {
        cityMap[cityLocationArray[i].xPoint][cityLocationArray[i].yPoint] = to_string(cityLocationArray[i].id);
        }
        displayMatrix(cityMap);
        deleteMap(cityMap);

    }
}

//Insert Data to show Cloud Index
void displayCloudIdx(){

    if(cloudCoverArray == nullptr){
        cout << endl;
        cout << "No data to display cloud index.Please insert data first!!" << endl;
        cout << endl;

    }else{
    string** cityMap = initializeMap();
    int value =0;
    int* valueptr = &value;
    for (int i = 0; i < cloudCoverArray->lineCount; i++)
    {   
       *valueptr =checkIdx(cloudCoverArray[i].value);    
        cityMap[cloudCoverArray[i].xPoint][cloudCoverArray[i].yPoint] = to_string(*valueptr);
    }
    cout << "\n\n\n";
    cout << "Cloud Coverage Map (cloudiness Index )" << endl;
    cout << "\n\n\n";
    displayMatrix(cityMap);
    deleteMap(cityMap);
  
    }
}

//Insert Data to show Cloud LMH
void displayCloudLMH(){

    if(cloudCoverArray == nullptr){
        cout << endl;
        cout << "No data to display cloud LMH.Please insert data first!!" << endl;
        cout << endl;

    }else{
    string** cityMap = initializeMap();
    string value;
    string* valueptr = &value;
    for (int i = 0; i < cloudCoverArray->lineCount; i++)
    {   
        *valueptr = checkLMH(cloudCoverArray[i].value);    
        cityMap[cloudCoverArray[i].xPoint][cloudCoverArray[i].yPoint] = *valueptr;
    }
    cout << "\n\n\n";
    cout << "Cloud Coverage Map (LMH Symbols )" << endl;
    cout << "\n\n\n";
    displayMatrix(cityMap);
    deleteMap(cityMap);
    
    }
}

//Insert Data to show Pressure Index
void displayPressureIdx(){

    if(pressureArray == nullptr){
        cout << endl;
        cout << "No data to display pressure index.Please insert data first!!" << endl;
        cout << endl;

    }else{
    string** cityMap = initializeMap();
    int value =0;
    int* valueptr = &value;
    for (int i = 0; i < pressureArray->lineCount; i++)
    {   
        *valueptr =checkIdx(pressureArray[i].value);
        cityMap[pressureArray[i].xPoint][pressureArray[i].yPoint] = to_string(*valueptr);
    }
    cout << "\n\n\n";
    cout << "Atmospheric Pressure Map (Pressure Index )" << endl;
    cout << "\n\n\n";
    displayMatrix(cityMap);
    deleteMap(cityMap);
    }
}

//Insert Data to show Pressure LMH 
void displayPressureLMH(){
    if(pressureArray == nullptr){
        cout << endl;
        cout << "No data to display pressure LMH.Please insert data first!!" << endl;
        cout << endl;

    }else{
    string** cityMap = initializeMap();
    string value;
    string* valueptr = &value;
    for (int i = 0; i < pressureArray->lineCount; i++)
    { 
        *valueptr = checkLMH(pressureArray[i].value); 
        cityMap[pressureArray[i].xPoint][pressureArray[i].yPoint] = *valueptr;
    }
    cout << "\n\n\n";
    cout << "Atmospheric Pressure Map (LMH Symbols )" << endl;
    cout << "\n\n\n";
    displayMatrix(cityMap);
    deleteMap(cityMap);
   
    }
}

// Display Report Function
void displayReport(){
    // Initialize main data map
    if(cloudCoverArray == nullptr && pressureArray == nullptr && cityLocationArray == nullptr){
        cout << endl;
        cout << "No data to display report.Please insert data first!!" << endl;
        cout << endl;

    }else{
    map<pair<int, string>, set<pair<int, int>>> cityMap;
    for (int i = 0; i < cityLocationArray->lineCount; i++)
    {
        int x = cityLocationArray[i].xPoint;
        int y = cityLocationArray[i].yPoint;
        int id = cityLocationArray[i].id;
        string name = cityLocationArray[i].value;
        // Calculation to find the surrounding coordinates
        pair<int,int> cityData(x,y);
        pair<int,int> cityData1(x-1,y);
        pair<int,int> cityData2(x+1,y);
        pair<int,int> cityData3(x,y-1);
        pair<int,int> cityData4(x,y+1);
        pair<int,int> cityData5(x-1,y+1);
        pair<int,int> cityData6(x+1,y+1);
        pair<int,int> cityData7(x+1,y-1);
        pair<int,int> cityData8(x-1,y-1);
        
        cityMap[{id,name}].insert(cityData);
        if (cityData1.first <= coordinatearray->gridXmax && cityData1.second <= coordinatearray->gridYmax){
             cityMap[{id,name}].insert(cityData1);
        }
        if (cityData2.first <= coordinatearray->gridXmax && cityData2.second <= coordinatearray->gridYmax){
             cityMap[{id,name}].insert(cityData2);
        }
        if (cityData3.first <= coordinatearray->gridXmax && cityData3.second <= coordinatearray->gridYmax){
             cityMap[{id,name}].insert(cityData3);
        }
        if (cityData4.first <= coordinatearray->gridXmax && cityData4.second <= coordinatearray->gridYmax){
             cityMap[{id,name}].insert(cityData4);
        }
        if (cityData5.first <= coordinatearray->gridXmax && cityData5.second <= coordinatearray->gridYmax){
             cityMap[{id,name}].insert(cityData5);
        }
        if (cityData6.first <= coordinatearray->gridXmax && cityData6.second <= coordinatearray->gridYmax){
             cityMap[{id,name}].insert(cityData6);
        }
        if (cityData7.first <= coordinatearray->gridXmax && cityData7.second <= coordinatearray->gridYmax){
             cityMap[{id,name}].insert(cityData7);
        }
        if (cityData8.first <= coordinatearray->gridXmax && cityData8.second <= coordinatearray->gridYmax){
             cityMap[{id,name}].insert(cityData8);
        }
    }

    string** cloudMap = initializeMap();
    string** pressureMap = initializeMap();
    for (int i = 0; i < cloudCoverArray->lineCount; i++)
    {        
        cloudMap[cloudCoverArray[i].xPoint][cloudCoverArray[i].yPoint] = to_string(cloudCoverArray[i].value);
    }
    for (int i = 0; i < pressureArray->lineCount; i++)
    {        
        pressureMap[pressureArray[i].xPoint][pressureArray[i].yPoint] = to_string(pressureArray[i].value);
    }
    cout << endl;
    cout << "Weather Forecast Summary Report" << endl;
    cout << "---------------------------------";
    for (const auto& entry : cityMap) {
        double acc = 0.00;
        double ap = 0.00;
        string accLMH = "";
        string apLMH ="";
        double rain = 0;
        string rainGraphic = "";
        for (const auto& coordinates : entry.second) {
            double valueAcc = stod(cloudMap[coordinates.first][coordinates.second]);
            double valueAp = stod(pressureMap[coordinates.first][coordinates.second]);
            acc += valueAcc;
            ap += valueAp;
        }
        acc = acc / entry.second.size();
        ap = ap / entry.second.size();
        accLMH = checkLMH(acc);
        apLMH = checkLMH(ap);

        if(apLMH == "L" and accLMH == "H"){
            rain = 90.00;
            rainGraphic = "~~~~\n~~~~~\n\\\\\\\\\\";
        }else if(apLMH == "L" and accLMH == "M"){
            rain = 80.00;
            rainGraphic = "~~~~\n~~~~~\n \\\\\\\\";
        }else if(apLMH == "L" and accLMH == "L"){
            rain = 70.00;
            rainGraphic = "~~~~\n~~~~~\n \\\\\\";
        }else if(apLMH == "M" and accLMH == "H"){
            rain = 60.00;
            rainGraphic = "~~~~\n~~~~~\n \\\\";
        }else if(apLMH == "M" and accLMH == "M"){
            rain = 50.00;
            rainGraphic = "~~~~\n~~~~~\n\\";
        }else if(apLMH == "M" and accLMH == "L"){
            rain = 40.00;
            rainGraphic = "~~~~\n~~~~~";
        }else if(apLMH == "H" and accLMH == "H"){
            rain = 30.00;
            rainGraphic = "~~~\n~~~~";
        }else if(apLMH == "H" and accLMH == "M"){
            rain = 20.00;
            rainGraphic = "~~\n~~~\n \\\\\\\\";
        }else if(apLMH == "H" and accLMH == "L"){
            rain = 10.00;
            rainGraphic = "~\n~~\n \\\\\\\\";
        }
        cout << endl;
        cout << "City Name : " << entry.first.second <<endl;
        cout << "City ID   : " << entry.first.first <<endl;
        printf("Ave. Cloud Cover (ACC)   : %.2f (%s)\n", acc,accLMH.c_str());
        printf("Ave. Pressure    (Ap)    : %.2f (%s)\n", ap,apLMH.c_str());
        printf("Probability of Rain (%)  : %.2f\n",rain);
        cout<<rainGraphic<<endl;
        cout << endl;
    }
    cityMap.clear();
    }
}

//Check Data to generate LMH
string checkLMH(double &value){
    string LMH = "";

     if(value >=0.0 && value <35.0 ){
            LMH = "L";
        }else if (value>=35.0 && value <65.0)
        {
            LMH = "M";
        }else if (value >=65.0 && value <100.0)
        {
            LMH = "H";
        }
    return LMH;

}

string checkLMH(int &value){
    string LMH = "";

     if(value >=0.0 && value <35.0 ){
            LMH = "L";
        }else if (value>=35.0 && value <65.0)
        {
            LMH = "M";
        }else if (value >=65.0 && value <100.0)
        {
            LMH = "H";
        }
    return LMH;

}

//Check Data to generate Index
int checkIdx(int &value){
    int result;
    if(value >=0 && value <10 ){
            result = 0;
        }else if (value >=10 && value <20)
        {
            result= 1;
        }else if (value >=20 && value <30)
        {
           result = 2;
        }else if (value >=30 && value <40)
        {
           result = 3;
        }else if (value >=40 && value <50)
        {
           result = 4;
        }else if (value >=50 && value <60)
        {
            result = 5;
        }else if (value >=60 && value <70)
        {
           result = 6;
        }else if (value >=70 && value <80)
        {
            result = 7;
        }else if (value >=80 && value <90)
        {
            result = 8;
        }else if (value >=90 && value <100)
        {
           result = 9;
        }
    return result;
}

// delete temporary 2d array and free memory to pointer function
void deleteMap(string** delArray) {
    for (int x = 0; x < coordinatearray->gridXsize; ++x) {
        delete[] delArray[x];
    }
    delete[] delArray;
}

//reset everything
void resetData(){
    delete[] coordinatearray;
    cout << "coordinates memory deallocation...done!" << endl;

    delete[] cityLocationArray;
    cout << "city location memory deallocation...done!" << endl;
  
    delete[] cloudCoverArray;
    cout << "cloud cover memory deallocation...done!" << endl;
   
    delete[] pressureArray;
    cout << "atmospheric pressure memory deallocation...done!" << endl;
}

