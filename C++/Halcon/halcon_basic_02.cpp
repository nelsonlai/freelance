/*
 * Halcon Beginner Program 2: Image Conversion and Color Spaces
 * 
 * This program demonstrates:
 * - Converting between different image types (byte, int1, int2, int4, real)
 * - Working with different color spaces (RGB, HSV, Lab)
 * - Basic image manipulation operations
 * 
 * Prerequisites: 
 * - Halcon license file
 * - Sample image file (test_image.jpg)
 * 
 * Compilation: g++ -o halcon_basic_02 halcon_basic_02.cpp -lhalcon
 */

#include <iostream>
#include <HalconCpp.h>

using namespace HalconCpp;
using namespace std;

int main()
{
    try 
    {
        cout << "=== Halcon Beginner Program 2: Image Conversion and Color Spaces ===" << endl;
        
        // Create a window for displaying images
        HWindow window(0, 0, 800, 600, 0, "visible", "");
        window.SetWindowParam("background_color", "black");
        
        // Load an image
        HImage image;
        try 
        {
            image.ReadImage("test_image.jpg");
            cout << "Successfully loaded image: test_image.jpg" << endl;
        }
        catch (HException& e)
        {
            // Create a colorful test pattern if no image file exists
            cout << "No image file found, creating a colorful test pattern..." << endl;
            image.GenImageConst("byte", 300, 300);
            
            // Create a gradient pattern
            HImage gradient;
            gradient.GenImageGradient("sobel", image, &gradient);
            image = gradient;
        }
        
        // Display original image
        window.DispImage(image);
        cout << "Original image displayed" << endl;
        
        // Convert to different image types
        HImage image_int1, image_int2, image_real;
        
        // Convert to int1 (8-bit signed integer)
        image_int1.ConvertImageType(image, "int1");
        cout << "Converted to int1 format" << endl;
        
        // Convert to int2 (16-bit signed integer)
        image_int2.ConvertImageType(image, "int2");
        cout << "Converted to int2 format" << endl;
        
        // Convert to real (floating point)
        image_real.ConvertImageType(image, "real");
        cout << "Converted to real format" << endl;
        
        // If the image is RGB, demonstrate color space conversions
        HTuple channels;
        image.CountChannels(&channels);
        
        if (channels[0].I() == 3) 
        {
            cout << "RGB image detected, demonstrating color space conversions..." << endl;
            
            // Convert RGB to HSV
            HImage hsv_image;
            hsv_image.Rgb1ToHsv(image);
            cout << "Converted RGB to HSV" << endl;
            
            // Convert RGB to Lab
            HImage lab_image;
            lab_image.Rgb1ToLab(image);
            cout << "Converted RGB to Lab" << endl;
            
            // Display HSV image
            window.ClearWindow();
            window.DispImage(hsv_image);
            cout << "HSV image displayed" << endl;
            cin.get();
            
            // Display Lab image
            window.ClearWindow();
            window.DispImage(lab_image);
            cout << "Lab image displayed" << endl;
            cin.get();
        }
        else 
        {
            cout << "Grayscale image detected, demonstrating intensity scaling..." << endl;
            
            // Scale intensity values
            HImage scaled_image;
            scaled_image.ScaleImage(image, 2.0, 50.0);  // Scale by factor 2, add offset 50
            cout << "Scaled image intensity (factor: 2.0, offset: 50)" << endl;
            
            window.ClearWindow();
            window.DispImage(scaled_image);
            cout << "Scaled image displayed" << endl;
            cin.get();
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
