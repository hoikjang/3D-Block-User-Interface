#pragma once

#include "BlockTree.h"
#include "BoxRenderer.h"
#include "BoxData.h"
#include "Cube.h"

#include "vtkAutoInit.h" 
VTK_MODULE_INIT(vtkRenderingOpenGL2)
VTK_MODULE_INIT(vtkRenderingFreeType)
VTK_MODULE_INIT(vtkInteractionStyle)


class Variables//정상 작동
{
public:
Variables();

static BoxRenderer boxrenderer;

static Node Block[16];

static Tree Base[6];

static Cube cube;
 
static BoxData boxdata;
};

extern Variables variables;

extern int baseid;
extern int baseonoff;
