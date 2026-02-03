/*
 * Halcon Intermediate Program 5: Camera Calibration
 * 
 * This program demonstrates:
 * - Camera calibration using calibration plate
 * - Intrinsic and extrinsic parameter estimation
 * - Distortion correction
 * - 3D coordinate transformation
 * 
 * Prerequisites: 
 * - Halcon license file
 * - Calibration images or simulated calibration data
 * 
 * Compilation: g++ -o halcon_intermediate_05 halcon_intermediate_05.cpp -lhalcon
 */

#include <iostream>
#include <HalconCpp.h>

using namespace HalconCpp;
using namespace std;

int main()
{
    try 
    {
        cout << "=== Halcon Intermediate Program 5: Camera Calibration ===" << endl;
        
        HWindow window(0, 0, 800, 600, 0, "visible", "");
        window.SetWindowParam("background_color", "black");
        
        // Create calibration data
        HTuple calib_data_id;
        CreateCalibData("calibration_object", 1, 1, &calib_data_id);
        
        // Set calibration plate parameters
        HTuple plate_width = HTuple(0.1);  // 100mm
        HTuple plate_height = HTuple(0.1); // 100mm
        HTuple plate_spacing = HTuple(0.01); // 10mm spacing
        
        SetCalibDataCalibObject(calib_data_id, 0, plate_width, plate_height, 
                               plate_spacing, plate_spacing, HTuple());
        
        // Set camera parameters (initial estimates)
        HTuple camera_type = HTuple("area_scan_division");
        HTuple camera_params;
        camera_params = HTuple(0.008, 0.0, 0.000005, 0.000005, 320, 240, 640, 480);
        
        SetCalibDataCamPose(calib_data_id, 0, HTuple());
        SetCalibDataCamParam(calib_data_id, 0, camera_type, camera_params);
        
        cout << "Calibration data created" << endl;
        
        // Generate simulated calibration images
        cout << "Generating simulated calibration images..." << endl;
        
        for (int i = 0; i < 5; i++) 
        {
            // Create simulated calibration plate image
            HImage calib_image;
            calib_image.GenImageConst("byte", 640, 480);
            
            // Add calibration pattern (simplified)
            HTuple spacing = HTuple(50);  // Pixel spacing
            HTuple start_x = HTuple(100 + i * 20);
            HTuple start_y = HTuple(100 + i * 15);
            
            for (int row = 0; row < 8; row++) 
            {
                for (int col = 0; col < 8; col++) 
                {
                    HTuple x = HTuple(start_x[0].I() + col * spacing[0].I());
                    HTuple y = HTuple(start_y[0].I() + row * spacing[0].I());
                    
                    if (x[0].I() < 640 && y[0].I() < 480) 
                    {
                        calib_image.PaintRegion(HCircle(y, x, 3), 255);
                    }
                }
            }
            
            // Add calibration image to calibration data
            AddCalibDataImage(calib_image, calib_data_id, i, HTuple());
            
            cout << "Added calibration image " << i << endl;
        }
        
        // Perform calibration
        cout << "Performing camera calibration..." << endl;
        
        HTuple error;
        CalibrateCameras(calib_data_id, &error);
        
        cout << "Calibration completed with error: " << error[0].D() << endl;
        
        // Get calibrated camera parameters
        HTuple calibrated_params;
        GetCalibDataCamParam(calib_data_id, 0, HTuple(), &calibrated_params);
        
        cout << "Calibrated camera parameters:" << endl;
        cout << "Focal length: " << calibrated_params[0].D() << endl;
        cout << "Principal point: (" << calibrated_params[4].D() << ", " << calibrated_params[5].D() << ")" << endl;
        cout << "Image size: " << calibrated_params[6].I() << " x " << calibrated_params[7].I() << endl;
        
        // Demonstrate distortion correction
        cout << "Demonstrating distortion correction..." << endl;
        
        HImage test_image;
        test_image.GenImageConst("byte", 640, 480);
        
        // Add some geometric patterns
        test_image.PaintRegion(HRectangle2(200, 200, 0, 100, 100), 200);
        test_image.PaintRegion(HCircle(400, 300, 50), 150);
        
        // Apply distortion correction
        HImage corrected_image;
        corrected_image.ChangeRadialDistortionImage(test_image, calibrated_params, 
                                                  HTuple("constant"), &corrected_image);
        
        window.DispImage(test_image);
        cout << "Original image displayed" << endl;
        cin.get();
        
        window.ClearWindow();
        window.DispImage(corrected_image);
        cout << "Distortion-corrected image displayed" << endl;
        cin.get();
        
        // Demonstrate coordinate transformation
        cout << "Demonstrating coordinate transformation..." << endl;
        
        HTuple image_points_x, image_points_y;
        image_points_x = HTuple(320, 400, 480);
        image_points_y = HTuple(240, 200, 280);
        
        HTuple world_points_x, world_points_y, world_points_z;
        ImagePointsToWorldPlane(calibrated_params, HTuple(), image_points_x, image_points_y, 
                              HTuple("mm"), &world_points_x, &world_points_y, &world_points_z);
        
        cout << "Image to world coordinate transformation:" << endl;
        for (int i = 0; i < image_points_x.Length(); i++) 
        {
            cout << "Image (" << image_points_x[i].D() << ", " << image_points_y[i].D() 
                 << ") -> World (" << world_points_x[i].D() << ", " << world_points_y[i].D() 
                 << ", " << world_points_z[i].D() << ")" << endl;
        }
        
        // Clean up
        ClearCalibData(calib_data_id);
        
        window.ClearWindow();
        cout << "Program completed successfully!" << endl;
    }
    catch (HException& e)
    {
        cout << "Halcon Error: " << e.ErrorMessage() << endl;
        return -1;
    }
    catch (exception& e)
    {
        cout << "Standard Error: " << e.what() << endl;
        return -1;
    }
    
    return 0;
}
