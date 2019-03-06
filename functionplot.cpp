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

 * @file functionplot.cpp
 * @brief The implimentation file for the function plot window.
 *
 * This is the function plot window for the project.
 *
 * @author Ryan Du (Empyreal092)
 * @author Firat Taxpulat (FT-1984)
 * @author Anita Chen (achen1105)
 *
 * @bug No known bugs, but more features to be added
 */

#include "helpwindow.h"
#include "functionplot.h"
#include "qcustomplot.h"
#include "ui_functionplot.h"
#include <algorithm>
#include <QPalette>
#include <QRandomGenerator>

FunctionPlot::FunctionPlot(QWidget *parent) :
    QWidget(parent), ui(new Ui::FunctionPlot), function_str(){

    initial = 0.0; // default initial value
    final = 10.0; // default final value
    nsteps = 1000; // default step number
    ui->setupUi(this);

    setWindowTitle("Plotting Function"); // set the window title

    input = new QWidget(); // widget of inputs on the left of the window
    inputlayout = new QVBoxLayout(); // the layout of the input
    paralayout = new QGridLayout(); // layout for the initial and final

    functionstring = new QLineEdit(); // where the user input the function
    inputf_t = new QLabel("y(t) := ");
    inputf_t -> setMaximumWidth(50);
    fstrlayout = new QHBoxLayout;
    fstrlayout -> addWidget(inputf_t);
    fstrlayout -> addWidget(functionstring);

    functionstring -> setToolTip("The function you want to plot"); // set the tooltip
    input_initial = new QDoubleSpinBox(); // a double spinbox for the initial
    input_initial -> setToolTip("In initial t"); // set the tooltip
    input_final = new QDoubleSpinBox(); // a double spinbox for the final
    input_final -> setToolTip("The final t"); // set the tooltip

    input_nsteps_spin_box = new QSpinBox(); // a double spinbox for the nsteps value
    input_nsteps_spin_box -> setToolTip("The number of steps"); // set the tooltip

    input_initial -> setMaximum(1000); // set max and min for initial and final spinbox
    input_initial -> setMinimum(-1000);
    input_initial -> setValue(initial);
    input_final -> setMaximum(1000);
    input_final -> setMinimum(-1000);
    input_final -> setValue(final);

    input_nsteps_spin_box -> setMaximum(10000000); // set max and min for nsteps spinbox and nsteps slider
    input_nsteps_spin_box -> setMinimum(0);
    input_nsteps_spin_box -> setValue(nsteps);
      
    plotbutton = new QPushButton("Plot!"); // plot button
    plotbutton -> setToolTip("Plot the funciton");
    clearbutton = new QPushButton("Clear!"); // clear button
    clearbutton -> setToolTip("Clear the plots");

    QObject::connect(plotbutton, SIGNAL(clicked()), this, SLOT(changefstring()));
        // when plot pressed, change the function string
    QObject::connect(clearbutton, SIGNAL(clicked()), this, SLOT(clearstring()));
        // when plot pressed, clear the string
    QObject::connect(input_initial, SIGNAL(valueChanged(double)), this, SLOT(changeini(double)));
        // when user input new initial, change the initial value
    QObject::connect(input_final, SIGNAL(valueChanged(double)), this, SLOT(changefinal(double)));
        // when user input new final, change the final value

    QObject::connect(input_nsteps_spin_box, SIGNAL(valueChanged(int)), this, SLOT(changensteps(int)));
        // when user input new number of steps, change the nsteps value

    promp_function = new QLabel ("Input the function you want to plot here \n(Only use t as your variables):"); // some prompt to tell the user what to do
    promp_ini = new QLabel  ("t initial");
    promp_final = new QLabel  ("t final");
    promp_nsteps = new QLabel ("Num of steps");


    // set the formats into the layout
    inputlayout->addWidget(promp_function);
    inputlayout->addLayout(fstrlayout);
    paralayout->addWidget(promp_ini,0,0);
    paralayout->addWidget(promp_final,0,1);

    paralayout->addWidget(promp_nsteps,2,0);

    paralayout->addWidget(input_initial,1,0);
    paralayout->addWidget(input_final,1,1);

    paralayout->addWidget(input_nsteps_spin_box,3,0);

    inputlayout->addLayout(paralayout);
    inputlayout->addWidget(plotbutton);
    inputlayout->addWidget(clearbutton);

    plotbutton->setStyleSheet("background-color:rgb(20, 150, 15); " // Plot button is green
                                "color: white; " // Font is white
                                "border-style: outset; " // Outer border
                                "border-width: 2 px; " // Border is 2 px
                                "border-color: beige; " // Border color is beige
                                "padding: 6 px"); // Padding is 6 px

    clearbutton->setStyleSheet("background-color:rgb(150, 20, 15); " // Clear button is red
                                "color: white; " // Font is white
                                "border-style: outset; " // Outer border
                                "border-width: 2 px; " // Border is 2 px
                                "border-color: beige; " // Border color is beige
                                "padding: 6 px"); // Padding is 6 px

    // Spacing for the user input
    inputlayout->insertStretch(0);
    inputlayout->setAlignment(promp_function, Qt::AlignTop); // 1
    inputlayout->setAlignment(functionstring, Qt::AlignTop); // 2
    // 3 is the gridboxlayout
    inputlayout->insertStretch(4); // Space in the middle
    inputlayout->setAlignment(plotbutton, Qt::AlignTop); // 5
    inputlayout->setAlignment(clearbutton, Qt::AlignTop); // 6
    inputlayout->insertStretch(7);
    inputlayout->insertStretch(8);
    inputlayout->insertStretch(9);
    inputlayout->insertStretch(10);
    inputlayout->insertStretch(11);
    inputlayout->insertStretch(12);
    inputlayout->insertStretch(13);
    inputlayout->insertStretch(14);
    inputlayout->insertStretch(15);
    inputlayout->insertStretch(16);
    inputlayout->insertStretch(17);
    inputlayout->addStretch();
    inputlayout->setMargin(0);
    paralayout->setMargin(0);

    input->setLayout(inputlayout);
    input->setMaximumWidth(250); // so that the input is not too big when the window is big

    //makepoints();
    //makeplot(); // call the make pot to plot the default graph
    ui->gridLayout->addWidget(input,0,0); // add input in the left of the window

    this->setMinimumSize(1080,880);
}

