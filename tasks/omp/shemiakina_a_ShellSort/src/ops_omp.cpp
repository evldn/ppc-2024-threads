// Copyright 2024 Shemiakina Alesya
#include "omp/shemiakina_a_ShellSort/include/ops_omp.hpp"

#include <thread>

using namespace std::chrono_literals;

bool ShellTaskOMP::pre_processing() {
  internal_order_test();
  // Init value for input and output
  for (int i = 0; i < static_cast<int>(taskData->inputs_count[0]); i++) {
    input_.push_back(reinterpret_cast<int*>(taskData->inputs[0])[i]);
  }
  return true;
}

bool ShellTaskOMP::validation() {
  internal_order_test();
  // Check count elements of output
  return taskData->inputs_count.size() == 1 && taskData->inputs_count[0] > 0 && taskData->outputs_count.size() == 1 &&
         taskData->inputs_count[0] == taskData->outputs_count[0];
}

bool ShellTaskOMP::run() {
  internal_order_test();
  ShellSort_Parallel(input_);
  return true;
}

bool ShellTaskOMP::post_processing() {
  internal_order_test();
  for (int i = 0; i < static_cast<int>(taskData->inputs_count[0]); i++) {
    reinterpret_cast<int*>(taskData->outputs[0])[i] = input_[i];
  }
  return true;
}

std::vector<int> ShellTaskOMP::merge(const std::vector<std::vector<int>>& chunks) {
  std::vector<int> res;

  // Merge the sorted chunks
  for (const auto& chunk : chunks) {
    // Merge the current chunk with the result vector
    std::vector<int> merged;
    merged.reserve(res.size() + chunk.size());
    auto resIter = res.begin();
    auto chunkIter = chunk.begin();

    while (resIter != res.end() && chunkIter != chunk.end()) {
      if (*resIter < *chunkIter) {
        merged.push_back(*resIter);
        ++resIter;
      } else {
        merged.push_back(*chunkIter);
        ++chunkIter;
      }
    }

    // Copy remaining elements from result vector
    while (resIter != res.end()) {
      merged.push_back(*resIter);
      ++resIter;
    }

    // Copy remaining elements from current chunk
    while (chunkIter != chunk.end()) {
      merged.push_back(*chunkIter);
      ++chunkIter;
    }

    // Update result vector with merged vector
    res = std::move(merged);
  }

  return res;
}

void ShellTaskOMP::ShellSort_Parallel(std::vector<int>& input) {
  int numProcs = omp_get_num_procs();
  int size = static_cast<int>(input.size());
  int chunkSize = size / numProcs;
  int remainder = size % numProcs;

  std::vector<std::vector<int>> chunks(numProcs);

#pragma omp parallel for
  for (int i = 0; i < numProcs; ++i) {
    int startIdx = i * chunkSize;
    int endIdx = startIdx + chunkSize;
    if (i == numProcs - 1) {
      endIdx += remainder;  // Add remaining elements to the last chunk
    }
    chunks[i].assign(input.begin() + startIdx, input.begin() + endIdx);
    ShellSort(chunks[i]);
  }

#pragma omp barrier

  input = merge(chunks);
}

std::vector<int> ShellTaskOMP::ShellSort(const std::vector<int>& input) {
  std::vector<int> vec(input);

  for (int interval = static_cast<int>(vec.size()) / 2; interval > 0; interval /= 2) {
    for (int i = interval; i < static_cast<int>(vec.size()); i++) {
      int tmp = vec[i];
      int j = i;
      for (; j >= interval && vec[j - interval] > tmp; j = j - interval) {
        vec[j] = vec[j - interval];
      }
      vec[j] = tmp;
    }
  }

  return vec;
}

bool ShellTaskOMP::CheckSort(std::vector<int> input) { return std::is_sorted(input.begin(), input.end()); }

std::vector<int> ShellTaskOMP::give_random_vector(int size, int min, int max) {
  std::random_device rnd_device;
  std::mt19937 mersenne_engine{rnd_device()};
  std::uniform_int_distribution<int> dist{min, max};

  auto gen = [&dist, &mersenne_engine]() { return dist(mersenne_engine); };

  std::vector<int> vec(size);
  generate(begin(vec), end(vec), gen);

  return vec;
}
