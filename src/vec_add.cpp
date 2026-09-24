#include<iostream>
#include<vector>
#include<chrono>

#define VEC_SIZE 100000000

int main(){
    std::vector<double> A(VEC_SIZE);
    std::vector<double> B(VEC_SIZE);
    std::vector<double> C(VEC_SIZE);

    //initialization
    for(int i = 0; i < VEC_SIZE; i++) {A[i] = i; B[i] = 1.0;}

    //vector addition
    auto start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < VEC_SIZE; i++){
        C[i] = A[i] + B[i];
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto duration_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    auto duration_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    std::cout << "Single Core Execution time: " << duration_us.count() << " microseconds" << std::endl;
    std::cout << "GFlop/s: " << VEC_SIZE / (double)duration_ns.count() << std::endl;

    start = std::chrono::high_resolution_clock::now();
    #pragma omp parallel for
    for(int i = 0; i < VEC_SIZE; i++){
        C[i] = A[i] + B[i];
    }
    end = std::chrono::high_resolution_clock::now();

    duration_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    duration_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    std::cout << "Multi Core Execution time: " << duration_us.count() << " microseconds" << std::endl;
    std::cout << "GFlop/s: " << VEC_SIZE / (double)duration_ns.count() << std::endl;

    return 0;
}
