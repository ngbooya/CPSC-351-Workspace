#include <iostream>
#include <fstream>
#include <queue>

using namespace std;


//Create structure to store information for each process
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




  /*  do{
        cout << "Enter memory size: ";
        cin >> memInput;

        intFail = cin.fail();

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');

    }while(intFail == true);*/


    fstream inputFile;
    inputFile.open("in1.txt", ios::in);


    if(!inputFile){
      cout << "Error. File does not exist!\n";
    }else{

      inputFile >> numOfProcesses;

      Processes * MainProcess = new Processes [numOfProcesses];

      //while(!inputFile.eof()){
      for(int processIndex = 0; processIndex < numOfProcesses; processIndex++){

        inputFile >> MainProcess[processIndex].pID;
        inputFile >> MainProcess[processIndex].arriveTime;
        inputFile >> MainProcess[processIndex].lifeTime;
        inputFile >> MainProcess[processIndex].numOfFrame;

        for(int frameIndex = 0; frameIndex < MainProcess[processIndex].numOfFrame; frameIndex++){
          inputFile >> MainProcess[processIndex].sizeOfFrame[frameIndex];
        }


    //Output results of file for testing purposes
      cout << MainProcess[processIndex].pID << endl;
      cout << MainProcess[processIndex].arriveTime << " ";
      cout << MainProcess[processIndex].lifeTime << endl;
      cout << MainProcess[processIndex].numOfFrame << " ";



      for(int c = 0; c < MainProcess[processIndex].numOfFrame; c++){
        cout << MainProcess[processIndex].sizeOfFrame[c] << " ";
      }
      cout << endl << endl;
    }

  return 0;


  }
}
