#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <Windows.h>
#include <time.h>

using namespace std;


int main() {
  _int64 lpPerformanceCount, lpFrequency;
  long double time1, time2, time3;

  BOOL int2 = QueryPerformanceFreqeuncy((LARGE_INTEGER *) &lpFrequency);

  BOOL int1 = QueryPerformanceFreqeuncy((LARGE_INTEGER *) &lpPerformanceCount);

  time1 = lpPerformanceCount;

  for(int i = 0; i < 1000000; i++) {}

  int1 = QueryPerformanceFreqeuncy((LARGE_INTEGER *) &lpPerformanceCount);
  time2 = lpPerformanceCount;

  int1 = QueryPerformanceFreqeuncy((LARGE_INTEGER *) &lpPerformanceCount);
  time3 = lpPerformanceCount;

  cout << "Frequency" << lpFrequency << "ticks/sec" << endl;
  cout << "Period:" << (long double) 1/lpFrequency << "sec/tick" << endl;


  long double forLoop = (time2 - time1) / (lpFrequency);
  long double overhead = (time3 - time2) / (lpFrequency);

  cout << "Duration of for loop:" << forLoop * 1000 << "milliseconds" << endl;
  cout << "Overhead:" << overhead * 1000 << "milliseconds" << endl;

  system("PAUSE");

  retun 0;
}
