/*
 * Halcon Advanced Program 6: Industrial Vision System
 * 
 * This program demonstrates:
 * - Complete industrial vision pipeline
 * - Quality control and inspection
 * - Measurement and metrology
 * - Defect detection and classification
 * 
 * Prerequisites: 
 * - Halcon license file
 * 
 * Compilation: g++ -o halcon_advanced_06 halcon_advanced_06.cpp -lhalcon
 */

#include <iostream>
#include <HalconCpp.h>

using namespace HalconCpp;
using namespace std;

int main()
{
    try 
    {
        cout << "=== Halcon Advanced Program 6: Industrial Vision System ===" << endl;
        
        HWindow window(0, 0, 800, 600, 0, "visible", "");
        window.SetWindowParam("background_color", "black");
        
        // Create industrial test image
        HImage product_image;
        product_image.GenImageConst("byte", 500, 500);
        
        HImage pattern;
        pattern.GenImageConst("byte", 500, 500);
        pattern.PaintRegion(HRectangle2(0, 0, 0, 500, 500), 100);
        
        // Create product features
        pattern.PaintRegion(HRectangle2(200, 200, 0, 100, 100), 200);  // Main product
        pattern.PaintRegion(HCircle(250, 250, 30), 180);  // Hole
        pattern.PaintRegion(HRectangle2(220, 220, 0, 20, 20), 150);  // Feature 1
        pattern.PaintRegion(HRectangle2(260, 260, 0, 20, 20), 150);  // Feature 2
        
        // Add some defects
        pattern.PaintRegion(HCircle(300, 300, 5), 50);  // Defect 1
        pattern.PaintRegion(HRectangle2(180, 180, 0, 10, 10), 50);  // Defect 2
        
        product_image = pattern;
        
        window.DispImage(product_image);
        cout << "Product image displayed" << endl;
        cin.get();
        
        // Step 1: Product detection and localization
        cout << "Step 1: Product detection and localization..." << endl;
        
        HRegion product_region;
        product_region.BinaryThreshold(product_image, "max_separability", "light", &product_region);
        
        // Filter by area to get main product
        HRegion main_product;
        main_product.SelectShape(product_region, "area", "and", 5000, 20000, &main_product);
        
        HTuple product_area, product_row, product_col;
        main_product.AreaCenter(&product_area, &product_row, &product_col);
        
        cout << "Product detected at: (" << product_row[0].D() << ", " << product_col[0].D() << ")" << endl;
        cout << "Product area: " << product_area[0].I() << " pixels" << endl;
        
        window.ClearWindow();
        window.DispImage(product_image);
        window.SetColor("green");
        window.DispRegion(main_product);
        cout << "Product region displayed" << endl;
        cin.get();
        
        // Step 2: Dimensional measurement
        cout << "Step 2: Dimensional measurement..." << endl;
        
        HTuple product_width, product_height;
        main_product.WidthHeight(&product_width, &product_height);
        
        HTuple orientation, major_axis, minor_axis;
        main_product.OrientationRegion(&orientation);
        main_product.EllipticAxis(main_product, &major_axis, &minor_axis);
        
        cout << "Product dimensions:" << endl;
        cout << "  Width: " << product_width[0].D() << " pixels" << endl;
        cout << "  Height: " << product_height[0].D() << " pixels" << endl;
        cout << "  Major axis: " << major_axis[0].D() << " pixels" << endl;
        cout << "  Minor axis: " << minor_axis[0].D() << " pixels" << endl;
        cout << "  Orientation: " << orientation[0].D() << " radians" << endl;
        
        // Step 3: Feature detection and measurement
        cout << "Step 3: Feature detection and measurement..." << endl;
        
        HRegionArray features;
        features.SelectShape(product_region, "area", "and", 200, 2000, &features);
        
        HTuple num_features;
        num_features = features.CountObj();
        cout << "Found " << num_features[0].I() << " features" << endl;
        
        // Measure feature positions
        for (int i = 1; i <= num_features[0].I(); i++) 
        {
            HRegion feature;
            feature.SelectObj(features, i);
            
            HTuple feature_area, feature_row, feature_col;
            feature.AreaCenter(&feature_area, &feature_row, &feature_col);
            
            cout << "Feature " << i << ": area=" << feature_area[0].I() 
                 << ", position=(" << feature_row[0].D() << ", " << feature_col[0].D() << ")" << endl;
        }
        
        window.ClearWindow();
        window.DispImage(product_image);
        window.SetColor("blue");
        window.DispRegion(features);
        cout << "Features displayed" << endl;
        cin.get();
        
        // Step 4: Defect detection
        cout << "Step 4: Defect detection..." << endl;
        
        HRegionArray defects;
        defects.SelectShape(product_region, "area", "and", 10, 200, &defects);
        
        HTuple num_defects;
        num_defects = defects.CountObj();
        cout << "Found " << num_defects[0].I() << " potential defects" << endl;
        
        // Analyze defects
        for (int i = 1; i <= num_defects[0].I(); i++) 
        {
            HRegion defect;
            defect.SelectObj(defects, i);
            
            HTuple defect_area, defect_row, defect_col;
            defect.AreaCenter(&defect_area, &defect_row, &defect_col);
            
            HTuple defect_circularity;
            defect.Circularity(&defect_circularity);
            
            cout << "Defect " << i << ": area=" << defect_area[0].I() 
                 << ", position=(" << defect_row[0].D() << ", " << defect_col[0].D() << ")"
                 << ", circularity=" << defect_circularity[0].D() << endl;
        }
        
        window.ClearWindow();
        window.DispImage(product_image);
        window.SetColor("red");
        window.DispRegion(defects);
        cout << "Defects displayed" << endl;
        cin.get();
        
        // Step 5: Quality assessment
        cout << "Step 5: Quality assessment..." << endl;
        
        bool quality_pass = true;
        string quality_report = "Quality Assessment Report:\n";
        
        // Check product size
        if (product_area[0].I() < 8000 || product_area[0].I() > 15000) 
        {
            quality_pass = false;
            quality_report += "FAIL: Product size out of tolerance\n";
        }
        else 
        {
            quality_report += "PASS: Product size within tolerance\n";
        }
        
        // Check feature count
        if (num_features[0].I() < 2 || num_features[0].I() > 4) 
        {
            quality_pass = false;
            quality_report += "FAIL: Feature count out of range\n";
        }
        else 
        {
            quality_report += "PASS: Feature count within range\n";
        }
        
        // Check defects
        if (num_defects[0].I() > 0) 
        {
            quality_pass = false;
            quality_report += "FAIL: Defects detected\n";
        }
        else 
        {
            quality_report += "PASS: No defects detected\n";
        }
        
        cout << quality_report << endl;
        cout << "Overall quality: " << (quality_pass ? "PASS" : "FAIL") << endl;
        
        // Step 6: Metrology and measurement
        cout << "Step 6: Metrology and measurement..." << endl;
        
        // Create metrology model
        HTuple metrology_handle;
        CreateMetrologyModel(&metrology_handle);
        
        // Add measurement objects
        HTuple measure_handle;
        AddMetrologyObjectRectangle2(metrology_handle, product_row[0].D(), product_col[0].D(), 
                                   orientation[0].D(), major_axis[0].D()/2, minor_axis[0].D()/2, 
                                   HTuple(5), HTuple(5), HTuple(1), HTuple(30), HTuple(HTuple()), 
                                   HTuple(), &measure_handle);
        
        // Apply metrology
        ApplyMetrologyModel(product_image, metrology_handle);
        
        // Get measurement results
        HTuple measure_results;
        GetMetrologyObjectResult(metrology_handle, measure_handle, HTuple("all"), 
                               HTuple("result_type"), HTuple("all_param"), &measure_results);
        
        cout << "Metrology results: " << measure_results.Length() << " measurements" << endl;
        
        // Display final results
        window.ClearWindow();
        window.DispImage(product_image);
        window.SetColor("green");
        window.DispRegion(main_product);
        window.SetColor("blue");
        window.DispRegion(features);
        window.SetColor("red");
        window.DispRegion(defects);
        cout << "Final inspection results displayed" << endl;
        cin.get();
        
        // Clean up
        ClearMetrologyModel(metrology_handle);
        
        window.ClearWindow();
        cout << "Industrial vision system completed successfully!" << endl;
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
