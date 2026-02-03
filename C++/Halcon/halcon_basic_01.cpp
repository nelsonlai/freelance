/*
 * Halcon Beginner Program 1: Basic Image Loading and Display
 * 
 * This program demonstrates the most fundamental Halcon operations:
 * - Loading an image from file
 * - Displaying the image in a window
 * - Basic error handling
 * 
 * Prerequisites: 
 * - Halcon license file
 * - Sample image file (test_image.jpg)
 * 
 * Compilation: g++ -o halcon_basic_01 halcon_basic_01.cpp -lhalcon
 */

#include <iostream>
#include <HalconCpp.h>

using namespace HalconCpp;
using namespace std;

int main()
{
    try 
    {
        cout << "=== Halcon Beginner Program 1: Basic Image Loading and Display ===" << endl;
        
        // Create a window for displaying images
        HWindow window(0, 0, 512, 512, 0, "visible", "");
        window.SetWindowParam("background_color", "black");
        
        // Load an image from file
        HImage image;
        try 
        {
            // Try to load a sample image - replace with your own image path
            image.ReadImage("test_image.jpg");
            cout << "Successfully loaded image: test_image.jpg" << endl;
        }
        catch (HException& e)
        {
            // If no image file exists, create a simple test pattern
            cout << "No image file found, creating a test pattern..." << endl;
            image.GenImageConst("byte", 400, 400);
            
            // Create a simple gradient pattern
            HImage gradient;
            gradient.GenImageGradient("sobel", image, &gradient);
            image = gradient;
        }
        
        // Get image dimensions
        HTuple width, height;
        image.GetImageSize(&width, &height);
        cout << "Image dimensions: " << width[0].I() << " x " << height[0].I() << " pixels" << endl;
        
        // Display the image
        window.DispImage(image);
        
        // Wait for user input
        cout << "Image displayed. Press any key to continue..." << endl;
        cin.get();
        
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
