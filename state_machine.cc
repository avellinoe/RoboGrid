#include <iostream>
#include <tuple>
#include "elma.h"

namespace elma {

    int State::_id_counter = 0;

    StateMachine& StateMachine::set_initial(State& s) {
        _initial = &s;
        return *this;
    }

    StateMachine& StateMachine::add_transition(string event_name, State& from, State& to) {
        
        // Add to _transitions
        _transitions.push_back(Transition(event_name, from, to));
        to._state_machine_ptr = this;
        from._state_machine_ptr = this;

        return *this;
    }

    json StateMachine::to_json() {

        json j, j_trans;

        bool containsFrom = false; // Flag to determine if _state_names already contains from
        bool containsTo = false; // Flag to determine if _state_names already contains to

        // Iterate thru transitions, adding names of the unique States
        for (int i = 0; i < _transitions.size(); i++) {
            
            // If _state_names is empty, just add both the from and to states
            if (_state_names.empty()) {
                
                // std::cout << "_state_names is empty.\tcontainsFrom = false\tcontainsTo = false\n";
                containsFrom = false;
                containsTo = false;
            
            } else {

                // Check if the states in the ith transition are already contained in _state_names
                for (int j = 0; j < _state_names.size(); j++) {

                    // std::cout << "Comparing " << _state_names[j] << " with from: " << _transitions.at(i).from().name() << "\n";
                    // std::cout << "Comparing " << _state_names[j] << " with to: " << _transitions.at(i).to().name() << "\n";
                    if (_state_names[j] == _transitions.at(i).from().name()) {
                        // std::cout << "Contains From!\n";
                        containsFrom = true;
                        continue;
                    }
                    if (_state_names[j] == _transitions.at(i).to().name()) {
                        // std::cout << "Contains To!\n";
                        containsTo = true;
                        continue;
                    }
                }
            }
            
            if (!containsFrom) _state_names.push_back(_transitions.at(i).from().name());
            if (!containsTo) _state_names.push_back(_transitions.at(i).to().name());

            containsFrom = false; // reset flag
            containsTo = false; // reset flag
        }

        // Iterate thru transitions, adding transitions to _trans
        for (int i = 0; i < _transitions.size(); i++) {
            auto trans = std::make_tuple(_transitions.at(i).from().name(),
                                        _transitions.at(i).to().name(),
                                        _transitions.at(i).event_name());
            _trans.push_back (trans);
        }

        // std::cout << "There are " << _state_names.size() << " States.\n";
        // for (int i = 0; i < _state_names.size(); i++) {
        //     std::cout << _state_names[i] << std::endl;
        // }

        // std::cout << "There are " << _trans.size() << " Transitions.\n";
        // for (int i = 0; i < _trans.size(); i++) {
        //     std::cout << "from : '" << std::get<0>(_trans[i]) << "' to: '" << std::get<1>(_trans[i]) << "' when: '" << std::get<2>(_trans[i]) << "'\n";
        // }

        j = {
            {"name", name()},
            {"states", _state_names},
            {"transitions", {}}
        };

        // Now we populate the transitions json object
        for (int i = 0; i < _trans.size(); i++) {
            j_trans = {
                {"from",std::get<0>(_trans[i])},
                {"to",std::get<1>(_trans[i])},
                {"when",std::get<2>(_trans[i])}
            };
            j["transitions"] += j_trans;
        }

        return j;
    }

    void StateMachine::init() {
        for (auto transition : _transitions ) {
            watch(transition.event_name(), [this, transition](Event& e) {
                if ( _current->id() == transition.from().id() ) {
                    _current->exit(e);
                    _current = &transition.to();
                    _current->entry(e);
                    if ( !_propagate ) {
                      e.stop_propagation();
                    }
                }
            });
        }
    }

    void StateMachine::start() {
        if ( _initial == NULL ) { 
            throw(Exception("State machine started without an initial state (call set_initial(...) first)"));
        }
        _current = _initial;
        _current->entry(Event("start"));
    }

    void StateMachine::update() {
        _current->during();
    }

    void StateMachine::stop() {}

};