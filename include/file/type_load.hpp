#ifndef DATA_TYPE_HPP_FILE
#define DATA_TYPE_HPP_FILE
#include <cstddef>
#include <cstdlib>
#include <cstdint>
#include <utility>
#include <exception>

#include <cmath>

#include <fstream>
#include <iostream>

#include <vector>
#include <map>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

using std::cout;
using std::endl;
using std::cerr;
using std::forward;
using std::move;
using std::cout;
using std::vector;
using std::map;
using std::pair;
using std::fstream;
using std::ofstream;
using std::ifstream;
using std::string;
//math  part
using std::abs;
using std::ceil;
using std::floor;
using std::cos;
using std::sin;
using std::tan;
using std::cosh;
using std::sinh;
using std::tanh;
using std::acos;
using std::asin;
using std::atan;
using std::acosh;
using std::asinh;
using std::atanh;
using std::acoshf;
using std::asinhf;
using std::atanhf;
//glm part
using glm::lookAt;
using glm::perspective;
using glm::ortho;
using glm::radians;
using glm::scale;
using glm::rotate;
using glm::translate;
using glm::eulerAngles;

using glm::qua;
using glm::quat;
using glm::vec2;
using glm::vec3;
using glm::vec3;
using glm::dvec2;
using glm::dvec3;
using glm::dvec4;
using glm::ivec2;
using glm::ivec3;
using glm::ivec4;
using glm::uvec2;
using glm::uvec3;
using glm::uvec4;
using glm::mat2;
using glm::mat3;
using glm::mat4;
using glm::dmat2;
using glm::dmat3;
using glm::dmat4;

#endif //!DATA_TYPE_HPP_FILE