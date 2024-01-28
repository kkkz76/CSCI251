#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <ios>
#include <limits>
#include <algorithm>
#include <iomanip>

using namespace std;

// Coordinates Array
struct graphCoordinates
{
    int start;
    int end;
};

// Citylocation Array
struct cityLocation
{
    int cityX;
    int cityY;
    string cityId;
    string cityName;
};

// CloudCover Array
struct CloudCover
{
    int ccX;
    int ccY;
    int value;
};

// pressure Array
struct pressure
{
    int pX;
    int pY;
    int value;
};

// global var
graphCoordinates *coordinatePointer;
CloudCover *cCover;
cityLocation *city;
pressure *P;

int *citySize;
int *ccSize;
int *pSize;

// function
void heading();
void menu(bool &check);
void inputFileName();
void readFile(string filename);
void readFile(string filename, int &fileCounter);
int fileSize(string filename);
vector<string> tokenizeString(string input, string delimiter);

void displayCityMap();
void displayCCMap();
void displayCCMapS();
void displayPressureMap();
void displayPressureMapS();

void table(string **tempArray);
string **tempArray();
void deleteTempArray(string **tempArray);
int valueIndex(int &value);
string valueSB(int &value);
string valueSB(double &value);
double calValue(vector<string> specCity, string **temp);
void cloudSB(string &CC, string &AP);
vector<vector<string>> groupCity();
void displayReport();
void displaySingleCity();

// conditioncheck
bool checkFileName(fstream &inputFile);
void memoryReset();

int main()
{

    bool check = true;
    while (check)
    {
        heading();
        menu(check);
    }

    memoryReset();

    return 0;
}

void heading()
{
    cout << "StudentID\t"
         << ": 8220992" << endl;
    cout << "StudentName\t"
         << ": Nay Aung Lwin" << endl;
    cout << "---------------------------------------" << endl;
}

void menu(bool &check)
{
    cout << "Welcome to Weather Information Processing System!" << endl
         << endl;
    cout << "1)\tRead in and process a configuration file" << endl;
    cout << "2)\tDisplay city map" << endl;
    cout << "3)\tDisplay cloud coverage map (cloudiness index)" << endl;
    cout << "4)\tDisplay cloud coverage map (LMH symbols)" << endl;
    cout << "5)\tDisplay atmospheric pressure map (pressure index)" << endl;
    cout << "6)\tDisplay atmospheric pressure map (LMH symbols)" << endl;
    cout << "7)\tShow weather forcast summary report" << endl;
    cout << "8)\tSearch individual city" << endl;
    cout << "9)\tQuit" << endl
         << endl;

    bool switchCheck = false;
    int choice = 0;
    do
    {
        switchCheck = false;
        cout << "Please enter your choice: ";
        cin >> choice;
        cout << endl;

        if (cin.peek() == '\n')
        {
            switch (choice)
            {
            case 1:
                inputFileName();
                break;
            case 2:
                displayCityMap();
                break;
            case 3:
                displayCCMap();
                break;
            case 4:

                displayCCMapS();
                break;
            case 5:
                displayPressureMap();
                break;
            case 6:
                displayPressureMapS();
                break;
            case 7:
                displayReport();
                break;
            case 8:
                displaySingleCity();
                break;
            case 9:
                check = false;
                break;
            default:
                cout << "Wrong input! Try Again." << endl
                     << endl;
                switchCheck = true;
            }
        }
        else
        {
            cin.clear();                                         // buffer
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // buffer
            cout << "Wrong input! Try Again." << endl
                 << endl;
            switchCheck = true;
            continue;
        }
    } while (switchCheck);
}

void inputFileName()
{
    cin.ignore();
    cout << "[Read in and process a configuration file]" << endl;
    cout << "Please enter config filename: ";
    string filename;
    cin >> filename;
    readFile(filename);
    cout << endl;
}

