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

struct pageObject //each pages contains this info
{
	int memSizeBase, memSizeLimit, processID;
};

//this function takes process information and splits the processes' memory space request into page size
void makePages(Processes mainProc[], int procIDbuff, pageObject pageTablebuff[], int pageSizebuff, int pageNumBuff)
{
    int memRequest = 0, pageNumFree = 0;

    for(int i = 0; i < pageNumBuff; i++)
    {
      if(pageTablebuff[i].processID <= 0)
        pageNumFree++; //used for checking
    }

    if(mainProc[procIDbuff-1].numOfFrame > 1) //if numofFrame > 2, then add the two sizeofFrame together
    {
      for(int i = 0; i < mainProc[procIDbuff-1].numOfFrame; i++)
        memRequest += mainProc[procIDbuff-1].sizeOfFrame[i];

      if((memRequest % pageSizebuff) > 0) //if requested memory = 250 and page size = 100, then 250%100 = 50
        memRequest += pageSizebuff - (memRequest%pageSizebuff); //this changes partial a memory request to a full page size

      if(pageNumFree >= (memRequest/pageSizebuff)) //checks if there are enough pages to fit the requested memory size
      {
        for(int i = 0; i < pageNumBuff; i++)
        {
          if(pageTablebuff[i].processID <= 0 && memRequest > 0) //check if current page is empty and memory is being requested
          {
            pageTablebuff[i].memSizeBase = i * pageSizebuff; //"page number = array index"; i = current page number, mult. by page size to get the base (starting memory)
            pageTablebuff[i].memSizeLimit = pageTablebuff[i].memSizeBase + (pageSizebuff - 1); //add base to pageSize to get the limit
            pageTablebuff[i].processID = mainProc[procIDbuff-1].pID;
            memRequest -= pageSizebuff; //decrements memory request by "page size" amount; since each page is fixed to pageSize
            pageNumFree--;
          }
        }
      }
    }
    else //if numOfFrame = 1; similar to the one above
    {
      memRequest = mainProc[procIDbuff-1].sizeOfFrame[0];

      if((memRequest % pageSizebuff) > 0)
        memRequest += pageSizebuff - (memRequest%pageSizebuff);

      if(pageNumFree >= (memRequest/pageSizebuff))
      {
        for(int i = 0; i < pageNumBuff; i++)
        {
          if(pageTablebuff[i].processID <= 0 && memRequest > 0) //check if current page is empty and memory is being requested
          {
            pageTablebuff[i].memSizeBase = i * pageSizebuff; //"page number = array index"; i = current page number, mult. by page size to get the base (starting memory)
            pageTablebuff[i].memSizeLimit = pageTablebuff[i].memSizeBase + (pageSizebuff - 1); //add base to pageSize to get the limit
            pageTablebuff[i].processID = mainProc[procIDbuff-1].pID;
            memRequest -= pageSizebuff; //decrements memory request by "page size" amount; since each page is fixed to pageSize
            pageNumFree--;
          }
        }
      }
    }
};

//remove pages from the page table when their time is up
void removePages(Processes mainProc[], int procIDbuff, pageObject pageTablebuff[], int pageNumBuff, int timerBuff)
{
  int pageNumFree = 0;

  for(int i = 0; i < pageNumBuff; i++)
  {
    if(pageTablebuff[i].processID <= 0)
      pageNumFree++; //used for checking
  }

<<<<<<< HEAD
  //checks number of free page and compares current timer with process (arriveTime + lifeTime) time
=======
<<<<<<< HEAD
}
=======
>>>>>>> dc16b0ab6c573952509528f0a0bcb3056e87d9a8
  if(((mainProc[procIDbuff-1].arriveTime + mainProc[procIDbuff-1].lifeTime) == timerBuff) && pageNumFree > 0)
  {
    for (int i = 0; i < pageNumBuff; i++)
    {
      if(pageTablebuff[i].processID == mainProc[procIDbuff-1].pID) //if the check above is true, then compare process to page info
      {
        pageTablebuff[i].memSizeBase = 0; //if checks above is true, then zero-out the info
        pageTablebuff[i].memSizeLimit = 0;
        pageTablebuff[i].processID = 0;
        pageNumFree--; //derements to reduce the for-loop checking; not all the pages will be free
      }
    }
  }
};
>>>>>>> ca980ae82219aab2612c0173d07f3acb7c89bc40

//christian is working above

int main(){

  int memInput = 2000, pageNum = 0, pageSize = 100, timer = 0;
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

    while(timer <= 1500)
    {
      makePages(MainProcess, 1, pageTable, pageSize, pageNum); //simulates process #1 going in from queue
      makePages(MainProcess, 2, pageTable, pageSize, pageNum); //simulates process #2 going in from queue
      makePages(MainProcess, 3, pageTable, pageSize, pageNum); //simulates process #3 going in from queue; this does not fit so remove process #1
      removePages(MainProcess, 1, pageTable, pageNum, timer); //simulates removing process #1 from page table
      makePages(MainProcess, 3, pageTable, pageSize, pageNum); //simulates process #3 going in from queue

      // output below for testing purposes
      if(timer == 0 || timer == 1000)
      {
        if(timer == 0)
          cout << endl << "at timer = 0, process #3 doesn't fit" << endl;
        if(timer == 1000)
          cout << endl << "at timer = 1000, removes process #1 and allocate space for process #3" << endl;
        for(int i = 0; i < pageNum; i++)
        {
          cout << pageTable[i].memSizeBase << "  -  " << pageTable[i].memSizeLimit
              << '\t' << "Page size, " << "Page #" << (i + 1) << ", Proccess #" << pageTable[i].processID << endl;
        }
      }

      timer++;
    };

    //christian is working above

    delete[] MainProcess;
  	delete[] pageTable;

  return 0;


  }
}
