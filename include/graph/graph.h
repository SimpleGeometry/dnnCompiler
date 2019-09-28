// Copyright 2018 The AITS DNNC Authors.All Rights Reserved.
//
// Licensed to the Apache Software Foundation(ASF) under one
// or more contributor license agreements.See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.See the License for the
// specific language governing permissionsand limitations
// under the License.
//
// This file is part of AITS DNN compiler maintained at
// https://github.com/ai-techsystems/dnnCompiler
//
#pragma once

#include <graph/node.h>
#include <set>

namespace dnnc {
typedef std::tuple<std::string, DNNC_DataType, std::vector<dnnc::DIMENSION>>
    variable;

/*!< This is a directed graph representing data flow graph
 * for deep neural networks. Default graph is singleton by design, 
 * and light by construction. Default graph lives throughout the 
 * life of program and dies with it.
 *
 * One can create subgraphs pointers owned by default graph.
 */
class graph {
protected:
  std::string _name = "";
  std::vector<node> _nodes;
  std::vector<variable> _inputs;
  std::vector<variable> _outputs;
  std::vector<nodeAttribute> _initializers;

  std::vector<graph*>   _subgraphs;

  // prohibited methods for singleton instance
  graph() {}
  // graph(const graph &other) = delete;
  // graph &operator=(const graph &other) = delete;

public:
  static graph &singleton() {
    static graph
        _graph; /*!< only one graph can be created, (singleton by design) */
    return _graph;
  }
  graph* subgraph() {
      graph* sg = new graph() ; 
      _subgraphs.push_back(sg) ;
      return sg;
  }
  ~graph() {
      for (auto& sg : _subgraphs)
          delete sg;
  }
  void setName(std::string name) { _name = name; }
  void addNode(node n) { _nodes.push_back(n); }
};
static graph &Graph() { return graph::singleton(); }
} // namespace dnnc
