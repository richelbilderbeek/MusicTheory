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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtmusictheorysinglescaledialog.h"

#include <cassert>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include <QGraphicsScene>
#include <QGraphicsView>

#include "musicchord.h"
#include "musicnote.h"
#include "musicscale.h"
#include "qtchordvertex.h"
#include "trace.h"
#include "ui_qtmusictheorysinglescaledialog.h"

#pragma GCC diagnostic pop

ribi::QtMusicTheorySingleScaleDialog::QtMusicTheorySingleScaleDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtMusicTheorySingleScaleDialog)
{
  ui->setupUi(this);

  //Put all available scales in the scales combobox
  {
    ui->scale->clear();
    const std::vector<boost::shared_ptr<Music::Scale> > v = Music::Scale::CreateScales(Music::Note(0));
    std::for_each(v.begin(),v.end(),
      [this](const boost::shared_ptr<Music::Scale>& scale)
      {
        ui->scale->addItem(scale->GetName().c_str());
      }
    );
  }

  QObject::connect(
    ui->scale, SIGNAL(currentIndexChanged(int)),
    this, SLOT(any_change())
  );
  QObject::connect(ui->root,SIGNAL(currentIndexChanged(int)),this,SLOT(any_change()));
  QObject::connect(ui->display_major,SIGNAL(stateChanged(int)),this,SLOT(any_change()));
  QObject::connect(ui->display_minor,SIGNAL(stateChanged(int)),this,SLOT(any_change()));
  QObject::connect(ui->display_aug,SIGNAL(stateChanged(int)),this,SLOT(any_change()));
  QObject::connect(ui->display_dim,SIGNAL(stateChanged(int)),this,SLOT(any_change()));
  QObject::connect(ui->display_6,SIGNAL(stateChanged(int)),this,SLOT(any_change()));
  QObject::connect(ui->display_m6,SIGNAL(stateChanged(int)),this,SLOT(any_change()));
  QObject::connect(ui->display_7,SIGNAL(stateChanged(int)),this,SLOT(any_change()));
  QObject::connect(ui->display_m7,SIGNAL(stateChanged(int)),this,SLOT(any_change()));

  //any_change();
}

ribi::QtMusicTheorySingleScaleDialog::~QtMusicTheorySingleScaleDialog() noexcept
{
  delete ui;
}

void ribi::QtMusicTheorySingleScaleDialog::any_change()
{
  //this->setWindowTitle( QString::number( std::rand() ));  //Display the notes
  //Obtain the root
  const Music::Note root(ui->root->currentText().toStdString());

  //Obtain the scale
  const boost::shared_ptr<Music::Scale> scale = Music::Scale::CreateScale(
    ui->scale->currentText().toLower().toStdString(),root);

  //Obtain the notes in the scale
  const std::vector<Music::Note> notes = scale->GetNotes();
  std::string notes_str;
  std::for_each(notes.begin(),notes.end(),
    [&notes_str](const Music::Note& note)
    {
      notes_str+=note.ToStr();
      notes_str+="-";
    }
  );
  notes_str.resize(notes_str.size() - 1);
  ui->notes->setText(notes_str.c_str());

  //Obtain the fitting chords in the scale
  std::vector<boost::shared_ptr<Music::Chord> > chords = Music::Chord::CreateAllChords();
  {
    std::vector<boost::shared_ptr<Music::Chord> > tmp;
    std::copy_if(chords.begin(),chords.end(),std::back_inserter(tmp),
      [scale](const boost::shared_ptr<Music::Chord>& chord)
      {
        return scale->Fits(chord);
      }
    );
    chords.swap(tmp);
  }

  //Obtain only the chords the user wants to have displayed
  {
    std::vector<boost::shared_ptr<Music::Chord> > tmp;
    std::copy_if(chords.begin(),chords.end(),std::back_inserter(tmp),
      [this](const boost::shared_ptr<Music::Chord>& chord)
      {
        return UserWantsIt(chord);
      }
    );
    chords.swap(tmp);

  }

  ui->widget->SetChords(chords);
}

void ribi::QtMusicTheorySingleScaleDialog::resizeEvent(QResizeEvent *)
{
  any_change();
}

bool ribi::QtMusicTheorySingleScaleDialog::UserWantsIt(
  const boost::shared_ptr<Music::Chord>& chord
) const
{
  return
     (ui->display_6->isChecked() && dynamic_cast<const Music::Chord6*>(chord.get()))
  || (ui->display_7->isChecked() && dynamic_cast<const Music::Chord7*>(chord.get()))
  || (ui->display_aug->isChecked() && dynamic_cast<const Music::ChordAug*>(chord.get()))
  || (ui->display_dim->isChecked() && dynamic_cast<const Music::ChordDim*>(chord.get()))
  || (ui->display_m6->isChecked() && dynamic_cast<const Music::ChordMinor6*>(chord.get()))
  || (ui->display_m7->isChecked() && dynamic_cast<const Music::ChordMinor7*>(chord.get()))
  || (ui->display_major->isChecked() && dynamic_cast<const Music::ChordMajor*>(chord.get()))
  || (ui->display_minor->isChecked() && dynamic_cast<const Music::ChordMinor*>(chord.get()))
  ;
}
