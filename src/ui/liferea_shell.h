/**
 * @file ui_shell.h  UI layout handling
 *
 * Copyright (C) 2004-2005 Nathan J. Conrad <t98502@users.sourceforge.net>
 * Copyright (C) 2007-2008 Lars Lindner <lars.lindner@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 * 
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */
 
#ifndef _LIFEREA_SHELL_H
#define _LIFEREA_SHELL_H
 
#include <glib-object.h>
#include <glib.h>
#include <gtk/gtk.h>

#include "node.h"

/** possible main window states */
enum mainwindowState {
	MAINWINDOW_SHOWN,	/**< main window is visible */
	MAINWINDOW_MAXIMIZED,	/**< main window is visible and maximized */
	MAINWINDOW_ICONIFIED,	/**< main window is iconified */
	MAINWINDOW_HIDDEN	/**< main window is not visible at all */
};

G_BEGIN_DECLS

#define LIFEREA_SHELL_TYPE		(liferea_shell_get_type ())
#define LIFEREA_SHELL(obj)		(G_TYPE_CHECK_INSTANCE_CAST ((obj), LIFEREA_SHELL_TYPE, LifereaShell))
#define LIFEREA_SHELL_CLASS(klass)	(G_TYPE_CHECK_CLASS_CAST ((klass), LIFEREA_SHELL_TYPE, LifereaShellClass))
#define IS_LIFEREA_SHELL(obj)		(G_TYPE_CHECK_INSTANCE_TYPE ((obj), LIFEREA_SHELL_TYPE))
#define IS_LIFEREA_SHELL_CLASS(klass)	(G_TYPE_CHECK_CLASS_TYPE ((klass), LIFEREA_SHELL_TYPE))

typedef struct LifereaShell		LifereaShell;
typedef struct LifereaShellClass	LifereaShellClass;
typedef struct LifereaShellPrivate	LifereaShellPrivate;

extern LifereaShell *liferea_shell;

struct LifereaShell
{
	GObject		parent;
	
	/*< private >*/
	LifereaShellPrivate	*priv;
};

struct LifereaShellClass 
{
	GtkObjectClass parent_class;
};

GType liferea_shell_get_type	(void);

/**
 * Searches the glade XML UI tree for the given widget
 * name and returns the found widget.
 *
 * @param name	the widget name
 *
 * @returns the found widget or NULL
 */
GtkWidget * liferea_shell_lookup (const gchar *name);

/**
 * Set up the Liferea main window.
 *
 * @param initialState	state code MAINWINDOW_*
 */
void liferea_shell_create (int initialState);

/**
 * Destroys the global liferea_shell object.
 */
void liferea_shell_destroy (void);

/**
 * Presents the main window if it is hidden.
 */
void liferea_shell_present (void);

/**
 * Toggles main window visibility.
 */ 
void liferea_shell_toggle_visibility (void);

/**
 * Saves the current main window position to be
 * restored later using liferea_shell_present().
 */
void liferea_shell_save_position (void);

/**
 * Sets the toolbar to a particular style
 *
 * @param toolbar_style text string containing the type of style to use
 */
void liferea_shell_set_toolbar_style (const gchar *toolbar_style);

/**
 * According to the preferences this function enables/disables the toolbar.
 *
 * @todo: use signal instead
 */
void liferea_shell_update_toolbar (void);

/** 
 * Update the sensitivity of options affecting single feeds.
 *
 * @param add           TRUE if subscribing is to be enabled
 * @param enabled	TRUE if feed actions are to be enabled
 * @param readWrite	TRUE if feed list modifying actions are enabled
 *
 * @todo: use signal instead
 */
void liferea_shell_update_feed_menu (gboolean add, gboolean enabled, gboolean readWrite);

/** 
 * Update the sensitivity of options affecting single items.
 *
 * @param enabled	TRUE if item actions are to be enabled
 *
 * @todo: use signal instead
 */
void liferea_shell_update_item_menu (gboolean enabled);

/**
 * Update the sensitivity of options affecting item sets.
 *
 * @param isNotEmpty	TRUE if there is a non-empty item set active
 * @param isRead	TRUE if there are no unread items in the item set
 *
 * @todo: use signal instead
 */
void liferea_shell_update_allitems_actions (gboolean isNotEmpty, gboolean isRead);

/**
 * Set the sensitivity of items in the update menu.
 *
 * @param enabled	TRUE if menu options are to be enabled
 *
 * @todo: use signal instead
 */
void liferea_shell_update_update_menu (gboolean enabled);

/**
 * Updates the unread/new item count right beneath the status bar.
 *
 * @todo: use signal instead
 */
void liferea_shell_update_unread_stats (void);

/**
 * Sets the status bar text. Takes printf() like parameters.
 */
void liferea_shell_set_status_bar (const char *format, ...);

/**
 * Similar to liferea_shell_set_status_message(), but ensures
 * that messages stay visible and avoids that those messages
 * are overwritten by unimportant ones.
 */
void liferea_shell_set_important_status_bar (const char *format, ...);

/**
 * Changes the online state UI representation.
 *
 * @param online	1 = online, 0 = offline
 *
 * @todo: use signal instead
 */
void liferea_shell_online_status_changed(int online);

/**
 * Returns the Liferea main window.
 *
 * @returns main window widget
 */
GtkWidget * liferea_shell_get_window (void);

// FIXME:
void on_onlinebtn_clicked (GtkButton *button, gpointer user_data);

/**
 * Helper method to set up URL drop receiver
 *
 * @param widget	a widget that can receive URL drops
 */
void liferea_shell_setup_URL_receiver (GtkWidget *widget);

/**
 * Update the mode selection in the menu
 *
 * @param newMode	the new mode
 */
void liferea_shell_set_view_mode (nodeViewType newMode);

void liferea_shutdown (void);

G_END_DECLS
 
#endif