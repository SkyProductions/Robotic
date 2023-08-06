// include required OCCT headers
#include <Standard_Version.hxx>
#include <Message_ProgressIndicator.hxx>
#include <Message_ProgressScope.hxx>
//for OCC graphic
//#include <Aspect_DisplayConnection.hxx>
//#include <WNT_Window.hxx>
//#include <OpenGl_GraphicDriver.hxx>
////for object display
//#include <V3d_Viewer.hxx>
//#include <V3d_View.hxx>
//#include <AIS_InteractiveContext.hxx>
//#include <AIS_Shape.hxx>
//topology
#include <TopoDS_Shape.hxx>
#include <TopoDS_Compound.hxx>
//brep tools
#include <BRep_Builder.hxx>
#include <BRepTools.hxx>
// iges I/E
#include <IGESControl_Reader.hxx>
#include <IGESControl_Controller.hxx>
#include <IGESControl_Writer.hxx>
#include <IFSelect_ReturnStatus.hxx>
#include <Interface_Static.hxx>
//step I/E
#include <STEPControl_Reader.hxx>
#include <STEPControl_Writer.hxx>
//for stl export
#include <StlAPI_Writer.hxx>
//for vrml export
#include <VrmlAPI_Writer.hxx>

//#include <TDocStd_Document.hxx>
#include <TDocStd_Application.hxx>
#include <DDocStd.hxx>
//#include <STEPCAFControl_Reader.hxx>
//#include <TColStd_IndexedDataMapOfStringString.hxx>
//#include <RWMesh_CoordinateSystem.hxx>
//#include <UnitsMethods.hxx>
#include <RWObj_CafWriter.hxx>
#include <UnitsMethods.hxx>
//#include <Message_ProgressIndicator.hxx>

//wrapper of pure C++ classes to ref classes
#include <NCollection_Haft.h>

#include <vcclr.h>
#include <BRepMesh_IncrementalMesh.hxx>
#include <BRepBndLib.hxx>
#include <STEPCAFControl_Reader.hxx>
#include <XCAFDoc_ShapeTool.hxx>
#include <XCAFDoc_DocumentTool.hxx>
//#include <Draw_ProgressIndicator.hxx>

// list of required OCCT libraries
#pragma comment(lib, "TKernel.lib")
#pragma comment(lib, "TKMath.lib")
#pragma comment(lib, "TKBRep.lib")
#pragma comment(lib, "TKXSBase.lib")
#pragma comment(lib, "TKService.lib")
#pragma comment(lib, "TKV3d.lib")
//#pragma comment(lib, "TKOpenGl.lib")
#pragma comment(lib, "TKIGES.lib")
#pragma comment(lib, "TKSTEP.lib")
#pragma comment(lib, "TKStl.lib")
//#pragma comment(lib, "TKVrml.lib")
#pragma comment(lib, "TKMesh.lib")
#pragma comment(lib, "TKRWMesh.lib")
#pragma comment(lib, "TKCDF.lib")
#pragma comment(lib, "TKCAF.lib")
#pragma comment(lib, "TKLCAF.lib")
#pragma comment(lib, "TKVCAF.lib")
#pragma comment(lib, "TKTObj.lib")
#pragma comment(lib, "TKXCAF.lib")

#pragma comment(lib, "TKDCAF.lib")
////
//#pragma comment(lib, "TKG2d.lib")
//#pragma comment(lib, "TKG3d.lib")
#pragma comment(lib, "TKTopAlgo.lib")
#pragma comment(lib, "TKXDESTEP.lib")


//! Auxiliary tool for converting C# string into UTF-8 string.
static TCollection_AsciiString toAsciiString (String^ theString)
{
  if (theString == nullptr)
  {
    return TCollection_AsciiString();
  }

  pin_ptr<const wchar_t> aPinChars = PtrToStringChars (theString);
  const wchar_t* aWCharPtr = aPinChars;
  if (aWCharPtr == NULL
  || *aWCharPtr == L'\0')
  {
    return TCollection_AsciiString();
  }
  return TCollection_AsciiString (aWCharPtr);
}

