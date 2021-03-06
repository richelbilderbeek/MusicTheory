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
#ifndef QTMUSICTHEORYMULTISCALEDIALOG_H
#define QTMUSICTHEORYMULTISCALEDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"
#include "musicchord.h"
#include "musicscale.h"
#pragma GCC diagnostic pop

namespace Ui {
class QtMusicTheoryMultiScaleDialog;
}

namespace ribi {

class QtMusicTheoryMultiScaleDialog : public QtHideAndShowDialog
{
  Q_OBJECT //!OCLINT
    
public:
  explicit QtMusicTheoryMultiScaleDialog(QWidget *parent = 0);
  QtMusicTheoryMultiScaleDialog(const QtMusicTheoryMultiScaleDialog&) = delete;
  QtMusicTheoryMultiScaleDialog& operator=(const QtMusicTheoryMultiScaleDialog&) = delete;
  ~QtMusicTheoryMultiScaleDialog() noexcept;

  void resizeEvent(QResizeEvent *);
    
private slots:
  //Called whenever there is a change
  //Cannot call this slot 'any_change', because this will result in the warning
  //'QMetaObject::connectSlotsByName: No matching signal for any_change()'
  void any_change();

private:
  Ui::QtMusicTheoryMultiScaleDialog *ui;

  void ConnectAll();

  Music::Note GetRoot1() const;
  Music::Note GetRoot2() const;

  void ShowNotes1();
  void ShowNotes2();

  bool UserWantsIt(const boost::shared_ptr<Music::Chord>& chord) const;
};

//Obtain the fitting chords in the scale
std::vector<boost::shared_ptr<Music::Chord>> FilterFittingChords(
  std::vector<boost::shared_ptr<Music::Chord>> chords,
  const boost::shared_ptr<Music::Scale>& scale
);


} //~namespace ribi

#endif // QTMUSICTHEORYMULTISCALEDIALOG_H
