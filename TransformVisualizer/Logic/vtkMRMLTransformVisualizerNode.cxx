/*==============================================================================

  Program: 3D Slicer

  Portions (c) Copyright Brigham and Women's Hospital (BWH) All Rights Reserved.

  See COPYRIGHT.txt
  or http://www.slicer.org/copyright/copyright.txt for details.

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
  
  This file was originally developed by Franklin King, PerkLab, Queen's University
  and was supported through the Applied Cancer Research Unit program of Cancer Care
  Ontario with funds provided by the Ontario Ministry of Health and Long-Term Care

==============================================================================*/

#include "vtkMRMLTransformVisualizerNode.h"

// VTK includes
#include <vtkCommand.h>
#include <vtkObjectFactory.h>

// MRML includes
#include <vtkMRMLScene.h>
#include <vtkMRMLVectorVolumeNode.h>
#include <vtkMRMLModelNode.h>

//----------------------------------------------------------------------------
std::string vtkMRMLTransformVisualizerNode::InputReferenceRole = std::string("inputNode");
std::string vtkMRMLTransformVisualizerNode::ReferenceVolumeReferenceRole = std::string("referenceVolume");
std::string vtkMRMLTransformVisualizerNode::OutputModelReferenceRole = std::string("outputModel");

std::string vtkMRMLTransformVisualizerNode::GlyphSliceReferenceRole = std::string("glyphSlice");
std::string vtkMRMLTransformVisualizerNode::GridSliceReferenceRole = std::string("gridSlice");

//----------------------------------------------------------------------------
vtkMRMLNodeNewMacro(vtkMRMLTransformVisualizerNode);

//----------------------------------------------------------------------------
vtkMRMLTransformVisualizerNode::vtkMRMLTransformVisualizerNode()
{
 
  //Glyph Parameters
  this->GlyphPointMax = 2000;
  this->GlyphScale = 1;
  this->GlyphThresholdMax = 1000;
  this->GlyphThresholdMin = 0;
  this->GlyphSeed = 687848400;
  this->GlyphSourceOption = 0;
  //Arrow Parameters
  this->GlyphArrowScaleDirectional = true;
  this->GlyphArrowScaleIsotropic = false;  
  this->GlyphArrowTipLength = 0.35;
  this->GlyphArrowTipRadius = 0.5;
  this->GlyphArrowShaftRadius = 0.15;
  this->GlyphArrowResolution = 6;
  //Cone Parameters
  this->GlyphConeScaleDirectional = true;
  this->GlyphConeScaleIsotropic = false;
  this->GlyphConeHeight = 1.0;
  this->GlyphConeRadius = 0.6;
  this->GlyphConeResolution = 6;
  //Sphere Parameters
  this->GlyphSphereResolution = 6;

  //Grid Parameters
  this->GridScale = 1;
  this->GridSpacingMM = 12;
  
  //Block Parameters
  this->BlockScale = 1;
  this->BlockDisplacementCheck = 0;
    
  //Contour Parameters
  this->ContourNumber = 3;
  this->ContourValues = new double[this->ContourNumber];
  this->ContourValues[0] = 1; this->ContourValues[1] = 2; this->ContourValues[2] = 3;
  this->ContourDecimation = 0.25;

  //Glyph Slice Parameters
  this->GlyphSlicePointMax = 6000;
  this->GlyphSliceThresholdMax = 1000;
  this->GlyphSliceThresholdMin = 0;  
  this->GlyphSliceScale = 1;
  this->GlyphSliceSeed = 687848400;
  
  //Grid Slice Parameters
  this->GridSliceScale = 1;
  this->GridSliceSpacingMM = 12;
    
}

//----------------------------------------------------------------------------
vtkMRMLTransformVisualizerNode::~vtkMRMLTransformVisualizerNode()
{
  delete[] this->ContourValues;
}