void readFile(string filename)
{
    fstream inputFile(filename.c_str(), fstream::in);
    bool error = checkFileName(inputFile);
    if (error)
    {
        return;
    }

    string line;
    int fileCounter = 0;
    int coCounter = 0;

    if (coordinatePointer != nullptr)
    {
        delete[] coordinatePointer;
    }

    coordinatePointer = new graphCoordinates[2]; //[[start,end],[start,end]]
    cout << endl;

    while (getline(inputFile, line)) // 18 loop
    {
        // cout << line << endl;

        size_t commentPos = line.find("//");
        size_t equalPos = line.find("=");
        size_t txtPos = line.find(".txt");

        if (commentPos != string::npos)
        {
            continue;
        }

        else if (equalPos != string::npos)
        {
            vector<string> XYstring = tokenizeString(line, "=");
            vector<string> coordinates = tokenizeString(XYstring[1], "-");
            coordinatePointer[coCounter].start = stoi(coordinates[0]);
            coordinatePointer[coCounter].end = stoi(coordinates[1]);
            cout << "Reading in " << XYstring[0] << ": " << coordinatePointer[coCounter].start << "-" << coordinatePointer[coCounter].end << "...done!" << endl;
            coCounter++;
        }

        else if (txtPos != string::npos)
        {
            if (fileCounter == 0)
            {
                cout << endl;
                cout << "Storing data from input file:" << endl;
            }
            readFile(line, fileCounter);
            fileCounter++;
        }
    }
    cout << "All records successfully stored. Going back to main menu" << endl
         << endl;
    inputFile.close();
}

void readFile(string filename, int &fileCounter)
{

    fstream inputFile(filename.c_str(), fstream::in);

    bool error = checkFileName(inputFile);
    if (error)
    {
        return;
    }

    int arraySize = fileSize(filename);
    string line;

    int arrayIndex = 0;
    if (fileCounter == 0)
    {
        if (city != nullptr)
        {
            delete citySize;
            delete[] city;
        }
        citySize = new int(arraySize);
        city = new cityLocation[arraySize];
    }
    else if (fileCounter == 1)
    {
        if (cCover != nullptr)
        {
            delete ccSize;
            delete[] cCover;
        }
        ccSize = new int(arraySize);
        cCover = new CloudCover[arraySize];
    }
    else if (fileCounter == 2)
    {
        if (pSize != nullptr)
        {
            delete P;
            delete[] pSize;
        }
        pSize = new int(arraySize);
        P = new pressure[arraySize];
    }
    while (getline(inputFile, line))
    {
        vector<string> values = tokenizeString(line, "-");

        if (fileCounter == 0)
        {
            city[arrayIndex].cityX = stoi(values[0]);
            city[arrayIndex].cityY = stoi(values[1]);
            city[arrayIndex].cityId = values[2];
            city[arrayIndex].cityName = values[3];
        }
        else if (fileCounter == 1)
        {
            cCover[arrayIndex].ccX = stoi(values[0]);
            cCover[arrayIndex].ccY = stoi(values[1]);
            cCover[arrayIndex].value = stoi(values[2]);
        }
        else if (fileCounter == 2)
        {
            P[arrayIndex].pX = stoi(values[0]);
            P[arrayIndex].pY = stoi(values[1]);
            P[arrayIndex].value = stoi(values[2]);
        }
        inputFile.ignore();
        arrayIndex++;
    }
    inputFile.close();
    cout << filename << "...done!" << endl;
}

bool checkFileName(fstream &inputFile)
{
    bool error = false;
    if (!inputFile.is_open())
    {
        error = true;
        cout << "File does not exist or could not be opened." << endl;
    }
    return error;
}

int fileSize(string filename)
{
    int arraySize = 0;
    fstream inputFile(filename.c_str(), fstream::in);
    string line;
    while (getline(inputFile, line))
    {
        arraySize++;
        inputFile.ignore();
    }

    return arraySize;
}

vector<string> tokenizeString(string input, string delimiter)
{
    size_t pos = 0;
    string token;
    vector<string> finalResult;
    input.erase(remove(input.begin(), input.end(), '['), input.end());
    replace(input.begin(), input.end(), ',', '-');
    input.erase(remove(input.begin(), input.end(), ' '), input.end());
    input.erase(remove(input.begin(), input.end(), ']'), input.end());

    while ((pos = input.find(delimiter)) != string::npos)
    {

        token = input.substr(0, pos);
        finalResult.push_back(token);
        input.erase(0, pos + delimiter.length());
    }

    finalResult.push_back(input);
    return (finalResult);
}

string **tempArray()
{
    int rows = coordinatePointer[0].end - coordinatePointer[0].start + 1;
    int cols = coordinatePointer[1].end - coordinatePointer[1].start + 1;
    string **dynamicArray = new string *[rows];
    for (int i = 0; i < rows; i++)
    {
        dynamicArray[i] = new string[cols];
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            dynamicArray[i][j] = " ";
        }
    }
    return dynamicArray;
}

