/**
 * This file is part of PIC 10C Final Project - A Graphic Calculator.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.

 * We declare that this work is our own.
 * We did this work honestly and can fully stand behind everything that we have written.
 * We did not copy code from anyone, student or otherwise, expect files we downloaded and have the permission to use.
 * We pledge that we have neither given nor received unauthorized assistance on making this project.

 * @file diffeqsolver.h
 * @brief The header file for the ODE solver window.
 *
 * This is the ODE solver window for the project.
 *
 * @author Ryan Du (Empyreal092)
 * @author Firat Taxpulat (FT-1984)
 * @author Anita Chen (achen1105)
 *
 * @bug No known bugs, but more features to be added
 */


#ifndef DIFFEQSOLVER_H
#define DIFFEQSOLVER_H

#include <QWidget>
#include "qcustomplot.h"
#include "exprtk.hpp"
#include <QDialog>
#include <QString>
#include <QPushButton>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QActionGroup>
#include "functionplot.h"
#include "eulermethod.h"
#include "Backeulermethod.h"
#include "RK2method.h"
#include "rk4method.h"
#include "trapezoidalmethod.h"

namespace Ui {
class diffeqsolver;
}

/**
 * @class	diffeqsolver
 *
 * @brief	A diffeqsolver window.
 */

class diffeqsolver : public QWidget
{
    Q_OBJECT

public:

    /**
     * @fn	explicit diffeqsolver::diffeqsolver(QWidget *parent = nullptr);
     *
     * @brief	Constructor
     *
     * @param [in,out]	parent	(Optional) If non-null, the parent.
     */

    explicit diffeqsolver(QWidget *parent = nullptr);

    /**
     * @fn	diffeqsolver::~diffeqsolver();
     *
     * @brief	Destructor
     */

    ~diffeqsolver();

public slots:

    /**
    * @fn	void diffeqsolver::goToMethod();
    *
    * @brief	Go to each of the solving methods
    */
   // void goToMethod();
   /**
   * @fn	void diffeqsolver::goToMethod0();
   *
   * @brief  Go to method 0
   */
   void goToMethod0();
   /**
   * @fn	void diffeqsolver::goToMethod0();
   *
   * @brief  Go to method 1
   */
   void goToMethod1();
   /**
   * @fn	void diffeqsolver::goToMethod0();
   *
   * @brief  Go to method 2
   */
   void goToMethod2();
   /**
   * @fn	void diffeqsolver::goToMethod0();
   *
   * @brief  Go to method 3
   */
   void goToMethod3();
   /**
   * @fn	void diffeqsolver::goToMethod0();
   *
   * @brief  Go to method 4
   */
   void goToMethod4();


private:
    /** @brief	The solver stacked widget */
    QStackedWidget * solverStackedWidget;
    /** @brief The drop down menu */
    // QComboBox * dropDownMenu;
    /** @brief	The user interface */
    Ui::diffeqsolver *ui;
    /** @brief  The differential equation solver drop-down menu bar */
    QMenuBar* odeMenuBar;
};

#endif // DIFFEQSOLVER_H