//----------------------------------------------------------------------------
void vtkMRMLTransformVisualizerNode::ReadXMLAttributes(const char** atts)
{
  std::cerr << "Reading TransformVisualizer parameter node" << std::endl;
  Superclass::ReadXMLAttributes(atts);

  const char* attName;
  const char* attValue;
  while (*atts != NULL){
    attName = *(atts++);
    attValue = *(atts++);
    
    if (!strcmp(attName,"GlyphPointMax")){
      std::stringstream ss;
      ss << attValue;
      ss >> this->GlyphPointMax;
      continue;
    }
    if (!strcmp(attName,"GlyphScale")){
      std::stringstream ss;
      ss << attValue;
      ss >> this->GlyphScale;
      continue;
    }    
    if (!strcmp(attName,"GlyphThresholdMax")){
      std::stringstream ss;
      ss << attValue;
      ss >> this->GlyphThresholdMax;
      continue;
    }  
    if (!strcmp(attName,"GlyphThresholdMin")){
      std::stringstream ss;
      ss << attValue;
      ss >> this->GlyphThresholdMin;
      continue;
    }
    if (!strcmp(attName,"GlyphSeed")){
      std::stringstream ss;
      ss << attValue;
      ss >> this->GlyphSeed;
      continue;
    }
    if (!strcmp(attName,"GlyphSourceOption")){
      std::stringstream ss;
      ss << attValue;
      ss >> this->GlyphSourceOption;
      continue;
    }
      if (!strcmp(attName,"GlyphArrowScaleDirectional")){
        std::stringstream ss;
        ss << attValue;
        ss >> this->GlyphArrowScaleDirectional;
        continue;
      }
      if (!strcmp(attName,"GlyphArrowScaleIsotropic")){
        std::stringstream ss;
        ss << attValue;
        ss >> this->GlyphArrowScaleIsotropic;
        continue;
      }    
      if (!strcmp(attName,"GlyphArrowTipLength")){
        std::stringstream ss;
        ss << attValue;
        ss >> this->GlyphArrowTipLength;
        continue;
      }
      if (!strcmp(attName,"GlyphArrowTipRadius")){
        std::stringstream ss;
        ss << attValue;
        ss >> this->GlyphArrowTipRadius;
        continue;
      }
      if (!strcmp(attName,"GlyphArrowShaftRadius")){
        std::stringstream ss;
        ss << attValue;
        ss >> this->GlyphArrowShaftRadius;
        continue;
      }
      if (!strcmp(attName,"GlyphArrowResolution")){
        std::stringstream ss;
        ss << attValue;
        ss >> this->GlyphArrowResolution;
        continue;
      }
      
      if (!strcmp(attName,"GlyphConeScaleDirectional")){
        std::stringstream ss;
        ss << attValue;
        ss >> this->GlyphConeScaleDirectional;
        continue;
      }
      if (!strcmp(attName,"GlyphConeScaleIsotropic")){
        std::stringstream ss;
        ss << attValue;
        ss >> this->GlyphConeScaleIsotropic;
        continue;
      }
      if (!strcmp(attName,"GlyphConeHeight")){
        std::stringstream ss;
        ss << attValue;
        ss >> this->GlyphConeHeight;
        continue;
      }
      if (!strcmp(attName,"GlyphConeRadius")){
        std::stringstream ss;
        ss << attValue;
        ss >> this->GlyphConeRadius;
        continue;
      }
      if (!strcmp(attName,"GlyphConeResolution")){
        std::stringstream ss;
        ss << attValue;
        ss >> this->GlyphConeResolution;
        continue;
      }
      
      if (!strcmp(attName,"GlyphSphereResolution")){
        std::stringstream ss;
        ss << attValue;
        ss >> this->GlyphSphereResolution;
        continue;
      }
      
    if (!strcmp(attName,"GridScale")){
      std::stringstream ss;
      ss << attValue;
      ss >> this->GridScale;
      continue;
    }
    if (!strcmp(attName,"GridSpacingMM")){
      std::stringstream ss;
      ss << attValue;
      ss >> this->GridSpacingMM;
      continue;
    }        
    
    if (!strcmp(attName,"BlockScale")){
      std::stringstream ss;
      ss << attValue;
      ss >> this->BlockScale;
      continue;
    }  
    if (!strcmp(attName,"BlockDisplacementCheck")){
      std::stringstream ss;
      ss << attValue;
      ss >> this->BlockDisplacementCheck;
      continue;
    }      
    
    
    if (!strcmp(attName,"ContourNumber")){
      std::stringstream ss;
      ss << attValue;
      ss >> this->ContourNumber;
      continue;
    }
    /*
    if (!strcmp(attName,"ContourValues")){
      std::stringstream ss;
      ss << attValue;
      ss >> this->ContourValues;
      continue;
    }
    */
    if (!strcmp(attName,"ContourDecimation")){
      std::stringstream ss;
      ss << attValue;
      ss >> this->ContourDecimation;
      continue;
    }
    
    if (!strcmp(attName,"GlyphSlicePointMax")){
      std::stringstream ss;
      ss << attValue;
      ss >> this->GlyphSlicePointMax;
      continue;
    }  
    if (!strcmp(attName,"GlyphSliceThresholdMax")){
      std::stringstream ss;
      ss << attValue;
      ss >> this->GlyphSliceThresholdMax;
      continue;
    }  
    if (!strcmp(attName,"GlyphSliceThresholdMin")){
      std::stringstream ss;
      ss << attValue;
      ss >> this->GlyphSliceThresholdMin;
      continue;
    }  
    if (!strcmp(attName,"GlyphSliceScale")){
      std::stringstream ss;
      ss << attValue;
      ss >> this->GlyphSliceScale;
      continue;
    }    
    if (!strcmp(attName,"GlyphSliceSeed")){
      std::stringstream ss;
      ss << attValue;
      ss >> this->GlyphSliceSeed;
      continue;
    }    

    if (!strcmp(attName,"GridSliceScale")){
      std::stringstream ss;
      ss << attValue;
      ss >> this->GridSliceScale;
      continue;
    }  
    if (!strcmp(attName,"GridSliceSpacingMM")){
      std::stringstream ss;
      ss << attValue;
      ss >> this->GridSliceSpacingMM;
      continue;
    }          
  }

  this->WriteXML(std::cout,1);
}

