/*
Copyright (C) 2011 Georgia Institute of Technology, University of Utah, Weill Cornell Medical College

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <Delayed_Buffer_To_Log.h>
#include <QtGui>

extern "C" Plugin::Object *createRTXIPlugin(void) {
	return new Spike_Logger();
}

static DefaultGUIModel::variable_t vars[] = {
	{
		"Start OR Stop To Record",
		"TRUE = the model will Activate the log model, FALSE = the model will deactivate the log model",
		DefaultGUIModel::INPUT,
	},
	{
		"How Much Back?",
		"How much iteration back to remember",
		DefaultGUIModel::PARAMETER | DefaultGUIModel::INTEGER,
	},
//----------------------Delayed Channels---------------------------------
//for every IN entrey need to add an out entery
	{
		"Channel 1 In",
		"The signal to be recored in delay",
		DefaultGUIModel::INPUT,
	},
	{
		"Channel 1 Deleayed",
		"Vin in delay",
		DefaultGUIModel::OUTPUT,
	},
	{
		"Channel 2 In",
		"The signal to be recored in delay",
		DefaultGUIModel::INPUT,
	},
	{
		"Channel 2 Deleayed",
		"Vin in delay",
		DefaultGUIModel::OUTPUT,
	},
	{
		"Channel 3 In",
		"The signal to be recored in delay",
		DefaultGUIModel::INPUT,
	},
	{
		"Channel 3 In Deleayed",
		"Vin in delay",
		DefaultGUIModel::OUTPUT,
	},
	{
		"Channel 4 In",
		"The signal to be recored in delay",
		DefaultGUIModel::INPUT,
	},
	{
		"Channel 4 In Deleayed",
		"Vin in delay",
		DefaultGUIModel::OUTPUT,
	},
	{
		"Channel 5 In",
		"The signal to be recored in delay",
		DefaultGUIModel::INPUT,
	},
	{
		"Channel 5 In Deleayed",
		"Vin in delay",
		DefaultGUIModel::OUTPUT,
	},
	{
		"Channel 6 In",
		"The signal to be recored in delay",
		DefaultGUIModel::INPUT,
	},
	{
		"Channel 6 In Deleayed",
		"Vin in delay",
		DefaultGUIModel::OUTPUT,
	},
	{
		"Channel 7 In",
		"The signal to be recored in delay",
		DefaultGUIModel::INPUT,
	},
	{
		"Channel 7 In Deleayed",
		"Vin in delay",
		DefaultGUIModel::OUTPUT,
	},
	{
		"Channel 8 In",
		"The signal to be recored in delay",
		DefaultGUIModel::INPUT,
	},
	{
		"Channel 8 In Deleayed",
		"Vin in delay",
		DefaultGUIModel::OUTPUT,
	},
	{
		"Channel 9 In",
		"The signal to be recored in delay",
		DefaultGUIModel::INPUT,
	},
	{
		"Channel 9 In Deleayed",
		"Vin in delay",
		DefaultGUIModel::OUTPUT,
	},
	{
		"Channel 10 In",
		"The signal to be recored in delay",
		DefaultGUIModel::INPUT,
	},
	{
		"Channel 10 In Deleayed",
		"Vin in delay",
		DefaultGUIModel::OUTPUT,
	},

//-------------------------------------------------------
};

static size_t num_vars = sizeof(vars)/sizeof(DefaultGUIModel::variable_t);

Spike_Logger::Spike_Logger(void) : DefaultGUIModel("Delayed Buffer To Log",::vars,::num_vars) {
	setWhatsThis(
	"<p><b>Delayed Buffer To Log:</b><br>This module will delay the input signal and on demand will start to output it to the loggind model</p>");
	createGUI(vars, num_vars);
	/*
	* Initialize Parameters & Variables
	*/

	Channel_A = NULL;
	Channel_B = NULL;
	Channel_C = NULL;
	Channel_D = NULL;
	Channel_E = NULL;
	Channel_F = NULL;
	Channel_G = NULL;
	Channel_H = NULL;
	Channel_I = NULL;
	Channel_J = NULL;

	Iteration_Back = 25; // default size
	Init_Memory();
	
	/*
	* Initialize the GUI
	*/
	setParameter("How Much Back?",Iteration_Back);
	refresh();

	QTimer::singleShot(0, this, SLOT(resizeMe()));
}

