/***************************************************************
 * Name:      CodeWriterApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Max Heller (max.heller94@web.de)
 * Created:   2010-12-14
 * Copyright: Max Heller ()
 * License:
 **************************************************************/

#include "wx_pch.h"
#include "CodeWriterApp.h"

//(*AppHeaders
#include "CodeWriterMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(CodeWriterApp);

bool CodeWriterApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	CodeWriterFrame* Frame = new CodeWriterFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
