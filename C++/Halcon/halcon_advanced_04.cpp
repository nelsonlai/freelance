/*
 * Halcon Advanced Program 4: Advanced Morphology and Topology
 * 
 * This program demonstrates:
 * - Advanced morphological operations
 * - Skeletonization and thinning
 * - Topological analysis
 * - Distance transforms and watershed
 * 
 * Prerequisites: 
 * - Halcon license file
 * 
 * Compilation: g++ -o halcon_advanced_04 halcon_advanced_04.cpp -lhalcon
 */

#include <iostream>
#include <HalconCpp.h>

using namespace HalconCpp;
using namespace std;

int main()
{
    try 
    {
        cout << "=== Halcon Advanced Program 4: Advanced Morphology and Topology ===" << endl;
        
        HWindow window(0, 0, 800, 600, 0, "visible", "");
        window.SetWindowParam("background_color", "black");
        
        // Create complex test image
        HImage test_image;
        test_image.GenImageConst("byte", 400, 400);
        
        HImage pattern;
        pattern.GenImageConst("byte", 400, 400);
        pattern.PaintRegion(HRectangle2(0, 0, 0, 400, 400), 50);
        
        // Create complex shapes
        pattern.PaintRegion(HCircle(100, 100, 60), 200);
        pattern.PaintRegion(HRectangle2(200, 200, 0, 100, 80), 180);
        pattern.PaintRegion(HCircle(300, 300, 40), 190);
        
        // Add some noise
        HImage noise;
        noise.GenImageConst("byte", 400, 400);
        noise.AddNoiseWhiteContourXld(noise, 0.05);
        pattern.AddImage(pattern, noise, &pattern);
        
        test_image = pattern;
        
        window.DispImage(test_image);
        cout << "Original image displayed" << endl;
        cin.get();
        
        // Threshold to binary
        HRegion binary_region;
        binary_region.BinaryThreshold(test_image, "max_separability", "light", &binary_region);
        
        window.ClearWindow();
        window.DispImage(test_image);
        window.SetColor("red");
        window.DispRegion(binary_region);
        cout << "Binary region displayed" << endl;
        cin.get();
        
        // Advanced morphological operations
        cout << "Applying advanced morphological operations..." << endl;
        
        // Skeletonization
        HRegion skeleton;
        skeleton.Skeleton(binary_region, &skeleton);
        
        window.ClearWindow();
        window.DispImage(test_image);
        window.SetColor("green");
        window.DispRegion(skeleton);
        cout << "Skeleton displayed" << endl;
        cin.get();
        
        // Thinning
        HRegion thinned;
        thinned.Thinning(binary_region, HTuple("lutz"), &thinned);
        
        window.ClearWindow();
        window.DispImage(test_image);
        window.SetColor("blue");
        window.DispRegion(thinned);
        cout << "Thinned region displayed" << endl;
        cin.get();
        
        // Distance transform
        cout << "Computing distance transform..." << endl;
        
        HImage distance_image;
        distance_image.DistanceTransform(binary_region, "euclidean", "true", &distance_image);
        
        window.ClearWindow();
        window.DispImage(distance_image);
        cout << "Distance transform displayed" << endl;
        cin.get();
        
        // Watershed segmentation
        cout << "Applying watershed segmentation..." << endl;
        
        HRegionArray watershed_regions;
        watershed_regions.WatershedsThreshold(distance_image, 5);
        
        HTuple num_watershed;
        num_watershed = watershed_regions.CountObj();
        cout << "Watershed found " << num_watershed[0].I() << " regions" << endl;
        
        window.ClearWindow();
        window.DispImage(test_image);
        window.SetColor("yellow");
        window.DispRegion(watershed_regions);
        cout << "Watershed regions displayed" << endl;
        cin.get();
        
        // Topological analysis
        cout << "Performing topological analysis..." << endl;
        
        // Count holes
        HTuple num_holes;
        binary_region.CountHoles(&num_holes);
        cout << "Number of holes: " << num_holes[0].I() << endl;
        
        // Count connected components
        HRegionArray connected_components;
        connected_components.Connection(binary_region);
        
        HTuple num_components;
        num_components = connected_components.CountObj();
        cout << "Number of connected components: " << num_components[0].I() << endl;
        
        // Analyze each component
        for (int i = 1; i <= num_components[0].I(); i++) 
        {
            HRegion component;
            component.SelectObj(connected_components, i);
            
            HTuple area, circularity, compactness;
            component.AreaCenter(&area, HTuple(), HTuple());
            component.Circularity(&circularity);
            component.Compactness(&compactness);
            
            cout << "Component " << i << ": area=" << area[0].I() 
                 << ", circularity=" << circularity[0].D() 
                 << ", compactness=" << compactness[0].D() << endl;
        }
        
        // Advanced morphological filters
        cout << "Applying advanced morphological filters..." << endl;
        
        // Top-hat transform
        HRegion top_hat;
        top_hat.TopHat(binary_region, HTuple("circle"), HTuple(5), &top_hat);
        
        window.ClearWindow();
        window.DispImage(test_image);
        window.SetColor("cyan");
        window.DispRegion(top_hat);
        cout << "Top-hat transform displayed" << endl;
        cin.get();
        
        // Bottom-hat transform
        HRegion bottom_hat;
        bottom_hat.BottomHat(binary_region, HTuple("circle"), HTuple(5), &bottom_hat);
        
        window.ClearWindow();
        window.DispImage(test_image);
        window.SetColor("magenta");
        window.DispRegion(bottom_hat);
        cout << "Bottom-hat transform displayed" << endl;
        cin.get();
        
        // Morphological gradient
        HRegion morpho_gradient;
        morpho_gradient.MorphGrad(binary_region, HTuple("circle"), HTuple(3), &morpho_gradient);
        
        window.ClearWindow();
        window.DispImage(test_image);
        window.SetColor("white");
        window.DispRegion(morpho_gradient);
        cout << "Morphological gradient displayed" << endl;
        cin.get();
        
        // Convex hull
        cout << "Computing convex hull..." << endl;
        
        HRegion convex_hull;
        convex_hull.ConvexHull(binary_region, &convex_hull);
        
        window.ClearWindow();
        window.DispImage(test_image);
        window.SetColor("red");
        window.DispRegion(binary_region);
        window.SetColor("green");
        window.DispRegion(convex_hull);
        cout << "Convex hull displayed (green outline)" << endl;
        cin.get();
        
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
