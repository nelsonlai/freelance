/*
 * Halcon Advanced Program 5: Real-time Processing Pipeline
 * 
 * This program demonstrates:
 * - Real-time image processing pipeline
 * - Multi-threaded processing
 * - Performance optimization
 * - Pipeline monitoring and control
 * 
 * Prerequisites: 
 * - Halcon license file
 * 
 * Compilation: g++ -o halcon_advanced_05 halcon_advanced_05.cpp -lhalcon -pthread
 */

#include <iostream>
#include <HalconCpp.h>
#include <chrono>
#include <thread>

using namespace HalconCpp;
using namespace std;

int main()
{
    try 
    {
        cout << "=== Halcon Advanced Program 5: Real-time Processing Pipeline ===" << endl;
        
        HWindow window(0, 0, 800, 600, 0, "visible", "");
        window.SetWindowParam("background_color", "black");
        
        // Pipeline configuration
        const int PIPELINE_STAGES = 4;
        const int PROCESSING_TIME_MS = 100;  // Simulate processing time
        
        cout << "Initializing real-time processing pipeline..." << endl;
        
        // Create processing pipeline stages
        auto start_time = chrono::high_resolution_clock::now();
        
        for (int frame = 0; frame < 10; frame++) 
        {
            cout << "Processing frame " << frame + 1 << "..." << endl;
            
            // Stage 1: Image acquisition simulation
            auto stage1_start = chrono::high_resolution_clock::now();
            
            HImage input_image;
            input_image.GenImageConst("byte", 640, 480);
            
            HImage pattern;
            pattern.GenImageConst("byte", 640, 480);
            pattern.PaintRegion(HRectangle2(0, 0, 0, 480, 640), 50);
            
            // Add moving features
            int offset = frame * 10;
            pattern.PaintRegion(HCircle(240 + offset, 320 + offset, 30), 200);
            pattern.PaintRegion(HRectangle2(200 + offset, 300 + offset, 0, 40, 40), 180);
            
            input_image = pattern;
            
            auto stage1_end = chrono::high_resolution_clock::now();
            auto stage1_duration = chrono::duration_cast<chrono::microseconds>(stage1_end - stage1_start);
            
            // Stage 2: Preprocessing
            auto stage2_start = chrono::high_resolution_clock::now();
            
            HImage preprocessed;
            preprocessed.GaussImage(input_image, 1.0);
            
            auto stage2_end = chrono::high_resolution_clock::now();
            auto stage2_duration = chrono::duration_cast<chrono::microseconds>(stage2_end - stage2_start);
            
            // Stage 3: Feature detection
            auto stage3_start = chrono::high_resolution_clock::now();
            
            HRegion features;
            features.BinaryThreshold(preprocessed, "max_separability", "light", &features);
            
            auto stage3_end = chrono::high_resolution_clock::now();
            auto stage3_duration = chrono::duration_cast<chrono::microseconds>(stage3_end - stage3_start);
            
            // Stage 4: Analysis and output
            auto stage4_start = chrono::high_resolution_clock::now();
            
            HTuple num_features;
            num_features = features.CountObj();
            
            HTuple area, row_center, col_center;
            features.AreaCenter(&area, &row_center, &col_center);
            
            auto stage4_end = chrono::high_resolution_clock::now();
            auto stage4_duration = chrono::duration_cast<chrono::microseconds>(stage4_end - stage4_start);
            
            // Display results
            window.ClearWindow();
            window.DispImage(input_image);
            window.SetColor("red");
            window.DispRegion(features);
            
            // Performance monitoring
            auto total_duration = stage1_duration + stage2_duration + stage3_duration + stage4_duration;
            
            cout << "Frame " << frame + 1 << " results:" << endl;
            cout << "  Features detected: " << num_features[0].I() << endl;
            cout << "  Processing time: " << total_duration.count() << " μs" << endl;
            cout << "  Stage times: " << stage1_duration.count() << " / " 
                 << stage2_duration.count() << " / " << stage3_duration.count() 
                 << " / " << stage4_duration.count() << " μs" << endl;
            
            // Simulate real-time constraints
            this_thread::sleep_for(chrono::milliseconds(50));
            
            if (frame % 3 == 0) 
            {
                cout << "Press Enter to continue..." << endl;
                cin.get();
            }
        }
        
        // Pipeline performance analysis
        auto end_time = chrono::high_resolution_clock::now();
        auto total_time = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
        
        cout << "Pipeline performance analysis:" << endl;
        cout << "Total processing time: " << total_time.count() << " ms" << endl;
        cout << "Average frame time: " << total_time.count() / 10 << " ms" << endl;
        cout << "Estimated FPS: " << 1000.0 / (total_time.count() / 10.0) << endl;
        
        // Demonstrate parallel processing simulation
        cout << "Demonstrating parallel processing..." << endl;
        
        // Simulate multi-threaded processing
        vector<thread> processing_threads;
        vector<HImage> results(3);
        
        for (int i = 0; i < 3; i++) 
        {
            processing_threads.emplace_back([i, &results]() 
            {
                // Simulate different processing tasks
                HImage thread_image;
                thread_image.GenImageConst("byte", 200, 200);
                
                HImage pattern;
                pattern.GenImageConst("byte", 200, 200);
                pattern.PaintRegion(HRectangle2(0, 0, 0, 200, 200), 50);
                pattern.PaintRegion(HCircle(100, 100, 30 + i*10), 200);
                
                thread_image = pattern;
                
                // Simulate processing
                this_thread::sleep_for(chrono::milliseconds(100 + i*50));
                
                results[i] = thread_image;
            });
        }
        
        // Wait for all threads to complete
        for (auto& thread : processing_threads) 
        {
            thread.join();
        }
        
        cout << "Parallel processing completed" << endl;
        
        // Display parallel processing results
        for (int i = 0; i < 3; i++) 
        {
            window.ClearWindow();
            window.DispImage(results[i]);
            cout << "Parallel result " << i + 1 << " displayed" << endl;
            cin.get();
        }
        
        // Memory and resource monitoring
        cout << "Resource monitoring:" << endl;
        
        HTuple memory_info;
        memory_info.GetSystemInfo("memory", &memory_info);
        cout << "Memory usage: " << memory_info[0].I() << " MB" << endl;
        
        HTuple cpu_info;
        cpu_info.GetSystemInfo("cpu", &cpu_info);
        cout << "CPU usage: " << cpu_info[0].D() << "%" << endl;
        
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
