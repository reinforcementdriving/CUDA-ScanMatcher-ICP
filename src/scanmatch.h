#pragma once

#include <stdio.h>
#include <chrono>
#include <thrust/sort.h>
#include <thrust/execution_policy.h>
#include <thrust/random.h>
#include <thrust/device_vector.h>
#include <cuda.h>
#include <cmath>
#include <vector>
#include "pointcloud.h"
#include "utilityCore.hpp"
#include "octree.h"

namespace ScanMatch {
    void copyPointCloudToVBO(float *vbodptr_positions, float *vbodptr_rgb, bool usecpu);
    void endSimulation();
    void unitTest();

	//CPU SCANMATCHING
    void initSimulationCPU(int N, std::vector<glm::vec3> coords);
	void stepICPCPU();
	void findNNCPU(pointcloud* src, pointcloud* target, float* dist, int* indicies, int N);
	void reshuffleCPU(pointcloud* a, int* indicies, int N);
	void bestFitTransform(pointcloud* src, pointcloud* target, int N, glm::mat3 &R, glm::vec3 &t);

	//GPU_NAIVE SCANMATCHING
    void initSimulationGPU(int N, std::vector<glm::vec3> coords);
	void stepICPGPU_NAIVE();
	void findNNGPU_NAIVE(pointcloud* src, pointcloud* target, float* dist, int* indicies, int N);
	void reshuffleGPU(pointcloud* a, int* indicies, int N);
	void bestFitTransformGPU(pointcloud* src, pointcloud* target, int N, glm::mat3 &R, glm::vec3 &t);

	//GPU OCTREE SCANMATCHING
    void initSimulationGPUOCTREE(int N, std::vector<glm::vec3> coords);
	void stepICPGPU_OCTREE();
	void findNNGPU_OCTREE(pointcloud* src, pointcloud* target, float* dist, int* indicies, int N, OctNodeGPU* octoNodes);
} 