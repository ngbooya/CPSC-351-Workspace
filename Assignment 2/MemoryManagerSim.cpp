#include <iostream>
#include <fstream>

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

  Processes prod1;

    do{
        cout << "Enter memory size: ";
        cin >> memInput;

        intFail = cin.fail();

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');

    }while(intFail == true);






    fstream inputFile;
    inputFile.open("in1.txt", ios::in);

    if(!inputFile){
      cout << "Error. File does not exist!\n";
    }else{

        inputFile >> numOfProcesses;
      //while(!inputFile.eof()){
        inputFile >> prod1.pID;
        inputFile >> prod1.arriveTime;
        inputFile >> prod1.lifeTime;
        inputFile >> prod1.numOfFrame;

        for(int i = 0; i < prod1.numOfFrame; i++){
          inputFile >> prod1.sizeOfFrame[i];
        }

    //  }
    }

    cout << prod1.pID << endl;
    cout << prod1.arriveTime << endl;
    cout << prod1.lifeTime << endl;
    cout << prod1.numOfFrame << endl;

    cout << prod1.sizeOfFrame[0] << endl;
    cout << prod1.sizeOfFrame[1] << endl;
    cout <<"###############################" << endl;

    for(int i = 0; i < prod1.numOfFrame; i++){
      cout << prod1.sizeOfFrame[i] << endl;
    }


  return 0;
}