//----------------------------------------------------------------------------
void vtkMRMLTransformVisualizerNode::WriteXML(ostream& of, int nIndent)
{
  Superclass::WriteXML(of, nIndent);
  vtkIndent indent(nIndent);
  
  of << indent << " GlyphPointMax=\""<< this->GlyphPointMax << "\"";
  of << indent << " GlyphScale=\""<< this->GlyphScale << "\"";
  of << indent << " GlyphThresholdMax=\""<< this->GlyphThresholdMax << "\"";
  of << indent << " GlyphThresholdMin=\""<< this->GlyphThresholdMin << "\"";
  of << indent << " GlyphSeed=\""<< this->GlyphSeed << "\"";
  of << indent << " GlyphSourceOption=\""<< this->GlyphSourceOption << "\"";
    of << indent << " GlyphArrowScaleDirectional=\"" << this->GlyphArrowScaleDirectional << "\"";
    of << indent << " GlyphArrowScaleIsotropic=\"" << this->GlyphArrowScaleIsotropic << "\"";
    of << indent << " GlyphArrowTipLength=\"" << this->GlyphArrowTipLength << "\"";
    of << indent << " GlyphArrowTipRadius=\""<< this->GlyphArrowTipRadius << "\"";
    of << indent << " GlyphArrowShaftRadius=\"" << this->GlyphArrowShaftRadius << "\"";
    of << indent << " GlyphArrowResolution=\"" << this->GlyphArrowResolution << "\"";
    of << indent << " GlyphConeScaleDirectional=\"" << this->GlyphConeScaleDirectional << "\"";
    of << indent << " GlyphConeScaleIsotropic=\"" << this->GlyphConeScaleIsotropic << "\"";
    of << indent << " GlyphConeHeight=\"" << this->GlyphConeHeight << "\"";
    of << indent << " GlyphConeRadius=\"" << this->GlyphConeRadius << "\"";
    of << indent << " GlyphConeResolution=\"" << this->GlyphConeResolution << "\"";
    of << indent << " GlyphSphereResolution=\"" << this->GlyphSphereResolution << "\"";
    
  of << indent << " GridScale=\""<< this->GridScale << "\"";
  of << indent << " GridSpacingMM=\""<< this->GridSpacingMM << "\"";
  
  of << indent << " BlockScale=\""<< this->BlockScale << "\"";
  of << indent << " BlockDisplacementCheck=\""<< this->BlockDisplacementCheck << "\"";
  
  of << indent << " ContourNumber=\""<< this->ContourNumber << "\"";
  //of << indent << " ContourValues=\""<< this->ContourValues << "\"";
  of << indent << " ContourDecimation=\""<< this->ContourDecimation << "\"";
 
  of << indent << " GlyphSlicePointMax=\""<< this->GlyphSlicePointMax << "\"";
  of << indent << " GlyphSliceThresholdMax=\""<< this->GlyphSliceThresholdMax << "\"";
  of << indent << " GlyphSliceThresholdMin=\""<< this->GlyphSliceThresholdMin << "\"";  
  of << indent << " GlyphSliceScale=\""<< this->GlyphSliceScale << "\"";
  of << indent << " GlyphSliceSeed=\""<< this->GlyphSliceSeed << "\"";    
  
  of << indent << " GridSliceScale=\""<< this->GridSliceScale << "\"";
  of << indent << " GridSliceSpacingMM=\""<< this->GridSliceSpacingMM << "\"";      
}

