//**************************************************************************/
// Copyright (c) 1998-2007 Autodesk, Inc.
// All rights reserved.
// 
// These coded instructions, statements, and computer programs contain
// unpublished proprietary information written by Autodesk, Inc., and are
// protected by Federal copyright law. They may not be disclosed to third
// parties or copied or duplicated in any form, in whole or in part, without
// the prior written consent of Autodesk, Inc.
//**************************************************************************/
// DESCRIPTION: Appwizard generated plugin
// AUTHOR: 
//***************************************************************************/

#include "DiamondSquare.h"
#include "Grid.h"

#define DiamondSquare_CLASS_ID	Class_ID(0x650bae02, 0x9cf1b258)

#define PBLOCK_REF	0

#define MIN_WIDTH 1.0f
#define MIN_LENGTH 1.0f

class DiamondSquare : public SimpleObject2
{
public:
    //Constructor/Destructor
    DiamondSquare();
    virtual ~DiamondSquare();

    // Parameter block handled by parent
    static IObjParam *ip; // Access to the interface

    // From BaseObject
    virtual CreateMouseCallBack* GetCreateMouseCallBack();

    // From Object
    virtual BOOL HasUVW();
    virtual void SetGenUVW(BOOL sw);
    virtual int CanConvertToType(Class_ID obtype);
    virtual Object* ConvertToType(TimeValue t, Class_ID obtype);
    virtual void GetCollapseTypes(Tab<Class_ID>& clist,Tab<TSTR*>& nlist);
    virtual int IntersectRay(TimeValue t, Ray& ray, float& at, Point3& norm);

    // From Animatable
    virtual void BeginEditParams( IObjParam  *ip, ULONG flags,Animatable *prev);
    virtual void EndEditParams( IObjParam *ip, ULONG flags,Animatable *next);

    // From SimpleObject
    virtual void BuildMesh(TimeValue t);
    virtual void InvalidateUI();

    //From Animatable
    virtual Class_ID ClassID() {return DiamondSquare_CLASS_ID;}
    virtual SClass_ID SuperClassID() { return GEOMOBJECT_CLASS_ID; }
    virtual void GetClassName(TSTR& s) {s = GetString(IDS_CLASS_NAME);}

    virtual RefTargetHandle Clone( RemapDir& remap );

    virtual int NumParamBlocks() { return 1; }					// return number of ParamBlocks in this instance
    virtual IParamBlock2* GetParamBlock(int /*i*/) { return pblock2; } // return i'th ParamBlock
    virtual IParamBlock2* GetParamBlockByID(BlockID id) { return (pblock2->ID() == id) ? pblock2 : NULL; } // return id'd ParamBlock

    void DeleteThis() { delete this; }
};



class DiamondSquareClassDesc : public ClassDesc2 
{
public:
    virtual int IsPublic() 							{ return TRUE; }
    virtual void* Create(BOOL /*loading = FALSE*/) 		{ return new DiamondSquare(); }
    virtual const TCHAR *	ClassName() 			{ return GetString(IDS_CLASS_NAME); }
    virtual SClass_ID SuperClassID() 				{ return GEOMOBJECT_CLASS_ID; }
    virtual Class_ID ClassID() 						{ return DiamondSquare_CLASS_ID; }
    virtual const TCHAR* Category() 				{ return GetString(IDS_CATEGORY); }

    virtual const TCHAR* InternalName() 			{ return _T("DiamondSquare"); }	// returns fixed parsable name (scripter-visible name)
    virtual HINSTANCE HInstance() 					{ return hInstance; }					// returns owning module handle
    

};


ClassDesc2* GetDiamondSquareDesc() { 
    static DiamondSquareClassDesc DiamondSquareDesc;
    return &DiamondSquareDesc; 
}





enum { diamondsquare_params };


//TODO: Add enums for various parameters
enum { 
    pb_width,
    pb_length,
    pb_dims
};




static ParamBlockDesc2 diamondsquare_param_blk ( diamondsquare_params, _T("params"),  0, GetDiamondSquareDesc(), 
    P_AUTO_CONSTRUCT + P_AUTO_UI, PBLOCK_REF, 
    //rollout
    IDD_PANEL, IDS_PARAMS, 0, 0, NULL,
    // params
    pb_width,			_T("width"),		    TYPE_FLOAT,		0,          		IDS_WIDTH,
        p_default,		100.0f,
        p_range,		MIN_WIDTH,1000000.0f,
        p_ui,           TYPE_SPINNER,   EDITTYPE_UNIVERSE,  IDC_WIDTH_EDIT,		    IDC_WIDTH_SPIN,			0.1f,
        p_end,
    pb_length,			_T("length"),		    TYPE_FLOAT,		0,          		IDS_LENGTH,
        p_default,		100.0f,
        p_range,	    MIN_LENGTH,1000000.0f,
        p_ui,			TYPE_SPINNER,   EDITTYPE_UNIVERSE,	IDC_LENGTH_EDIT,	    IDC_LENGTH_SPIN,		0.1f,
        p_end,
    pb_dims,             _T("dimensions"),       TYPE_INT,       0,                  IDS_DIM,
        p_default,      4,
        p_range,        2, 12,
        p_ui,			TYPE_SPINNER,	EDITTYPE_INT,	    IDC_DIM_EDIT,           IDC_DIM_SPIN,           0.05f,
        p_end,
    p_end
    );




