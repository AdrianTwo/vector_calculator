#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

std::vector<std::string> split_string(const std::string& s, char delim) {
    std::string string_token;
    std::vector<std::string> string_vector;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == delim) {
            string_vector.push_back(string_token);
            string_token = "";
        } else {
            string_token += s[i];
        }
    }
    string_vector.push_back(string_token);
    
    return string_vector;
}

std::vector<double> convert_string_vector_to_double_vector(const std::vector<std::string>& string_vector) {
    std::vector<double> double_vector(string_vector.size());
    try { 
        std::transform(string_vector.begin(), string_vector.end(), double_vector.begin(), [](const std::string& val) {
            return stod(val);
        });
    } catch (const std::invalid_argument& ia) {
        // When a invalid element is in the vector it gets catched, and the 'converted' vector is set to one with only one element, 
        // so the vector is too short for the calculations and does not get used
        double_vector = { 0 };
    }
    return double_vector;
}

std::vector<double> calculate_sum(const std::vector<double>& mathematical_vector_1, const std::vector<double>& mathematical_vector_2) {
    std::vector<double> result_mathematical_vector;
    
    for (std::size_t i = 0; i < mathematical_vector_1.size(); i++) {
        result_mathematical_vector.push_back(mathematical_vector_1[i] + mathematical_vector_2[i]);
    }
    
    return result_mathematical_vector;
}

std::vector<double> calculate_difference(const std::vector<double>& mathematical_vector_1, const std::vector<double>& mathematical_vector_2) {
    std::vector<double> result_mathematical_vector;
    
    for (std::size_t i = 0; i < mathematical_vector_1.size(); i++) {
        result_mathematical_vector.push_back(mathematical_vector_1[i] - mathematical_vector_2[i]);
    }
    
    return result_mathematical_vector;
}

std::vector<double> calculate_scalar_product(const std::vector<double>& mathematical_vector_1, const std::vector<double>& mathematical_vector_2) {
    std::vector<double> result_mathematical_vector;
    
    for (std::size_t i = 0; i < mathematical_vector_1.size(); i++) {
        result_mathematical_vector.push_back(mathematical_vector_1[i] * mathematical_vector_2[i]);
    }
    
    return result_mathematical_vector;
}

std::vector<double> calculate_cross_product(const std::vector<double>& mathematical_vector_1, const std::vector<double>& mathematical_vector_2) {
    std::vector<double> result_mathematical_vector;
    
    result_mathematical_vector.push_back(mathematical_vector_1[1] * mathematical_vector_2[2] - mathematical_vector_1[2] * mathematical_vector_2[1]);
    result_mathematical_vector.push_back(mathematical_vector_1[2] * mathematical_vector_2[0] - mathematical_vector_1[0] * mathematical_vector_2[2]);
    result_mathematical_vector.push_back(mathematical_vector_1[0] * mathematical_vector_2[1] - mathematical_vector_1[1] * mathematical_vector_2[0]);
    
    return result_mathematical_vector;
}

std::string display_mathematical_vector(const std::vector<double>& v) {
    std::string result_string = "(";
    
    // Handle every element in the mathematical_vector, but the last
    for (std::size_t i = 0; i < v.size() - 1; i++) {
        result_string += std::to_string(v[i]) + ", ";
    }
    // Handle last element in the mathematical vector
    result_string += std::to_string(v[v.size() - 1]) + ")";
    
    return result_string;
}

void display_results(const std::vector<double>& mathematical_vector_1, const std::vector<double>& mathematical_vector_2) {
    std::vector<double> mathematical_vector_sum = calculate_sum(mathematical_vector_1, mathematical_vector_2);
    std::vector<double> mathematical_vector_difference = calculate_difference(mathematical_vector_1, mathematical_vector_2);
    std::vector<double> mathematical_vector_scalar_product = calculate_scalar_product(mathematical_vector_1, mathematical_vector_2);
    std::vector<double> mathematical_vector_cross_product;
    
    
    // Check if mathematical vector is 2- or 3-dimensional, because only 3-dimensional vectors have a cross product
    if (mathematical_vector_1.size() == 3) {
        mathematical_vector_cross_product = calculate_cross_product(mathematical_vector_1, mathematical_vector_2);
        
        std::cout << "Sum: " << display_mathematical_vector(mathematical_vector_sum) << std::endl;
        std::cout << "Difference: " << display_mathematical_vector(mathematical_vector_difference) << std::endl;
        std::cout << "Scalar product: " << display_mathematical_vector(mathematical_vector_scalar_product) << std::endl;
        std::cout << "Cross product: " << display_mathematical_vector(mathematical_vector_cross_product) << std::endl;
    } else if (mathematical_vector_1.size() == 2) {
        std::cout << "Sum: " << display_mathematical_vector(mathematical_vector_sum) << std::endl;
        std::cout << "Difference: " << display_mathematical_vector(mathematical_vector_difference) << std::endl;
        std::cout << "Scalar product: " << display_mathematical_vector(mathematical_vector_scalar_product) << std::endl;
    }
}

std::vector<std::vector<double>> get_mathematical_vectors() {
    std::vector<std::vector<double>> mathematical_vectors;
    
    std::string mathematical_vector_string_1;
    std::string mathematical_vector_string_2;
    
    std::vector<double> mathematical_vector_1;
    std::vector<double> mathematical_vector_2;
    
    while (true) {
        std::cout << "Enter the first mathematical vector with each number seperated by a comma (','): ";
        std::cin >> mathematical_vector_string_1;
        mathematical_vector_1 = convert_string_vector_to_double_vector(split_string(mathematical_vector_string_1, ','));
        
        if ((mathematical_vector_1.size() > 3) || (mathematical_vector_1.size() < 2)) {
            std::cout << "[ERROR] The mathematical vector has an invalid length or contains invalid numbers!" << std::endl;
            continue;
        }
        
        std::cout << "Enter the second mathematical vector with each number seperated by a comma (','): ";
        std::cin >> mathematical_vector_string_2;
        mathematical_vector_2 = convert_string_vector_to_double_vector(split_string(mathematical_vector_string_2, ','));
        
        if ((mathematical_vector_2.size() > 3) || (mathematical_vector_2.size() < 2)) {
            std::cout << "[ERROR] The mathematical vector has an invalid length or contains invalid numbers!" << std::endl;
            continue;
        } else if (mathematical_vector_2.size() != mathematical_vector_1.size()) {
            std::cout << "[ERROR] The mathematical vector has not the same dimensions as the first!" << std::endl;
            continue;
        }
        
        mathematical_vectors.push_back(mathematical_vector_1);
        mathematical_vectors.push_back(mathematical_vector_2);
        
        break;
    }
    
    return mathematical_vectors;
}

int main() {
    std::cout << "Welcome! This program supports 2D and 3D vectors!" << std::endl;
    std::vector<std::vector<double>> mathematical_vectors = get_mathematical_vectors();
    display_results(mathematical_vectors[0], mathematical_vectors[1]);
    
    return 0;
}
