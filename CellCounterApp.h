/***************************************************************
 * Name:      CellCounterApp.h
 * Purpose:   Defines Application Class
 * Author:    Nghia Ho (nghiaho12@yahoo.com)
 * Created:   2011-11-20
 * Copyright: Nghia Ho (http://nghiaho.com)
 * License:
 **************************************************************/

#ifndef CELLCOUNTERAPP_H
#define CELLCOUNTERAPP_H

#include <wx/app.h>

class CellCounterApp : public wxApp
{
    public:
        virtual bool OnInit();
		virtual int FilterEvent(wxEvent& event); // used to catch keytrokes globally
};

#endif // CELLCOUNTERAPP_H