void deleteTempArray(string **tempArray)
{
    int rows = coordinatePointer[0].end - coordinatePointer[0].start + 1;

    for (int i = 0; i < rows; i++)
    {
        delete[] tempArray[i];
    }

    delete[] tempArray;
}

void table(string **tempArray)
{
    int startX = coordinatePointer[0].start;
    int startY = coordinatePointer[1].start;
    int rows = coordinatePointer[0].end - coordinatePointer[0].start + 1;
    int cols = coordinatePointer[1].end - coordinatePointer[1].start + 1;

    cout << "  ";

    for (int j = startX; j < rows + 2; j++)
    {
        cout << "# ";
    }
    cout << endl;

    for (int i = cols - 1; i >= startY; i--)
    {
        cout << i << " # ";
        for (int j = startX; j < rows; j++)
        {
            cout << tempArray[j][i]
                 << " ";
        }
        cout << "# ";

        cout << endl;
    }

    cout << "  ";
    for (int j = startX; j < rows + 2; j++)
    {
        cout << "# ";
    }
    cout << endl;
    cout << "    ";
    for (int j = startX; j < rows; j++)
    {
        cout << j << " ";
    }
    cout << endl
         << endl;
}

void displayCityMap()
{
    if (city == nullptr)
    {
        cout << "There is no data!" << endl
             << endl;
        return;
    }

    string **temp = tempArray();

    for (int i = 0; i < *citySize; i++)
    {
        temp[city[i].cityX][city[i].cityY] = city[i].cityId;
    }
    table(temp);
    deleteTempArray(temp);
}

void displayCCMap()
{
    if (cCover == nullptr)
    {
        cout << "There is no data!" << endl
             << endl;
        return;
    }
    string **temp = tempArray();
    for (int i = 0; i < *ccSize; i++)
    {
        temp[cCover[i].ccX][cCover[i].ccY] = to_string(valueIndex(cCover[i].value));
    }
    table(temp);
    deleteTempArray(temp);
}

void displayCCMapS()
{
    if (city == nullptr)
    {
        cout << "There is no data!" << endl
             << endl;
        return;
    }
    string **temp = tempArray();
    for (int i = 0; i < *ccSize; i++)
    {
        // cout << valueSB(cCover[i].value) << endl;
        temp[cCover[i].ccX][cCover[i].ccY] = valueSB(cCover[i].value);
    }
    table(temp);
    deleteTempArray(temp);
}

void displayPressureMap()
{
    if (P == nullptr)
    {
        cout << "There is no data!" << endl
             << endl;
        return;
    }
    string **temp = tempArray();
    for (int i = 0; i < *pSize; i++)
    {
        temp[P[i].pX][P[i].pY] = to_string(valueIndex(P[i].value));
    }
    table(temp);
    deleteTempArray(temp);
}

void displayPressureMapS()
{
    if (P == nullptr)
    {
        cout << "There is no data!" << endl
             << endl;
        return;
    }
    string **temp = tempArray();
    for (int i = 0; i < *pSize; i++)
    {
        temp[P[i].pX][P[i].pY] = valueSB(P[i].value);
    }
    table(temp);
    deleteTempArray(temp);
}

void displayReport()

{
    if (city == nullptr)
    {
        cout << "There is no data!" << endl
             << endl;
        return;
    }

    cout << "Weather Forecast Summary Report" << endl;
    cout << "-------------------------------" << endl;
    // cc
    string **ccTemp = tempArray();
    for (int i = 0; i < *ccSize; i++)
    {
        ccTemp[cCover[i].ccX][cCover[i].ccY] = to_string(cCover[i].value);
    }

    // // p
    string **pTemp = tempArray();
    for (int i = 0; i < *pSize; i++)
    {
        pTemp[P[i].pX][P[i].pY] = to_string(P[i].value);
    }

    vector<vector<string>> groupedCities = groupCity();

    for (auto &group : groupedCities)
    {
        double avgCC = calValue(group, ccTemp);

        double avgP = calValue(group, pTemp);

        string ccSB = valueSB(avgCC);
        string apSB = valueSB(avgP);

        cout << "City Name\t"
             << ": " << group[5] << endl;
        cout << "City ID\t\t"
             << ": " << group[4] << endl;
        cout << "Ave. Cloud Cover\t"
             << "(ACC)\t"
             << ": " << fixed << setprecision(2) << avgCC << " (" << ccSB << ")" << endl;
        cout << "Ave. Pressure\t\t"
             << "(AP)\t"
             << ": " << fixed << setprecision(2) << avgP << " (" << apSB << ")" << endl;
        cloudSB(ccSB, apSB);
        cout << endl;
    }

    deleteTempArray(ccTemp);
    deleteTempArray(pTemp);
    groupedCities.clear();
}

