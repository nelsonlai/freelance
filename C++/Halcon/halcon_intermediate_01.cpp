/*
 * Halcon Intermediate Program 1: Camera Acquisition and Live Display
 * 
 * This program demonstrates:
 * - Opening and configuring a camera/framegrabber
 * - Live image acquisition from camera
 * - Real-time image display
 * - Camera parameter control
 * 
 * Prerequisites: 
 * - Halcon license file
 * - Camera/framegrabber connected to system
 * - Appropriate camera drivers installed
 * 
 * Compilation: g++ -o halcon_intermediate_01 halcon_intermediate_01.cpp -lhalcon
 */

#include <iostream>
#include <HalconCpp.h>

using namespace HalconCpp;
using namespace std;

int main()
{
    try 
    {
        cout << "=== Halcon Intermediate Program 1: Camera Acquisition and Live Display ===" << endl;
        
        // Create a window for displaying images
        HWindow window(0, 0, 640, 480, 0, "visible", "");
        window.SetWindowParam("background_color", "black");
        
        HTuple acq_handle;
        
        try 
        {
            // Try to open a framegrabber (camera)
            // Note: Parameters depend on your specific camera setup
            cout << "Attempting to open framegrabber..." << endl;
            
            // Common framegrabber configurations:
            // For USB cameras: "USB3Vision", "DirectShow", "GigEVision"
            // For industrial cameras: "GigEVision", "USB3Vision", "1394IIDC"
            
            OpenFramegrabber("DirectShow", 0, 0, 0, 0, 0, 0, "default", -1, "default", 
                           -1, "false", "default", "default", 0, -1, &acq_handle);
            
            cout << "Framegrabber opened successfully!" << endl;
            
            // Configure camera parameters
            cout << "Configuring camera parameters..." << endl;
            
            // Set image size (if supported by camera)
            SetFramegrabberParam(acq_handle, "image_width", 640);
            SetFramegrabberParam(acq_handle, "image_height", 480);
            
            // Set exposure time (if supported)
            SetFramegrabberParam(acq_handle, "exposure_time", 10000);  // 10ms
            
            // Set gain (if supported)
            SetFramegrabberParam(acq_handle, "gain", 1.0);
            
            cout << "Camera parameters configured" << endl;
            
            // Start acquisition
            cout << "Starting image acquisition..." << endl;
            GrabImageStart(acq_handle, -1);
            
            // Live display loop
            cout << "Starting live display (press 'q' to quit)..." << endl;
            
            HImage image;
            int frame_count = 0;
            char key = 0;
            
            while (key != 'q' && key != 'Q') 
            {
                try 
                {
                    // Grab image from camera
                    GrabImageAsync(&image, acq_handle, -1);
                    
                    // Display image
                    window.DispImage(image);
                    
                    frame_count++;
                    if (frame_count % 30 == 0) 
                    {
                        cout << "Frames captured: " << frame_count << endl;
                    }
                    
                    // Check for key press (non-blocking)
                    window.GetKey(&key);
                    
                    // Small delay to prevent excessive CPU usage
                    usleep(10000);  // 10ms delay
                }
                catch (HException& e)
                {
                    cout << "Error during acquisition: " << e.ErrorMessage() << endl;
                    break;
                }
            }
            
            // Stop acquisition
            GrabImageStop(acq_handle);
            cout << "Stopped image acquisition" << endl;
            
            // Close framegrabber
            CloseFramegrabber(acq_handle);
            cout << "Framegrabber closed" << endl;
        }
        catch (HException& e)
        {
            cout << "Error opening framegrabber: " << e.ErrorMessage() << endl;
            cout << "This is normal if no camera is connected." << endl;
            cout << "Creating simulated camera feed instead..." << endl;
            
            // Simulate camera feed with generated images
            HImage simulated_image;
            simulated_image.GenImageConst("byte", 640, 480);
            
            cout << "Simulated camera feed (press 'q' to quit)..." << endl;
            
            int frame_count = 0;
            char key = 0;
            
            while (key != 'q' && key != 'Q') 
            {
                // Generate a moving pattern
                HImage pattern;
                pattern.GenImageConst("byte", 640, 480);
                
                // Create a moving circle
                HTuple center_x = HTuple(320 + 200 * sin(frame_count * 0.1));
                HTuple center_y = HTuple(240 + 150 * cos(frame_count * 0.1));
                HTuple radius = HTuple(50 + 20 * sin(frame_count * 0.05));
                
                pattern.PaintRegion(HCircle(center_y, center_x, radius), 255);
                
                // Display simulated image
                window.DispImage(pattern);
                
                frame_count++;
                if (frame_count % 30 == 0) 
                {
                    cout << "Simulated frames: " << frame_count << endl;
                }
                
                // Check for key press
                window.GetKey(&key);
                
                // Small delay
                usleep(50000);  // 50ms delay
            }
        }
        
        // Clear the window
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
