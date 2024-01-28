// #include <iostream>
// using namespace std;

// int count;

// void deleteMap();
// string ** initializeMap(){
//     string** cityMap = new string*[5];
    
//     for (int x = 0; x < 5; ++x) {
//         cityMap[x] = new string[5];
//         for (int y = 0; y < 5; ++y) {
//             cityMap[x][y] = "A";
//         }
//     }
//     return cityMap;
// }

// void Display(){
//     string** a = initializeMap();

//      for (int x = 0; x < 5; ++x) {
//         for (int y = 0; y < 5; ++y) {
//             count +=1;
//             cout << count;
//            cout << a[x][y] << endl;
//         }
//     }

//     cout << "before Delete" << endl;
//     cout << (a==nullptr) << endl;
//      cout << "After Delete" << endl;
//      deleteMap(a);
//     cout << (a==nullptr) << endl;;

// }

// void deleteMap(string(&myarray)[5][5]) {
//     for (int x = 0; x < 5; ++x) {
//         delete[] myarray[x];
//     }
//     delete[] myarray;
// }


// int main(){
//     cout << (a==nullptr) << endl;
//     initializeMap();
//     Display();
 
//     return 0;
   
// }

