/*
 * Halcon Beginner Program 3: Basic Image Filtering
 * 
 * This program demonstrates:
 * - Basic image filtering operations (smoothing, sharpening)
 * - Noise reduction techniques
 * - Edge detection basics
 * 
 * Prerequisites: 
 * - Halcon license file
 * - Sample image file (test_image.jpg)
 * 
 * Compilation: g++ -o halcon_basic_03 halcon_basic_03.cpp -lhalcon
 */

#include <iostream>
#include <HalconCpp.h>

using namespace HalconCpp;
using namespace std;

int main()
{
    try 
    {
        cout << "=== Halcon Beginner Program 3: Basic Image Filtering ===" << endl;
        
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
            // Create a test pattern with some noise
            cout << "No image file found, creating a test pattern with noise..." << endl;
            image.GenImageConst("byte", 400, 400);
            
            // Add some noise to make filtering effects visible
            HImage noise;
            noise.GenImageConst("byte", 400, 400);
            noise.AddNoiseWhiteContourXld(noise, 0.1);  // Add 10% noise
            image = noise;
        }
        
        // Display original image
        window.DispImage(image);
        cout << "Original image displayed" << endl;
        cin.get();
        
        // 1. Smoothing filters
        cout << "Applying smoothing filters..." << endl;
        
        // Mean filter (simple averaging)
        HImage mean_filtered;
        mean_filtered.MeanImage(image, 5, 5);  // 5x5 kernel
        cout << "Applied mean filter (5x5)" << endl;
        
        window.ClearWindow();
        window.DispImage(mean_filtered);
        cout << "Mean filtered image displayed" << endl;
        cin.get();
        
        // Gaussian filter (better smoothing)
        HImage gaussian_filtered;
        gaussian_filtered.GaussImage(image, 1.0);  // Sigma = 1.0
        cout << "Applied Gaussian filter (sigma=1.0)" << endl;
        
        window.ClearWindow();
        window.DispImage(gaussian_filtered);
        cout << "Gaussian filtered image displayed" << endl;
        cin.get();
        
        // 2. Sharpening filter
        cout << "Applying sharpening filter..." << endl;
        HImage sharpened;
        sharpened.Emphasize(image, 7, 7, 1.0);  // 7x7 kernel, factor 1.0
        cout << "Applied emphasize filter for sharpening" << endl;
        
        window.ClearWindow();
        window.DispImage(sharpened);
        cout << "Sharpened image displayed" << endl;
        cin.get();
        
        // 3. Edge detection
        cout << "Applying edge detection..." << endl;
        
        // Sobel edge detection
        HImage sobel_edges;
        sobel_edges.SobelAmp(image);
        cout << "Applied Sobel edge detection" << endl;
        
        window.ClearWindow();
        window.DispImage(sobel_edges);
        cout << "Sobel edges displayed" << endl;
        cin.get();
        
        // Roberts edge detection
        HImage roberts_edges;
        roberts_edges.RobertsAmp(image);
        cout << "Applied Roberts edge detection" << endl;
        
        window.ClearWindow();
        window.DispImage(roberts_edges);
        cout << "Roberts edges displayed" << endl;
        cin.get();
        
        // 4. Median filter (good for noise reduction)
        cout << "Applying median filter for noise reduction..." << endl;
        HImage median_filtered;
        median_filtered.MedianImage(image, "circle", 3, "mirrored");  // 3x3 circular kernel
        cout << "Applied median filter" << endl;
        
        window.ClearWindow();
        window.DispImage(median_filtered);
        cout << "Median filtered image displayed" << endl;
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
