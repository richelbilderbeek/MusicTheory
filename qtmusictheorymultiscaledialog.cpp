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
#include "qtmusictheorymultiscaledialog.h"

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
#include "ui_qtmusictheorymultiscaledialog.h"

#pragma GCC diagnostic pop

ribi::QtMusicTheoryMultiScaleDialog::QtMusicTheoryMultiScaleDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtMusicTheoryMultiScaleDialog)
{
  ui->setupUi(this);

  //Put all available scales in the scales combobox
  {
    ui->scale_1->clear();
    ui->scale_2->clear();
    const std::vector<boost::shared_ptr<Music::Scale> > v
      = Music::Scale::CreateScales(Music::Note(0));
    std::for_each(v.begin(),v.end(),
      [this](const boost::shared_ptr<Music::Scale>& scale)
      {
        ui->scale_1->addItem(scale->GetName().c_str());
        ui->scale_2->addItem(scale->GetName().c_str());
      }
    );
  }

  ConnectAll();
}

ribi::QtMusicTheoryMultiScaleDialog::~QtMusicTheoryMultiScaleDialog() noexcept
{
  delete ui;
}

void ribi::QtMusicTheoryMultiScaleDialog::ConnectAll()
{
  QObject::connect(
    ui->scale_1, SIGNAL(currentIndexChanged(int)),
    this, SLOT(any_change())
  );
  QObject::connect(
    ui->scale_2, SIGNAL(currentIndexChanged(int)),
    this, SLOT(any_change())
  );
  QObject::connect(
    ui->root_1, SIGNAL(currentIndexChanged(int)),
    this, SLOT(any_change())
  );
  QObject::connect(
    ui->root_2, SIGNAL(currentIndexChanged(int)),
    this, SLOT(any_change())
  );
  QObject::connect(
    ui->display_major, SIGNAL(stateChanged(int)),
    this, SLOT(any_change())
  );
  QObject::connect(
    ui->display_minor, SIGNAL(stateChanged(int)),
    this, SLOT(any_change())
  );
  QObject::connect(
    ui->display_aug, SIGNAL(stateChanged(int)),
    this, SLOT(any_change())
  );
  QObject::connect(ui->display_dim,SIGNAL(stateChanged(int)),this,
    SLOT(any_change())
  );
  QObject::connect(ui->display_6,SIGNAL(stateChanged(int)),this,
    SLOT(any_change())
  );
  QObject::connect(ui->display_m6,SIGNAL(stateChanged(int)),this,
    SLOT(any_change())
  );
  QObject::connect(ui->display_7,SIGNAL(stateChanged(int)),this,
    SLOT(any_change())
  );
  QObject::connect(ui->display_m7,SIGNAL(stateChanged(int)),this,
    SLOT(any_change())
  );

}

void ribi::QtMusicTheoryMultiScaleDialog::any_change()
{
  ShowNotes1();
  ShowNotes2();
  std::vector<boost::shared_ptr<Music::Chord>> chords_1
    = Music::Chord::CreateAllChords();
  {
    //Obtain the root
    const Music::Note root{GetRoot1()};

    //Obtain the scale
    const boost::shared_ptr<Music::Scale> scale = Music::Scale::CreateScale(
      ui->scale_1->currentText().toLower().toStdString(),root);

    //Obtain the fitting chords in the scale
    chords_1 = FilterFittingChords(chords_1, scale);

    //Obtain only the chords the user wants to have displayed
    {
      std::vector<boost::shared_ptr<Music::Chord> > tmp;
      std::copy_if(chords_1.begin(),chords_1.end(),std::back_inserter(tmp),
        [this](const boost::shared_ptr<Music::Chord>& chord)
        {
          return UserWantsIt(chord);
        }
      );
      chords_1.swap(tmp);
    }
  }
  std::vector<boost::shared_ptr<Music::Chord> > chords_2 = Music::Chord::CreateAllChords();
  {
    //Obtain the root
    const Music::Note root{GetRoot2()};

    //Obtain the scale
    const boost::shared_ptr<Music::Scale> scale = Music::Scale::CreateScale(
      ui->scale_2->currentText().toLower().toStdString(),root);

    //Obtain the fitting chords in the scale
    chords_2 = FilterFittingChords(chords_2, scale);

    //Obtain only the chords the user wants to have displayed
    {
      std::vector<boost::shared_ptr<Music::Chord> > tmp;
      std::copy_if(chords_2.begin(),chords_2.end(),std::back_inserter(tmp),
        [this](const boost::shared_ptr<Music::Chord>& chord)
        {
          return UserWantsIt(chord);
        }
      );
      chords_2.swap(tmp);
    }
  }

  ui->widget->SetChords(chords_1,chords_2);
}

std::vector<boost::shared_ptr<ribi::Music::Chord>>
ribi::FilterFittingChords(
  std::vector<boost::shared_ptr<ribi::Music::Chord>> chords,
  const boost::shared_ptr<Music::Scale>& scale
)
{
  std::vector<boost::shared_ptr<Music::Chord> > tmp;
  std::copy_if(
    std::begin(chords),
    std::end(chords),
    std::back_inserter(tmp),
    [scale](const boost::shared_ptr<Music::Chord>& chord)
    {
      return scale->Fits(chord);
    }
  );
  return tmp;
}

ribi::Music::Note ribi::QtMusicTheoryMultiScaleDialog::GetRoot1() const
{
  return Music::Note(ui->root_1->currentText().toStdString());
}

ribi::Music::Note ribi::QtMusicTheoryMultiScaleDialog::GetRoot2() const
{
  return Music::Note(ui->root_2->currentText().toStdString());
}

void ribi::QtMusicTheoryMultiScaleDialog::resizeEvent(QResizeEvent *)
{
  any_change();
}

void ribi::QtMusicTheoryMultiScaleDialog::ShowNotes1()
{
  const Music::Note root{GetRoot1()};

  const boost::shared_ptr<Music::Scale> scale = Music::Scale::CreateScale(
    ui->scale_1->currentText().toLower().toStdString(),root);

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
  ui->notes_1->setText(notes_str.c_str());
}

void ribi::QtMusicTheoryMultiScaleDialog::ShowNotes2()
{
  const Music::Note root{GetRoot2()};

  const boost::shared_ptr<Music::Scale> scale = Music::Scale::CreateScale(
    ui->scale_2->currentText().toLower().toStdString(),root);

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
  ui->notes_2->setText(notes_str.c_str());
}

bool ribi::QtMusicTheoryMultiScaleDialog::UserWantsIt(
  const boost::shared_ptr<Music::Chord>& chord
) const
{
  return (ui->display_6->isChecked() && dynamic_cast<const Music::Chord6*>(chord.get()))
    || (ui->display_7->isChecked() && dynamic_cast<const Music::Chord7*>(chord.get()))
    || (ui->display_aug->isChecked() && dynamic_cast<const Music::ChordAug*>(chord.get()))
    || (ui->display_dim->isChecked() && dynamic_cast<const Music::ChordDim*>(chord.get()))
    || (ui->display_m6->isChecked() && dynamic_cast<const Music::ChordMinor6*>(chord.get()))
    || (ui->display_m7->isChecked() && dynamic_cast<const Music::ChordMinor7*>(chord.get()))
    || (ui->display_major->isChecked() && dynamic_cast<const Music::ChordMajor*>(chord.get()))
    || (ui->display_minor->isChecked() && dynamic_cast<const Music::ChordMinor*>(chord.get()))
  ;
}
