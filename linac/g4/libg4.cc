//////////////////////////////////////////////////////////////////////////
// License & Copyright
// ===================
// 
// Copyright 2012 Christopher M Poole <mail@christopherpoole.net>
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////////


#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "SteppingAction.hh"
#include "EventAction.hh"
#include "PrimaryGeneratorAction.hh"

#include "Phasespace.hh"
#include "PhasespaceRecord.hh"

// GEANT4 //
#include "G4LogicalVolume.hh"

// BOOST/PYTHON //
#include "boost/python.hpp"
#include "pyublas/numpy.hpp"


using namespace boost::python;

// Members with default kwargs ..
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(_AddCADComponent,
                                       DetectorConstruction::AddCADComponent, 3, 8)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(_SetupHead,
                                       DetectorConstruction::SetupHead, 6, 6)


BOOST_PYTHON_MODULE(libg4) {

    class_<DetectorConstruction, DetectorConstruction*,
        bases<G4VUserDetectorConstruction>, boost::noncopyable>
        ("DetectorConstruction", "detector")
        .def("AddMaterial", &DetectorConstruction::AddMaterial)
        .def("AddPhasespace", &DetectorConstruction::AddPhasespace,
            return_internal_reference<>())
        .def("AddCADComponent", &DetectorConstruction::AddCADComponent,
            return_internal_reference<>())
        .def("AddCylinder", &DetectorConstruction::AddCylinder,
            return_internal_reference<>())
        .def("AddSlab", &DetectorConstruction::AddSlab,
            return_internal_reference<>())
//        .def("AddCADComponent", &DetectorConstruction::AddCADComponent,
//             _AddCADComponent(
//                 args("name", "filename", "material", "in_vacuum", "scale", "translation",
//                      "rotation", "colour"),
//                 "doc string"
//             )[return_internal_reference<>()])
        .def("UsePhantom", &DetectorConstruction::UsePhantom)
        .def("SetupHead", &DetectorConstruction::SetupHead)
//             _SetupHead(
//                 args("head_radius", "head_length", "head_position",
//                      "vacuum_radius", "vacuum_length", "vacuum_position"),
//                 "doc string"
//             )[return_internal_reference<>()])
        .def("GetEnergyHistogram", &DetectorConstruction::GetEnergyHistogram)
        .def("GetCountsHistogram", &DetectorConstruction::GetCountsHistogram)
        .def("ZeroHistograms", &DetectorConstruction::ZeroHistograms)
        ;   // End DetectorConstruction

    class_<PhysicsList, PhysicsList*,
        //bases<G4VModularPhysicsList> >
        bases<G4VUserPhysicsList> >
        ("PhysicsList", "physics list")
        ;   // End PhysicsList

    class_<SteppingAction, SteppingAction*,
        bases<G4UserSteppingAction>, boost::noncopyable>
        ("SteppingAction", "SteppingAction")
        ;   // End SteppingAction

    class_<EventAction, EventAction*,
        bases<G4UserEventAction> >
        ("EventAction", "EventAction")
        ;   // End EventAction

    class_<PrimaryGeneratorAction, PrimaryGeneratorAction*,
        bases<G4VUserPrimaryGeneratorAction>, boost::noncopyable>
        ("PrimaryGeneratorAction", "PrimaryGeneratorAction")
        .def("SetPosition", &PrimaryGeneratorAction::SetPosition)
        .def("SetDirection", &PrimaryGeneratorAction::SetDirection)
        .def("SetEnergy", &PrimaryGeneratorAction::SetEnergy)
        .def("SetFWHM", &PrimaryGeneratorAction::SetFWHM)
        .def("SetSource", &PrimaryGeneratorAction::SetSource)
        .def("SetRecyclingNumber", &PrimaryGeneratorAction::SetRecyclingNumber)
        .def("SetRedistribute", &PrimaryGeneratorAction::SetRedistribute)
        .def("SetGantryRotation", &PrimaryGeneratorAction::SetGantryRotation)
        ;   // End PrimaryGeneratorAction
}
