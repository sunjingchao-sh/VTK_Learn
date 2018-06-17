#include <QApplication>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkPolyDataReader.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <QVTKOpenGLWidget.h>
#include <vtkStructuredGridReader.h>
#include <vtkDataSetMapper.h>
 
//Development Enviroment:
//OS:Win 10 64bit
//Compile:VS 2017
//Qt:5.10.1 64bit
//VTK:8.1.0 64bit
int main(int argc, char** argv)
{
  QApplication app(argc, argv);
 
  vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
  QVTKOpenGLWidget widget;
  widget.SetRenderWindow(renderWindow);

  widget.resize( 256, 256 ); 
  //vtkSmartPointer<vtkPolyDataReader> pReader = vtkSmartPointer<vtkPolyDataReader>::New(); //Cube
  vtkSmartPointer<vtkStructuredGridReader> pReader = vtkSmartPointer<vtkStructuredGridReader>::New();
  //pReader->SetFileName("C:/work/VTKWork/mycode/SimVTK/Data/VTKFiles/cube.vtk"); //Cube
  pReader->SetFileName("C:/work/VTKWork/mycode/SimVTK/Data/VTKFiles/SampleStructGrid.vtk");
  pReader->Update();

  //vtkSmartPointer<vtkPolyDataMapper> sphereMapper = vtkSmartPointer<vtkPolyDataMapper>::New(); //Cube
  vtkSmartPointer<vtkDataSetMapper> sphereMapper = vtkSmartPointer<vtkDataSetMapper>::New();
  sphereMapper->SetInputConnection(pReader->GetOutputPort() );
 
  vtkSmartPointer<vtkActor> sphereActor = vtkSmartPointer<vtkActor>::New();
  sphereActor->SetMapper( sphereMapper );
 
  vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor( sphereActor );
 
  widget.GetRenderWindow()->AddRenderer(renderer);
  widget.show();
 
  app.exec();
 
  return EXIT_SUCCESS;
}