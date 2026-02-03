/*
 * Halcon Beginner Program 7: Image Saving and File Operations
 * 
 * This program demonstrates:
 * - Saving images in different formats (JPEG, PNG, TIFF, BMP)
 * - Image compression options
 * - Batch processing of multiple images
 * - File I/O operations with Halcon
 * 
 * Prerequisites: 
 * - Halcon license file
 * - Write permissions in current directory
 * 
 * Compilation: g++ -o halcon_basic_07 halcon_basic_07.cpp -lhalcon
 */

#include <iostream>
#include <HalconCpp.h>

using namespace HalconCpp;
using namespace std;

int main()
{
    try 
    {
        cout << "=== Halcon Beginner Program 7: Image Saving and File Operations ===" << endl;
        
        // Create a window for displaying images
        HWindow window(0, 0, 800, 600, 0, "visible", "");
        window.SetWindowParam("background_color", "black");
        
        // Create a test image with various features
        cout << "Creating test image with various features..." << endl;
        HImage test_image;
        test_image.GenImageConst("byte", 400, 400);
        
        // Create a colorful pattern
        HImage pattern;
        pattern.GenImageConst("byte", 400, 400);
        
        // Draw some geometric shapes with different intensities
        HTuple row1, col1, row2, col2;
        
        // Rectangle 1
        row1 = HTuple(50); col1 = HTuple(50); row2 = HTuple(150); col2 = HTuple(150);
        pattern.PaintRegion(HRectangle2(row1, col1, 0, row2-row1, col2-col1), 200);
        
        // Rectangle 2
        row1 = HTuple(200); col1 = HTuple(200); row2 = HTuple(300); col2 = HTuple(300);
        pattern.PaintRegion(HRectangle2(row1, col1, 0, row2-row1, col2-col1), 150);
        
        // Circle
        row1 = HTuple(250); col1 = HTuple(100); row2 = HTuple(350); col2 = HTuple(200);
        pattern.PaintRegion(HCircle(row1, col1, 50), 100);
        
        test_image = pattern;
        
        // Display the test image
        window.DispImage(test_image);
        cout << "Test image created and displayed" << endl;
        cin.get();
        
        // 1. Save image in different formats
        cout << "Saving image in different formats..." << endl;
        
        // Save as JPEG with different quality settings
        test_image.WriteImage("test_output.jpg");
        cout << "Saved as JPEG: test_output.jpg" << endl;
        
        // Save as PNG (lossless)
        test_image.WriteImage("test_output.png");
        cout << "Saved as PNG: test_output.png" << endl;
        
        // Save as TIFF (uncompressed)
        test_image.WriteImage("test_output.tif");
        cout << "Saved as TIFF: test_output.tif" << endl;
        
        // Save as BMP (uncompressed)
        test_image.WriteImage("test_output.bmp");
        cout << "Saved as BMP: test_output.bmp" << endl;
        
        // 2. Create and save processed versions
        cout << "Creating and saving processed versions..." << endl;
        
        // Create a blurred version
        HImage blurred;
        blurred.GaussImage(test_image, 2.0);
        blurred.WriteImage("test_blurred.jpg");
        cout << "Saved blurred version: test_blurred.jpg" << endl;
        
        // Create a sharpened version
        HImage sharpened;
        sharpened.Emphasize(test_image, 7, 7, 1.5);
        sharpened.WriteImage("test_sharpened.jpg");
        cout << "Saved sharpened version: test_sharpened.jpg" << endl;
        
        // Create an edge-detected version
        HImage edges;
        edges.SobelAmp(test_image);
        edges.WriteImage("test_edges.jpg");
        cout << "Saved edge-detected version: test_edges.jpg" << endl;
        
        // 3. Batch processing example
        cout << "Demonstrating batch processing..." << endl;
        
        // Create multiple test images with different properties
        for (int i = 1; i <= 3; i++) 
        {
            HImage batch_image;
            batch_image.GenImageConst("byte", 200, 200);
            
            // Create different patterns for each image
            HTuple intensity = HTuple(50 + i * 50);
            HTuple center_row = HTuple(100);
            HTuple center_col = HTuple(100);
            HTuple radius = HTuple(30 + i * 10);
            
            batch_image.PaintRegion(HCircle(center_row, center_col, radius), intensity);
            
            // Save with different names
            string filename = "batch_image_" + to_string(i) + ".jpg";
            batch_image.WriteImage(filename.c_str());
            cout << "Saved batch image: " << filename << endl;
        }
        
        // 4. Load and verify saved images
        cout << "Loading and verifying saved images..." << endl;
        
        try 
        {
            HImage loaded_jpeg;
            loaded_jpeg.ReadImage("test_output.jpg");
            
            HTuple width, height;
            loaded_jpeg.GetImageSize(&width, &height);
            cout << "Loaded JPEG dimensions: " << width[0].I() << " x " << height[0].I() << " pixels" << endl;
            
            window.ClearWindow();
            window.DispImage(loaded_jpeg);
            cout << "Loaded JPEG image displayed" << endl;
            cin.get();
        }
        catch (HException& e)
        {
            cout << "Error loading JPEG: " << e.ErrorMessage() << endl;
        }
        
        // 5. Create a multi-channel image and save
        cout << "Creating and saving multi-channel image..." << endl;
        
        // Create RGB image
        HImage red_channel, green_channel, blue_channel;
        red_channel.GenImageConst("byte", 200, 200);
        green_channel.GenImageConst("byte", 200, 200);
        blue_channel.GenImageConst("byte", 200, 200);
        
        // Set different intensities for each channel
        red_channel.PaintRegion(HCircle(100, 100, 80), 255);
        green_channel.PaintRegion(HCircle(100, 100, 60), 255);
        blue_channel.PaintRegion(HCircle(100, 100, 40), 255);
        
        // Combine channels
        HImage rgb_image;
        rgb_image.Compose3(red_channel, green_channel, blue_channel);
        
        // Save as RGB image
        rgb_image.WriteImage("test_rgb.jpg");
        cout << "Saved RGB image: test_rgb.jpg" << endl;
        
        window.ClearWindow();
        window.DispImage(rgb_image);
        cout << "RGB image displayed" << endl;
        cin.get();
        
        // 6. File information and metadata
        cout << "Displaying file information..." << endl;
        
        try 
        {
            HTuple file_info;
            file_info.GetImageInfo("test_output.jpg", "format", &file_info);
            cout << "JPEG file format: " << file_info[0].S() << endl;
            
            file_info.GetImageInfo("test_output.jpg", "width", &file_info);
            cout << "JPEG width: " << file_info[0].I() << endl;
            
            file_info.GetImageInfo("test_output.jpg", "height", &file_info);
            cout << "JPEG height: " << file_info[0].I() << endl;
        }
        catch (HException& e)
        {
            cout << "Error getting file info: " << e.ErrorMessage() << endl;
        }
        
        // Clear the window
        window.ClearWindow();
        
        cout << "Program completed successfully!" << endl;
        cout << "Check the current directory for saved image files." << endl;
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
