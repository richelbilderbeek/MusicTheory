//---------------------------------------------------------------------------
/*
MusicTheory, tool for visualizing my music theory
Copyright (C) 2012-2015 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ToolMusicTheory.htm
//---------------------------------------------------------------------------
#ifndef QTMUSICTHEORYSINGLESCALEDIALOG_H
#define QTMUSICTHEORYSINGLESCALEDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"
#include "musicchord.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtMusicTheorySingleScaleDialog;
}

namespace ribi {

class QtMusicTheorySingleScaleDialog : public QtHideAndShowDialog
{
  Q_OBJECT //!OCLINT
    
public:
  explicit QtMusicTheorySingleScaleDialog(QWidget *parent = 0);
  QtMusicTheorySingleScaleDialog(const QtMusicTheorySingleScaleDialog&) = delete;
  QtMusicTheorySingleScaleDialog& operator=(const QtMusicTheorySingleScaleDialog&) = delete;
  ~QtMusicTheorySingleScaleDialog() noexcept;

  void resizeEvent(QResizeEvent *);
    
private slots:
  void any_change();

private:
  Ui::QtMusicTheorySingleScaleDialog *ui;

  bool UserWantsIt(const boost::shared_ptr<Music::Chord>& chord) const;
};

} //~namespace ribi

#endif // QTMUSICTHEORYSINGLESCALEDIALOG_H