void displaySingleCity()

{
    if (city == nullptr)
    {
        cout << "There is no data!" << endl
             << endl;
        return;
    }
    string cityId;
    cout << "Please enter city id: ";
    cin >> cityId;
    cout << endl;

    // cc
    string **ccTemp = tempArray();
    for (int i = 0; i < *ccSize; i++)
    {
        ccTemp[cCover[i].ccX][cCover[i].ccY] = to_string(cCover[i].value);
    }

    // // p
    string **pTemp = tempArray();
    for (int i = 0; i < *pSize; i++)
    {
        pTemp[P[i].pX][P[i].pY] = to_string(P[i].value);
    }

    vector<vector<string>> groupedCities = groupCity();

    for (auto &group : groupedCities)
    {

        if (group[4] == cityId)
        {
            double avgCC = calValue(group, ccTemp);

            double avgP = calValue(group, pTemp);

            string ccSB = valueSB(avgCC);
            string apSB = valueSB(avgP);

            cout << "Weather Forecast Summary Report" << endl;
            cout << "-------------------------------" << endl;

            cout << "City Name\t"
                 << ": " << group[5] << endl;
            cout << "City ID\t\t"
                 << ": " << group[4] << endl;
            cout << "Ave. Cloud Cover\t"
                 << "(ACC)\t"
                 << ": " << setprecision(2) << avgCC << " (" << ccSB << ")" << endl;
            cout << "Ave. Pressure\t\t"
                 << "(AP)\t"
                 << ": " << setprecision(2) << avgP << " (" << apSB << ")" << endl;
            cloudSB(ccSB, apSB);
            cout << endl;
            break;
        }
    }
    deleteTempArray(ccTemp);
    deleteTempArray(pTemp);
    groupedCities.clear();
}

int valueIndex(int &value)
{
    return (value >= 0 && value < 100) ? value / 10 : -1;
}

string valueSB(int &value)
{
    string SB;
    if (value >= 0 && value < 35)
    {
        SB = "L";
    }
    else if (value >= 35 && value < 65)
    {
        SB = "M";
    }
    else if (value >= 65 && value < 100)
    {
        SB = "H";
    }

    return SB;
}

string valueSB(double &value)
{
    string SB;
    if (value >= 0 && value < 35)
    {
        SB = "L";
    }
    else if (value >= 35 && value < 65)
    {
        SB = "M";
    }
    else if (value >= 65 && value < 100)
    {
        SB = "H";
    }

    return SB;
}

void cloudSB(string &CC, string &AP)
{

    double percentage = 0;

    if (AP == "L" && CC == "H")
    {
        percentage = 90.00;
        cout << "Probability of Rain\t(%)\t: " << percentage << endl;
        cout << "~~~~\n"
             << "~~~~~\n"
             << "\\\\\\\\\\" << endl;
    }
    else if (AP == "L" && CC == "M")
    {
        percentage = 80.00;
        cout << "Probability of Rain\t(%)\t: " << percentage << endl;
        cout << "~~~~\n"
             << "~~~~~\n"
             << " \\\\\\\\" << endl;
    }
    else if (AP == "L" && CC == "L")
    {
        percentage = 70.00;
        cout << "Probability of Rain\t(%)\t: " << percentage << endl;
        cout << "~~~~\n"
             << "~~~~~\n"
             << "  \\\\\\" << endl;
    }
    else if (AP == "M" && CC == "H")
    {
        percentage = 60.00;
        cout << "Probability of Rain\t(%)\t: " << percentage << endl;
        cout << "~~~~\n"
             << "~~~~~\n"
             << "   \\\\" << endl;
    }
    else if (AP == "M" && CC == "M")
    {
        percentage = 50.00;
        cout << "Probability of Rain\t(%)\t: " << percentage << endl;
        cout << "~~~~\n"
             << "~~~~~\n"
             << "    \\" << endl;
    }
    else if (AP == "M" && CC == "L")
    {
        percentage = 40.00;
        cout << "Probability of Rain\t(%)\t: " << percentage << endl;
        cout << "~~~~\n"
             << "~~~~~\n"
             << " " << endl;
    }
    else if (AP == "H" && CC == "H")
    {
        percentage = 30.00;
        cout << "Probability of Rain\t(%)\t: " << percentage << endl;
        cout << "~~~\n"
             << "~~~~\n"
             << " " << endl;
    }
    else if (AP == "H" && CC == "M")
    {
        percentage = 20.00;
        cout << "Probability of Rain\t(%)\t: " << percentage << endl;
        cout << "~~\n"
             << "~~~\n"
             << " " << endl;
    }
    else if (AP == "H" && CC == "L")
    {
        percentage = 10.00;
        cout << "Probability of Rain\t(%)\t: " << percentage << endl;
        cout << "~\n"
             << "~~\n"
             << " " << endl;
    }
}

