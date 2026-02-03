/*
 * Halcon Advanced Program 1: 3D Vision and Stereo Reconstruction
 * 
 * This program demonstrates:
 * - Stereo camera calibration
 * - Disparity map computation
 * - 3D point cloud generation
 * - Depth estimation
 * 
 * Prerequisites: 
 * - Halcon license file
 * 
 * Compilation: g++ -o halcon_advanced_01 halcon_advanced_01.cpp -lhalcon
 */

#include <iostream>
#include <HalconCpp.h>

using namespace HalconCpp;
using namespace std;

int main()
{
    try 
    {
        cout << "=== Halcon Advanced Program 1: 3D Vision and Stereo Reconstruction ===" << endl;
        
        HWindow window(0, 0, 800, 600, 0, "visible", "");
        window.SetWindowParam("background_color", "black");
        
        // Create stereo calibration data
        HTuple calib_data_id;
        CreateCalibData("calibration_object", 2, 1, &calib_data_id);
        
        // Set calibration parameters
        HTuple plate_width = HTuple(0.1);
        HTuple plate_height = HTuple(0.1);
        HTuple plate_spacing = HTuple(0.01);
        
        SetCalibDataCalibObject(calib_data_id, 0, plate_width, plate_height, 
                               plate_spacing, plate_spacing, HTuple());
        
        // Set camera parameters
        HTuple camera_type = HTuple("area_scan_division");
        HTuple camera_params;
        camera_params = HTuple(0.008, 0.0, 0.000005, 0.000005, 320, 240, 640, 480);
        
        SetCalibDataCamParam(calib_data_id, 0, camera_type, camera_params);
        SetCalibDataCamParam(calib_data_id, 1, camera_type, camera_params);
        
        cout << "Stereo calibration data created" << endl;
        
        // Generate simulated stereo images
        HImage left_image, right_image;
        left_image.GenImageConst("byte", 640, 480);
        right_image.GenImageConst("byte", 640, 480);
        
        // Create patterns for stereo matching
        HImage left_pattern, right_pattern;
        left_pattern.GenImageConst("byte", 640, 480);
        right_pattern.GenImageConst("byte", 640, 480);
        
        // Add features with known disparity
        left_pattern.PaintRegion(HCircle(200, 200, 30), 200);
        right_pattern.PaintRegion(HCircle(200, 180, 30), 200);  // 20 pixel disparity
        
        left_pattern.PaintRegion(HCircle(300, 300, 25), 180);
        right_pattern.PaintRegion(HCircle(300, 275, 25), 180);  // 25 pixel disparity
        
        left_image = left_pattern;
        right_image = right_pattern;
        
        window.DispImage(left_image);
        cout << "Left stereo image displayed" << endl;
        cin.get();
        
        window.ClearWindow();
        window.DispImage(right_image);
        cout << "Right stereo image displayed" << endl;
        cin.get();
        
        // Compute disparity map
        cout << "Computing disparity map..." << endl;
        
        HImage disparity_map;
        disparity_map.BinocularDisparity(left_image, right_image, HTuple("census"), 
                                       HTuple("census"), HTuple(5), HTuple(5), 
                                       HTuple(0), HTuple(50), HTuple(0.5), 
                                       HTuple("false"), HTuple("false"), 
                                       HTuple("sub_pixel"), HTuple("false"), 
                                       &disparity_map);
        
        window.ClearWindow();
        window.DispImage(disparity_map);
        cout << "Disparity map displayed" << endl;
        cin.get();
        
        // Convert disparity to depth
        cout << "Converting disparity to depth..." << endl;
        
        HImage depth_map;
        depth_map.BinocularDistance(left_image, right_image, HTuple("census"), 
                                   HTuple("census"), HTuple(5), HTuple(5), 
                                   HTuple(0), HTuple(50), HTuple(0.5), 
                                   HTuple("false"), HTuple("false"), 
                                   HTuple("sub_pixel"), HTuple("false"), 
                                   &depth_map);
        
        window.ClearWindow();
        window.DispImage(depth_map);
        cout << "Depth map displayed" << endl;
        cin.get();
        
        // Generate 3D point cloud
        cout << "Generating 3D point cloud..." << endl;
        
        HTuple x_coords, y_coords, z_coords;
        DisparityToDistance(disparity_map, HTuple(0.1), HTuple(0.008), 
                           HTuple(0.1), &x_coords, &y_coords, &z_coords);
        
        cout << "3D point cloud generated with " << x_coords.Length() << " points" << endl;
        
        // Display 3D points
        window.ClearWindow();
        window.DispImage(left_image);
        window.SetColor("red");
        for (int i = 0; i < min(100, (int)x_coords.Length()); i += 5) 
        {
            HTuple row = HTuple(y_coords[i].D());
            HTuple col = HTuple(x_coords[i].D());
            window.DispCross(row[0].D(), col[0].D(), 3, 0);
        }
        cout << "3D points overlaid on left image" << endl;
        cin.get();
        
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
