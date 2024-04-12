//Names:Aria Kafie, Htet Hnin Su Wai
//Class Accounts : cssc4055, cssc4043
//Class Information : CS 530, Spring 2024
//Assignment Information : Assignment #2, XE assembler program
//File name : OPTAB.h

#ifndef OPTAB_H_
#define OPTAB_H_

#include <map>
#include <string>

#include "structs.h"

using namespace std;

const unsigned char FORMAT_1 = 1;
const unsigned char FORMAT_2 = 2;
const unsigned char FORMAT_3_4 = 3;

void deleteOpTab();
map<string, OpInfo*>* getOpTab();

#endif
