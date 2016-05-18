/**
 * lanedetector - Application skeleton for detecting lane markings.
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

#include <iostream>
#include <memory>

#include <opencv/cv.h>
#include <opencv/highgui.h>

#include "opendavinci/odcore/base/KeyValueConfiguration.h"
#include "opendavinci/odcore/base/Lock.h"
#include "opendavinci/odcore/data/Container.h"
#include "opendavinci/odcore/wrapper/SharedMemoryFactory.h"

#include "opendavinci/odtools/player/Player.h"

#include "opendavinci/GeneratedHeaders_OpenDaVINCI.h"
#include "automotivedata/GeneratedHeaders_AutomotiveData.h"

#include "LaneDetector.h"
#include <unistd.h>


namespace automotive {
    namespace miniature {

        using namespace std;
        using namespace odcore::base;
        using namespace odcore::base::module;
        using namespace odcore::data;
        using namespace odcore::data::image;
        using namespace odtools::player;
        using namespace automotive;
        using namespace cv;

        void LaneDetector::verticalLine( cv::Mat img, cv::Point start, cv::Point end )
		{
			int thickness = 1;
			int lineType = 8;
			line( img,
				start,
				end,
				cv::Scalar( 0, 0, 255 ),
				thickness,
				lineType );
		}
		void LaneDetector::rightArrow( cv::Mat img, cv::Point start, cv::Point end )
		{
			int thickness = 1;
			int lineType = 8;
			line( img,
				start,
				end,
				cv::Scalar( 98, 206, 81 ),
				thickness,
				lineType );
		}
		void LaneDetector::leftArrow( cv::Mat img, cv::Point start, cv::Point end )
		{
			int thickness = 1;
			int lineType = 8;
			line( img,
				start,
				end,
				cv::Scalar(255,154,0 ),
				thickness,
				lineType );
		}


void LaneDetector::leftArrow_2( cv::Mat img, cv::Point start, cv::Point end )
		{
			int thickness = 1;
			int lineType = 8;
			line( img,
				start,
				end,
				cv::Scalar(255,154,0 ),
				thickness,
				lineType );
		}


void LaneDetector::leftArrow_3( cv::Mat img, cv::Point start, cv::Point end )
		{
			int thickness = 1;
			int lineType = 8;
			line( img,
				start,
				end,
				cv::Scalar(255,154,0 ),
				thickness,
				lineType );
		}

void LaneDetector::leftArrow_4( cv::Mat img, cv::Point start, cv::Point end )
		{
			int thickness = 1;
			int lineType = 8;
			line( img,
				start,
				end,
				cv::Scalar(255,154,0 ),
				thickness,
				lineType );
		}
/*void LaneDetector::rightArrow_1( cv::Mat img, cv::Point start, cv::Point end )
		{
			int thickness = 1;
			int lineType = 8;
			line( img,
				start,
				end,
				cv::Scalar( 98, 206, 81 ),
				thickness,
				lineType );
		}*/
		void LaneDetector::leftArrow_1( cv::Mat img, cv::Point start, cv::Point end )
		{
			int thickness = 1;
			int lineType = 8;
			line( img,
				start,
				end,
				cv::Scalar(255,154,0 ),
				thickness,
				lineType );
		}
                
                

               
       	bool LaneDetector::IsWhite(cv::Mat img, int y, int x){
	    	int blue = img.at<cv::Vec3b>(y,x)[0];
	    	 //blue = intensity.val[0];
	    	 int green = img.at<cv::Vec3b>(y,x)[1];
	    	 int red = img.at<cv::Vec3b>(y,x)[2];

	    	if(blue == 255 && green == 255 && red == 255){
	        	return true;
	    	}
			return false;
		}

        LaneDetector::LaneDetector(const int32_t &argc, char **argv) :
            TimeTriggeredConferenceClientModule(argc, argv, "LaneDetector"),
            m_hasAttachedToSharedImageMemory(false),
            m_sharedImageMemory(),
            m_image(NULL),
            m_debug(false) {}

        LaneDetector::~LaneDetector() {}

        void LaneDetector::setUp() {
	        // This method will be called automatically _before_ running body().

            // If in debug mode, display the image from the camera feed.
	        if (m_debug) {
		        cvNamedWindow("Camera Feed Image", CV_WINDOW_AUTOSIZE);
		        cvMoveWindow("Camera Feed Image", 300, 100);
	        }
        }

        void LaneDetector::tearDown() {
	        // This method will be called automatically _after_ return from body().
	        cout << "Control C is pressed" << endl;
	        if (m_image != NULL) {
		        cvReleaseImage(&m_image);

	        }

	        if (m_debug) {
		        cvDestroyWindow("Camera Feed Image");
	        }
        }

        bool LaneDetector::readSharedImage(Container &c) {
	        bool retVal = false;

	        if (c.getDataType() == odcore::data::image::SharedImage::ID()) {
		        SharedImage si = c.getData<SharedImage> ();

		        // Check if we have already attached to the shared memory containing the image from the virtual camera.
		        if (!m_hasAttachedToSharedImageMemory) {
			        m_sharedImageMemory = odcore::wrapper::SharedMemoryFactory::attachToSharedMemory(si.getName());
		        }

		        // Check if we could successfully attach to the shared memory.
		        if (m_sharedImageMemory->isValid()) {
			        // Lock the memory region to gain exclusive access using a scoped lock.
                    Lock l(m_sharedImageMemory);

			        if (m_image == NULL) {
				        m_image = cvCreateImage(cvSize(si.getWidth(), si.getHeight()), IPL_DEPTH_8U, si.getBytesPerPixel());
			        }

			        // Example: Simply copy the image into our process space.
			        if (m_image != NULL) {
				        memcpy(m_image->imageData, m_sharedImageMemory->getSharedMemory(), si.getWidth() * si.getHeight() * si.getBytesPerPixel());
			        }

			        // Mirror the image.
			        cvFlip(m_image, 0, -1);

			        retVal = true;
		        }
	        }
	        return retVal;
        }

        // This method is called to process an image described by the SharedImage data structure.
        void LaneDetector::processImage() {
            // Example: Show the image.
            if (m_debug) {
            	cv::Mat mat_img(m_image); //converts the IPL image to a mat image
                IplImage *img_gray = cvCreateImage(cvGetSize(m_image),IPL_DEPTH_8U,1);
		IplImage *canny_image = cvCreateImage(cvGetSize(m_image),IPL_DEPTH_8U,1);

		//convert image to Canny image
		cvCvtColor(m_image,img_gray, CV_RGB2GRAY);// makes image gray
		cvCanny(img_gray, canny_image, 100, 150, 3 );// canny edge detection
		cvCvtColor(canny_image, m_image, CV_GRAY2RGB);

		//Release filtered image
		cvReleaseImage(&img_gray);
		cvReleaseImage(&canny_image);
				int rows = mat_img.rows;
				int cols = mat_img.cols;
				// cv::Size s = mat_img.size(); //gets rows and columns
				// rows = s.height;
				// cols = s.width;
				cv::Point pt1; //initialize the startin and ending points for each arrow
				cv::Point pt2;
				cv::Point pt3;
				cv::Point pt4;
				cv::Point pt5;
				cv::Point pt6;
cv::Point pt7;
cv::Point pt8;
cv::Point pt9;
cv::Point pt10;
cv::Point pt11;
cv::Point pt12;
cv::Point pt13;
cv::Point pt14;
cv::Point pt15;
cv::Point pt16;
cv::Point pt17;



				pt1.x=cols/2; //starting points for first arrow
				pt1.y=0;
				pt2.x=cols/2; //ending points for first arrow
				pt2.y=rows;

				pt3.x=cols/2;
				pt3.y=350;
				pt4.x = pt3.x;
				pt4.y = pt3.y;
				pt5.x = pt3.x;
				pt5.y = pt3.y;
				pt6.x = cols/2;
				pt6.y = 390;
				pt10.x = pt6.x;
				pt10.y = pt6.y;
				

                                pt7.x = cols/2;
                                pt7.y = 370;
                                pt8.x = pt7.x;
                                pt8.y = pt7.y;
                                pt9.x = pt7.x;
                                pt9.y = pt7.y;

                                pt11.x = cols/2;
                                pt11.y = 410;
                                pt12.x = pt11.x;
                                pt12.y = pt11.y;

                                pt13.x = cols/2;
                                pt13.y = 330;
                                pt14.x = pt13.x;
                                pt14.y = pt13.y;



				
				while(pt4.x != cols){
					pt4.x = pt4.x +1; //extend the arrow
					
					 //checks for color at current position
					if(IsWhite(mat_img,pt4.y,pt4.x)){
						break; //color is white at current position
					}
				}
				rightArrow(mat_img, pt3, pt4);
				
				while(pt5.x != 0){
					pt5.x = pt5.x -1;
					if(IsWhite(mat_img,pt5.y,pt5.x)){
						break; //color is white at current position
					}
				}
				leftArrow(mat_img, pt3, pt5);
			
				while(pt8.x != cols){
					pt8.x = pt8.x +1; //extend the arrow
					
					 //checks for color at current position
					if(IsWhite(mat_img,pt8.y,pt8.x)){
						break; //color is white at current position
					}
				}
				rightArrow_1(mat_img, pt7, pt8);
				
				while(pt9.x != 0){
					pt9.x = pt9.x -1;
					if(IsWhite(mat_img,pt9.y,pt9.x)){
						break; //color is white at current position
					}
				}
				leftArrow_1(mat_img, pt7, pt9);
				
				while(pt10.x != 0) {
					pt10.x = pt10.x -1;
					if(IsWhite(mat_img, pt6.y, pt6.x)) {
						break;
					}
				}
				leftArrow_2(mat_img, pt6, pt10);
				
				while(pt12.x != 0) {
					pt12.x = pt12.x -1;
					if(IsWhite(mat_img, pt12.y, pt12.x)) {
						break;
					}
				}
				leftArrow_3(mat_img, pt11, pt12);

                    while(pt14.x != 0) {
					pt14.x = pt14.x -1;
					if(IsWhite(mat_img, pt14.y, pt14.x)) {
						break;
					}
				}
				leftArrow_4(mat_img, pt13, pt14);
                                
                                

				//vertical arrow
				
				while(pt1.y != rows){
					pt1.y = pt1.y +1;
					//cout << "line detected" << endl;
					if(IsWhite(mat_img,pt1.y,pt1.x)){
						break; //color is white at current position
					}
				}


				verticalLine(mat_img, pt1, pt2);

                if (m_image != NULL) {
                    cvShowImage("Camera Feed Image", m_image);
                    cvWaitKey(10);
                }


// Container containerSteeringData = getKeyValueDataStore().get(SteeringData::ID());
				// SteeringData sd = containerSteeringData.getData<SteeringData>();
				Container containerVC = getKeyValueDataStore().get(VehicleControl::ID());
				VehicleControl vc = containerVC.getData<VehicleControl>(); ; 
				double angle = 0.0;
				int center;
				int rightLaneLength;
				int leftLaneLength;
				//vc.setSpeed(1);

				//checks vertical line
				//if(pt1.y > 350 && pt1.y < 360){
				//sends boolean to driver
				//sd.setStopData(true);

				//}
				//checks right line

				 cout << "RIGHT LANE: " << pt4.x << "\n"<<endl;
				// cout << "LEFT LANE: " << pt5.x << "\n"<<endl;
				center = cols/2;

				rightLaneLength = pt4.x-center;
				leftLaneLength = std::abs(pt5.x-center);

				//&& leftLaneLength - rightLaneLength > 15
				if(rightLaneLength<leftLaneLength && rightLaneLength > 2*leftLaneLength/3 && pt5.x != 0 && pt9.x != 0 && pt10.x != 0 && pt12.x != 0 && pt14.x !=0 && pt4.x !=640 && leftLaneLength - rightLaneLength > 15){
					if(leftLaneLength - rightLaneLength > 5){
						angle =-10;
						vc.setSteeringWheelAngle(angle);
						//sd.setExampleData(angle);
						cout << "left a little " <<endl;

					}
				}	
				else if(rightLaneLength<leftLaneLength && rightLaneLength < 2*leftLaneLength/3 && pt5.x != 0 && pt9.x != 0 && pt10.x != 0 && pt12.x != 0 && pt14.x !=0 && pt4.x !=640 ){
					angle =-26;
					vc.setSteeringWheelAngle(angle);
					//sd.setExampleData(angle);
					cout << "left " <<endl;

				}
				else if(rightLaneLength>leftLaneLength && 2*rightLaneLength/3 < leftLaneLength && pt5.x != 0 && pt9.x != 0 && pt10.x != 0 && pt12.x != 0 && pt14.x !=0  && pt4.x !=640 && rightLaneLength -leftLaneLength > 15 ){
					if(rightLaneLength -leftLaneLength > 5){
						angle =10;
						vc.setSteeringWheelAngle(angle);
						//sd.setExampleData(angle);
					cout << "right a little" <<endl;

					}
				}
				else if(rightLaneLength>leftLaneLength && 2*rightLaneLength/3 > leftLaneLength && pt5.x != 0 && pt9.x != 0 && pt10.x != 0 && pt12.x != 0 && pt14.x !=0 && pt4.x !=640){
					angle =26;
					vc.setSteeringWheelAngle(angle);
					//sd.setExampleData(angle);
					cout << "right" <<endl;
					
				}else if(pt5.x == 0){
					angle = 0;
					vc.setSteeringWheelAngle(angle);
					//sd.setExampleData(angle);
					//vc.setSpeed(0.5);
					cout << "blind on the pt5 (left)" <<endl;
					if (pt4.x != 640){
						if(rightLaneLength > 0 && rightLaneLength < 25){
							angle = -26;
							//sd.setExampleData(angle);
							vc.setSteeringWheelAngle(angle);
							cout << "Doing the if in if to turn left" << endl;
						}if (rightLaneLength> 25 && rightLaneLength <130){
							angle =10;
							//sd.setExampleData(angle);
							vc.setSteeringWheelAngle(angle);

						}
						if (rightLaneLength> 250 && rightLaneLength <320){
							angle = 26;
							vc.setSteeringWheelAngle(angle);
							//sd.setExampleData(angle);
							cout << "Doing the if in if to turn right" << endl;
						}
					}
				
				else if(pt9.x == 0){
					angle = 0;
					vc.setSteeringWheelAngle(angle);
					//sd.setExampleData(angle);
					//vc.setSpeed(0.5);
					cout << "blind on the pt9(left)" <<endl;
					if (pt4.x != 640){
						if(rightLaneLength > 0 && rightLaneLength < 25){
							angle = -26;
							//sd.setExampleData(angle);
							vc.setSteeringWheelAngle(angle);
							cout << "Doing the if in if to turn left" << endl;
						}if (rightLaneLength> 25 && rightLaneLength <130){
							angle =10;
							//sd.setExampleData(angle);
							vc.setSteeringWheelAngle(angle);

						}
						if (rightLaneLength> 250 && rightLaneLength <320){
							angle = 26;
							vc.setSteeringWheelAngle(angle);
							//sd.setExampleData(angle);
							cout << "Doing the if in if to turn right" << endl;
						}
					}
				}else if(pt10.x == 0){
					angle = 0;
					vc.setSteeringWheelAngle(angle);
					//sd.setExampleData(angle);
					//vc.setSpeed(0.5);
					cout << "blind on the pt10(left)" <<endl;
					if (pt4.x != 640){
						if(rightLaneLength > 0 && rightLaneLength < 25){
							angle = -26;
							//sd.setExampleData(angle);
							vc.setSteeringWheelAngle(angle);
							cout << "Doing the if in if to turn left" << endl;
						}if (rightLaneLength> 25 && rightLaneLength <130){
							angle =10;
							//sd.setExampleData(angle);
							vc.setSteeringWheelAngle(angle);

						}
						if (rightLaneLength> 250 && rightLaneLength <320){
							angle = 26;
							vc.setSteeringWheelAngle(angle);
							//sd.setExampleData(angle);
							cout << "Doing the if in if to turn right" << endl;
						}
					}
				}
				else if(pt12.x == 0){
					angle = 0;
					vc.setSteeringWheelAngle(angle);
					//sd.setExampleData(angle);
					//vc.setSpeed(0.5);
					cout << "blind on the pt12(left)" <<endl;
					if (pt4.x != 640){
						if(rightLaneLength > 0 && rightLaneLength < 25){
							angle = -26;
							//sd.setExampleData(angle);
							vc.setSteeringWheelAngle(angle);
							cout << "Doing the if in if to turn left" << endl;
						}if (rightLaneLength> 25 && rightLaneLength <130){
							angle =10;
							//sd.setExampleData(angle);
							vc.setSteeringWheelAngle(angle);

						}
						if (rightLaneLength> 250 && rightLaneLength <320){
							angle = 26;
							vc.setSteeringWheelAngle(angle);
							//sd.setExampleData(angle);
							cout << "Doing the if in if to turn right" << endl;
						}
					}
				}
				else if(pt14.x == 0){
					angle = 0;
					vc.setSteeringWheelAngle(angle);
					//sd.setExampleData(angle);
					//vc.setSpeed(0.5);
					cout << "blind on the pt14(left)" <<endl;
					if (pt4.x != 640){
						if(rightLaneLength > 0 && rightLaneLength < 25){
							angle = -26;
							//sd.setExampleData(angle);
							vc.setSteeringWheelAngle(angle);
							cout << "Doing the if in if to turn left" << endl;
						}if (rightLaneLength> 25 && rightLaneLength <130){
							angle =10;
							//sd.setExampleData(angle);
							vc.setSteeringWheelAngle(angle);

						}
						if (rightLaneLength> 250 && rightLaneLength <320){
							angle = 26;
							vc.setSteeringWheelAngle(angle);
							//sd.setExampleData(angle);
							cout << "Doing the if in if to turn right" << endl;
						}
					}
				}
				else if(pt4.x == 640){
					angle = 0;
					vc.setSteeringWheelAngle(angle);
					//vc.setSpeed(0.5);
					//sd.setExampleData(angle);

					cout << "blind on the pt4 (right)" <<endl;
					cout << leftLaneLength << endl;
					if (pt5.x != 0){
						if(leftLaneLength > 0 && leftLaneLength < 25){
							angle = 26;
							vc.setSteeringWheelAngle(angle);
					//		sd.setExampleData(angle);
							cout << "Doing the if in if to turn right" << endl;
						}
						if (leftLaneLength> 25 && leftLaneLength <130){
							angle = -10;
							vc.setSteeringWheelAngle(angle);
					//		sd.setExampleData(angle);
							cout << "Doing the if in if to turn left" << endl;
						}
						if (leftLaneLength> 220 && leftLaneLength <320){
							angle = -26;
							vc.setSteeringWheelAngle(angle);
					//		sd.setExampleData(angle);
							cout << "Doing the if in if to turn left" << endl;
						}
					}
				}

				
				
				
				//cout << vc.getSpeed() << vc.getSteeringWheelAngle()<< endl;
				Container c(vc);
				//Container c(sd);
            	// Send container.
            	getConference().send(c);
                
            	
            }
            
            


            // 1. Do something with the image m_image here, for example: find lane marking features, optimize quality, ...



            // 2. Calculate desired steering commands from the image features.



            // Here, you see an example of how to send the data structure SteeringData to the ContainerConference.
            // This data structure will be received by all running components. In our example, it will be processed
            // by a potential component to "drive" the car.
           
            
            
            // Create container for finally sending the data.
            
        }

        // This method will do the main data processing job.
        // Therefore, it tries to open the real camera first. If that fails, the virtual camera images from camgen are used.
        odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode LaneDetector::body() {

int selection;

 cout << "Choose driving mode:" << endl;
          cout << "+++++++++++++++++" << endl;
          cout << "Key 1 for Parking" << endl;
          cout << "Key 2 for Overtaking" << endl;
          cout << "Any key for normal Driving" << endl;
          cout << "++++++++++++++++++++++++++" << endl;
          cin >> selection;
          cout << endl;


	        // Get configuration data.
	        KeyValueConfiguration kv = getKeyValueConfiguration();
	        m_debug = kv.getValue<int32_t> ("lanedetector.debug") == 1;

            unique_ptr<Player> player;
/*
            // Lane-detector can also directly read the data from file. This might be interesting to inspect the algorithm step-wisely.
            odcore::io::URL url("file://recording.rec");
            // Size of the memory buffer.
            const uint32_t MEMORY_SEGMENT_SIZE = kv.getValue<uint32_t>("global.buffer.memorySegmentSize");
            // Number of memory segments.
            const uint32_t NUMBER_OF_SEGMENTS = kv.getValue<uint32_t>("global.buffer.numberOfMemorySegments");
            // If AUTO_REWIND is true, the file will be played endlessly.
            const bool AUTO_REWIND = true;
            // We do not want player to run in parallel but we want to process frame by frame sequentially.
            const bool THREADING = false;
            // Construct the player.
            player = unique_ptr<Player>(new Player(url, AUTO_REWIND, MEMORY_SEGMENT_SIZE, NUMBER_OF_SEGMENTS, THREADING));
*/

            // Main data processing loop.
	        while (getModuleStateAndWaitForRemainingTimeInTimeslice() == odcore::data::dmcp::ModuleStateMessage::RUNNING) {
	        	//cout << "Hello" << endl;
		        bool has_next_frame = false;

		        // Use the shared memory image.
                Container c;
                if (player.get() != NULL) {
		            // Read the next container from file.
                    c = player->getNextContainerToBeSent();
                }
                else {
		            // Get the most recent available container for a SHARED_IMAGE.
		            c = getKeyValueDataStore().get(odcore::data::image::SharedImage::ID());
                }

		        if (c.getDataType() == odcore::data::image::SharedImage::ID()) {
			        // Example for processing the received container.
			        has_next_frame = readSharedImage(c);
		        }

		        // Process the read image.
		        if (true == has_next_frame) {
			        processImage();
		        }
	        }

	        return odcore::data::dmcp::ModuleExitCodeMessage::OKAY;
        }

    } // miniature
} // automotive
            


     
