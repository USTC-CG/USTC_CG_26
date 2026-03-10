#include <dlib/dnn.h>
#include <iostream>
#include <vector>
#include <dlib/statistics.h>

#include <string>

int main()
{
  std::vector<dlib::matrix<double>> src_vec_input, src_vec;
  std::vector<dlib::matrix<float>> dst_vec_input, dst_vec;
  dlib::matrix<float> output_means, output_stds;
  std::string data_path = "../data/training_set.txt";
  // Load training data from "data/training_set.txt"
  std::ifstream file(data_path);
  if (!file.is_open()) {
    std::cerr << "Error: Could not open file " << data_path << std::endl;
    return 1;
  }
  std::string line;
  while (std::getline(file, line)) {
    std::istringstream iss(line);
    dlib::matrix<double> src(2, 1);
    dlib::matrix<float> dst(2, 1);
    iss >> src(0) >> src(1) >> dst(0) >> dst(1);
    src_vec_input.push_back(src);
    dst_vec_input.push_back(dst);
    src_vec.push_back(src);
    dst_vec.push_back(dst);
  }
  file.close();
  
  // ========================== Data Processing (Normalization) ==========================
  dlib::vector_normalizer<dlib::matrix<double>> input_normalizer;
  dlib::vector_normalizer<dlib::matrix<float>> output_normalizer;
  input_normalizer.train(src_vec);
  for (auto& x : src_vec) x = input_normalizer(x);
  output_normalizer.train(dst_vec);
  output_means = output_normalizer.means();
  output_stds = output_normalizer.std_devs();
  for (auto& x : dst_vec) x = output_normalizer(x);
  // Print the data status: number, mean, and standard deviation
  std::cout << "Number of samples: " << src_vec.size() << std::endl;
  std::cout << "Output means: " << output_means << std::endl;
  std::cout << "Output stds: " << output_stds << std::endl;


  // ========================== Network architecture ==========================
  using network_type = dlib::loss_mean_squared_multioutput< // Loss function: mean squared error
    dlib::fc<2, // Full connection layer with 2 output neurons
    dlib::relu<dlib::fc<64, // Full connection layer with 64 neurons, followed by ReLU activation
    dlib::relu<dlib::fc<64, // Full connection layer with 64 neurons, followed by ReLU activation
    dlib::input<dlib::matrix<double>> // Input layer
    >>>>>>;
  // ========================== Train the network ==========================
  // Select the solver (e.g. ADAM, SGD)
  // 0.002 - weight_decay (Similar to L2 regularization adding to loss. Reduce overfitting)
  // 0.9, 0.999 - beta1, beta2 (ADAM hyperparameters)
  dlib::adam solver(0.002, 0.9, 0.999);
  // Initialize the trainer
  network_type net;
  dlib::dnn_trainer<network_type, dlib::adam> trainer(net, solver);
  // Training parameters
  trainer.set_learning_rate(0.001);
  trainer.set_min_learning_rate(1e-6);
  trainer.set_mini_batch_size(128);
  trainer.set_learning_rate_shrink_factor(0.1);
  trainer.set_iterations_without_progress_threshold(500);
  trainer.be_verbose();
  std::cout << "Starting training..." << std::endl;
  trainer.train(src_vec, dst_vec);


  // ========================== Evaluations ==========================
  // Test the pixels from [0, 0] to [255, 255]
  std::vector<dlib::matrix<double>> test_input;
  for (int i = 0; i < 256; i++) {
    for (int j = 0; j < 256; j++) {
      dlib::matrix<double> input(2, 1);
      input(0, 0) = j;
      input(1, 0) = i;
      test_input.push_back(input);
    }
  }
  for (auto& x : test_input) x = input_normalizer(x);
  std::vector<dlib::matrix<float>> test_output = net(test_input);
  for (auto& x : test_output) {
    x(0, 0) = x(0, 0) / output_stds(0, 0) + output_means(0, 0);
    x(1, 0) = x(1, 0) / output_stds(1, 0) + output_means(1, 0);
  }
  // Create file and save the output to "data/test_output.txt"
  std::ofstream output_file("../data/test_output.txt");
  if (!output_file.is_open()) {
    std::cerr << "Error: Could not open file " << "../data/test_output.txt" << std::endl;
    return 1;
  }
  for (int i = 0; i < 256; i++) {
    for (int j = 0; j < 256; j++) {
      output_file << j << " " << i << " " << test_output[i * 256 + j](0, 0) << " " << test_output[i * 256 + j](1, 0) << std::endl;
    }
  }
  // Compare the predicted dst_point and ground truth for training data
  // Print: The point (x, y) \t should be mapped to (x', y'), \t fitting result: (x'', y'')
  for (int i = 0; i < src_vec.size(); i++) {
    dlib::matrix<float> dst_point = net(src_vec[i]);
    dst_point(0, 0) = dst_point(0, 0) / output_stds(0, 0) + output_means(0, 0);
    dst_point(1, 0) = dst_point(1, 0) / output_stds(1, 0) + output_means(1, 0);
    std::cout << "The point (" << src_vec_input[i](0, 0) << ", " << src_vec_input[i](1, 0) 
      << ") \t should be mapped to (" << dst_vec_input[i](0, 0) << ", " << dst_vec_input[i](1, 0) 
      << "), \t fitting result: (" << dst_point(0, 0) << ", " << dst_point(1, 0) << ")" 
      << std::endl;
  }
}