//----------------------------------------------------------------------------
void vtkMRMLTransformVisualizerNode::Copy(vtkMRMLNode *anode)
{
  Superclass::Copy(anode);
  vtkMRMLTransformVisualizerNode *node = vtkMRMLTransformVisualizerNode::SafeDownCast(anode);
  this->DisableModifiedEventOn();
  
  this->GlyphPointMax = node->GlyphPointMax;
  this->GlyphThresholdMax = node->GlyphThresholdMax;
  this->GlyphThresholdMin = node->GlyphThresholdMin;  
  this->GlyphSeed = node->GlyphSeed;
  this->GlyphSourceOption = node->GlyphSourceOption;
    this->GlyphArrowScaleDirectional = node->GlyphArrowScaleDirectional;
    this->GlyphArrowScaleIsotropic = node->GlyphArrowScaleIsotropic;  
    this->GlyphArrowTipLength = node->GlyphArrowTipLength;
    this->GlyphArrowTipRadius = node->GlyphArrowTipRadius;
    this->GlyphArrowShaftRadius = node->GlyphArrowShaftRadius;
    this->GlyphArrowResolution = node->GlyphArrowResolution;
    this->GlyphConeScaleDirectional = node->GlyphConeScaleDirectional;
    this->GlyphConeScaleIsotropic = node->GlyphConeScaleIsotropic;      
    this->GlyphConeHeight = node->GlyphConeHeight;
    this->GlyphConeRadius = node->GlyphConeRadius;
    this->GlyphConeResolution = node->GlyphConeResolution;
    this->GlyphSphereResolution = node->GlyphSphereResolution;

  this->GridScale = node->GridScale;
  this->GridSpacingMM = node->GridSpacingMM;
  
  this->BlockScale = node->BlockScale;
  this->BlockDisplacementCheck = node->BlockDisplacementCheck;
  
  this->ContourNumber = node->ContourNumber;
  //this->ContourValues = node->ContourValues;
  this->ContourDecimation = node->ContourDecimation;

  this->GlyphSlicePointMax = node->GlyphSlicePointMax;
  this->GlyphSliceThresholdMax = node->GlyphSliceThresholdMax;
  this->GlyphSliceThresholdMin = node->GlyphSliceThresholdMin;  
  this->GlyphSliceScale = node->GlyphSliceScale;
  this->GlyphSliceSeed = node->GlyphSliceSeed;
  
  this->GridSliceScale = node->GridSliceScale;
  this->GridSliceSpacingMM = node->GridSliceSpacingMM;  

  this->DisableModifiedEventOff();
  this->InvokePendingModifiedEvent();
}

//----------------------------------------------------------------------------
vtkMRMLNode* vtkMRMLTransformVisualizerNode::GetInputNode()
{
  return this->GetNodeReference(vtkMRMLTransformVisualizerNode::InputReferenceRole.c_str());
}

//----------------------------------------------------------------------------
void vtkMRMLTransformVisualizerNode::SetAndObserveInputNode(vtkMRMLNode* node)
{
  this->SetNthNodeReferenceID(vtkMRMLTransformVisualizerNode::InputReferenceRole.c_str(),0,node->GetID());
}

//----------------------------------------------------------------------------
vtkMRMLNode* vtkMRMLTransformVisualizerNode::GetReferenceVolumeNode()
{
  return this->GetNodeReference(vtkMRMLTransformVisualizerNode::ReferenceVolumeReferenceRole.c_str());
}

//----------------------------------------------------------------------------
void vtkMRMLTransformVisualizerNode::SetAndObserveReferenceVolumeNode(vtkMRMLNode* node)
{
  this->SetNthNodeReferenceID(vtkMRMLTransformVisualizerNode::ReferenceVolumeReferenceRole.c_str(),0,node->GetID());
}

//----------------------------------------------------------------------------
vtkMRMLNode* vtkMRMLTransformVisualizerNode::GetOutputModelNode()
{
  return this->GetNodeReference(vtkMRMLTransformVisualizerNode::OutputModelReferenceRole.c_str());
}

//----------------------------------------------------------------------------
void vtkMRMLTransformVisualizerNode::SetAndObserveOutputModelNode(vtkMRMLNode* node)
{
  this->SetNthNodeReferenceID(vtkMRMLTransformVisualizerNode::OutputModelReferenceRole.c_str(),0,node->GetID());
}

//----------------------------------------------------------------------------
vtkMRMLNode* vtkMRMLTransformVisualizerNode::GetGlyphSliceNode()
{
  return this->GetNodeReference(vtkMRMLTransformVisualizerNode::GlyphSliceReferenceRole.c_str());
}

//----------------------------------------------------------------------------
void vtkMRMLTransformVisualizerNode::SetAndObserveGlyphSliceNode(vtkMRMLNode* node)
{
  this->SetNthNodeReferenceID(vtkMRMLTransformVisualizerNode::GlyphSliceReferenceRole.c_str(),0,node->GetID());
}

