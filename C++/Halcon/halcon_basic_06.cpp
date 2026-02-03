/*
 * Halcon Beginner Program 6: Image Statistics and Analysis
 * 
 * This program demonstrates:
 * - Basic image statistics (mean, variance, histogram)
 * - Image quality metrics
 * - Region properties and measurements
 * 
 * Prerequisites: 
 * - Halcon license file
 * - Sample image file (test_image.jpg)
 * 
 * Compilation: g++ -o halcon_basic_06 halcon_basic_06.cpp -lhalcon
 */

#include <iostream>
#include <HalconCpp.h>

using namespace HalconCpp;
using namespace std;

int main()
{
    try 
    {
        cout << "=== Halcon Beginner Program 6: Image Statistics and Analysis ===" << endl;
        
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
            // Create a test pattern with varying intensities
            cout << "No image file found, creating a test pattern with varying intensities..." << endl;
            image.GenImageConst("byte", 400, 400);
            
            // Create a gradient pattern
            HImage gradient;
            gradient.GenImageGradient("sobel", image, &gradient);
            image = gradient;
        }
        
        // Display original image
        window.DispImage(image);
        cout << "Original image displayed" << endl;
        cin.get();
        
        // 1. Basic image statistics
        cout << "Calculating basic image statistics..." << endl;
        
        HTuple mean, deviation;
        image.Intensity(image, &mean, &deviation);
        cout << "Mean intensity: " << mean[0].D() << endl;
        cout << "Standard deviation: " << deviation[0].D() << endl;
        
        HTuple min_val, max_val;
        image.MinMaxGray(image, image, &min_val, &max_val);
        cout << "Minimum intensity: " << min_val[0].I() << endl;
        cout << "Maximum intensity: " << max_val[0].I() << endl;
        
        // 2. Image histogram
        cout << "Calculating image histogram..." << endl;
        HTuple histogram;
        image.GrayHisto(image, &histogram);
        
        cout << "Histogram calculated with " << histogram.Length() << " bins" << endl;
        
        // Display histogram
        window.ClearWindow();
        window.DispImage(image);
        window.SetColor("red");
        
        // Draw histogram as a simple bar chart
        HTuple max_hist = histogram.Max();
        for (int i = 0; i < histogram.Length() && i < 256; i += 4) 
        {
            HTuple height = histogram[i].I() * 100 / max_hist[0].I();
            window.DispRectangle1(400 - height[0].I(), i, 400, i + 2);
        }
        
        cout << "Histogram overlaid on image (red bars)" << endl;
        cin.get();
        
        // 3. Image quality metrics
        cout << "Calculating image quality metrics..." << endl;
        
        // Calculate image entropy (measure of information content)
        HTuple entropy;
        entropy.EntropyImage(image, 7, 7);
        cout << "Image entropy: " << entropy[0].D() << endl;
        
        // Calculate image variance (measure of contrast)
        HTuple variance;
        image.VarianceImage(image, 7, 7, &variance);
        cout << "Image variance: " << variance[0].D() << endl;
        
        // 4. Region-based analysis
        cout << "Performing region-based analysis..." << endl;
        
        // Create a thresholded region
        HRegion threshold_region;
        threshold_region.BinaryThreshold(image, "max_separability", "light", &threshold_region);
        
        // Calculate region properties
        HTuple area, row_center, col_center;
        threshold_region.AreaCenter(&area, &row_center, &col_center);
        cout << "Threshold region area: " << area[0].I() << " pixels" << endl;
        cout << "Region center: (" << row_center[0].D() << ", " << col_center[0].D() << ")" << endl;
        
        // Calculate region orientation and major/minor axes
        HTuple orientation, major_axis, minor_axis;
        threshold_region.OrientationRegion(&orientation);
        threshold_region.EllipticAxis(threshold_region, &major_axis, &minor_axis);
        cout << "Region orientation: " << orientation[0].D() << " radians" << endl;
        cout << "Major axis length: " << major_axis[0].D() << endl;
        cout << "Minor axis length: " << minor_axis[0].D() << endl;
        
        // Display region
        window.ClearWindow();
        window.DispImage(image);
        window.SetColor("green");
        window.DispRegion(threshold_region);
        cout << "Threshold region displayed in green" << endl;
        cin.get();
        
        // 5. Connected components analysis
        cout << "Analyzing connected components..." << endl;
        HRegionArray connected_regions;
        connected_regions.Connection(threshold_region);
        
        HTuple num_regions;
        num_regions = connected_regions.CountObj();
        cout << "Number of connected components: " << num_regions[0].I() << endl;
        
        // Calculate properties for each connected component
        for (int i = 1; i <= num_regions[0].I() && i <= 5; i++) 
        {
            HRegion single_region;
            single_region.SelectObj(connected_regions, i);
            
            HTuple region_area, region_row, region_col;
            single_region.AreaCenter(&region_area, &region_row, &region_col);
            
            cout << "Component " << i << ": area=" << region_area[0].I() 
                 << ", center=(" << region_row[0].D() << ", " << region_col[0].D() << ")" << endl;
        }
        
        // Display connected components
        window.ClearWindow();
        window.DispImage(image);
        window.SetColor("blue");
        window.DispRegion(connected_regions);
        cout << "Connected components displayed in blue" << endl;
        cin.get();
        
        // 6. Image moments
        cout << "Calculating image moments..." << endl;
        HTuple moments;
        image.MomentsGray(image, image, &moments);
        
        cout << "Image moments calculated:" << endl;
        cout << "M00 (area): " << moments[0].D() << endl;
        cout << "M10: " << moments[1].D() << endl;
        cout << "M01: " << moments[2].D() << endl;
        cout << "M20: " << moments[3].D() << endl;
        cout << "M11: " << moments[4].D() << endl;
        cout << "M02: " << moments[5].D() << endl;
        
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