vector<vector<string>> groupCity()
{
    // Group cities by cityId using a vector of vectors
    vector<vector<string>> groupedCities;
    vector<string> newGroup;

    for (int i = 0; i < *citySize; i++)
    {
        bool foundGroup = false;

        for (auto &group : groupedCities)
        {
            if (!group.empty() && group[4] == city[i].cityId)
            {

                if (stoi(group[0]) > city[i].cityX)
                {
                    group[0] = to_string(city[i].cityX);
                }

                if (stoi(group[1]) < city[i].cityX)
                {
                    group[1] = to_string(city[i].cityX);
                }

                if (stoi(group[2]) > city[i].cityY)
                {
                    group[2] = to_string(city[i].cityY);
                }

                if (stoi(group[3]) < city[i].cityY)
                {
                    group[3] = to_string(city[i].cityY);
                }
                foundGroup = true;
                break;
            }
        }

        if (!foundGroup)
        {
            newGroup.push_back(to_string(city[i].cityX));
            newGroup.push_back(to_string(city[i].cityX));
            newGroup.push_back(to_string(city[i].cityY));
            newGroup.push_back(to_string(city[i].cityY));
            newGroup.push_back(city[i].cityId);
            newGroup.push_back(city[i].cityName);
            groupedCities.push_back(newGroup);
            newGroup.clear();
        }
    }

    return groupedCities;
}

double calValue(vector<string> specCity, string **temp)
{

    int rows_max = coordinatePointer[0].end;
    int cols_max = coordinatePointer[1].end;
    int rows_min = coordinatePointer[0].start;
    int cols_min = coordinatePointer[1].start;
    int cols_start = stoi(specCity[2]) - 1;
    int cols_end = stoi(specCity[3]) + 1;
    int rows_start = stoi(specCity[0]) - 1;
    int rows_end = stoi(specCity[1]) + 1;

    // cout << specCity[0] << specCity[1] << specCity[2] << specCity[3] << endl;

    double sum = 0;
    double count = 0;

    if (cols_start < cols_min)
    {
        cols_start = cols_min;
    }

    if (rows_start < rows_min)
    {
        rows_start = rows_min;
    }

    if (cols_end > cols_max)
    {
        cols_end = cols_max;
    }

    if (rows_end > rows_max)
    {
        rows_end = rows_max;
    }

    // cout << cols_start << " " << rows_start << endl;
    // cout << cols_end << " " << rows_end << endl;

    for (int col = cols_start; col <= cols_end; col++)
    {
        for (int row = rows_start; row <= rows_end; row++)
        {
            // cout << temp[row][col] << " " << row << col << endl;
            sum += stod(temp[row][col]);
            count++;
        }
    }
    // cout << sum << " " << count << endl;
    double avgValue = sum / count;
    return avgValue;
}

void memoryReset()
{
    delete[] coordinatePointer;
    cout << "coordinates memory deallocation...done!" << endl;
    delete ccSize;
    delete[] cCover;
    cout << "cloud cover memory deallocation...done!" << endl;
    delete citySize;
    delete[] city;
    cout << "city location memory deallocation...done!" << endl;
    delete pSize;
    delete[] P;
    cout << "atmospheric pressure memory deallocation...done!" << endl;
}