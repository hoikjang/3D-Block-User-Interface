#include "header.h"



//변수 정상 작동

Node Variables::Block[16]={Node(0), Node(1), Node(2), Node(3),Node(4),Node(5),Node(6),Node(7),Node(8),Node(9),Node(10),Node(11),Node(12),Node(13),Node(14),Node(15)};


Tree Variables::Base[6]={Tree(&(Block[0])),Tree(&(Block[1])),Tree(&(Block[2])),Tree(&(Block[3])),Tree(&(Block[4])),Tree(&(Block[5]))};



BoxRenderer Variables::boxrenderer;

Cube Variables::cube;
 
BoxData Variables::boxdata;


Variables::Variables()
{} 

int baseid=0;
int baseonoff=0;