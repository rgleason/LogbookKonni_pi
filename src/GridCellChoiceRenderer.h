/**
 * Copyright (c) 2011-2013 Konnibe
 * Copyright (c) 2013-2015 Del Edson
 * Copyright (c) 2015-2021 Peter Tulp
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _GRIDCELLCHOICERENDERER_H_INCLUDED_
#define _GRIDCELLCHOICERENDERER_H_INCLUDED_

#include "wx/grid.h"
#include "wx/laywin.h"

class wxGridCellChoiceRenderer : public wxGridCellStringRenderer
{
public:
    wxGridCellChoiceRenderer( wxLayoutAlignment border = wxLAYOUT_NONE ) :
        m_border( border ) {}
    ~wxGridCellChoiceRenderer( void ) {}
    void Draw( wxGrid& grid,
               wxGridCellAttr& attr,
               wxDC& dc,
               const wxRect& rect,
               int row, int col,
               bool isSelected );
    wxGridCellRenderer *Clone() const
    {
        return new wxGridCellChoiceRenderer;
    }
private:
    wxLayoutAlignment m_border;
};


#endif // _GRIDCELLCHOICERENDERER_H_INCLUDED_