/// <summary>
/// Proxy class encapsulating calls to OCCT C++ classes within 
/// C++/CLI class visible from .Net (CSharp)
/// </summary>
public ref class StepProxy
{
public:
  // ============================================
  // Viewer functionality
  // ============================================

  /// <summary>
  ///Initialize a viewer
  /// </summary>
  /// <param name="theWnd">System.IntPtr that contains the window handle (HWND) of the control</param>
  bool InitViewer(System::IntPtr theWnd)
  {
    return true;
  }
  /// <summary>
  ///Get version
  /// </summary>
  float GetOCCVersion(void)
  {
    return (float)OCC_VERSION;
  }


public:
  // ============================================
  // Import / export functionality
  // ============================================

  /// <summary>
  ///Import BRep file
  /// </summary>
  /// <param name="theFileName">Name of import file</param>
  bool ImportBrep(System::String^ theFileName)
  {
    return ImportBrep (toAsciiString (theFileName));
  }

  /// <summary>
  ///Import BRep file
  /// </summary>
  /// <param name="theFileName">Name of import file</param>
  bool ImportBrep (const TCollection_AsciiString& theFileName)
  {
    TopoDS_Shape aShape;
    BRep_Builder aBuilder;
    Standard_Boolean isResult = BRepTools::Read(aShape,theFileName.ToCString(),aBuilder);
    if (!isResult)
    {
      return false;
    }

   // myAISContext()->Display (new AIS_Shape (aShape), Standard_True);
    return true;
  }

  /// <summary>
  ///Import Step file
  /// </summary>
  /// <param name="theFileName">Name of import file</param>
  bool ImportStep(const TCollection_AsciiString& theFileName, const TCollection_AsciiString& objFileName)
  {

    Handle(TDocStd_Document) aDoc;
    

    
    Handle(TDocStd_Application) anApp = DDocStd::GetApplication();
    anApp->NewDocument(TCollection_ExtendedString("BinXCAF"), aDoc);
    //anApp->NewDocument(TCollection_ExtendedString("BinXCAF"), myDoc);

    STEPCAFControl_Reader theStepReader;
    theStepReader.SetColorMode(true);
    theStepReader.SetNameMode(true);
    IFSelect_ReturnStatus status = theStepReader.ReadFile(theFileName.ToCString());

    //STEPControl_Reader aReader;
    //IFSelect_ReturnStatus aStatus = aReader.ReadFile(theFileName.ToCString());
    if (status == IFSelect_RetDone )
    {
      bool isFailsonly = false;
      //aReader.PrintCheckLoad( isFailsonly, IFSelect_ItemsByEntity );

      //int aNbRoot = aReader.NbRootsForTransfer();
      //aReader.PrintCheckTransfer( isFailsonly, IFSelect_ItemsByEntity );

      //aReader.TransferEntity(aDoc);

      theStepReader.Transfer(aDoc);

      TDF_LabelSequence aRootLabels;
      Handle(XCAFDoc_ShapeTool) Assembly = XCAFDoc_DocumentTool::ShapeTool(aDoc->Main());
      //myDoc->ShapeTool()->GetFreeShapes(aRootLabels);
      
      Assembly->GetFreeShapes(aRootLabels);

      TopoDS_Compound aCompound;
      BRep_Builder    aBuildTool;
      aBuildTool.MakeCompound(aCompound);
      for (TDF_LabelSequence::Iterator aLabIter(aRootLabels); aLabIter.More(); aLabIter.Next())
      {
          TopoDS_Shape     aShape;
          const TDF_Label& aLabel = aLabIter.Value();
          if (XCAFDoc_ShapeTool::GetShape(aLabel, aShape))
          {
              BRepMesh_IncrementalMesh(aShape, 0.01).Perform();
              //aBuildTool.Add(aCompound, aShape);
          }
      }

      

      //for ( Standard_Integer n = 1; n <= aNbRoot; n++ )
      //{
      //  Standard_Boolean ok = aReader.TransferRoot( n );
      //  int aNbShap = aReader.NbShapes();
      //  if ( aNbShap > 0 )
      //  {
      //    for ( int i = 1; i <= aNbShap; i++ )
      //    {
      //      TopoDS_Shape aShape = aReader.Shape( i );
      //      //myAISContext()->Display (new AIS_Shape (aShape), Standard_False);

      //      aBuildTool.Add(aCompound, aShape);
      //    }
      //    //myAISContext()->UpdateCurrentViewer();
      //  }
      //}


     /* Bnd_Box aBndBox;
      BRepBndLib::Add(aCompound, aBndBox, Standard_False);
      if (aBndBox.IsVoid())
      {
          return false;
      }

      NCollection_Vec3<double> aMin, aMax;
      aBndBox.Get(aMin.x(), aMin.y(), aMin.z(), aMax.x(), aMax.y(), aMax.z());
      const NCollection_Vec3<double> aBndDelta = aMax - aMin;*/

      //BRepMesh_IncrementalMesh anAlgo;
      //anAlgo.ChangeParameters().Deflection = aBndDelta.maxComp() * myLinearDeflection * 4.0;
      //anAlgo.ChangeParameters().Angle = myAngularDeflection;
      //anAlgo.ChangeParameters().InParallel = Standard_True;
      //anAlgo.SetShape(aCompound);
      //anAlgo.Perform();
       
      
      //Handle(TDocStd_Application) anApp = DDocStd::GetApplication();
      //const Standard_Real aSystemUnitFactor = UnitsMethods::GetCasCadeLengthUnit() * 0.001;

      //TColStd_IndexedDataMapOfStringString aFileInfo;

      //aFileInfo.Add("Author", "frank");

      //Standard_Real aFileUnitFactor = 1.0;
      //RWMesh_CoordinateSystem aSystemCoordSys = RWMesh_CoordinateSystem_Zup, aFileCoordSys = RWMesh_CoordinateSystem_Yup;
      //Handle(Message_ProgressIndicator) progress = Handle(Message_ProgressIndicator)();
      //
      //RWObj_CafWriter aWriter(TCollection_AsciiString("test.obj"));
      ////aWriter.ChangeCoordinateSystemConverter().SetInputLengthUnit(aSystemUnitFactor);
      //aWriter.ChangeCoordinateSystemConverter().SetInputCoordinateSystem(aSystemCoordSys);
      ////aWriter.ChangeCoordinateSystemConverter().SetOutputLengthUnit(aFileUnitFactor);
      // aWriter.ChangeCoordinateSystemConverter().SetOutputCoordinateSystem(aFileCoordSys);
      //aWriter.Perform(aDoc, aFileInfo, progress->Start());

      Standard_Real aFileUnitFactor = 1.0;
      RWMesh_CoordinateSystem aSystemCoordSys = RWMesh_CoordinateSystem_Zup, aFileCoordSys = RWMesh_CoordinateSystem_Yup;
      //Draw_Interpretor di;
      //Handle(Draw_ProgressIndicator) progress = new Draw_ProgressIndicator(di);

      TColStd_IndexedDataMapOfStringString aFileInfo;
      aFileInfo.Add("Author", "sky");
      const Standard_Real aSystemUnitFactor = UnitsMethods::GetCasCadeLengthUnit() * 0.001;
      RWObj_CafWriter aWriter(objFileName.ToCString());
      aWriter.ChangeCoordinateSystemConverter().SetInputLengthUnit(aSystemUnitFactor);
      aWriter.ChangeCoordinateSystemConverter().SetInputCoordinateSystem(aSystemCoordSys);
      aWriter.ChangeCoordinateSystemConverter().SetOutputLengthUnit(aFileUnitFactor);
      aWriter.ChangeCoordinateSystemConverter().SetOutputCoordinateSystem(aFileCoordSys);
      Message_ProgressRange theProgress;
      aWriter.Perform(aDoc, aFileInfo, theProgress);
    }
    else
    {
      return false;
    }

    return true;
  }

  /// <summary>
  ///Export Step file
  /// </summary>
  /// <param name="theFileName">Name of export file</param>
  bool ExportStepToObj (System::String^ theFileName , System::String^ objFile)
  {

      const TCollection_AsciiString aFilename = toAsciiString(theFileName);
      const TCollection_AsciiString oFilename = toAsciiString(objFile);
     return ImportStep(aFilename, oFilename);
    
  }

};
