///////////////////////////////////////////////////////////////////////////////////////
// File Name    : 2021202078_simple_ls.c                                             //
// Date         : 2023/03/29                                                         //
// OS           : Ubuntu 16.04.5 Desktop 64bits                                      //
// Author       : Choi Kyeong Jeong                                                  //
// Student ID   : 2021202078                                                         //
// --------------------------------------------------------------------------------- //
// Title        : System Programming Assignment 1-1                                  //
// Descriptions : A c-code program that outputs file names and directory names       //
//               that exist in the directory entered by the user                     //
///////////////////////////////////////////////////////////////////////////////////////



#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#define MAX_FILE_NAME_LEN 1000

///////////////////////////////////////////////////////////////////////////////////////
// main                                                                              //
// --------------------------------------------------------------------------------- //
// Input: char* [] -> argv(Directory name that the user enters)                      //
// output: char* [] -> fileList(Sorted file names to output to the terminal)         //
// purpose: Receive directory names from users, retrieve file names                  //
//         and directory names within the entered directory, sort them               //
//         , and output them                                                         //
///////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[]) {

    DIR *dirp;
    DIR *dirpNum;
    struct dirent *dir;

    if (argc == 1) { // If no directory path is given as an argument
        dirp = opendir("."); // Open the current directory
        dirpNum = opendir(".");
    }

    else if (argc == 2) { // If a directory path is given as an argument
        if (opendir(argv[1]) == NULL) { // Handle exceptions when a non-existent file path (directory) is entered or a file is input instead of a directory as an argument.
            printf("cannot access '%s' : No such directory\n", argv[1]);
            return 0;
        }

        dirp = opendir(argv[1]); // Open the given directory path
        dirpNum = opendir(argv[1]);
    }

    else { // If more than one directory path is given (exception handling)
        printf("simple_ls: only one directory path can be processed\n");
        return 0;
    }

    int fileNum = 0; // Count the number of directories and files in the directory
    while ((dir = readdir(dirpNum)) != NULL)
        ++fileNum;

    char **fileList = (char**)malloc(sizeof(char*) * (fileNum+1)); // Allocate memory to store directory and file names
    for(int i = 0; i < fileNum; i++) {
        fileList[i] = (char*)malloc(sizeof(char) * 300); // Dynamically allocate the size of the array
        dir = readdir(dirp);
        fileList[i] = dir->d_name; // Store the current directory and file name in the array
    }

    // Sort the filenames using the bubble sort algorithm
    for (int i = 0; i < (fileNum - 1); i++) {
        for (int j = i + 1; j < fileNum; j++) {
            if (strcasecmp(fileList[i], fileList[j]) > 0) { // If the first filename is alphabetically later than the second filename, swap the positions of the two filenames in the array (case-insensitive)
                char temp[MAX_FILE_NAME_LEN];
                strcpy(temp, fileList[i]);
                strcpy(fileList[i], fileList[j]);
                strcpy(fileList[j], temp);
            }
        }
    }

    // Print the sorted filenames in the terminal
    for(int k = 0; k < fileNum; k++) {
        if(fileList[k][0] != '.') // Do not print hidden files (files starting with ".")
            printf("%s\n", fileList[k]);
    }

    closedir(dirp); // Close the directory
    closedir(dirpNum);

    free(fileList); // Free memory allocated for the array

    return 0;
}