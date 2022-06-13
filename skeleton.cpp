//************************************************************************
//************************************************************************
// skeleton.cpp
// created: february 2019
// How to:
// - use 2 panels (one for controls, one for drawings)
// - manage basic events (so that controls impact drawings)
// with wxWidgets (3.0.2) 
// Author: Pascal Bertolino, UGA - GIPSA-lab laboratory, Grenoble - France
// Email pascal.bertolino@gipsa-lab.fr
// Web http://www.gipsa-lab.inpg.fr/~pascal.bertolino/
//
// tested with xWidget 3.0.2 under Linux and Windows 10
// Under Linux, compile then link as follows (with g++):
// g++ -c `wx-config --cxxflags` skeleton.cpp
// g++ -o skeleton skeleton.o `wx-config --libs`
//************************************************************************
//************************************************************************
// this skeleton includes 4 classes that are all derived from wxWidgets classes:
// the application class:	MyApp
// the main frame class:	MyFrame
// the left panel class:	MyControlPanel
// the right panel class:	MyDrawingPanel
//************************************************************************
//************************************************************************

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include<wx/filedlg.h>
#include <wx/image.h>
#include <wx/file.h>
#include <wx/bitmap.h>

//------------------------------------------------------------------------
// Some constants
//------------------------------------------------------------------------
#define APPLICATION_WIDTH	600
#define APPLICATION_HEIGHT	500 
#define WIDGET_PANEL_WIDTH	150
#define WIDGET_Y0			30
#define WIDGET_Y1			70
#define WIDGET_Y_STEP		90
#define APP_NAME "M1102 Skeleton 1.0"

//------------------------------------------------------------------------
// Some enums for widgets
//------------------------------------------------------------------------
enum
{
	ID_QUIT = 1,
	ID_ABOUT,
	ID_LOAD,
	ID_SAVE,
	ID_BUTTON1,
	ID_BUTTON2,
	ID_SLIDER1,
	ID_CHECKBOX1
};

//------------------------------------------------------------------------
// The class declarations
//------------------------------------------------------------------------
class MyControlPanel ;

//------------------------------------------------------------------------
class MyApp: public wxApp
//------------------------------------------------------------------------
{
    virtual bool OnInit() ;
};

//------------------------------------------------------------------------
class MyDrawingPanel: public wxPanel
//------------------------------------------------------------------------
{
public:
	MyDrawingPanel( wxWindow *parent ) ;
	void OpenFile(wxString fileName) ;
	void SaveFile(wxString fileName) ;

	//Var
	int btnSelected = 0;
	bool stepLine = false;
	wxPoint m_PointLinebase;
	wxPoint m_Point2Linebase;

private:
	void OnMouseMove(wxMouseEvent &event) ;
	void OnMouseLeftDown(wxMouseEvent &event) ;
	void OnPaint(wxPaintEvent &event) ;
	wxPoint m_mousePoint ;
	wxPoint m_onePoint ;
};

//------------------------------------------------------------------------
class MyControlPanel: public wxPanel
//------------------------------------------------------------------------
{
public:
	MyControlPanel( wxWindow *parent ) ;
	int GetSliderValue() {return m_slider->GetValue() ;} ;
	bool GetCheckBoxValue() {return m_checkBox->GetValue() ;} ;

private:
	void OnButton(wxCommandEvent &event) ;
	void OnSlider(wxScrollEvent &event) ;
	void OnCheckBox(wxCommandEvent &event) ;
	wxButton* m_button ;
	wxSlider* m_slider ;
	wxCheckBox* m_checkBox ;
};

//------------------------------------------------------------------------
class MyFrame: public wxFrame
//------------------------------------------------------------------------
{
public:
	MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
	MyControlPanel* GetControlPanel(){return m_controlPanel ;} ;
	void RefreshDrawing(){m_drawingPanel->Refresh() ;} ;

protected:
	void OnQuit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void OnOpenFile(wxCommandEvent& WXUNUSED(event) ) ;
	void OnSaveFile(wxCommandEvent & WXUNUSED(event)) ;
	void OnClose(wxCloseEvent& event) ;
	void OnSize(wxSizeEvent &event) ;

	MyControlPanel *m_controlPanel; // the panel with controls
	MyDrawingPanel *m_drawingPanel; // the panel in which we draw
} ;

