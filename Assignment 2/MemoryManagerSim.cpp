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

//this function takes process information and splits the processes' memory space request into page size
void makePages(Processes mainProc[], int procNum, pageObject pageTablebuff[], int pageSizebuff){
    int *memRequest, currentPage = 0;

    memRequest = new int [procNum]; //make an array[processID] to store their memory request

    for(int i = 0; i < procNum; i++)
    {
      if(mainProc[i].numOfFrame > 1) //if the frame size is 2 or more add the size of the frame together
      {
        for(int c = 0; c < mainProc[i].numOfFrame; c++)
          memRequest[i] += mainProc[i].sizeOfFrame[c];
      } else
          memRequest[i] = mainProc[i].sizeOfFrame[0];
    }

    /*this section is not complete until i see the queue function*/
    for(int i = 0; i < procNum; i++)
    {
    	for(int c = currentPage; c < currentPage + (memRequest[i]/pageSizebuff); c++) //(memRequest / pageSizebuff) = the page numbers
    	{
    		pageTablebuff[c].memSizeBase = c * pageSizebuff; //creates the min memory size of the current page; reminder: array[page number]
    		pageTablebuff[c].memSizeLimit = pageTablebuff[c].memSizeBase + (pageSizebuff - 1); //calculate the limit or max of the current page
        pageTablebuff[c].timeIn = mainProc[i].arriveTime; //saves info into current page; same for the next 2 lines
        pageTablebuff[c].timeOut = mainProc[i].lifeTime;
        pageTablebuff[c].processID = mainProc[i].pID;
    	}
        currentPage += memRequest[i]/pageSizebuff; //this lets me know where the last index was filled
    }

//christian is working above

}

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

      inputFile >> numOfProcesses; //Read in first number of the input file, number of total processes

      Processes * MainProcess = new Processes [numOfProcesses];


      for(int processIndex = 0; processIndex < numOfProcesses; processIndex++){ //Index through the file to read

        inputFile >> MainProcess[processIndex].pID; //First row
        inputFile >> MainProcess[processIndex].arriveTime; //First number of the second row
        inputFile >> MainProcess[processIndex].lifeTime; //Second number on the second row
        inputFile >> MainProcess[processIndex].numOfFrame; //First number on the third row

        for(int frameIndex = 0; frameIndex < MainProcess[processIndex].numOfFrame; frameIndex++){ //Read multiple number of frames
          inputFile >> MainProcess[processIndex].sizeOfFrame[frameIndex];
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

  	pageNum = memInput / pageSize; //since memInput and pageSize can vary, divides the two to get page numbers.
    //ex: total memory size = 2000 and each page has a size of 100, then 2000/100 = 20 pages
    //makePages function simulates or creates the PAGE TABLE; the table will have 20 pages or an array of 20

  	pageObject *pageTable = new pageObject [pageNum]; //create an array of objects (contains info of processes)

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
