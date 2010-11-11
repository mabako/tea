/*
Copyright (c) 2010 mabako

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include <list>
#include <assert.h>
#include <gtk/gtk.h>

class Window
{
public:
	 Window( );
	~Window( );
	
	static gint Pulse( gpointer data );
	static void Destroy( GtkWidget* pWidget, gpointer data );
	
	static void Pause( GtkWidget* pWidget, gpointer data );
private:
	void		Update( bool noUpdate = false );
	void		SetActive( bool b )	{ active = b; }
	const bool	GetActive( )		{ return active; }
	
	GtkWidget*	pgStatus;
	
	bool			active;
	unsigned long	seconds;
};