void FunctionPlot::changefstring(){
    if (initial >= final){ // if initial is larger than final, do nothing
        return; // here should be error handeling
    }
    else{
        function_str = functionstring->text(); // change the function_str according to the input
        makepoints();
        makeplot(); // call make plot
    }
}

void FunctionPlot::clearstring(){
    // clear all the data saved
    vec_points_to_plot.clear();
    funstr_vec.clear();
    reds.clear();
    greens.clear();
    blues.clear();
    makeplot(); // call make plot

}

void FunctionPlot::changeini(double i){
    initial = i; // change initial
}

void FunctionPlot::changefinal(double i){
    final = i; // change final
}

void FunctionPlot::changensteps(int i){
    nsteps = i; // change nsteps
}

FunctionPlot::~FunctionPlot(){
    delete ui;
}

void FunctionPlot::makepoints(){
    // exprtk commands
    typedef exprtk::symbol_table<double> symbol_table_t;
    typedef exprtk::expression<double>     expression_t;
    typedef exprtk::parser<double>             parser_t;

    QString expr_string = function_str; // the function string

    double x = initial; // initialize x

    symbol_table_t symbol_table;
    symbol_table.add_variable("t",x); // add x as a variable

    // exprtk commands to parse the function
    expression_t expression;
    expression.register_symbol_table(symbol_table);
    parser_t parser;
    parser.compile(expr_string.toStdString(),expression);

    const double delta = (final-initial)/nsteps; // the step size

    //plot functions
    QVector<std::pair <double,double>> points; // the variable and value vector

    for (x = initial; x <= final; x += delta) // for all value points
    {
       double result = expression.value(); // evaluate the result of the function string
       std::pair <double,double> data_point = std::make_pair(x,result);
       points.push_back(data_point); // add the data point
    }

    vec_points_to_plot.push_back(points); // add the points of the graph to the vector of graphs to plot
    funstr_vec.push_back(function_str); // save the function string in a vetor

    int r; int g; int b; // rgb paramaters
    do{ // randomize
        r = QRandomGenerator::global()->bounded(0, 255);
        g = QRandomGenerator::global()->bounded(0, 255);
        b = QRandomGenerator::global()->bounded(0, 255);
    }
    while (r+g+b<300); // if the color is too light do it again

    reds.push_back(r); // save the color int to vectors
    greens.push_back(g);
    blues.push_back(b);
}