//************************************************************************
//************************************************************************
// MyDrawingPanel class (where controls are displayed)
//************************************************************************
//************************************************************************

//------------------------------------------------------------------------
MyControlPanel::MyControlPanel(wxWindow *parent) : wxPanel(parent)
//------------------------------------------------------------------------
// In this constructor, create the controls and associate each of them (bind) a method
{
	///PANEAU DE CONTROLE A GAUCHE///

	int w, h, y ;
	GetParent()->GetSize(&w,&h) ;
	SetSize(wxRect(wxPoint(0,0), wxPoint(WIDGET_PANEL_WIDTH, h))) ;
	SetBackgroundColour(*wxLIGHT_GREY) ;

	//Ajout d'un bouton (Exemple)
	y = WIDGET_Y0 ;
	m_button = new wxButton(this, ID_BUTTON1, wxT("Click me"), wxPoint(10, y)) ;
	Bind(wxEVT_BUTTON, &MyControlPanel::OnButton, this, ID_BUTTON1) ;
	
	//Ajout d'un bouton (Pinceau)
	y = WIDGET_Y1 ; //Emplacement dans le panneau en fonction de la verticalité
	m_button = new wxButton(this, ID_BUTTON2, wxT("Pinceau"), wxPoint(10, y)) ;
	Bind(wxEVT_BUTTON, &MyControlPanel::OnButton, this, ID_BUTTON2) ;
	
	y+= WIDGET_Y_STEP ;
	wxStaticText* text1 = new wxStaticText(this, wxID_ANY, wxT("Radius"), wxPoint(10, y)) ;
	
	y+= 15 ;
	m_slider = new wxSlider(this, ID_SLIDER1, 10, 2, 100, wxPoint(10, y), wxSize(100,20)) ;
	Bind(wxEVT_SCROLL_THUMBTRACK, &MyControlPanel::OnSlider, this, ID_SLIDER1) ;	
	
	y+= WIDGET_Y_STEP ;
	m_checkBox = new wxCheckBox(this, ID_CHECKBOX1, "Show (x,y)", wxPoint(10, y), wxSize(100,20)) ;
	Bind(wxEVT_CHECKBOX, &MyControlPanel::OnCheckBox, this, ID_CHECKBOX1) ;	
}

//------------------------------------------------------------------------
void MyControlPanel::OnButton(wxCommandEvent &event)
//------------------------------------------------------------------------
{
//	char* s = GetCString() ;
//	wxMessageBox(wxString::FromAscii(s)) ; // call a C function located in the sample.cp module
//	free(s) ;

	btnSelected = event.GetId();
	switch(btnSelected){
		case ID_BUTTON2 :
			//A chaque nouveau pinceau on definit son action
			wxMessageBox(wxT("Pinceau activé")) ;
			break;
		default:
			wxMessageBox(wxT("Bouton inutilisé")) ;
			break;
	}

}

//------------------------------------------------------------------------
void MyControlPanel::OnSlider(wxScrollEvent &event)
//------------------------------------------------------------------------
{
	MyFrame* frame = (MyFrame*)GetParent() ;
	frame->RefreshDrawing() ;	// update the drawing panel
}

//------------------------------------------------------------------------
void MyControlPanel::OnCheckBox(wxCommandEvent &event)
//------------------------------------------------------------------------
{
	MyFrame* frame = (MyFrame*)GetParent() ;
	frame->RefreshDrawing() ;	// update the drawing panel
}

//************************************************************************
//************************************************************************
// MyDrawingPanel class (where drawings are displayed)
//************************************************************************
//************************************************************************

