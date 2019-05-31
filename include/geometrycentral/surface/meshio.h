#pragma once

// The MeshIO class provides a variety of methods for mesh input/output.

#include "geometrycentral/surface/geometry.h"

#include <fstream>
#include <string>

namespace geometrycentral {
namespace surface {

// Loads a halfedge mesh and its geometry from file.
// Specify a type like "ply" or "obj", if no type is specified, attempts to infer from extension.
std::tuple<std::unique_ptr<HalfedgeMesh>, std::unique_ptr<Geometry<Euclidean>>>
loadMesh(std::string filename, bool verbose = false, std::string type = "");

// Load just the connectivity of a mesh from file.
// Specify a type like "ply" or "obj", if no type is specified, attempts to infer from extension.
std::unique_ptr<HalfedgeMesh> loadConnectivity(std::string filename, bool verbose = false, std::string type = "");

class WavefrontOBJ {
public:
  static bool write(std::string filename, Geometry<Euclidean>& geometry);
  static bool write(std::string filename, Geometry<Euclidean>& geometry, CornerData<Vector2>& texcoords);

protected:
  static bool openStream(std::ofstream& out, std::string filename);
  static void writeHeader(std::ofstream& out, Geometry<Euclidean>& geometry);
  static void writeVertices(std::ofstream& out, Geometry<Euclidean>& geometry);
  static void writeTexCoords(std::ofstream& out, Geometry<Euclidean>& geometry, CornerData<Vector2>& texcoords);
  static void writeFaces(std::ofstream& out, Geometry<Euclidean>& geometry, bool useTexCoords = false);
};


// TODO write halfedge mesh as a permutation, in binary format (for quicker loading/smaller files)

} // namespace surface
} // namespace geometrycentral