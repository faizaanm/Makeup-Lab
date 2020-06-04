/* Program:     Lab #13 (Makeup Lab):
 Author:        F. Merchant
 Class:         CSCI 230 TTh
 Date:          6/4/20
 Description:   ...
 
 I certify that the code below if my own work.
 
 Exception(s): N/A
 
 */

//Faizaan Merchant

#include <string>
#include <list>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

const int size = 100000;
const int bSize = 256;
string text1File = "/Users/faizaan/randText1.txt";
string binary1File = "/Users/faizaan/randBinary1.txt";
string binary256File = "/Users/faizaan/randBinary256.txt";

double totaltime(clock_t s)
{
    double d = (clock() - s) / (double) CLOCKS_PER_SEC;
    return d;
}

void randomNums(int arr[])
{
    srand(time(NULL));

    for (int i = 0; i < size; i++)
    {
        int num = rand() % 100;
        arr[i] = num;
    }
}

void checkArrayVals(int arr[], int t)
{
    cout << "first 5 values: ";
    for (int i = 0; i < t; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
    cout << "last 5 values: ";
    for (int i = size - 5; i < size; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void writeToText1(fstream &myFile, int arr[])
{
    cout << "Writing text format with 1 value at a time." << endl;
    myFile.open(text1File);

    clock_t start = clock();

    for (int i = 0; i < size; i++)
    {
        myFile << arr[i] << endl;
    }

    cout << "Time: " << totaltime(start) << endl;
    myFile.close();
    cout << endl;
}

void writeToBinary1(fstream &myFile, int arr[])
{
    cout << "Writing binary format with 1 value at a time." << endl;
    myFile.open(binary1File, ios::binary | ios::out | ios::trunc);
    
    clock_t start = clock();

    for (int i = 0; i < size; i++)
    {
        myFile.write(reinterpret_cast<char*>(&arr[i]), sizeof(arr[i]));
    }

    cout << "Time: " << totaltime(start) << endl;
    myFile.close();
    cout << endl;
}

void writeToBinary256(fstream &myFile, int arr[])
{
    cout << "Writing binary format with 256 values (1024 bytes) at a time." << endl;
    myFile.open(binary256File, ios::binary | ios::out | ios::trunc);

    int buffer[bSize];
    bool end = false;
    int index = 0;

    clock_t start = clock();

    while (!end)
    {
        for (int i = 0; i < bSize; i++)
        {
            if (index == size)
            {
                end = true;
                break;
            }
            buffer[i] = arr[index];
            index++;
        }
        myFile.write(reinterpret_cast<char*>(&buffer), sizeof(buffer));
    }

    cout << "Time: " << totaltime(start) << endl;
    myFile.close();
    cout << endl;
}

void readFromText1(fstream &myF, int arr[], int readArr[])
{
    cout << "Reading text format 1 value at a time." << endl;
    cout << endl;
    cout << "Values written in file: " << endl;
    checkArrayVals(arr, 5);
    int n;

    myF.open(text1File);

    clock_t start = clock();

    int i = 0;
    while (i < 200000)
    {
        myF >> n;
        readArr[i] = n;
        i++;
    }

    cout << endl;
    cout << "Time: " << totaltime(start) << endl;
    cout << endl;
    myF.close();
    cout << "Values read from file: " << endl;
    checkArrayVals(readArr, 5);
    cout << endl;
}

void readFromBinary1(fstream &myFile, int arr[], int readArr[])
{
    cout << "Reading binary format with 1 value at a time." << endl;
    cout << endl;
    int n;
    cout << "Values written in file: " << endl;
    checkArrayVals(arr, 5);

    myFile.open(binary1File, ios::binary | ios::in);

    clock_t start = clock();

    for (int i = 0; i < size; i++)
    {
        myFile.read(reinterpret_cast<char*>(&n), sizeof(int));
        readArr[i] = n;
    }
    cout << endl;

    cout << "Time: " << totaltime(start) << endl;
    cout << endl;
    myFile.close();
    cout << "Values read from file: " << endl;
    checkArrayVals(readArr, 5);
    cout << endl;
}

void readFromBinary256(fstream &myFile, int arr[], int readArr[])
{
    int buffer[bSize];
    bool end = false;
    int index = 0;
    int loopTimes = 0;
    long position = 0;
    
    cout << "Reading binary format with 256 values (1024 bytes) at a time." << endl;
    cout << endl;
    cout << "Values written in file: " << endl;
    checkArrayVals(arr, 5);

    myFile.open(binary256File, ios::binary | ios::in);

    clock_t start = clock();

    while (!end)
    {
        if (myFile.eof())
        {
            end = true;
            break;
        }
        position = loopTimes * (sizeof(buffer));
        myFile.seekg(position);
        myFile.read(reinterpret_cast<char*>(&buffer), sizeof(buffer));
        for (int i = 0; i < bSize; i++)
        {
            readArr[index] = buffer[i];
            index++;
        }
        loopTimes++;
    }
    cout << endl;

    cout << "Time: " << totaltime(start) << endl;
    cout << endl;
    myFile.close();
    cout << "Values read from file: " << endl;
    checkArrayVals(readArr, 5);
    cout << endl;
}


int main()
{
    fstream myText1File;
    fstream myBinary1File;
    fstream myBinary256File;
    int arr[size];
    int readArr[size];
    
    randomNums(arr);
    
//    writeToBinary1(myBinary1File, arr);
//    readFromBinary1(myBinary1File, arr, readArr);
    
    writeToBinary256(myBinary256File, arr);
    readFromBinary256(myBinary256File, arr, readArr);

//    writeToText1(myText1File, arr);
//    readFromText1(myText1File, arr, readArr);
    
    return 0;
}