//--- DiamondSquare -------------------------------------------------------

IObjParam* DiamondSquare::ip = NULL;

DiamondSquare::DiamondSquare()
{
    GetDiamondSquareDesc()->MakeAutoParamBlocks(this);
}

DiamondSquare::~DiamondSquare()
{
}

void DiamondSquare::BeginEditParams(IObjParam* ip, ULONG flags, Animatable* prev)
{
    this->ip = ip;

    SimpleObject2::BeginEditParams(ip,flags,prev);
    GetDiamondSquareDesc()->BeginEditParams(ip, this, flags, prev);
}

void DiamondSquare::EndEditParams( IObjParam* ip, ULONG flags, Animatable* next )
{
    //TODO: Save plugin parameter values into class variables, if they are not hosted in ParamBlocks. 
    SimpleObject2::EndEditParams(ip,flags,next);
    GetDiamondSquareDesc()->EndEditParams(ip, this, flags, next);

    this->ip = NULL;
}

//From Object
BOOL DiamondSquare::HasUVW() 
{ 
    //TODO: Return whether the object has UVW coordinates or not
    return TRUE; 
}

void DiamondSquare::SetGenUVW(BOOL sw) 
{
    if (sw==HasUVW()) 
        return;
    //TODO: Set the plugin's internal value to sw
}

//Class for interactive creation of the object using the mouse
class DiamondSquareCreateCallBack : public CreateMouseCallBack {
    IPoint2 sp0;              //First point in screen coordinates
    DiamondSquare* ob; //Pointer to the object 
    Point3 p0;                //First point in world coordinates
    Point3 p1;                //Second point in world coordinates
public:	
    int proc( ViewExp *vpt,int msg, int point, int flags, IPoint2 m, Matrix3& mat);
    void SetObj(DiamondSquare *obj) {ob = obj;}
};

int DiamondSquareCreateCallBack::proc(ViewExp *vpt,int msg, int point, int /*flags*/, IPoint2 m, Matrix3& mat )
{
    //TODO: Implement the mouse creation code here
    if ( ! vpt || ! vpt->IsAlive() )
    {
        // why are we here
        DbgAssert(!_T("Invalid viewport!"));
        return FALSE;
    }

    if (msg == MOUSE_POINT || msg == MOUSE_MOVE) {
        switch(point) {
            case 0: // only happens with MOUSE_POINT msg
                ob->suspendSnap = TRUE;
                sp0 = m;
                p0 = vpt->SnapPoint(m,m,NULL,SNAP_IN_PLANE);
                mat.SetTrans(p0);

                //Set a default overall size in the parameter block
                ob->pblock2->SetValue(pb_width, ob->ip->GetTime(), 0.0f);
                ob->pblock2->SetValue(pb_length, ob->ip->GetTime(), 0.0f);
                break;
            case 1:
            {
                ob->suspendSnap = TRUE; 
                p1 = vpt->SnapPoint(m,m,NULL,SNAP_IN_PLANE);
                Point3 diff = p1 - p0;
                mat.SetTrans(p0 + diff / 2.0f);
                
                //Set the overall size in parameter block
                ob->pblock2->SetValue(pb_width, ob->ip->GetTime(), abs(diff.x));
                ob->pblock2->SetValue(pb_length, ob->ip->GetTime(), abs(diff.y));

                //Invalidate and display the mesh in the viewport
                diamondsquare_param_blk.InvalidateUI();
                break;
            }
            case 2: // happens when user releases mouse
            {
                ob->suspendSnap = TRUE; 
                p1 = vpt->SnapPoint(m,m,NULL,SNAP_IN_PLANE);
                Point3 diff = p1 - p0;
                
                if (abs(diff.x) < MIN_WIDTH || abs(diff.y) < MIN_LENGTH)
                {
                    return CREATE_ABORT; // abort if the size is too small
                }
                else
                {
                    return CREATE_STOP;
                }
            }
        }
    } else {
        if (msg == MOUSE_ABORT) return CREATE_ABORT;
    }

    return TRUE;
}

static DiamondSquareCreateCallBack DiamondSquareCreateCB;

//From BaseObject
CreateMouseCallBack* DiamondSquare::GetCreateMouseCallBack() 
{
    DiamondSquareCreateCB.SetObj(this);
    return(&DiamondSquareCreateCB);
}

