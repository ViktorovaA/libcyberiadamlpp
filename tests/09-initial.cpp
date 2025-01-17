/* -----------------------------------------------------------------------------
 * The Cyberiada GraphML C++ library implemention
 *
 * The initial pseudostate test
 *
 * Copyright (C) 2024-25 Alexey Fedoseev <aleksey@fedoseev.net>
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
 * along with this program. If not, see https://www.gnu.org/licenses/
 * ----------------------------------------------------------------------------- */

#include <iostream>
#include "cyberiadamlpp.h"
#include "testutils.h"

using namespace Cyberiada;
using namespace std;

int main(int argc, char** argv)
{
	try {
		// check wrong graph with two initial pseudostates on the same level
		LocalDocument().open(string(argv[0]) + "-input.graphml", formatDetect);
	} catch (const Cyberiada::CybMLException&){
	}
	
	Document d;

	StateMachine* sm = d.new_state_machine("SM");
	State* parent = d.new_state(sm, "State");
	try {
		// check id uniqueness
		d.new_initial(sm, "n0", "init name");
	} catch (const Cyberiada::ParametersException&){
	}
	d.new_initial(sm);
	try {
		// check non-empty name
		d.new_initial(sm, "");
	} catch (const Cyberiada::ParametersException&){
	}
	d.new_initial(parent, "Local init", Point(30, 40));
	try {
		// check double initial
		d.new_initial(parent);
	} catch (const Cyberiada::ParametersException&){
	}
	
	try {
		cout << d << endl;
		LocalDocument(d, string(argv[0]) + ".graphml").save();
	} catch (const Cyberiada::Exception&) {
		return 1;
	}
	return 0;
}
