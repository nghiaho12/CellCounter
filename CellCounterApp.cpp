/***************************************************************
 * Name:      CellCounterApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Nghia Ho (nghiaho12@yahoo.com)
 * Created:   2011-11-20
 * Copyright: Nghia Ho (http://nghiaho.com)
 * License:
 **************************************************************/

#include "CellCounterApp.h"

//(*AppHeaders
#include "CellCounterMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(CellCounterApp);

static CellCounterFrame *g_frame = NULL;

bool CellCounterApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	CellCounterFrame* Frame = new CellCounterFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
		
		g_frame = Frame;
    }
    //*)

    return wxsOK;
}

int CellCounterApp::FilterEvent(wxEvent& event)
{
    if ((event.GetEventType() == wxEVT_KEY_DOWN) && (((wxKeyEvent&)event).GetKeyCode() == 'S')) {
        g_frame->SwitchViews();
        return true;
    }
 
    return -1;
}