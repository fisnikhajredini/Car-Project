/**
 * driver is an example application to demonstrate how to 
 *         generate driving commands from an application realized
 *         with OpenDaVINCI
 * Copyright (C) 2012 - 2015 Christian Berger
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include <cstdio>
#include <cmath>
#include <iostream>

#include "opendavinci/odcore/io/conference/ContainerConference.h"
#include "opendavinci/odcore/data/Container.h"

#include "automotivedata/GeneratedHeaders_AutomotiveData.h"

#include "Driver.h"

namespace automotive {
    namespace miniature {

        using namespace std;
        using namespace odcore::base;
        using namespace odcore::data;
        using namespace odcore::data;
        using namespace automotive;
        using namespace automotive::miniature;

        Driver::Driver(const int32_t &argc, char **argv) :
            TimeTriggeredConferenceClientModule(argc, argv, "Driver") {
        }

        Driver::~Driver() {}

        void Driver::setUp() {
            // This method will be call automatically _before_ running body().
        }

        void Driver::tearDown() {
            // This method will be call automatically _after_ return from body().
        }

        // This method will do the main data processing job.
        odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode Driver::body() {
            //bool carIsMoving = false;
            //bool spaceMeasurementCommenced = false;
            //bool startParkingSequence = false;
            //bool startReverseRightParking = false;
            //bool startReverseLeftParking = false;
            //bool prepareToPark = false;
            //int counter =0;
            int spaceCounter = 0;
            int stopCounter = 0;
        

        enum State {
                FORWARD,
                MEASURING_SPACE,
                PARK,

                };


                State state = FORWARD;




            while (getModuleStateAndWaitForRemainingTimeInTimeslice() == odcore::data::dmcp::ModuleStateMessage::RUNNING) {
                // In the following, you find example for the various data sources that are available:

                // 1. Get most recent vehicle data:
                Container containerVehicleData = getKeyValueDataStore().get(automotive::VehicleData::ID());
                VehicleData vd = containerVehicleData.getData<VehicleData> ();
            //    cerr << "Most recent vehicle data: '" << vd.toString() << "'" << endl;

                // 2. Get most recent sensor board data:
                Container containerSensorBoardData = getKeyValueDataStore().get(automotive::miniature::SensorBoardData::ID());
                SensorBoardData sbd = containerSensorBoardData.getData<SensorBoardData> ();
          //      cerr << "Most recent sensor board data: '" << sbd.toString() << "'" << endl;

                // Design your control algorithm here depending on the input data from above.

                // Create vehicle control data.
                VehicleControl vc;
                
                cerr << "Obstacle" << sbd.getValueForKey_MapOfDistances(2)<< endl; 
              



    switch (state) {


        case FORWARD:
            cerr << "Car Moving" << endl;
     
            vc.setSpeed(1);
            vc.setSteeringWheelAngle(0);
            //carIsMoving = true;
                    //cerr << "Car Initialized" << endl;
            
        if(sbd.getValueForKey_MapOfDistances(0) < 50 && sbd.getValueForKey_MapOfDistances(0) > 0  ) {// space sequence detected
                    //spaceMeasurementCommenced = true;
                    //spaceSearchStartPosition = vd.getAbsTraveledPath(); // tell me the on going millage
                  
                    //spaceCounter++;
                   
                    state = MEASURING_SPACE;
        }           

        break;

        case MEASURING_SPACE: 
            cout << "Car is measuring" << endl;
            vc.setSpeed(1);
            spaceCounter++;

            if(spaceCounter > 40 ){
            
            //cout << "Final Space Counter : " << spaceCounter << endl;
            
                    state = PARK;           
            }
        break;

        case PARK:
            cerr << "STATE : Park" << endl;

            vc.setSpeed(0);
            stopCounter++;
            vc.setSteeringWheelAngle(0);
            //prepareToPark = true;

        if(stopCounter > 10){
            vc.setSpeed(-1);
            vc.setSteeringWheelAngle(20);

            if(sbd.getValueForKey_MapOfDistances(2) < 50) {
                cout << "State: Final PARKING; "<< sbd.getValueForKey_MapOfDistances(2) <<endl;
                vc.setSpeed(-1);
                vc.setSteeringWheelAngle(-25);

                if(sbd.getValueForKey_MapOfDistances(1) > 100 ){
                    cout << "State: Final STOP;" << sbd.getValueForKey_MapOfDistances(1)<< endl;

                    vc.setSpeed(0);
                    vc.setSteeringWheelAngle(0);
                }

            }   

        }

        break;




    }


//              if(carIsMoving == false) { // initialize speed
//                   vc.setSpeed(1);
//                   vc.setSteeringWheelAngle(0);
//                      carIsMoving = true;
//                     //cerr << "Car Initialized" << endl;

//                 }else if(prepareToPark == false && spaceMeasurementCommenced == false && startParkingSequence == false
//                          && startParkingSequence == false && startReverseRightParking == false && startReverseLeftParking == false){
//                     vc.setSpeed(1);
//                     vc.setSteeringWheelAngle(0);
//                     carIsMoving = true;
//                     cerr << "Car Moving" << endl;
//                 }
                
                
//                 // With setSpeed you can set a desired speed for the vehicle in the range of -2.0 (backwards) .. 0 (stop) .. +2.0 (forwards)
//                 if(sbd.getValueForKey_MapOfDistances(2) < 0  && spaceMeasurementCommenced == false) {// space sequence detected
//                  spaceMeasurementCommenced = true;
//                  //spaceSearchStartPosition = vd.getAbsTraveledPath(); // tell me the on going millage
                  
//                     spaceCounter = 0;
//                     cerr << "sequence detected" << endl;
//                 }

//              if(spaceMeasurementCommenced == true && prepareToPark ==false){
                    
                   
//                     //while(true){
//                         //space = vd.getAbsTraveledPath() - spaceSearchStartPosition; // calculate the milage from where u are
//                      //   cerr << "Measured space: " << space<< endl;
//                         if(spaceCounter > 100){
//                             vc.setSpeed(0);
//                             vc.setSteeringWheelAngle(0);
//                             prepareToPark = true;
//                             cerr << "Final Space Counter : " << spaceCounter << endl;
                        
//                         }else{
                        
//                             if(sbd.getValueForKey_MapOfDistances(2) > 0){
//                                 spaceMeasurementCommenced = false;
                                
//                             }else{
//                                 spaceCounter++;
//                                 cerr << "Current Space Count : " << spaceCounter << endl;
//                             }
//                         }
//                         vc.setSpeed(1);
//                         vc.setSteeringWheelAngle(0);
        
//              }
                
//              if(prepareToPark == true  && startParkingSequence == false){
//                  vc.setFlashingLightsRight(true);
//                  vc.setSpeed(1);
//                     vc.setSteeringWheelAngle(0);
//                     if (++counter > 15){ // count b4 u check
                    
//                         startParkingSequence = true;
//                     }
//                     cerr << "Prepaerring to park: Counter " << counter<< endl;
//              }
//              if(startParkingSequence == true && startReverseRightParking == false){
//                  vc.setBrakeLights(true);
//                  vc.setSpeed(0);
//                  vc.setSteeringWheelAngle(0);
//                     startReverseRightParking = true;
//                     cerr << "Prepaerring to park: Counter " << counter<< endl;
//              }
                
//              if(startReverseRightParking == true && startReverseLeftParking == false){
//                  vc.setBrakeLights(false);
//                  vc.setSpeed(-1.6);
//                  vc.setSteeringWheelAngle(25);
//                  if(++counter > 60){
//                      startReverseLeftParking = true;
//                  }
//                     cerr << "Reverse Right"<< endl;
//              }
                
//              if(startReverseLeftParking == true){
//                     cerr << "Reverse left"<< endl;
//                  vc.setSpeed(-.175);
//                  vc.setSteeringWheelAngle(-25);
//                  if(++counter > 195){
//                      // park car
//                      vc.setBrakeLights(true);
//                      vc.setSpeed(0);
//                      vc.setSteeringWheelAngle(0);
//                      vc.setBrakeLights(true);
//                      vc.setFlashingLightsRight(false);
                        
//                  }
                
//              }
//                 // With setSteeringWheelAngle, you can steer in the range of -26 (left) .. 0 (straight) .. +25 (right)
//                 //double desiredSteeringWheelAngle = 4; // 4 degree but SteeringWheelAngle expects the angle in radians!
//                 //vc.setSteeringWheelAngle(desiredSteeringWheelAngle * cartesian::Constants::DEG2RAD);

//                 // You can also turn on or off various lights:
//                 //vc.setBrakeLights(false);
//                 //vc.setFlashingLightsLeft(false);
//                 //vc.setFlashingLightsRight(true);

//                 // Create container for finally sending the data.

                Container c(vc);
                // Send container.
                getConference().send(c);
            }// while loop

            return odcore::data::dmcp::ModuleExitCodeMessage::OKAY;
        }// body 

    }
} // automotive::miniature

// STEPHEN MENSAH
