#ifndef __Rendering_h
#define __Rendering_h

#include "cubesource.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkMath.h"
#include "vtkTransform.h"
#include "vtkTransformFilter.h"
#include <vtkConeSource.h>
#include <vtkPolyData.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkTransform.h>
#include <vtkSmartPointer.h>
#include <vtkXMLPolyDataWriter.h>
#include "vtkSphereSource.h"
#include "vtkGlyph3D.h"
#include "vtkAxes.h"
#include "vtkTubeFilter.h"
#include "vtkCallbackCommand.h"
#include <string>
#include <vtkCamera.h>
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkLookupTable.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <vtkMatrix4x4.h>
#include <vtkAxesActor.h>
#include <vtkOrientationMarkerWidget.h>


class Rendering
{
public:



void BoxRendering(int size, int boxid, double w, double x, double y, double z);

};



#endif