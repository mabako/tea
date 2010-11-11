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

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include "window.hpp"

Window::Window( )
{
	active = true;
	seconds = 0;
	
	/* Create the window */
	GtkWidget* pgWindow = gtk_window_new( GTK_WINDOW_TOPLEVEL );
	
	/* adjust some properties */
	gtk_window_set_title( GTK_WINDOW( pgWindow ), "Tea" );
	gtk_window_set_default_size( GTK_WINDOW( pgWindow ), 200, 60 );
	gtk_window_set_policy( GTK_WINDOW( pgWindow), true, true, false );
	gtk_container_set_border_width( GTK_CONTAINER( pgWindow ), 5 );
	
	/* Create a layout */
	GtkWidget* pLayout = gtk_table_new( 2, 1, TRUE );
	gtk_table_set_col_spacings( GTK_TABLE( pLayout ), 3 );
	gtk_table_set_row_spacings( GTK_TABLE( pLayout ), 3 );
	gtk_container_add( GTK_CONTAINER( pgWindow ), pLayout );
	
	/* Time label */
	pgStatus = gtk_label_new( "" );
	gtk_table_attach_defaults( GTK_TABLE( pLayout ), pgStatus, 0, 1, 0, 1 );
	Update( true );
	
	/* Pause/Continue */
	GtkWidget* pButtonPause = gtk_button_new_with_label( "Pause" );
	gtk_table_attach_defaults( GTK_TABLE( pLayout ), pButtonPause, 0, 1, 1, 2 );
	gtk_signal_connect( GTK_OBJECT( pButtonPause ), "clicked", GTK_SIGNAL_FUNC( &Pause ), this );
	
	/* Show our windows */
	gtk_widget_show_all( pgWindow );
	
	/* we want to be updated! */
	gtk_timeout_add( 1000, &Pulse, this );
	
	/* Closing handler */
	g_signal_connect_swapped( G_OBJECT( pgWindow ), "destroy", G_CALLBACK( &Destroy ), this );
}

/* Should we even do this? GTK can handle deletion of its widgets? */
Window::~Window( )
{
}

/* Called whenever we click 'Close' or the X. Obviously we want to exit */
void Window::Destroy( GtkWidget* pWidget, gpointer data )
{
	/* Let GTK handle itself. */
	gtk_main_quit( );
}

/* Called to let us handle our internal stuff. */
gint Window::Pulse( gpointer data )
{
	Window* pWindow = static_cast < Window* > ( data );
	assert( pWindow );
	
	pWindow->Update( );
}

/* Update status label */
void Window::Update( bool noUpdate )
{
	if( active || noUpdate )
	{
		if( !noUpdate )
			++ seconds;
		
		GString* temp = g_string_new( NULL );
		g_string_sprintf( temp, "<span size=\"x-large\">%lu days %02lu:%02lu:%02lu</span>", seconds / ( 24 * 3600 ), ( seconds / 3600 ) % 24, ( seconds / 60 ) % 60, seconds % 60 );
		gtk_label_set_markup( GTK_LABEL( pgStatus ), temp->str );
	}
}

void Window::Pause( GtkWidget* pWidget, gpointer data )
{
	Window* pWindow = static_cast < Window* > ( data );
	assert( pWindow );
	
	if( pWindow->GetActive( ) )
	{
		pWindow->SetActive( false );
		gtk_button_set_label( GTK_BUTTON( pWidget ), ( gchar* ) "Continue" );
	}
	else
	{
		pWindow->SetActive( true );
		gtk_button_set_label( GTK_BUTTON( pWidget ), ( gchar* ) "Pause" );
	}
}
