/*
 * Halcon Advanced Program 2: Machine Learning and Classification
 * 
 * This program demonstrates:
 * - Feature extraction for classification
 * - Support Vector Machine (SVM) training
 * - Neural network classification
 * - Model evaluation and testing
 * 
 * Prerequisites: 
 * - Halcon license file
 * 
 * Compilation: g++ -o halcon_advanced_02 halcon_advanced_02.cpp -lhalcon
 */

#include <iostream>
#include <HalconCpp.h>

using namespace HalconCpp;
using namespace std;

int main()
{
    try 
    {
        cout << "=== Halcon Advanced Program 2: Machine Learning and Classification ===" << endl;
        
        HWindow window(0, 0, 800, 600, 0, "visible", "");
        window.SetWindowParam("background_color", "black");
        
        // Create training data
        cout << "Creating training data..." << endl;
        
        HTuple class_train_data_id;
        CreateClassTrainData("image", &class_train_data_id);
        
        // Generate synthetic training images
        for (int class_id = 0; class_id < 3; class_id++) 
        {
            for (int sample = 0; sample < 10; sample++) 
            {
                HImage train_image;
                train_image.GenImageConst("byte", 100, 100);
                
                HImage pattern;
                pattern.GenImageConst("byte", 100, 100);
                pattern.PaintRegion(HRectangle2(0, 0, 0, 100, 100), 50);
                
                // Create different patterns for each class
                if (class_id == 0) 
                {
                    // Class 0: Circles
                    pattern.PaintRegion(HCircle(50, 50, 30), 200);
                }
                else if (class_id == 1) 
                {
                    // Class 1: Rectangles
                    pattern.PaintRegion(HRectangle2(35, 35, 0, 30, 30), 200);
                }
                else 
                {
                    // Class 2: Triangles (approximated)
                    pattern.PaintRegion(HRectangle2(40, 40, 0, 20, 20), 200);
                }
                
                train_image = pattern;
                
                // Add to training data
                AddClassTrainDataImage(train_image, class_train_data_id, class_id, 
                                     HTuple(), HTuple());
            }
        }
        
        cout << "Training data created" << endl;
        
        // Train SVM classifier
        cout << "Training SVM classifier..." << endl;
        
        HTuple svm_handle;
        CreateClassSvm(class_train_data_id, HTuple("rbf"), HTuple(0.01), 
                      HTuple(1.0), HTuple(0.001), HTuple("one-versus-one"), 
                      HTuple("normalization"), HTuple("true"), &svm_handle);
        
        TrainClassSvm(svm_handle, HTuple(0.001), HTuple("default"));
        
        cout << "SVM training completed" << endl;
        
        // Train Neural Network classifier
        cout << "Training Neural Network classifier..." << endl;
        
        HTuple nn_handle;
        CreateClassMlp(class_train_data_id, HTuple("false"), HTuple(10), 
                       HTuple("softmax"), HTuple("normalization"), HTuple("true"), 
                       &nn_handle);
        
        TrainClassMlp(nn_handle, HTuple(0.01), HTuple(1), HTuple(0.01), 
                     HTuple(100), HTuple("default"));
        
        cout << "Neural Network training completed" << endl;
        
        // Test classification
        cout << "Testing classification..." << endl;
        
        // Create test images
        HImage test_image;
        test_image.GenImageConst("byte", 100, 100);
        
        HImage test_pattern;
        test_pattern.GenImageConst("byte", 100, 100);
        test_pattern.PaintRegion(HRectangle2(0, 0, 0, 100, 100), 50);
        test_pattern.PaintRegion(HCircle(50, 50, 25), 200);  // Circle test
        
        test_image = test_pattern;
        
        window.DispImage(test_image);
        cout << "Test image displayed" << endl;
        cin.get();
        
        // Classify with SVM
        HTuple svm_class, svm_confidence;
        ClassifyImageClassSvm(test_image, svm_handle, &svm_class, &svm_confidence);
        
        cout << "SVM Classification:" << endl;
        cout << "Class: " << svm_class[0].I() << endl;
        cout << "Confidence: " << svm_confidence[0].D() << endl;
        
        // Classify with Neural Network
        HTuple nn_class, nn_confidence;
        ClassifyImageClassMlp(test_image, nn_handle, &nn_class, &nn_confidence);
        
        cout << "Neural Network Classification:" << endl;
        cout << "Class: " << nn_class[0].I() << endl;
        cout << "Confidence: " << nn_confidence[0].D() << endl;
        
        // Test with different patterns
        cout << "Testing with rectangle pattern..." << endl;
        
        HImage test_rect;
        test_rect.GenImageConst("byte", 100, 100);
        
        HImage rect_pattern;
        rect_pattern.GenImageConst("byte", 100, 100);
        rect_pattern.PaintRegion(HRectangle2(0, 0, 0, 100, 100), 50);
        rect_pattern.PaintRegion(HRectangle2(35, 35, 0, 30, 30), 200);
        
        test_rect = rect_pattern;
        
        window.ClearWindow();
        window.DispImage(test_rect);
        cout << "Rectangle test image displayed" << endl;
        cin.get();
        
        // Classify rectangle
        ClassifyImageClassSvm(test_rect, svm_handle, &svm_class, &svm_confidence);
        ClassifyImageClassMlp(test_rect, nn_handle, &nn_class, &nn_confidence);
        
        cout << "Rectangle Classification:" << endl;
        cout << "SVM - Class: " << svm_class[0].I() << ", Confidence: " << svm_confidence[0].D() << endl;
        cout << "NN - Class: " << nn_class[0].I() << ", Confidence: " << nn_confidence[0].D() << endl;
        
        // Clean up
        ClearClassSvm(svm_handle);
        ClearClassMlp(nn_handle);
        ClearClassTrainData(class_train_data_id);
        
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