//----------------------------------------------------------------------------
vtkMRMLNode* vtkMRMLTransformVisualizerNode::GetGridSliceNode()
{
  return this->GetNodeReference(vtkMRMLTransformVisualizerNode::GridSliceReferenceRole.c_str());
}

//----------------------------------------------------------------------------
void vtkMRMLTransformVisualizerNode::SetAndObserveGridSliceNode(vtkMRMLNode* node)
{
  this->SetNthNodeReferenceID(vtkMRMLTransformVisualizerNode::GridSliceReferenceRole.c_str(),0,node->GetID());
}

//----------------------------------------------------------------------------
void vtkMRMLTransformVisualizerNode::SetContourValues(double* values, int size)
{
  if (this->ContourValues) { delete [] this->ContourValues; }
  this->ContourValues = new double[size];
  if (values)
  {
    for (int i = 0;i<size;i++)
    {
      this->ContourValues[i] = values[i];
    }
  }
  else
  {
    this->ContourValues = NULL;
  }
}

//----------------------------------------------------------------------------
double* vtkMRMLTransformVisualizerNode::GetContourValues()
{
  return this->ContourValues;
}

//----------------------------------------------------------------------------
void vtkMRMLTransformVisualizerNode::PrintSelf(ostream& os, vtkIndent indent)
{
  Superclass::PrintSelf(os,indent);

  os << indent << " GlyphPointMax = "<< this->GlyphPointMax << "\n";
  os << indent << " GlyphScale = "<< this->GlyphScale << "\n";
  os << indent << " GlyphThresholdMax = "<< this->GlyphThresholdMax << "\n";
  os << indent << " GlyphThresholdMin = "<< this->GlyphThresholdMin << "\n";  
  os << indent << " GlyphSeed = "<< this->GlyphSeed << "\n";
  os << indent << " GlyphSourceOption = "<< this->GlyphSourceOption << "\n";
    os << indent << "   GlyphArrowScaleDirectional = " << this->GlyphArrowScaleDirectional << "\n";
    os << indent << "   GlyphArrowScaleIsotropic =  " << this->GlyphArrowScaleIsotropic << "\n";
    os << indent << "   GlyphArrowTipLength = " << this->GlyphArrowTipLength << "\n";
    os << indent << "   GlyphArrowTipRadius = "<< this->GlyphArrowTipRadius << "\n";
    os << indent << "   GlyphArrowShaftRadius =  " << this->GlyphArrowShaftRadius << "\n";
    os << indent << "   GlyphArrowResolution = " << this->GlyphArrowResolution << "\n";
    os << indent << "   GlyphConeScaleDirectional = " << this->GlyphConeScaleDirectional << "\n";
    os << indent << "   GlyphConeScaleIsotropic =  " << this->GlyphConeScaleIsotropic << "\n";
    os << indent << "   GlyphConeHeight = " << this->GlyphConeHeight << "\n";
    os << indent << "   GlyphConeRadius = " << this->GlyphConeRadius << "\n";
    os << indent << "   GlyphConeResolution = " << this->GlyphConeResolution << "\n";
    os << indent << "   GlyphSphereResolution = " << this->GlyphSphereResolution << "\n";
    
  os << indent << " GridScale = "<< this->GridScale << "\n";
  os << indent << " GridSpacingMM = "<< this->GridSpacingMM << "\n";
  
  os << indent << " BlockScale = "<< this->BlockScale << "\n";
  os << indent << " BlockDisplacementCheck = "<< this->BlockDisplacementCheck << "\n";
  
  os << indent << " ContourNumber = "<< this->ContourNumber << "\n";
  //os << indent << " ContourValues = "<< this->ContourValues << "\n";
  os << indent << " ContourDecimation = "<< this->ContourDecimation << "\n";

  os << indent << " GlyphSlicePointMax = "<< this->GlyphSlicePointMax << "\n";
  os << indent << " GlyphSliceThresholdMax = "<< this->GlyphSliceThresholdMax << "\n";
  os << indent << " GlyphSliceThresholdMin = "<< this->GlyphSliceThresholdMin << "\n";  
  os << indent << " GlyphSliceScale = "<< this->GlyphSliceScale << "\n";
  os << indent << " GlyphSliceSeed = "<< this->GlyphSliceSeed << "\n";    
   
  os << indent << " GridSliceScale = "<< this->GridSliceScale << "\n";
  os << indent << " GridSliceSpacingMM = "<< this->GridSliceSpacingMM << "\n";    
}

