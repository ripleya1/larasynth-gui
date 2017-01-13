/*
Copyright 2016 Nathan Sommer

This file is part of Larasynth.

Larasynth is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Larasynth is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Larasynth.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "midi_config.hpp"

using namespace std;
using namespace larasynth;

MidiConfig::MidiConfig( ConfigParameters& config_params ) {
  vector<unsigned char> defaults;

  try {
    config_params.set_var( "controllers", _ctrls );
    config_params.set_var( "controller_defaults", defaults );
  }
  catch( runtime_error& e ) {
    throw MidiConfigException( e.what() );
  }

  if( _ctrls.size() == 0 )
    throw MidiConfigException( "There are no MIDI controllers defined" );
 
  if( defaults.size() % 2 != 0 )
    throw MidiConfigException( "Controller defaults are set like so:\ncontroller_defaults: <ctrl 1>, <ctrl 1 default>, <ctrl 2>, <ctrl 2 default> ..." );

  for( size_t i = 0; i < defaults.size(); i += 2 ) {
    event_data_t ctrl = defaults[i];
    event_data_t value = defaults[i+1];

    _ctrl_defaults[ctrl] = value;
  }

  unordered_map<string,string*> port_var_pointers = {
    { "recording_source_port", &_recording_source_port },
    { "performing_source_port", &_performing_source_port },
    { "performing_destination_port", &_performing_destination_port }
  };

  for( auto& kv : port_var_pointers ) {
    try {
      config_params.set_var( kv.first, *kv.second );
    }
    catch( UndefinedParameterException& e ) {
    }
    catch( ConfigParameterException& e ) {
      throw MidiConfigException( e.what() );
    }
  }

  for( const string& name : config_params.get_unset_params() )
    throw MidiConfigException( "Unknown parameter " + name );
}
