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

#include <default_gui_model.h>

class Spike_Logger : public DefaultGUIModel {
	
	public:
	
		Spike_Logger(void);
		virtual ~Spike_Logger(void);
	
		void execute(void);
		void Init_Memory(void);
	
	protected:
	
		void update(DefaultGUIModel::update_flags_t);
	
	private:
	
		bool	Start_Log;
		int 	Iteration_Back;
		double  Log_Signal;
		//------------
		double *Channel_A,*Channel_B,*Channel_C,*Channel_D,*Channel_E,*Channel_F,*Channel_G,*Channel_H,*Channel_I,*Channel_J;
		int 	delayed_pointer,In_pointer;


	
};
