#include <iostream>
#include <fstream>
#include <queue>

using namespace std;



struct Processes{
  int pID;
  int arriveTime;
  int lifeTime;

  int numOfFrame = NULL;
  int * sizeOfFrame = new int [numOfFrame];

};

int main(){

  int memInput = 0;
  bool intFail;

  int numOfProcesses = 0;

  Processes prod;



    do{
        cout << "Enter memory size: ";
        cin >> memInput;

        intFail = cin.fail();

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');

    }while(intFail == true);


    fstream inputFile;
    inputFile.open("in1.txt", ios::in);

  //  Processes MainProcess[8];

    if(!inputFile){
      cout << "Error. File does not exist!\n";
    }else{

        inputFile >> numOfProcesses;

        Processes * MainProcess = new Processes [numOfProcesses];

      //while(!inputFile.eof()){
      for(int a = 0; a < numOfProcesses; a++){

        inputFile >> MainProcess[a].pID;
        inputFile >> MainProcess[a].arriveTime;
        inputFile >> MainProcess[a].lifeTime;
        inputFile >> MainProcess[a].numOfFrame;

        for(int b = 0; b < MainProcess[a].numOfFrame; b++){
          inputFile >> MainProcess[a].sizeOfFrame[b];
        }

    cout << MainProcess[a].pID << endl;
    cout << MainProcess[a].arriveTime << " ";
    cout << MainProcess[a].lifeTime << endl;
    cout << MainProcess[a].numOfFrame << " ";



    for(int c = 0; c < MainProcess[a].numOfFrame; c++){
      cout << MainProcess[a].sizeOfFrame[c] << " ";
    }
    cout << endl << endl;
  }

  return 0;


  }
}