void FunctionPlot::makeplot(){
    QVector<double> value_maxs; // the max and min of value and var for setting limit later
    QVector<double> value_mins;
    QVector<double> var_maxs;
    QVector<double> var_mins;

    ui->customPlot->clearGraphs(); // clear graph first
    ui->customPlot->clearPlottables();
    ui->customPlot->legend->setVisible(true); // the graph has legends
    for (size_t i = 0; i < vec_points_to_plot.size(); ++i){ // for all the saved graph data, plot
        ui->customPlot->addGraph(); // add graph
        QVector<std::pair <double,double>> points = vec_points_to_plot[i]; // take the saved data points
        QVector<double> var; // the vector of variables and values
        QVector<double> value;
        // transform the vector of pairs to vector of value
        std::transform(points.begin(), points.end(), std::back_inserter(var),
                         (const double& (*)(const std::pair<double, double>&))std::get<0>);
        std::transform(points.begin(), points.end(), std::back_inserter(value),
                         (const double& (*)(const std::pair<double, double>&))std::get<1>);

        double var_max = *std::max_element(var.begin(), var.end()); // get the max and min
        var_maxs.push_back(var_max);
        double var_min = *std::min_element(var.begin(), var.end());
        var_mins.push_back(var_min);
        double value_max = *std::max_element(value.begin(), value.end());
        value_maxs.push_back(value_max);
        double value_min = *std::min_element(value.begin(), value.end());
        value_mins.push_back(value_min);

        ui->customPlot->graph(i)->setData(var, value); // set the data of the graph
        ui->customPlot->graph(i)->setPen(QPen(QColor(reds[i],greens[i],blues[i]))); // set the color
        ui->customPlot->graph(i)->setName(funstr_vec[i]); // set the name
    }

    // give the axes some labels
    ui->customPlot->xAxis->setLabel("t");
    ui->customPlot->yAxis->setLabel("y");
    // set axes ranges, so we see all data
    double min = *std::min_element(value_mins.begin(), value_mins.end());
    double max = *std::max_element(value_maxs.begin(), value_maxs.end());
    double ini = *std::min_element(var_mins.begin(), var_mins.end());;
    double fin = *std::max_element(var_maxs.begin(), var_maxs.end());;
    ui->customPlot->xAxis->setRange(ini-0.1*abs(fin-ini), fin+0.1*abs(fin-ini));
    ui->customPlot->yAxis->setRange(min-0.1*abs(max-min), max+0.1*abs(max-min));
    ui->customPlot->replot(); // replot
}

void FunctionPlot::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Return) // When the return key is pressed, change and plot the string.
    {
        changefstring();

        if (event->modifiers() & Qt::ControlModifier) // When the return and control keys are pressed, clear the plot.
        {
            clearstring();
        }
    }
}

void FunctionPlot::MakeHelpWindow()
{
    QWidget* h_window = new helpWindow();
    //c_window->show();
}