static float GetWrap(float* arr, int len, int width, int i, int j)
{
    i = i % len;
    j = j % len;

    return *(arr + i * width + j);
}

static void SetWrap(float* arr, int len, int width, int i, int j, float val)
{
    i = i % len;
    j = j % len;
    
    *(arr + i * width + j) = val;
}

//From SimpleObject
void DiamondSquare::BuildMesh(TimeValue /*t*/)
{
    //TODO: Implement the code to build the mesh representation of the object
    //      using its parameter settings at the time passed. The plug-in should 
    //      use the data member mesh to store the built mesh.
    //      SimpleObject ivalid member should be updated. This can be done while
    //      retrieving values from pblock2.
    ivalid = FOREVER;

    float width = pblock2->GetFloat(pb_width, 0);
    float length = pblock2->GetFloat(pb_length, 0);

    int dims = pblock2->GetInt(pb_dims, 0);
    int segs = 0x1 << dims; // 2^dims
    Grid *grid = new Grid(width, length, segs);
    grid->DiamondSquare(12345, 1.0, 10.0);

    int faces_x = grid->GetWidthSegs();
    int faces_y = grid->GetLengthSegs();
    int vertices_x = grid->GetWidthVertices();
    int vertices_y = grid->GetLengthVertices();
    int numVerts = vertices_x * vertices_y;
    int numFaces = faces_x * faces_y * 2; // Double number of quads to make tris.

    float halfWidth = width / 2.0f;
    float halfLength = length / 2.0f;

    mesh.setNumVerts(numVerts);
    mesh.setNumFaces(numFaces);
    mesh.setNumTVerts(numVerts);
    mesh.setNumTVFaces(numFaces);

    int vtx = 0;
    float max_u = (float)faces_x, max_v = (float)faces_y;
    for (int i = 0; i < vertices_x; i++)
    {
        for (int j = 0; j < vertices_y; j++)
        {
            Point3 pt(i * width / faces_x - halfWidth, j * length / faces_y - halfLength, grid->GetVertexHeightWrap(i, j));
            mesh.setVert(vtx, pt);
            mesh.setTVert(vtx, i / max_u, j / max_v, 0.0f);
            ++vtx;
        }
    }

    int face = 0;
    for (int i = 0; i < faces_x; i++)
    {
        for (int j = 0; j < faces_y; j++)
        {
            int pt1 = (i+1) * vertices_y + j;
            int pt2 = (i+1) * vertices_y + j + 1;
            int pt3 = i * vertices_y + j + 1;
            int pt4 = i * vertices_y + j;

            mesh.faces[face].setVerts(pt1, pt2, pt3);
            mesh.faces[face].setEdgeVisFlags(1, 1, 0);
            mesh.faces[face].setSmGroup(1);
            mesh.tvFace[face].setTVerts(pt1, pt2, pt3);
            ++face;

            mesh.faces[face].setVerts(pt3, pt4, pt1);
            mesh.faces[face].setEdgeVisFlags(1, 1, 0);
            mesh.faces[face].setSmGroup(1);
            mesh.tvFace[face].setTVerts(pt3, pt4, pt1);
            ++face;
        }
    }

    delete grid;

    mesh.InvalidateGeomCache();
}

void DiamondSquare::InvalidateUI() 
{
    // Hey! Update the param blocks
    pblock2->GetDesc()->InvalidateUI();
}

Object* DiamondSquare::ConvertToType(TimeValue t, Class_ID obtype)
{
    //TODO: If the plugin can convert to a nurbs surface then check to see 
    //      whether obtype == EDITABLE_SURF_CLASS_ID and convert the object
    //      to nurbs surface and return the object
    //      If no special conversion is needed remove this implementation.
    
    return SimpleObject::ConvertToType(t,obtype);
}

int DiamondSquare::CanConvertToType(Class_ID obtype)
{
    //TODO: Check for any additional types the plugin supports
    //      If no special conversion is needed remove this implementation.
    return SimpleObject::CanConvertToType(obtype);
}

// From Object
int DiamondSquare::IntersectRay(TimeValue /*t*/, Ray& /*ray*/, float& /*at*/, Point3& /*norm*/)
{
    //TODO: Return TRUE after you implement this method
    return FALSE;
}

void DiamondSquare::GetCollapseTypes(Tab<Class_ID>& clist,Tab<TSTR*>& nlist)
{
    Object::GetCollapseTypes(clist, nlist);
    //TODO: Append any any other collapse type the plugin supports
}

// From ReferenceTarget
RefTargetHandle DiamondSquare::Clone(RemapDir& remap) 
{
    DiamondSquare* newob = new DiamondSquare();	
    //TODO: Make a copy all the data and also clone all the references
    newob->ReplaceReference(0,remap.CloneRef(pblock2));
    newob->ivalid.SetEmpty();
    BaseClone(this, newob, remap);
    return(newob);
}
