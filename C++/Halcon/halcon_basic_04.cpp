/*
 * Halcon Beginner Program 4: Image Thresholding and Binary Operations
 * 
 * This program demonstrates:
 * - Different thresholding techniques (global, local, adaptive)
 * - Binary image operations (morphology)
 * - Region growing and connected components
 * 
 * Prerequisites: 
 * - Halcon license file
 * - Sample image file (test_image.jpg)
 * 
 * Compilation: g++ -o halcon_basic_04 halcon_basic_04.cpp -lhalcon
 */

#include <iostream>
#include <HalconCpp.h>

using namespace HalconCpp;
using namespace std;

int main()
{
    try 
    {
        cout << "=== Halcon Beginner Program 4: Image Thresholding and Binary Operations ===" << endl;
        
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
            // Create a test pattern with different intensity regions
            cout << "No image file found, creating a test pattern with different regions..." << endl;
            image.GenImageConst("byte", 400, 400);
            
            // Create regions with different intensities
            HImage pattern;
            pattern.GenImageConst("byte", 400, 400);
            
            // Draw some geometric shapes with different intensities
            HTuple row1, col1, row2, col2;
            row1 = HTuple(100); col1 = HTuple(100); row2 = HTuple(200); col2 = HTuple(200);
            pattern.PaintRegion(HRectangle2(row1, col1, 0, row2-row1, col2-col1), 150);
            
            row1 = HTuple(250); col1 = HTuple(150); row2 = HTuple(350); col2 = HTuple(250);
            pattern.PaintRegion(HRectangle2(row1, col1, 0, row2-row1, col2-col1), 200);
            
            image = pattern;
        }
        
        // Display original image
        window.DispImage(image);
        cout << "Original image displayed" << endl;
        cin.get();
        
        // 1. Global thresholding
        cout << "Applying global thresholding..." << endl;
        HRegion global_threshold;
        global_threshold.BinaryThreshold(image, "max_separability", "light", &global_threshold);
        cout << "Applied global thresholding (max_separability)" << endl;
        
        window.ClearWindow();
        window.DispRegion(global_threshold);
        cout << "Global threshold result displayed" << endl;
        cin.get();
        
        // 2. Local thresholding
        cout << "Applying local thresholding..." << endl;
        HRegion local_threshold;
        local_threshold.LocalThreshold(image, 10, 10, "light", &local_threshold);
        cout << "Applied local thresholding (10x10 neighborhood)" << endl;
        
        window.ClearWindow();
        window.DispRegion(local_threshold);
        cout << "Local threshold result displayed" << endl;
        cin.get();
        
        // 3. Adaptive thresholding
        cout << "Applying adaptive thresholding..." << endl;
        HRegion adaptive_threshold;
        adaptive_threshold.AdaptiveThreshold(image, 10, 10, 0, 0, "light", &adaptive_threshold);
        cout << "Applied adaptive thresholding" << endl;
        
        window.ClearWindow();
        window.DispRegion(adaptive_threshold);
        cout << "Adaptive threshold result displayed" << endl;
        cin.get();
        
        // 4. Binary morphology operations
        cout << "Applying binary morphology operations..." << endl;
        
        // Erosion
        HRegion eroded;
        eroded.ErosionCircle(global_threshold, 3.5, &eroded);
        cout << "Applied erosion with circular structuring element (radius=3.5)" << endl;
        
        window.ClearWindow();
        window.DispRegion(eroded);
        cout << "Eroded regions displayed" << endl;
        cin.get();
        
        // Dilation
        HRegion dilated;
        dilated.DilationCircle(global_threshold, 3.5, &dilated);
        cout << "Applied dilation with circular structuring element (radius=3.5)" << endl;
        
        window.ClearWindow();
        window.DispRegion(dilated);
        cout << "Dilated regions displayed" << endl;
        cin.get();
        
        // Opening (erosion followed by dilation)
        HRegion opened;
        opened.OpeningCircle(global_threshold, 3.5, &opened);
        cout << "Applied opening operation" << endl;
        
        window.ClearWindow();
        window.DispRegion(opened);
        cout << "Opened regions displayed" << endl;
        cin.get();
        
        // Closing (dilation followed by erosion)
        HRegion closed;
        closed.ClosingCircle(global_threshold, 3.5, &closed);
        cout << "Applied closing operation" << endl;
        
        window.ClearWindow();
        window.DispRegion(closed);
        cout << "Closed regions displayed" << endl;
        cin.get();
        
        // 5. Connected components analysis
        cout << "Analyzing connected components..." << endl;
        HRegionArray connected_regions;
        connected_regions.Connection(global_threshold);
        
        HTuple num_regions;
        num_regions = connected_regions.CountObj();
        cout << "Found " << num_regions[0].I() << " connected components" << endl;
        
        // Display connected components with different colors
        window.ClearWindow();
        window.SetColor("red");
        window.DispRegion(connected_regions);
        cout << "Connected components displayed in red" << endl;
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