Spike_Logger::~Spike_Logger(void) {
	if (Channel_A!=NULL)
		delete[] Channel_A;
	if (Channel_B!=NULL)
		delete[] Channel_B;
	if (Channel_C!=NULL)
		delete[] Channel_C;
	if (Channel_D!=NULL)
		delete[] Channel_D;
	if (Channel_E!=NULL)
		delete[] Channel_E;
	if (Channel_F!=NULL)
		delete[] Channel_F;
	if (Channel_G!=NULL)
		delete[] Channel_G;
	if (Channel_H!=NULL)
		delete[] Channel_H;
	if (Channel_I!=NULL)
		delete[] Channel_I;
	if (Channel_J!=NULL)
		delete[] Channel_J;


}

void Spike_Logger::execute(void) {

if (Log_Signal != input (0)){ // if there was a change from the input 0 change the regord state
	if (Start_Log){
		// Stop data recorder
		Event::Object event(Event::STOP_RECORDING_EVENT);
		Event::Manager::getInstance()->postEventRT(&event);
		Start_Log = false;
	}else{
		// Start data recorder
		Event::Object event(Event::START_RECORDING_EVENT);
		Event::Manager::getInstance()->postEventRT(&event);
		Start_Log = true;
	}
Log_Signal = input (0);
}

//---------------------------------

// Save Data to buffer
Channel_A[In_pointer] = input(1);
Channel_B[In_pointer] = input(2);
Channel_C[In_pointer] = input(3);
Channel_D[In_pointer] = input(4);
Channel_E[In_pointer] = input(5);
Channel_F[In_pointer] = input(6);
Channel_G[In_pointer] = input(7);
Channel_H[In_pointer] = input(8);
Channel_I[In_pointer] = input(9);
Channel_J[In_pointer] = input(10);

// Output delayed Data
output(0) = Channel_A[delayed_pointer];
output(1) = Channel_B[delayed_pointer];
output(2) = Channel_C[delayed_pointer];
output(3) = Channel_D[delayed_pointer];
output(4) = Channel_E[delayed_pointer];
output(5) = Channel_F[delayed_pointer];
output(6) = Channel_G[delayed_pointer];
output(7) = Channel_H[delayed_pointer];
output(8) = Channel_I[delayed_pointer];
output(9) = Channel_J[delayed_pointer];


delayed_pointer++;
if (delayed_pointer==Iteration_Back)
	delayed_pointer= 0;

In_pointer++;
if (In_pointer==Iteration_Back)
	In_pointer = 0;
//-------------

}

void Spike_Logger::Init_Memory(void){
	Start_Log = false;
	Log_Signal = 0;

	if (Channel_A!=NULL)
		delete[] Channel_A;
	if (Channel_B!=NULL)
		delete[] Channel_B;
	if (Channel_C!=NULL)
		delete[] Channel_C;
	if (Channel_D!=NULL)
		delete[] Channel_D;
	if (Channel_E!=NULL)
		delete[] Channel_E;
	if (Channel_F!=NULL)
		delete[] Channel_F;
	if (Channel_G!=NULL)
		delete[] Channel_G;
	if (Channel_H!=NULL)
		delete[] Channel_H;
	if (Channel_I!=NULL)
		delete[] Channel_I;
	if (Channel_J!=NULL)
		delete[] Channel_J;
	
	Channel_A = new double[Iteration_Back];
	Channel_B = new double[Iteration_Back];
	Channel_C = new double[Iteration_Back];
	Channel_D = new double[Iteration_Back];
	Channel_E = new double[Iteration_Back];
	Channel_F = new double[Iteration_Back];
	Channel_G = new double[Iteration_Back];
	Channel_H = new double[Iteration_Back];
	Channel_I = new double[Iteration_Back];
	Channel_J = new double[Iteration_Back];

	for(int i=0 ; i < Iteration_Back ; i++){
		Channel_A[i] = 0.0;
		Channel_B[i] = 0.0;
		Channel_C[i] = 0.0;
		Channel_D[i] = 0.0;
		Channel_E[i] = 0.0;
		Channel_F[i] = 0.0;
		Channel_G[i] = 0.0;
		Channel_H[i] = 0.0;
		Channel_I[i] = 0.0;
		Channel_J[i] = 0.0;
	}

	In_pointer = 0;
	delayed_pointer = 1;
}

void Spike_Logger::update(DefaultGUIModel::update_flags_t flag) {
	if(flag == MODIFY) {
		int temp_Memory_Back   = getParameter("How Much Back?").toDouble();
		if (temp_Memory_Back != Iteration_Back){
		 Iteration_Back = temp_Memory_Back;
		 Init_Memory();		 
		}
	}
}