//------------------------------------------------------------------------
MyDrawingPanel::MyDrawingPanel(wxWindow *parent) : wxPanel(parent)
//------------------------------------------------------------------------
// In this constructor, bind some mouse events and the paint event with the appropriate methods
{
	int w, h ;
	GetParent()->GetClientSize(&w,&h) ;
	SetSize(wxRect(wxPoint(WIDGET_PANEL_WIDTH,0), wxPoint(w, h))) ;
	SetBackgroundColour(wxColour(0xFF,0xFF,0xFF)) ;
	Bind(wxEVT_MOTION, &MyDrawingPanel::OnMouseMove, this);
	Bind(wxEVT_LEFT_DOWN, &MyDrawingPanel::OnMouseLeftDown, this);
	Bind(wxEVT_PAINT, &MyDrawingPanel::OnPaint, this) ;
	m_onePoint.x = (w-WIDGET_PANEL_WIDTH)/2 ;
	m_onePoint.y = h/2 ;
	m_mousePoint = m_onePoint ;
}

//------------------------------------------------------------------------
void MyDrawingPanel::OnMouseMove(wxMouseEvent &event)
//------------------------------------------------------------------------
// called when the mouse is moved
{
	m_mousePoint.x = event.m_x ;
	m_mousePoint.y = event.m_y ;
	Refresh() ;	// send an event that calls the OnPaint method
}

//------------------------------------------------------------------------
void MyDrawingPanel::OnMouseLeftDown(wxMouseEvent &event)
//------------------------------------------------------------------------
// called when the mouse left button is pressed
{
	m_onePoint.x = event.m_x ;
	m_onePoint.y = event.m_y ;

	switch(btnSelected){
		case ID_BUTTON2 :
			//A chaque nouveau pinceau on definit son action
			if(!stepLine){
				m_PointLinebase = m_onePoint.x;
				stepLine = true;
			}
			else{
				m_Point2Linebase = m_onePoint.y;
				stepLine = false;
			}
			break;
		default:
			break;
	}


	Refresh() ; // send an event that calls the OnPaint method
}

//------------------------------------------------------------------------
void MyDrawingPanel::OnPaint(wxPaintEvent &event)
//------------------------------------------------------------------------
// called automatically when the panel is shown for the first time or
// when the panel is resized
// You have to call OnPaint with Refresh() when you need to update the panel content
{
	// read the control values
	MyFrame* frame =  (MyFrame*)GetParent() ;
	int radius = frame->GetControlPanel()->GetSliderValue() ;
	bool check = frame->GetControlPanel()->GetCheckBoxValue() ;

	// then paint
	wxPaintDC dc(this);	
		
	dc.DrawLine(m_mousePoint, m_onePoint) ;
	if(m_PointLinebase != NULL && m_Point2Linebase != NULL){dc.DrawLine(m_PointLinebase, m_Point2Linebase) ;}
	dc.DrawRectangle(wxPoint(m_onePoint.x-radius/2, m_onePoint.y-radius/2), wxSize(radius,radius)) ;
	dc.DrawCircle(wxPoint(m_mousePoint), radius/2) ;
	
	if (check)
	{
		wxString coordinates ;
		coordinates.sprintf(wxT("(%d,%d)"), m_mousePoint.x, m_mousePoint.y) ;
		dc.DrawText(coordinates, wxPoint(m_mousePoint.x, m_mousePoint.y+20)) ;
	}
}

//------------------------------------------------------------------------
void MyDrawingPanel::OpenFile(wxString fileName)
//------------------------------------------------------------------------
{
	// just to open (and close) any file 
	FILE* f = fopen(fileName, "r") ;
	if (f)
	{
		wxMessageBox(wxT("The file was opened then closed")) ;
		fclose(f) ;
	}
}

//------------------------------------------------------------------------
void MyDrawingPanel::SaveFile(wxString fileName)
//------------------------------------------------------------------------
{
	// just to create a tiny file
	FILE* f = fopen(fileName, "w") ;
	if (!f)
		wxMessageBox(wxT("Cannot save file"));
	else
	{
		fprintf(f, "S1102 software can create and write a file") ;
		wxMessageBox(wxT("The file was saved")) ;
		fclose(f) ;
	}
}

//************************************************************************
//************************************************************************
// Frame class (the main window)
//************************************************************************
//************************************************************************

//------------------------------------------------------------------------
MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
       : wxFrame((wxFrame *)NULL, -1, title, pos, size)
