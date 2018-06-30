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

//christian is working below

struct pageObject
{
	int memSizeBase, memSizeLimit, timeIn, timeOut, processID;
};

void makePages(Processes mainProc[], int procNum, pageObject pageTablebuff[], int pageSizebuff){
    int *memRequest, currentPage = 0;

    memRequest = new int [procNum];

    for(int i = 0; i < procNum; i++)
    {
      if(mainProc[i].numOfFrame > 1)
      {
        for(int c = 0; c < mainProc[i].numOfFrame; c++)
          memRequest[i] += mainProc[i].sizeOfFrame[c];
      } else
          memRequest[i] = mainProc[i].sizeOfFrame[0];
    }

    for(int i = 0; i < procNum; i++)
    {
    	for(int c = currentPage; c < currentPage + (memRequest[i]/pageSizebuff); c++)
    	{
    		pageTablebuff[c].memSizeBase = c * pageSizebuff;
    		pageTablebuff[c].memSizeLimit = pageTablebuff[c].memSizeBase + (pageSizebuff - 1);
        pageTablebuff[c].timeIn = mainProc[i].arriveTime;
        pageTablebuff[c].timeOut = mainProc[i].lifeTime;
        pageTablebuff[c].processID = mainProc[i].pID;
    	}
        currentPage += memRequest[i]/pageSizebuff;
    }

//christian is working above

};

int main(){

  int memInput = 2000, pageNum = 0, pageSize = 100;
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
	//inserting Processes into queue
        for(int i = 0; i < numOfProcesses; i++){
          processQueue.push(MainProcess[i])
        }
      /*
      //Output results of file for testing purposes
      cout << MainProcess[processIndex].pID << endl;
      cout << MainProcess[processIndex].arriveTime << " ";
      cout << MainProcess[processIndex].lifeTime << endl;
      cout << MainProcess[processIndex].numOfFrame << " ";



      for(int c = 0; c < MainProcess[processIndex].numOfFrame; c++){
        cout << MainProcess[processIndex].sizeOfFrame[c] << " ";
      }
      cout << endl << endl;
      */

    }

    //christian is working below

  	pageNum = memInput / pageSize;

  	pageObject *pageTable = new pageObject [pageNum];

    makePages(MainProcess, numOfProcesses, pageTable, pageSize);

    // output below for testing purposes
  	for(int i = 0; i < pageNum; i++)
  	{
  		cout << pageTable[i].memSizeBase << "  -  " << pageTable[i].memSizeLimit
          << '\t' << "Page size, " << "Page #" << (i + 1) << ", Proccess #" << pageTable[i].processID << endl;
  	}

    //christian is working above

    delete[] MainProcess;
  	delete[] pageTable;

  return 0;


  }
}
