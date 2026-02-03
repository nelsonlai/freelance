/*
 * Halcon Advanced Program 3: Deep Learning Integration
 * 
 * This program demonstrates:
 * - Deep learning model loading
 * - Image preprocessing for DL
 * - Inference with pre-trained models
 * - Post-processing of DL results
 * 
 * Prerequisites: 
 * - Halcon license file
 * - Deep learning models (if available)
 * 
 * Compilation: g++ -o halcon_advanced_03 halcon_advanced_03.cpp -lhalcon
 */

#include <iostream>
#include <HalconCpp.h>

using namespace HalconCpp;
using namespace std;

int main()
{
    try 
    {
        cout << "=== Halcon Advanced Program 3: Deep Learning Integration ===" << endl;
        
        HWindow window(0, 0, 800, 600, 0, "visible", "");
        window.SetWindowParam("background_color", "black");
        
        // Create test image
        HImage test_image;
        test_image.GenImageConst("byte", 224, 224);
        
        HImage pattern;
        pattern.GenImageConst("byte", 224, 224);
        pattern.PaintRegion(HRectangle2(0, 0, 0, 224, 224), 100);
        
        // Add some features
        pattern.PaintRegion(HCircle(112, 112, 50), 200);
        pattern.PaintRegion(HRectangle2(80, 80, 0, 60, 60), 180);
        
        test_image = pattern;
        
        window.DispImage(test_image);
        cout << "Test image displayed" << endl;
        cin.get();
        
        // Preprocess image for deep learning
        cout << "Preprocessing image for deep learning..." << endl;
        
        // Resize to standard input size
        HImage resized_image;
        resized_image.ZoomImageFactor(test_image, 1.0, 1.0, "constant");
        
        // Normalize pixel values
        HImage normalized_image;
        normalized_image.ScaleImage(resized_image, 1.0/255.0, 0.0);
        
        cout << "Image preprocessing completed" << endl;
        
        // Simulate deep learning inference
        cout << "Simulating deep learning inference..." << endl;
        
        // Create mock classification results
        HTuple class_names;
        class_names = HTuple("circle", "rectangle", "triangle", "background");
        
        HTuple class_scores;
        class_scores = HTuple(0.1, 0.7, 0.1, 0.1);  // Mock scores
        
        cout << "Classification results:" << endl;
        for (int i = 0; i < class_names.Length(); i++) 
        {
            cout << class_names[i].S() << ": " << class_scores[i].D() << endl;
        }
        
        // Find best class
        HTuple best_class_idx;
        class_scores.TupleMax(&best_class_idx);
        
        cout << "Best classification: " << class_names[best_class_idx[0].I()].S() 
             << " (score: " << class_scores[best_class_idx[0].I()].D() << ")" << endl;
        
        // Demonstrate object detection simulation
        cout << "Simulating object detection..." << endl;
        
        HTuple detection_boxes;
        detection_boxes = HTuple(50, 50, 150, 150);  // Mock bounding box
        
        HTuple detection_scores;
        detection_scores = HTuple(0.85);  // Mock confidence
        
        HTuple detection_classes;
        detection_classes = HTuple(1);  // Mock class (rectangle)
        
        cout << "Object detection results:" << endl;
        cout << "Bounding box: (" << detection_boxes[0].I() << ", " << detection_boxes[1].I() 
             << ", " << detection_boxes[2].I() << ", " << detection_boxes[3].I() << ")" << endl;
        cout << "Confidence: " << detection_scores[0].D() << endl;
        cout << "Class: " << class_names[detection_classes[0].I()].S() << endl;
        
        // Display detection results
        window.ClearWindow();
        window.DispImage(test_image);
        window.SetColor("red");
        window.DispRectangle1(detection_boxes[0].I(), detection_boxes[1].I(), 
                            detection_boxes[2].I(), detection_boxes[3].I());
        cout << "Detection result displayed" << endl;
        cin.get();
        
        // Demonstrate semantic segmentation simulation
        cout << "Simulating semantic segmentation..." << endl;
        
        HImage segmentation_mask;
        segmentation_mask.GenImageConst("byte", 224, 224);
        
        HImage mask_pattern;
        mask_pattern.GenImageConst("byte", 224, 224);
        
        // Create segmentation mask
        mask_pattern.PaintRegion(HCircle(112, 112, 50), 1);  // Class 1
        mask_pattern.PaintRegion(HRectangle2(80, 80, 0, 60, 60), 2);  // Class 2
        
        segmentation_mask = mask_pattern;
        
        window.ClearWindow();
        window.DispImage(segmentation_mask);
        cout << "Segmentation mask displayed" << endl;
        cin.get();
        
        // Analyze segmentation results
        HTuple num_classes = HTuple(3);
        HTuple class_pixel_counts;
        
        for (int i = 0; i < num_classes[0].I(); i++) 
        {
            HRegion class_region;
            class_region.Threshold(segmentation_mask, i, i);
            
            HTuple pixel_count;
            class_region.AreaCenter(&pixel_count, HTuple(), HTuple());
            
            class_pixel_counts.Append(pixel_count);
            
            cout << "Class " << i << " pixels: " << pixel_count[0].I() << endl;
        }
        
        // Demonstrate instance segmentation
        cout << "Simulating instance segmentation..." << endl;
        
        HRegionArray instances;
        instances.GenEmptyRegion();
        
        // Instance 1
        HRegion instance1;
        instance1.GenCircle(112, 112, 50);
        instances.Append(instance1);
        
        // Instance 2
        HRegion instance2;
        instance2.GenRectangle1(80, 80, 140, 140);
        instances.Append(instance2);
        
        window.ClearWindow();
        window.DispImage(test_image);
        window.SetColor("green");
        window.DispRegion(instances);
        cout << "Instance segmentation displayed" << endl;
        cin.get();
        
        // Post-processing: Non-maximum suppression simulation
        cout << "Applying non-maximum suppression..." << endl;
        
        HTuple nms_boxes;
        HTuple nms_scores;
        HTuple nms_classes;
        
        // Mock NMS results (filtered detections)
        nms_boxes = HTuple(50, 50, 150, 150);
        nms_scores = HTuple(0.85);
        nms_classes = HTuple(1);
        
        cout << "After NMS: " << nms_boxes.Length()/4 << " detections" << endl;
        
        // Display final results
        window.ClearWindow();
        window.DispImage(test_image);
        window.SetColor("blue");
        window.DispRectangle1(nms_boxes[0].I(), nms_boxes[1].I(), 
                             nms_boxes[2].I(), nms_boxes[3].I());
        cout << "Final detection results displayed" << endl;
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