//------------------------------------------------------------------------
// The constructor of the main frame that creates the menu stuffs and the 2 panels
{
	wxMenu *fileMenu = new wxMenu();
	fileMenu->Append(ID_LOAD, wxT("&Open file..."));
	fileMenu->Append(ID_SAVE, wxT("&Save file..."));
	fileMenu->Append(ID_ABOUT, wxT("&About..."));
	fileMenu->AppendSeparator();
	fileMenu->Append(ID_QUIT, wxT("&Exit"));

	wxMenuBar *menuBar = new wxMenuBar();
	menuBar->Append(fileMenu, wxT("&File"));

	Bind(wxEVT_MENU, &MyFrame::OnOpenFile, this, ID_LOAD);
	Bind(wxEVT_MENU, &MyFrame::OnSaveFile, this, ID_SAVE);
	Bind(wxEVT_MENU, &MyFrame::OnQuit, this, ID_QUIT);
	Bind(wxEVT_MENU, &MyFrame::OnAbout, this, ID_ABOUT);
	Bind(wxEVT_CLOSE_WINDOW, &MyFrame::OnClose, this);
	Bind(wxEVT_SIZE, &MyFrame::OnSize, this);

	SetMenuBar( menuBar );

// create the panel that will contain the controls
	m_controlPanel = new MyControlPanel(this);
// create the panel that will display the graphics
	m_drawingPanel = new MyDrawingPanel(this);
	CreateStatusBar() ;
	SetStatusText(wxT("click in the right panel and tune the controls of the left panel. Visit the File menu!")) ;
	Centre() ; // Guess what it does ;-)
}

//------------------------------------------------------------------------
void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
//------------------------------------------------------------------------
{
	Close(true) ;
}

//------------------------------------------------------------------------
void MyFrame::OnClose(wxCloseEvent& event)
//------------------------------------------------------------------------
{
	delete m_controlPanel ;
	delete m_drawingPanel ;
	event.Skip() ;
}

//------------------------------------------------------------------------
void MyFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
//------------------------------------------------------------------------
{
	wxMessageBox(wxT("How to .. \n\n- use 2 panels (one for controls, one for drawings)\n- manage basic events (so that controls impact drawings)\n\n... with wxWidgets (3.0.2)\n\nPascal Bertolino UGA - GIPSA-lab, Grenoble - France\npascal.bertolino@gipsa-lab.fr"),
                  wxT(APP_NAME), wxOK | wxICON_INFORMATION ) ;
}

//------------------------------------------------------------------------
void MyFrame::OnOpenFile(wxCommandEvent& WXUNUSED(event) )
//------------------------------------------------------------------------
{
	wxString filename = wxFileSelector(wxT("Select file"));
	if ( !filename.empty() )
		m_drawingPanel->OpenFile(filename) ;
}

//------------------------------------------------------------------------
void MyFrame::OnSaveFile(wxCommandEvent & WXUNUSED(event))
//------------------------------------------------------------------------
{
	wxString filename = wxSaveFileSelector(wxT("Save file as"), wxT("*.txt"), wxT("data"));
	if ( !filename.empty() )
		m_drawingPanel->SaveFile(filename) ;
}

//------------------------------------------------------------------------
void MyFrame::OnSize(wxSizeEvent &event)
//------------------------------------------------------------------------
// Called when you resize the frame
{
	int w, h ;
	GetSize(&w,&h) ;	
	m_controlPanel->SetSize(wxRect(wxPoint(0,0), wxPoint(WIDGET_PANEL_WIDTH, h))) ;
	m_drawingPanel->SetSize(wxRect(wxPoint(WIDGET_PANEL_WIDTH,0), wxPoint(w, h))) ;
}

//************************************************************************
//************************************************************************
// Application class
//************************************************************************
//************************************************************************

IMPLEMENT_APP(MyApp) // macro that contains the main() function

//------------------------------------------------------------------------
bool MyApp::OnInit()
//------------------------------------------------------------------------
{
	MyFrame *frame = new MyFrame(wxT(APP_NAME), wxDefaultPosition, wxSize(APPLICATION_WIDTH,APPLICATION_HEIGHT)) ;
	frame->Show(true) ;
	SetTopWindow(frame) ;
	return true ;
}
