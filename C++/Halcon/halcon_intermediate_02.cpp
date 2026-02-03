/*
 * Halcon Intermediate Program 2: Advanced Image Segmentation
 * 
 * This program demonstrates:
 * - Watershed segmentation
 * - Region growing algorithms
 * - Color-based segmentation
 * - Multi-threshold segmentation
 * 
 * Prerequisites: 
 * - Halcon license file
 * - Sample image file (test_image.jpg)
 * 
 * Compilation: g++ -o halcon_intermediate_02 halcon_intermediate_02.cpp -lhalcon
 */

#include <iostream>
#include <HalconCpp.h>

using namespace HalconCpp;
using namespace std;

int main()
{
    try 
    {
        cout << "=== Halcon Intermediate Program 2: Advanced Image Segmentation ===" << endl;
        
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
            // Create a complex test pattern for segmentation
            cout << "No image file found, creating a complex test pattern..." << endl;
            image.GenImageConst("byte", 400, 400);
            
            // Create multiple regions with different intensities
            HImage pattern;
            pattern.GenImageConst("byte", 400, 400);
            
            // Background
            pattern.PaintRegion(HRectangle2(0, 0, 0, 400, 400), 50);
            
            // Region 1 - bright
            pattern.PaintRegion(HCircle(100, 100, 60), 200);
            
            // Region 2 - medium
            pattern.PaintRegion(HCircle(200, 200, 50), 150);
            
            // Region 3 - dark
            pattern.PaintRegion(HCircle(300, 150, 40), 100);
            
            // Region 4 - very bright
            pattern.PaintRegion(HCircle(150, 300, 45), 220);
            
            // Add some noise
            HImage noise;
            noise.GenImageConst("byte", 400, 400);
            noise.AddNoiseWhiteContourXld(noise, 0.05);  // 5% noise
            pattern.AddImage(pattern, noise, &pattern);
            
            image = pattern;
        }
        
        // Display original image
        window.DispImage(image);
        cout << "Original image displayed" << endl;
        cin.get();
        
        // 1. Watershed segmentation
        cout << "Applying watershed segmentation..." << endl;
        
        // First, create a gradient image for watershed
        HImage gradient;
        gradient.GenImageGradient("sobel", image, &gradient);
        
        // Apply watershed segmentation
        HRegionArray watershed_regions;
        watershed_regions.WatershedsThreshold(gradient, 10);
        
        HTuple num_watershed;
        num_watershed = watershed_regions.CountObj();
        cout << "Watershed segmentation found " << num_watershed[0].I() << " regions" << endl;
        
        window.ClearWindow();
        window.DispImage(image);
        window.SetColor("red");
        window.DispRegion(watershed_regions);
        cout << "Watershed segmentation result displayed" << endl;
        cin.get();
        
        // 2. Region growing
        cout << "Applying region growing..." << endl;
        
        // Start with seed points
        HTuple seed_rows, seed_cols;
        seed_rows = HTuple(100, 200, 300, 150);
        seed_cols = HTuple(100, 200, 150, 300);
        
        HRegionArray grown_regions;
        grown_regions.RegionGrowing(image, seed_rows, seed_cols, 30, 5);
        
        HTuple num_grown;
        num_grown = grown_regions.CountObj();
        cout << "Region growing found " << num_grown[0].I() << " regions" << endl;
        
        window.ClearWindow();
        window.DispImage(image);
        window.SetColor("green");
        window.DispRegion(grown_regions);
        cout << "Region growing result displayed" << endl;
        cin.get();
        
        // 3. Multi-threshold segmentation
        cout << "Applying multi-threshold segmentation..." << endl;
        
        // Calculate multiple thresholds
        HTuple thresholds;
        thresholds.AutoThreshold(image, 0.5);
        
        cout << "Found " << thresholds.Length() << " thresholds: ";
        for (int i = 0; i < thresholds.Length(); i++) 
        {
            cout << thresholds[i].I() << " ";
        }
        cout << endl;
        
        // Create regions for each threshold
        HRegionArray multi_threshold_regions;
        for (int i = 0; i < thresholds.Length() - 1; i++) 
        {
            HRegion threshold_region;
            threshold_region.Threshold(image, thresholds[i].I(), thresholds[i+1].I());
            multi_threshold_regions.Append(threshold_region);
        }
        
        window.ClearWindow();
        window.DispImage(image);
        window.SetColor("blue");
        window.DispRegion(multi_threshold_regions);
        cout << "Multi-threshold segmentation result displayed" << endl;
        cin.get();
        
        // 4. Color-based segmentation (if RGB image)
        HTuple channels;
        image.CountChannels(&channels);
        
        if (channels[0].I() == 3) 
        {
            cout << "Applying color-based segmentation..." << endl;
            
            // Convert to HSV for better color segmentation
            HImage hsv_image;
            hsv_image.Rgb1ToHsv(image);
            
            // Access individual channels
            HImage h_channel, s_channel, v_channel;
            h_channel.AccessChannel(hsv_image, 1);
            s_channel.AccessChannel(hsv_image, 2);
            v_channel.AccessChannel(hsv_image, 3);
            
            // Segment based on hue
            HRegionArray hue_regions;
            hue_regions.Threshold(h_channel, 0, 60);  // Red hues
            
            window.ClearWindow();
            window.DispImage(image);
            window.SetColor("yellow");
            window.DispRegion(hue_regions);
            cout << "Color-based segmentation (red hues) displayed" << endl;
            cin.get();
        }
        
        // 5. Edge-based segmentation
        cout << "Applying edge-based segmentation..." << endl;
        
        // Detect edges
        HImage edges;
        edges.EdgesSubPix(image, "canny", 1.0, 20, 40);
        
        // Convert edges to regions
        HRegionArray edge_regions;
        edge_regions.EdgesToRegion(edges, "hysteresis", 20, 40);
        
        window.ClearWindow();
        window.DispImage(image);
        window.SetColor("cyan");
        window.DispRegion(edge_regions);
        cout << "Edge-based segmentation result displayed" << endl;
        cin.get();
        
        // 6. Morphological segmentation
        cout << "Applying morphological segmentation..." << endl;
        
        // Start with a simple threshold
        HRegion threshold_region;
        threshold_region.BinaryThreshold(image, "max_separability", "light", &threshold_region);
        
        // Apply morphological operations to separate touching objects
        HRegionArray morpho_regions;
        
        // Distance transform
        HImage distance_image;
        distance_image.DistanceTransform(threshold_region, "euclidean", "true", &distance_image);
        
        // Watershed on distance transform
        HImage morpho_gradient;
        morpho_gradient.GenImageGradient("sobel", distance_image, &morpho_gradient);
        morpho_regions.WatershedsThreshold(morpho_gradient, 5);
        
        window.ClearWindow();
        window.DispImage(image);
        window.SetColor("magenta");
        window.DispRegion(morpho_regions);
        cout << "Morphological segmentation result displayed" << endl;
        cin.get();
        
        // 7. Region analysis and filtering
        cout << "Analyzing and filtering regions..." << endl;
        
        // Select regions by area
        HRegionArray filtered_regions;
        filtered_regions.SelectShape(morpho_regions, "area", "and", 500, 10000);
        
        HTuple num_filtered;
        num_filtered = filtered_regions.CountObj();
        cout << "After area filtering: " << num_filtered[0].I() << " regions" << endl;
        
        // Select regions by circularity
        HRegionArray circular_regions;
        circular_regions.SelectShape(filtered_regions, "circularity", "and", 0.7, 1.0);
        
        HTuple num_circular;
        num_circular = circular_regions.CountObj();
        cout << "After circularity filtering: " << num_circular[0].I() << " regions" << endl;
        
        window.ClearWindow();
        window.DispImage(image);
        window.SetColor("white");
        window.DispRegion(circular_regions);
        cout << "Final filtered regions displayed" << endl;
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
